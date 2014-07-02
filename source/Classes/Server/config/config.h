#ifndef BATTLECONFIG_HPP_
#define BATTLECONFIG_HPP_

#include "../log.h"

#include <string>
#include <map>
#include <vector>
#include <list>
#include <set>
#include <deque>
#include "../battlefields/tileworld.hpp"
#include "tinyxml.h"

using namespace taomee;


/*used to get value from string like "1/1/1/;1/1/1"*/
template <class ValueType>
inline int get_variable_value(int element_cnt, std::string &source, std::deque<ValueType> &stack)
{
	stack.clear();
	std::string::size_type pos;
	std::string::size_type pos1;
	std::string::size_type pos_pre = 0;
	std::string::size_type pos_pre1 = 0;
	//if(element_cnt < 2) {
	//    ERROR_RETURN(("input"), -1);
	//}
	int info_cnt = 1;
	ValueType value= ValueType();
	do {
		pos = source.find(';', pos_pre);
		if(pos != std::string::npos) {
			info_cnt++;
		}
		std::string t = source.substr(pos_pre, pos - pos_pre);
		if(element_cnt == 1) {
			pos1 = t.find('/', pos_pre1);
			if(pos1 != std::string::npos) {
				return -1;
			}
			std::istringstream s(t);
			s>>value;
			stack.push_back(value);
		} else {
			int format_cnt = 0;
			do {
				pos1 = t.find('/', pos_pre1);
				/*not enought '/'*/
				if(pos1 == std::string::npos && format_cnt < (element_cnt - 1)) {
					//ERROR_RETURN(("format error or no value"), -1);
					return -1;
				}
				if(pos1 != std::string::npos) {
					format_cnt++;
					/*too many '/'*/
					if(format_cnt > (element_cnt - 1)) {
						return 100;
					}
				}
				std::string t1 = t.substr(pos_pre1, pos1 - pos_pre1);
				std::istringstream s(t1);
				s>>value;
				stack.push_back(value);
				pos_pre1 = pos1 + 1;
			} while(pos1 != std::string::npos);
		}
		pos_pre = pos + 1;
	} while(pos != std::string::npos);
	source.clear();
	return info_cnt;
}

class Monster_t {
public:
	uint32_t id;
	uint32_t health_point;
	bool is_boss;
	uint32_t experience;
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
	uint32_t speed;
	std::vector<uint32_t> skills;
};

class MonsterConfig
{
	public:
		void clear();

		Monster_t* get_monster_info(uint32_t id);

		typedef std::map<uint32_t, Monster_t*>  MonsterMap;
		static MonsterMap monster_map;
		template<typename ParseType>
		static Monster_t* load(ParseType& parse);
		int load();
	private:
    	std::string m_strFilePath;
		Monster_t* get_monster_info_from_lua(uint32_t id);
};

enum SkillType {
	CLOSEVEC	= 0,
	REMOVEVEC	= 2,
	REMOTEVEC	= 3,
};

typedef std::map<TileWorld<>::Point, TileWorld<>::Rectangle> RecMap;
typedef std::map<TileWorld<>::Point, TileWorld<>::Point> OffsetMap;
class Skill_t {
public:
	void insert(TileWorld<>::Point direct, TileWorld<>::Rectangle rec) {
		direct.unitised();
		INFO_LOG("ID:%d SET (%d, %d)", id, direct.x, direct.y);
		m_recs[direct] = rec;	
		rec = rec.mirrorY();
		direct.x = -direct.x;
		INFO_LOG("ID:%d SET (%d, %d)", id, direct.x, direct.y);
		m_recs[direct] = rec;	
	}

	void insert(TileWorld<>::Point direct, TileWorld<>::Point point) {
		direct.unitised();
		m_offsets[direct] = point;
		direct.x = -direct.x;
		point.x = - point.x;
		m_offsets[direct] = point;
	}

	uint32_t id;
	uint32_t type;
	uint32_t critical_rate;
	uint32_t cool_down;
	uint32_t can_attack_number;
	RecMap m_recs;
	OffsetMap m_offsets;
	uint32_t release_time;
	uint32_t effect_time;
	uint32_t dead_time;

