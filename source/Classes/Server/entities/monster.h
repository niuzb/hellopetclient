#ifndef MONSTER_H_
#define MONSTER_H_
#include "../base/Manager.hpp"
#include "../base/ProbabilityGen.hpp"
#include "../base/Vector.hpp"

#include "cs_battle.pb.h"
#include "object.h"
#include "../config/config.h"
#include "skill.h"

using namespace taomee;
using namespace base;

class RandomPatrol: public base::Object<uint32_t> {
public:
	RandomPatrol(uint32_t speed);

	Vector2D getOne();

private:
	base::AverageGen<Vector2D> gen_;	
};

class RandomPatrolManager: public base::Manager<RandomPatrol> {
public:
	RandomPatrol* getRandomPatrol(uint32_t speed);

};

extern RandomPatrolManager random_patrols; 

#define HATRED_FREQUENCY (4)
#define HATRED_BASE		(10)

class Hatred:public sigslot::has_slots<> {
public:
	Hatred();	

	void add(Entity* entity, uint32_t value=HATRED_BASE);
	
	void on_player_leave(base::Object<uint32_t>* pPlayer);

	bool exist(Entity* entity);

	bool empty();

	Entity* get_current();	

private:
	std::map<Entity*, uint32_t> m_hatred_map;
	uint32_t m_cool_time;
	Entity* m_current;
};

class Monster : public Entity, public sigslot::has_slots<> {
public:
	Monster(uint32_t random_id, TileWorld<>* tileworld, EffectManager* effect_manager);
	
	~Monster();

	void init_info(const Monster_t& info, const MapMonster_t& map_info);

	enum MonsterStat {
		PATROL = 1,
		LOCKING = 2,
		IDLE = 3,
	};
	
	void dead();
	
	bool patrol();	
	
	bool locking(CSMonsterAttackRsp* attack_rsp);	

	bool try_locking(Entity* pEntity);

	bool walk_to(Entity* pEntity);

	void update(CSMonsterMoveRsp* move_rsp, CSMonsterAttackRsp* attack_rsp);

	void on_player_leave(base::Object<uint32_t>* pPlayer);

	void under_attack(Entity* pEntity, uint32_t blood);

	void under_attack_back(const TileWorld<>::Point& point);

	bool stop();

	void pack_move(MonsterMoveValue* move_msg);

	uint32_t get_type_id() {return type_id_;}
	
	uint32_t get_level() {return level_;}
	
	uint32_t is_boss() {return boss_;}
	
	uint32_t get_speed() {return m_prop.speed;}

	bool attack_check(Entity* des);

	virtual	void do_attack(Entity* pEntity, CSMonsterAttackRsp* attack_msg );

protected:

	Hatred m_hatred;

//	Skill* m_current_pskill;
	SkillControl m_skill_control;

public:

private:
	
	/*attributes*/
	MonsterStat stat_;
	
	uint32_t type_id_;

	uint32_t level_;
	
	bool boss_;

	uint32_t m_accumulate;
	
	TileWorld<>::RandomRangePath m_patrol;	

	TileWorld<>* m_pworld;	

	TileWorld<>::Points m_road;	

	TileWorld<>::Point m_target_point;
	
	EffectManager* m_effect_manager;
};

class MonsterManager: public base::Manager<Monster> {
public:
	MonsterManager();

	void add_monster(MapMonster_t * mapmonster, TileWorld<>* world, EffectManager* effect_manager);

	int update(CSMonsterMoveRsp* move_rsp, CSMonsterAttackRsp* attack_rsp);

	void pack_move(CSMonsterMoveRsp *rsp);
	
	void try_locking(Entity* pEntity);
private:
	uint32_t m_increase_key;
};

#endif
