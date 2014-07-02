#include "config.h"
#include "../base/TinyxmlAdapt.hpp"
#include "LuatableAdapt.hpp"

MonsterConfig* g_monster_config;
SkillConfig* g_skill_config;
TileConfig* g_tile_config;
MapContentConfig* g_mapcontent_config;
RangeConfig* g_range_config;

typedef  base::TinyxmlAdapt   XmlParse; 

#define KINFO_LOG(x, y) CCLog(y)

//------------------------------------------------ MonsterConfig -----------------------------------------
MonsterConfig::MonsterMap MonsterConfig::monster_map;

void MonsterConfig::clear() {
	MonsterMap::iterator itr = monster_map.begin();
	for(; itr!=monster_map.end(); ++itr) {
			delete itr->second;
	}
	monster_map.clear();
}

int MonsterConfig::load() {
	//KINFO_LOG(0, "----------------------[BEGIN_MONSTER_CONFIG]-----------------------");
	XmlParse root("./Data/MonsterBasicInfomation.xml");
	XmlParse child(root);
	while(child.available()) {
		if(child.name() == "Monster") {			
			Monster_t* monster = load(child);
			if(monster) {
				monster_map[monster->id] = monster;
			}
		}
		child = XmlParse(root);
	};
	//KINFO_LOG(0,"--------------------------[END_MONSTER_CONFIG]------------------------");
	return 0;
}

	
Monster_t* MonsterConfig::get_monster_info(uint32_t id) 
{
	if(monster_map.find(id) != monster_map.end()) {
		return monster_map[id];
	} else {
		return get_monster_info_from_lua(id);
	}
}
	
Monster_t* MonsterConfig::get_monster_info_from_lua(uint32_t id) 
{
	base::LuatableAdapt root("../conf/MonsterBasicInfomation.lua","MonsterBasicInfomation");
	base::LuatableAdapt parse(root,id);
	Monster_t* monster = load(parse);
	if(monster) {
		monster_map[id] = monster;
	}
	return monster;
}

//------------------------------------------------ SkillConfig -----------------------------------------
SkillConfig::SkillMap SkillConfig::skill_map;


void SkillConfig::clear() {
	SkillMap::iterator itr = skill_map.begin();
	for(; itr!=skill_map.end(); ++itr) {
		delete itr->second;
	}
	skill_map.clear();
}

int SkillConfig::load() {
	//KINFO_LOG(0, "----------------------[BEGIN_SKILL_CONFIG]-----------------------");
	XmlParse root("./Data/MonsterSkill.xml");
	XmlParse child(root);
	while(child.available()) {
		if(child.name() == "MonsterSkill") {			
			Skill_t* skill_config = new Skill_t();
			child.get("skill_id", skill_config->id);
			child.get("skill_type", skill_config->type);
			child.get("critical_rate", skill_config->critical_rate);
			float cool_down;
			child.get("cool_time", cool_down);
			skill_config->cool_down = cool_down*1000;
			child.get("can_attack_number", skill_config->can_attack_number);
			child.get("remote_attack_range", skill_config->remote_attack_range);
			child.get("rate", skill_config->rate);
			uint32_t start_frame, end_frame;
			child.get("start_frame", start_frame);
			child.get("end_frame", end_frame);
			skill_config->effect_time 	= 1000 * start_frame/24;
			skill_config->dead_time		= 1000 * end_frame/24;
			child.get("up_animation_id", skill_config->up_animation);
			child.get("down_animation_id", skill_config->down_animation);
			assert(skill_config->up_animation);
			assert(skill_config->down_animation);
			child.get("effect_id", skill_config->effect_id);
			skill_map[skill_config->id] = skill_config;
			//KINFO_LOG(0,"LOAD SKILL ID:%d TYPE:%d CD:%d START:%d END:%d", skill_config->id, skill_config->type, skill_config->cool_down, skill_config->effect_time, skill_config->dead_time );
		}
		child = XmlParse(root);
	};
	//KINFO_LOG(0, "----------------------[END_SKILL_CONFIG]-----------------------");
	return 0;
}

