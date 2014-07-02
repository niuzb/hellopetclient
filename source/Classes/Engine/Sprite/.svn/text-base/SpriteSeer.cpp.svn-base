#include "SpriteSeer.h"
#include "SpriteSeerListener.h"
#include "LevelDefine.h"

//#include "Define.h"
#include "EnginePlayerManager.h"
#include "GameManager.h"
#include "ItemManager.h"

// UILayer
#include "MainMenuLayer.h"
#include "BattleUILayer.h"
#include "CrossPlatform.h"
#include "GameFontManager.h"
#include "BaseAttackState.h"
#include "EffectSprite.h"
#include "ParticleManager.h"
#include "SkillDispMgr.h"
#include "SpriteMonsterMgr.h"
#include "GameDataManager.h"
#include "InstanceManager.h"
#include "XLogicManager.h"
#include "GameAudioManager.h"
#include "SkeletonAnimRcsManager.h"
#include "GameResourceManager.h"
#include "SpriteFactory.h"
#include "MapDataManager.h"
#include "MainLandManager.h"
#include "UserData.h"
#include "CityListLayer.h"
#include "NpcSprite.h"
#include "BoneNPCManager.h"
#include "ItemUpdateManager.h"

#define AUTO_ATTACK_OFFSET 60.0f
#define AUTO_ATTACK_CD 0.2f
#define PORTAL_CHECK_CD 0.5f
#define PORTAL_CHECK_DISTANCE 100.0f

using namespace cocos2d;


SpriteSeer::SpriteSeer(int type, bool isPlayerSet)
	:BoneSpriteMoveable(type, isPlayerSet)	
	,m_nNormalAttackNum(0)
	,autoAttack(false)
	,autoAttackCDTime(0.0f)
	, m_bNormalAttack(true)
    ,attackedSoundCDTime(0)
	, m_acceleration(0.0f)
	, m_battleSide(0)
	, m_stateMachineRunning(true)
	,posInited(false)
	,portalCheckCDTime(0.0f)
	,m_nameLabel(NULL)
{
     m_pStateMachine = new SkillStateMachine(); 
	 m_pStateFactory = new StateFactory(this);

	 ItemUpdateManager::Get()->addToUpdateManager(this);
}

void SpriteSeer::InitStateMachine()
{
	if(!m_pStateMachine->CheckStateRuning(ToIdle))
		m_pStateMachine->Push(m_pStateFactory->Create(ToIdle, 0));

	ItemUpdateManager::Get()->removeFromUpdateManager(this);
}

void SpriteSeer::ShutDownStateMachine()
{
	//m_pStateMachine->RemoveAllState();

}

SpriteSeer::~SpriteSeer()
{
	ShutDownStateMachine();
    delete m_pStateMachine;
	m_pStateMachine = NULL;

	if(m_pStateFactory)
	{
		delete m_pStateFactory;
		m_pStateFactory = NULL;
	}

	CC_SAFE_DELETE(m_map);

	// Note: 删除和角色绑定的精灵对象
	SpriteFactory::sharedFactory()->RemoveElfFromHero(m_ID,false);
}


SpriteSeer* SpriteSeer::seerWithID(int s_id, const char *name, int type, bool isPlayerSet,bool isCreateEffect)
{
	SpriteSeer *seer = new SpriteSeer(type, isPlayerSet);
	if (seer && seer->initWithId(s_id,type,name,isCreateEffect))
	{
		seer->autorelease();
		return  seer;
	}
	CC_SAFE_DELETE(seer);
	return NULL;
}


