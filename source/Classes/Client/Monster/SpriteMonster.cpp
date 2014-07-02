#include "SpriteMonster.h"
#include "SpriteSeerListener.h"
#include "LevelDefine.h"

//#include "Define.h"
#include "EnginePlayerManager.h"
#include "GameManager.h"
#include "CrossPlatform.h"
#include "GameFontManager.h"
#include "SpriteMonsterMgr.h"
#include "GameAudioManager.h"
#include "ParticleManager.h"
#include "SkillDispMgr.h"
#include "LevelManager.h"
#include "simplefsm_macro.h"
#include "ItemUpdateManager.h"


using namespace cocos2d;

//状态切换
bool SpriteMonster::Rule::States(StateMachineEvent event, int state)
{
	BeginStateMachine

	State(MONSTER_STATE_INITIALIZE)
	OnEnter
	//CCLOG("monster %d enter MONSTER_STATE_INITIALIZE", _this->m_ID);
	OnUpdate
	OnExit

	State(MONSTER_STATE_IDLE)
	OnEnter
	//CCLOG("monster %d enter MONSTER_STATE_IDLE", _this->m_ID);
	_this->setAnimFromStateAndDirection(MONSTER_STATE_IDLE, _this->direction);
	OnUpdate
	OnExit

	State(MONSTER_STATE_RUN)
	OnEnter
	//CCLOG("monster %d enter MONSTER_STATE_RUN", _this->m_ID);
	_this->setAnimFromStateAndDirection(MONSTER_STATE_RUN, _this->direction);
	OnUpdate
	OnExit

	State(MONSTER_STATE_ATTACK)
	OnEnter
	//CCLOG("monster %d enter MONSTER_STATE_ATTACK", _this->m_ID);
	//_this->m_rootSprite->stopAllActions();
	//_this->setAnimFromStateAndDirection(MONSTER_STATE_ATTACK, _this->direction);
	OnUpdate
	OnExit

	State(MONSTER_STATE_HURT)
	OnEnter
	//CCLOG("monster %d enter MONSTER_STATE_HURT", _this->m_ID);
	_this->setAnimFromStateAndDirection(MONSTER_STATE_HURT, _this->direction);
	OnUpdate
	OnExit

	State(MONSTER_STATE_DEAD)
	OnEnter
	//CCLOG("monster %d enter MONSTER_STATE_DEAD", _this->m_ID);
	OnUpdate
	OnExit

	EndStateMachine
}

SpriteMonster::SpriteMonster(MonsterInitInfo info)
	:BoneSpriteMoveable(info.typeId, false),
	m_TotalHp(info.totalHp),
	totalScheduleTimer(0.7f),
	selfScheduleTimer(-1.0f),
	blood(info.totalHp),
	speed(info.speed * 16),
	isBoss(info.isBoss),
	isElite(info.isElite),
	m_attackedEffectSprite(NULL),
	lastAnimId(0),
	lastFlip(false),
	showAnim(true)
{
	ItemUpdateManager::Get()->addToUpdateManager(this);
}

SpriteMonster::~SpriteMonster()
{
	if (SpriteMonsterMgr::Get())
	{
		SpriteMonsterMgr::Get()->Remove(this);
	}

	if(m_attackedEffectSprite)
	{
		EnginePlayerManager::getInstance()->removeEffectAsprite(m_attackedEffectSprite);
		m_attackedEffectSprite = NULL;
	}

	ItemUpdateManager::Get()->removeFromUpdateManager(this);
}

