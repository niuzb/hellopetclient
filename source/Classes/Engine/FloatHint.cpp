//
//  FloatHint.cpp
//  iSeer
//
//  Created by wuwei on 3/31/12.
//  Copyright (c) 2012 Taomee.Inc. All rights reserved.
//

#include "FloatHint.h"
#include "CrossUtil.h"

using namespace cocos2d;

// ------------------------------------------------------------
// ------------------------------------------------------------
// class FloatHint implementation

#define MAX_CHAR        64
#define HINT_DEPTH      100000  // hints display over all other layers

#define HINT_FONT       "Arial"
#define HINT_FONT_SIZE  20

#define HINT_ROW_SPACE  30
#define HINT_FADE_TIME  0.5
#define HINT_STAY_TIME  1

#define COLOR_NORMAL    ccYELLOW
#define COLOR_KEY       ccc3(255,0,128)

FloatHint* FloatHint::pSharedInstance = NULL;

FloatHint::FloatHint()
:m_maxWidth(0)
{
    m_pHintBkg = new FloatHintBkg();
    m_hintNodes.clear();
}

FloatHint::~FloatHint()
{
    if(m_pHintBkg)
    {
        delete m_pHintBkg;
        m_pHintBkg = NULL;
    }
    
    for(int i = 0; i < (int)m_hintNodes.size(); ++i)
    {
        m_hintNodes[i]->removeFromParentAndCleanup(true);
    }
    m_hintNodes.clear();
}

FloatHint* FloatHint::sharedInstance()
{
    if(!pSharedInstance)
    {
        pSharedInstance = new FloatHint();
    }
    return pSharedInstance;
}

void FloatHint::purgeInstance()
{
    if(pSharedInstance)
    {
        delete pSharedInstance;
        pSharedInstance = NULL;
    }
}

void FloatHint::pushHint(int type, const char *key, int count)
{
    switch (type)
    {
        case HINT_GET_ITEM:
        case HINT_MINE_RECYCLING:
        {
            pushHint_getItem(type, key, count);
            break;
        }
        case HINT_ACCEPT_QUEST:
        case HINT_FINISH_QUEST:
        case HINT_SUBMIT_QUEST:
        {
            pushHint_quest(type, key);
            break;
        }
        case HINT_SPRITE_TO_BAG:
        case HINT_SPRITE_TO_STORAGE:
        {
            pushHint_getSprite(type, key);
            break;
        }
        case HINT_EXTEND_STORAGE:
        {
            pushHint_extendStorage();
            break;
        }
        default:
            break;
    }
    
    // first hint since last show
    // set hint background visible
    if(m_hintNodes.size() == 1)
    {
        CCDirector::sharedDirector()->getRunningScene()->addChild(m_pHintBkg, HINT_DEPTH - 1);
    }
    
    // calculate current range of all hint rows
    // set the proper width and height to the background
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint leftTop = ccp((winSize.width - m_maxWidth) * 0.5f, (winSize.height + HINT_ROW_SPACE) * 0.5f);
    m_pHintBkg->setLeftTop(leftTop);
    m_pHintBkg->setWidth(m_maxWidth);
    m_pHintBkg->setHeight(m_hintNodes.size() * HINT_ROW_SPACE);
}

void FloatHint::pushHint_getItem(int type, const char* key, int count)
{
    // set strings
    const char* strPre = "";
    if(type == HINT_GET_ITEM)
    {
        strPre = CCLocalizedString("HINT_GET_ITEM", "HINT_GET_ITEM");
    }
    else if(type == HINT_MINE_RECYCLING)
    {
        strPre = CCLocalizedString("HINT_MINE_RECYCLING", "HINT_MINE_RECYCLING");
    }
    char strKey[MAX_CHAR];
    sprintf(strKey, CCLocalizedString("HINT_KEY", "HINT_KEY"), key);
    char strCount[MAX_CHAR];
    sprintf(strCount, "x%d", count);
    
    // set labels
    setLabels(strPre, strKey, strCount);
}

void FloatHint::pushHint_quest(int type, const char* key)
{
    // set strings
    char strKey[MAX_CHAR];
    sprintf(strKey, CCLocalizedString("HINT_KEY", "HINT_KEY"), key);
    
    const char* strPre = "";
    const char* strPost = "";
    if(type == HINT_ACCEPT_QUEST)
    {
        strPre = CCLocalizedString("HINT_ACCEPT_QUEST_PRE", "HINT_ACCEPT_QUEST_PRE");
    }
    else if(type == HINT_FINISH_QUEST)
    {
        strPre  = CCLocalizedString("HINT_FINISH_QUEST_PRE", "HINT_FINISH_QUEST_PRE");
        strPost = CCLocalizedString("HINT_FINISH_QUEST_POST", "HINT_FINISH_QUEST_POST");
    }
    else // HINT_SUBMIT_QUEST
    {
        strPre  = CCLocalizedString("HINT_SUBMIT_QUEST_PRE", "HINT_SUBMIT_QUEST_PRE");
    }
    
    // set labels
    setLabels(strPre, strKey, strPost);
}

