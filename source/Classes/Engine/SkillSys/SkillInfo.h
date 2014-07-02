// TAOMEE GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Taomee Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 2012-2015 Taomee Game Technologies. 
//      All Rights Reserved.
//
// Taomee Game Technologies, Shanghai, China
// http://www.taomee.com
//
#pragma once
#include <map>
#include <string>
#include "PhysicsLayer.h"
#include "StateEventType.h"
#include "SASpriteDefine.h"
#include "UserData.h"

typedef enum Skill_Phase
{
	PHASE_UNKNOWN	= -1,
	PHASE_PERFORM	= 1,
	PHASE_SHOW	= 2,
	PHASE_IMPACT= 3,
} SKILL_PHASE;


typedef enum Spell_Show_Type	
{
	SHOW_IMMEDIATE,     // 在目标处瞬间出现
	SHOW_FLYINGTO,      // 从施法者飞向目标者
	SHOW_CONTINUOUS,    // 连续类表现
} SPELL_SHOW_TYPE;


typedef struct tagDispData
{
	/// sound 
	unsigned int SoundId;
	/// effect Id
	unsigned int EffectId;
}DISP_DATA, *LPDISP_DATA;
typedef const DISP_DATA*   LPCDISP_DATA;


typedef struct tagPerform_Phase
{
	float       fTotalTime;
	DISP_DATA   DispData;

	tagPerform_Phase()
	{
		fTotalTime  = 0.0f;
	}

	~tagPerform_Phase() {};
} PERFORM_PHASE, *LPPERFORM_PHASE;
typedef const PERFORM_PHASE*   LPCPERFORM_PHASE;



typedef struct tagShow_Phase
{
	// Public data
	SPELL_SHOW_TYPE emShowType;
	unsigned int    SoundId;

	// Immediate show data
	unsigned int  CasterEffectId;
	unsigned int  CasterEffectPos;
	unsigned int  TargetEffectId;

	int  TargetEffectPos;

	// Flying show data
	unsigned int    FlyingEffectId;
	int  StartPos;
	int  TargetPos;
	float   fFlyingSpeed;

	tagShow_Phase()
	{
		emShowType  = SHOW_IMMEDIATE;
		SoundId  = 0;

		FlyingEffectId = 0;
		fFlyingSpeed = 0.0f;

		CasterEffectId = 0;
		TargetEffectId = 0;

		StartPos = 0;
		TargetPos = 0;
	}
} SHOW_PHASE, *LPSHOW_PHASE;
typedef const SHOW_PHASE*   LPCSHOW_PHASE;


typedef struct tagImpact_Phase
{
	float       fTotalTime;
	DISP_DATA   DispData;
	unsigned   int  ABoxAnimationId;

	tagImpact_Phase()
	{
		fTotalTime  = 0.0f;
	}

	~tagImpact_Phase() {};
} IMPACT_PHASE, *LPIMPACT_PHASE;
typedef const IMPACT_PHASE* LPCIMPACT_PHASE;


typedef struct tagSkillInfo
{
	struct ANIMATION_INFO
	{
		unsigned int animationID;
		bool isFlipX;
		bool isFlipY;
		ANIMATION_INFO()
			: animationID(-1)
			,isFlipX(false)
			,isFlipY(false)
		{
			
		}
		
	};

	tagSkillInfo(void)
		:Id(0)
		,partID(0)
		,linkSkillId(0)
		,linkTime(0.0f)
		,displacement(0)
		,beatBackDistance(0)
		,isSpecial(false)
		,canCommonBreak(false)
		,canSpecialBreak(false)
		,damage(0)
		,criticalRate(0.0f)
		,attackNumber(0)
		,canControl(false)
		,continueTime(0.0f)
		,whichTime(0)
		,type(ToNormalAttack)
		,iShakeCamera(0)
		,bCameraStartTime(0.0f)
		,fCoolTime(0.0f)
		,SoundId(0)
		,bSoundLoop(false)
		,bAim(false)
		,effectId(0)
		,longDistanceAttackRange(0)
		,bAdaptationDistance(false)
		,bBasedOnFrame(false)
		,roleType(kTypeFighter_Boy)
	{

	}

	enum ATTACK_TYPE
	{
		E_NORMAL = 1,
		E_MAGIC,
		E_SKILL,

		E_DODGE,	// 闪避
		E_PARRY,	// 格挡
		E_STRIKE,	// 暴击
	};

	// skill Id
	int Id;
	EventType type;

	int partID;
	int linkSkillId;

	ANIMATION_INFO animation[4];
	
	float linkTime;
	int displacement;
	int beatBackDistance;
	bool isSpecial;
	bool canCommonBreak;
	bool canSpecialBreak;
	int damage;
	float criticalRate;

	// 主角该技能过程中可以击中的次数
	int attackNumber;

	// 技能释放过程中是否可以移动（0为不行，1为可以）
	bool canControl;

	// 该技能可持续时间
	float continueTime;

	// 主角形成位移时的速度由哪个时间控制（1为动画时间，2为continue_time。。。）
	int whichTime;

	/// skill description
	char   SkillDesp[512];


	/// camera effect
	int   iShakeCamera;
	float  bCameraStartTime;
	float  fCoolTime;
	
	int SoundId;

	bool bSoundLoop;
	bool bAim;

	int effectId;
	int effectsoundID;

	std::string actionName;
	std::string actionIcon;

	int longDistanceAttackRange;
	float longDistanceEffectSpeed;
	bool bShowFarWay;	// 在某个地方瞬间出来
	bool bDisappear;
	float alpha;

	float ownCD;
	float shareCD;

	bool bAdaptationDistance;

	bool bBasedOnFrame;

	RoleJobType roleType;

	bool bBuff;

	ATTACK_TYPE attackType;

	unsigned int firstSkillID;

	/// states of skill 
	PERFORM_PHASE  Perform;
	SHOW_PHASE  Show;
	IMPACT_PHASE  Impact;

}SKILL_INFO, *LPSKILL_INFO;
typedef const SKILL_INFO*   LPCSKILL_INFO;


typedef struct tagSkillSlotInfo
{
	unsigned int slotIndex;
	unsigned int skillId;

	tagSkillSlotInfo(){
		slotIndex = 0;
		skillId = 0;
	}
}SKILL_SLOT_INFO, *LPSKILL_SLOT_INFO;
typedef const SKILL_SLOT_INFO*   LPCSKILL_SLOT_INFO;

struct FAIRY_SKILL_INFO : public INFOID, public BATTLEINFO
{
	enum TYPE
	{
		E_ATTACK,
		E_BUFFER,

	};

	enum AIM
	{
		E_HERO,
		E_ENEMY,
		E_FULL_SCREEN,

	};

	FAIRY_SKILL_INFO(void)
	{
		memset(this, 0x00, sizeof(FAIRY_SKILL_INFO));
	}

	unsigned int  fairy_ID;
	TYPE type;
	AIM aim;
	bool bLock;
	tagSkillInfo::ANIMATION_INFO animation[4];
	int attack_number;
	float continueTime;
	int effectID;
	int longDistanceAttackRange;
	int longDistanceEffectSpeed;
	int soundID;
	int effectSoundID;
	int hurt;

	float ownCD;

};