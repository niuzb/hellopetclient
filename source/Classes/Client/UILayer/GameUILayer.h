//
//  MainMenuLayer.h
//  iSeer
//
//  Created by arthurgong on 11-12-8.
//  Copyright 2011ƒÍ __MyCompanyName__. All rights reserved.
//
#pragma once

#include "AspriteManager.h"
#include "cocos2d.h"
#include "UIButton.h"
#include "UILayout.h"
#include "TaskData.h"

using namespace std;
using namespace cocos2d;

//
// π‹¿Ì’Ω∂∑UIµ„ª˜¬ﬂº≠
//
class GameUILayer : public cocos2d::CCLayer,
					public TXGUI::ObserverProtocol
{    
public:
	GameUILayer();
	virtual ~GameUILayer();
   
	CREATE_FUNC(GameUILayer);
    virtual bool init();

	/// hide all buttons
	void	PuckerButtons();

	void	showSpecialButtonEffect();
protected:
	/// store the button points
	void	MapButtonPointsH(TXGUI::UILayout* layout, const char * szName);
	/// pucker buttons to right bottom corner
	void    PuckerButtonsH(CCPoint ptDest);
	/// un pucker buttons from right bottom corner
	void    UnPuckerButtonsH();

	/// store the button points
	void	MapButtonPointsW(TXGUI::UILayout* layout, const char * szName);
	/// pucker buttons to right bottom corner
	void    PuckerButtonsW(CCPoint ptDest);
	/// un pucker buttons from right bottom corner
	void    UnPuckerButtonsW();

	/// open bag 
    void	OnButtonBag(CCObject *sender);
    
    ///open Talent
    void    OnButtonTalent(CCObject *sender);

	void    OnButtonSetting(CCObject *sender);
	/// shrink button
	void	OnButtonShrink(CCObject* sender);

	void	OnButtonUpgrade(CCObject* sender);

	void	OnButtonAlchemy(CCObject* sender);

	//// on button activity
	void	OnButtonActivity(CCObject* sender);

	//// on head shot click
	void	OnHeadShotClick(CCObject* sender);
	void	OnDelRoleMessageOK(CCObject* pObject);

	/**
	* Instruction : æ´¡È∞¥≈•
	* @param 
	*/
	void	OnButtonFairy(CCObject* sender);	
    
    /////on button reward
    void    OnButtonReWard(CCObject* sender);

	//// on task btn click
	void	OnButtonTask(CCObject* sender);

	void	OnButtonRank(CCObject* sender);


	void	HideButton(CCNode* sender);
	void	ShowButton(CCNode* sender);

	/**
	* Instruction : µ„ª˜”“…œΩ«Icon
	* @param 
	*/
	void	OnButtonInstanceClick(CCObject* sender);

	/// œ˚œ¢œÏ”¶∫Ø ˝
	virtual void onBroadcastMessage(BroadcastMessage* msg);

public:
	/// override of node
	virtual void setVisible(bool visible);

	/**
	* Instruction : À¢–¬»ŒŒÒœµÕ≥Icon
	* @param state 0 Ω”»ŒŒÒ 1 Ωª»ŒŒÒ
	*/	
	void	UpdateTaskUpRightIcon(std::string icon_name,eTaskState state = kType_TASK_UNKNOW);

	void stopHeroMove();

private:
	void resetPlayerGoldLabel();
	void resetPlayerDiamondLabel();
	void resetPlayerReputationLabel();
	void resetPlayerStaminaLabel();
	void setPlayerLevel();
protected:
	map<TXGUI::UIButton*, CCPoint> m_mapBttonPointH, m_mapBttonPointW;
	CCPoint m_ptDestShrink;
	TXGUI::UIButton* m_pBtnShrink;
	bool m_bPuckered;
};
