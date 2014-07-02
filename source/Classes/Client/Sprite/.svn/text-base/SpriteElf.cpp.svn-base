#include "SpriteElf.h"
#include "EnginePlayerManager.h"
#include "SpriteElfManager.h"
#include "LevelLayer.h"
#include "LevelManager.h"
#include "ElfChaseState.h"
#include "ElfCloseToState.h"
#include "ElfSkillAttackState.h"
#include "MainLandManager.h"
#include "SkillDispMgr.h"

SpriteElf::~SpriteElf()
{
	ShutDownStateMachine();

	delete m_pStateMachine;
	m_pStateMachine = NULL;

	if(m_pStateFactory)
	{
		delete m_pStateFactory;
		m_pStateFactory = NULL;
	}
}

SpriteElf::SpriteElf()
	:BoneSpriteMoveable(0, 0)
{
	attachedHero = 0;
	elfTempPos = CCPointZero;
	isStartMove = false;
	relativePosToHero = CCPointZero;
	targetPos = CCPointZero;

	m_pStateMachine = new SkillStateMachine(); 
	m_pStateFactory = new ElfStateFactory(this);
}

void SpriteElf::InitStateMachine()
{
	/*if(!m_pStateMachine->CheckStateRuning(ToElfCloseTo))
		m_pStateMachine->Push(m_pStateFactory->Create(ToElfCloseTo,0, 0));*/
}

void SpriteElf::ShutDownStateMachine()
{
	//m_pStateMachine->RemoveAllState();
}

bool SpriteElf::initWithId(int typeId)
{
	m_TypeID = typeId;

	m_animBone =  EnginePlayerManager::getInstance()->addBoneAnimSprite(typeId);
	if (m_animBone == 0)
	{
		return false;
	}
	attachBoneAnimToRootSprite(1);

	// init state machine
	InitStateMachine();

	return true;
}

void SpriteElf::Update(float fTime)
{
	if (m_pStateMachine)
	{
		m_pStateMachine->Update(fTime);
	}
}

void SpriteElf::ElfMoveToTarget()
{
	isStartMove = false;
	elfTempPos = targetPos;
}

bool SpriteElf::IsElfStartMove(SpriteSeer* pHero,CCPoint &targetPoint)
{
	if (pHero == 0)
	{
		return false;
	}
	targetPoint = GetMoveTargetPos(pHero->IsAnimFlipX());
	CCPoint disPos = ccpSub(targetPoint,elfTempPos);
	float distance = 4;
	if(ccpLengthSQ(disPos) >= distance)
	{
		return true;
	}
	return false;
}

CCPoint SpriteElf::GetMoveTargetPos(bool bRight)
{
	if (attachedHero == 0)
	{
		return CCPointZero;
	}
	CCPoint distPoint = relativePosToHero;
	if (false == bRight)
	{
		distPoint.x = -distPoint.x;
	}
	return ccpAdd(attachedHero->getPosition(),distPoint);
}

void SpriteElf::AttachToOneHero(SpriteSeer* hero)
{
	attachedHero = hero;

	this->m_name = hero->m_name;

	// Note: Add To Obj Layer
	LevelLayer* pLayer = LevelManager::sShareInstance()->getCurrentLevelLayer();
	if (pLayer)
	{
		CCNode* pObjLayer = pLayer->getObjectLayer();
		if (pObjLayer)
		{
			// Note: 设置精灵的起始位置
			relativePosToHero = ccpAdd(attachedHero->getAttachPoint(kType_PLAYER_NAME),SpriteElfManager::s_fixDistanceToHero);
			elfTempPos = GetMoveTargetPos(true);
			this->setPosition(elfTempPos);

			pObjLayer->addChild(this,MAP_Z_OBJ_TOP);
			this->SetAnim(kTypeIdle_FaceDown_Stand_OTH,1);
			//this->getRoot()->setScale(0.5);
			
			PushOneElfCloseToState(attachedHero, 0, new BaseElfAttachData());
		}
	}
}


