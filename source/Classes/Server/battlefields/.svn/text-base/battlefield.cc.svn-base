// project-specific headers go here
#include "battlefield.h"
#include "../base/Time.hpp"

#include "cs_battle.pb.h"

using namespace google::protobuf;

Battlefield::Battlefield(Player* pPlayer, uint32_t battle_id, uint32_t map_id) :
	base::Object<uint32_t>(map_id),
	m_battle_id(battle_id),
	owner(pPlayer),
	m_complete(false)
{
	init_map(map_id);
	if(pPlayer) {
		player_join(pPlayer);
	}
	sig_obj_post_decrease.connect(this, &Battlefield::on_player_leave);
}

void Battlefield::player_join(Player* pPlayer) 
{
	pPlayer->m_pos = m_hero_born;
	if(pPlayer != owner) {
		CSBattleUserJoinRsp rsp;
		BasicUserInfo * info = rsp.add_userinfo();
		pPlayer->pack_basic_info(info);
		send_to_players(rsp);
	}
	add_obj(pPlayer);
}

void Battlefield::attack(Player *pPlayer, const CSPlayerAttackReq * req) {
/*Todo must check the available of action*/
	CSPlayerAttackRsp attack_rsp;
	CSMonsterBloodRsp blood_rsp;
	CSMonsterDieRsp rsp;

/*
message CSPlayerAttackReq { //用户打击怪物
    required uint32 userid = 1; //用户ID
    required CSPoint start_pos = 2; //开始位置
    required CSPoint start_direct = 3; //开始方向
    required CSPoint end_pos = 4; //结束位置
    required CSPoint end_direct = 5; //结束方向
    required uint32 action_id = 6; //动作ID
    repeated AttackMonsterInfo monsters = 7; //被攻击怪物信息
}
 
*/
	
	pPlayer->m_pos = TileWorld<>::Point(req->end_pos().xpos(), req->end_pos().ypos());

	attack_rsp.set_userid(req->userid());
	CSPoint* start_point = attack_rsp.mutable_start_pos();
	start_point->set_xpos(req->start_pos().xpos());
	start_point->set_ypos(req->start_pos().ypos());

	CSPoint* start_direct = attack_rsp.mutable_start_direct();
	start_direct->set_xpos(req->start_direct().xpos());
	start_direct->set_ypos(req->start_direct().ypos());
	
	CSPoint* end_point = attack_rsp.mutable_end_pos();
	end_point->set_xpos(req->end_pos().xpos());
	end_point->set_ypos(req->end_pos().ypos());
	
	CSPoint* end_direct = attack_rsp.mutable_end_direct();
	end_direct->set_xpos(req->end_direct().xpos());
	end_direct->set_ypos(req->end_direct().ypos());

	attack_rsp.set_action_id(req->action_id());
	
	for(int i =0; i<req->monsters_size(); i++) {
		AttackMonsterInfo info = req->monsters(i);
		*attack_rsp.mutable_monsters() = req->monsters();
		Monster *pmonster = monsters_.get_ref_by_key(info.id());
		if(pmonster) {
			pmonster->under_attack_back(TileWorld<>::Point(info.pos().xpos(), info.pos().ypos()));
			pmonster->under_attack(pPlayer, info.blood());
			CSAttackMonsterBackInfo* rsp_info = blood_rsp.add_monsters();
			rsp_info->set_blood(pmonster->m_prop.health_point);
			rsp_info->set_id(pmonster->get_id());
			if(!pmonster->m_prop.health_point) {
				rsp.add_monsters(pmonster->get_id());				
				delete pmonster;
			}
			DEBUG_LOG("USER :%d ATTACK MONSTER:%d HEALTH:%d POS:%d %d", pPlayer->get_id(), pmonster->get_id(), pmonster->m_prop.health_point, info.pos().xpos(), info.pos().ypos());
		} else {
			ERROR_LOG("USER :%d ERROR ATTACK MONSTER %d",pPlayer->get_id(), info.id());
		}
	}
	send_to_players(attack_rsp);
	send_to_players(blood_rsp);
	send_to_players(rsp);
}
	
void Battlefield::skill_begin(Player *pPlayer, const CSSkillBeginReq * req) {
/*
message CSSkillBeginReq {
    required uint32 userid = 1;
    required CSPoint pos   = 2;
    required CSPoint target_pos = 3;
    required float   direct_x   = 4;
    required float   direct_y   = 5;
    required bool    aim        = 6;
}
*/
	CSSkillBeginRsp rsp;
	rsp.set_action_id(req->action_id());
	rsp.set_userid(req->userid());
	CSPoint* pos = rsp.mutable_pos();
	pos->set_xpos(req->pos().xpos());
	pos->set_ypos(req->pos().ypos());
#if 1	// lyle add 2013-04-12 (确认该加请del 注释)
	rsp.set_start_dir_x(req->start_dir_x());
	rsp.set_start_dir_y(req->start_dir_y());
#endif
	CSPoint* target_pos  = rsp.mutable_target_pos();
	target_pos->set_xpos(req->target_pos().xpos());
	target_pos->set_ypos(req->target_pos().ypos());
	rsp.set_direct_x(req->direct_x());
	rsp.set_direct_y(req->direct_y());
	rsp.set_aim(req->aim());
	send_to_players(rsp);
}

