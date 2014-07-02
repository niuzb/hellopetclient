#include "MonsterSingleEffect.h"
#include "SpriteMonsterMgr.h"

#include "LevelManager.h"
#include "LevelLayer.h"
#include "ParticleManager.h"

#define	EFFECT_COUNT 5
#define EFFECT_TAG	 1000
#define EFFECT_OFFSET 100.0f

MonsterSingleEffect::MonsterSingleEffect(MonsterInitInfo info)
	:SpriteMonster(info)
	,effectInited(false)
{
	
}

MonsterSingleEffect::~MonsterSingleEffect()
{
	removeSelf();
}

void MonsterSingleEffect::Update(float fTime,bool &bDeleteSelf)
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

void MonsterSingleEffect::onEventMsgAttack(CCPoint serverPos, CCPoint direction, int animId, SkillInfo info)
{
	SpriteMonster::onEventMsgAttack(serverPos, direction, animId, info);
	if (info.effectId)
	{
		playEffect(info);
	}
}

CCPoint MonsterSingleEffect::onEventAttacked(CCPoint desPoint)
{	
	//CCLOG("monster %d receive attacked msg............", m_ID);
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

void MonsterSingleEffect::ccCallShowEffect(CCNode * node, void * data)
{
	CCNode * effectNode = (CCNode *)data;
	effectNode->setVisible(true);
	EffectSprite * skillAnim = (EffectSprite *)effectNode->getChildByTag(EFFECT_TAG);
	if (!skillAnim)
	{
		ASSERT(0, "can't get effect");
		return;
	}
	skillAnim->SetAnim(kType_Play, 1, false);
}

void MonsterSingleEffect::playEffect(SkillInfo info)
{		
	initEffect(info.effectId);
	
	CCNode * effectNode = getFreeEffectNode();
	if (!effectNode)
	{
		return;
	}
	
	effectNode->setPosition(ccpAdd(info.endPosition, ccp(0, EFFECT_OFFSET)));

	CCArray *arrayOfActions = CCArray::create();
	CCDelayTime * delayEffect = CCDelayTime::create(info.delayTime / 1000);
	CCCallFunc *showFunc = CCCallFuncND::create(this, 
										callfuncND_selector(MonsterSingleEffect::ccCallShowEffect),
										(void *)effectNode);
	CCDelayTime * delayHide = CCDelayTime::create(2.0f);
	CCCallFunc *hideFunc = CCCallFuncND::create(this, 
										callfuncND_selector(MonsterSingleEffect::ccCallHideEffect),
										(void *)effectNode);

	arrayOfActions->addObject(delayEffect);
	arrayOfActions->addObject(showFunc);
	arrayOfActions->addObject(delayHide);
	arrayOfActions->addObject(hideFunc);
	CCFiniteTimeAction *sequence = CCSequence::create(arrayOfActions);

	effectNode->stopAllActions();
	effectNode->runAction(sequence);

	return;	
}

void MonsterSingleEffect::initEffect(unsigned int effectId)
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
		skillAnim->SetAnim(kType_Play, 1, false);
		skillAnim->setTag(EFFECT_TAG);
		//特效相对父节点位置下移，方便计算层级
		skillAnim->setPosition(ccp(0, - EFFECT_OFFSET));
		effectNode->addChild(skillAnim);
		effectNode->setVisible(false);

		//添加到动态管理层
		
		effectNodes.push_back(effectNode);
		layer->getObjectLayer()->addChild(effectNodes[i], LevelLayer::sCalcZorder(m_oldPos));
	}
	effectInited = true;
}

CCNode * MonsterSingleEffect::getFreeEffectNode()
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