bool SpriteSeer::initWithId(int id,int typeId,const char *name,bool isCreateEffect)
{
	m_name = std::string(name);
	m_ID = id;
	m_TypeID = typeId;

	m_animBone =  EnginePlayerManager::getInstance()->addBoneAnimSprite(typeId);
	if (m_animBone == 0)
	{
		return false;
	}
	if(isCreateEffect)
	{
		m_effectSprite = ParticleManager::Get()->createEffectSprite(103,"");
		m_rootSprite->addChild(m_effectSprite,m_rootSprite->getZOrder()+20);
		m_effectSprite->setPosition(getAttachPoint(kType_ATTACK_HURT));
		m_effectSprite->setVisible(false);
	}
	attachBoneAnimToRootSprite(1);

	float labelFontSize = GameFontManager::smallFontSize();
    CCSize nameLabelSize = CCSizeMake(150 / CC_CONTENT_SCALE_FACTOR(), labelFontSize * 1.5);
    m_nameLabel = UILabelTTF::create(name, KJLinXin, labelFontSize, nameLabelSize, kCCTextAlignmentCenter);
    if(m_nameLabel)
    {
        m_nameLabel->setPosition(getAttachPoint(kType_PLAYER_NAME));
        m_rootSprite->addChild(m_nameLabel);
		if(UserData::getUserId() == id)
		{
			m_nameLabel->setColor(ccORANGE);
		}
		else
		{
			if(!MainLandManager::Get()->isMainLand(LevelManager::sShareInstance()->getCurMapId()) && LevelManager::sShareInstance()->isCurrentPVPLevel())
			{
				USERINFO* info = UserData::Get()->GetUserInfo(id);
				if(info)
				{
					USERINFO userInfo = UserData::GetUserInfo();
					if(abs((int)userInfo.battleSide - (int)info->battleSide) % 2 != 0)
					{
						m_nameLabel->setColor(ccRED);
					}
				}
			}
		}
    }

	// init state machine
	InitStateMachine();
	GameDataManager * mgr = GameDataManager::Get();
	HSJoystick * stick = HSJoystick::sharedJoystick();
	if (mgr)
	{		
		bool isMainLandLevel = MainLandManager::Get()->isMainLand(LevelManager::sShareInstance()->getCurMapId());
		SetMoveType(mgr->getHeroMoveType());
		if (isMainLandLevel)
		{
			stick->setIsEnable(false);
			m_eMoveType = MOVE_BY_MOUSE;

			//主城中停止自动攻击
			mgr->setHeroAutoAttack(false);
		}	
		else
		{
			stick->setIsEnable(m_eMoveType == MOVE_BY_MOUSE ? false : true);
		}
	}

	//startAutoAttack();


	//初始化技能vector
	SkillDispMgr * skillMgr = SkillDispMgr::Get();

	vector<int> skillTmp = skillMgr->GetAllSkillID((RoleJobType)getType());
	for (size_t i = 0; i < skillTmp.size(); i++)
	{
		bool isUnlock = skillMgr->IsEquipSkill(skillTmp[i]);
		const SKILL_INFO * info = skillMgr->GetSkillInfo(skillTmp[i]);
		//未解锁技能及buff技能不加入
		if (isUnlock && !info->bBuff)
		{
			skills.push_back(skillTmp[i]);
		}
		else if (info->type == ToNormalAttack && info->partID == 1)
		{
			skills.push_back(skillTmp[i]);
		}
	}
	

	//初始化自己的physicsLayer
    m_map = createSearchLayer();
	
	portalPosition = InstanceManager::Get()->getPortalPosition();

	// Note: 主角
	if (m_ID == UserData::getUserId())
	{
		unsigned int weaponId = ItemManager::Get()->getHeroWeaponId();
		this->SetEquipItemsData(weaponId);
	}

    return  true;
}



void SpriteSeer::startMove()
{   
	switch(m_eMoveType)
	{
	case MOVE_BY_JOY:
		if (m_step < m_map->getPathTop()) 
		{
			//BoneSpriteMoveable::startMove();
			beginAStarSearch();
		}
		else
		{
			if(m_step != 0 && m_map->getPathTop() != 0)
			{
				//BoneSpriteMoveable::endMove();
				endAStarSearch();
			}
		}
		
		break;

	case MOVE_BY_MOUSE:
		//if (m_step < m_map->getPathTop()) 
		//{       
		//	//---------------------------------------------------------------------------------
		//	// diff logic for player seer and other seers
		//	//---------------------------------------------------------------------------------
		//	BaseListener * baseListener = LevelLayer::sGetListenerByTag(getTag());
		//	if (baseListener)
		//	{
		//		SpriteSeerListener* listener =  dynamic_cast<SpriteSeerListener*>(baseListener);
		//		if (listener)
		//		{
		//			listener->HandleObjectMoveEvent(this);
		//		}		 
		//	}
		//}

		////
		//BoneSpriteMoveable::startMove();
		beginAStarSearch();
		if (m_isMoving)
		{
			startPathFinding();
		}

		break;
	}
}


