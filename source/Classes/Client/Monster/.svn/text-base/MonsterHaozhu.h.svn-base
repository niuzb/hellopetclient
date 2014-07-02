#pragma once

#include "SpriteMonster.h"
#include "time.h"

class MonsterHaozhu : public SpriteMonster
{
	friend class SpriteMonsterMgr;
public:
	virtual void onEventMsgAttack(CCPoint serverPos, CCPoint direction, int animId, SkillInfo info);

	virtual void setAttackAnimation(int animId, DIRECTION_MONSTER direction);

	virtual void animationHandler(const char* _aniType, const char* _aniID, const char* _frameID);

	void runByInfo();
	void endRun();

protected:
	MonsterHaozhu(MonsterInitInfo info);
    virtual ~MonsterHaozhu(); 

	SkillInfo runEffectInfo;
	clock_t start, finish;
};