#include "skill.h"

EffectSpace::EffectSpace(uint32_t effect_time, uint32_t dead_time):
	m_status(IDLE),
	m_effect_time(effect_time),
	m_dead_time(dead_time),
	m_update_time(0)
{
	if(!m_effect_time) {
		m_status = EFFECT; 
	}
	if(!m_dead_time) {
		m_status = DEAD;
	}
}

bool EffectSpace::update()
{
	m_update_time += UPDATETIME;
	if(m_update_time >= m_effect_time) {
		m_status = EFFECT;
	}
	if(m_update_time >= m_dead_time) {
		m_status = DEAD;
	}
	return true;
};

EffectRec::EffectRec(TileWorld<>::Rectangle rec, uint32_t effect_time, uint32_t dead_time ):
	EffectSpace(effect_time, dead_time),
	m_rec(rec) 
{
};
	
bool EffectRec::effect(Entity* des, CSMonsterHitRsp* rsp) {
	if( status() == EffectSpace::EFFECT && !m_effected_list.count(des) && m_rec.touch(des->space())) {
		CSMonsterHitRsp_UserInfo * user = rsp->add_users();
		user->set_userid(des->get_id());
		user->set_blood(10);
		m_effected_list.insert(des);
		return true;
	}
	return false;
}
	
MoveEffectRec::MoveEffectRec(TileWorld<>::Rectangle rec, TileWorld<>::Point src, TileWorld<>::Point des, uint32_t speed, uint32_t effect_time):
	EffectSpace(effect_time, 0),
	m_rec(rec),
	m_src(src),
	m_des(des),
	m_speed(speed),
	m_accumulate(0)
{
	DEBUG_LOG("TEST NEW REC:%p",this);
	m_status = IDLE; 
};
	
MoveEffectRec::~MoveEffectRec(){
	DEBUG_LOG("TEST DELETE REC:%p",this);
}

bool MoveEffectRec::effect(Entity* des, CSMonsterHitRsp* rsp) {
	TileWorld<>::Rectangle effect_rec = m_rec;
	effect_rec.move(m_src);
//	DEBUG_LOG("MOVE EFFECT NOW PALCE:(%d %d) (%d %d) DES(%d %d) (%d %d) STATUS:%d",effect_rec.start.x,effect_rec.start.y, effect_rec.end.x,effect_rec.end.y, des->space().start.x, des->space().start.y, des->space().end.x, des->space().end.y, status());
	if( status() == EffectSpace::EFFECT && !m_effected_list.count(des) && effect_rec.touch(des->space())) {
		CSMonsterHitRsp_UserInfo * user = rsp->add_users();
		user->set_userid(des->get_id());
		user->set_blood(10);
		m_effected_list.insert(des);
		return true;
	}
	return false;
}
	
bool MoveEffectRec::update() {
	if (m_src == m_des) {
		m_status = DEAD;
		return false;
	}
	m_update_time += UPDATETIME;
	if(m_update_time >= m_effect_time) {
		m_status = EFFECT;
		m_accumulate += m_speed * 10 * UPDATETIME / 1000;
		m_src = TileWorld<>::walk_direct_path(m_src, m_des, m_accumulate);
		DEBUG_LOG("TEST MOVE START(%d %d) END(%d %d) %p",m_src.x,m_src.y, m_des.x, m_des.y, this);
		return true;
	}
	return true;
}
	
EffectManager::~EffectManager() {
	EffectList::iterator itr = m_effect_list.begin();
	for(;itr!=m_effect_list.end();) {
		delete *itr;
		itr++;
	}	
}

void EffectManager::update() {
	EffectList::iterator itr = m_effect_list.begin();
	for(;itr!=m_effect_list.end();) {
		if(!(*itr)->update()) {
			delete *itr;
			itr = m_effect_list.erase(itr);
		} else {
			++itr;
		}
	}	
}
	
void EffectManager::effect(Entity* des, CSMonsterHitRsp* rsp) {
	EffectList::iterator itr = m_effect_list.begin();
	for(;itr!=m_effect_list.end();) {
		if((*itr)->status() == EffectSpace::EFFECT) {
			(*itr) -> effect(des, rsp);
		}
		itr++;
	}	
}
	
void EffectManager::add_effect(EffectSpace* peffect ) {
	m_effect_list.push_back(peffect);
}

Skill::Skill(uint32_t id) :
	m_id(id), m_available(true), m_update_time(0) {

};
	
