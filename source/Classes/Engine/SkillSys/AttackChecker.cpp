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
#include "OnlineNetworkManager.h"
#include "AttackChecker.h"
#include "SpriteSeer.h"
#include "SpriteMonsterMgr.h"
#include "SpriteMonster.h"
#include "GameManager.h"
#include "SceneLayer.h"
#include "MainMenuLayer.h"
#include "ParticleManager.h"
#include "SkillDispMgr.h"
#include "SkillInfo.h"
#include "GameAudioManager.h"
#include "UserData.h"
#include "LevelManager.h"
#include "LevelLayer.h"
#include "CameraController.h"

AttackChecker::CBase::CBase(BoneSpriteBase* pAttacker) 
	:m_skillID(0)
	,m_attackPeriod(0.0f)
	, m_pAttacker(pAttacker)
	, m_bAttackOtherPlayer(false)
	, m_attackNumber(0)
	, m_bBasedOnFrame(false)
	, m_defenderID(0)
	, m_beatBackDistance(0)
	, m_type(ToNormalAttack)
	, m_attackType(tagSkillInfo::E_NORMAL)
	, m_attackBoxFrame(-1)
	, m_bFullScreenAttack(false)
	, m_bShakeCamera(false)
{
	m_bPlayCritSound = false;
	m_bPlayUncritSound = false;
	m_fDeltaTimeCrit = 0;
	m_fDeltaTimeUncrit = 0;
	if(m_pAttacker)
	{
		if(dynamic_cast<EffectSprite*>(m_pAttacker))
		{
			m_attackerID = GameManager::Get()->getHero()->GetID();
		}
		else
		{
			m_attackerID = m_pAttacker->GetID();
		}
	}
}

AttackChecker::CBase::~CBase()
{

}

void AttackChecker::CBase::Update( float dt )
{
	// reset crit sound playing flag
	m_bPlayCritSound = false;
	m_bPlayUncritSound = false;
	m_curAttackTime -= dt;

	if(m_curAttackTime > 0.0f)
	{
		return;
	}

	m_curAttackTime = m_attackPeriod;

	if (m_pAttacker)
	{
		cocos2d::CCRect heroABox = m_pAttacker->getRelativeParentAttackBox();

		if(m_bFullScreenAttack)
		{
			CCPoint cameraOffset = CCDirector::sharedDirector()->getLevelRenderCameraOffset();
			CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
			heroABox = CCRectMake(cameraOffset.x,cameraOffset.y,visibleSize.width,visibleSize.height);	
		}

		if(heroABox.size.width > 0.0f || heroABox.size.height > 0.0f)
		{
			int curFrame = m_pAttacker->getCurAnimationFrameID();
			if(m_attackBoxFrame != curFrame)
			{
				m_attackBoxFrame = curFrame;

				if(m_bAttackOtherPlayer)
				{
					if(LevelManager::sShareInstance()->getCurrentLevelLayer())
					{
						if(GameManager::Get()->getHero()->GetID() != m_attackerID)
						{
							if(!IsBattleSide(GameManager::Get()->getHero()))
							{
								IntersectsRect(heroABox, GameManager::Get()->getHero());
							}
						}

						std::map<unsigned int, OthersPlayerInfo>& otherPlayer = LevelManager::sShareInstance()->getCurrentLevelLayer()->m_othersPlayerInfo;
						for(std::map<unsigned int, OthersPlayerInfo>::const_iterator iter = otherPlayer.begin(); iter != otherPlayer.end(); iter++)
						{
							BoneSpriteBase* pOtherHero = dynamic_cast<BoneSpriteBase*>(iter->second.seer); 
							if(pOtherHero->GetID() == m_attackerID)
								continue;
							if(!IsBattleSide(pOtherHero))
								IntersectsRect(heroABox, pOtherHero);
						}
					}
				}
				else
				{
					const map<int, SpriteMonster*>& allMonster = SpriteMonsterMgr::Get()->GetAllMonster();
					for(map<int, SpriteMonster*>::const_iterator iter = allMonster.begin(); iter != allMonster.end(); iter++)
					{
						SpriteMonster* pMonster = iter->second; 
						IntersectsRect(heroABox, pMonster);
					}
				} // if(m_bAttackOtherPlayer)
			}
			

		}
		
	}

	// 播放攻击的声音
	if (m_bPlayCritSound )
	{
		PlayCritSound(dt);
	}

	if (m_bPlayUncritSound)
	{
		PlayUncritSound(dt);
	}

}

