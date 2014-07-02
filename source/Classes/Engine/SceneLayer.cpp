#include "OnlineNetworkManager.h"
#include "SceneLayer.h"
#include "LevelDefine.h"
#include "SpriteSeer.h"
#include "MainMenuLayer.h"
#include "GameManager.h"
#include "UserData.h"
#include "ParticleManager.h"
#include "AParticleNode.h"
#include "UIManager.h"
#include "GameAudioManager.h"
#include "CConnectionData.h"
#include "SkeletonAnimRcsManager.h"
#include "LoadingLayer.h"
#include "TaskManager.h"
#include "ResoureUpdate.h"
#include "XLogicManager.h"
#include "GMessage.h"
#include "SpriteElfManager.h"
#include "MainLandManager.h"
#include "StoryDataCenter.h"
#include "InstanceManager.h"
#include "StoryInstanceDirector.h"
#include "GameConfigFromLuaManager.h"
#include "GameUILayer.h"

#define LOADINGTIME 10

SceneLayer::SceneLayer()
:m_curMapId(-1)
,m_lastMapId(-1)
,m_fromMapType(-1)
,m_LevelLayer(NULL)
,m_uiLayer(NULL)
,_barFrame(NULL)
,m_pStepMapLoader(NULL)
{
	this->m_accumulator = 0;
	this->m_lastTickTime = 0;
	m_pStepMapLoader = new StepMapLoader(this);
}

SceneLayer::~SceneLayer()
{  
	if (m_pStepMapLoader)
	{
		delete m_pStepMapLoader;
		m_pStepMapLoader = NULL;
	}


	if (_barFrame)
		_barFrame->release();
	_barFrame = NULL;


	GameManager::Get()->exitGame();
}


//////////////////////////////////////////////////////////////////////////
bool SceneLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}    
	//this->joystick = HSJoystick::create();
	//this->addChild(joystick, 2);
	HSJoystick* joystick = HSJoystick::sharedJoystick();
	//joystick->retain();
	//joystick->removeFromParent();
	float scale = TXGUI::UIManager::sharedManager()->getScaleFactor();
	joystick->setScale(scale);
	this->addChild(joystick, 2);
	//joystick->release();
	
	m_pLoadingUI = LoadingLayer::create();
	this->addChild(m_pLoadingUI,100);
    
    setupLoadbar();

	m_uiLayer = CCLayer::create();
	addChild(m_uiLayer, SCENE_Z_DYNAMIC_UI, SCENE_Z_DYNAMIC_UI);
    
	return true;
}

//////////////////////////////////////////////////////////////////////////
SpriteSeer*	SceneLayer::getSpriteSeer()
{
	if (m_LevelLayer)
	{
		return m_LevelLayer->getSpriteSeer();
	}

	return NULL;
}

MainMenuLayer *SceneLayer::getMainMenuLayer()
{
	if(m_uiLayer != NULL)
	{
		return (MainMenuLayer *)m_uiLayer->getChildByTag(SCENE_Z_MAIN_MENU);
	}
	return NULL;
}

CCLayer* SceneLayer::getUiLayerByTag(int tag)
{
	return (CCLayer*)m_uiLayer->getChildByTag(tag);
}


bool SceneLayer::isInHometownMap()
{
	return (0 == m_curMapId);
}

//////////////////////////////////////////////////////////////////////////

void SceneLayer::setUiLayer(CCLayer* layer,int tag)
{
	if(layer)
	{
		m_uiLayer->removeAllChildrenWithCleanup(true);
		layer->setTag(tag);
		m_uiLayer->addChild(layer);
	}
}

//////////////////////////////////////////////////////////////////////////

void SceneLayer::addUiLayer(CCLayer* layer,float zorder,int tag)
{
	if(layer)
	{
		m_uiLayer->addChild(layer,zorder,tag);
	}
}

void SceneLayer::setMainMenuLayerVisible(bool isVisible)
{
	if (this->getChildByTag(SCENE_Z_MAIN_MENU))
	{
		this->getChildByTag(SCENE_Z_MAIN_MENU)->setVisible(isVisible);
	}
}

//////////////////////////////////////////////////////////////////////////
void SceneLayer::setupMap()
{ 
	showLoading();

	needUpdate = false;
	//if(m_lastMapId != -1 && m_lastMapId != m_curMapId)
	{        
		removeMap(); 
		needUpdate = true;
	}

	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
	// re load

}

