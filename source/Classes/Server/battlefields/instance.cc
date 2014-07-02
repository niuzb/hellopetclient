#include "instance.h"
#include "errcode.pb.h"
	
Instance::Instance(uint32_t instance_id, InstanceType type):
	m_instance_id(instance_id),
	m_current_map_id(0),
	m_type(type)
{
	/*get first map_info*/
	MapContent_t* mapcontent  = g_mapcontent_config->get_mapcontent_info(m_instance_id, 0);
	assert(mapcontent);
	m_current_map_id = mapcontent->map_id;
}
	
int Instance::init() {
	if(!empty() && m_current_map_id) {
		Player* pPlayer = next_ref(NULL);
		if(pPlayer) {
			sBattlefield.create_battle(pPlayer, m_instance_id, m_current_map_id);
			Battlefield* pbattle = sBattlefield.get_battle(pPlayer); 
			if(pbattle) {
				pPlayer = next_ref(pPlayer);
				while(pPlayer) {
					pbattle->player_join(pPlayer);
					pPlayer = next_ref(pPlayer);
				}
				m_battlefields.add_obj(pbattle);
				pbattle->sig_obj_del.connect(this,&Instance::on_battle_leave);
				
				CSBattleCreateRsp rsp;			
				pbattle->pack_main_info(&rsp);
				pPlayer = next_ref(NULL);
				while(pPlayer) {
					m_user_complete[pPlayer] = false;
					pPlayer->send_msg(rsp);
					pPlayer = next_ref(pPlayer);
				}
				if(m_type == PPVE) { 	
					sGloble.Timer.add_event(*this, &Instance::start_battle, m_current_map_id, base::Time()+LOADWAITTIMEOUT);
				}
			}
		}
	}
	return 0;
}
	
int Instance::join_timeout(uint32_t& map_id) {
	if(map_id == m_current_map_id) {
		Battlefield* pbattle = m_battlefields.get_ref_by_key(map_id);
		if(pbattle) {
			Player* pPlayer = next_ref(NULL);	
			while(pPlayer) {
				Battlefield* pbattle_now = static_cast<Battlefield*>(sBattlefield.get_manager_by_key(pPlayer->get_id()));
				if(pbattle_now != pbattle) {
					pbattle_now->reduce_obj(pPlayer);
					pbattle->player_join(pPlayer);	
					CSBattleCreateRsp rsp;			
					pbattle->pack_main_info(&rsp);
					pPlayer->send_msg(rsp);	
				}
				pPlayer = next_ref(pPlayer);
			}
			sGloble.Timer.add_event(*this, &Instance::start_battle, map_id, base::Time()+LOADWAITTIMEOUT);
		}
	}
	return 0;
}
	
int Instance::start_battle(uint32_t& map_id) {
	Battlefield* pbattle = m_battlefields.get_ref_by_key(map_id);
	if(pbattle) {
		CompleteMap::iterator itr = m_user_complete.begin();
		for(; itr!= m_user_complete.end(); ++ itr) {
			itr->second = false;
		}
		pbattle->set_complete();
	}
	return 0;
}
	
void Instance::transfer_next(Player* pPlayer) {
	Battlefield* pbattle_now = static_cast<Battlefield*>(sBattlefield.get_manager_by_key(pPlayer->get_id()));
	if(pbattle_now && pbattle_now->monster_clear()) {
		pbattle_now->reduce_obj(pPlayer);
		MapContent_t* mapcontent  = g_mapcontent_config->get_mapcontent_info(m_instance_id, pbattle_now->get_map_id());
		assert(mapcontent);
		m_current_map_id = mapcontent->trans_des;
		if(m_current_map_id) {
			Battlefield* pbattle = m_battlefields.get_ref_by_key(m_current_map_id);
			if(pbattle) {
				pbattle->player_join(pPlayer);
			} else {
				pbattle = sBattlefield.create_battle(pPlayer, m_instance_id, m_current_map_id);
				if(pbattle) { 
					m_battlefields.add_obj(pbattle);
					if(m_type == PPVE) {
						sGloble.Timer.add_event(*this, &Instance::join_timeout, m_current_map_id, base::Time()+JOINTWAITTIMEOUT);
					}
				}
			}
			if(pbattle) {
				CSBattleCreateRsp rsp;			
				pbattle->pack_main_info(&rsp);
				pPlayer->send_msg(rsp);
			}
		}
	} else {
		pPlayer->send_stderr(olerr_can_transfer_next);
	}
}
	