void FloatHint::pushHint_getSprite(int type, const char* key)
{
    // set strings
    char strKey[MAX_CHAR];
    sprintf(strKey, CCLocalizedString("HINT_KEY", "HINT_KEY"), key);
    
    const char* strPre = "";
    const char* strPost = "";
    if(type == HINT_SPRITE_TO_BAG)
    {
        strPost = CCLocalizedString("HINT_SPRITE_TO_BAG", "HINT_SPRITE_TO_BAG");
    }
    else // HINT_SPRITE_TO_STORAGE
    {
        strPost = CCLocalizedString("HINT_SPRITE_TO_STORAGE", "HINT_SPRITE_TO_STORAGE");
    }
    
    // set labels
    setLabels(strPre, strKey, strPost);
}

void FloatHint::pushHint_extendStorage()
{
    // set strings
    const char* strPre = CCLocalizedString("HINT_EXTEND_STORAGE", "HINT_EXTEND_STORAGE");
    
    // set labels
    setLabels(strPre, "", "");
}

void FloatHint::setLabels(const char *strPre, const char *strKey, const char *strPost)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    int rowIndex = m_hintNodes.size() + 1;
    
    // labels
    CCLabelTTF* pLabelPre   = CCLabelTTF::create(strPre, HINT_FONT, HINT_FONT_SIZE);
    CCLabelTTF* pLabelKey   = CCLabelTTF::create(strKey, HINT_FONT, HINT_FONT_SIZE);
    CCLabelTTF* pLabelPost  = CCLabelTTF::create(strPost, HINT_FONT, HINT_FONT_SIZE);
    pLabelPre->setColor(COLOR_NORMAL);
    pLabelKey->setColor(COLOR_KEY);
    pLabelPost->setColor(COLOR_NORMAL);
    CCSize sizePre  = pLabelPre->getContentSize();
    CCSize sizeKey  = pLabelKey->getContentSize();
    CCSize sizePost = pLabelPost->getContentSize();
    
    // adjust position
    float totalWidth = sizePre.width + sizeKey.width + sizePost.width;
    m_maxWidth = MAX(totalWidth, m_maxWidth);
    pLabelPre->setAnchorPoint(ccp(0.0f, 0.5f));
    pLabelPre->setPosition(ccp((winSize.width - totalWidth) * 0.5f, winSize.height * 0.5f - HINT_ROW_SPACE * rowIndex));
    pLabelKey->setAnchorPoint(ccp(0.0f, 0.5f));
    pLabelKey->setPosition(ccp(pLabelPre->getPosition().x + sizePre.width, pLabelPre->getPosition().y));
    pLabelPost->setAnchorPoint(ccp(0.0f, 0.5f));
    pLabelPost->setPosition(ccp(pLabelKey->getPosition().x + sizeKey.width, pLabelKey->getPosition().y));
    
    // add to layer
    CCNode* pNode = CCNode::create();
    pNode->setPosition(CCPointZero);
    m_hintNodes.push_back(pNode);
    CCDirector::sharedDirector()->getRunningScene()->addChild(pNode, HINT_DEPTH, rowIndex);
    pNode->addChild(pLabelPre);
    pNode->addChild(pLabelKey);
    pNode->addChild(pLabelPost);
    
    // fade in labels
    fadeIn(pNode);
}

void FloatHint::fadeIn(CCNode *pNode)
{    
    CCArray* children = pNode->getChildren();
    for(size_t i = 0; i < children->count(); ++i)
    {
        CCLabelTTF* pLabel = (CCLabelTTF*)children->objectAtIndex(i);
        pLabel->setOpacity(0);
        CCFadeTo* fade = CCFadeTo::create(HINT_FADE_TIME, 255);
        pLabel->runAction(fade);
    }
    
    CCMoveBy* move = CCMoveBy::create(HINT_FADE_TIME, ccp(0, HINT_ROW_SPACE));
    CCDelayTime* delay = CCDelayTime::create(HINT_STAY_TIME);
    CCCallFuncN* func = CCCallFuncN::create(this, callfuncN_selector(FloatHint::fadeOut));
    CCFiniteTimeAction* seq = CCSequence::create(move, delay, func, NULL);
    pNode->runAction(seq);
}

void FloatHint::fadeOut(CCNode *pNode)
{
    CCArray* children = pNode->getChildren();
    for(size_t i = 0; i < children->count(); ++i)
    {
        CCLabelTTF* pLabel = (CCLabelTTF*)children->objectAtIndex(i);
        CCFadeTo* fade = CCFadeTo::create(HINT_FADE_TIME, 0);
        pLabel->runAction(fade);
    }
    
    CCMoveBy* move = CCMoveBy::create(HINT_FADE_TIME, ccp(0, HINT_ROW_SPACE));
    CCCallFunc* func = CCCallFuncN::create(this, callfuncN_selector(FloatHint::hintEnd));
    CCFiniteTimeAction* seq = CCSequence::create(move, func, NULL);
    pNode->runAction(seq);
}

void FloatHint::hintEnd(CCNode *pNode)
{
    pNode->removeFromParentAndCleanup(true);
    
    int rowIndex = pNode->getTag();
    if(rowIndex == m_hintNodes.size())
    {
        m_hintNodes.clear();
        m_pHintBkg->removeFromParentAndCleanup(true);
        m_maxWidth = 0;
    }
}

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------

// -----------------------------------------------------------------------
// class FloatHintBkg implementation

#include "Painter.h"

void FloatHintBkg::draw()
{
    Painter::drawHintBkg(m_leftTop, m_width, m_height);
}

// -----------------------------------------------------------------------