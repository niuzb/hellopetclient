/************************************************************************/
/* 精灵类，负责精灵的创建，移动 动作播放的管理							*/
/************************************************************************/
#pragma once

#include "BoneSpriteMoveable.h"
#include "SpriteSeer.h"
#include "FAbstractTransition.h"
#include "BaseAttackState.h"

class SkillStateMachine;
class ElfStateFactory;
class BaseElfAttachData;

class SpriteElf : public BoneSpriteMoveable
{
	friend class ElfChaseState;
	friend class ElfCloseToState;
	friend class ElfSkillAttackState;
	friend class ElfBaseState;
public:
    SpriteElf();
	virtual ~SpriteElf(); 

	/**
	* Instruction : Call by SpriteElfManager pre frame
	* @param 
	*/	
	void Update(float fTime);
    
    /**
     * Instruction : Init SpriteElf 只负责显示
     * @param
     */
	virtual bool  initWithId(int typeId);

	/**
	* Instruction : 
	* @param 
	*/
	void AttachToOneHero(SpriteSeer* hero);

	SpriteSeer* GetAttackedHero(void){return attachedHero;}

	/**
	* Instruction : init state machine
	* @param 
	*/	
	virtual void InitStateMachine();
	/**
	* Instruction : shut down state machine
	* @param 
	*/	
	virtual void ShutDownStateMachine();

	/**
	* Instruction : 插入一个追逐状态
	* @param 
	*/
	void PushOneElfChaseState(SpriteSeer* pHero,int skillId,BaseElfAttachData* pData = 0);

	/**
	* Instruction : 插入一个靠近状态
	* @param 
	*/
	void PushOneElfCloseToState(SpriteSeer* pHero,int skillId,BaseElfAttachData* pData = 0);

	/**
	* Instruction : 插入一个攻击状态
	* @param 
	*/
	void PushOneElfAttackState(SpriteSeer* pHero,int skillId,BaseElfAttachData* pData = 0);

	bool DoSkillAttack( unsigned int skillId, const CCPoint& rolePos, const CCPoint& roleDir, const CCPoint& aimDir, const CCPoint& monsterPos, bool bAnimMonster );
	
protected:
	bool IsElfStartMove(SpriteSeer* pHero,CCPoint &targetPoint);
	void ElfMoveToTarget();
	CCPoint GetMoveTargetPos(bool bRight);
protected:
	SpriteSeer* attachedHero;
	// Note: 状态机相关
	SkillStateMachine* m_pStateMachine;
	ElfStateFactory* m_pStateFactory;
private:
	CCPoint elfTempPos;
	CCPoint targetPos;
	CCPoint relativePosToHero;
	bool isStartMove;
};