void SpriteSeer::endMove()
{
	switch(m_eMoveType)
	{
	case MOVE_BY_JOY:
		//BoneSpriteMoveable::endMove();
		endAStarSearch();
		break;

	case MOVE_BY_MOUSE:
		//---------------------------------------------------------------------------------
		// diff logic for player seer and other seers
		//---------------------------------------------------------------------------------
		BaseListener * baseListener = LevelLayer::sGetListenerByTag(getTag());
		if (baseListener)
		{
			SpriteSeerListener* listener =  dynamic_cast<SpriteSeerListener*>(baseListener);
			if (listener)
			{
				listener->HandleObjectEndMoveEvent(this);
			}
		}
		//
		//BoneSpriteMoveable::endMove();	
		endAStarSearch();

		if (!autoAttack)
		{
			endPathFinding();
		}
		
		break;
	}

}

void SpriteSeer::beginAStarSearch()
{
	if (m_colliderRect.size.width != 0 && m_colliderRect.size.height != 0)
	{
		CCRect selfColliderRect = this->getRelativeParentColliderRect();
		if (selfColliderRect.intersectsRect(m_colliderRect))
		{
			m_rootSprite->stopAllActions();
			m_map->setStart(getPosition());

			endMove();
			return ;
		}
	}
	if (m_map && m_step < m_map->getPathTop()) 
	{
		float deviceScale = CCDirector::sharedDirector()->getContentScaleFactor();

		CCPoint pos = m_map->getPathPos(m_step);
		float Speed = GetMoveSpeed();

		updateDirection(pos);
		updateRunAnim();
		CCPoint pt1 = this->getPosition();
		

		CCPoint destPoint = CCPoint(pos.x / deviceScale, pos.y / deviceScale);
		    
		m_rootSprite->stopAllActions();

		if(m_pStateMachine && m_pStateFactory)
		{
			VariableSpeedMoveToHandler* pMoveTo = dynamic_cast<VariableSpeedMoveToHandler*>(m_pStateMachine->GetState(ToVariableSpeedMoveToHandler));
			if(pMoveTo == NULL)
			{
				pMoveTo = dynamic_cast<VariableSpeedMoveToHandler*>(m_pStateFactory->Create(ToVariableSpeedMoveToHandler, -1));
				m_pStateMachine->Push(pMoveTo);
				pMoveTo->SetTarget(this, destPoint, Speed);
			}
			else
			{
				pMoveTo->ChangeDstPos(destPoint);
			}
		}
		
		

		m_map->setStart(getPosition());
		m_step++;
	}
	else
	{  
		m_rootSprite->stopAllActions();
		m_map->setStart(getPosition());

		endMove();
	}
}

void SpriteSeer::endAStarSearch()
{
	m_isMoving = false;

	updateWaitAnim();

	//
	if (m_Target && m_func)
	{
		(m_Target->*m_func)();
	}

	m_Target = NULL;
	m_func = NULL;

	//m_fMoveRate = 2.0f;
	m_fAdditionMoveRate = 0.0f;
}
//
//Machtimer machTimer;
//CCPoint g_p1;
//CCPoint g_p2;
//int g_count = 0;
//float speedCount = 0.0f;

