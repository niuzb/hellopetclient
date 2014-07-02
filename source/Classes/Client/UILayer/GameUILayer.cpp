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
#include "GameUILayer.h"
#include "resources.h"
#include <stdlib.h>
#include <stdio.h>

#include "XLogicManager.h"
#include "GameManager.h"
#include "UserData.h"
#include "LevelDefine.h"
#include "UIManager.h"
#include "TXGUIHeader.h"
#include "Define.h"
#include "GameFontManager.h"
#include "CrossUtil.h"

#include "SpriteSeer.h"
#include "ParticleManager.h"
#include "GameAudioManager.h"
#include "BackPackLayer.h"
#include "MainMenuLayer.h"

#include "ItemBase.h"
#include "EquipmentItem.h"
#include "GameConfigFromLuaManager.h"
#include "HSJoystick.h"
#include "GameDataManager.h"
#include "TaskManager.h"
#include "Localization.h"
#include "CityListLayer.h"
#include "NotificationCenter.h"
#include "GMessage.h"
#include "SpriteElfConfigFromLua.h"
#include "CCLuaEngine.h"

#include "particle_manager.h"
#include "GameResourceManager.h"
#include "MessageBoxLayer.h"

#include "particle_manager.h"
#include "TipMgr.h"
#include "TalentLayer.h"
#include "LuaTinkerManager.h"

using namespace TXGUI;

//////////////////////////////////////////////////////////////////////////
///  
///  
///

GameUILayer::GameUILayer()
{
	m_bPuckered = false;
	m_pBtnShrink = NULL;
}

GameUILayer::~GameUILayer()
{
	CCLog("GameUILayer::~GameUILayer()");
	UIManager::sharedManager()->RemoveUILayout("MainMenu");
	NotificationCenter::defaultCenter()->unregisterAllMsgObserver(this);
}

bool GameUILayer::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    
	setTouchEnabled(true);

	UIManager *manager = UIManager::sharedManager();
	UILayout* testLayout = manager->CreateUILayoutFromFile("UIplist/MainMenu.plist",this,  "MainMenu");
    CCAssert(testLayout,"GameUILayer create ERROR");

	manager->RegisterMenuHandler("MainMenu","GameUILayer::OnButtonBag",
		menu_selector(GameUILayer::OnButtonBag), this);
    
    manager->RegisterMenuHandler("MainMenu","GameUILayer::OnButtonTalent",
                                 menu_selector(GameUILayer::OnButtonTalent), this);

	manager->RegisterMenuHandler("MainMenu","GameUILayer::OnButtonSetting",
		menu_selector(GameUILayer::OnButtonSetting), this);
	manager->RegisterMenuHandler("MainMenu","GameUILayer::OnButtonShrink",
		menu_selector(GameUILayer::OnButtonShrink), this);
	manager->RegisterMenuHandler("MainMenu","GameUILayer::OnButtonUpgrade",
		menu_selector(GameUILayer::OnButtonUpgrade), this);
	manager->RegisterMenuHandler("MainMenu","GameUILayer::OnButtonAlchemy",
		menu_selector(GameUILayer::OnButtonAlchemy), this);

	manager->RegisterMenuHandler("MainMenu","GameUILayer::OnButtonActivity",
		menu_selector(GameUILayer::OnButtonActivity), this);
    
    manager->RegisterMenuHandler("MainMenu","GameUILayer::OnButtonReWard",
                                 menu_selector(GameUILayer::OnButtonReWard), this);

	manager->RegisterMenuHandler("MainMenu","GameUILayer::OnButtonFairy",
		menu_selector(GameUILayer::OnButtonFairy), this);

	manager->RegisterMenuHandler("MainMenu","GameUILayer::OnButtonInstanceClick",
		menu_selector(GameUILayer::OnButtonInstanceClick), this);

	manager->RegisterMenuHandler("MainMenu","GameUILayer::OnButtonTask",
		menu_selector(GameUILayer::OnButtonTask), this);

	manager->RegisterMenuHandler("MainMenu","GameUILayer::OnButtonRank",
		menu_selector(GameUILayer::OnButtonRank), this);	

	manager->RegisterMenuHandler("MainMenu","GameUILayer::OnHeadShotClick",
		menu_selector(GameUILayer::OnHeadShotClick), this);		
	
	UILayout* layout = manager->getUILayout("MainMenu");
	
    //MapButtonPointsH(layout, "button_talent");
	MapButtonPointsH(layout, "button_bag");
	MapButtonPointsH(layout, "button_fairy");
	MapButtonPointsH(layout, "button_dailytask");
	MapButtonPointsH(layout, "button_alchemy");
	MapButtonPointsH(layout, "button_enchase");
	MapButtonPointsH(layout, "button_communicate");
	MapButtonPointsW(layout, "button_rank");
	MapButtonPointsW(layout, "button_setting");
    

	if (layout)
	{
		UIButton* btn = layout->FindChildObjectByName<TXGUI::UIButton>("button_shrink");
		if (btn)
		{
			m_pBtnShrink = btn;
			m_ptDestShrink = btn->getWorldPosition();
		}

		UIPicture* pic = layout->FindChildObjectByName<UIPicture>("iconHeadShot");
		if(pic)
		{
			ASprite *as = AspriteManager::getInstance()->getAsprite(KICON_BIN); 
			const char* headIconName = LuaTinkerManager::Get()->getLuaConfig<const char *>("characterString", "Characters", UserData::GetUserType(), "HeadPicture");
			int idx = getResourceIDByName(headIconName);
			CCPoint pt;
			CCSprite * lockPic = as->getSpriteFromFrame_Middle( idx, 0, pt);
			if(lockPic)
			{
				pic->setSprite(lockPic);
			}	
		}
	}
	resetPlayerGoldLabel();
	resetPlayerDiamondLabel();
	resetPlayerReputationLabel();
	resetPlayerStaminaLabel();
    setPlayerLevel();

    
	NotificationCenter::defaultCenter()->registerAllMsgObserver(this);
    return true;
}