bool AttackChecker::CBase::IsBattleSide(BoneSpriteBase* pOther)
{
	if(m_bAttackOtherPlayer)
	{
		
		USERINFO* pAttackerUserInfo = UserData::Get()->GetUserInfo(m_attackerID);
		USERINFO* pDefenUserInfo = UserData::Get()->GetUserInfo(pOther->GetID());
		if(pAttackerUserInfo && pDefenUserInfo)
		{
			if(pAttackerUserInfo->battleSide % 2 == pDefenUserInfo->battleSide % 2)
			{
				return true;
			}
			return false;
		}
	}
	return true;
}
void AttackChecker::CBase::IntersectsRect(cocos2d::CCRect& attackBox, BoneSpriteBase* pOther)
{
	cocos2d::CCRect monsterRect = pOther->getRelativeParentColliderRect();
	

	if(monsterRect.size.width > 0.0f && 
		monsterRect.size.height > 0.0f &&
		attackBox.intersectsRect(monsterRect)
		)
	{
		m_defenderID = pOther->GetID();

		int attackedCount = 0; 
		map<int, int>::iterator attackIter = m_attackedMonsterList.find(m_defenderID);

		if(attackIter != m_attackedMonsterList.end())
		{
			attackIter->second++;
			attackedCount = attackIter->second;
		}
		else
		{
			attackedCount = 1;
			m_attackedMonsterList[m_defenderID] = attackedCount;
		}

		DoAttack(pOther, attackedCount);
	}
}

/// 申请播放暴击声音
void AttackChecker::CBase::PlayCritSound(float dt)
{
	//m_fDeltaTimeCrit -= dt;

	//if (m_fDeltaTimeCrit < 0)
	//{
	//	GameAudioManager::sharedManager()->playEffect(GetSkillInfo()->SoundId,	false);
	//	m_fDeltaTimeCrit = 1.0f;
	//}

	if (false == GameAudioManager::sharedManager()->isEffectIsPlaying(321003))
	{
		GameAudioManager::sharedManager()->playEffect(321003,	false);
	}
}

/// 申请播放非暴击声音
void AttackChecker::CBase::PlayUncritSound(float dt)
{
	//m_fDeltaTimeUncrit -= dt;

	//if (m_fDeltaTimeUncrit < 0)
	//{
	//	m_fDeltaTimeUncrit = 0.5f;
	//	GameAudioManager::sharedManager()->playEffect(GetSkillInfo()->SoundId,	false);
	//}

	if (false == GameAudioManager::sharedManager()->isEffectIsPlaying(321004))
	{
		GameAudioManager::sharedManager()->playEffect(321004,	false);
	}
}

void AttackChecker::CBase::SetSkillID( unsigned int id )
{
	m_skillID = id;
	m_attackedMonsterList.clear();
	
	const SKILL_INFO* pSkill = SkillDispMgr::Get()->GetSkillInfo(id);
	m_attackNumber = 1;
	float fContinueTime = 0.0f;

	m_bBasedOnFrame = false;
	m_beatBackDistance = 0.0f;

	if(pSkill)
	{
		UserSkillInfo info;
		if(SkillDispMgr::Get()->GetOneSkillInfoById(m_attackerID, m_skillID, info))
		{
			//if(SkillDispMgr::Get()->GetOneSkillInfoById(m_skillID, info))
			{
				if(pSkill->partID == info.parts(0).part())
				{
					fContinueTime = info.parts(0).continue_time();
				}
			}
		}
		else
		{
			
			fContinueTime = pSkill->continueTime;
		}

		m_bBasedOnFrame = pSkill->bBasedOnFrame;
		m_beatBackDistance = pSkill->beatBackDistance;

		m_type = pSkill->type;
		m_attackType = pSkill->attackType;
		m_attackNumber = pSkill->attackNumber;

		if(pSkill->iShakeCamera == 2)
		{
			m_bShakeCamera = true;
		}
	}
	else
	{
		const FAIRY_SKILL_INFO* pFairySkill = SkillDispMgr::Get()->GetFairySkillInfo(id);
		if(pFairySkill)
		{
			m_attackNumber = pFairySkill->attack_number;
			fContinueTime = pFairySkill->continueTime;
			m_attackType = tagSkillInfo::E_SKILL;
		}
	}

	if( m_attackNumber > 1)
	{
		float time = 0.0f;

		if(fContinueTime > 0.0f)
		{
			time = fContinueTime;
		}
		else
		{
			// TODO: Animation Time
			//time = 
		}
		m_attackPeriod = time / (float)m_attackNumber;
	}
		
		


	m_curAttackTime = 0.0f;
}