void SpriteSeer::Update(float fTime)
{
	if (!posInited)
	{
		if (getPosition().x > 0)
		{
			posInited = true;
			TaskPosition taskPos = GameDataManager::Get()->getTaskPosition();
			int heroId = UserData::Get()->getUserId();
			if (m_ID == heroId && taskPos.cityId)
			{
				//moveToCityPosition(taskPos.cityId, taskPos.position);
				moveToCityPosition(taskPos.cityId,taskPos.position,taskPos.npcId);
			}
		}
	}
	//if(getTag() == MAP_TAG_SEER)
	//{
	//	CCPoint curPos = LevelManager::sShareInstance()->pointPixelToCell(getPosition());
	//	if(curPos.x != g_p1.x || curPos.y != g_p1.y)
	//	{
	//		float speed =  ccpDistance(getPosition(), g_p2) / (machTimer.elapsedMS() / 1000.0f);
	//		//CCLog("Speed : %f", speed);
	//		speedCount += speed;
	//		g_count++;
	//		if(g_count == 30)
	//		{
	//			speed = speedCount / (float)g_count;
	//			CCLog("****** AVG Speed : %f", speed);
	//			speedCount = 0.0f;
	//			g_count = 0;

	//		}
	//		g_p1 = curPos;
	//		g_p2 = getPosition();
	//		machTimer.start();

	//	}
	//}
	//

    if (m_bInRedState)
	{
		m_InRedTime += fTime;
		if (m_InRedTime > 0.1f)
		{
			m_InRedTime = 0;
			revertToOriginColor();
		}
	}
	
	if (m_pStateMachine && m_stateMachineRunning)
	{
		m_pStateMachine->Update(fTime);

		VariableSpeedMoveToHandler* pMoveTo = dynamic_cast<VariableSpeedMoveToHandler*>(m_pStateMachine->GetState(ToVariableSpeedMoveToHandler));
		if(pMoveTo)
		{
			if(pMoveTo)
			{
				if(pMoveTo->IsFinish())
				{
					m_pStateMachine->Remove(ToVariableSpeedMoveToHandler);
					beginAStarSearch();
					
				}
			}
		}
	}

	//自动攻击更新
	if (autoAttackCDTime < AUTO_ATTACK_CD)
	{
		autoAttackCDTime += fTime;
	}
	else if (autoAttack)
	{
		moveToMonster();
		autoAttackCDTime = 0.0f;
	}

	//传送点检测更新
	if (portalCheckCDTime < PORTAL_CHECK_CD)
	{
		portalCheckCDTime += fTime;
	}
	else if (m_eMoveType == MOVE_BY_JOY)
	{
		portalCheckCDTime = 0;
		SpriteMonster * monster = SpriteMonsterMgr::Get()->getNearestMonster();
		float distance = ccpDistance(portalPosition, getPosition());
		if (NULL == monster && distance < PORTAL_CHECK_DISTANCE)
		{
			activePortal();
		}
	}

    if(attackedSoundCDTime > 0)
    {
        attackedSoundCDTime = (attackedSoundCDTime > fTime) ? (attackedSoundCDTime - fTime) : 0 ;
    }
}

void SpriteSeer::PauseStateMachine()
{
	m_stateMachineRunning = false;
}

void SpriteSeer::ResumeStateMachine()
{
	m_stateMachineRunning = true;
}

bool SpriteSeer::tellIsAttackEnable()
{
	bool ret = false;
	BattleUILayer* battleUI = GetBattleUILayer();

	if (battleUI && battleUI->getNormalAttackBtn()->isSelected())
	{
		ret = true;

		SpriteSeer* hero = this;
		if (hero)
		{
			unsigned int skillID = 0;
			//switch(hero->getType())
			//{
			//case kTypeFighter_Boy:
			//case kTypeFighter_Girl:
			//	skillID = 4011101;	// 战士
			//	break;
			//case kTypeMagician_Girl:
			//case kTypeMagician_Boy:
			//	skillID = 4041101;	// 法师
			//	break;
			//case kTypeAssassin_Boy:
			//case kTypeAssassin_Girl:
			//	skillID = 4051101;	// 刺客
			//	break;
			//default:
			//	break;
			//}

			skillID = SkillDispMgr::Get()->GetNormalAttackID(getType());
			if(skillID != 0)
				hero->DoNormalAttack(skillID);
		}
	}
	return ret;
}