bool SpriteMonster::initWithId(unsigned int m_id, const char *name, unsigned int typeId)
{    
	/// store the monster's id
	this->m_ID = m_id;
	this->m_TypeID = typeId;
	m_name = std::string(name);

	m_animBone =  EnginePlayerManager::getInstance()->addBoneAnimSprite(typeId); 
	resetParentRole(this);
	attachBoneAnimToRootSprite(1);
	m_effectSprite = ParticleManager::Get()->createEffectSprite(102,"");
	m_rootSprite->addChild(m_effectSprite,m_rootSprite->getZOrder()+20);	
	m_effectSprite->setPosition(getAttachPoint(kType_ATTACK_HURT));
	m_effectSprite->setVisible(false);

	m_attackedEffectSprite = ParticleManager::Get()->createEffectSprite(101,"");
	m_rootSprite->addChild(m_attackedEffectSprite,m_rootSprite->getZOrder()+20);
	m_attackedEffectSprite->setPosition(getAttachPoint(kType_ATTACK_HURT));
	m_attackedEffectSprite->setVisible(false);

	//初始化状态机
	fsm_rule._this = this;

	fsm_rule.Initialize();

	//设置启动方向及状态
	this->direction = DIRECTION_DOWN_LEFT;

	fsm_rule.SetState(MONSTER_STATE_IDLE);

    return  true;
}

void SpriteMonster::Update(float fTime,bool &bDeleteSelf)
{
	
	bDeleteSelf = false;

	if (GetUpdateEnabled() && !showAnim)
	{
		this->SetAnim(lastAnimId,1,true,this);
		this->SetAnimFlipX(lastFlip);
		showAnim = true;
	}
	
	if (!GetUpdateEnabled() && showAnim)
	{
		showAnim = false;
	}

	//状态机更新	
	fsm_rule.Update();

	//怪物渐隐消失操作
	if (selfScheduleTimer != -1)
	{
		selfScheduleTimer += fTime;
		if (selfScheduleTimer >= (totalScheduleTimer))
		{
			selfScheduleTimer = -1;
			m_animBone->getCurRoleActorBase()->setArmaturetOpacity(255);

			bDeleteSelf = true;
		}
		else
		{
			m_animBone->getCurRoleActorBase()->setArmaturetOpacity(255 * (1.0 - ((float)selfScheduleTimer)/totalScheduleTimer));

		}
	}

	//层级更新
	LevelLayer* layer = LevelManager::sShareInstance()->getCurrentLevelLayer();
	if (!layer)
	{
		return;
	}

	//怪物层级更新	
	CCPoint pos = getPosition();
	if(pos.x != m_oldPos.x || pos.y != m_oldPos.y)
	{
		m_oldPos = pos;	
		
		if (layer)
		{
			layer->getObjectLayer()->reorderChild(this, LevelLayer::sCalcZorder(pos));
		}		
	}
}

CCPoint SpriteMonster::moveToPoint(CCPoint desPoint, float speed)
{
	CCPoint curPoint = this->getPosition();

	CPhysicsLayer * pLayer = LevelManager::sShareInstance()->getCurrentLevelLayer()->getPhysicsLayer();

	if (!pLayer->isPointReachable(desPoint))
	{
		desPoint = curPoint;
	}	

	if (desPoint.x == curPoint.x && desPoint.y == curPoint.y)
	{
		return curPoint;
	}

	CCArray *arrayOfActions = CCArray::create();

	float distance = ccpDistance(curPoint, desPoint);
	CCMoveTo *move = CCMoveTo::create( distance / speed, desPoint);

	//被击退结束时切换回idle状态
	this->mtpState = int(MONSTER_STATE_IDLE);
	CCCallFunc *endFunc = CCCallFuncND::create(this, 
								callfuncND_selector(SpriteMonster::ccCallChangeState),
								(void *)&mtpState);

	arrayOfActions->addObject(move);
	//arrayOfActions->addObject(endFunc);
				
	CCFiniteTimeAction *sequence = CCSequence::create(arrayOfActions);

	m_rootSprite->stopAllActions();
	m_rootSprite->runAction(sequence);		
	

	return desPoint;
}