void Skill::update() {
	if(!m_available) {
		m_update_time += UPDATETIME;
		if(m_update_time >= m_cool_down) {
			m_update_time = 0;
			m_available = true;
		}
	}
}
	
bool Skill::effect(Entity* src, Entity* des, TileWorld<>::Point& direct, EffectManager* pManager, CSMonsterAttackInfo* info) {
	m_update_time = 0;
	m_available = false;
	return true;
}
	
uint32_t Skill::get_id() {
	return m_id;
}
	
bool Skill::available() {
	return m_available;
}
	
Skill* Skill::generate_skill(uint32_t role_id, uint32_t id) {
	Skill_t* skill_info = g_skill_config->get_skill_info(id);
	if(skill_info) {
		switch (skill_info->type) {
			case 0:
			{	
				VecSkill* pskill = new VecSkill(id);
				pskill->m_recs= skill_info->m_recs; 
				pskill->m_effect_time = (skill_info->effect_time / UPDATETIME)* UPDATETIME ;
				pskill->m_dead_time = skill_info->dead_time;
				pskill->m_cool_down = skill_info->cool_down;
				pskill->m_up_animation = skill_info->up_animation;
				pskill->m_down_animation = skill_info->down_animation;
				return pskill;
			}
			break;
			case 2:
			{
				MoveVecSkill* pskill = new MoveVecSkill(id);
				pskill->m_recs= skill_info->m_recs;
				pskill->m_offsets= skill_info->m_offsets;
				pskill->m_effect_time = (skill_info->effect_time / UPDATETIME)* UPDATETIME ;
				pskill->m_dead_time = skill_info->dead_time;
				pskill->m_speed = skill_info->rate;
				pskill->m_dead_len = skill_info->remote_attack_range;
				pskill->m_cool_down = skill_info->cool_down;
				pskill->m_effect_id = skill_info->effect_id;
				pskill->m_up_animation = skill_info->up_animation;
				pskill->m_down_animation = skill_info->down_animation;
				return pskill;
			}
			break;
		}
	}
	return NULL;
}

VecSkill::VecSkill(uint32_t id) :
	Skill(id)
{
}
	
bool VecSkill::try_effect(Entity* src, Entity* des) {
	Skill::try_effect(src, des);
	RecMap::iterator itr = m_recs.begin();
	for(;itr!=m_recs.end(); itr++) {
		TileWorld<>::Rectangle rec = itr->second;
		rec.move(src->m_pos);
		if(rec.touch(des->space())) {
			return true;	
		}
	}
	return false;
}

bool VecSkill::effect(Entity* src, Entity* des, TileWorld<>::Point& direct, EffectManager* pManager, CSMonsterAttackInfo* info) {
	info->set_type(1);
	if(m_recs.find(direct) != m_recs.end()) {
		TileWorld<>::Rectangle rec = m_recs[direct];
		rec.move(src->m_pos);
		if(	rec.touch(des->space()) )
		{
			EffectRec* effect= new EffectRec(rec, m_effect_time, m_dead_time);
			pManager->add_effect(effect);
			if(direct.y > 0) {
				info->set_action_id(m_up_animation);
			} else {
				info->set_action_id(m_down_animation);
			}	
			return Skill::effect(src, des, direct, pManager, info);
		}
	}
	RecMap::iterator itr = m_recs.begin();
	for(;itr!=m_recs.end(); itr++) {
		TileWorld<>::Rectangle rec = itr->second;
		rec.move(src->m_pos);
		if(rec.touch(des->space())) {
			EffectRec* effect= new EffectRec(rec, m_effect_time, m_dead_time);
			pManager->add_effect(effect);
			direct = itr->first;
			if(direct.y > 0) {
				info->set_action_id(m_up_animation);
			} else {
				info->set_action_id(m_down_animation);
			}
			return Skill::effect(src, des, direct, pManager, info);
		}
	}
	return false;
}
	
MoveVecSkill::MoveVecSkill(uint32_t id) :
	Skill(id)
{
}
	
bool MoveVecSkill::try_effect(Entity* src, Entity* des) {
	Skill::try_effect(src, des);
	RecMap::iterator itr = m_recs.begin();
	for(;itr!=m_recs.end(); itr++) {
		TileWorld<>::Rectangle rec = itr->second;
		rec.move(src->m_pos);
		if(rec.distance2(des->space()) <= m_dead_len*m_dead_len ) {
			return true;	
		}
	}
	return false;
}
	