bool SpriteSeer::DoNormalAttack(unsigned int skillId)
{
	m_nNormalAttackNum++;
	//printf("m_nNormalAttackNum : %ld\n", m_nNormalAttackNum);
	if(m_pStateMachine->CheckStateRuning(ToNormalAttack))
	{
		return false;
	}
	if (!m_bNormalAttack)
	{
		return false;
	}

	m_pStateMachine->Remove(ToRun);
	m_pStateMachine->Remove(ToIdle);
    
	m_nNormalAttackNum = 1;
	m_pStateMachine->Push(m_pStateFactory->Create(ToNormalAttack, skillId));
	return true;
}

bool SpriteSeer::DoNormalAttack( void )
{
	unsigned int skillID = 0;
	switch(getType())
	{
	case kTypeFighter_Boy:
	case kTypeFighter_Girl:
		skillID = 4011101;	// 战士
		break;
	case kTypeMagician_Girl:
	case kTypeMagician_Boy:
		skillID = 4041101;	// 法师
		break;
	case kTypeAssassin_Boy:
	case kTypeAssassin_Girl:
		skillID = 4051101;	// 刺客
		break;
	default:
		break;
	}

	if(skillID != 0)
		DoNormalAttack(skillID);

	return true;

}

bool SpriteSeer::DoSkillAttack(unsigned int skillId)
{
	if(!SkillDispMgr::Get()->IsCD(GetID(), skillId))
	{
		SkillDispMgr::Get()->SetCD(GetID(), skillId);
        
		m_pStateMachine->Remove(ToRun);
		m_pStateMachine->Remove(ToIdle);
		m_pStateMachine->Remove(ToNormalAttack);

		const SKILL_INFO* pSkillInfo = SkillDispMgr::Get()->GetSkillInfo(skillId);
		/*if (m_pStateMachine->CheckStateRuning(pSkillInfo->type))
		{
			return false;
		}*/
		m_pStateMachine->Push(m_pStateFactory->Create(pSkillInfo->type, skillId));
        
        if(autoAttack)
        {
            MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
            BattleUILayer* battlayer = mLayer->GetBattleUILayer();
            battlayer->autoSkillAttack(skillId);
        }
		return true;

	}
	
	return false;
}

void SpriteSeer::ByAttacked(unsigned int blood, bool isCrit)
{	
	if(m_effectSprite)
	{
		m_effectSprite->SetAnim(kType_Play,1,false);
	}

	bool isHarmful = true;

	USERINFO* info = UserData::Get()->GetUserInfo(m_ID);
	if(info)
	{
		USERINFO* pHeroInfo = UserData::Get()->GetUserInfo(GameManager::Get()->getHero()->GetID());
		if(info->battleSide % 2 == pHeroInfo->battleSide % 2)
		{
			isHarmful = false;
		}
	}

	GameManager::Get()->GetSceneLayer()->getMainMenuLayer()->HandleDamageNumberEffect(this, blood, isCrit, isHarmful);

	playBecomeRedEffect();
	
		unsigned int soundID = 321013;
		switch(getType())
		{
		case kTypeFighter_Boy:
		case kTypeFighter_Girl:
			//skillID = 4011101;	// 战士
			break;
		case kTypeMagician_Girl:
		case kTypeMagician_Boy:
			soundID = 323004;	// 法师
			break;
		case kTypeAssassin_Boy:
		case kTypeAssassin_Girl:
			//skillID = 4051101;	// 刺客
			break;
		default:
			break;
		}
	
    if(attackedSoundCDTime == 0)
    {
        GameAudioManager::sharedManager()->playEffect(soundID, false);
        attackedSoundCDTime = 0.5f;
    }
	

}