void SpriteMonster::moveByPoints(const std::vector<CCPoint>& points)
{
	CCPoint nowPoint = this->getPosition();	
	float distance1 = ccpDistance(points[0], nowPoint);

	if(points.size() == 1 && distance1 < 1.0f)
	{
		//CCLOG("no move");
		return;
	}
	//使用格子点判断方向，同格子不改方向
	CCPoint endCell = LevelManager::sShareInstance()->pointPixelToCell(points[0]);
	CCPoint startCell = LevelManager::sShareInstance()->pointPixelToCell(nowPoint);

	this->mbpDir1 = CCPoint(ccpSub(endCell, startCell));
	//CCLOG("monster: %d  position: %f, %f, delay distance: %f", (int)this->m_ID, startCell.x, startCell.y, distance1);

	//启动和结束时的动画转换
	this->mbpState1 = int(MONSTER_STATE_IDLE);
	this->mbpState2 = int(MONSTER_STATE_RUN);
	
	CCCallFunc *startFunc = CCCallFuncND::create(this, 
										callfuncND_selector(SpriteMonster::ccCallChangeState),
										(void *)&mbpState2);
	CCCallFunc *endFunc = CCCallFuncND::create(this, 
										callfuncND_selector(SpriteMonster::ccCallChangeState),
										(void *)&mbpState1);


	CCArray *arrayOfActions = CCArray::create();

	if(points.size() > 1)
	{
		float distance2 = ccpDistance(points[1], points[0]);
		this->mbpDir2 = CCPoint(ccpSub(points[1], points[0]));

		float time1 = distance1 / (speed);
		float totalTime = (distance2) / speed;

		//偏差过大时闪烁
		//if (distance1 > 32.0f)
		{
			//time1 = 0;
		}		
		CCMoveTo *move1 = CCMoveTo::create( time1, points[0]);
		CCMoveTo *move2 = CCMoveTo::create( totalTime - time1 , points[1]);

		//func1和func2为调整方向
		CCCallFunc *func1 = CCCallFuncND::create(this, 
										callfuncND_selector(SpriteMonster::ccCallChangeDirection),
										(void *)&mbpDir1);
		CCCallFunc *func2 = CCCallFuncND::create(this, 
										callfuncND_selector(SpriteMonster::ccCallChangeDirection),
										(void *)&mbpDir2);
		arrayOfActions->addObject(startFunc);

		arrayOfActions->addObject(func1);
		arrayOfActions->addObject(move1);

		arrayOfActions->addObject(func2);
		arrayOfActions->addObject(move2);
	}
	else
	{
		CCMoveTo *move = CCMoveTo::create( distance1 / (speed), points[0]);	
		CCCallFunc *func = CCCallFuncND::create(this, 
										callfuncND_selector(SpriteMonster::ccCallChangeDirection),
										(void *)&mbpDir1);

		arrayOfActions->addObject(startFunc);

		arrayOfActions->addObject(func);
		arrayOfActions->addObject(move);
	}

	for(size_t i = 1; i < points.size() - 1; i++)
	{
		float distance = ccpDistance(points[i+1], points[i]);
		this->mbpDir3 = CCPoint(ccpSub(points[i+1], points[i]));

		CCMoveTo *move = CCMoveTo::create( distance / speed, points[i+1]);
		CCCallFunc *func = CCCallFuncND::create(this, 
										callfuncND_selector(SpriteMonster::ccCallChangeDirection),
										(void *)&mbpDir3);
		arrayOfActions->addObject(func);
		arrayOfActions->addObject(move);
	}

	arrayOfActions->addObject(endFunc);

	CCFiniteTimeAction *sequence = CCSequence::create(arrayOfActions);

	m_rootSprite->stopAllActions();
	m_rootSprite->runAction(sequence);

}