void SceneLayer::showLoading(bool bShowOnly /* = false */)
{
	if(m_pLoadingUI)
	{
		m_pLoadingUI->ShowLoading(bShowOnly);
	}
}

void SceneLayer::hideLoading()
{
    _barFrame->setVisible(true);
    if(ResoureUpdate::sharedResoureUpdate()->IsRunning())
	{
		loadResoure(30);
		loadMap();
	}
    else
    {  
		/// load map now!		
		loadResoure(10);
        loadMap();
    }
}

////// load map update function, called by schedule function
void SceneLayer::loadMapUpdate(float dt)
{
	m_pStepMapLoader->Update();
	if (m_pStepMapLoader->isCompleted())
	{
		unschedule(schedule_selector(SceneLayer::loadMapUpdate));
		schedule(schedule_selector(SceneLayer::hideloading),2.3f);
	}
}

void SceneLayer::StepMapLoader::Update()
{
	bool bMainLandLevel = MainLandManager::Get()->isMainLand(LevelManager::sShareInstance()->getCurMapId());

	switch(m_iCurStep)
	{
	case 0:
		{			
			if (bMainLandLevel)
			{
				std::vector<unsigned int> vecRoleIds;
				vecRoleIds.push_back(1);
				vecRoleIds.push_back(2);
				vecRoleIds.push_back(3);
				vecRoleIds.push_back(4);
				vecRoleIds.push_back(5);
				vecRoleIds.push_back(6);
				SkeletonAnimRcsManager::getInstance()->addOneRoleTypeIdToMap(vecRoleIds);
			}
			else
			{
				// Note: PVE 模式
				bool bPVEMode = LevelManager::sShareInstance()->isCurrentPVELevel();
				if (bPVEMode)
				{
					int heroTypeId = GameManager::Get()->getHeroTypeId();
					if (heroTypeId != -1)
					{
						std::vector<unsigned int> vecRoleIds;
						vecRoleIds.push_back(heroTypeId);
						SkeletonAnimRcsManager::getInstance()->addOneRoleTypeIdToMap(vecRoleIds);
					}
				}
				else
				{
					std::vector<unsigned int> vecRoleIds;
					vecRoleIds.push_back(1);
					vecRoleIds.push_back(2);
					vecRoleIds.push_back(3);
					vecRoleIds.push_back(4);
					vecRoleIds.push_back(5);
					vecRoleIds.push_back(6);
					SkeletonAnimRcsManager::getInstance()->addOneRoleTypeIdToMap(vecRoleIds);
				}
			}

			sActiveLevelConfig config;
			config.fromType = m_pScene->m_fromMapType;

			CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
			CCTextureCache::sharedTextureCache()->removeUnusedTextures();

			if(bMainLandLevel)
			{
				LevelManager::sShareInstance()->setCurrentLevelStatus(EInHomeTown);
			}
			else
			{
				LevelManager::sShareInstance()->setCurrentLevelStatus(EInInstance);
			}
			SpriteElfManager::Get()->ClearAllData();
			SkeletonAnimRcsManager::getInstance()->ClearSpriteElfVecIds();
			SkeletonAnimRcsManager::getInstance()->LoadCommonRcs(!bMainLandLevel);


			 CCProgressTimer *progressBar = (CCProgressTimer*)m_pScene->_barFrame->getChildByTag(0);
			 progressBar->setPercentage(50.0f);
		}

		/// goto next step
		m_iCurStep = 1;
		break;

	case 1:
		{
			SkeletonAnimRcsManager::getInstance()->LoadRoleRcsOneMap(bMainLandLevel);

			CCProgressTimer *progressBar = (CCProgressTimer*)m_pScene->_barFrame->getChildByTag(0);
			progressBar->setPercentage(70);
		}
		m_iCurStep = 2;
		break;
	case 2:
		{
			SkeletonAnimRcsManager::getInstance()->LoadOneMapRcs(m_pScene->m_curMapId,!bMainLandLevel);
			CCProgressTimer *progressBar = (CCProgressTimer*)m_pScene->_barFrame->getChildByTag(0);
			progressBar->setPercentage(80.0f);
		}
		m_iCurStep = 3;
		break;

	case 3:
		{
			sActiveLevelConfig config;
			config.fromType = m_pScene->m_fromMapType;

			CCLog("began to active level: %d",m_pScene->m_curMapId);
			unsigned int nStoryType = 0;

			bool bLoadMapNormal = true;
			bool bPVEMode = LevelManager::sShareInstance()->isCurrentPVELevel();
			bool bStoryMode = false;
			int nInstanceStars = InstanceManager::Get()->getOneInstanceStarts(InstanceManager::Get()->getCurInstanceId());
			if(bPVEMode && false == bMainLandLevel && nInstanceStars <= 0)
			{				
				bStoryMode = StoryDataCenter::Get()->IsOneItemHasStory(InstanceManager::Get()->getCurInstanceId(),m_pScene->m_curMapId,0,nStoryType);
				if (bStoryMode)
				{
					// Note: 进入副本时触发剧情
					if (nStoryType == 0)
					{
						m_pScene->m_LevelLayer = LevelManager::sShareInstance()->activeLevel(m_pScene->m_curMapId, config,true);
						StoryInstanceDirector::Get()->Begin(InstanceManager::Get()->getCurInstanceId(),m_pScene->m_curMapId,nStoryType);
						bLoadMapNormal = false;
					}
				}
			}

			if (bLoadMapNormal)
			{
				m_pScene->m_LevelLayer = LevelManager::sShareInstance()->activeLevel(m_pScene->m_curMapId, config);
				OnlineNetworkManager::sShareInstance()->sendLoadCompleteMessage();
				if (!bMainLandLevel && (LevelManager::sShareInstance()->isCurrentPPVELevel() || LevelManager::sShareInstance()->isCurrentPPVELevel()) )
				{
					MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
					if (mLayer)
					{
						BattleCoverLayer* battleCoverLayer = mLayer->GetBattleCoverLayer();
						battleCoverLayer->openBattleCoverLayer(COVER_WAITINGOTHER);	
					}
				}
			}

			m_pScene->m_LevelLayer->setPosition(ccp(0, 0));

			// Note: 主城剧情逻辑
			if (bMainLandLevel)
			{
				std::vector<unsigned int> vecId ;
				if (StoryDataCenter::Get()->IsMainLandHasStory(m_pScene->m_curMapId,2,vecId))
				{
					for (std::vector<unsigned int>::iterator iter = vecId.begin();
						 iter != vecId.end(); iter++)
					{
						int nInstanceStars = InstanceManager::Get()->getOneInstanceStarts((*iter));
						if (nInstanceStars > 0 && false == StoryDataCenter::Get()->IsOneMainLandStoryOver((*iter)))
						{
							StoryInstanceDirector::Get()->Begin((*iter),m_pScene->m_curMapId,2);
							break;
						}
					}
				}
			}

			// Note: 获取任务信息
			if (bMainLandLevel)
			{
				TaskManager::getInstance()->RqsTaskFromServer();
			}
			CCLog("finish to active level: %d",m_pScene->m_curMapId);

			playMapBGM();
			OnlineNetworkManager::sShareInstance()->sendGetOtherPlayersMessage();
			m_pScene->needUpdate = true;


			if(m_pScene->needUpdate && m_pScene->m_LevelLayer)
			{
				m_pScene->addChild(m_pScene->m_LevelLayer, SCENE_Z_MAP, SCENE_Z_MAP);
			}
			//if (false == bPVEMode || false == bStoryMode)
			//{
			//	OnlineNetworkManager::sShareInstance()->sendLoadCompleteMessage();
			//}		

			CCProgressTimer *progressBar = (CCProgressTimer*)m_pScene->_barFrame->getChildByTag(0);
			progressBar->setPercentage(100.0f);
		}
		m_iCurStep = -1;
		break;

	default:
		m_iCurStep = -1;		
		break;
	}
}

