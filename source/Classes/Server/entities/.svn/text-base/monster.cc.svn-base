#include "monster.h"
#include "boss.h"
#include <assert.h>
#include <math.h>

RandomPatrolManager random_patrols; 

RandomPatrol::RandomPatrol(uint32_t speed2) {
	for(int i=2; i<=10; i++) {
		gen_.push(Vector2D(sqrtf(speed2/i), sqrtf(speed2 - speed2/i)));
	}
}
	
Vector2D RandomPatrol::getOne() {
	return gen_.get_one();
}
	
RandomPatrol* RandomPatrolManager::getRandomPatrol(uint32_t speed) {
	if(exist_key(speed)) {
		return get_ref_by_key(speed); 
	} else {
		RandomPatrol *pRandomPatrol = new RandomPatrol(speed);
		add_obj(pRandomPatrol);
		return pRandomPatrol;
	}
}
	
Hatred::Hatred():
	m_cool_time(0),
	m_current(NULL)
{

}
	
void Hatred::add(Entity* entity, uint32_t value) {
	if(m_hatred_map.find(entity) == m_hatred_map.end() ) {
		entity->sig_obj_del.connect(this,&Hatred::on_player_leave);
	}
	m_hatred_map[entity] += value;
}
	
void Hatred::on_player_leave(base::Object<uint32_t>* pPlayer) {
	m_hatred_map.erase(static_cast<Entity*>(pPlayer));
	if(m_current == pPlayer) {
		m_current = NULL;
	}
}
	
bool Hatred::exist(Entity* entity) {
	return m_hatred_map.find(entity) != m_hatred_map.end();
}
	
bool Hatred::empty() {
	return m_hatred_map.empty();
}
	
Entity* Hatred::get_current() {
	if(!m_current) {
		uint32_t max_hatred = 0;
		std::map<Entity*, uint32_t>::iterator itr = m_hatred_map.begin();
		for(; itr!= m_hatred_map.end(); ++itr) {
			if(itr->second > max_hatred) {
				max_hatred = itr->second;
				m_current = itr->first;
			}
		}
		m_cool_time = HATRED_FREQUENCY; 
		return m_current;
	} else if(m_cool_time) {
		m_cool_time--;
		return m_current;
	} else {
		uint32_t max_hatred = m_hatred_map[m_current] * 1.1;
		std::map<Entity*, uint32_t>::iterator itr = m_hatred_map.begin();
		for(; itr!= m_hatred_map.end(); ++itr) {
			if(itr->second > max_hatred) {
				max_hatred = itr->second;
				m_current = itr->first;
				m_cool_time = HATRED_FREQUENCY;
			}
		}
		return m_current;
	}
}
	
Monster::Monster(uint32_t random_id, TileWorld<>* tileworld, EffectManager* effect_manager) :
	Entity(random_id,MONSTER_DEFAULT_GROUP),
//	m_current_pskill(NULL),
	m_accumulate(0),
	m_pworld(tileworld),
	m_target_point(-1,-1),
	m_effect_manager(effect_manager)
{
}
		
Monster::~Monster() {
//	delete m_current_pskill;
}

void Monster::init_info(const Monster_t& info, const MapMonster_t& map_info) {
	m_fightprop.physical_attack = info.physical_attack;
	m_fightprop.magic_attack = info.magic_attack;
	m_fightprop.skill_attack = info.skill_attack;
	m_fightprop.physical_defence = info.physical_defence;
	m_fightprop.magic_defence = info.magic_defence;
	m_fightprop.skill_defence = info.skill_defence;
	m_fightprop.hit_rate = info.hit_rate;
	m_fightprop.dodge_rate = info.dodge_rate;
	m_fightprop.crit_rate = info.crit_rate;
	m_fightprop.crit_defence_rate = info.crit_defence_rate;
	m_fightprop.attack_type = info.attack_type;
	m_fightprop.attack_range_type = info.attack_range_type;
	m_prop.health_point = info.health_point;	
	m_prop.experience = info.experience;	
	m_prop.speed = info.speed;	
	type_id_ = info.id;
	boss_ 	 = info.is_boss;

	ObjectRange_t* range  = g_range_config->get_role_range_info(type_id_);
    if(range) {
        m_prop.space = range->body_range;
    } else {
        ERROR_LOG("ERROR MONSTER TYPE [type=%u]", get_type_id());
    }
//	m_current_pskill = Skill::generate_skill(type_id_, info.skills[0]);	
	m_skill_control.generate_skills(info);
	
/*ToDo hard code*/
	/*temp code */
	m_fightprop.vision = 20;

	m_pos = map_info.birth_place;
	m_patrol = map_info.patrol_place;
	stat_ = PATROL;
}

void Monster::dead() {
	delete this;
}
	