void GameUILayer::UpdateTaskUpRightIcon(std::string icon_name,eTaskState state /* = kType_TASK_UNKNOW */)
{
	UILayout* layout = UIManager::sharedManager()->getUILayout("MainMenu");
	UIButton *pBtn = layout->FindChildObjectByName<UIButton>("button_instance");
	if(pBtn)
	{
		ASprite *as = AspriteManager::getInstance()->getAsprite(KICON_BIN); 
		int idx = getResourceIDByName(icon_name.c_str());
		CCPoint pt;
		CCSprite * lockPic = as->getSpriteFromFrame_Middle( idx, 0, pt);
		if(lockPic)
		{
			if(icon_name.compare("map_ui_system_icon_FRAME_ICON_INSTANCE") != 0)
			{
				CCNode* particle = ParticleManagerX::sharedManager()->getParticles_uieffect("particle_effect_taskguide");
				if(particle != NULL)
				{
					CCNode* child = lockPic->getChildByTag(100);
					if(child)
					{
						child->removeFromParentAndCleanup(true);
						child = NULL;
					}
					lockPic->addChild(particle,100,100);
					//particle->setPosition(CCPointZero);
					particle->setPosition(ccp(lockPic->getContentSize().width * 0.5,lockPic->getContentSize().height * 0.5));
				}
			}
			pBtn->setIconSprite(lockPic);
		}
	}
}

void GameUILayer::MapButtonPointsH(UILayout* layout, const char * szName)
{
    if (layout)
	{
		TXGUI::UIButton* btn = layout->FindChildObjectByName<TXGUI::UIButton>(szName);
		if (btn)
		{
			CCPoint pt = btn->getWorldPosition();
			this->m_mapBttonPointH[btn] = pt;
		}
	}
}

