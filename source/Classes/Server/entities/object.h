#ifndef RU_OBJECT_H_
#define RU_OBJECT_H_
#include <stdint.h>
#include "../base/Manager.hpp"
#include "../battlefields/tileworld.hpp"
#include "cs_battle.pb.h"

#define PLAYER_MIN 10000

#define MONSTER_MIN 2000

#define MONSTER_MAX 1000


#define PLAYER_DEFAULT_GROUP (1)
#define MONSTER_DEFAULT_GROUP (1<<2)

using namespace taomee;
using namespace google::protobuf;
/**
 * @brief 所有物体（玩家、怪物、伙伴、宝箱、陷阱等等）的基类
 */
class Object {
public:
	virtual ~Object() { }
	virtual void update() = 0;

private:
};

class FightProp {
public:
	uint32_t physical_attack;
	uint32_t magic_attack;
	uint32_t skill_attack;
	uint32_t physical_defence;
	uint32_t magic_defence;
	uint32_t skill_defence;
	uint32_t hit_rate;
	uint32_t dodge_rate;
	uint32_t crit_rate;
	uint32_t crit_defence_rate;
	uint32_t attack_type;
	uint32_t attack_range_type;
	uint32_t vision;
	TileWorld<>::Rectangle fight_rec1;
	TileWorld<>::Rectangle fight_rec2;
	TileWorld<>::Rectangle fight_rec3;
	TileWorld<>::Rectangle fight_rec4;
};

class Prop {
public:
	uint32_t health_point;
	uint32_t experience;
	uint32_t speed;
	TileWorld<>::Rectangle space;
};

class Entity: public base::Object<uint32_t> {
public:
	Entity(uint32_t id=0, uint8_t groupid=0);

	TileWorld<>::Rectangle space();

	bool attack_check(Entity* pEntity);
	
	void attack(Entity* pEntity);

	void skill(Entity* pEntity, uint32_t skill_id);
	
	virtual void under_attack(Entity* pEntity) {};

	virtual void under_skill(Entity* pEntity, uint32_t skill_id) {};

	virtual bool attach(const TileWorld<>::Point& point, uint8_t rule );
	
	virtual bool attach(const TileWorld<>::Rectangle& rec, uint8_t rule );


public:
	uint8_t m_groupid;

	FightProp m_fightprop;

	Prop m_prop;

	TileWorld<>::Point m_pos;
	
	TileWorld<>::Point m_direct;
};

#endif // RU_OBJECT_H_