bool Monster::patrol() {
	if(stat_ == PATROL) {
		if(stop()) {
			TileWorld<>::Point end = m_patrol.get_one_path(m_pos);
			//DEBUG_LOG("FIND PATROL ID:%d :(%d , %d) TO (%d, %d)", get_id(), m_pos.x, m_pos.y, end.x, end.y );
			const TileWorld<>::Points* pPoints = m_pworld->findpath(m_pos, end);
			m_accumulate = 0; 
			if(pPoints) {
				m_road = *pPoints;
				m_road.push_back(m_pos);
			} else {
			//	DEBUG_LOG("FIND PATROL ERROR");
			}
			return true;
		} else {
	//		DEBUG_LOG("--------------------------BEGIN %d--------------------------------------",m_accumulate);
			m_pos = TileWorld<>::walk_path(m_road, m_direct, m_accumulate); 
	//		DEBUG_LOG("--------------------------END %d--------------------------------------",m_accumulate);
			return false;
		}
	}
	return false;
}
	
bool Monster::try_locking(Entity* pEntity) {
	if(	m_hatred.exist(pEntity)) {
		return true;
	}
	if( (uint32_t) (m_pos.distance2(pEntity->m_pos) ) <= m_fightprop.vision * m_fightprop.vision ) 
	{
		m_hatred.add(pEntity);
		DEBUG_LOG("MONSTER %d ADD LOCKING %d",get_id(), pEntity->get_id());
		pEntity->sig_obj_del.connect(this,&Monster::on_player_leave);
		stat_ = LOCKING;
		return true;
	}
	return false;
}
	
bool Monster::locking(CSMonsterAttackRsp* attack_rsp) {
	Entity* enemy = m_hatred.get_current();
	if(enemy) {
		if(attack_check(enemy)) {
	//		DEBUG_LOG("MONSTER %d ATTACK CHECK OK SKILL:%d",get_id(),m_current_pskill->get_id());
			do_attack(enemy, attack_rsp);
			m_accumulate = 0;
			return false;
		}
		walk_to(enemy);
		return true;
	} else {
		stat_ = PATROL;
	}
	return false;
}
	
bool Monster::attack_check(Entity* des) {
//	if( m_current_pskill) {
	if(m_skill_control.available()) {
		return m_skill_control.try_effect(this, des);
//		return m_current_pskill->try_effect(this, des);
	} else {
		ERROR_LOG("MONSTER %d NO SKILL",get_id());
	}
	return false;
}
	
void Monster::do_attack(Entity* pEntity, CSMonsterAttackRsp* attack_msg ) {
/*
message CSMonsterAttackInfo {
    required uint32 id = 1;  //怪物在副本中的ID
    required CSPoint pos = 2; //怪物的位置
    required CSPoint direct = 3;//怪物的方向
    required uint32 action_id = 4; //动作ID
}
*/
//	if(m_current_pskill && m_current_pskill->available()) {
	if(m_skill_control.available()) {
			CSMonsterAttackInfo* info = attack_msg->add_attacks();
			info->set_id(get_id());
			m_direct = (pEntity->m_pos - m_pos);
			m_direct.unitised();
//			m_current_pskill->effect(this, pEntity, m_direct, m_effect_manager, info) ;
			m_skill_control.effect(this, pEntity, m_direct, m_effect_manager, info) ;
			DEBUG_LOG("MONSTER %d DO ATTACK SKILL:%d POS:(%d %d) USER POS(%d %d)",get_id(),m_skill_control.current_skill_id(),m_pos.x, m_pos.y, pEntity->m_pos.x, pEntity->m_pos.y);
			m_road.clear();
			info->set_id(get_id());	
			CSPoint* pos = info->mutable_pos();
			pos->set_xpos(m_pos.x);	
			pos->set_ypos(m_pos.y);	
			CSPoint* direct = info->mutable_direct();
			direct->set_xpos(m_direct.x);
			direct->set_ypos(m_direct.y);
			info->set_userid(pEntity->get_id());
	}
}
	