bool MoveVecSkill::effect(Entity* src, Entity* des, TileWorld<>::Point& direct, EffectManager* pManager, CSMonsterAttackInfo* info) {
	if(direct.x == 0) {direct.x = 1;};
	if(direct.y == 0) {direct.y = 1;};
	if(m_recs.find(direct) != m_recs.end() && m_offsets.find(direct) != m_offsets.end()) {
		TileWorld<>::Rectangle rec = m_recs[direct];
		TileWorld<>::Point offset = m_offsets[direct];
		{
			TileWorld<>::Point start_pos = src->m_pos;
			start_pos += offset;
			TileWorld<>::Point end_pos 	= des->space().center();		
			if(start_pos == end_pos) {
					end_pos.y += m_dead_len; 
			}
			float dis = start_pos.distance(end_pos);
			if(dis < m_dead_len) {
				end_pos -= start_pos;
				end_pos *= (m_dead_len/dis);
				end_pos += start_pos;
			}
			DEBUG_LOG("MOVE EFFECT START:(%d %d) DIRECT(%d %d) ",start_pos.x,start_pos.y, direct.x, direct.y);
			MoveEffectRec* effect= new MoveEffectRec(rec, start_pos, end_pos, m_speed, m_effect_time);
			pManager->add_effect(effect);
/*template code*/
			info->set_type(2);
			if(direct.y > 0) {
				info->set_action_id(m_up_animation);
			} else {
				info->set_action_id(m_down_animation);
			}
			CSPoint* start_point = info->mutable_start_pos();
			start_point->set_xpos(start_pos.x);
			start_point->set_ypos(start_pos.y);
			CSPoint* end_point = info->mutable_end_pos();
			end_point->set_xpos(end_pos.x);
			end_point->set_ypos(end_pos.y);
			info -> set_skill_speed(m_speed);
			info -> set_delay_time(m_effect_time);
			info -> set_effect_id(m_effect_id);
			return Skill::effect(src, des, direct, pManager, info);
		}
	}
	return false;
}
	
TargetSkill::TargetSkill(uint32_t id):
	Skill(id) {
}

bool TargetSkill::try_effect(Entity* src, Entity* des) {
	Skill::try_effect(src, des);
	RecMap::iterator itr = m_recs.begin();
	for(;itr!=m_recs.end(); itr++) {
		TileWorld<>::Rectangle rec = itr->second;
		rec.move(src->m_pos);
		if(rec.distance2(des->space()) <= m_dead_len*m_dead_len ) {
			return true;	
		}
	}
	return false;
}
	
bool TargetSkill::effect(Entity* src, Entity* des, TileWorld<>::Point& direct, EffectManager* pManager, CSMonsterAttackInfo* info) {
	if(!m_recs.empty()) {
		TileWorld<>::Rectangle rec = m_recs.begin()->second;
		{
			TileWorld<>::Point pos 	= des->space().center();		
			DEBUG_LOG("TARGET EFFECT POS:(%d %d) DIRECT(%d %d) ",pos.x,pos.y, direct.x, direct.y);
			rec.move(des->space().center()-=rec.center());
			EffectRec* effect= new EffectRec(rec, m_effect_time, m_dead_time);
			pManager->add_effect(effect);
/*template code*/
			info->set_type(3);
			if(direct.y > 0) {
				info->set_action_id(m_up_animation);
			} else {
				info->set_action_id(m_down_animation);
			}
			CSPoint* end_point = info->mutable_end_pos();
			end_point->set_xpos(pos.x);
			end_point->set_ypos(pos.y);
			info -> set_delay_time(m_release_time);
			info -> set_effect_id(m_effect_id);
			return Skill::effect(src, des, direct, pManager, info);
		}
	}
	return false;
}
	
TargetVecSkill::TargetVecSkill(uint32_t id):
	Skill(id) {
}

bool TargetVecSkill::try_effect(Entity* src, Entity* des) {
	Skill::try_effect(src, des);
	return true;	
}
	
bool TargetVecSkill::effect(Entity* src, Entity* des, TileWorld<>::Point& direct, EffectManager* pManager, CSMonsterAttackInfo* info) {
	if(direct.x == 0) {direct.x = 1;};
	if(direct.y == 0) {direct.y = 1;};
	RecMap::iterator itr = m_recs.begin();
	for(; itr!=m_recs.end(); ++itr) {
		DEBUG_LOG("TARGET VEC EFFECT POS");
		EffectRec* effect= new EffectRec(itr->second, m_effect_time, m_dead_time);
		pManager->add_effect(effect);
/*template code*/
		info->set_type(3);
		info -> set_delay_time(m_effect_time);
		info -> set_effect_id(m_effect_id);
		return Skill::effect(src, des, direct, pManager, info);
	}
	return false;
}
	
