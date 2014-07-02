#include "OnlineNetworkManager.h"


#include "GameManager.h"
#include "EnginePCH.h"
#include "TXGUIHeader.h"
#include "CrossPlatform.h"
#include "XPlatformManager.h"
#include "ILogicManager.h"
#include "GameAudioManager.h"
#include "GameResourceManager.h"

#include "CConnectionData.h"
#include "SkeletonAnimRcsManager.h"
#include "LevelManager.h"
#include "ParticleManager.h"
#include "CameraController.h"
#include "SkillDispMgr.h"
#include "SpriteMonsterMgr.h"
#include "HelloWorldScene.h"
#include "MainLandManager.h"

using namespace TXGUI;

// constructor
GameManager::GameManager() :
m_pLogicMgr(NULL),
m_pSpriteSeer(NULL),
m_sceneLayer(NULL),
m_spriteSeerTypeId(-1)
{

	// Init Platform device
	XPlatformManager::_SMInit();
	XPlatformManager::m_sPlatformMgr->SetExternalResourceMgr(GameResourceManager::sharedManager());
	XPlatformManager::m_sPlatformMgr->InitDevice();

	// init TXGUI Engine
	TXMainSDM::Init();

	Engine::_SDMInit();

	/// init audio device
	GameAudioManager::sharedManager()->InitDevice();

	SkillDispMgr::Create();
	SpriteMonsterMgr::Create();

}


GameManager::~GameManager()
{
	/// clear cameara controller
	CameraController::purgeInstance();

	SpriteMonsterMgr::Destroy();
	SkillDispMgr::Destroy();
	LevelManager::Destroy();
	ParticleManager::Destroy();
	MainLandManager::Destroy();

	/// un-init audio device
	GameAudioManager::sharedManager()->Destroy();

	Engine::_SDMShutDown();

	// shut down TXGUI Engine
	TXMainSDM::ShutDown();

	// Shut down Platform device
	XPlatformManager::_SMShutDown();
	m_pLogicMgr = NULL;	

	// ¹Ø±ÕÍøÂç²ã
	OnlineNetworkManager::Destroy();

	GameResourceManager::purgeInstance();
}

SpriteSeer *GameManager::getHero()
{
	return m_pSpriteSeer;
}

void GameManager::setHero(SpriteSeer* hero)
{
	m_pSpriteSeer = hero;
}

int GameManager::getHeroTypeId()
{
	return m_spriteSeerTypeId;
}

void GameManager::setHeroTypeId(int typeId)
{
	m_spriteSeerTypeId = typeId;
}

void GameManager::SetLogicManager(ILogicManager *pILogicMgr)
{
	CCAssert(m_pLogicMgr == NULL, "m_pLogicMgr is not null!");
	m_pLogicMgr = pILogicMgr;
}

CCScene* GameManager::goToSplash()
{
	if(m_sceneLayer)
	{
		m_sceneLayer->clearCurScene();
	}
	CCScene *pScene = HelloWorld::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
	CCTextureCache::sharedTextureCache()->removeUnusedTextures();
	m_sceneLayer = NULL;

	return pScene;
}

SceneLayer* GameManager::GetSceneLayer()
{
	return m_sceneLayer;
}

// process touch
void GameManager::processTouchBegan(CCPoint touchPoint)
{
	bool isReacted = false;
	// player processing..

	// NPC processing...	

}

void GameManager::changeMap(int mapId, KMapFromType fromMapType)
{
	if (0 != m_sceneLayer)
	{
		((SceneLayer*)m_sceneLayer)->changeMap(mapId, fromMapType);
	}	
}


// go to the frontend UI
void GameManager::goToFrontend()
{
	if(!m_sceneLayer)
	{
		CCDirector *pDirector = CCDirector::sharedDirector();

		m_sceneLayer = (SceneLayer*)SceneLayer::create();	
		pDirector->replaceScene((CCScene*)m_sceneLayer);

		this->startGame();
	}
}

// start game
void GameManager::startGame()
{
	if (m_pLogicMgr)
	{
		m_pLogicMgr->startGame();
	}
}

void GameManager::exitGame()
{
	if (m_pLogicMgr)
	{
		m_pLogicMgr->exitGame();
	}
}