/// pucker buttons to right bottom corner
void   GameUILayer::PuckerButtonsH(CCPoint ptDest)
{
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();

	map<TXGUI::UIButton*, CCPoint>::iterator it = m_mapBttonPointH.begin();
	for( ; it != m_mapBttonPointH.end(); it++)
	{
		TXGUI::UIButton* btn = it->first;
		CCPoint pt0 = it->second;
		pt0.x  = ptDest.x - pt0.x;
		pt0.y  = ptDest.y - pt0.y;
		CCActionInterval* actionMove = CCMoveBy::create(0.3f, pt0);
		CCActionInterval* actionFade = CCFadeOut::create(0.3f);
		CCSpawn* FirstAction = CCSpawn::createWithTwoActions(actionFade,actionMove);
		CCCallFuncN* hideFun =  CCCallFuncN::create(this,callfuncN_selector(GameUILayer::HideButton));

		btn->getAnimationNode()->runAction(CCSequence::create(FirstAction, hideFun, NULL));
	}

	m_bPuckered =  true;
}

/// un pucker buttons from right bottom corner
void  GameUILayer::UnPuckerButtonsH()
{
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();

	map<TXGUI::UIButton*, CCPoint>::iterator it = m_mapBttonPointH.begin();
	for( ; it != m_mapBttonPointH.end(); it++)
	{
		TXGUI::UIButton* btn = it->first;

		CCPoint ptDest = it->second;
		CCPoint pt0 = btn->getWorldPosition();
		pt0.x  = ptDest.x - pt0.x - 30;
		pt0.y  = ptDest.y - pt0.y;
		CCActionInterval* actionMove = CCMoveBy::create(0.3f, pt0);
		CCActionInterval* actionFade = CCFadeIn::create(0.3f);
		CCActionInterval* actionMoveX1 = CCMoveBy::create(0.1f, CCPoint(5, 0));
		CCActionInterval* actionMoveX2 = CCMoveBy::create(0.1f, CCPoint(25, 0));
		CCSpawn* FirstAction = CCSpawn::createWithTwoActions(actionMove, actionFade );
		CCCallFuncN* showFun =  CCCallFuncN::create(this,callfuncN_selector(GameUILayer::ShowButton));

		btn->getAnimationNode()->runAction(CCSequence::create(showFun, FirstAction, actionMoveX1, actionMoveX2, NULL));
	}

	m_bPuckered = false;
}


void GameUILayer::MapButtonPointsW(UILayout* layout, const char * szName)
{
	if (layout)
	{
		TXGUI::UIButton* btn = layout->FindChildObjectByName<TXGUI::UIButton>(szName);
		if (btn)
		{
			CCPoint pt = btn->getWorldPosition();
			this->m_mapBttonPointW[btn] = pt;
		}
	}
}

/// pucker buttons to right bottom corner
void   GameUILayer::PuckerButtonsW(CCPoint ptDest)
{
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();

	map<TXGUI::UIButton*, CCPoint>::iterator it = m_mapBttonPointW.begin();
	for( ; it != m_mapBttonPointW.end(); it++)
	{
		TXGUI::UIButton* btn = it->first;
		CCPoint pt0 = it->second;
		pt0.x  = ptDest.x - pt0.x;
		pt0.y  = ptDest.y - pt0.y;
		CCActionInterval* actionMove = CCMoveBy::create(0.3f, pt0);
		CCActionInterval* actionFade = CCFadeOut::create(0.3f);
		CCSpawn* FirstAction = CCSpawn::createWithTwoActions(actionFade,actionMove);
		CCCallFuncN* hideFun =  CCCallFuncN::create(this,callfuncN_selector(GameUILayer::HideButton));
		btn->getAnimationNode()->runAction(CCSequence::create(FirstAction, hideFun, NULL));
	}

	m_bPuckered = true;
}