void SpriteElf::PushOneElfChaseState(SpriteSeer* pHero,int skillId,BaseElfAttachData* pData /* = 0 */)
{
	float goTime = 0;
	if (m_pStateMachine->CheckStateRuning(ToElfChase))
	{
		m_pStateMachine->Remove(m_pStateMachine->GetState(ToElfChase));
	}
	if (m_pStateMachine->CheckStateRuning(ToElfSkillAttack))
	{
		m_pStateMachine->Remove(m_pStateMachine->GetState(ToElfSkillAttack));
	}
	if (m_pStateMachine->CheckStateRuning(ToElfCloseTo))
	{
		ElfCloseToState* pCloseToState = (ElfCloseToState*)m_pStateMachine->GetState(ToElfCloseTo);
		m_pStateMachine->Remove((FState*)pCloseToState);
	}
	ElfChaseState* pChaseState = (ElfChaseState*)m_pStateFactory->Create(ToElfChase, pHero,skillId,pData);
	m_pStateMachine->Push((FState*)pChaseState);
}

void SpriteElf::PushOneElfCloseToState(SpriteSeer* pHero,int skillId,BaseElfAttachData* pData /* = 0 */)
{
	if (m_pStateMachine->CheckStateRuning(ToElfChase))
	{
		m_pStateMachine->Remove(ToElfChase);
	}
	if (m_pStateMachine->CheckStateRuning(ToElfCloseTo))
	{
		m_pStateMachine->Remove(ToElfCloseTo);
	}

	if(!m_pStateMachine->CheckStateRuning(ToElfSkillAttack))
		m_pStateMachine->Push(m_pStateFactory->Create(ToElfCloseTo, pHero,skillId,pData));
	
	if(!MainLandManager::Get()->isMainLand(LevelManager::sShareInstance()->getCurMapId()))
	{
		if(!m_pStateMachine->CheckStateRuning(ToElfAttackTrigger))
			m_pStateMachine->Push(m_pStateFactory->Create(ToElfAttackTrigger, pHero, SkillDispMgr::Get()->GetFairySkillID(GetTypeId()), pData));
	}
}

void SpriteElf::PushOneElfAttackState(SpriteSeer* pHero,int skillId,BaseElfAttachData* pData /* = 0 */)
{
	if (m_pStateMachine->CheckStateRuning(ToElfCloseTo))
	{
		m_pStateMachine->Remove(ToElfCloseTo);
	}
	if (m_pStateMachine->CheckStateRuning(ToElfChase))
	{
		m_pStateMachine->Remove(ToElfChase);
	}
	if (m_pStateMachine->CheckStateRuning(ToElfSkillAttack))
	{
		m_pStateMachine->Remove(ToElfSkillAttack);
	}
	m_pStateMachine->Push(m_pStateFactory->Create(ToElfSkillAttack, pHero,skillId,pData));
}

bool SpriteElf::DoSkillAttack( unsigned int skillId, const CCPoint& rolePos, const CCPoint& roleDir, const CCPoint& aimDir, const CCPoint& monsterPos, bool bAnimMonster )
{
	m_pStateMachine->Remove(ToElfSkillAttack);

	const FAIRY_SKILL_INFO* pSkillInfo = SkillDispMgr::Get()->GetFairySkillInfo(skillId);
	if(pSkillInfo == NULL)
	{
		ASSERT(false, "Can't find elf skill!!!");
		return false;
	}

	FState* pState = m_pStateFactory->Create(ToElfSkillAttack, attachedHero, skillId, NULL);
	StateContainer* pContainer = dynamic_cast<StateContainer*>(pState);
	if(pContainer)
	{
		SkillBeginReceiverHandler* pRecevier = new SkillBeginReceiverHandler( new BaseAttackEvt( attachedHero, skillId ) );;
		if(pRecevier)
		{
			pRecevier->SetAimMonster(bAnimMonster);
			pRecevier->SetDirection(aimDir);
			pRecevier->SetNearestMonsterPos(monsterPos);
			pRecevier->SetRolePos(rolePos);
			pRecevier->SetRoleDirection(roleDir);

			pContainer->Push(pRecevier);

		}
	}
	m_pStateMachine->Push(pState);

	return true;
}
