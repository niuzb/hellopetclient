#pragma once

#include "ASprite.h"
#include "TXGUIHeader.h"

using namespace std;
using namespace cocos2d;


/*
 * MessageBox() Flags
 */
#define MB_OK                       0x00000000L
#define MB_OKCANCEL                 0x00000001L
#define MB_ABORTRETRYIGNORE         0x00000002L
#define MB_YESNOCANCEL              0x00000003L
#define MB_YESNO                    0x00000004L
#define MB_RETRYCANCEL              0x00000005L

namespace TXGUI
{
	class MessageBox : public cocos2d::CCLayer
	{
	public:	
		MessageBox();
		virtual ~MessageBox();

		CREATE_FUNC(MessageBox);
		virtual bool init();

		static void Show(const char* message_body,cocos2d::CCObject * handler = 0, 
			SEL_MenuHandler pfnOkClicked = 0,SEL_MenuHandler pfnCancelClicked = 0,
			unsigned int uType = MB_YESNO,ccColor3B labelColor = ccc3(255,255,255),int fontSize = 24);

		static void Show(const char* message_body,int pfnOkHandler,int pfnCancelHandler,
			unsigned int uType = MB_YESNO,ccColor3B labelColor = ccc3(255,255,255),int fontSize = 24);

		static void AdjustStyle(string okBtnContent,string cancelBtnContent);

		void Destroy();

		void ResetValue();

		void okBtnClickEvent(CCObject* sender);
		void cancelBtnClickEvent(CCObject* sender);
        void closeBtnClickEvent(CCObject* sender);
        
        static void showCloseBtn();
        
	protected:
		virtual void registerWithTouchDispatcher();
		virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
		virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
		virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
		virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	private:		
		static MessageBox* selfInstance;

		TXGUI::UILayout* messageboxLayer;
		TXGUI::UILabel* messageBodyLabel;
		TXGUI::UIButton* okBtn;
		TXGUI::UIButton* cancelBtn;
		TXGUI::UILabel* okContentLabel;
		TXGUI::UILabel* cancelContentLabel;
		CCObject* clickEventHander;
		SEL_MenuHandler pfnOkClicked;
		SEL_MenuHandler pfnCancelClicked;
        TXGUI::UIButton* closeBtn;

		std::string okBtnContent;
		std::string cancelBtnContent;
	};
};