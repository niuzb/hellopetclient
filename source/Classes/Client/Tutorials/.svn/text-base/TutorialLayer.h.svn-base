#pragma once

#include "cocos2d.h"
#include "string"

using namespace std;
using namespace cocos2d;

class TutorialLayer : public cocos2d::CCLayer
{
public:
	TutorialLayer();
	virtual ~TutorialLayer();

	CREATE_FUNC(TutorialLayer);

	virtual bool init();  
	void update(float dt);

	void ShowLayer();
	void ShowLayer(std::string uiName);
	void HideLayer();

protected:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

private:
	CCSprite* m_pUISprite;
};
