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
#include "PPVELayer.h"
#include "PVPLayer.h"
#include "MainMenuLayer.h"
#include "resources.h"
#include <stdlib.h>
#include <stdio.h>

#include "GameManager.h"
#include "ItemDragLayer.h"
#include "BattleUILayer.h"
#include "GameUILayer.h"
#include "BattleWinLayer.h"
#include "BackPackLayer.h"
#include "InstanceListLayer.h"
#include "CityListLayer.h"
#include "EquipmentUpgradeUILayer.h"
#include "TXGUIHeader.h"
#include "LevelManager.h"

#include "WaitingLayer.h"
/// ppve 
#include "GMessage.h"
#include "ChatToolbar.h"
#include "MessageBoxLayer.h"
#include "Localization.h"
#include "EquipMixLayer.h"
#include "AlchemyUILayer.h"
#include "MainLandManager.h"
#include "GameAudioManager.h"
#include "StoryInstanceDirector.h"
#include "BattleCoverLayer.h"
#include "TalentLayer.h"
#include "AutoOnHook.h"
#include "ShopUILayer.h"
#include "LuaTinkerManager.h"

using namespace TXGUI;


//////////////////////////////////////////////////////////////////////////
///  管理所有的UI图层，这里控制游戏中的所有的UI层
///  如装备层，
/*     战斗界面图层，
       背包图层...
	   PPVE图层...


*/   
///  本显示层，在游戏过程中，是不会被释放掉的，相当于游戏界面的总的管理器
///

MainMenuLayer::MainMenuLayer():
	damageValueLable(NULL)
{
	m_pCityListUI = NULL;
	m_pBattleCoverUI = NULL;
	m_pInstanceListUI = NULL;
	m_pBackPackUI = NULL;
	m_pTaskChatUI = NULL;
	m_pTaskListUI = NULL;
	m_pBattleUI = NULL;
	m_pGameUI = NULL;
	m_pBattleWinUI = NULL;
	m_equipmentUpgradeLayer = NULL;
	m_pUIMessage = NULL;
	m_pUIWaiting = NULL;
    
	//// PPVE , but don't create the ppve layer when init MainMenuLayer!!!!!
	m_pPPVELayer = NULL;
    m_pPVPLayer = NULL;
    m_pTalentLayer = NULL;
    m_pAutoOnHook = NULL;
    m_pShopUILayer = NULL;

	m_pChatToolbar = NULL;
	m_equipMixLayer = NULL;
	m_pAlchemyUILayer = NULL;
}

MainMenuLayer::~MainMenuLayer()
{
	CCLog("***************************MainMenuLayer::~MainMenuLayer()************************");
	HidePVPLayer(false);
	HidePPVELayer(false);
    HideTalentLayer(false);
    HideAutoOnHook(false);
    HideShopUILayer(false);
    
	UIManager::sharedManager()->setUIDefaultRoot(NULL);

	NotificationCenter::defaultCenter()->unregisterAllMsgObserver(this);

    if (sVecLayersInQuene)
        sVecLayersInQuene->clear();
	CC_SAFE_DELETE(sVecLayersInQuene);
}


void MainMenuLayer::CreateTaskListLayer()
{
	//if (m_pTaskListUI == 0)
	{
		m_pTaskListUI = TaskListLayer::create();
		this->addChild(m_pTaskListUI, Z_Order_Task);
		m_pTaskListUI->ShowTaskListLayer(true);
	}
}

void MainMenuLayer::DestroyTaskListLayer()
{
	m_pTaskListUI->removeFromParentAndCleanup(true);
	m_pTaskListUI = 0;
}

