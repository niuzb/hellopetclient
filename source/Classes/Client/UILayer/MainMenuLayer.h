//
//  MainMenuLayer.h
//  iSeer
//
//  Created by arthurgong on 11-12-8.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#ifndef _MAIN_MENU_LAYER_
#define _MAIN_MENU_LAYER_

#include "AspriteManager.h"
#include "cocos2d.h"
#include "UIButton.h"
#include "DamageValueEffect.h"
#include "TaskChatLayer.h"
#include "UIMessageLayer.h"
#include "TaskListLayer.h"
#include "SpriteElfLayer.h"
#include "BattleCoverLayer.h"
#include "vector"
using namespace std;
using namespace cocos2d;

class ItemDragLayer;
class BattleUILayer;
class GameUILayer;
class BattleWinLayer;
class BackPackLayer;
class TaskChatLayer;
class TaskListLayer;
class InstanceListLayer;
class CityListLayer;
class BattleCoverLayer;
class EquipmentUpgradeUILayer;
class EquipMixLayer;
class AlchemyUILayer;
class PPVELayer;
class PVPLayer;
class TalentLayer;
class AutoOnHook;
class ShopUILayer;

class SpriteElfLayer;
class ChatToolbar;

class WaitingLayer;

class MainMenuLayer : public cocos2d::CCLayer, public TXGUI::ObserverProtocol
{    
public:
    enum Z_MAINMENU
    {
        Z_ITEM_BACK,
        Z_ITEM_TOUCH,
        Z_ITEM_TOUCH2,
        Z_ITEM_BACK2,        
    };

public:
	MainMenuLayer();
	virtual ~MainMenuLayer();
   
	CREATE_FUNC(MainMenuLayer);
    virtual bool init();

	virtual ItemDragLayer* GetItemDragLayer();

	/// get battle ui layer
	virtual BattleUILayer* GetBattleUILayer();

	/// get gaming ui layer
	virtual GameUILayer* GetGameUILayer();

	virtual BattleWinLayer* GetBattleWinLayer();

	virtual BackPackLayer* GetBackPackLayer();

	virtual TaskChatLayer* GetTaskChatLayer();

	virtual TaskListLayer* GetTaskListLayer();

	virtual InstanceListLayer* GetInstanceListLayer();

	virtual CityListLayer* GetCityListLayer();

	virtual BattleCoverLayer * GetBattleCoverLayer();

	virtual EquipmentUpgradeUILayer* GetEquipmentUpgradeLayer();
	/// change current UI to according to the current Map config
	virtual void ChangeMapUI(int mapID);

	virtual void ShowEquipmentUpgradeUI(unsigned int coldTime);

	virtual void HideEquipmentUpgradeUI();

	void HandleDamageNumberEffect(CCNode* parent,unsigned int damage,bool isCrit,bool isHarmful = true);
	// 伤害数字UI，damage 伤害,isCrit 是否爆击,isHarmful 是否敌对目标

	void HandleAttackMissEffect(CCPoint parentPt);
	// 攻击miss

	void HandleAttackBlockEffect(CCPoint parentPt);
	// 攻击隔挡

	void HandleComboIncrease(unsigned int incremental = 1);
	// 连击数显示 incremental增量

	virtual UIMessageLayer* getUIMessageLayer();
	virtual WaitingLayer*  getWaitingLayer();
	//////////////////////////////
	///   ppve 
	/////////////////////////////
	virtual PPVELayer* ShowPPVELayer();
	virtual void HidePPVELayer(bool bShowGameUI);
	virtual PPVELayer* GetPPVELayer() {return m_pPPVELayer;}
	virtual bool IsInPPVEModule();
    
    //pvp
    virtual PVPLayer* ShowPVPLayer();
    virtual void HidePVPLayer(bool bShowGameUI);
    
    virtual PVPLayer* getPVPLayer() { return m_pPVPLayer;}
    virtual bool IsInPVPModule();
    
    virtual TalentLayer* ShowTalentLayer();
    virtual void HideTalentLayer(bool bShowGameUI);
    
    virtual TalentLayer* getTalentLayer() { return m_pTalentLayer; }
    virtual bool IsInTalentModule();
    
    virtual AutoOnHook* ShowAutoOnHook();
    virtual void HideAutoOnHook(bool bShowGameUI);

    virtual AutoOnHook* getAutoOnHook() { return m_pAutoOnHook; }
    virtual bool IsInAutoOnHookModule();
    

    virtual ShopUILayer* ShowShopUILayer();
    virtual void HideShopUILayer(bool bShowGameUI);
    
    virtual ShopUILayer* getShopUILayer() { return m_pShopUILayer; }
    virtual bool IsInShopUILayerModule();

    virtual EquipMixLayer* ShowEquipMixLayer();
	virtual void HideEquipMixLayer();
	EquipMixLayer* GetCurrentEquipMixLayer();
	
	virtual AlchemyUILayer* ShowAlchemyUILayer();
	virtual void HideAlchemyUILayer();
	virtual AlchemyUILayer* GetCurrentAlchemyLayer();
    
