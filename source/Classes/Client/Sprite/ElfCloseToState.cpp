#include "ElfCloseToState.h"
#include "SpriteElfManager.h"
#include "SpriteElfConfigFromLua.h"

ElfCloseToState::ElfCloseToState(BaseElfEvt *pEvt) : ElfBaseState(pEvt)
{
	m_Type = ToElfCloseTo;
	
	m_fMoveSpeed = 0;
	m_fGoTime = 0;	
	m_accelateRate = 0;
	m_maxSpeed = 0;
	m_followPointType = 0;
	m_isMoveEnd = false;
	m_accTotalTime = SpriteElfConfigFromLuaManager::getInstance()->GetTotalAccTimer();
	m_outerCircleRadius = SpriteElfConfigFromLuaManager::getInstance()->GetOuterCircleRadius();
	m_startSpeedCoefficient = SpriteElfConfigFromLuaManager::getInstance()->GetStartSpeedCoefficient();
}

ElfCloseToState::~ElfCloseToState( void )
{
}

bool ElfCloseToState::Entered()
{
	ElfBaseState::Entered();
	//CCLog("ElfCloseToState::Entered()----------------------------------");

	m_fMoveSpeed = 0;
	m_fGoTime = 0;
	m_maxSpeed = m_pRole->GetMoveSpeed();
	m_accelateRate = m_maxSpeed*(1-m_startSpeedCoefficient)/m_accTotalTime;
	m_isMoveEnd = false;

	if (m_pAttachData && m_pAttachData->bStartWithAcc)
	{
		m_fGoTime = m_accTotalTime;
	}

	// Note: 计算精灵的跟随点类型
	m_followPointType = GetFollowPointType(m_actionId,true);

	return true;
}

void ElfCloseToState::Exited()
{
	ElfBaseState::Exited();
	//CCLog("ElfCloseToState::Exited()----------------------------------");
}

void ElfCloseToState::Update(float dt)
{
	ElfBaseState::Update(dt);

	if (m_isMoveEnd)
	{
		return ;
	}

	unsigned int roleActionId = m_pRole->GetAnimID();
	unsigned int followPointType = GetFollowPointType(roleActionId);
	if (followPointType != -1)
	{
		if (followPointType != m_followPointType)
		{
			m_followPointType = followPointType;
			Reset();
			return ;
		}
	}

	if (m_fGoTime < m_accTotalTime)
	{
		CCPoint elfPos = m_pElf->getPosition();
		m_fGoTime += dt;
		m_fMoveSpeed = m_fGoTime * m_accelateRate + m_maxSpeed*m_startSpeedCoefficient;
		if (m_fMoveSpeed >= m_maxSpeed)
		{
			m_fMoveSpeed = m_maxSpeed;
		}
	}
	else
	{
		m_fMoveSpeed = m_maxSpeed;
	}

	CCPoint targetPoint = GetCloseToHeroPoint(m_followPointType);
	CCPoint elfPos = m_pElf->getPosition();

	CCPoint dir = ccpSub(targetPoint, elfPos);
	float dirLength = sqrt(ccpLengthSQ(dir));
	if (IsInOuterCircle(dirLength))
	{
		SpriteElfManager::Get()->PushOneElfChaseState(m_pRole,0);
		return ;
	}

	unsigned int animId = m_pRole->GetAnimID();
	if (animId == kTypeIdle_FaceHor_Stand_MAIN ||
		animId == kTypeIdle_FaceHor_Stand_OTH ||
		animId == kTypeIdle_FaceDown_Stand_MAIN ||
		animId == kTypeIdle_FaceDown_Stand_OTH ||
		animId == kTypeIdle_FaceUp_Stand_MAIN ||
		animId == kTypeIdle_FaceUp_Stand_OTH
		)
	{
		if(dirLength <= 1)
		{
			bool bFlip = false;
			unsigned int roleActionId = m_pRole->GetAnimID();
			unsigned int animDirectionId = GetAnimDirection(roleActionId);
			unsigned int animID = GetAnimId(animDirectionId,bFlip);

			m_pElf->SetAnim(animID,0);
			m_pElf->SetAnimFlipX(bFlip);
			m_isMoveEnd = true;

			return ;
		}
	}

	if(dir.x != 0 || dir.y != 0)
	{
		dir = ccpNormalize(dir);
	}
	else
	{
		return ;
	}

	float speed = m_fMoveSpeed;

	float newPosX = elfPos.x + dt*speed*dir.x;
	float newPosY = elfPos.y + dt*speed*dir.y;

	// Note: 修复位置误差
	CCPoint newElfTempPos(newPosX,newPosY);
	CCPoint elfToTargetDir = ccpNormalize(ccpSub(targetPoint,elfPos));
	CCPoint newPosToTargetDir = ccpNormalize(ccpSub(targetPoint,newElfTempPos));
	if (elfToTargetDir.x * newPosToTargetDir.x <0 
		|| elfToTargetDir.y * newPosToTargetDir.y <0 )
	{
		m_pElf->setPosition(targetPoint);
		return ;
	}


	m_pElf->setPosition(ccp(newPosX,newPosY));

	// Note: 更新方向
	bool bFlip = false;
	unsigned int animDirectionId = GetAnimDirection(dir);
	unsigned int animID = GetAnimId(animDirectionId,bFlip);
	if (animID != m_tempAnimDirection)
	{
		m_pElf->SetAnim(animID,0);
		m_pElf->SetAnimFlipX(bFlip);

		m_tempAnimDirection = animID;
		m_isFlip = bFlip;
	}
	else if(bFlip != m_isFlip)
	{
		m_pElf->SetAnimFlipX(bFlip);
		m_isFlip = bFlip;
	}
}

void ElfCloseToState::Reset()
{
	ElfBaseState::Reset();

	m_fGoTime = 0;
	m_isMoveEnd = false;
}

bool ElfCloseToState::IsInOuterCircle(float distance)
{
	if (distance >= m_outerCircleRadius)
	{
		return true;
	}
	return false;
}