void Instance::on_player_leave(base::Manager<Player>*, Player* pPlayer) {
	m_user_complete.erase(pPlayer);	
	CompleteMap::iterator itr = m_user_complete.begin();
	for(; itr!= m_user_complete.end(); ++ itr) {
		if(!itr->second) {
			return ;
		}
	}
	start_battle(m_current_map_id);
}
	
void Instance::load_complete(Player* pPlayer) {
	m_user_complete[pPlayer] = true;
	Battlefield* pbattle = m_battlefields.get_ref_by_key(m_current_map_id);
	if(pbattle) {
		Player* pPlayer_join = pbattle->next_ref(NULL);
		CSBattleUserJoinRsp rsp;
		while(pPlayer_join) {
			if(pPlayer != pPlayer_join) {
				BasicUserInfo * info = rsp.add_userinfo();
				pPlayer_join->pack_basic_info(info);
			}
			pPlayer_join = pbattle->next_ref(pPlayer_join);
		}
		pPlayer->send_msg(rsp);
	}
	CompleteMap::iterator itr = m_user_complete.begin();
	for(; itr!= m_user_complete.end(); ++ itr) {
		if(!itr->second) {
			return ;
		}
	}
	start_battle(m_current_map_id);
}
	
void Instance::on_battle_leave(base::Object<uint32_t>* pbattle) {
	if(m_battlefields.empty()) {
		delete this;
	}
}

int sInstanceManager::create_instance(Player* pPlayer, uint32_t instance_id) {
	DEBUG_LOG("PLAYER :%d CREATE INSTANCE %d ",pPlayer->get_id(), instance_id);
	Instance_t* instance = g_mapcontent_config->get_instance_info(instance_id);
	if(instance) {
		Instance* pinstance = new Instance(instance_id, (InstanceType)instance->type);
		add_manager(pinstance);
		pinstance->add_obj(pPlayer);
		return 0;
	}
	return 0;
}
	
int sInstanceManager::load_complete(Player* pPlayer) {
	DEBUG_LOG("PLAYER :%d LOAD COMPLETE",pPlayer->get_id());
	Instance* pinstance = static_cast<Instance*>(get_manager_by_key(pPlayer->get_id()));
	if(pinstance) {	
		pinstance->load_complete(pPlayer);
	}
	return 0;
}
	
int sInstanceManager::transfer_next(Player* pPlayer) {
	DEBUG_LOG("PLAYER :%d TRANSFER NEXT INSTANCE",pPlayer->get_id());
	Instance* pinstance = static_cast<Instance*>(get_manager_by_key(pPlayer->get_id()));
	if(pinstance) {	
		pinstance->transfer_next(pPlayer);
	}
	return 0;
}
	
int sInstanceManager::join_instance(Player* pPlayer, Player* owner) {
	DEBUG_LOG("PLAYER :%d JOIN INSTANCE OWNER: %d",pPlayer->get_id(), owner->get_id());
	Instance* pinstance = static_cast<Instance*>(get_manager_by_key(owner->get_id()));	
	if(pinstance) {
		pinstance->add_obj(pPlayer);
	}
	return 0;
}
	
int sInstanceManager::init_instance(Player* owner) {
	Instance* pinstance = static_cast<Instance*>(get_manager_by_key(owner->get_id()));	
	if(pinstance) {
		return pinstance->init();
	}
	return 0;
}
	
int sInstanceManager::leave_instance(Player* pPlayer) {
	Instance* pinstance = static_cast<Instance*>(get_manager_by_key(pPlayer->get_id()));	
	if(pinstance) {
		pinstance->reduce_obj(pPlayer);
	}
	return 0;
}
