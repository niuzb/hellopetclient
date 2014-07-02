#include "MonsterHaozhu.h"
#include "SpriteMonsterMgr.h"

MonsterHaozhu::MonsterHaozhu(MonsterInitInfo info)
	:SpriteMonster(info)
{
	
}

MonsterHaozhu::~MonsterHaozhu()
{
	removeSelf();
}

void MonsterHaozhu::onEventMsgAttack(CCPoint serverPos, CCPoint direction, int animId, SkillInfo info)
{
	SpriteMonster::onEventMsgAttack(serverPos, direction, animId, info);
	if (info.effectId == 0)
	{
		return;
	}
	runEffectInfo = info;
	
	CCArray *arrayOfActions = CCArray::create();

	CCDelayTime * delay = CCDelayTime::create(info.delayTime / 1000);
	CCCallFunc * func = CCCallFunc::create(this, callfunc_selector(MonsterHaozhu::runByInfo));

	arrayOfActions->addObject(delay);
	arrayOfActions->addObject(func);

	CCFiniteTimeAction *sequence = CCSequence::create(arrayOfActions);

	m_rootSprite->stopAllActions();
	m_rootSprite->runAction(sequence);
}

void MonsterHaozhu::setAttackAnimation(int animId, DIRECTION_MONSTER direction)
{
	size_t i;
	for (i = 0; i < extraAnims.size(); i++)
	{
		if (extraAnims[i] == animId)
		{
			break;
		}
	}

	if (i >= extraAnims.size())
	{
		extraAnims.push_back(animId);
	}


	bool isFlipX = false;
	switch (direction)
	{
		case DIRECTION_UP_LEFT:
		case DIRECTION_DOWN_RIGHT:
			isFlipX = true;
			break;

		case DIRECTION_UP_RIGHT:
		case DIRECTION_DOWN_LEFT:
			isFlipX = false;
			break;

		default:
			break;
	}

	this->SetAnim(animId,1,true,this);
	this->SetAnimFlipX(isFlipX);
	//start = clock();
	return;
}

void MonsterHaozhu::runByInfo()
{
	
	bool isFlipX = false;
	switch (direction)
	{
		case DIRECTION_UP_LEFT:
		case DIRECTION_DOWN_RIGHT:
			isFlipX = true;
			break;

		case DIRECTION_UP_RIGHT:
		case DIRECTION_DOWN_LEFT:
			isFlipX = false;
			break;

		default:
			break;
	}

	this->SetAnim(runEffectInfo.effectId,1,true,this);
	this->SetAnimFlipX(isFlipX);

	CCPoint nowPoint = this->getPosition();
	float distance = ccpDistance(getPosition(), runEffectInfo.endPosition);
	float speed = runEffectInfo.speed * 16;

	CCArray *arrayOfActions = CCArray::create();

	CCMoveTo * move = CCMoveTo::create(distance / speed, runEffectInfo.endPosition);
	CCCallFunc * func = CCCallFunc::create(this, callfunc_selector(MonsterHaozhu::endRun));

	arrayOfActions->addObject(move);
	arrayOfActions->addObject(func);

	CCFiniteTimeAction *sequence = CCSequence::create(arrayOfActions);

	m_rootSprite->stopAllActions();
	m_rootSprite->runAction(sequence);
}

void MonsterHaozhu::endRun()
{
	CCLOG("end run....");
	this->fsm_rule.SetState(MONSTER_STATE_IDLE);
}


void MonsterHaozhu::animationHandler(const char* _aniType, const char* _aniID, const char* _frameID)
{
	if (0 == strcmp(_aniType,"loopComplete") ||
		0 == strcmp(_aniType,"complete"))
	{
		//¹¥»÷×´Ì¬½áÊøÇÐ»Øidle
		int animId = m_animBone->getAnimId();
		if( (int)kTypeAttack_FaceDown_1 == animId ||
			(int)kTypeAttack_FaceUp_1   == animId)			
		{
			CCLOG("haozhu attack end...............");
			if (m_TypeID != MONSTER_TYPE_TIEQIU)
			{
				this->fsm_rule.SetState(MONSTER_STATE_IDLE);			
				return ;
			}			
		}

		if((int)kTypeDie_FaceDown     == animId ||
			(int)kTypeDie_FaceUp       == animId )
		{
			selfScheduleTimer = 0;
		}


		for (int i = 0; i < extraAnims.size(); i++)
		{
			if (extraAnims[i] == animId)
			{
				//finish = clock();
				//double dur =  (double)(finish - start) / CLOCKS_PER_SEC;
				//runByInfo();
			}
		}

	}
}