bool SpriteSeer::MoveToByJoystick(float dt)
{
	float speed = GetMoveSpeed();

	CCPoint velocity = HSJoystick::sharedJoystick()->getVelocity();
	if(velocity.x == 0 && velocity.y == 0)
	{
		m_isMoving = false;		
		updateWaitAnim();
		return false;
	}
	m_isMoving = true;
	float dx = speed * velocity.x * dt ;
	float dy = speed * velocity.y * dt ;

	CCPoint curPos = this->getPosition();
	CCPoint newPos = ccpAdd(curPos, ccp(dx,dy));

	updateDirection(newPos);
	updateRunAnim();

	//m_map = GameManager::Get()->GetSceneLayer()->getLevelLayer()->getPhysicsLayer();	
	if(m_map && m_map->isPointReachable(newPos))
	{
		this->setPosition(newPos);
	}
	else if(m_map && m_map->isPointReachable(ccpAdd(curPos, ccp(dx,0))))
	{
		this->setPosition(ccpAdd(curPos, ccp(dx,0)));
	}
	else if(m_map && m_map->isPointReachable(ccpAdd(curPos, ccp(0,dy))))
	{
		this->setPosition(ccpAdd(curPos, ccp(0,dy)));
	}	

	return true;
}


bool SpriteSeer::moveByJoystick( float dt )
{
	if (m_eMoveType == MOVE_BY_JOY)
	{
		moveToTarget(getPosition(), getPosition());
	}
	
	if (m_pStateMachine->CheckStateRuning(ToNormalAttack) ||
		m_pStateMachine->CheckStateRuning(ToLinkTime))
	{
		return false;
	}

	BattleUILayer* battleUI = GetBattleUILayer();
	if (battleUI && battleUI->getNormalAttackBtn()->isSelected())
	{
		return false;
	}

	if(BoneSpriteMoveable::moveByJoystick(dt))
	{
		return true;
	}
	else
	{
		if (m_pStateMachine->CheckStateRuning(ToRun))
		{
			
			FState* pState = m_pStateMachine->GetState(ToRun);
			if(pState)
				m_pStateMachine->Remove(pState);

			if(m_pStateMachine->CheckStateRuning(ToIdle))
			{
				m_pStateMachine->Remove(m_pStateMachine->GetState(ToIdle));
			}
			m_pStateMachine->Push(m_pStateFactory->Create(ToIdle, 0));
		}

		return false;
	}

	return false;
	
}

void SpriteSeer::DoRun( void )
{
	CCPoint velocity = HSJoystick::sharedJoystick()->getVelocity();
	if(velocity.x == 0 && velocity.y == 0)
	{
		return;
	}

	BattleUILayer* battleUI = GetBattleUILayer();
	if (battleUI && battleUI->getNormalAttackBtn()->isSelected())
	{
		return;
	}

	if(m_pStateMachine->CheckStateRuning(ToIdle))
	{
		if (canMove)
		{
			m_pStateMachine->Remove(ToRun);
			m_pStateMachine->Remove(ToIdle);
			m_pStateMachine->Push(m_pStateFactory->Create(ToRun, 0));
		}
	}
	
}

void SpriteSeer::startPathFinding()
{
	if (!m_pStateMachine->CheckStateRuning(ToRun) && m_pStateMachine->CheckStateRuning(ToIdle))
	{
		m_pStateMachine->Remove(ToIdle);
		m_pStateMachine->Push(m_pStateFactory->Create(ToRun, 0));
	}
}

void SpriteSeer::endPathFinding()
{
	if(m_pStateMachine->CheckStateRuning(ToRun))
	{
		m_pStateMachine->Remove(ToRun);
		m_pStateMachine->Push(m_pStateFactory->Create(ToIdle, 0));
	}
}

void SpriteSeer::startAutoAttack()
{
	if (autoAttack)
	{
		return;
	}
	autoAttack = true;
	m_eMoveType = MOVE_BY_MOUSE;
}

void SpriteSeer::endAutoAttack()
{
	if (!autoAttack)
	{
		return;
	}
	autoAttack = false;
	m_eMoveType = GameDataManager::Get()->getHeroMoveType();
	
	this->moveToTarget(getPosition(), getPosition());
}