void SceneLayer::StepMapLoader::playMapBGM()
{
	int musicId = 0;
	if(MainLandManager::Get()->isMainLand(m_pScene->m_curMapId))
	{
		musicId = MainLandManager::Get()->GetCityBGM(m_pScene->m_curMapId);
		
	}
	else
	{
		int instanceId = InstanceManager::Get()->getCurInstanceId();
		musicId = GameConfigFromLuaManager::Get()->getInstanceMusicId(instanceId,m_pScene->m_curMapId);
	}
	GameAudioManager::sharedManager()->playBGMWithMap(musicId);
}

void SceneLayer::loadMap()
{
	//CCAssert(!m_LevelLayer,"m_LevelLayer not NULL");
    if(!m_LevelLayer)
	{
		m_pStepMapLoader->Begin();
		schedule(schedule_selector(SceneLayer::loadMapUpdate), 0.1f);
	}
	
}

//////////////////////////////////////////////////////////////////////////
void SceneLayer::removeMap()
{   
	CCLog("began to remove map :%d", m_lastMapId);
	LevelManager::sShareInstance()->deactiveCurrentLevel(true, true);
	GameAudioManager::sharedManager()->stopPlayBGM();
	CCLog("finish remove map :%d", m_lastMapId);
	m_LevelLayer = NULL;
}