	// Note: Sprite Elf
	virtual SpriteElfLayer* ShowSpriteElfLayer();

	////////////////////////////
	///   chat toolbar
	////////////////////////////
	virtual ChatToolbar* GetChatToolbar();
	virtual void  setChatToolbar(bool isChatVisible,bool isFunctionVisible,bool isExtraVisible = false,int order = -1);

	static const char* GetNumByFormat(unsigned int num);
	// 得到固定格式的数字.大于100000以XXXk的形式显示,大于100000k以xxxm的形式显示

	static MainMenuLayer* getMainMenuLayer();
	/**
	* Instruction : 创建并显示任务layer
	* @param 
	*/
	void CreateTaskListLayer();
	/**
	* Instruction : 销毁任务layer
	* @param 
	*/
	void DestroyTaskListLayer();

	/**
	* Instruction : 插入一个Layer到队列中
	* @param 
	*/
	static void PushOneLayer(CCLayer *pLayer,std::string param_1 = "",std::string param_2 = ""); 

	/**
	* Instruction : 删除某Layer
	* @param 
	*/
	static void RemoveOneLayer(CCLayer *pLayer);

	void DarkEffectOver();

	virtual void keyBackClicked();//监听Android 返回键
	virtual void keyMenuClicked();//监听Android 菜单键

	void OkBtnClick(CCObject* obj);
	void CancelBtnClick(CCObject* obj);	

	static void ClearLayersInQueneData();	
protected:
	/// overload touch event
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

protected:
	/// 消息响应函数
	virtual void onBroadcastMessage(BroadcastMessage* msg);
	
protected:
	ItemDragLayer* m_pDragLayer;

	BattleUILayer * m_pBattleUI;

	GameUILayer * m_pGameUI;

	DamageValueEffect* damageValueLable;

	BattleWinLayer* m_pBattleWinUI;

	BackPackLayer* m_pBackPackUI;

	TaskChatLayer* m_pTaskChatUI;

	TaskListLayer* m_pTaskListUI;

	InstanceListLayer* m_pInstanceListUI;

	CityListLayer * m_pCityListUI;

	BattleCoverLayer * m_pBattleCoverUI;

	EquipmentUpgradeUILayer* m_equipmentUpgradeLayer;

	PPVELayer*	m_pPPVELayer;

    PVPLayer*   m_pPVPLayer;
    
    TalentLayer* m_pTalentLayer;
    
    AutoOnHook* m_pAutoOnHook;
    
    ShopUILayer* m_pShopUILayer;
    
	ChatToolbar* m_pChatToolbar;
    
	UIMessageLayer* m_pUIMessage;
    WaitingLayer* m_pUIWaiting;
    
	EquipMixLayer* m_equipMixLayer;
	AlchemyUILayer* m_pAlchemyUILayer;
    
	/**
	* Instruction : 显示队列中的Layer
	* @param 
	*/	
	static std::vector<CCLayer*> *sVecLayersInQuene;
};

MainMenuLayer*  GetMainMenuLayer();

/// API for UI
ItemDragLayer*	GetItemDragLayer();
BattleUILayer*	GetBattleUILayer();
GameUILayer*	GetGameUILayer();
BattleWinLayer* GetBattleWinLayer();
BackPackLayer*	GetBackPackLayer();
InstanceListLayer*			GetInstanceListLayer();
CityListLayer *  GetCityListLayer();
BattleCoverLayer * GetBattleCoverLayer();
EquipmentUpgradeUILayer*	GetEquipmentUpgradeLayer();

/// ppve UI 
PPVELayer*      GetPPVELayer();
PVPLayer*       GetPVPLayer();
TalentLayer*    GetTalentLayer();
AutoOnHook*     GetAutoOnHook();
ShopUILayer*    GetShopUILayer();

void  RemovePPVELayer(bool showGameUI);
void  RemovePVPLayer(bool showGameUI);
void  RemoveTalentLayer(bool showGameUI);
void  RemoveAutoHook(bool showGameUI);
void  RemoveShopUILayer(bool showGameUI);


/// charToolbar 
ChatToolbar*    GetChatToolbar();

void	ShowChatBar(bool isExtrVisible,int order = -1);
// 显示聊天框 isExtrVisible 底部的功能按键是否显示，order是聊天框的层级，默认是-1.

void	ShowMessage(const char* message,const ccColor3B& color = KMessageDefaultColor);

/// WaitingLayer
void   ShowWaitingLayer(bool bShowRightNow = true,float sumTimer = 0.3f);
void   HideWaitingLayer();

EquipMixLayer* ShowEquipMixLayer();
EquipMixLayer* GetCurrentEquipMixLayer();
void HideEquipMixLayer();

AlchemyUILayer* ShowAlchemyUILayer();
void HideAlchemyUILayer();
AlchemyUILayer* GetCurrentAlchemyLayer();

#endif // _MAIN_MENU_LAYER_