SkillControl::SkillControl() :
	m_id(0) {
}
	
SkillControl::~SkillControl() {
	SkillMap::iterator itr = m_skill_map.begin();
	for(; itr!= m_skill_map.end(); ++itr) {
		delete itr->second;
	}	
}
	
void SkillControl::generate_skills(const Monster_t& info) {
	for(size_t i = 0; i < info.skills.size(); i++) {
		add_skill(info.skills[i]);
	}
	if(!m_skill_map.empty()) {
		m_id = m_skill_map.begin()->first;
	}
}
	
void SkillControl::add_skill(uint32_t id) {
	Skill_t* skill_info = g_skill_config->get_skill_info(id);
	if(skill_info) {
		switch (skill_info->type) {
			case CLOSEVEC:
			{	
				VecSkill* pskill = new VecSkill(id);
				pskill->m_recs= skill_info->m_recs; 
				pskill->m_effect_time = (skill_info->effect_time / UPDATETIME)* UPDATETIME ;
				pskill->m_dead_time = skill_info->dead_time;
				pskill->m_cool_down = skill_info->cool_down;
				pskill->m_up_animation = skill_info->up_animation;
				pskill->m_down_animation = skill_info->down_animation;
				m_skill_map[id] = pskill;
			}
			break;
			case REMOVEVEC:
			{
				MoveVecSkill* pskill = new MoveVecSkill(id);
				pskill->m_recs= skill_info->m_recs;
				pskill->m_offsets= skill_info->m_offsets;
				pskill->m_effect_time = (skill_info->effect_time / UPDATETIME)* UPDATETIME ;
				pskill->m_dead_time = skill_info->dead_time;
				pskill->m_speed = skill_info->rate;
				pskill->m_dead_len = skill_info->remote_attack_range;
				pskill->m_cool_down = skill_info->cool_down;
				pskill->m_effect_id = skill_info->effect_id;
				pskill->m_up_animation = skill_info->up_animation;
				pskill->m_down_animation = skill_info->down_animation;
				m_skill_map[id] = pskill;
			}
			break;
			case REMOTEVEC:
			{
				TargetSkill* pskill = new TargetSkill(id);
				pskill->m_recs= skill_info->m_recs;
				pskill->m_effect_time = (skill_info->effect_time / UPDATETIME)* UPDATETIME ;
				pskill->m_release_time = (skill_info->release_time / UPDATETIME)* UPDATETIME ;
				pskill->m_dead_time = skill_info->dead_time;
				pskill->m_dead_len = skill_info->remote_attack_range;
				pskill->m_cool_down = skill_info->cool_down;
				pskill->m_effect_id = skill_info->effect_id;
				pskill->m_up_animation = skill_info->up_animation;
				pskill->m_down_animation = skill_info->down_animation;
				m_skill_map[id] = pskill;
			}
			break;
		}
	}
}
	
bool SkillControl::available() {
	if(m_id) {
		return m_skill_map[m_id]->available();
	}
	return false;
}
	
void SkillControl::update() {
	SkillMap::iterator itr = m_skill_map.begin();
	for(; itr!=m_skill_map.end(); ++itr) {
		itr->second->update();	
	}
}
	
bool SkillControl::try_effect( Entity* src, Entity* des ) {
	if(m_id) {
		return m_skill_map[m_id]->try_effect(src, des);
	}
	return false;
}
	
bool SkillControl::effect(Entity* src, Entity* des, TileWorld<>::Point& direct, EffectManager* pManager, CSMonsterAttackInfo* info) {
	if(m_id) {
		return m_skill_map[m_id]->effect(src, des, direct, pManager, info);
	}
	return false;
}
	
bool SkillControl::exchange_current(uint32_t id) {
	if(m_skill_map.find(id)!=m_skill_map.end()) {
		m_id = id;
		return true;
	}
	return false;
}
	
Skill* SkillControl::current_skill() {
	if(m_id) {
		return m_skill_map[m_id];
	}
	return NULL;
}
	
uint32_t SkillControl::current_skill_id() {
	return m_id;
}
	
