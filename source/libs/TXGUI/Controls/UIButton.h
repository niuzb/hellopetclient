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

#ifndef iSeer_UIButton_h
#define iSeer_UIButton_h


#include "TXGUI.h"
#include "UIControlBase.h"
#include "UIMenu.h"
#include "UILabelTTF.h"
namespace TXGUI {
    USING_NS_CC;
    
    class UIButton : public UIControlBase 
    {       
        NiDeclareRTTI;
        NiDeclareStream;  
    public:
        UIButton(cocos2d::CCNode* parent);

		UIButton(
			std::string name,
			int tag,
			float z,
			UIControlBase* parent,
			CCMenuItemSprite *sprite,
			CCMenuItemLabel *label,
			int priority
			);

		UIButton(
			std::string name,
			int tag,
			float z,
			UIControlBase* parent,
			CCMenuItemSprite *sprite,
			CCMenuItemLabel *label,
			int priority,
			std::string clickedFunc
			);
        
        virtual   ~UIButton();        
        
		virtual CCPoint getWorldPosition();

        virtual void setPosition(CCPoint pt);

		virtual void setScale(float scale);

		virtual void setScale(float xScale, float yScale);

		virtual CCMenuItemSprite* getMenuItemSprite();

		virtual void setMenuItemSprite(CCMenuItemSprite *pSprite);

		virtual CCMenuItemLabel* getMenuItemLabel();

		virtual UILabelTTF* getTextLabel();

		virtual void setTextLabel(const char * text,float fontSize,const char* font,CCPoint pt = CCPointZero);

		virtual void setMenuItemLabel(CCMenuItemLabel *pLabel);

		virtual void setClickedFunc(std::string func);

		virtual bool isSelected();
        
		virtual void setTouchEnabled(bool value);

		virtual void setMenuInitPriority(int priority);

		virtual void setIconSprite(CCSprite* sprite);

		virtual CCSprite* getIconSprite(){return m_pBtIcon;}

		virtual void BindNode(CCNode* pParentNode);

		virtual CCNode* getAnimationNode(){return m_pAnimationNode;}

		virtual void creatDragReceiver(DragHandlerType type);
		virtual void SetDoubleClickHandler(CCObject* listerner,SEL_MenuHandler handler);
		virtual void SetTappedHandler(CCObject* listerner,SEL_MenuHandler tapHandler,SEL_MenuHandler tapCancelHandler);
		virtual bool isReleaseInButton(CCTouch* touch);
		virtual void setDragMove(bool);
		virtual DragReceiver* getDragReceiver(){return m_dragHandler;}
		virtual void setFrameSprite(CCNode* node,CCPoint pt = CCPointZero);

		virtual CCSize getButtonSize(); 
		virtual unsigned int getButtonIndex(){return m_buttonIndex;}
		virtual void setButtonIndex(unsigned int index){m_buttonIndex = index;}
		/// show /hide function
		virtual void setVisible(bool visible);

		/// set button tag for user data
		virtual void setTag(int iTag) ;

		virtual void setEnabled(bool value);
		virtual bool isEnabled();

		// 动态修改按键优先级
		virtual void setHandlerPriority(int newPriority);

		int getHandlerPriority();

    protected:
        UIButton();
        
        virtual void  Clicked(CCObject* pObject);
		void OnDoubleClicked(CCObject *pObject);
		void OnTapped(CCObject *pObject);
		void OnTapCancel(CCObject *pObject);
    protected:        
		int m_priority;
		CCPoint m_anmationPosition;
        UIMenu* m_pBtnMenu;
		CCSprite* m_pBtIcon;
		CCNode* m_pFrameNode;
		CCNode* m_pAnimationNode;
		unsigned int m_iconOrder;
        CCMenuItemSprite* m_pButtonItem;
		CCMenuItemLabel* m_pButtonLabel;
        string  m_strClickedFun;
		string m_strDoubleClickedFun;
		string m_strTappedFun;
		string m_strTapCancelFun;
		bool m_bIsEnabled;
		bool m_bIsTouchEnabled;
		bool m_bSoundEnabled;
		UILabelTTF* m_pTextLabel;
		unsigned int m_buttonIndex;
		DragReceiver* m_dragHandler;
		unsigned int m_ExtraSpriteOrder;
		unsigned int m_pButtonPosZ;
    };
}

#endif