void Battlefield::move(Player* pPlayer, TileWorld<>::Point& pos, TileWorld<>::Point& direct) {
/*Todo must check the available of move*/
	DEBUG_LOG("PLAYER MOVE TO: %d %d", pos.x, pos.y);
	pPlayer->m_pos = pos;
	pPlayer->m_direct = direct;
	CSBattleMoveRsp rsp;
	rsp.set_id(pPlayer->get_id());
	rsp.set_time(0);

	CSPoint* one_point =rsp.mutable_pos();
	one_point->set_xpos(pPlayer->m_pos.x);
	one_point->set_ypos(pPlayer->m_pos.y);
	CSPoint* one_direct =rsp.mutable_direct();
	one_direct->set_xpos(pPlayer->m_direct.x);
	one_direct->set_ypos(pPlayer->m_direct.y);
	send_to_players(rsp);
}

int Battlefield::update() {
	if(monster_clear() && !get_next_map_id()) {
		Player* pPlayer = next_ref(NULL);
		while(pPlayer !=NULL) {
			CSBattleLeaveRsp leave_rsp;
			leave_rsp.set_initiative(false);
			/*2 means temp code*/
			leave_rsp.set_star(2);
			pPlayer->finish_instance(m_battle_id, 2, leave_rsp);
			pPlayer->send_msg(leave_rsp);
			pPlayer = next_ref(pPlayer);
		}
		delete this;
		return 0;
	}
	if(empty()) {
		delete this;
		return 0;
	}
	CSMonsterHitRsp hit_rsp;
	m_effect_manager.update();
	CSMonsterMoveRsp move_rsp;
	CSMonsterAttackRsp attack_rsp;
	monsters_.update(&move_rsp, &attack_rsp);
	if(move_rsp.moves_size()) {
		//DEBUG_LOG("%s",move_rsp.DebugString().c_str());
		send_to_players(move_rsp);
	}
	if(attack_rsp.attacks_size()) {
		send_to_players(attack_rsp);
	}
	Player* pPlayer = next_ref(NULL);
	while(pPlayer != NULL) {
		monsters_.try_locking(pPlayer);
		m_effect_manager.effect(pPlayer, &hit_rsp);
		pPlayer = next_ref(pPlayer);
	}
	if(hit_rsp.users_size()) {
		send_to_players(hit_rsp);
	}
	return 0;
}
	
void Battlefield::on_player_leave(base::Manager<Player>*, Player* pPlayer) {
	DEBUG_LOG("PLAYER :%d LEAVE",pPlayer->get_id());
	if(owner == pPlayer) {
		owner = NULL;
	}
	CSBattleUserLeaveRsp rsp;
	rsp.set_userid(pPlayer->get_id());
	send_to_players_except(rsp, pPlayer);
}

void Battlefield::send_to_players(const Message& msg) {
	Player* pPlayer = next_ref(NULL);
	while (pPlayer) {
		pPlayer->send_msg(msg);
		pPlayer = next_ref(pPlayer);
	}
}
	
void Battlefield::send_to_players_except(const google::protobuf::Message& msg, Player* p) {
	Player* pPlayer = next_ref(NULL);
	while (pPlayer) {
		if(p != pPlayer) {
			pPlayer->send_msg(msg);
			pPlayer = next_ref(pPlayer);
		}
	}
}

void Battlefield::init_map(uint32_t map_id) {
	MapContent_t* mapcontent  = g_mapcontent_config->get_mapcontent_info(m_battle_id, map_id);
	m_tile_world = g_tile_config->get_tile_info(mapcontent->map_id);
	assert(m_tile_world);
	std::vector<MapMonster_t>::iterator itr = mapcontent->monsters.begin();
	for(; itr!=mapcontent->monsters.end(); ++itr) {
		monsters_.add_monster(&(*itr), m_tile_world, &m_effect_manager );
	}
	if(owner) owner->m_pos = mapcontent->user_birth_place;
	m_hero_born = mapcontent -> user_birth_place;
	m_portal = mapcontent -> trans_place;
	m_map_id = mapcontent -> map_id;
	m_next_map_id = mapcontent->trans_des;
}

