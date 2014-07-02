

#include "MainMenuLayer.h"

#include "SpriteSeer.h"
#include "GameManager.h"
#include "HSJoystick.h"
#include "LevelManager.h"
#include "MainLandManager.h"
#include "GameDataManager.h"
#include "BattleCoverLayer.h"

GameDataManager::GameDataManager()
	:heroMoveType(MOVE_BY_JOY)
	,heroAutoAttack(false)
{   
	taskPos.cityId = 0;
	taskPos.position = ccp(0, 0);
}

GameDataManager::~GameDataManager()
{
	
}

void GameDataManager::setHeroMoveType(Move_Type type)
{
	this->heroMoveType = type;

	bool isMainLandLevel = MainLandManager::Get()->isMainLand(LevelManager::sShareInstance()->getCurMapId());
	SpriteSeer * seer = GameManager::Get()->getHero();
	if (seer && !isMainLandLevel)
	{
		seer->SetMoveType(type);
		seer->moveToTarget(seer->getPosition(), seer->getPosition());
	}

	HSJoystick * stick = HSJoystick::sharedJoystick();

	if (stick)
	{
		if (!isMainLandLevel)
		{
			stick->setIsEnable(MOVE_BY_JOY == type ? true : false);
		}
		else
		{
			stick->setIsEnable(false);
		}	
	}
}

void GameDataManager::setHeroAutoAttack(bool autoAttack)
{
	if (heroAutoAttack == autoAttack)
	{
		return;
	}
	heroAutoAttack = autoAttack;
	SpriteSeer * seer = GameManager::Get()->getHero();
	if (GameManager::Get()->GetSceneLayer())
	{
		MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
		if (mLayer)
		{
			BattleCoverLayer * coverLayer = mLayer->GetBattleCoverLayer();
			if (autoAttack)
			{
				coverLayer->openBattleCoverLayer(COVER_AUTOATTACK);
			}
			else
			{
				coverLayer->closeBattleCoverLayer(NULL);
			}
		}
	}

	if (seer)
	{
		if (autoAttack)
		{		
			seer->startAutoAttack();
		}
		else
		{
			seer->endAutoAttack();
		}
	}
}