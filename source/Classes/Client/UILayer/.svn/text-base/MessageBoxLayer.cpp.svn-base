#include "MessageBoxLayer.h"
#include "UIManager.h"
#include "GameResourceManager.h"
#include "GameConfigFromLuaManager.h"
#include "TaskConfigFromLuaManager.h"
#include "Localization.h"
#include "AspriteManager.h"
#include "GameFontManager.h"
#include "algorithm"
#include "MainMenuLayer.h"
#include "GameManager.h"
#include "LevelLayer.h"

using namespace TXGUI;

TXGUI::MessageBox* TXGUI::MessageBox::selfInstance = 0;

TXGUI::MessageBox::MessageBox()
{
	clickEventHander = 0;
	pfnOkClicked = 0;
	pfnCancelClicked = 0;
	messageBodyLabel = 0;
	okBtn = 0;
	cancelBtn = 0;
	okContentLabel = 0;
	cancelContentLabel = 0;
	okBtnContent = std::string(Localizatioin::getLocalization("S_OK"));
	cancelBtnContent = std::string(Localizatioin::getLocalization("S_CANCEL"));
    
    this->closeBtn = NULL;
}

TXGUI::MessageBox::~MessageBox()
{
	selfInstance = 0;
	UIManager::sharedManager()->RemoveUILayout("MessageBoxPanel");
}

void TXGUI::MessageBox::Destroy()
{
	this->removeFromParentAndCleanup(true);
	selfInstance = 0;
}

void TXGUI::MessageBox::ResetValue()
{
	std::string value = std::string(Localizatioin::getLocalization("S_OK"));
	okBtnContent = std::string(Localizatioin::getLocalization("S_OK"));
	cancelBtnContent = std::string(Localizatioin::getLocalization("S_CANCEL"));
}

bool TXGUI::MessageBox::init()
{
	if(!CCLayer::init())
	{
		return false;
	}

	UIManager *manager = UIManager::sharedManager();

	messageboxLayer = manager->CreateUILayoutFromFile("UIplist/msgBox.plist", this, "MessageBoxPanel");

	manager->RegisterMenuHandler("MessageBoxPanel","MessageBox::okBtnClickEvent",
		menu_selector(MessageBox::okBtnClickEvent), this);

	manager->RegisterMenuHandler("MessageBoxPanel","MessageBox::cancelBtnClickEvent",
		menu_selector(MessageBox::cancelBtnClickEvent), this);
    
    
    manager->RegisterMenuHandler("MessageBoxPanel","MessageBox::closeBtnClickEvent",
                                 menu_selector(MessageBox::closeBtnClickEvent), this);


	messageBodyLabel = messageboxLayer->FindChildObjectByName<UILabel>("message_body");
	okBtn = messageboxLayer->FindChildObjectByName<UIButton>("OkBtn");
	cancelBtn = messageboxLayer->FindChildObjectByName<UIButton>("CancelBtn");
	okContentLabel = messageboxLayer->FindChildObjectByName<UILabel>("ok_btn_label");
	cancelContentLabel = messageboxLayer->FindChildObjectByName<UILabel>("cancel_btn_label");
    
    closeBtn = messageboxLayer->FindChildObjectByName<UIButton>("closeBtn");
    closeBtn->setVisible(false);
    
    setTouchEnabled(true);
    
	return true;
}

bool TXGUI::MessageBox::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void TXGUI::MessageBox::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	CCLayer::ccTouchMoved(pTouch, pEvent);
}

void TXGUI::MessageBox::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	CCLayer::ccTouchCancelled(pTouch, pEvent);
}

void TXGUI::MessageBox::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCLayer::ccTouchEnded(pTouch, pEvent);
}

void TXGUI::MessageBox::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, KCCMessageBoxPripority, true);
}