void SpriteMonster::PlayAttackedEffect(bool isCrit)
{
	//EffectType type = EUnkownEffect;
	if(isCrit)
	{
		/*type = CritAttackEffect;*/
		m_effectSprite->SetAnim(kType_Play,1,false);
	}
	else
	{
		//type = NormalAttackEffect;
		m_attackedEffectSprite->SetAnim(kType_Play,1,false);
	}
	//m_effectSprite->SetAnim(kType_Play,1,false);
}

void SpriteMonster::ccCallChangeDirection(CCNode * node, void * data)
{
	CCPoint *pdirect = (CCPoint *)data;
	this->changeDirection(*pdirect);
}

void SpriteMonster::ccCallChangeState(CCNode * node, void * data)
{
	int * pstate = (int *)data;
	if (MONSTER_STATE_DEAD != this->fsm_rule.GetState())
	{
		this->fsm_rule.SetState(*pstate);
	}	
}

void SpriteMonster::ccCallShowEffect(CCNode * node, void * data)
{
	CCNode * effectNode = (CCNode *)data;
	effectNode->setVisible(true);
}

void SpriteMonster::ccCallHideEffect(CCNode * node, void * data)
{
	CCNode * effectNode = (CCNode *)data;
	effectNode->setVisible(false);
}

void SpriteMonster::changeDirection(CCPoint direct)
{
	if(direct.x == 0 && direct.y == 0)
	{
		return;
	}
	if((MONSTER_STATE_DEAD == this->fsm_rule.GetState()) || (this->pointToDirection(direct) == this->direction) )
	{
		return;
	}
	//更新方向
	this->direction = this->pointToDirection(direct);
	
	//设置动画
	setAnimFromStateAndDirection(this->fsm_rule.GetState(), this->direction);
	return;
	
}

DIRECTION_MONSTER SpriteMonster::pointToDirection(CCPoint direct)
{
	DIRECTION_MONSTER direction =  DIRECTION_MONSTER_UNKNOW;

	if (direct.y > 0)
	{
		if (direct.x > 0)
		{
			direction = DIRECTION_UP_RIGHT;
		}else
		{
			direction = DIRECTION_UP_LEFT;
		}
	}
	else
	{
		if (direct.x > 0)
		{
			direction = DIRECTION_DOWN_RIGHT;
		}else
		{
			direction = DIRECTION_DOWN_LEFT;
		}
	}

	return direction;
}

void SpriteMonster::setAnimFromStateAndDirection(MONSTER_STATE state, DIRECTION_MONSTER direction)
{
	int animId = kTypeAction_UnKnow;
	bool isFlipX = false;
	bool isLoop = true;
	bool isPauseOnOver = false;

	//根据怪物状态确定基准animId
	switch(state){
		case MONSTER_STATE_IDLE:
			animId = kTypeIdle_FaceDown_Stand_OTH;
			break;

		case MONSTER_STATE_RUN:
			animId = kTypeRun_FaceDown_OTH;
			break;

		case MONSTER_STATE_ATTACK:
			animId = kTypeAttack_FaceDown_1;
			isLoop = false;
			break;

		case MONSTER_STATE_HURT:
			animId = kTypeHurt_FaceDown;
			isLoop = false;
			break;

		case MONSTER_STATE_DEAD:
			isLoop = false;
			isPauseOnOver = true;
			selfScheduleTimer = 0;
			animId = kTypeDie_FaceDown;
			break;

		default:
			break;
	}

	//根据方向修正animId及水平翻转
	switch(direction)
	{
		case DIRECTION_UP_LEFT:
			isFlipX = true;
			animId += 1;
			break;

		case DIRECTION_UP_RIGHT:
			isFlipX = false;
			animId += 1;
			break;

		case DIRECTION_DOWN_LEFT:
			isFlipX = false;
			break;

		case DIRECTION_DOWN_RIGHT:
			isFlipX = true;
			break;

		default:
			break;
	}

	this->SetAnim(animId,1,true,this);
	this->SetAnimFlipX(isFlipX);

	lastAnimId = animId;
	lastFlip = isFlipX;

	if (isPauseOnOver)
	{
		this->SetAnimPauseOnOver(true);
	}	
	return;
}