	uint32_t up_animation;
	uint32_t down_animation;

	/*remote attack special*/
	uint32_t remote_attack_range;
	uint32_t rate;
	uint32_t effect_id;
};

class SkillConfig 
{
	public:
		virtual void clear();

		Skill_t* get_skill_info(uint32_t id);

		int load();
	private:
		typedef std::map<uint32_t, Skill_t*> SkillMap;
		static SkillMap skill_map;
		Skill_t* get_skill_info_from_lua(uint32_t id);
};

class TileConfig {
public:
	void load_config(uint32_t map_id);
	void clear();

	TileWorld<>* get_tile_info(uint32_t id);

typedef std::map<uint32_t, TileWorld<>* > TileMap;
	static TileMap tile_map;
private:
};

class MapMonster_t {
public:
	uint32_t raid_id;
	uint32_t monster_id;
	uint32_t monster_level;
	TileWorld<>::Point birth_place;
	TileWorld<>::Rectangle patrol_place;
};

class Reward_t {
public:
	uint32_t item_id;
	uint32_t item_level;
	uint32_t item_num;
};

class MapContent_t {
public:
	uint32_t map_id;
	uint32_t trans_des;
	TileWorld<>::Point trans_place;
	TileWorld<>::Point user_birth_place;
	std::vector<MapMonster_t> monsters;
};

typedef std::list<MapContent_t*> MapContentList;

enum InstanceType {
	PVE = 1,
	PPVE = 2,
	PVP	= 3,
};

class Instance_t {
public:
	~Instance_t();
	uint32_t id;
	uint32_t type;
	MapContentList contents;
typedef std::vector< base::AverageGen<Reward_t> > InstanceReward;
	InstanceReward rewards;
typedef std::map<uint32_t , uint32_t> MonsterNumMap;
	MonsterNumMap monster_nums;
};

class MapContentConfig {
public:
	void clear();
	
	MapContent_t* get_mapcontent_info(uint32_t instance_id, uint32_t map_id = 0);

	Instance_t* get_instance_info(uint32_t instance_id);
	
	bool exist_instance(uint32_t id);
	
	bool pve_instance(uint32_t id);

	void instance_range(uint32_t& start, uint32_t& end); 

	int load();

	/* 
	 @ load a battle map raidbasic information to memory. the file name is formed by RaidBasic123456.xml 
  	
  
     @ since v0.9

	*/
	int load(int map, int battleID);

private:
	typedef std::map<uint32_t, Instance_t*> InstanceMap;

	static InstanceMap instance_map;
};

class ActionRange_t {
public:
	uint32_t action_id;
	TileWorld<>::Rectangle attack_range;
	uint32_t attack_start;
	uint32_t attack_end;
};

class ObjectRange_t {
public:
	uint32_t role_id;
	TileWorld<>::Rectangle body_range;
typedef std::map<uint32_t, ActionRange_t> ActionMap;
	ActionMap attack_map;
};

class ObjectOffset_t {
public:
	uint32_t role_id;
	TileWorld<>::Point up_offset;
	TileWorld<>::Point down_offset;
};

class RangeConfig {
public:
	void clear();
	
	ActionRange_t* get_action_range_info(uint32_t role_id, uint32_t action_id);

	ObjectRange_t* get_role_range_info(uint32_t id);
	
	ObjectOffset_t* get_offset_info(uint32_t id) ;

	int load();
private:
typedef std::map<uint32_t, ObjectRange_t*> RangeMap;
static RangeMap role_range_map;

typedef std::map<uint32_t, ObjectOffset_t*> OffsetMap;
	
	static OffsetMap offset_map;
};

extern MonsterConfig* g_monster_config;
extern SkillConfig* g_skill_config;
extern TileConfig* g_tile_config;
extern MapContentConfig* g_mapcontent_config;
extern RangeConfig* g_range_config;