void TXGUI::MessageBox::Show(const char* message_body,cocos2d::CCObject * handler /* = 0 */, 
	SEL_MenuHandler pfnOkClicked /* = 0 */,SEL_MenuHandler pfnCancelClicked /* = 0 */, 
	unsigned int  uType /* = MB_YESNO */,ccColor3B labelColor /* = ccc3 */,int fontSize /* = 24 */)
{
	if (selfInstance != 0)
	{
		// Note: 销毁原来窗口
		selfInstance->Destroy();
	}

	TXGUI::MessageBox* msgLayer = TXGUI::MessageBox::create();
	selfInstance = msgLayer;
	selfInstance->ResetValue();

	MainMenuLayer * Layer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (Layer == 0)
	{
		return ;
	}
	Layer->addChild(msgLayer,INT_MAX);
	msgLayer->setVisible(true);

	msgLayer->messageBodyLabel->setString(message_body);
	msgLayer->messageBodyLabel->setColor(labelColor);

	msgLayer->clickEventHander = handler;
	msgLayer->pfnOkClicked = pfnOkClicked;
	msgLayer->pfnCancelClicked = pfnCancelClicked;

	if (uType == MB_OK)
	{
		CCPoint okBtnPos = msgLayer->okBtn->getPosition();
		CCPoint cancelBtnPos = msgLayer->cancelBtn->getPosition();
		CCPoint midPos = ccpAdd(okBtnPos,cancelBtnPos);

		msgLayer->cancelBtn->setVisible(false);
		msgLayer->cancelContentLabel->setVisible(false);
		msgLayer->okBtn->setPosition(ccp(midPos.x/2,midPos.y/2));
		msgLayer->okContentLabel->setPosition(ccp(midPos.x/2,midPos.y/2));
	}

	selfInstance->okContentLabel->setString(selfInstance->okBtnContent.c_str());
	selfInstance->cancelContentLabel->setString(selfInstance->cancelBtnContent.c_str());	
}

void TXGUI::MessageBox::Show(const char* message_body,int pfnOkHandler,int pfnCancelHandler,
	unsigned int uType/* = MB_YESNO*/,ccColor3B labelColor/* = ccc3(255,255,255)*/,int fontSize/* = 24*/)
{
	if (selfInstance != 0)
	{
		// Note: 销毁原来窗口
		selfInstance->Destroy();
	}
	TXGUI::MessageBox* msgLayer = TXGUI::MessageBox::create();
	selfInstance = msgLayer;
	selfInstance->ResetValue();

	MainMenuLayer * Layer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (Layer == 0)
	{
		return ;
	}
	Layer->addChild(msgLayer,INT_MAX);
	msgLayer->setVisible(true);

	msgLayer->messageBodyLabel->setString(message_body);
	msgLayer->messageBodyLabel->setColor(labelColor);
	msgLayer->clickEventHander = NULL;
	msgLayer->pfnOkClicked = NULL;
	msgLayer->pfnCancelClicked = NULL;

	msgLayer->okBtn->getMenuItemSprite()->registerScriptTapHandler(pfnOkHandler);
	msgLayer->cancelBtn->getMenuItemSprite()->registerScriptTapHandler(pfnCancelHandler);

	if (uType == MB_OK)
	{
		CCPoint okBtnPos = msgLayer->okBtn->getPosition();
		CCPoint cancelBtnPos = msgLayer->cancelBtn->getPosition();
		CCPoint midPos = ccpAdd(okBtnPos,cancelBtnPos);

		msgLayer->cancelBtn->setVisible(false);
		msgLayer->cancelContentLabel->setVisible(false);
		msgLayer->okBtn->setPosition(ccp(midPos.x/2,midPos.y/2));
		msgLayer->okContentLabel->setPosition(ccp(midPos.x/2,midPos.y/2));
	}

	selfInstance->okContentLabel->setString(selfInstance->okBtnContent.c_str());
	selfInstance->cancelContentLabel->setString(selfInstance->cancelBtnContent.c_str());	
}

void TXGUI::MessageBox::AdjustStyle(std::string okBtnContent,std::string cancelBtnContent)
{
	selfInstance->okContentLabel->setString(okBtnContent.c_str());
	selfInstance->cancelContentLabel->setString(cancelBtnContent.c_str());
}

void TXGUI::MessageBox::okBtnClickEvent(CCObject* sender)
{
	if (this->clickEventHander != 0 && pfnOkClicked != 0)
	{
		(this->clickEventHander->*pfnOkClicked)(sender);
	}
	Destroy();
}

void TXGUI::MessageBox::cancelBtnClickEvent(CCObject* sender)
{
	if (this->clickEventHander != 0 && pfnCancelClicked != 0)
	{
		(this->clickEventHander->*pfnCancelClicked)(sender);
	}
	Destroy();
}

void TXGUI::MessageBox::closeBtnClickEvent(CCObject* sender)
{
	Destroy();
}

void TXGUI::MessageBox::showCloseBtn()
{
    if(selfInstance->closeBtn)
        selfInstance->closeBtn->setVisible(true);
}