/// un pucker buttons from right bottom corner
void  GameUILayer::UnPuckerButtonsW()
{
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();

	map<TXGUI::UIButton*, CCPoint>::iterator it = m_mapBttonPointW.begin();
	for( ; it != m_mapBttonPointW.end(); it++)
	{
		TXGUI::UIButton* btn = it->first;

		CCPoint ptDest = it->second;
		CCPoint pt0 = btn->getWorldPosition();
		pt0.x  = ptDest.x - pt0.x;
		pt0.y  = ptDest.y - pt0.y + 30;
		CCActionInterval* actionMove = CCMoveBy::create(0.3f, pt0);
		CCActionInterval* actionFade = CCFadeIn::create(0.3f);
		CCActionInterval* actionMoveX1 = CCMoveBy::create(0.1f, CCPoint(0, -5));
		CCActionInterval* actionMoveX2 = CCMoveBy::create(0.1f, CCPoint(0, -25));
		CCSpawn* FirstAction = CCSpawn::createWithTwoActions(actionMove, actionFade );
		CCCallFuncN* showFun =  CCCallFuncN::create(this,callfuncN_selector(GameUILayer::ShowButton));

		btn->getAnimationNode()->runAction(CCSequence::create(showFun, FirstAction, actionMoveX1, actionMoveX2, NULL));
	}

	m_bPuckered = false;
}

void GameUILayer::HideButton(CCNode* btn)
{
	if (btn)
	{
		btn->setVisible(false);
	}
}

void GameUILayer::ShowButton(CCNode* btn)
{
	if (btn)
	{
		btn->setVisible(true);
	}
}

void GameUILayer::setVisible(bool visible)
{
	CCLayer::setVisible(visible);

	/// hide / show UILayerOut
	UIManager *manager = UIManager::sharedManager();
	UILayout* layout = manager->getUILayout("MainMenu");
	if (layout)
	{
		layout->setVisible(visible);
	}

	/// fold shrink buttons
	//this->PuckerButtons();
}

extern long long millisecondNow();

void GameUILayer::PuckerButtons()
{
	
	if (!m_bPuckered)
	{
		PuckerButtonsH(m_ptDestShrink);
		PuckerButtonsW(m_ptDestShrink);
		CCActionInterval* actionRotate = CCRotateTo::create(0.3f, 180.0f);
		m_pBtnShrink->getAnimationNode()->runAction(actionRotate);
	}
}

void GameUILayer::OnButtonShrink(CCObject* sender)
{
	CCLog("GameUILayer::OnButtonShrink");

	static long  long nLastClickTime = 0;
    long long vTime = millisecondNow();
	if (vTime - nLastClickTime < 0.5 * 1000)
	{
		return;
	}

	nLastClickTime = vTime;

	if (!m_bPuckered)
	{
		PuckerButtonsH(m_ptDestShrink);
		PuckerButtonsW(m_ptDestShrink);
		CCActionInterval* actionRotate = CCRotateTo::create(0.3f, 180.0f);
		m_pBtnShrink->getAnimationNode()->runAction(actionRotate);
	}
	else
	{
		UnPuckerButtonsH();
		UnPuckerButtonsW();
		CCActionInterval* actionRotate = CCRotateTo::create(0.3f, 0);
		m_pBtnShrink->getAnimationNode()->runAction(actionRotate);
	}
}

void GameUILayer::OnButtonBag(CCObject *sender)
{
	CCLog("GameUILayer::OnButtonBag");
	stopHeroMove();
	BackPackLayer* layer = GetBackPackLayer();
	if(layer)
	{
		layer->onBagButtonClicked();
	}
}

void GameUILayer::OnButtonTalent(cocos2d::CCObject *sender)
{
    CCLog("gameUIlayer on btton\n");
	stopHeroMove();
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{
        mLayer->ShowTalentLayer();
	}
}


void GameUILayer::OnButtonSetting(CCObject *sender)
{
	CCLog("GameUILayer::OnButtonSetting");
	stopHeroMove();
	string toJoy = Localizatioin::getLocalization("T_operator_text_1");
	string toMouse = Localizatioin::getLocalization("T_operator_text_2");

	Move_Type type = GameDataManager::Get()->getHeroMoveType();

	switch (type)
	{
		case MOVE_BY_JOY:
			ShowMessage(toMouse.c_str());
			GameDataManager::Get()->setHeroMoveType(MOVE_BY_MOUSE);
			break;

		case MOVE_BY_MOUSE:
			ShowMessage(toJoy.c_str());			
			GameDataManager::Get()->setHeroMoveType(MOVE_BY_JOY);
			break;
            
		default:
			break;
	}
}