void SceneLayer::removeUi()
{
	m_uiLayer->removeAllChildrenWithCleanup(true);
	//CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

void SceneLayer::clearCurScene()
{
	removeUi();
	removeMap();    
}
//////////////////////////////////////////////////////////////////////////


void SceneLayer::changeMap(int toMapId,KMapFromType fromMapType)
{    
	CCLog("change map to :%d", toMapId);
	if (m_curMapId == toMapId)
	{
		return ;
	}

	LevelManager::sShareInstance()->setCurrentLevelStatus(EChangeMap);
	GameAudioManager::sharedManager()->stopAllEffect();
   
	//
	m_lastMapId = m_curMapId;
	m_curMapId  = toMapId;
	m_fromMapType = fromMapType;

	setupMap();

	MainMenuLayer* mLayer = getMainMenuLayer();
	if (mLayer)
	{
		mLayer->ChangeMapUI(toMapId);
	}
}

//////////////////////////////////////////////////////////////////////////
/// 进入主城
void SceneLayer::enterMyRoom()
{
	// create main menu layer and add it to the SceneLayer as its child
	MainMenuLayer *mainMenu = getMainMenuLayer();
	if (!mainMenu)
	{
		mainMenu = (MainMenuLayer *)MainMenuLayer::create();
		m_uiLayer->addChild(mainMenu, SCENE_Z_MAIN_MENU, SCENE_Z_MAIN_MENU);
	}        

	int mapId = UserData::GetUserMapId();
	//by benyang: test
	changeMap(mapId, KMapFromMyRoom);	
}

void SceneLayer::resumeLastMap()
{
	changeMap(m_curMapId,KMapFromLast);
}

//////////////////////////////////////////////////////////////////////////
void SceneLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	// convert touch point
	CCTouch* touch = (CCTouch*)pTouches->anyObject();
	CCPoint touchPoint = this->convertTouchToNodeSpace(touch);
	touchPoint = LevelMultiResolution::sTransformWindowPointToMap(touchPoint);
    
	// let game manager unified process the touch
	GameManager::Get()->processTouchBegan(touchPoint);
}

void SceneLayer::setupLoadbar()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	if (_barFrame == NULL)
	{
		CCSprite* barFrame = CCSprite::create("load0001.png");
		_barFrame = barFrame;
		_barFrame->retain();

		barFrame->setPosition(ccp(visibleSize.width/2, visibleSize.height/6));
		m_pLoadingUI->addChild(barFrame,0,100);


		CCSprite* sp = CCSprite::create("load0002.png");
		CCProgressTimer *progressBar = CCProgressTimer::create(sp);
		barFrame->addChild(progressBar,-1,0);

		progressBar->setPosition(ccp(6,barFrame->getContentSize().height/2-4));
		progressBar->setType(kCCProgressTimerTypeBar);
		progressBar->setAnchorPoint(ccp(0,0));
		progressBar->setMidpoint(ccp(0,0));
		progressBar->setBarChangeRate(ccp(1,0));
		progressBar->setPercentage(0.0f);
	}

    _barFrame->setVisible(false);
}

