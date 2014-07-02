#ifndef SPRITE_MONSTER_H
#define SPRITE_MONSTER_H

#include "BoneSpriteMoveable.h"
#include "FAbstractTransition.h"
#include "simplefsm.h"

//using namespace cocos2d;
#define SHADOW_TAG 10001
#define ELITE_TAG  10002

enum MonsterType
{
	MONSTER_TYPE_QIUQIU      = 10001,
	MONSTER_TYPE_YEZHU       = 10002,
	MONSTER_TYPE_QINGWA      = 10003,
	MONSTER_TYPE_XIAOHUAYAO  = 10004,
	MONSTER_TYPE_ZHIZHU      = 10007,
	MONSTER_TYPE_DAOLONG     = 10012,
	MONSTER_TYPE_RENMA       = 10020,
	MONSTER_TYPE_FENGYUANSU  = 10021,
	MONSTER_TYPE_JIQIANGBING = 10023,
	MONSTER_TYPE_TIEQIU      = 10024,
	MONSTER_TYPE_HAOZHU      = 19001,
	MONSTER_TYPE_HUAYAO      = 19002,
	MONSTER_TYPE_UNKNOWN,
};

enum MONSTER_STATE
{
	MONSTER_STATE_INITIALIZE,
	MONSTER_STATE_IDLE,
	MONSTER_STATE_RUN,
	MONSTER_STATE_ATTACK,
	MONSTER_STATE_HURT,
	MONSTER_STATE_DEAD,
};

typedef struct MonsterInitInfo
{
	int uid;
	const char * monsterName;
	int typeId;
	int totalHp;
	CCPoint pos;
	float speed;
	bool isBoss;
	bool isElite;
}MonsterInitInfo;

typedef struct SkillInfo
{
	unsigned int effectId;
	CCPoint startPosition;
	CCPoint endPosition;
	float speed;
	float delayTime;
}SkillInfo;

class SpriteMonster : public BoneSpriteMoveable
{
	friend class SpriteMonsterMgr;
public:   
	virtual ~SpriteMonster(); 
	//状态机
	struct Rule:public SimpleStateMachine
	{
		Rule(){_this = NULL;}
		SpriteMonster * _this;
	protected:
		virtual bool States(StateMachineEvent event, int state);
	}fsm_rule;

	//操作函数
	void moveByPoints(const std::vector<CCPoint>& points);
	CCPoint moveToPoint(CCPoint desPoint,float speed);
	
	//回调函数
	void ccCallChangeDirection(CCNode * node, void * data);
	void ccCallChangeState(CCNode * node, void * data);
	virtual void ccCallShowEffect(CCNode * node, void * data);
	virtual void ccCallHideEffect(CCNode * node, void * data);

	void changeDirection(CCPoint direct);

	//血量控制
	unsigned int getBlood(){return this->blood;}
	void setBlood(unsigned int blood){this->blood = blood;}
	unsigned int getTotalBlood(){return this->m_TotalHp;}

	//事件处理
	virtual void onEventMsgMove(const std::vector<CCPoint>& points);
	virtual void onEventMsgAttack(CCPoint serverPos, CCPoint direction, int animId, SkillInfo info);
	virtual void onEventMsgDead();
	virtual CCPoint onEventAttacked(CCPoint desPoint);

	//辅助函数
	DIRECTION_MONSTER pointToDirection(CCPoint direct);	
	virtual void Update(float fTime,bool &bDeleteSelf);
	virtual void PlayAttackedEffect(bool isCrit);
	virtual void animationHandler(const char* _aniType, const char* _aniID, const char* _frameID);
	
protected:

    SpriteMonster(MonsterInitInfo info);    
    
	//init
    virtual bool    initWithId(unsigned int index,const char *name, unsigned int typeId);

protected:
	void removeSelf();

	virtual void setAttackAnimation(int animId, DIRECTION_MONSTER direction);
	void setAnimFromStateAndDirection(MONSTER_STATE state, DIRECTION_MONSTER direction);
	void setAnimFromStateAndDirection(int state, DIRECTION_MONSTER direction);

	float speed;

	unsigned int blood;

	DIRECTION_MONSTER direction;

	CCPoint m_oldPos;

	unsigned int m_TotalHp;

	bool isBoss;
	bool isElite;

	float totalScheduleTimer;
	float selfScheduleTimer;

	//提供给ccCallFunc的参数
	int mtpState;
	int mbpState1;
	int mbpState2;
	CCPoint mbpDir1;
	CCPoint mbpDir2;
	CCPoint mbpDir3;

	//额外的攻击动画，用于攻击完成后切换回idle状态
	std::vector<int> extraAnims;	
	EffectSprite* m_attackedEffectSprite;

	int lastAnimId;
	bool lastFlip;

	bool showAnim;
};


#endif