Skill_t* SkillConfig::get_skill_info(uint32_t id) 
{
	return skill_map[id] != NULL ? skill_map[id] : get_skill_info_from_lua(id);
}

Skill_t* SkillConfig::get_skill_info_from_lua(uint32_t id) 
{
	base::LuatableAdapt root("../conf/MonsterSkill.lua","MonsterSkills");
	base::LuatableAdapt child(root,id);
	if(child.available()) {
		Skill_t* skill_config = new Skill_t();
		child.get("skill_id", skill_config->id);
		child.get("skill_type", skill_config->type);
		child.get("critical_rate", skill_config->critical_rate);
		float cool_down;
		child.get("cool_time", cool_down);
		skill_config->cool_down = cool_down*1000;
		child.get("can_attack_number", skill_config->can_attack_number);
		child.get("remote_attack_range", skill_config->remote_attack_range);
		child.get("rate", skill_config->rate);
		uint32_t start_frame, end_frame;
		child.get("start_frame", start_frame);
		child.get("end_frame", end_frame);
		skill_config->effect_time 	= 1000 * start_frame/24;
		skill_config->dead_time		= 1000 * end_frame/24;
		child.get("up_animation_id", skill_config->up_animation);
		child.get("down_animation_id", skill_config->down_animation);
		assert(skill_config->up_animation);
		assert(skill_config->down_animation);
		child.get("effect_id", skill_config->effect_id);
		skill_map[skill_config->id] = skill_config;
		//KINFO_LOG(0,"LOAD SKILL ID:%d TYPE:%d CD:%d START:%d END:%d", skill_config->id, skill_config->type, skill_config->cool_down, skill_config->effect_time, skill_config->dead_time );
		return skill_config;
	}
	return NULL;
}

static const char* TILE_CONFIG_PATH = "./spriteBin/";

TileConfig::TileMap TileConfig::tile_map;
			
void TileConfig::load_config(uint32_t map_id) {
	if(tile_map.find(map_id) == tile_map.end() ) {
		std::string strFilePath = TILE_CONFIG_PATH;

		std::ostringstream oss;
		oss << strFilePath << map_id << "iPad.map";

		std::string path = GameResourceManager::sharedManager()->storedFullPathFromRelativePath(oss.str().c_str());

		TileWorld<> *p = new TileWorld<>(path.c_str());	
		tile_map[map_id] = p;
	}
}
	
void TileConfig::clear() {
	TileMap::iterator itr = TileConfig::tile_map.begin();
	for( ; itr!=TileConfig::tile_map.end(); ++itr) {
		delete itr->second;
	}
	TileConfig::tile_map.clear();
}
	
TileWorld<>* TileConfig::get_tile_info(uint32_t id) {
	return TileConfig::tile_map[id];
}

Instance_t::~Instance_t() {
	MapContentList::iterator itr = contents.begin(); 
	for(; itr!=contents.end(); ++ itr) {
		MapContent_t* map = *itr;
	
		delete map;
	}
}

MapContentConfig::InstanceMap MapContentConfig::instance_map;

void MapContentConfig::clear()
{
	InstanceMap::iterator itr = instance_map.begin();
	for( ; itr!=MapContentConfig::instance_map.end(); ++itr) {
		Instance_t* instance = itr->second;
		delete instance;
	}
	instance_map.clear();
}


