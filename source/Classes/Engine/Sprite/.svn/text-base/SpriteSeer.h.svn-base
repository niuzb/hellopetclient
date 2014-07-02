#ifndef ISEER_SPRITE_SEER_H
#define ISEER_SPRITE_SEER_H

#include "BoneSpriteMoveable.h"
#include "FAbstractTransition.h"
#include "SpriteMonster.h"
#include "UILabelTTF.h"
class SkillStateMachine;
class StateFactory;

class SpriteSeer : public BoneSpriteMoveable
{
	friend class IdleState;
	friend class RunState;
	friend class NormalAttackState;
	friend class LinkTimeState;
	friend class PvAIManager;

public:    
    virtual ~SpriteSeer(); 
    
	static  SpriteSeer*		seerWithID(int s_id,const char *name, int type, bool isPlayerSet,bool isCreateEffect = true);
    
	virtual void setPosition(const CCPoint &position);

	virtual bool	moveByJoystick(float dt);
	/// do skill 
	virtual bool	DoNormalAttack(void);
	virtual bool	DoNormalAttack(unsigned int skillId);
	void SetCanNormalAttack(bool bAttack){ m_bNormalAttack = bAttack;}
	virtual bool	DoSkillAttack(unsigned int skillId);
	int GetNormalAttackNum(){return m_nNormalAttackNum;}
	virtual void    ByAttacked(unsigned int blood, bool isCrit = false);
	/// called by LevelLayer
	void Update(float fTime);

	bool tellIsAttackEnable();

	void DoRun(void);

	void startPathFinding();
	void endPathFinding();

	//自动攻击
	void startAutoAttack();
	void endAutoAttack();

	void moveToMonster();

	void moveToPortal();
	void activePortal();

	int getBestSkill();

	bool isAutoAttacking(){return autoAttack;}

	//跨地图寻路
	void moveToCityPosition(int cityId, CCPoint position,int npcId = -1);
	
	// return s
	float GetCurAnimTotalTime(void);

	virtual CCPoint GetJoystickVelocity(void);

	void setLastPosition(CCPoint pt);
	CCPoint getLastPosition();

	float GetAcceleration(void){return m_acceleration;}
	void SetAcceleratiion(float acc){m_acceleration = acc;}

	void stopAllActions(void);

	unsigned int GetBattleSide(void){return m_battleSide;}
	void SetBattleSide(unsigned int side){m_battleSide = side;}

	void PauseStateMachine();
	void ResumeStateMachine();

	void resetNameLabelColor(const ccColor3B& color); 
protected:

    SpriteSeer(int type, bool isPlayerSet);
    
	//init
    virtual bool  initWithId(int index,int typeId,const char *name,bool isCreateEffect);
	
    //actions
    virtual void	startMove();
    virtual void	endMove();

	virtual void beginAStarSearch();
	virtual void endAStarSearch();

	/// init state machine
	virtual void InitStateMachine();
	/// shut down state machine
	virtual void ShutDownStateMachine();

	bool MoveToByJoystick(float dt);

	CPhysicsLayer* createSearchLayer();

protected:
	SkillStateMachine	* m_pStateMachine;
	StateFactory* m_pStateFactory;

	int m_nNormalAttackNum;
	bool m_bNormalAttack;

	bool autoAttack;
	float autoAttackCDTime;
    float attackedSoundCDTime;
	std::vector<int> skills;

	CCPoint m_ptLastServerPosition;

	float m_acceleration;

	unsigned int m_battleSide;
	bool m_stateMachineRunning;

	bool posInited;

	//检测是否在传送点附近并激活传送点
	CCPoint portalPosition;
	float portalCheckCDTime;
	TXGUI::UILabelTTF* m_nameLabel;
};

#endif
