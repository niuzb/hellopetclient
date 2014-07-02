#include "TutorialLayer.h"
#include "GameManager.h"
#include "SceneLayer.h"
#include "UIDefine.h"

#include "AspriteManager.h"

TutorialLayer::TutorialLayer()
{
	m_pUISprite = NULL;
}

TutorialLayer::~TutorialLayer()
{
}

bool TutorialLayer::init()
{
	bool bRet = false;
	do {
		setTouchEnabled(true);
		bRet = true;
	}while (0);
	return true;
}

void TutorialLayer::update(float dt)
{
}

void TutorialLayer::ShowLayer()
{
	if (m_pUISprite)
	{
		m_pUISprite->removeFromParentAndCleanup(true);
		m_pUISprite = NULL;
	}
	this->setVisible(true);
}

void TutorialLayer::ShowLayer(std::string uiName)
{
	if (m_pUISprite)
	{
		m_pUISprite->removeFromParentAndCleanup(true);
		m_pUISprite = NULL;
	}

	m_pUISprite = CCSprite::create(uiName.c_str());
	if (m_pUISprite)
	{
		this->addChild(m_pUISprite,1);
	}
	this->setVisible(true);
}

void TutorialLayer::HideLayer()
{
	this->setVisible(false);
}

bool TutorialLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if(isVisible())
	{
		return true;
	}

	return false;
}

void TutorialLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCLayer::ccTouchMoved(pTouch,pEvent);
}

void TutorialLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCLayer::ccTouchEnded(pTouch,pEvent);
}

void TutorialLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	CCLayer::ccTouchCancelled(pTouch,pEvent);
}

void TutorialLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, KCCLayerTutorialPripority, true);
}