int MapContentConfig::load(int map, int battleID)
{
	std::ostringstream oss;
	oss << "./Data/" << battleID << "RaidBasic.xml";
	XmlParse root(oss.str());
	XmlParse child(root);
	while(child.available())
	{
		uint32_t id = 0;
		uint32_t map_id = 0;
		child.get("RaidID",id);
		child.get("MapID",map_id);
		Instance_t* instance = NULL;	
		MapContent_t* mapcontent = NULL;
		if(instance_map.find(id) == instance_map.end()) 
		{
			instance = new Instance_t();
			instance->id = id;
			child.get("Type",instance->type);
			instance_map[id] = instance;
			{
				std::string source;
				std::deque<uint32_t> content;
				child.get("RaidDrops1",source);
				base::AverageGen<Reward_t> gen;
				int cnt = get_variable_value(3,source,content);
				for(; cnt >0; cnt--) {
					Reward_t reward;
					reward.item_id =content.front();
					content.pop_front();
					reward.item_level =content.front();
					content.pop_front();
					reward.item_num =content.front();
					content.pop_front();
					gen.push(reward);
				}
				instance->rewards.push_back(gen);
			}
			{
				std::string source;
				std::deque<uint32_t> content;
				child.get("RaidDrops2",source);
				base::AverageGen<Reward_t> gen;
				int cnt = get_variable_value(3,source,content);
				for(; cnt >0; cnt--) {
					Reward_t reward;
					reward.item_id =content.front();
					content.pop_front();
					reward.item_level =content.front();
					content.pop_front();
					reward.item_num =content.front();
					content.pop_front();
					gen.push(reward);
				}
				instance->rewards.push_back(gen);
			}
			{
				std::string source;
				std::deque<uint32_t> content;
				child.get("RaidDrops3",source);
				base::AverageGen<Reward_t> gen;
				int cnt = get_variable_value(3,source,content);
				for(; cnt >0; cnt--) {
					Reward_t reward;
					reward.item_id =content.front();
					content.pop_front();
					reward.item_level =content.front();
					content.pop_front();
					reward.item_num =content.front();
					content.pop_front();
					gen.push(reward);
				}
				instance->rewards.push_back(gen);
			}
		} else {
			instance = instance_map[id];
			MapContentList::iterator itr = instance_map[id]->contents.begin();
			for(; itr!=instance_map[id]->contents.end(); itr++) {
				if( (*itr)->map_id == map_id ) {
					mapcontent = (*itr);
					break;
				}
			}
		}
		if(!mapcontent) {
			mapcontent = new MapContent_t();
			mapcontent->map_id = map_id;
			child.get("TransDestination",mapcontent->trans_des);

			bool bInsert = false;
			MapContentList::iterator itr = instance_map[id]->contents.begin();
			for(; itr!=instance_map[id]->contents.end(); ++itr) {
				if( (*itr)->trans_des == map_id ) {
					instance_map[id]->contents.insert(++itr, mapcontent);
					bInsert = true;
					break;
				}
				if(mapcontent->trans_des == (*itr)->map_id) {
					instance_map[id]->contents.insert(itr, mapcontent);
					bInsert = true;
					break;
				}	
			}


			if(!bInsert) {
				instance_map[id]->contents.push_back(mapcontent);
			}
		}
		std::string source;
		std::deque<uint32_t> content;
		child.get("HeroBornCoordinate", source);
		get_variable_value(2,source,content);
		mapcontent->user_birth_place.x = content.front();
		content.pop_front();
		mapcontent->user_birth_place.y = content.front();
		content.pop_front();

		child.get("TransDestination", mapcontent->trans_des);
		if(mapcontent->trans_des) {	
			source.clear();
			content.clear();
			child.get("TransCoordinate", source);
			get_variable_value(2,source,content);
			mapcontent->trans_place.x = content.front();
			content.pop_front();
			mapcontent->trans_place.y = content.front();
			content.pop_front();
		}

		MapMonster_t* mapmonster = new MapMonster_t();			
		child.get("RaidMonsterID", mapmonster->raid_id);
		child.get("MonsterID", mapmonster->monster_id);
		child.get("MosterLevel", mapmonster->monster_level);

		source.clear();
		content.clear();
		child.get("MosterBornCoordinate", source);
		get_variable_value(2,source,content);
		TileWorld<>::Point point_born;
		point_born.x = content.front();
		content.pop_front();
		point_born.y = content.front();
		content.pop_front();

		mapmonster->birth_place = point_born;	

		source.clear();
		content.clear();
		child.get("MosterPatrolRange", source);
		get_variable_value(2,source,content);
		TileWorld<>::Point point_start;
		point_start.x = content.front();
		content.pop_front();
		point_start.y = content.front();
		content.pop_front();
		TileWorld<>::Point point_end;
		point_end.x = content.front();
		content.pop_front();
		point_end.y = content.front();
		content.pop_front();

		mapmonster->patrol_place = TileWorld<>::Rectangle(point_start, point_end);	

		mapcontent->monsters.push_back(*mapmonster);
		instance->monster_nums[mapmonster->monster_id] ++;

		delete mapmonster;	

		child = XmlParse(root);
	}	

	/// find the right titled map information
	if (0 == map)
	{
		MapContent_t* pMap = get_mapcontent_info(battleID, 0);
		if( pMap)
		{
			map = pMap->map_id;
		}		
	}

	g_tile_config->clear();
	g_tile_config->load_config(map);

	//KINFO_LOG(0,"--------------------------[END_MAPCONTENT_CONFIG]------------------------");
	return 0;
}

