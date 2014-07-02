#include "SpriteMonsterArcher.h"
#include "SpriteMonsterMgr.h"

#include "LevelManager.h"
#include "LevelLayer.h"
#include "ParticleManager.h"

#define	EFFECT_COUNT 5

SpriteMonsterArcher::SpriteMonsterArcher(MonsterInitInfo info)
	:SpriteMonster(info)
	,effectInited(false)
{
	
}

SpriteMonsterArcher::~SpriteMonsterArcher()
{
	removeSelf();
}

void SpriteMonsterArcher::Update(float fTime,bool &bDeleteSelf)
{
	SpriteMonster::Update(fTime, bDeleteSelf);
	//层级更新
	LevelLayer* layer = LevelManager::sShareInstance()->getCurrentLevelLayer();
	if (!layer)
	{
		return;
	}

	//特效层级更新
	if (effectInited)
	{
		for (size_t i = 0; i < effectNodes.size(); i++)
		{
			if (effectNodes[i] && effectNodes[i]->isVisible())
			{
				CCPoint nowPos = effectNodes[i]->getPosition();
				layer->getObjectLayer()->reorderChild(effectNodes[i], LevelLayer::sCalcZorder(nowPos));
			}			
		}
	}
}

void SpriteMonsterArcher::onEventMsgAttack(CCPoint serverPos, CCPoint direction, int animId, SkillInfo info)
{
	SpriteMonster::onEventMsgAttack(serverPos, direction, animId, info);
	if (info.effectId)
	{
		playEffect(info);
	}
}

CCPoint SpriteMonsterArcher::onEventAttacked(CCPoint desPoint)
{	
	CCPoint nowPos = this->getPosition();
	CCPoint endPos = nowPos;

	if (!LevelManager::sShareInstance()->getCurrentLevelLayer()->getPhysicsLayer()->isPointReachable(desPoint))
	{
		desPoint = nowPos;
	}	

	//防止未接收到死亡包时怪物不消失
	if (this->fsm_rule.GetState() == MONSTER_STATE_DEAD)
	{
		return endPos;
	}

	if(!this->isBoss && !this->isElite)
	{
		endPos = this->moveToPoint(desPoint, 200.0f);	
		this->fsm_rule.SetState(MONSTER_STATE_HURT);
		for (size_t i = 0; i < effectNodes.size(); i++)
		{
			if (!effectNodes[i]->isVisible())
			{
				effectNodes[i]->stopAllActions();
			}
		}
	}	

	return endPos;
}

void SpriteMonsterArcher::playEffect(SkillInfo info)
{		
	initEffect(info.effectId);
	
	CCNode * effectNode = getFreeEffectNode();
	if (!effectNode)
	{
		return;
	}

	float distance = ccpDistance(info.startPosition, info.endPosition);
	float speed = info.speed * 16;
	CCPoint directVec = ccpSub(info.endPosition, info.startPosition);

	float degree;
	degree = atan(directVec.x / directVec.y) * 180 / 3.14;
	if (directVec.y < 0)
	{
		degree += 180;
	}

	CCPoint startCell = LevelManager::sShareInstance()->pointPixelToCell(info.startPosition);
	CCPoint endCell = LevelManager::sShareInstance()->pointPixelToCell(info.endPosition);
	//CCLOG("arrow start pos: %f, %f, end pos: %f, %f", startCell.x, startCell.y, endCell.x, endCell.y);

	effectNode->setPosition(info.startPosition);	
	effectNode->setRotation(degree);	
	
	CCArray *arrayOfActions = CCArray::create();

	CCDelayTime * delayEffect = CCDelayTime::create(info.delayTime / 1000);
	CCCallFunc *showFunc = CCCallFuncND::create(this, 
										callfuncND_selector(SpriteMonster::ccCallShowEffect),
										(void *)effectNode);
	CCMoveTo * moveEffect = CCMoveTo::create(distance / speed, info.endPosition);	
	CCCallFunc *hideFunc = CCCallFuncND::create(this, 
										callfuncND_selector(SpriteMonster::ccCallHideEffect),
										(void *)effectNode);

	arrayOfActions->addObject(delayEffect);
	arrayOfActions->addObject(showFunc);
	arrayOfActions->addObject(moveEffect);
	arrayOfActions->addObject(hideFunc);
	CCFiniteTimeAction *sequence = CCSequence::create(arrayOfActions);

	effectNode->stopAllActions();
	effectNode->runAction(sequence);

	return;	
}

void SpriteMonsterArcher::initEffect(unsigned int effectId)
{
	if(effectInited)
	{
		return;
	}

	effectNodes.clear();
	LevelLayer * layer = LevelManager::sShareInstance()->getCurrentLevelLayer();
	if (!layer)
	{
		ASSERT(0, "LevelLayer is NULL");
		return;
	}

	for (int i = 0; i < EFFECT_COUNT; i++)
	{
		CCNode * effectNode = CCNode::create();
		EffectSprite * skillAnim = ParticleManager::Get()->createEffectSprite(effectId,"");
		skillAnim->SetAnim(kType_Play, 1, true);
		effectNode->addChild(skillAnim);
		effectNode->setVisible(false);

		//添加到动态管理层
		
		effectNodes.push_back(effectNode);
		layer->getObjectLayer()->addChild(effectNodes[i], LevelLayer::sCalcZorder(m_oldPos));
	}
	effectInited = true;
}

CCNode * SpriteMonsterArcher::getFreeEffectNode()
{
	for (size_t i = 0; i < effectNodes.size(); i++)
	{
		if (false == effectNodes[i]->isVisible())
		{
			return effectNodes[i];			
		}
	}
	ASSERT(0, "Too much effect in monster");
	return NULL;
}