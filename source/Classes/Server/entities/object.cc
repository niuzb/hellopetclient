// project-specific headers go here
#include "object.h"
#include <math.h>

using namespace google::protobuf;
	
Entity::Entity(uint32_t id, uint8_t groupid) :
	base::Object<uint32_t> (id), m_groupid(groupid), m_pos(0,0), m_direct(0 -1) {

}
	
TileWorld<>::Rectangle Entity::space() {
	return m_prop.space+m_pos;
}
	
bool Entity::attack_check(Entity* pEntity) {
	TileWorld<>::Rectangle rec = m_fightprop.fight_rec1.move(m_pos);
	if(rec.touch(pEntity->space())) {
		return true;
	}
	rec = m_fightprop.fight_rec2.move(m_pos);
	if(rec.touch(pEntity->space())) {
		return true;
	}
	rec = m_fightprop.fight_rec3.move(m_pos);
	if(rec.touch(pEntity->space())) {
		return true;
	}
	rec = m_fightprop.fight_rec4.move(m_pos);
	if(rec.touch(pEntity->space())) {
		return true;
	}
	return false;
}
	
void Entity::attack(Entity* pEntity) {
	pEntity->under_attack(this);	
	uint32_t hp = pEntity->m_prop.health_point;
	uint32_t hit = m_fightprop.physical_attack - pEntity->m_fightprop.physical_defence;
	if(hp>=hit) {
		pEntity->m_prop.health_point -= hit;
	} else {
		pEntity->m_prop.health_point = 0;
	}
}
	
void Entity::skill(Entity* pEntity, uint32_t skill_id) {
	pEntity->under_skill(this, skill_id);
	uint32_t hp = pEntity->m_prop.health_point;
/*modify furture*/
	uint32_t hit = 10;
	if(hp>=hit) {
		pEntity->m_prop.health_point -= hit;
	} else {
		pEntity->m_prop.health_point = 0;
	}
}
	
bool Entity::attach(const TileWorld<>::Point& point, uint8_t rule ) {
	if( (m_groupid  | rule) != 0) {
		return false;
	} else {
		TileWorld<>::Rectangle rec = space() ;
		return rec.point_in_range(point);		
	}
}
	
bool Entity::attach(const TileWorld<>::Rectangle& rec, uint8_t rule ) {
	if( (m_groupid  | rule) != 0) {
		return false;
	} else {
		TileWorld<>::Rectangle pos_rec = space();
		return pos_rec.touch(rec);		
	}
}
