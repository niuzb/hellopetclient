//
//  TipMgr.cpp
//  HelloLua
//
//  Created by rickycheng  on 13-5-6.
//
//

#include "TipMgr.h"
#include "UILabel.h"

#include "ASprite.h"
#include "resources.h"
#include "GameFontManager.h"
#include "GameManager.h"
#include "MainMenuLayer.h"
#include "GameAudioManager.h"

using namespace cocos2d;

//TXGUI::UILabelTTF* labelName = TXGUI::UILabelTTF::create(message,KJLinXin,20,CCSizeZero,kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);

TipMgr::TipMgr()
{
    this->m_pColorLayer = NULL;
    this->m_pIcon = NULL;
    this->m_bkSprite = NULL;
    this->m_childcnt = 0;
    this->m_maxHeight = 0;
    this->m_maxWidth = 0;
    
    this->m_tapx = 10;
    this->m_tapy = 10;
    
    m_pChildNode = CCArray::create();
    m_pChildNode->retain();
}

TipMgr::~TipMgr()
{
    CC_SAFE_RELEASE(m_pChildNode);
}

void TipMgr::createTip(cocos2d::CCSprite *icon, CCPoint spt)
{
	GameAudioManager::sharedManager()->playEffect(350001,false);
    destroyTip();
    m_pt = spt;
    
    ASprite *as = AspriteManager::getInstance()->getAsprite(KUI_BIN);
    int idx = getResourceIDByName("map_ui_FRAME_TIPS_BACKGROUND");
    CCPoint pt;
    m_bkSprite = as->getSpriteFromFrame_Middle( idx, 0, pt);

    float scaleFactor = UIManager::sharedManager()->getScaleFactor();
    CCSize winsize = CCDirector::sharedDirector()->getWinSize();
    m_pChildNode->removeAllObjects();
    m_pColorLayer = CCLayerColor::create(ccc4(200,200,200,0), winsize.width/4, 0);
    m_pIcon = icon;
    
    this->m_childcnt = 0;
    this->m_maxHeight = 0;
    this->m_maxWidth = 0;
}

void TipMgr::add(cocos2d::CCSprite *labelIcon, const char *message, cocos2d::ccColor3B color, int fontsize)
{
    CCLabelTTF* labelName = CCLabelTTF::create(message, KJLinXin, fontsize);
    if(labelName->getContentSize().width >= m_pColorLayer->getContentSize().width)
    {
        std::string str = message;
        std::string str1 = str.substr(0,str.length()/3);
        std::string str2 = str.substr(str.length()/3, str.length());
        add(labelIcon, str1.c_str(), color, fontsize);
        add(str2.c_str(), color, fontsize);
    }
    else
    {
        CCNode *node = CCNode::create();
        CCLabelTTF* labelName = CCLabelTTF::create(message, KJLinXin, fontsize);
        labelName->setColor(color);
        node->addChild(labelIcon);
        node->addChild(labelName);
        float height = max(labelIcon->getContentSize().height, labelName->getContentSize().height);
        node->setContentSize(CCSize(m_pColorLayer->getContentSize().width, height));
        
        labelIcon->setPosition(ccp(m_tapx-node->getContentSize().width/2 + labelIcon->getContentSize().width/2, node->getContentSize().height/2));
        labelName->setPosition(ccp(labelIcon->getPosition().x+labelIcon->getContentSize().width/2 + labelName->getContentSize().width/2,node->getContentSize().height/2));
        
        m_pChildNode->addObject(node);
    }
}

void TipMgr::add(const char *message, cocos2d::ccColor3B color, int fontsize)
{
    CCLabelTTF* labelName = CCLabelTTF::create(message, KJLinXin, fontsize);
    if(labelName->getContentSize().width >= m_pColorLayer->getContentSize().width)
    {
        std::string str = message;
        std::string str1 = str.substr(0,str.length()/2);
        std::string str2 = str.substr(str.length()/2, str.length());
        add(str1.c_str(), color, fontsize);
        add(str2.c_str(), color, fontsize);
    }
    else
    {
        CCNode* node = CCNode::create();
        CCLabelTTF* labelName = CCLabelTTF::create(message, KJLinXin, fontsize);
        labelName->setColor(color);
        node->addChild(labelName);
        node->setContentSize(labelName->getContentSize());
        labelName->setPosition(ccp(m_tapx, node->getContentSize().height/2));
        m_pChildNode->addObject(node);
    }
}