bool Monster::walk_to(Entity* pEntity) {
	/*magic_number 4*/
	if(!stop()) {
		m_pos = TileWorld<>::walk_path(m_road, m_direct, m_accumulate); 
	}
	if( m_target_point.distance2(pEntity->m_pos) >= 25 || m_pos.distance2(pEntity->m_pos) <= 36 || stop()  ) 
	{
		DEBUG_LOG("LOCKING ID:%d WALK FROM :(%d , %d) TO (%d, %d) ID:%d", get_id(), m_pos.x, m_pos.y, pEntity->m_pos.x, pEntity->m_pos.y, pEntity->get_id() );
		if(pEntity->m_pos == m_pos) {
			m_road.clear();
			m_target_point = pEntity->m_pos;
			return false;
		}
		const TileWorld<>::Points* pPoints = m_pworld->findpath(m_pos, pEntity->m_pos);
		if(pPoints) {
			m_road = *(pPoints);	
			m_road.push_back(m_pos);
			m_target_point = pEntity->m_pos;
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}
	
void Monster::update(CSMonsterMoveRsp* move_rsp, CSMonsterAttackRsp* attack_rsp) {
	/*Todo must update all skill*/
	//DEBUG_LOG("UPDATE POS %d %d",m_pos.x, m_pos.y);
/*	if( m_current_pskill && !m_current_pskill->available()) {
		m_current_pskill->update();
	}
	if(!m_current_pskill->available()) {
		return ;
	}*/
	if(!m_skill_control.available()) {
		m_skill_control.update();	
	}
	if(!m_skill_control.available()) {
		return ;
	}
	/*Todo must delete such code*/
	if(stat_!= IDLE) {
		m_accumulate += m_prop.speed * 10 *	UPDATETIME / 1000;
	}
	switch (stat_) {
		case IDLE:
			{
				if(!m_hatred.empty()) {
					stat_ = LOCKING;
				} else {
					stat_ = PATROL;
				}
				DEBUG_LOG("STATUS IDLE");
			}
			break;
		case PATROL:
			{
				//if(patrol()) {
					patrol();
					MonsterMoveValue * move = move_rsp->add_moves();
					pack_move(move);
				//};
			}
			break;
		case LOCKING:
			{
				if(locking(attack_rsp)) {
					MonsterMoveValue * move = move_rsp->add_moves();
					pack_move(move);
				};
			}
			break;
	} 
}
	
void Monster::on_player_leave(base::Object<uint32_t>* obj) {
	if(m_hatred.empty()) {
		stat_ = PATROL;
		m_target_point  = TileWorld<>::Point(-1, -1);
	}
}
	
void Monster::under_attack(Entity* pEntity, uint32_t blood) {
	if(m_prop.health_point >blood ) {
		m_prop.health_point-=blood;
	} else {
		m_prop.health_point = 0;
	}
	m_hatred.add(pEntity, 10);
}
	
void Monster::under_attack_back(const TileWorld<>::Point& point) {
	m_pos = point;
	m_road.clear();
	stat_ = IDLE;
	DEBUG_LOG("MONSTER %d UNDER ATTACK",get_id());
}
	
bool Monster::stop() {
	if(m_road.empty() || (m_road.front() == m_pos )) {
		return true;
	}
	return false;
}
	
void Monster::pack_move(MonsterMoveValue* move_msg) {
	move_msg->set_id(get_id());
	CSPoint * direct = move_msg->mutable_direct();
	direct->set_xpos(m_direct.x);	
	direct->set_ypos(m_direct.y);
	TileWorld<>::Points::reverse_iterator itr = m_road.rbegin();
	for(; itr!=m_road.rend(); ++itr) {
		CSPoint* one_path = move_msg->add_paths();
		one_path->set_xpos(itr->x);
		one_path->set_ypos(itr->y);
//		DEBUG_LOG("POINT: %d %d", itr->x, itr->y);
	}
}
	
MonsterManager::MonsterManager():
	m_increase_key(1)
{
}
	
void MonsterManager::add_monster(MapMonster_t * mapmonster, TileWorld<>* world, EffectManager* effect_manager) {
	assert(mapmonster);
	assert(world);
	Monster_t* pmonster_t = g_monster_config->get_monster_info(mapmonster->monster_id);	
	assert(pmonster_t);
	Monster * pmonster = NULL;
	switch(mapmonster->monster_id) {
		case 19002: //MonsterID="19002" Name="花妖"
		{
			pmonster = new FlowerDemon(mapmonster->raid_id, world, effect_manager);	
		}
		break;
		default:
			pmonster = new Monster(mapmonster->raid_id, world, effect_manager);	
	}
	pmonster->init_info(*pmonster_t, *mapmonster);
	add_obj(pmonster);	 
}	
	
int MonsterManager::update(CSMonsterMoveRsp* move_rsp, CSMonsterAttackRsp* attack_rsp) {
	Monster * pmonster = next_ref(NULL);
	for (; pmonster!=NULL;) {
		pmonster->update(move_rsp, attack_rsp);
		pmonster = next_ref(pmonster);	
	} 
	return 0;
}
	
void MonsterManager::pack_move(CSMonsterMoveRsp* rsp) {
	Monster * pmonster = next_ref(NULL);
	for (; pmonster!=NULL;) {
		MonsterMoveValue* one = rsp->add_moves();
		pmonster->pack_move(one);
		pmonster = next_ref(pmonster);
	}	
}
	
void MonsterManager::try_locking(Entity* pEntity) {
	Monster * pmonster = next_ref(NULL);
	for(; pmonster!= NULL;)	{
		pmonster->try_locking(pEntity);
		pmonster = next_ref(pmonster);
	}
}