int MapContentConfig::load() {
	//KINFO_LOG(0, "----------------------[BEGIN_MAPCONTENT_CONFIG]-----------------------");
	XmlParse root("./Data/RaidBasic.xml");
	XmlParse child(root);
	while(child.available()) {
		uint32_t id = 0;
		uint32_t map_id = 0;
		child.get("RaidID",id);
		child.get("MapID",map_id);
		g_tile_config->load_config(map_id);
		Instance_t* instance = NULL;	
		MapContent_t* mapcontent = NULL;
		if(instance_map.find(id) == instance_map.end()) {
			instance = new Instance_t();
			instance->id = id;
			child.get("Type",instance->type);
			instance_map[id] = instance;
				{
					std::string source;
					std::deque<uint32_t> content;
					child.get("RaidDrops1",source);
					base::AverageGen<Reward_t> gen;
					int cnt = get_variable_value(3,source,content);
					for(; cnt >0; cnt--) {
						Reward_t reward;
						reward.item_id =content.front();
						content.pop_front();
						reward.item_level =content.front();
						content.pop_front();
						reward.item_num =content.front();
						content.pop_front();
						gen.push(reward);
					}
					instance->rewards.push_back(gen);
				}
				{
					std::string source;
					std::deque<uint32_t> content;
					child.get("RaidDrops2",source);
					base::AverageGen<Reward_t> gen;
					int cnt = get_variable_value(3,source,content);
					for(; cnt >0; cnt--) {
						Reward_t reward;
						reward.item_id =content.front();
						content.pop_front();
						reward.item_level =content.front();
						content.pop_front();
						reward.item_num =content.front();
						content.pop_front();
						gen.push(reward);
					}
					instance->rewards.push_back(gen);
				}
				{
					std::string source;
					std::deque<uint32_t> content;
					child.get("RaidDrops3",source);
					base::AverageGen<Reward_t> gen;
					int cnt = get_variable_value(3,source,content);
					for(; cnt >0; cnt--) {
						Reward_t reward;
						reward.item_id =content.front();
						content.pop_front();
						reward.item_level =content.front();
						content.pop_front();
						reward.item_num =content.front();
						content.pop_front();
						gen.push(reward);
					}
					instance->rewards.push_back(gen);
				}
			} else {
				instance = instance_map[id];
				MapContentList::iterator itr = instance_map[id]->contents.begin();
				for(; itr!=instance_map[id]->contents.end(); itr++) {
					if( (*itr)->map_id == map_id ) {
						mapcontent = (*itr);
						break;
					}
				}
			}
			if(!mapcontent) {
				mapcontent = new MapContent_t();
				mapcontent->map_id = map_id;
				child.get("TransDestination",mapcontent->trans_des);

				MapContentList::iterator itr = instance_map[id]->contents.begin();
				for(; itr!=instance_map[id]->contents.end(); ++itr) {
					if( (*itr)->trans_des == map_id ) {
						instance_map[id]->contents.insert(++itr, mapcontent);
						break;
					}
					if(mapcontent->trans_des == (*itr)->map_id) {
						instance_map[id]->contents.insert(itr, mapcontent);
						break;
					}	
				}
				if(itr == instance_map[id]->contents.end()) {
					instance_map[id]->contents.push_back(mapcontent);
				}
			}
			std::string source;
            std::deque<uint32_t> content;
			child.get("HeroBornCoordinate", source);
			get_variable_value(2,source,content);
			mapcontent->user_birth_place.x = content.front();
			content.pop_front();
			mapcontent->user_birth_place.y = content.front();
			content.pop_front();
			
			child.get("TransDestination", mapcontent->trans_des);
			if(mapcontent->trans_des) {	
				source.clear();
				content.clear();
				child.get("TransCoordinate", source);
				get_variable_value(2,source,content);
				mapcontent->trans_place.x = content.front();
				content.pop_front();
				mapcontent->trans_place.y = content.front();
				content.pop_front();
 			}

			MapMonster_t* mapmonster = new MapMonster_t();			
			child.get("RaidMonsterID", mapmonster->raid_id);
			child.get("MonsterID", mapmonster->monster_id);
			child.get("MosterLevel", mapmonster->monster_level);
	
			source.clear();
            content.clear();
			child.get("MosterBornCoordinate", source);
			get_variable_value(2,source,content);
			TileWorld<>::Point point_born;
			point_born.x = content.front();
			content.pop_front();
			point_born.y = content.front();
			content.pop_front();
			
			mapmonster->birth_place = point_born;	

			source.clear();
			content.clear();
			child.get("MosterPatrolRange", source);
			get_variable_value(2,source,content);
			TileWorld<>::Point point_start;
			point_start.x = content.front();
			content.pop_front();
			point_start.y = content.front();
			content.pop_front();
			TileWorld<>::Point point_end;
			point_end.x = content.front();
			content.pop_front();
			point_end.y = content.front();
			content.pop_front();
			
			mapmonster->patrol_place = TileWorld<>::Rectangle(point_start, point_end);	
	
			mapcontent->monsters.push_back(*mapmonster);
			instance->monster_nums[mapmonster->monster_id] ++;
			//KINFO_LOG(0,"LOAD RAID ID :%d MAP ID:%d HERO BORN:(%d %d) MONSTER [ RAID :%d ID:%d LEVEL:%d BORN:%d %d PATROL:(%d ,%d)(%d , %d)", instance->id, mapcontent->map_id, mapcontent->user_birth_place.x, mapcontent->user_birth_place.y, mapmonster->raid_id, mapmonster->monster_id, mapmonster->monster_level,point_born.x, point_born.y, point_start.x, point_start.y, point_end.x, point_end.y);
			delete mapmonster;	

			child = XmlParse(root);
		}	

	//KINFO_LOG(0,"--------------------------[END_MAPCONTENT_CONFIG]------------------------");
	return 0;
}
	