#pragma mark -
#pragma mark realtimeUpdate
void SceneLayer::realtimeUpdateBar(float dt)
{
	struct cc_timeval currentTimeX;
	CCTime::gettimeofdayCocos2d(&currentTimeX, NULL);
    
    // get current time
	double currentTime = (currentTimeX.tv_sec) + (currentTimeX.tv_usec / 1000000.0);

	if(!m_lastTickTime )
		m_lastTickTime = currentTime;
    
	//determine the amount of time elapsed since our last update
	double frameTime = currentTime - m_lastTickTime;
	m_accumulator += frameTime;
    
	//update the world with the same seconds per update
	int tickCount = 0;
	while( m_accumulator > LOADINGTIME )
	{
		m_accumulator -= LOADINGTIME;
        //std::string msg = Localizatioin::getLocalization("M_UPDATEFULL_NETWORKFAILURE");
        //showmsg(msg.c_str());
		NotificationCenter::defaultCenter()->broadcast(GM_DOWNLOAD_MAP_FAIL, this);
		return;
	}
	m_lastTickTime = currentTime;
	CCLog("accumlator:%f\n", m_accumulator);

    if(ResoureUpdate::_downloadPercent < 100)
    {
        CCProgressTimer *progressBar = (CCProgressTimer*)_barFrame->getChildByTag(0);
        progressBar->setPercentage(ResoureUpdate::_downloadPercent);
    }
    else
    {
        CCProgressTimer *progressBar = (CCProgressTimer*)_barFrame->getChildByTag(0);
        progressBar->setPercentage(100);
        unschedule(schedule_selector(SceneLayer::realtimeUpdateBar));
        schedule(schedule_selector(SceneLayer::realtimeUpdateDone), 0.25f);
    }
}

void SceneLayer::realtimeUpdateDone(float dt)
{
    CCProgressTimer *progressBar = (CCProgressTimer*)_barFrame->getChildByTag(0);
    progressBar->setPercentage(0.0f);
    _barFrame->setVisible(false);
    progressBar->stopAllActions();
    
    if(m_pLoadingUI)
    {
        m_pLoadingUI->HideLoading();
        CCLog("loading ui hideloaoding\n");
    }
    
    float duration = 1.1f;
    CCLayerColor* l = CCLayerColor::create(ccc4(0,0,0,255));
    addChild(l,0,1000);
    
    CCFadeOut *fadeout = CCFadeOut::create(duration);
    l->runAction(fadeout);
    
    CCCallFunc *rc = CCCallFunc::create(this,callfunc_selector(SceneLayer::removeColorLayer));
    CCSequence *seq = (CCSequence*)CCSequence::create(CCDelayTime::create(duration),rc,NULL);
    runAction(seq);
    unschedule(schedule_selector(SceneLayer::realtimeUpdateDone));
    ResoureUpdate::sharedResoureUpdate()->setRunning(false);
}

#pragma mark -
#pragma mark normal state
void SceneLayer::loadResoure(int percent)
{
    _barFrame->setVisible(true);
	CCProgressTimer *progressBar = (CCProgressTimer*)_barFrame->getChildByTag(0);
	progressBar->setPercentage(percent);
}

void SceneLayer::hideloadbar_func(cocos2d::CCNode *sender)
{
	hideloadlayer();
}

void SceneLayer::removeColorLayer()
{
   this->removeChildByTag(1000,true);

   bool bMainLandLevel = MainLandManager::Get()->isMainLand(LevelManager::sShareInstance()->getCurMapId());
   if (bMainLandLevel)
   {
	   MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	   if (mLayer)
	   {
		   mLayer->GetGameUILayer()->showSpecialButtonEffect();
	   }
   }
}

void  SceneLayer::hideloading(float dt)
{
	unschedule(schedule_selector(SceneLayer::hideloading));
	hideloadlayer();
}

void  SceneLayer::hideloadlayer()
{
	CCProgressTimer *progressBar = (CCProgressTimer*)_barFrame->getChildByTag(0);
    progressBar->setPercentage(0.0f);
    _barFrame->setVisible(false);
    progressBar->stopAllActions();

	if(m_pLoadingUI)
	{
		m_pLoadingUI->HideLoading();
		CCLog("loading ui hideloaoding\n");
	}
    
    float duration = 1.1f;
    CCLayerColor* l = CCLayerColor::create(ccc4(0,0,0,255));
    addChild(l,0,1000);
    
    CCFadeOut *fadeout = CCFadeOut::create(duration);
    l->runAction(fadeout);
    
    CCCallFunc *rc = CCCallFunc::create(this,callfunc_selector(SceneLayer::removeColorLayer));
    CCSequence *seq = (CCSequence*)CCSequence::create(CCDelayTime::create(duration),rc,NULL);
    runAction(seq);
}