void SpriteSeer::moveToMonster()
{	
	SpriteMonster * monster = SpriteMonsterMgr::Get()->getNearestMonster();
	SkillDispMgr * skillMgr = SkillDispMgr::Get();

	int skillId = getBestSkill();
	if (skillId)
	{
		for (size_t i = 0; i < skills.size(); i++)
		{
			if (skillId == skills[i])
			{
				skills.erase(skills.begin() + i);
				skills.push_back(skillId);
				break;
			}
		}

		if (skillMgr->GetSkillInfo(skillId)->type != ToNormalAttack)
		{
			CCPoint vec = ccpSub(monster->getPosition(), this->getPosition());
			vec = ccpNormalize(vec);
			setDirection(vec);
			if(!DoSkillAttack(skillId))
			{
				if (monster)
				{
					if( canMove )
						this->moveToTarget(monster->getPosition(), this->getPosition());
				}
			}
		}
		else
		{
			CCPoint vec = ccpSub(monster->getPosition(), this->getPosition());
			vec = ccpNormalize(vec);
			setDirection(vec);
			DoNormalAttack();
		}
	}
	else if (monster)
	{
		CCPoint pt = monster->getPosition();
		CCPoint pixPos = this->getPosition();
		if (m_map->isPointReachable(pt))
		{
			this->moveToTarget(pt, pixPos);
		}
		else
		{
			CCPoint vec = ccpNormalize(ccpSub(pt, pixPos));
			do
			{
				pt = ccpSub(pt, vec);
			} while (!m_map->isPointReachable(pt));
			this->moveToTarget(pt, pixPos);
		}
	}
	else
	{	
		CCPoint portalPos = InstanceManager::Get()->getPortalPosition();
		if (portalPos.x != 0 || portalPos.y !=0)
		{
			moveToPortal();
		}	
	}

	return;

}

int SpriteSeer::getBestSkill()
{
	int skillId = 0;
	int normalAttackId = 0;
	bool canDoSkill = false;

	//无怪物时不释放技能
	SpriteMonster * monster = SpriteMonsterMgr::Get()->getNearestMonster();	
	if (!monster)
	{
		return skillId;
	}

	//循环遍历确定是否有技能正在释放
	SkillDispMgr * skillMgr = SkillDispMgr::Get();

	bool doingSkill = false;
	for (size_t i = 0; i < skills.size(); i++)
	{
		const SKILL_INFO * info = skillMgr->GetSkillInfo(skills[i]);
		if (m_pStateMachine->CheckStateRuning(info->type))
		{
			doingSkill = true;
			break;
		}
	}

	//从头遍历可以释放的技能
	for (size_t i = 0; i < skills.size(); i++)
	{
		const SKILL_INFO * info = skillMgr->GetSkillInfo(skills[i]);
		
		//找出普通攻击id
		if (info->type == ToNormalAttack)
		{
			normalAttackId = skills[i];
			continue;
		}

		//未释放技能时才检测技能cd及距离
		if (!doingSkill)
		{
			bool isUnlock = skillMgr->IsEquipSkill(skills[i]);

			if (skillMgr->IsCD(GetID(), skills[i]) || !isUnlock)
			{
				continue;
			}		

			if (ccpDistance(this->getPosition(), monster->getPosition()) < info->longDistanceAttackRange)
			{
				canDoSkill = true;
				skillId = skills[i];
			
				break;
			}
		}		
	}



	//普通攻击
	if (!canDoSkill && normalAttackId)
	{
		const SKILL_INFO * info = skillMgr->GetSkillInfo(normalAttackId);		
		if (ccpDistance(this->getPosition(), monster->getPosition()) < info->longDistanceAttackRange)
		{
			skillId = normalAttackId;
		}
	}


	return skillId;
}