MapContent_t* MapContentConfig::get_mapcontent_info(uint32_t instance_id, uint32_t map_id) {
	if(instance_map.find(instance_id) != instance_map.end()) {
		MapContentList::iterator itr = instance_map[instance_id]->contents.begin();
		for(; itr!=instance_map[instance_id]->contents.end(); itr++) {
			if( (*itr)->map_id == map_id || !map_id ) {
				return (*itr);
			}
		}
	}
	return NULL;
}
	
Instance_t* MapContentConfig::get_instance_info(uint32_t instance_id) {
	if(instance_map.find(instance_id) != instance_map.end()) {
		return instance_map[instance_id];
	}
	return NULL;
}

	
bool MapContentConfig::exist_instance(uint32_t id) {
	return instance_map.find(id) != instance_map.end();
}
	
bool MapContentConfig::pve_instance(uint32_t id) {
	if(instance_map.find(id) != instance_map.end() && instance_map[id]->type == PVE )
		return true;
	return false;
}
	
void MapContentConfig::instance_range(uint32_t& start, uint32_t& end) {
	if(!instance_map.empty()) {
		start = instance_map.begin()->first;
		end = instance_map.rbegin()->first;
	}
}
	
RangeConfig::RangeMap RangeConfig::role_range_map;
RangeConfig::OffsetMap RangeConfig::offset_map;
	

	
void RangeConfig::clear() {
	RangeMap::iterator itr = role_range_map.begin();
	for( ; itr!=RangeConfig::role_range_map.end(); ++itr) {
		delete itr->second;
	}
	role_range_map.clear();
	OffsetMap::iterator itr2 = offset_map.begin();
	for(; itr2!=offset_map.end(); ++itr2) {
		delete itr2->second;
	}
	offset_map.clear();
}

