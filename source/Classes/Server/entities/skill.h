#ifndef SKILL_HPP_
#define SKILL_HPP_

#include "object.h"
#include <vector>
#include "../config/config.h"

#define UPDATETIME (200)

class EffectSpace {
public:
	EffectSpace(uint32_t effect_time, uint32_t dead_time);
	enum Status {
		IDLE = 1,
		EFFECT = 2,
		DEAD =3,
	};
	virtual ~EffectSpace(){};
	virtual bool effect(Entity* des, CSMonsterHitRsp* rsp)=0;
	virtual bool update();
	Status status() {
		return m_status;
	};
protected:
	Status m_status;
	uint32_t m_effect_time;
	uint32_t m_dead_time;
	uint32_t m_update_time;
//	Entity * m_attacker;
};

class EffectRec:public EffectSpace {
public:
	EffectRec(TileWorld<>::Rectangle rec, uint32_t effect_time, uint32_t dead_time);
	bool effect(Entity* des, CSMonsterHitRsp* rsp);
private:
typedef std::set<Entity*> EffectedList;
	TileWorld<>::Rectangle m_rec;
	EffectedList m_effected_list;
};

class MoveEffectRec: public EffectSpace {
public:
	MoveEffectRec(TileWorld<>::Rectangle rec, TileWorld<>::Point src, TileWorld<>::Point des, uint32_t speed, uint32_t effect_time);	
	~MoveEffectRec();	
	bool effect(Entity* des, CSMonsterHitRsp* rsp);
	bool update();
private:
	typedef std::set<Entity*> EffectedList;
	TileWorld<>::Rectangle m_rec;
	TileWorld<>::Point m_src;
	TileWorld<>::Point m_des;
	EffectedList m_effected_list;	
	uint32_t m_speed;
	uint32_t m_accumulate;
};

class EffectManager {
public:
	~EffectManager();
	void update();	
	void effect(Entity* des, CSMonsterHitRsp* rsp);	
	void add_effect(EffectSpace*);
private:
typedef	std::vector<EffectSpace*> EffectList;
	EffectList m_effect_list;
};

class Skill {
public:
	Skill(uint32_t id);
	uint32_t get_id();
	bool available();
	uint32_t get_effect_time(){return m_effect_time;};
	virtual uint32_t speed(){return 0;};
	virtual void update();
	virtual bool try_effect(Entity* src, Entity* des){return false;};
	virtual bool effect(Entity* src, Entity* des, TileWorld<>::Point& direct, EffectManager* pManager, CSMonsterAttackInfo* info);
	static Skill* generate_skill(uint32_t role_id, uint32_t id);
friend class SkillControl;
protected:
	uint32_t m_id;
	bool m_available;
	uint32_t m_effect_time;
	uint32_t m_dead_time;
	uint32_t m_update_time;
	uint32_t m_cool_down;
	
	uint32_t m_up_animation;
	uint32_t m_down_animation;
};

class SkillControl;

class VecSkill: public Skill {
public:
	VecSkill(uint32_t id);
	bool try_effect(Entity* src, Entity* des);
	bool effect(Entity* src, Entity* des, TileWorld<>::Point& direct, EffectManager* pManager, CSMonsterAttackInfo* info);
friend class SkillControl;
friend class Skill;
private:
	RecMap m_recs;
};

class MoveVecSkill: public Skill {
public:
	uint32_t speed(){return m_speed;};
	MoveVecSkill(uint32_t id);
	bool try_effect(Entity* src, Entity* des);
	bool effect(Entity* src, Entity* des, TileWorld<>::Point& direct, EffectManager* pManager, CSMonsterAttackInfo* info);
friend class SkillControl;
friend class Skill;
private:
	uint32_t m_speed;
	uint32_t m_dead_len;
	RecMap m_recs;
	OffsetMap m_offsets;
	uint32_t m_effect_id;
}; 

class TargetSkill: public Skill {
public:
	TargetSkill(uint32_t id);
	bool try_effect(Entity* src, Entity* des);
	bool effect(Entity* src, Entity* des, TileWorld<>::Point& direct, EffectManager* pManager, CSMonsterAttackInfo* info);
friend class SkillControl;
friend class Skill;
private:
	uint32_t m_release_time;
	uint32_t m_dead_len;
	uint32_t m_effect_id;
	RecMap m_recs;
};

class TargetVecSkill: public Skill {
public:
	TargetVecSkill(uint32_t id);
	bool try_effect(Entity* src, Entity* des);
	bool effect(Entity* src, Entity* des, TileWorld<>::Point& direct, EffectManager* pManager, CSMonsterAttackInfo* info);
friend class SkillControl;
friend class Skill;
private:
	uint32_t m_dead_len;
	uint32_t m_effect_id;
	RecMap m_recs;
};

class SkillControl {
public:
	SkillControl();
	
	~SkillControl();

	void generate_skills(const Monster_t& info);

	void add_skill(uint32_t id);	
	
	bool available();

	void update();

	bool try_effect(Entity* src, Entity* des);

	bool effect(Entity* src, Entity* des, TileWorld<>::Point& direct, EffectManager* pManager, CSMonsterAttackInfo* info);

	bool exchange_current(uint32_t id);

	Skill* current_skill();
	
	uint32_t current_skill_id();

private:
	typedef std::map<uint32_t, Skill*> SkillMap;
	SkillMap m_skill_map;
	uint32_t m_id;
};

#endif