bool MainMenuLayer::init()
{
    if(!CCLayer::init())
    {
        return false;
    }

	/// Init UI Manager Default Root Node
	UIManager::sharedManager()->setUIDefaultRoot(this);
    
	setTouchEnabled(true);
   
	m_pDragLayer = ItemDragLayer::create();
	this->addChild(m_pDragLayer, Z_Order_DragLayer);

	/// only show Game UI
	m_pGameUI = GameUILayer::create();
	this->addChild(m_pGameUI, Z_Order_Normal);

	m_pBackPackUI = BackPackLayer::create();
	this->addChild(m_pBackPackUI,3);

	m_pTaskChatUI = TaskChatLayer::create();
	this->addChild(m_pTaskChatUI,4);

	//EquipmentUpgradeUILayer::setUpgradeColdTime(0);

	/// add more!
	NotificationCenter::defaultCenter()->registerAllMsgObserver(this);

	this->setKeypadEnabled(true);

	setChatToolbar(true,true,true);
    return true;
}

void MainMenuLayer::ccTouchesBegan( CCSet *pTouches, CCEvent *pEvent )
{
	CCLayer::ccTouchesBegan(pTouches, pEvent);
}

void MainMenuLayer::ccTouchesMoved( CCSet *pTouches, CCEvent *pEvent )
{
	CCLayer::ccTouchesMoved(pTouches, pEvent);
}

void MainMenuLayer::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	CCLayer::ccTouchCancelled(pTouch, pEvent);
}

void MainMenuLayer::ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent )
{
	CCLayer::ccTouchesEnded(pTouches, pEvent);
}