void AttackChecker::CBase::DoAttack( BoneSpriteBase* pDefender, int count )
{

}

inline int ranged_random(int a, int b)
{
	int max = a>b?a:b;
	int min = a<=b?a:b;
	// generates ranged random number
	return (rand() % (max - min + 1)) + min;
}


AttackChecker::CBase::INJURE_DATA AttackChecker::CBase::CalInjure(tagSkillInfo::ATTACK_TYPE attackType, unsigned int damage, const BATTLEINFO* pAttackInfo, const BATTLEINFO* pDefenerInfo)
{
	static const unsigned int ALL_CONSTANT = 10000;
	static const unsigned int DODGE_CONSTANT = 1500;
	static const unsigned int PARRY_REDUCE_CONSTANT = 5000;
	static const unsigned int CRIT_MULT_CONSTANT = 10000;
	static const unsigned int MIN_HURT_CONSTANT = 3;

	INJURE_DATA ret;

	if(!pAttackInfo || !pDefenerInfo)
	{
		return ret;
	}

	int hurt = 0;
	tagSkillInfo::ATTACK_TYPE type = tagSkillInfo::E_NORMAL;

	unsigned int typeProbability = ranged_random(0, 10000);
	
	unsigned int probability_max = 8000;
	unsigned int current_dodge = DODGE_CONSTANT + pDefenerInfo->dodge * 10 > pAttackInfo->accurate *10 ? 
		DODGE_CONSTANT + pDefenerInfo->dodge * 10 - pAttackInfo->accurate *10 : 0 ;

	current_dodge = current_dodge > probability_max? probability_max : current_dodge;
	if(typeProbability < probability_max && typeProbability >= probability_max - current_dodge)
	{
		type = tagSkillInfo::E_DODGE;
	}
	probability_max -= current_dodge;
	
	unsigned int current_parry = pDefenerInfo->parry * 10 > pAttackInfo->wreck * 10 ?
		pDefenerInfo->parry * 10 - pAttackInfo->wreck * 10 : 0;

	current_parry = current_parry > probability_max? probability_max : current_parry;
	if(typeProbability < probability_max && typeProbability >= probability_max - current_dodge)
	{
		type = tagSkillInfo::E_PARRY;

	}
	probability_max -= current_parry;
	
	unsigned int  current_crit = pAttackInfo->critical_strike * 10 > pDefenerInfo->tenacity * 10 ?
		pAttackInfo->critical_strike * 10 - pDefenerInfo->tenacity * 10 : 0;

	current_crit = current_crit > probability_max? probability_max : current_crit;

	if(typeProbability < probability_max && typeProbability >= probability_max - current_dodge)
	{
		type = tagSkillInfo::E_STRIKE;

	}

	probability_max -= current_crit;

	switch(attackType)
	{
	case tagSkillInfo::E_NORMAL:	// 普通攻击
		{
			unsigned int attackValue = pAttackInfo->physical_attack;
			unsigned int defenceValue = pDefenerInfo->physical_defence / m_attackNumber;
			unsigned int hurt1 = (attackValue > defenceValue? attackValue - pDefenerInfo->physical_defence : 0) * damage /100 * ranged_random(95, 105) / 100;
			unsigned int hurt2 = attackValue * MIN_HURT_CONSTANT / 100;
			hurt = hurt1 > hurt2? hurt1: hurt2;

			if(hurt < 1)
				hurt = 1;
		}

		break;
	case tagSkillInfo::E_MAGIC: // 魔法攻击
		{
			unsigned int attackValue = pAttackInfo->magic_attack;
			unsigned int defenceValue = pDefenerInfo->magic_defence / m_attackNumber;
			unsigned int hurt1 = (attackValue > defenceValue ? attackValue - defenceValue : 0) * damage /100 * ranged_random(95, 105) / 100;
			unsigned int hurt2 = attackValue * MIN_HURT_CONSTANT / 100;
			hurt = hurt1 > hurt2? hurt1: hurt2;

			if(hurt < 1)
				hurt = 1;
		}
		break;
	case tagSkillInfo::E_SKILL: // 技能攻击
		{
			unsigned int hurtPercent = 100;
			unsigned int skillAttackValue = 0;
			UserSkillInfo info;
			if(SkillDispMgr::Get()->GetOneSkillInfoById(m_attackerID, m_skillID, info))
			{
				hurtPercent = info.parts(0).hurt();
				skillAttackValue = info.parts(0).exp_battle_info().skill_attack();
			}

			unsigned int attackValue = pAttackInfo->skill_attack;
			unsigned int defenceValue = pDefenerInfo->skill_defence / m_attackNumber;

			unsigned int hurt1 = 0;
			if(attackValue  * hurtPercent / 100 > defenceValue)
				hurt1 = ((attackValue  * hurtPercent / 100 - defenceValue));
			else
				hurt1 = 0;
			hurt1 = (hurt1 + skillAttackValue) * ranged_random(95, 105) / 100;
			unsigned int hurt2 = attackValue * MIN_HURT_CONSTANT / 100;
			hurt = hurt1 > hurt2? hurt1: hurt2;

			if(hurt < 1)
				hurt = 1;
		}
		break;
	default:
		break;
	}

	switch (type)
	{
	case tagSkillInfo::E_DODGE:
		{
			hurt = 0;
		}
		break;
	case tagSkillInfo::E_PARRY:
		{
			hurt = hurt * (ALL_CONSTANT - PARRY_REDUCE_CONSTANT) / ALL_CONSTANT ;

			if(hurt < 1)
				hurt = 1;

		}
		break;
	case tagSkillInfo::E_STRIKE:
		{
			hurt = hurt * (CRIT_MULT_CONSTANT + pAttackInfo->slay * 10 ) / ALL_CONSTANT;

			if(hurt < 1)
				hurt = 1;
		}
		break;
	default:
		break;
	}

	ret.hurt = hurt;
	ret.attackType = type;
	return ret;
}

