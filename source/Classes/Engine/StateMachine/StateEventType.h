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


//  state event type
enum EventType
{
    ET_None = -1,

    ToIdle	= 0,
    ToRun	= 1,
	ToBaseAttack,

    ToNormalAttack,
	ToSpecialAttack,
	ToGreatFireBall,
	ToCalving,
	ToBlackHole,
	ToTeleport,
	ToChopseries,
	ToAssassination,
	ToFatalDarkKnives,
	ToWhirlwind,
	ToStepSword,
	ToEarthSplitter,
	ToLinkTimeHandler,
	
	// buf
	ToIronDefense,
	ToInvincibility,
	ToInvisibleKiller,
	ToApocalypse,
	ToExtremeSpeed,

	// magic effect
	ToGreatMagicFireBall,
	ToNormalMagicFireBall,
	ToCalvingMagic,

	ToAnimHandler,
	ToMagicAnimHandler,
	ToAttackCheckerHandler,
	ToMagicCheckHandler,
	ToAttackSenderHandler,
	ToEffectAnimHandler,
	ToRoleEffectHandler,
	ToAimDirectionHandler,

	ToSkillBeginSenderHandler,
	ToSkillBeginReceiverHandler,
	ToMoveToHandler,
	ToVariableSpeedMoveToHandler,

	ToDoSkill,
	ToDead,
	ToRevival,
	ToLinkTime,

	ToBaseElfAttack,
	ToElfChase,
	ToElfCloseTo,
	ToElfSkillAttack,
	ToElfEffectAnimHandler,
	ToElfAimDirectionHandler,
	ToElfAnimHandler,
	ToElfAttackTrigger,
	ToElfMagicCheckHandler,

    // add more here!
};


static bool bET_Table[][3] = {
 //         | idle | run | fight|  
/*idle */   {false, false, false },
/*run  */   {false, false, false },
/*fight*/   {false, false, false }
};