/// 设备不同的关卡上的UI应该如何配置
void MainMenuLayer::ChangeMapUI(int mapID)
{
	if (MainLandManager::Get()->isMainLand(mapID))
	{
		/// 是主城
		if (m_pBattleUI)
		{
			m_pBattleUI->removeFromParentAndCleanup(true);
			m_pBattleUI = NULL;
		}

		if (m_pGameUI)
			m_pGameUI->setVisible(true);

		if(m_pChatToolbar)
		{
			m_pChatToolbar->setVisible(true);
			setChatToolbar(true,true,true);
		}
	}
	else
	{
		if(!m_pBattleUI)
		{
			m_pBattleUI = BattleUILayer::create();
			this->addChild(m_pBattleUI,1);
		}

		if (m_pGameUI)
			m_pGameUI->setVisible(false);

		if(m_pChatToolbar)
		{
			m_pChatToolbar->setVisible(false);
		}
	}
	if(m_pBattleWinUI)
	{
		m_pBattleWinUI->removeFromParentAndCleanup(true);
		m_pBattleWinUI = NULL;
	}
	if(m_pBackPackUI)
	{
		m_pBackPackUI->setVisible(false);
	}
	if(m_pTaskChatUI)
	{
		m_pTaskChatUI->setVisible(false);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///          API
MainMenuLayer*  GetMainMenuLayer()
{
    if (GameManager::Get()->GetSceneLayer() == NULL)
        return NULL;
    
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	return mLayer;
}


ItemDragLayer* GetItemDragLayer()
{
    if (GameManager::Get()->GetSceneLayer() == NULL)
        return NULL;
    
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{
		return mLayer->GetItemDragLayer();
	}

	return NULL;
}

ItemDragLayer* MainMenuLayer::GetItemDragLayer(){
	return m_pDragLayer;
}

/// get battle ui layer
BattleUILayer* GetBattleUILayer()
{
    if (GameManager::Get()->GetSceneLayer() == NULL)
        return NULL;
    
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{
		return mLayer->GetBattleUILayer();
	}

	return NULL;
}


BattleUILayer* MainMenuLayer::GetBattleUILayer(){
	return m_pBattleUI;
}

void MainMenuLayer::HandleDamageNumberEffect(CCNode* parent,unsigned int damage,bool isCrit,bool isHarmful)
{
	if(!damageValueLable)
	{
		damageValueLable = DamageValueEffect::create();
		this->addChild(damageValueLable,0,0);
	}
	damageValueLable->HandleDamageNumberEffect(parent,damage,isCrit,isHarmful);
}

void MainMenuLayer::HandleAttackMissEffect(CCPoint parentPt)
{
	if(!damageValueLable)
	{
		damageValueLable = DamageValueEffect::create();
		this->addChild(damageValueLable,0,0);
	}
	damageValueLable->CreateMissLabel(parentPt);
}

void MainMenuLayer::HandleAttackBlockEffect(CCPoint parentPt)
{
	if(!damageValueLable)
	{
		damageValueLable = DamageValueEffect::create();
		this->addChild(damageValueLable,0,0);
	}
	damageValueLable->CreateBlockLabel(parentPt);
}

void MainMenuLayer::HandleComboIncrease(unsigned int incremental)
{
	if(m_pBattleUI)
	{
		m_pBattleUI->HandleComboIncrease(incremental);
	}
}

BattleWinLayer* MainMenuLayer::GetBattleWinLayer()
{
	if(!m_pBattleWinUI)
	{
		m_pBattleWinUI = BattleWinLayer::create();
		this->addChild(m_pBattleWinUI,2);
	}
	return m_pBattleWinUI;
}

BattleWinLayer* GetBattleWinLayer()
{
	if(GameManager::Get()->GetSceneLayer())
	{
		MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
		if (mLayer)
		{
			return mLayer->GetBattleWinLayer();
		}
	}

	return NULL;
}

/// get game ui layer
GameUILayer* GetGameUILayer()
{
	if(GameManager::Get()->GetSceneLayer())
	{
		MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
		if (mLayer)
		{
			return mLayer->GetGameUILayer();
		}
	}

	return NULL;
}

GameUILayer* MainMenuLayer::GetGameUILayer()
{
	return m_pGameUI;
}

BackPackLayer* MainMenuLayer::GetBackPackLayer()
{
	return m_pBackPackUI;
}

TaskChatLayer* MainMenuLayer::GetTaskChatLayer()
{
	return m_pTaskChatUI;
}

TaskListLayer* MainMenuLayer::GetTaskListLayer()
{
	return m_pTaskListUI;
}

BackPackLayer* GetBackPackLayer()
{
	if(GameManager::Get()->GetSceneLayer())
	{
		MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
		if (mLayer)
		{
			return mLayer->GetBackPackLayer();
		}
	}
	
	return NULL;
}

InstanceListLayer* MainMenuLayer::GetInstanceListLayer()
{
	if (NULL == m_pInstanceListUI)
	{
		m_pInstanceListUI = InstanceListLayer::create();
		this->addChild(m_pInstanceListUI,4);
	}

	return m_pInstanceListUI;
}

InstanceListLayer* GetInstanceListLayer()
{
	if(GameManager::Get()->GetSceneLayer())
	{
		MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
		if (mLayer)
		{
			return mLayer->GetInstanceListLayer();
		}
	}
	return NULL;
}

CityListLayer* MainMenuLayer::GetCityListLayer()
{
	if (NULL == m_pCityListUI)
	{
		m_pCityListUI = CityListLayer::create();
		this->addChild(m_pCityListUI,5);
	}

	return m_pCityListUI;
}

CityListLayer* GetCityListLayer()
{
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{
		return mLayer->GetCityListLayer();
	}
	return NULL;
}

BattleCoverLayer* MainMenuLayer::GetBattleCoverLayer()
{
	if (NULL == m_pBattleCoverUI)
	{
		m_pBattleCoverUI = BattleCoverLayer::create();
		this->addChild(m_pBattleCoverUI, 1000);
	}

	return m_pBattleCoverUI;
}

BattleCoverLayer* GetBattleCoverLayer()
{
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{
		return mLayer->GetBattleCoverLayer();
	}
	return NULL;
}

void MainMenuLayer::ShowEquipmentUpgradeUI(unsigned int coldTime)
{
	if(NULL == m_equipmentUpgradeLayer)
	{
		m_equipmentUpgradeLayer = EquipmentUpgradeUILayer::create();
		this->addChild(m_equipmentUpgradeLayer,5);
	}
	m_equipmentUpgradeLayer->setUpgradeColdTime(coldTime);
	if(!m_equipmentUpgradeLayer->isVisible())
	{
		m_equipmentUpgradeLayer->setVisible(true);
	}
	GameAudioManager::sharedManager()->playEffect(350001,false);
	MainMenuLayer::PushOneLayer(m_equipmentUpgradeLayer);
}

EquipmentUpgradeUILayer* MainMenuLayer::GetEquipmentUpgradeLayer()
{
	return m_equipmentUpgradeLayer;
}

EquipmentUpgradeUILayer* GetEquipmentUpgradeLayer()
{
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{
		return mLayer->GetEquipmentUpgradeLayer();
	}

	return NULL;
}

void MainMenuLayer::HideEquipmentUpgradeUI()
{
	if(m_equipmentUpgradeLayer)
	{
		//m_equipmentUpgradeLayer->setVisible(false);
		m_equipmentUpgradeLayer->removeFromParentAndCleanup(true);
		m_equipmentUpgradeLayer = NULL;
	}
}

/////////////////////////////pvp///////////////////////////////////
PVPLayer* GetPVPLayer()
{
	if(GameManager::Get()->GetSceneLayer())
	{
		MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
		if (mLayer)
		{
			return mLayer->ShowPVPLayer();
		}
	}
	
    
	return NULL;
}

void  RemovePVPLayer(bool showGameUI)
{
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{
		mLayer->HidePVPLayer(showGameUI);
	}
}

PVPLayer* MainMenuLayer::ShowPVPLayer()
{
	if (NULL == m_pPVPLayer)
	{
        m_pPVPLayer = new PVPLayer();
        m_pPVPLayer->init();
        this->addChild(m_pPVPLayer, 5);
		MainMenuLayer::PushOneLayer(m_pPVPLayer);
	}
    
	/// hide gaming ui
	if (m_pGameUI)
		m_pGameUI->setVisible(false);
    
	return m_pPVPLayer;
}

SpriteElfLayer* MainMenuLayer::ShowSpriteElfLayer()
{
	SpriteElfLayer* pLayer = SpriteElfLayer::create();
	if (NULL != pLayer)
	{
		this->addChild(pLayer, 5,8);
		return pLayer;
	}
	return pLayer;
}

void MainMenuLayer::HidePVPLayer(bool showGameUI)
{
	if(m_pPVPLayer)
	{
		if(!m_pPVPLayer->IsOnCloseLayerCallBack())
			MainMenuLayer::RemoveOneLayer(m_pPVPLayer);
		m_pPVPLayer->removeFromParentAndCleanup(true);
        
		delete m_pPVPLayer;
		m_pPVPLayer = NULL;
        
		//m_pPVPLayer->removeFromParentAndCleanup(true);
		//m_pPVPLayer = NULL;
	}
    
	/// show gaming ui
	if (m_pGameUI)
		m_pGameUI->setVisible(showGameUI);
}

bool MainMenuLayer::IsInPVPModule()
{
	if (m_pPVPLayer != NULL)
		return true;
	return false;
}

/////////////////////////////Talent Layer//////////////////////////
TalentLayer* GetTalentLayer()
{
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{
		return mLayer->ShowTalentLayer();
	}
    
	return NULL;
}

void  RemoveTalentLayer(bool showGameUI)
{
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{
		mLayer->HideTalentLayer(showGameUI);
	}
}

TalentLayer* MainMenuLayer::ShowTalentLayer()
{
	if (NULL == m_pTalentLayer)
	{
        m_pTalentLayer = new TalentLayer();
        m_pTalentLayer->init();
        this->addChild(m_pTalentLayer, 5);
		MainMenuLayer::PushOneLayer(m_pTalentLayer);
	}
    
    ShowChatBar(true, -1);
    
	/// hide gaming ui
	//if (m_pGameUI)
		//m_pGameUI->setVisible(false);
    
	return m_pTalentLayer;
}

void MainMenuLayer::HideTalentLayer(bool showGameUI)
{
	if(m_pTalentLayer)
	{
		if(!m_pTalentLayer->IsOnCloseLayerCallBack())
			MainMenuLayer::RemoveOneLayer(m_pTalentLayer);
		m_pTalentLayer->removeFromParentAndCleanup(true);
        
		delete m_pTalentLayer;
		m_pTalentLayer = NULL;
	}
    
    //ShowChatBar(true,  -1);
	/// show gaming ui
	//if (m_pGameUI)
		//m_pGameUI->setVisible(showGameUI);
}

bool MainMenuLayer::IsInTalentModule()
{
	if (m_pTalentLayer != NULL)
		return true;
	return false;
}

/////////////////////////////AutoOnHook////////////////////////////
AutoOnHook* GetAutoOnHook()
{
    if(GameManager::Get()->GetSceneLayer())
    {
        MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
        if (mLayer)
        {
            return mLayer->ShowAutoOnHook();
        }
    }
	return NULL;
}

void  RemoveAutoOnHook(bool showGameUI)
{
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{
		mLayer->HideAutoOnHook(showGameUI);
	}
}

AutoOnHook* MainMenuLayer::ShowAutoOnHook()
{
	if (NULL == m_pAutoOnHook)
	{
        m_pAutoOnHook = new AutoOnHook();
        m_pAutoOnHook->init();
        this->addChild(m_pAutoOnHook, 5);
		MainMenuLayer::PushOneLayer(m_pAutoOnHook);
	}
    
	/// hide gaming ui
	if (m_pGameUI)
		m_pGameUI->setVisible(false);
    
	return m_pAutoOnHook;
}

void MainMenuLayer::HideAutoOnHook(bool showGameUI)
{
	if(m_pAutoOnHook)
	{
		if(!m_pAutoOnHook->IsOnCloseLayerCallBack())
			MainMenuLayer::RemoveOneLayer(m_pAutoOnHook);
		m_pAutoOnHook->removeFromParentAndCleanup(true);
        
		delete m_pAutoOnHook;
		m_pAutoOnHook = NULL;
	}
    
	/// show gaming ui
	if (m_pGameUI)
		m_pGameUI->setVisible(showGameUI);
}

bool MainMenuLayer::IsInAutoOnHookModule()
{
	if (m_pAutoOnHook != NULL)
		return true;
	return false;
}
/////////////////////////////ShopUILayer///////////////////////////

ShopUILayer* GetShopUILayer()
{
    if(GameManager::Get()->GetSceneLayer())
    {
        MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
        if (mLayer)
        {
            return mLayer->ShowShopUILayer();
        }
    }
	return NULL;
}

void  RemoveShopUILayer(bool showGameUI)
{
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{
		mLayer->HideShopUILayer(showGameUI);
	}
}

ShopUILayer* MainMenuLayer::ShowShopUILayer()
{
	if (NULL == m_pShopUILayer)
	{
        m_pShopUILayer = new ShopUILayer();
        m_pShopUILayer->init();
        this->addChild(m_pShopUILayer, 5);
		MainMenuLayer::PushOneLayer(m_pShopUILayer);
	}
    
	/// hide gaming ui
	if (m_pGameUI)
		m_pGameUI->setVisible(false);
    
	return m_pShopUILayer;
}

void MainMenuLayer::HideShopUILayer(bool showGameUI)
{
	if(m_pShopUILayer)
	{
		if(!m_pShopUILayer->IsOnCloseLayerCallBack())
			MainMenuLayer::RemoveOneLayer(m_pShopUILayer);
		m_pShopUILayer->removeFromParentAndCleanup(true);
        
		delete m_pShopUILayer;
		m_pShopUILayer = NULL;
	}
    
	//show gaming ui
	if (m_pGameUI)
		m_pGameUI->setVisible(showGameUI);
}

bool MainMenuLayer::IsInShopUILayerModule()
{
	if (m_pShopUILayer != NULL)
		return true;
	return false;
}

/////////////////////////////ppve//////////////////////////////////
PPVELayer* GetPPVELayer()
{
	if(GameManager::Get()->GetSceneLayer())
	{
		MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
		if (mLayer)
		{
			return mLayer->ShowPPVELayer();
		}
	}
	
	return NULL;
}

void  RemovePPVELayer(bool showGameUI)
{
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{
		mLayer->HidePPVELayer(showGameUI);
	}
}

PPVELayer* MainMenuLayer::ShowPPVELayer()
{
	if (NULL == m_pPPVELayer)
	{
		//m_pPPVELayer = PPVELayer::create();
		m_pPPVELayer = new PPVELayer();
		m_pPPVELayer->init();
		this->addChild(m_pPPVELayer, 5);
		MainMenuLayer::PushOneLayer(m_pPPVELayer);
	}

	/// hide gaming ui
	if (m_pGameUI)
		m_pGameUI->setVisible(false);
    
	return m_pPPVELayer;
}

void MainMenuLayer::HidePPVELayer(bool showGameUI)
{
	if(m_pPPVELayer)
	{
		if(!m_pPPVELayer->IsOnCloseLayerCallBack())
			MainMenuLayer::RemoveOneLayer(m_pPPVELayer);
		//m_pPPVELayer->setVisible(false);
		m_pPPVELayer->removeFromParentAndCleanup(true);
		
		delete m_pPPVELayer;

		m_pPPVELayer = NULL;
	}

	/// show gaming ui
	if (m_pGameUI)
		m_pGameUI->setVisible(showGameUI);
}

bool MainMenuLayer::IsInPPVEModule()
{
	if (m_pPPVELayer != NULL)
		return true;

	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////    toolbar

ChatToolbar* GetChatToolbar()
{
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{
		return mLayer->GetChatToolbar();
	}

	return NULL;
}

//void SetChatToolLayer(bool isChatHide,bool isFunctionHide,bool isExtraHide,int order)
//{
//	if (NULL == GameManager::Get()->GetSceneLayer())
//		return;
//
//	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
//	if (mLayer)
//	{
//		 mLayer->setChatToolbar(isChatHide,isFunctionHide,isExtraHide,order);
//	}
//}

void ShowChatBar(bool isExtrVisible,int order)
{
	if (NULL == GameManager::Get()->GetSceneLayer())
		return;

	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{
		mLayer->setChatToolbar(true,true,isExtrVisible,order);
	}
}

MainMenuLayer* MainMenuLayer::getMainMenuLayer()
{
	if (GameManager::Get()->GetSceneLayer() != NULL)
	{
		return GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	}
	return NULL;
}

ChatToolbar* MainMenuLayer::GetChatToolbar()
{
	if (NULL == m_pChatToolbar)
	{
		m_pChatToolbar = ChatToolbar::create();		
		this->addChild(m_pChatToolbar,-1);
	}

	return m_pChatToolbar;
}

void MainMenuLayer::setChatToolbar(bool isChatVisible,bool isFunctionVisible,bool isExtraVisible,int order)
{
	if(!m_pChatToolbar)
	{
		m_pChatToolbar = ChatToolbar::create();
		this->addChild(m_pChatToolbar,order);
	}
	if (m_pChatToolbar)
	{
		m_pChatToolbar->setChatBarVisible(isChatVisible,isFunctionVisible,isExtraVisible);
		if(m_pGameUI)
		{
			m_pGameUI->setVisible(isExtraVisible);
		}
		this->reorderChild(m_pChatToolbar,order);
	}
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////
/////                消息响应函数, 这里可以处理一些系统消息
///////
void MainMenuLayer::onBroadcastMessage(BroadcastMessage* msg)
{
	switch(msg->message)
	{
	case GM_CLOSE_PPVELAYER:
		HidePPVELayer(true);
		break;
            
    case GM_CLOSE_PVPLAYER:
        HidePVPLayer(true);
        break;
            
    case GM_CLOSE_TALENTLAYER:
        HideTalentLayer(true);
        break;
            
    case GM_CLOSE_AUTOONHOOK:
        HideAutoOnHook(true);
        //GetInstanceListLayer()->openInstanceList();
        break;
            
	case GM_APPLICATION_ENTER_BACKGROUND:
		/// game enter background now!
		/// check whether player is in mainland or not
		break;
	}
}
/////////////////////////////////////////////////////////////////////////////

UIMessageLayer* MainMenuLayer::getUIMessageLayer()
{
	if(NULL == m_pUIMessage)
	{
		m_pUIMessage = UIMessageLayer::create();
		addChild(m_pUIMessage,90);
	}

	return m_pUIMessage;
}

void ShowMessage(const char* message,const ccColor3B& color)
{
	if(GameManager::Get()->GetSceneLayer())
	{
		MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
		if (mLayer)
		{
			UIMessageLayer* uiMessageLayer = mLayer->getUIMessageLayer();
			if(uiMessageLayer)
			{
				uiMessageLayer->ShowMessage(message,color);
			}
		}
	}
	
}

void MainMenuLayer::PushOneLayer(CCLayer *pLayer,std::string param_1 /* = "" */,std::string param_2 /* = "" */)
{
	if (sVecLayersInQuene == 0)
	{
		sVecLayersInQuene = new std::vector<CCLayer*>();
	}
	for (std::vector<CCLayer*>::iterator iter = sVecLayersInQuene->begin();
		iter != sVecLayersInQuene->end();iter++)
	{
		CCLayer* layer = (*iter);
		if (layer == pLayer)
		{
			return ;
		}
	}
	for (std::vector<CCLayer*>::iterator iter = sVecLayersInQuene->begin();
		 iter != sVecLayersInQuene->end();iter++)
	{
		CCLayer* layer = (*iter);
		if (layer->getTag() != kCCNodeTagInvalid)
		{
			LuaTinkerManager::Get()->callLuaFunc<bool>("Script/MainMenuUILayer.lua", "HideOneLayerByTag", layer->getTag());
		}	
		layer->closeLayerCallBack();
			
	}

	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	NotificationCenter::defaultCenter()->broadcast(GM_LUA_LAYER_CLOSE,mLayer,param_1,param_2);

	GameConfigFromLuaManager::Get()->PushLayerInstanceToLua(pLayer);

	sVecLayersInQuene->clear();
	sVecLayersInQuene->push_back(pLayer);
}

void MainMenuLayer::ClearLayersInQueneData()
{
	if (sVecLayersInQuene == 0 || sVecLayersInQuene->size() == 0)
	{
		return ;
	}	
	sVecLayersInQuene->clear();
}

void MainMenuLayer::RemoveOneLayer(CCLayer *pLayer)
{
	if (sVecLayersInQuene == 0 || sVecLayersInQuene->size() == 0)
	{
		return ;
	}	
	for (std::vector<CCLayer*>::iterator iter = sVecLayersInQuene->begin();
		iter != sVecLayersInQuene->end();iter++)
	{
		CCLayer* layer = (*iter);
		if (pLayer == layer)
		{
			sVecLayersInQuene->erase(iter);
			return ;
		}
	}
}

std::vector<CCLayer*>* MainMenuLayer::sVecLayersInQuene = 0;
WaitingLayer* MainMenuLayer::getWaitingLayer()
{
	if(NULL == m_pUIWaiting)
	{
		m_pUIWaiting = WaitingLayer::create();
		addChild(m_pUIWaiting, Z_Order_WaitingLayer);
	}

	return m_pUIWaiting;
}


void ShowWaitingLayer(bool bShowRightNow /* = true */,float sumTimer /* = 0.3 */)
{
	if (GetMainMenuLayer())
	{
		GetMainMenuLayer()->getWaitingLayer()->ShowWaiting(bShowRightNow,sumTimer);
	}
}



void HideWaitingLayer()
{
	if (GetMainMenuLayer())
	{
		GetMainMenuLayer()->getWaitingLayer()->HideWaiting();
	}
}

void MainMenuLayer::OkBtnClick(CCObject* obj)
{
	CCDirector::sharedDirector()->end();
}

void MainMenuLayer::CancelBtnClick(CCObject* obj)
{
	CCLog("MainMenuLayer::CancelBtnClick");
}

void MainMenuLayer::keyBackClicked()
{
	bool bMainLandLevel = MainLandManager::Get()->isMainLand(LevelManager::sShareInstance()->getCurMapId());
	if (bMainLandLevel)
	{
		std::string content = Localizatioin::getLocalization("S_Message_common_content");
		TXGUI::MessageBox::Show(content.c_str(),this,menu_selector(MainMenuLayer::OkBtnClick),menu_selector(MainMenuLayer::CancelBtnClick));
	}
}

void MainMenuLayer::keyMenuClicked()
{
	CCLog("keyMenuClicked");
}

EquipMixLayer* MainMenuLayer::ShowEquipMixLayer()
{
	if(m_pBackPackUI)
	{
		m_pBackPackUI->setVisible(false);
	}
	if(!m_equipMixLayer)
	{
		m_equipMixLayer = EquipMixLayer::create();
		addChild(m_equipMixLayer,6);
		GameAudioManager::sharedManager()->playEffect(350001,false);
		PushOneLayer(m_equipMixLayer);
	}
	return m_equipMixLayer;
}

void MainMenuLayer::HideEquipMixLayer()
{
	if(m_equipMixLayer)
	{
		m_equipMixLayer->removeFromParentAndCleanup(true);
		m_equipMixLayer = NULL;

		/*if(m_pBackPackUI)
		{
			m_pBackPackUI->openBackPack();
		}*/
	}
}

EquipMixLayer* ShowEquipMixLayer()
{
	if(GameManager::Get()->GetSceneLayer())
	{
		MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
		if(mLayer)
		{
			return mLayer->ShowEquipMixLayer();
		}
	}
	return NULL;
}

EquipMixLayer* MainMenuLayer::GetCurrentEquipMixLayer()
{
	return m_equipMixLayer;
}

EquipMixLayer* GetCurrentEquipMixLayer()
{
	if(GameManager::Get()->GetSceneLayer())
	{
		MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
		if(mLayer)
		{
			return mLayer->GetCurrentEquipMixLayer();
		}
	}
	return NULL;
}

void HideEquipMixLayer()
{
	if(GameManager::Get()->GetSceneLayer())
	{
		MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
		if(mLayer)
		{
			mLayer->HideEquipMixLayer();
		}
	}
}

AlchemyUILayer* MainMenuLayer::ShowAlchemyUILayer()
{
	
	if(!m_pAlchemyUILayer)
	{
		m_pAlchemyUILayer = AlchemyUILayer::create();
		addChild(m_pAlchemyUILayer,8);
		GameAudioManager::sharedManager()->playEffect(350001,false);
		PushOneLayer(m_pAlchemyUILayer);
	}
	ShowChatBar(false);
	return m_pAlchemyUILayer;
}

AlchemyUILayer* MainMenuLayer::GetCurrentAlchemyLayer()
{
	if(m_pAlchemyUILayer)
	{
		return m_pAlchemyUILayer;
	}
	else
	{
		return NULL;
	}
}

void MainMenuLayer::HideAlchemyUILayer()
{
	if(m_pGameUI)
	{
		m_pGameUI->setVisible(true);
	}
	if(m_pAlchemyUILayer)
	{
		m_pAlchemyUILayer->removeFromParentAndCleanup(true);
		m_pAlchemyUILayer = NULL;
	}
}

AlchemyUILayer* ShowAlchemyUILayer()
{
	if(GameManager::Get()->GetSceneLayer())
	{
		MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
		if(mLayer)
		{
			return mLayer->ShowAlchemyUILayer();
		}
	}
	
	return NULL;
}

AlchemyUILayer* GetCurrentAlchemyLayer()
{
	if(GameManager::Get()->GetSceneLayer())
	{
		MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
		if(mLayer)
		{
			return mLayer->GetCurrentAlchemyLayer();
		}
	}
	return NULL;
}

void HideAlchemyUILayer()
{
	if(GameManager::Get()->GetSceneLayer())
	{
		MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
		if(mLayer)
		{
			mLayer->HideAlchemyUILayer();
		}
	}
}

void MainMenuLayer::DarkEffectOver()
{
	StoryInstanceDirector::Get()->CreateMapObjects();	
}

const char* MainMenuLayer::GetNumByFormat(unsigned int num)
{
	char numStr[20];
	if(num >= 100000000)
	{
		unsigned int m = num / 1000000;
		sprintf(numStr,"%dm",m);
	}
	else if(num >= 100000)
	{
		unsigned int k = num / 1000;
		sprintf(numStr,"%dk",k);
	}
	else
	{
		sprintf(numStr,"%d",num);
	}
	CCString* pRet = CCString::create(numStr);
	return pRet->m_sString.c_str();
}