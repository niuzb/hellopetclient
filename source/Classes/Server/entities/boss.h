#ifndef BOSS_H_
#define BOSS_H_
#include "../base/ProbabilityGen.hpp"

class FlowerDemon: public Monster {
public:
	FlowerDemon(uint32_t random_id, TileWorld<>* tileworld, EffectManager* effect_manager) :
		Monster(random_id, tileworld, effect_manager),
		m_change_value(0)
	{
		m_change_value = base::ranged_random(1,3);
	}

	void do_attack(Entity* pEntity, CSMonsterAttackRsp* attack_msg ) {
		if(!m_change_value) {
			m_skill_control.exchange_current(1900221);
			m_change_value = base::ranged_random(1,3);
		} else {
			m_skill_control.exchange_current(1900211);
			m_change_value --;
		}
		Monster::do_attack(pEntity, attack_msg);
	}

private:
	uint32_t m_change_value;
};

#endif