void SpriteMonster::setAnimFromStateAndDirection(int state, DIRECTION_MONSTER direction)
{
	setAnimFromStateAndDirection((MONSTER_STATE)state, direction);
}

void SpriteMonster::setAttackAnimation(int animId, DIRECTION_MONSTER direction)
{
	int i;
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

	lastAnimId = animId;
	lastFlip = isFlipX;

	return;
}

void SpriteMonster::onEventMsgMove(const std::vector<CCPoint>& points)
{
	if (this->speed == 0)
	{
		return;
	}
	//CCLOG("monster %d receive move msg............", m_ID);
	if(MONSTER_STATE_IDLE != fsm_rule.GetState() && MONSTER_STATE_RUN != fsm_rule.GetState())
	{
		return;
	}
	this->moveByPoints(points);
}

void SpriteMonster::onEventMsgAttack(CCPoint serverPos, CCPoint direction, int animId, SkillInfo info)
{
	if (this->fsm_rule.GetState() == MONSTER_STATE_DEAD)
	{
		return;
	}
	
	this->setPosition(serverPos);
	this->m_rootSprite->stopAllActions();
	this->fsm_rule.SetState(MONSTER_STATE_ATTACK);
	this->changeDirection(direction);
	setAttackAnimation(animId, this->direction);		
}

void SpriteMonster::onEventMsgDead()
{
	//CCLOG("monster %d receive dead msg............", m_ID);

	//鉴于该状态线程不安全，会被打断，此处采取极端做法，直接终止状态机并执行死亡状态相关操作
	this->fsm_rule.SetState(MONSTER_STATE_DEAD);
	this->fsm_rule.Terminate();
	this->m_rootSprite->stopAllActions();
	this->setAnimFromStateAndDirection(MONSTER_STATE_DEAD, this->direction);

	CCNode * shadow = this->m_rootSprite->getChildByTag(SHADOW_TAG);
	if (shadow)
	{
		shadow->removeFromParentAndCleanup(true);
	}

	CCNode * eliteEffect = this->m_rootSprite->getChildByTag(ELITE_TAG);
	if (eliteEffect)
	{
		eliteEffect->removeFromParentAndCleanup(true);
	}
}

CCPoint SpriteMonster::onEventAttacked(CCPoint desPoint)
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
		endPos = this->moveToPoint(desPoint, 192.0f);	
		this->fsm_rule.SetState(MONSTER_STATE_HURT);
	}	

	return endPos;
}

void SpriteMonster::removeSelf()
{
	SpriteMonsterMgr::Get()->Remove(this);
	this->removeFromParentAndCleanup(true);
}

void SpriteMonster::animationHandler(const char* _aniType, const char* _aniID, const char* _frameID)
{
	if (0 == strcmp(_aniType,"loopComplete") ||
		0 == strcmp(_aniType,"complete"))
	{
		//攻击状态结束切回idle
		int animId = m_animBone->getAnimId();
		if( (int)kTypeAttack_FaceDown_1 == animId ||
			(int)kTypeAttack_FaceUp_1   == animId)			
		{
			this->fsm_rule.SetState(MONSTER_STATE_IDLE);
		}

		if( (int)kTypeHurt_FaceDown == animId ||
			(int)kTypeHurt_FaceUp   == animId)			
		{
			this->fsm_rule.SetState(MONSTER_STATE_IDLE);
		}

		//if((int)kTypeDie_FaceDown     == animId ||
		//	(int)kTypeDie_FaceUp       == animId )
		//{
		//	selfScheduleTimer = 0;
		//}

		for (int i = 0; i < extraAnims.size(); i++)
		{
			if (extraAnims[i] == animId)
			{
				this->fsm_rule.SetState(MONSTER_STATE_IDLE);
			}
		}

	}
}