void TipMgr::addNodeDone()
{
    MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
    mLayer->addChild(m_pColorLayer,85);
    mLayer->addChild(m_bkSprite,84);
    
    if(m_pChildNode && m_pChildNode->count() > 0)
    {
        CCObject* child;
        CCARRAY_FOREACH(m_pChildNode, child)
        {
            CCNode* pChild = (CCNode*) child;
            if (pChild)
            {
                m_maxHeight += pChild->getContentSize().height;
                m_maxWidth = max(m_maxWidth, pChild->getContentSize().width);
            }
        }
    }
    
    m_maxWidth += m_pIcon->getContentSize().width + 50;
    m_maxHeight += 20;
    
    
    
    int width = m_pColorLayer->getContentSize().width;
    int height = m_maxHeight;
    m_pColorLayer->setContentSize(CCSize(width,height));
    
    computerPt(m_pt);
    posNode();
}

void TipMgr::posNode()
{
    if(m_pChildNode && m_pChildNode->count() > 0)
    {
        CCObject* child;
        CCARRAY_FOREACH(m_pChildNode, child)
        {
            CCNode* node = (CCNode*) child;
            if (node)
            {
                if(m_childcnt == 0)
                {
                    node->setPosition(ccp(node->getContentSize().width/2, m_pColorLayer->getContentSize().height-node->getContentSize().height-m_tapy));
                }
                else
                {
                    CCNode* prevnode = (CCNode*)m_pColorLayer->getChildByTag(m_childcnt-1);
                    if(prevnode)
                    {
                        node->setPosition(ccp(node->getContentSize().width/2,
                                              prevnode->getPosition().y - prevnode->getContentSize().height/2 - node->getContentSize().height/2));
                    }
                }
                
                m_pColorLayer->addChild(node,0,m_childcnt);
                m_childcnt += 1;
            }
        }
    }
    
    m_pColorLayer->setAnchorPoint(ccp(0.5f, 0.5f));
    m_pColorLayer->setPosition(ccp(m_pt.x - m_pColorLayer->getContentSize().width/2,
                                   m_pt.y - m_pColorLayer->getContentSize().height/2));
    m_pColorLayer->addChild(m_pIcon);
    
    m_pIcon->setPosition(ccp(m_pColorLayer->getContentSize().width - m_pIcon->getContentSize().width/2-m_tapx,
                             m_pColorLayer->getContentSize().height - m_pIcon->getContentSize().height/2-m_tapy));
    
    float scalex = 1.0f*m_pColorLayer->getContentSize().width/m_bkSprite->getContentSize().width;
    float scaley = 1.0f*m_pColorLayer->getContentSize().height/m_bkSprite->getContentSize().height;
    m_bkSprite->setScaleX(scalex);
    m_bkSprite->setScaleY(scaley);
    m_bkSprite->setPosition(m_pt);
}

void TipMgr::destroyTip()
{
    if(m_pColorLayer)
    {
        m_pColorLayer->removeFromParent();
        m_pColorLayer = NULL;
    }
    
    if(m_bkSprite)
    {
        m_bkSprite->removeFromParent();
        m_bkSprite = NULL;
    }
}

void TipMgr::computerPt(cocos2d::CCPoint pt)
{
    float scaleFactor = UIManager::sharedManager()->getScaleFactor();
    CCSize winsize = CCDirector::sharedDirector()->getWinSize();
    
    if(pt.x < winsize.width/2){
        m_pt.x = pt.x + m_pColorLayer->getContentSize().width;
        
        if(winsize.width >= 1280)
            pt.x -= 30;
    }
    
    if(pt.x >= winsize.width/2){
        m_pt.x = pt.x - m_pColorLayer->getContentSize().width;
    }
    
    if(m_pt.y + m_pColorLayer->getContentSize().width/2  + 90 > winsize.height)
        m_pt.y -= 90;
    
    
    m_pt.x *= scaleFactor;
    m_pt.y *= scaleFactor;
}