void SpriteSeer::moveToPortal()
{
	CCPoint portalPos = InstanceManager::Get()->getPortalPosition();
	if (portalPos.x == 0 && portalPos.y ==0)
	{
		moveToTarget(getPosition(), getPosition());
		return;
	}
	SEL_CallFunc cfActivePortal = callfunc_selector(SpriteSeer::activePortal);
	this->moveToTarget(portalPos, this->getPosition(), this, cfActivePortal);
}

void SpriteSeer::activePortal()
{
	int instanceId = InstanceManager::Get()->getCurInstanceId();
	int portalId = InstanceManager::Get()->getPortalId();

	//ASSERT(instanceId != 0, "SpriteSeer: Instance Id not init yet.");
	//ASSERT(portalId != 0, "SpriteSeer: Portal Id not init yet.");
	if (instanceId != 0 && portalId != 0)
	{
		XLogicManager::sharedManager()->createBattle(instanceId,portalId);
	}
}

float SpriteSeer::GetCurAnimTotalTime( void )
{
	return SkeletonAnimRcsManager::getInstance()->getOneAnimationDuration(m_TypeID, GetAnimID());
}

cocos2d::CCPoint SpriteSeer::GetJoystickVelocity( void )
{
	return HSJoystick::sharedJoystick()->getVelocity();
}

void SpriteSeer::setPosition( const CCPoint &position )
{
	BoneSpriteMoveable::setPosition(position);
}

void SpriteSeer::setLastPosition(CCPoint pt)
{
	m_ptLastServerPosition = pt;
}

CCPoint SpriteSeer::getLastPosition()
{
	return m_ptLastServerPosition;
}

void SpriteSeer::stopAllActions( void )
{
	BoneSpriteMoveable::stopAllActions();
	m_rootSprite->stopAllActions();
	if(m_pStateMachine)
	{
		m_pStateMachine->Remove(ToVariableSpeedMoveToHandler);
	}
}

CPhysicsLayer* SpriteSeer::createSearchLayer()
{
	if (GameManager::Get()->GetSceneLayer())
	{
		CPhysicsLayer* layer = new CPhysicsLayer();
		int id = GameManager::Get()->GetSceneLayer()->getCurMapId();
		BBYTE * file = (unsigned char*)MapDataManager::sharedManager()->getMapFileByMapID(id);

		int cellW = 0;
		memcpy(&cellW, file, sizeof(int));
		file += sizeof(int);
		int row = 0;
		memcpy(&row, file, sizeof(int));
		file += sizeof(int);
		int col = 0;
		memcpy(&col, file, sizeof(int));
		file += sizeof(int);

		layer->init(file, row, col, cellW, cellW);
		return layer;
	}else
	{
		return NULL;
	}
}

void SpriteSeer::moveToCityPosition(int cityId, CCPoint position,int npcId /* = -1 */)
{
	if (!MainLandManager::Get()->isMainLand(cityId))
	{
		return;
	}

	if (MainLandManager::Get()->getCurCityId() == cityId)
	{
		//在当前主城
		if (npcId == -1)
		{
			moveToTarget(position, getPosition());
		}
		else
		{
			// Note: 获取当前的Npc
			SpriteNPC* pNpc = BoneNPCManager::getInstance()->GetOneNpc(npcId);
			CCPoint targetPos = position;
			pNpc->MoveToTarget(targetPos,pNpc->getRelativeParentColliderRect());
		}		

		TaskPosition taskPos;
		taskPos.cityId = 0;
		taskPos.npcId = 0;
		taskPos.position = ccp(0, 0);
		GameDataManager::Get()->setTaskPosition(taskPos);
	}
	else
	{
		//其他主城
		TaskPosition taskPos;
		taskPos.cityId = cityId;
		taskPos.position = position;
		taskPos.npcId = npcId;
		GameDataManager::Get()->setTaskPosition(taskPos);
		CityListLayer * layer = GetCityListLayer();
		if (layer)
		{
			layer->openCityList();
			layer->moveToCity(cityId, 0.5f);
		}
	}
}

void SpriteSeer::resetNameLabelColor(const ccColor3B& color)
{
	if(m_nameLabel)
	{
		m_nameLabel->setColor(color);
	}
}