void GameUILayer::OnButtonUpgrade(CCObject* sender)
{
	stopHeroMove();
	OnlineNetworkManager::sShareInstance()->sentEquipUpgradeMessage();
}


void GameUILayer::OnButtonActivity(CCObject* sender)
{
	stopHeroMove();
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{
		mLayer->ShowPPVELayer();
	}
}

void GameUILayer::OnButtonFairy(CCObject* sender)
{
	GameAudioManager::sharedManager()->playEffect(350001,false);
	stopHeroMove();
	SpriteElfConfigFromLuaManager::getInstance()->CreateSpriteElfLayer();
	//CCLuaEngine::defaultEngine()->executeGlobalFunction("CreateSpriteElfLayer");
}

void GameUILayer::OnButtonReWard(cocos2d::CCObject *sender)
{
	stopHeroMove();
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{
		mLayer->ShowPVPLayer();
	}
}

void GameUILayer::OnButtonInstanceClick(CCObject* sender)
{
	stopHeroMove();
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{
		BattleCoverLayer * layer = mLayer->GetBattleCoverLayer();
		layer->openBattleCoverLayer(COVER_AUTOSEARCH);
	}
	TaskManager::getInstance()->TackInstanceIconClickEvent();
}

void GameUILayer::OnButtonTask(CCObject* sender)
{
	stopHeroMove();
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{
		TaskListLayer* pTaskListLayer = mLayer->GetTaskListLayer();
		if (pTaskListLayer == 0)
		{
			mLayer->CreateTaskListLayer();
			GameAudioManager::sharedManager()->playEffect(350001,false);
		}
		else
		{
			pTaskListLayer->ShowTaskListLayer(true);
			GameAudioManager::sharedManager()->playEffect(350001,false);
		}
	}
}
void GameUILayer::OnButtonRank(CCObject* sender)
{
	stopHeroMove();
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{
		CityListLayer* cityListLayer = mLayer->GetCityListLayer();
		cityListLayer->openCityList();		
	}
}

void GameUILayer::OnHeadShotClick(CCObject* sender)
{
	stopHeroMove();
	std::string msg = Localizatioin::getLocalization("S_Del_Role_Content");			
	MessageBox::Show(msg.c_str(), this, SEL_MenuHandler(&GameUILayer::OnDelRoleMessageOK), NULL, MB_YESNO);
}

void GameUILayer::OnDelRoleMessageOK(CCObject* pObject)
{
	OnlineNetworkManager::sShareInstance()->SendDelRoleReqMessage();
}

void GameUILayer::OnButtonAlchemy(CCObject* sender)
{
	stopHeroMove();
	ShowAlchemyUILayer();
}

void GameUILayer::onBroadcastMessage(BroadcastMessage* msg)
{
	switch(msg->message)
	{
	case GM_ATTR_COIN_UPDATE:
		resetPlayerGoldLabel();
		break;
	case GM_ATTR_SP_DIAMOND_UPDATE:
		resetPlayerDiamondLabel();
		break;
	case GM_ATTR_STAMINA_UPDATE:
		resetPlayerStaminaLabel();
		break;
	case GM_ATTR_REPUTATION_UPDATE:
		resetPlayerReputationLabel();
		break;
	case GM_ATTR_HERO_LEVEL_UPDATE:
		{
			setPlayerLevel();
			break;
		}
	}
}

void GameUILayer::resetPlayerDiamondLabel()
{
	UILayout* layout = UIManager::sharedManager()->getUILayout("MainMenu");
	if(layout)
	{
		UILabel *pLabel = layout->FindChildObjectByName<UILabel>("diamond");
		if(pLabel)
		{
			unsigned int diamond = UserData::GetDiamond();
			const char* str = MainMenuLayer::GetNumByFormat(diamond);
			if(str)
			{
				pLabel->setString(str);
			}
		}
	}
};