template<typename ParseType>
Monster_t* MonsterConfig::load(ParseType& parse) {
	Monster_t * monster_config = new Monster_t();
	parse.get("MonsterID", monster_config->id);
	parse.get("IsBoss", monster_config->is_boss);
	parse.get("HP", monster_config->health_point);
	parse.get("Experience", monster_config->experience);
	parse.get("PhysicalAttack", monster_config->physical_attack);
	parse.get("MagicAttack", monster_config->magic_attack);
	parse.get("SkillAttack", monster_config->skill_attack);
	parse.get("PhysicalDefence", monster_config->physical_defence);
	parse.get("MagicDefence", monster_config->magic_defence);
	parse.get("SkillDefence", monster_config->skill_defence);
	parse.get("HitRate", monster_config->hit_rate);
	parse.get("DodgeRate", monster_config->dodge_rate);
	parse.get("CritRate", monster_config->crit_rate);
	parse.get("CritDefenceRate", monster_config->crit_defence_rate);
	parse.get("AttackType", monster_config->attack_type);
	parse.get("AttackRangeType", monster_config->attack_range_type);
	parse.get("Speed", monster_config->speed);
	std::string source;
	std::deque<uint32_t> content;
	parse.get("Skill", source);
	int cnt = get_variable_value(1,source,content);
	if(!cnt) {
		ERROR_LOG("MONSTER:%d WITHOUT SKILL", monster_config->id);
 	}
	for(; cnt>0; cnt--) {
		uint32_t skill_id = content.front();
		monster_config->skills.push_back(skill_id);
		content.pop_front();
/*load range*/
		Skill_t* skill = g_skill_config->get_skill_info(skill_id);
		if(skill->type == CLOSEVEC) {
			ActionRange_t* up_action_range = g_range_config->get_action_range_info(monster_config->id, skill->up_animation);
			skill->insert(TileWorld<>::Point(1,1), up_action_range->attack_range);	
			ActionRange_t* down_action_range = g_range_config->get_action_range_info(monster_config->id, skill->down_animation);
			skill->insert(TileWorld<>::Point(-1,-1), down_action_range->attack_range);	
			skill->effect_time = down_action_range->attack_start;
			skill->dead_time = down_action_range->attack_end;
		} else if(skill->type == REMOTEVEC) { 
			ActionRange_t* down_action_range = g_range_config->get_action_range_info(monster_config->id, skill->down_animation);
			ActionRange_t* action_range = g_range_config->get_action_range_info(skill->effect_id, 100000);
			skill->release_time = down_action_range->attack_start;
			skill->effect_time = down_action_range->attack_start + action_range->attack_start;
			skill->dead_time = down_action_range->attack_start + action_range->attack_end;
			TileWorld<>::Rectangle rec = action_range->attack_range;
			skill->insert(TileWorld<>::Point(1,1), rec);
		} else if(skill->type == REMOVEVEC) {
			ActionRange_t* down_action_range = g_range_config->get_action_range_info(monster_config->id, skill->down_animation);
			skill->effect_time = down_action_range->attack_start;	
			ActionRange_t* action_range = g_range_config->get_action_range_info(skill->effect_id, 100000);
			ObjectOffset_t* offset = g_range_config->get_offset_info(monster_config->id);
			TileWorld<>::Rectangle rec = action_range->attack_range;
			skill->insert(TileWorld<>::Point(1,1), rec);
			skill->insert(TileWorld<>::Point(-1,-1), rec);
			skill->insert(TileWorld<>::Point(1,1), offset->up_offset);
			skill->insert(TileWorld<>::Point(-1,-1), offset->down_offset);
		}
	}
	INFO_LOG("LOAD MONSTER ID:%d HP:%d EXP:%d PA:%d MA:%d SA:%d PD:%d MD:%d SD:%d HR:%d DR:%d CR:%d CDR:%d AT:%d ART:%d SP:%d",monster_config->id, monster_config->health_point, monster_config->experience, monster_config->physical_attack, monster_config->magic_attack, monster_config->skill_attack, monster_config->physical_defence, monster_config->magic_defence, monster_config->skill_defence, monster_config->hit_rate, monster_config->dodge_rate, monster_config->crit_rate, monster_config->crit_defence_rate, monster_config->attack_type, monster_config->attack_range_type, monster_config->speed);
	return monster_config;
}



#endif
