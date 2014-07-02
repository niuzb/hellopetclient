#include "UIMessageLayer.h"
#include "GameFontManager.h"
#include "AspriteManager.h"
#include "ASprite.h"
#include "TXGUIHeader.h"
#include "resources.h"

#define KMessageBackPictureName "map_ui_FRAME_MSG_BAR"
UIMessageLayer::UIMessageLayer()
	:m_labelTTF(NULL),
	m_backPic(NULL),
	m_pAnmationNode(NULL)
{

}

UIMessageLayer::~UIMessageLayer()
{

}

bool UIMessageLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}

	m_pAnmationNode = CCSprite::create();
	m_pAnmationNode->setPosition(CCPointZero);
	m_pAnmationNode->setOpacityModifyRGB(false);
	addChild(m_pAnmationNode);
	int fontSize = 26;
	CCSize nameLabelSize = CCSizeMake(500 / CC_CONTENT_SCALE_FACTOR(), fontSize * 2.0f);
	m_labelTTF = UILabelTTF::create("1", KJLinXin, fontSize, 
		nameLabelSize, kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
	if(!m_labelTTF)
	{
		return false;
	}
	m_labelTTF->setColor(KMessageDefaultColor);
	
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	m_localStartPt = ccp(visibleSize.width *0.5,visibleSize.height * 0.6);

	ASprite* as = AspriteManager::getInstance()->getAsprite(KUI_BIN); 
	if(as)
	{
		CCPoint pt;
		int iSpriteFrame = getResourceIDByName(KMessageBackPictureName);
		m_backPic = as->getSpriteFromFrame_Middle(iSpriteFrame, 0, pt);
		if(m_backPic)
		{
			m_backPic->setAnchorPoint(ccp(0.5,0.5));
			m_pAnmationNode->addChild(m_backPic);
			m_backPic->setPosition(CCPointZero);
		}
	}
	m_pAnmationNode->addChild(m_labelTTF);
	m_labelTTF->setPosition(CCPointZero);
	return true;
}

void UIMessageLayer::ShowMessage(const char* message,const ccColor3B& color)
{
	setVisible(true);
	if(m_labelTTF && m_pAnmationNode)
	{
		m_pAnmationNode->setPosition(m_localStartPt);
		m_pAnmationNode->setOpacity(255);
		m_pAnmationNode->stopAllActions();
		//m_labelTTF->setPosition(m_localStartPt);
		m_labelTTF->setStringWithColor(message,color);
		//m_labelTTF->setOpacity(255);
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCMoveBy* actionMove1 = CCMoveBy::create(1.0f,ccp(0,visibleSize.height * 0.15f));
		CCActionInterval* actionMove2 = CCMoveBy::create(0.6f,ccp(0,visibleSize.height * 0.2f));
		CCActionInterval* actionFade = CCFadeOut::create(0.6f);
		CCSpawn* SecondAction = CCSpawn::createWithTwoActions(actionMove2,actionFade);
		m_pAnmationNode->runAction(CCSequence::create(actionMove1,CCDelayTime::create(1.5f),SecondAction
			,CCCallFuncN::create(this,callfuncN_selector(UIMessageLayer::HideMessage)),NULL));
	}
}

 void UIMessageLayer::HideMessage(CCNode* node)
 {
	 setVisible(false);
 }