void GameUILayer::resetPlayerGoldLabel()
{
	UILayout* layout = UIManager::sharedManager()->getUILayout("MainMenu");
	if(layout)
	{
		UILabel *pLabel = layout->FindChildObjectByName<UILabel>("coin");
		if(pLabel)
		{
			unsigned int gold = UserData::GetGold();
			const char* str = MainMenuLayer::GetNumByFormat(gold);
			if(str)
			{
				pLabel->setString(str);
			}
		}
	}
}

void GameUILayer::resetPlayerReputationLabel()
{
	UILayout* layout = UIManager::sharedManager()->getUILayout("MainMenu");
	if(layout)
	{
		UILabel *pLabel = layout->FindChildObjectByName<UILabel>("reputationText");
		if(pLabel)
		{
			USERINFO info = UserData::GetUserInfo();
			unsigned int reputation = info.m_reputation;
			const char* str = MainMenuLayer::GetNumByFormat(reputation);
			if(str)
			{
				pLabel->setString(str);
			}
		}
	}
}

void GameUILayer::resetPlayerStaminaLabel()
{
	UILayout* layout = UIManager::sharedManager()->getUILayout("MainMenu");
	if(layout)
	{
		UILabel *pLabel = layout->FindChildObjectByName<UILabel>("staminaText");
		if(pLabel)
		{
			USERINFO info = UserData::GetUserInfo();
			unsigned int stamina = info.m_stamina;
			char spNum[20];
			sprintf(spNum,"%d",stamina);
			pLabel->setString(spNum);
		}
	}
}

void GameUILayer::stopHeroMove()
{
	SpriteSeer* hero = GameManager::Get()->getHero();
	if (hero)
	{
		hero->moveToTarget(hero->getPosition(), hero->getPosition());
	}

	BattleCoverLayer * coverLayer = GetBattleCoverLayer();
	if (coverLayer)
	{
		coverLayer->closeBattleCoverLayer(NULL);
	}
}

void GameUILayer::setPlayerLevel()
{
	UILayout* layout = UIManager::sharedManager()->getUILayout("MainMenu");
	if(layout)
	{
		UILabel* label = layout->FindChildObjectByName<UILabel>("playerlevel");
		if(label)
		{
			unsigned int level = UserData::GetUserLevel();
			char levelStr[10];
			sprintf(levelStr,"Lv%d",level);
			label->setString(levelStr);
		}
	}
}

void GameUILayer::showSpecialButtonEffect()
{
	UIManager *manager = UIManager::sharedManager();
	UILayout* layout = manager->getUILayout("MainMenu");
	CCNode* pTalentBtn = (layout->FindChildObjectByName<TXGUI::UIButton>("button_talent"))->getAnimationNode();
	CCNode* pSkillBtn = (layout->FindChildObjectByName<TXGUI::UIButton>("button_skillupgrade"))->getAnimationNode();
	CCNode* pEquipBtn = (layout->FindChildObjectByName<TXGUI::UIButton>("button_equipupgrade"))->getAnimationNode();

	if (pTalentBtn)
	{
		CCNode* particle = ParticleManagerX::sharedManager()->getParticles_uieffect("particle_effect_transformelite");
		if(particle != NULL)
		{
			CCNode* child = pTalentBtn->getChildByTag(10100);
			if(child)
			{
				child->removeFromParentAndCleanup(true);
				child = NULL;
			}
			pTalentBtn->addChild(particle,100,10100);
		}
	}	

	if (pSkillBtn)
	{
		CCNode* particle = ParticleManagerX::sharedManager()->getParticles_uieffect("particle_effect_transformelite");
		if(particle != NULL)
		{
			CCNode* child = pSkillBtn->getChildByTag(10101);
			if(child)
			{
				child->removeFromParentAndCleanup(true);
				child = NULL;
			}
			pSkillBtn->addChild(particle,100,10101);
		}
	}

	if (pEquipBtn)
	{
		CCNode* particle = ParticleManagerX::sharedManager()->getParticles_uieffect("particle_effect_transformelite");
		if(particle != NULL)
		{
			CCNode* child = pEquipBtn->getChildByTag(10102);
			if(child)
			{
				child->removeFromParentAndCleanup(true);
				child = NULL;
			}
			pEquipBtn->addChild(particle,100,10102);
		}
	}
}