#pragma once

#include "SpriteMonster.h"

class SpriteMonsterArcher : public SpriteMonster
{
	friend class SpriteMonsterMgr;
public:
	virtual void Update(float fTime,bool &bDeleteSelf);
	virtual void onEventMsgAttack(CCPoint serverPos, CCPoint direction, int animId, SkillInfo info);
	virtual CCPoint onEventAttacked(CCPoint desPoint);

	virtual void playEffect(SkillInfo info);
	void initEffect(unsigned int effectId);
	CCNode * getFreeEffectNode();

protected:
	SpriteMonsterArcher(MonsterInitInfo info);
    virtual ~SpriteMonsterArcher(); 
	
	std::vector<CCNode *> effectNodes;	
	bool effectInited;

};