void Battlefield::pack_main_info(CSBattleCreateRsp* rsp) {
	Player* pPlayer = next_ref(NULL);
	while(pPlayer!=NULL) {
		BasicUserInfo* info = rsp->add_userinfo();
		pPlayer->pack_basic_info(info);
		pPlayer = next_ref(pPlayer);
	}
	Monster* monster = monsters_.next_ref(NULL);
	while(monster != NULL) {
		MonsterInfo* monsterinfo = rsp->add_monsterinfo();
		monsterinfo->set_id(monster->get_id());
		monsterinfo->set_type_id(monster->get_type_id());
		monsterinfo->set_level(monster->get_level());
		monsterinfo->set_blood(monster->m_prop.health_point);
		monsterinfo->set_boss(monster->is_boss() != 0);
		monsterinfo->set_speed(monster->get_speed());
		CSPoint* point = monsterinfo->mutable_point();
		point->set_xpos(monster->m_pos.x);
		point->set_ypos(monster->m_pos.y);
		CSPoint* direct = monsterinfo->mutable_direct();
		direct->set_xpos(monster->m_direct.x);
		direct->set_ypos(monster->m_direct.y);
		MonsterMoveValue * moves = monsterinfo->mutable_moves();
		monster->pack_move(moves);
		monster = monsters_.next_ref(monster);
	}
	rsp->set_battle_id(get_battle_id());
	rsp->set_map_id(get_map_id());
	CSPoint* portal = rsp->mutable_portal();
	portal->set_xpos(m_portal.x);
	portal->set_ypos(m_portal.y);
	rsp->set_portal_map_id(get_next_map_id());
}
	
bool Battlefield::monster_clear() {
	return  monsters_.empty(); 
}
	
uint32_t Battlefield::get_map_id() {
	return m_map_id;
}
	
uint32_t Battlefield::get_next_map_id() {
	return m_next_map_id;
}
	
Battlefield::IdType Battlefield::get_battle_id() {
	return m_battle_id;
}
	
Player* Battlefield::get_owner() {
	return owner;
}

bool Battlefield::get_complete() {
	return m_complete;
}
	
void Battlefield::set_complete() {
	if(!m_complete) {
		m_complete = true;
		sGloble.Timer.add_event(*this, &Battlefield::update, base::Time(), UPDATETIME, -1);
	}
}

BattlefieldManager::BattlefieldManager():
	tmp_battle(NULL) {
};

Battlefield* BattlefieldManager::create_battle(Player* pPlayer, uint32_t battle_id, uint32_t map_id) {
	Battlefield* pbattle = static_cast<Battlefield*>(get_manager_by_key(pPlayer->get_id()));
	if(pbattle) {
		pbattle->reduce_obj(pPlayer);
	};
	Instance_t* instance = g_mapcontent_config->get_instance_info(battle_id);	
	if(instance) {
		pbattle = new Battlefield(pPlayer, battle_id, map_id);
		add_manager(pbattle);
	} else {
		DEBUG_LOG("ERROR BATTLE_ID:%d",battle_id);
	}
	return pbattle;
}
	
Battlefield* BattlefieldManager::get_battle(Player* pPlayer) {
	return static_cast<Battlefield*>(get_manager_by_key(pPlayer->get_id()));
}
	
int BattlefieldManager::leave_battle(Player* pPlayer) {
	Battlefield* pbattle = static_cast<Battlefield*>(get_manager_by_key(pPlayer->get_id()));
	if(pbattle) {
		pbattle->reduce_obj(pPlayer);
	}
	CSBattleLeaveRsp rsp;
	rsp.set_initiative(true);
	pPlayer->send_msg(rsp);
	
	return 0;
}

int BattlefieldManager::player_attack(Player* pPlayer,const CSPlayerAttackReq * req) {
	Battlefield* pbattle = static_cast<Battlefield*>(get_manager_by_key(pPlayer->get_id()));
	if(pbattle) {
		//DEBUG_LOG("RECV ATTACK ID:%s",req->DebugString().c_str());
		pbattle->attack(pPlayer, req);
		return 0;
	} else {
		ERROR_LOG("%d ATTACK WITHOUT BATTLE",pPlayer->get_id());
	}
	return 0;
}
	
int BattlefieldManager::skill_begin(Player* pPlayer, const CSSkillBeginReq * req) {
	Battlefield* pbattle = static_cast<Battlefield*>(get_manager_by_key(pPlayer->get_id()));
	if(pbattle) {
		//DEBUG_LOG("RECV ATTACK ID:%s",req->DebugString().c_str());
		pbattle->skill_begin(pPlayer, req);
		return 0;
	} else {
		ERROR_LOG("%d ATTACK WITHOUT BATTLE",pPlayer->get_id());
	}
	return 0;
}

int BattlefieldManager::move(Player* pPlayer, TileWorld<>::Point& pos, TileWorld<>::Point& direct) {
	Battlefield* pbattle = static_cast<Battlefield*>(get_manager_by_key(pPlayer->get_id()));
	if(pbattle) {
		pbattle -> move(pPlayer, pos, direct);
	} else {
		DEBUG_LOG("%d MOVE WITHOUT BATTLE",pPlayer->get_id());
	}
	return 0;
}
	
bool BattlefieldManager::exist(const Player* pPlayer) {
	return exist_obj(pPlayer);
}
	
uint32_t BattlefieldManager::map_id(Player* pPlayer) {
	Battlefield* pbattle = static_cast<Battlefield*>(get_manager_by_key(pPlayer->get_id()));
	if(pbattle) {
		return 	pbattle -> get_map_id();
	} else {
		return 0;
	}
}