int RangeConfig::load() {
	//KINFO_LOG(0, "----------------------[BEGIN_ROLE_RANGE_CONFIG]-----------------------");
	XmlParse root("./skeleton_animation/AreaConfigTable.xml");
	XmlParse child(root);
	while(child.available()) {
		if(child.name() =="Role")
		{
			ObjectRange_t* range = new ObjectRange_t();
			child.get("id", range->role_id);
			XmlParse child2(child);
			while(child2.available()) {
				if(child2.name() == "Actions")
				{
					XmlParse child3(child2);
					while(child3.available()) {
						if(child3.name()== "Action") {
							ActionRange_t* action = new ActionRange_t();
							child3.get("id", action->action_id);
						
							XmlParse child4(child3)	;
							while(child4.available()) {
								if(child4.name() == ("A")) {
									child4.get("startFrame", action->attack_start);
									action->attack_start = 1000 * action->attack_start/24;	
									child4.get("endFrame", action->attack_end);
									action->attack_end = 1000 * action->attack_end/24;
									child4.get("upLeftPX", action->attack_range.start.x);
									child4.get("upLeftPY", action->attack_range.start.y);
									child4.get("downRightPX", action->attack_range.end.x);
									child4.get("downRightPY", action->attack_range.end.y);
								}
								if(child4.name() == ("C")) {
									child4.get("upLeftPX", range->body_range.start.x);
									child4.get("upLeftPY", range->body_range.start.y);
									child4.get("downRightPX", range->body_range.end.x);
									child4.get("downRightPY", range->body_range.end.y);
								}
								child4 = XmlParse(child3);
							}
							range->attack_map[action->action_id] = *action;
						}
						child3 = XmlParse(child2);
					}
					
				}else if(child2.name()==("PT"))
				{
					ObjectOffset_t* offset = new ObjectOffset_t();
					XmlParse child3(child2);
					while(child3.available()) {
						if(child3.name() == ("pt")) {
							uint32_t type;
							child3.get("Type", type);
							if(type == 3) {
								child3.get("posX", offset->up_offset.x);
								child3.get("posY", offset->up_offset.y);
							} else if(type == 4) {
								child3.get("posX", offset->down_offset.x);
								child3.get("posY", offset->down_offset.y);
							}
						}
						child3 = XmlParse(child2);
					}
					offset_map[range->role_id] = offset;
				}
				child2 = XmlParse(child);
			}
	
			role_range_map[range->role_id] = range;	
			//KINFO_LOG(0,"LOAD RANGE ID:%d BODY:(%d %d) (%d %d)", range->role_id, range->body_range.start.x, range->body_range.start.y, range->body_range.end.x, range->body_range.end.y );
		}
		child = XmlParse(root);
	}
	//KINFO_LOG(0,"--------------------------[END_ROLE_RANGE_CONFIG]------------------------");
	return 0;
}
	
ActionRange_t* RangeConfig::get_action_range_info(uint32_t role_id, uint32_t action_id) {
	ObjectRange_t* role_range = get_role_range_info(role_id);
	if(role_range !=NULL) {
		if (role_range->attack_map.find(action_id) != role_range->attack_map.end()) {
			return &(role_range->attack_map)[action_id];
		}
	} 
	return NULL;
}

ObjectRange_t* RangeConfig::get_role_range_info(uint32_t id) {
	if(role_range_map.find(id) != role_range_map.end()) {
		return RangeConfig::role_range_map[id];
	} else {
		return NULL;
	}
}
	
ObjectOffset_t* RangeConfig::get_offset_info(uint32_t id) {
	if(offset_map.find(id) != offset_map.end()) {
		return offset_map[id];
	} else {
		return NULL;
	}
}

