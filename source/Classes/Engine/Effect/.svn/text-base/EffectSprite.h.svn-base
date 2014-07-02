#pragma once

#include "cocos2d.h"
#include "SASpriteDefine.h"
#include "HeroEffectDefine.h"
#include "RoleActorBase.h"
#include "BoneSpriteMoveable.h"

class RoleActorBase;

class EffectSprite : public BoneSpriteMoveable
{
public:
	EffectSprite(int Type);	
	virtual ~EffectSprite();

	bool isTouchSelf(cocos2d::CCPoint pt);
	CCSize getCurContentSize();
	CCSize getColliderRectSize();

	static EffectSprite* effectWithID(int s_id,const char *name);
	bool initWithId(int id,const char *name);

	void setPlayerNameLabelPos(CCPoint pos);
	virtual void animationHandler(const char* _aniType, const char* _aniID, const char* _frameID);
private:
	CCLabelTTF *mEffectNameLabel;
};