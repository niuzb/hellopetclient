#ifndef UI_MESSAGE_H
#define UI_MESSAGE_H

#include "cocos2d.h"
#include "UILabelTTF.h"

using namespace cocos2d;
using namespace TXGUI;

#define KMessageDefaultColor ccc3(238,166,26)

class UIMessageLayer : public cocos2d::CCLayer
{
public: 
	UIMessageLayer();
	virtual ~UIMessageLayer();
	CREATE_FUNC(UIMessageLayer);
	virtual bool init();

	virtual void ShowMessage(const char* message,const ccColor3B& color);
	void HideMessage(CCNode* sender);
private:
	UILabelTTF* m_labelTTF;
	CCPoint m_localStartPt;
	CCSprite* m_backPic;
	CCSprite* m_pAnmationNode;
};

#endif 