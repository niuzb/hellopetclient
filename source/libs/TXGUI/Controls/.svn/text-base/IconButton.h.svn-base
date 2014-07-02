#ifndef iSeer_IconButton_h
#define iSeer_IconButton_h

#include "cocos2d.h"
#include "UIMenu.h"
#include "DragReceiver.h"
#include "UILabelTTF.h"
USING_NS_CC;

namespace TXGUI
{
	class IconButton : public CCNode
	{
	public: 
		IconButton(CCSprite* backgroundTex , CCSprite* normalTex, CCSprite* selectedTex,
			cocos2d::CCObject * handler, SEL_MenuHandler pfnClicked);		

		virtual ~IconButton();

		void SetButtonIndex(int index){m_pagePosition = index;}

		int GetButtonIndex(){return m_pagePosition;}

		void SetNormalIcon(CCSprite* normalTex);

		void SetSelectedIcon(CCSprite* selectedTex);

		void AddExternalSprite(CCSprite* sprite, CCPoint pt);

		virtual UILabelTTF* getItemLabel();

		virtual void setItemLabel(const char * text,float fontSize,const char* font);

		virtual void removeItemLabel();

		void SetUserData(int data);

		void creatDragReceiver(DragHandlerType type);

		void SetDragFlagTime(unsigned int ms);

		virtual void SetDoubleClickHandler(CCObject* listerner,SEL_MenuHandler handler);
		virtual void SetTappedHandler(CCObject* listerner,SEL_MenuHandler tapHandler,SEL_MenuHandler tapCancelHandler);
		virtual bool isReleaseInButton(CCTouch* touch);
		virtual void setDragMove(bool);
		virtual void setFrameSprite(CCSprite* sprite,CCPoint pt = CCPointZero);
		DragReceiver* getDragReceiver(){return m_dragHandler;}

		// 动态修改按键优先级
		virtual void setHandlerPriority(int newPriority);

		int getHandlerPriority();
	protected:
		CCSprite* m_normalTex;
		CCSprite* m_selectedTex;
		CCSprite* m_backgroundTex;
		CCSprite* m_pFrameIcon;
		CCMenuItemSprite* m_menuItem;
		UILabelTTF* m_pButtonLabel;
		UIMenu* m_menu;
		int m_pagePosition;
		DragReceiver* m_dragHandler;
		int m_priority;
	};
}

#endif