int AttackChecker::CBase::GetAttackCoef( )
{
	int attackCoef = 100;
	UserSkillInfo info;
	if(SkillDispMgr::Get()->GetOneSkillInfoById(m_attackerID, m_skillID, info))
	{
		attackCoef = (int)info.parts(0).hurt();
	}

	// CCLog("skillID : %u, attackCoef : %ld", m_skillID, attackCoef);

	return attackCoef;
}

// -----------------------------------------------------------------------------------------------------------

void AttackChecker::CNormalAttack::DoAttack( BoneSpriteBase* pDefender, int count )
{
	if(!m_bBasedOnFrame)
	{
		if(count > m_attackNumber)
			return;
	}

	BoneSpriteBase* pMonster = dynamic_cast<BoneSpriteBase*>(pDefender);
	SpriteSeer* pHero = dynamic_cast<SpriteSeer*>(GameManager::Get()->getHero());

	if(pHero == NULL || pMonster == NULL)
		return;

	int attackCoef = GetAttackCoef();

	BATTLEINFO* pAttackInfo = dynamic_cast<BATTLEINFO*>(UserData::Get()->GetUserInfo(pHero->GetID()));
	BATTLEINFO* pDefenerInfo = NULL;
	if(m_bAttackOtherPlayer)
	{
		pDefenerInfo = dynamic_cast<BATTLEINFO*>(UserData::Get()->GetUserInfo(pMonster->GetID()));
	}
	else
	{
		pDefenerInfo = (BATTLEINFO*)(USERINFO*)(EntityInfo::Get()->GetInfo(pMonster->GetID()));
	}

	INJURE_DATA injure = CalInjure( m_attackType, attackCoef, pAttackInfo, pDefenerInfo);

	CCPoint dir = ccpSub(pMonster->getPosition(), pHero->getPosition());

	//当主角和怪物位置重合时，不能直接Normalize
	if (dir.x == 0 && dir.y == 0)
	{
		dir = pHero->getDirectionVector();
	}
	dir = ccpNormalize(dir);
	dir = ccpMult(dir, m_beatBackDistance );
	dir = ccpAdd(dir, pMonster->getPosition());
	CCPoint pos = pMonster->getPosition();
	if(injure.attackType != tagSkillInfo::E_DODGE)
	{
		if(dynamic_cast<SpriteMonster*>(pMonster))
		{
			pos = dynamic_cast<SpriteMonster*>(pMonster)->onEventAttacked(dir);

		}

		GameManager::Get()->GetSceneLayer()->getMainMenuLayer()->HandleComboIncrease();

	}

	AttackMonsterInfo attackMonsterInfo;
	attackMonsterInfo.set_id(GetDefenderID());
	CSPoint* pCSPoint = attackMonsterInfo.mutable_start_pos();
	CCPoint startPos = LevelManager::sShareInstance()->pointPixelToCell(pMonster->getPosition());
	pCSPoint->set_xpos(startPos.x);
	pCSPoint->set_ypos(startPos.y);

	pCSPoint = attackMonsterInfo.mutable_pos();
	pos = LevelManager::sShareInstance()->pointPixelToCell(pos);
	pCSPoint->set_xpos(pos.x);
	pCSPoint->set_ypos(pos.y);
	
	pCSPoint = attackMonsterInfo.mutable_direct();
	dir.setPoint(1.0f, 0.0f);
	if(dynamic_cast<BoneSpriteMoveable*>(pMonster))
	{
		dir = dynamic_cast<BoneSpriteMoveable*>(pMonster)->getDirectionVector();

	}
	pCSPoint->set_xpos(dir.x);
	pCSPoint->set_ypos(dir.y);

	attackMonsterInfo.set_blood( injure.hurt );
	
	attackMonsterInfo.set_status(MONSTER_HURT);
	
	m_attackMessage.push_back(attackMonsterInfo);

	bool isCrit = false;

	if(!m_bAttackOtherPlayer)
	{
		switch(injure.attackType)
		{
		case tagSkillInfo::E_PARRY:
			GameManager::Get()->GetSceneLayer()->getMainMenuLayer()->HandleAttackBlockEffect(pMonster->getPosition());
			if(m_bAttackOtherPlayer)
			{
				if(dynamic_cast<SpriteSeer*>(m_pAttacker))
				{
					dynamic_cast<SpriteSeer*>(m_pAttacker)->ByAttacked(injure.hurt);
				}
			}
			else
			{
				GameManager::Get()->GetSceneLayer()->getMainMenuLayer()->HandleDamageNumberEffect(pMonster, injure.hurt, false);
				if(dynamic_cast<SpriteMonster*>(pMonster))
				{
					dynamic_cast<SpriteMonster*>(pMonster)->PlayAttackedEffect(false);
				}
			}
			break;
		case tagSkillInfo::E_STRIKE:
			{
				isCrit = true;
				if(m_bAttackOtherPlayer)
				{
					if(dynamic_cast<SpriteSeer*>(pMonster))
					{
						dynamic_cast<SpriteSeer*>(pMonster)->ByAttacked(injure.hurt, true);
					}
				}
				else
				{
					GameManager::Get()->GetSceneLayer()->getMainMenuLayer()->HandleDamageNumberEffect(pMonster, injure.hurt, true);
					if(dynamic_cast<SpriteMonster*>(pMonster))
					{
						dynamic_cast<SpriteMonster*>(pMonster)->PlayAttackedEffect(true);
					}
				}

			}
			break;
		case tagSkillInfo::E_DODGE:
			GameManager::Get()->GetSceneLayer()->getMainMenuLayer()->HandleAttackMissEffect(pMonster->getPosition());
			break;
		default:
			if(m_bAttackOtherPlayer)
			{
				if(dynamic_cast<SpriteSeer*>(pMonster))
				{
					dynamic_cast<SpriteSeer*>(pMonster)->ByAttacked(injure.hurt);
				}
			}
			else
			{
				GameManager::Get()->GetSceneLayer()->getMainMenuLayer()->HandleDamageNumberEffect(pMonster, injure.hurt, false);
				if(dynamic_cast<SpriteMonster*>(pMonster))
				{
					dynamic_cast<SpriteMonster*>(pMonster)->PlayAttackedEffect(false);
				}

			}
			break;
		}
	}
	
	if(isCrit)
	{
		m_bPlayCritSound = true;

		float scaleTime = 0.0f;
		CameraController::sharedCameraController()->shakeAndScale(scaleTime, 0.05f, 0.1f, 1.4f, 1.0f);

	}
	else
	{
		if(injure.attackType == tagSkillInfo::E_DODGE)
		{
			m_bPlayUncritSound = false;
		}
		else
		{
			// 击中了怪物，
			m_bPlayUncritSound = true;
		}
		
		if(m_bShakeCamera)
		{
			float scaleTime = 0.5f;
			CameraController::sharedCameraController()->shakeAndScale(scaleTime, 0.05f, 0.1f, 1.4f, 1.0f);

		}
	}
	
	if(m_bAttackOtherPlayer)
	{

		AttackPlayerInfo attackOtherHeroInfo;
		attackOtherHeroInfo.set_userid(pMonster->GetID());
		attackOtherHeroInfo.set_blood(injure.hurt);
		switch(injure.attackType)
		{
		case tagSkillInfo::E_DODGE:
			attackOtherHeroInfo.set_hurt_type(1);
			break;
		case tagSkillInfo::E_PARRY:
			attackOtherHeroInfo.set_hurt_type(2);
			break;
		case tagSkillInfo::E_STRIKE:
			attackOtherHeroInfo.set_hurt_type(3);
			break;
		default:
			attackOtherHeroInfo.set_hurt_type(4);
			break;
		}

		CSPlayerHitPlayerReq attackReq;
		attackReq.set_userid(pHero->GetID());
		CSPoint* pCSPoint = attackReq.mutable_start_pos();

		// TODO : user hero or effect?
		CCPoint pos = pHero->getPosition();

		pos = LevelManager::sShareInstance()->pointPixelToCell(pos);
		pCSPoint->set_xpos(pos.x);
		pCSPoint->set_ypos(pos.y);
		pCSPoint = attackReq.mutable_start_direct();
		CCPoint dir = pHero->getDirectionVector();
		pCSPoint->set_xpos(dir.x);
		pCSPoint->set_ypos(dir.y);

		dir = pHero->getDirectionVector();
		pCSPoint = attackReq.mutable_end_direct();
		pCSPoint->set_xpos(dir.x);
		pCSPoint->set_ypos(dir.y);

		pos = pHero->getPosition();
		pos = LevelManager::sShareInstance()->pointPixelToCell(pos);
		pCSPoint = attackReq.mutable_end_pos();
		pCSPoint->set_xpos(pos.x);
		pCSPoint->set_ypos(pos.y);

		attackReq.set_action_id(m_skillID);
		attackReq.clear_users();
		*attackReq.add_users() = attackOtherHeroInfo;

		if(pHero)
		{
			if(injure.attackType != tagSkillInfo::E_DODGE)
			{
				if(pHero->getTag() == MAP_TAG_SEER)
					OnlineNetworkManager::sShareInstance()->sendPlayerAttackOtherPlayerMessage(attackReq);
			}
		}
	}
	else
	{
		CSPlayerAttackReq attackReq;
		attackReq.set_userid(UserData::Get()->getUserId());
		pCSPoint = attackReq.mutable_start_pos();
		pos = pHero->getPosition();
		pos = LevelManager::sShareInstance()->pointPixelToCell(pos);
		pCSPoint->set_xpos(pos.x);
		pCSPoint->set_ypos(pos.y);
		pCSPoint = attackReq.mutable_start_direct();
		dir = pHero->getDirectionVector();
		pCSPoint->set_xpos(dir.x);
		pCSPoint->set_ypos(dir.y);

		dir = pHero->getDirectionVector();
		pCSPoint = attackReq.mutable_end_direct();
		pCSPoint->set_xpos(dir.x);
		pCSPoint->set_ypos(dir.y);

		pos = pHero->getPosition();
		pos = LevelManager::sShareInstance()->pointPixelToCell(pos);
		pCSPoint = attackReq.mutable_end_pos();
		pCSPoint->set_xpos(pos.x);
		pCSPoint->set_ypos(pos.y);

		attackReq.set_action_id(m_skillID);
		attackReq.clear_monsters();
		*attackReq.add_monsters() = attackMonsterInfo;

		if(injure.attackType != tagSkillInfo::E_DODGE)
		{
			if(pHero->getTag() == MAP_TAG_SEER)
				OnlineNetworkManager::sShareInstance()->sendPlayerAttackMessage(attackReq);
		}
		
	}
	
	
}
