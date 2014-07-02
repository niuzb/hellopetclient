//
//  NPC.cpp
//  iSeer
//
//  Created by wuwei on 3/7/12.
//  Copyright 2012 Taomee.Inc. All rights reserved.
//

#include "NPC.h"
#include "NPCManager.h"
#include "GameManager.h"
#include "LevelDefine.h"

#include "MapDataManager.h"
#include "GameFontManager.h"
#include "CrossPlatform.h"


using namespace cocos2d;

#define IMG_EXCLAMATION     "Img_exclam.png"
#define IMG_QUESTION        "Img_question.png"
#define IMG_QUESTION_GRAY   "Img_question_grey.png"
#define IMG_VS              "Img_VS.png"
#define FONT_SIZE_NAME      20

NPC::NPC(int npcID)
	:m_npcID(npcID)
	,m_isShowOnMap(false)
	,m_canSubmitQuest(false)
	,m_hasInProgressQuest(false)
	,m_canPublishQuest(false)
	,m_pAnim(NULL)
	,m_pSprite(NULL)
	,m_pNameLabel(NULL)
	,m_pSignSprite(NULL)
	,m_pNameBkg(NULL)
	,m_pTalkLayer(NULL)
	,m_canPlayEffect(true)
{
	CCNode::onEnter();
}

NPC::NPC(FILE* fp)
	:m_isShowOnMap(false)
	,m_canSubmitQuest(false)
	,m_hasInProgressQuest(false)
	,m_canPublishQuest(false)
	,m_pAnim(NULL)
	,m_pSprite(NULL)
	,m_pNameLabel(NULL)
	,m_pSignSprite(NULL)
	,m_pNameBkg(NULL)
	,m_pTalkLayer(NULL)
	,m_canPlayEffect(true)
{
	fread(&m_npcID, sizeof(m_npcID), 1, fp);
	fread(&m_funcType, sizeof(m_funcType), 1, fp);
	fread(&m_defaultDialog, sizeof(m_defaultDialog), 1, fp);
	fread(&m_fightDialog, sizeof(m_fightDialog), 1, fp);
	fread(&m_mapID, sizeof(m_mapID), 1, fp);
	fread(&m_posX, sizeof(m_posX), 1, fp);
	fread(&m_posY, sizeof(m_posY), 1, fp);
	fread(&m_resourceID, sizeof(m_resourceID), 1, fp);
	fread(&m_monsterID, sizeof(m_monsterID), 1, fp);

	if(IsRetinaDisplay())
	{
		m_posX *= (480.0f/1024.0f);
		m_posY *= (320.0f/768.0f);
	}

	CCNode::onEnter();
}

//by Stanley
NPC::NPC(unsigned char* buffer, int& readSize)
	:m_isShowOnMap(false)
	,m_canSubmitQuest(false)
	,m_hasInProgressQuest(false)
	,m_canPublishQuest(false)
	,m_pAnim(NULL)
	,m_pSprite(NULL)
	,m_pNameLabel(NULL)
	,m_pSignSprite(NULL)
	,m_pNameBkg(NULL)
	,m_pTalkLayer(NULL)
	,m_canPlayEffect(true)
{
    memcpy(&m_npcID, buffer + readSize, sizeof(m_npcID));
    readSize += sizeof(m_npcID);
    memcpy(&m_funcType, buffer + readSize, sizeof(m_funcType));
    readSize += sizeof(m_funcType);
    memcpy(&m_defaultDialog, buffer + readSize, sizeof(m_defaultDialog));
    readSize += sizeof(m_defaultDialog);
    memcpy(&m_fightDialog, buffer + readSize, sizeof(m_fightDialog));
    readSize += sizeof(m_fightDialog);
    memcpy(&m_mapID, buffer + readSize, sizeof(m_mapID));
    readSize += sizeof(m_mapID);
    memcpy(&m_posX, buffer + readSize, sizeof(m_posX));
    readSize += sizeof(m_posX);
    memcpy(&m_posY, buffer + readSize, sizeof(m_posY));
    readSize += sizeof(m_posY);
    memcpy(&m_resourceID, buffer + readSize, sizeof(m_resourceID));
    readSize += sizeof(m_resourceID);
    memcpy(&m_monsterID, buffer + readSize, sizeof(m_monsterID));
    readSize += sizeof(m_monsterID);
    
	CCPoint pt = LevelMultiResolution::sTransformPointToMap(ccp(m_posX, m_posY));
	m_posX = pt.x;
	m_posY = pt.y;
}

NPC::~NPC()
{
	removeAnim();

	// remove label
	if(m_pNameLabel)
	{
		m_pNameLabel->removeFromParentAndCleanup(true);
	}
	if(m_pNameBkg)
	{
		m_pNameBkg->removeFromParentAndCleanup(true);
	}

	CCNode::onExit();
}

// create animation
void NPC::createAnim(CCNode* pParent)
{
    if(m_funcType == NPC_BOSS)
    {
        m_pAnim = EnginePlayerManager::getInstance()->addAnimSprite(m_monsterID, AnimSprite::ANIM_TYPE_MOVE, 0, 0);
        m_pAnim->SetAnim(0,1,true);
    }
    else
    {
        m_pAnim = EnginePlayerManager::getInstance()->addAnimSprite(m_resourceID, AnimSprite::ANIM_TYPE_NPC, 0, 0);
        m_pAnim->SetAnim(1,1,true);
    }
  
    m_pSprite = CCSprite::create();
    m_pSprite->addChild(m_pAnim->getBatchNode());
    
    float deviceScale = CCDirector::sharedDirector()->getContentScaleFactor();
    m_pSprite->setPosition(ccp(m_posX / deviceScale,m_posY / deviceScale));
    
    
	m_pSprite->setScale(LevelMultiResolution::sGetLevelScale());

    pParent->addChild(m_pSprite, LevelLayer::sCalcZorder(m_pSprite->getPosition()));
    
    // adjust toward if is BOSS-NPC
    if(m_funcType == NPC_BOSS)
    {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        if((m_posX / deviceScale) > winSize.width * 0.5f)
        {
            m_pAnim->SetTransform(GameEnginePlayer::TRANS_MIRROR);
        }
    }
}

// remove animation
void NPC::removeAnim()
{
    EnginePlayerManager::getInstance()->removeAsprite(m_pAnim);
    
    if(m_pSprite)
    {
        m_pSprite->removeFromParentAndCleanup(true);
        delete m_pSprite;
        m_pSprite = NULL;
        
        m_pNameLabel = NULL;
		m_pSignSprite = NULL;
		m_pNameBkg = NULL;
    }
}

// attach NPC name
void NPC::attachName()
{
	CCRect bound = m_pAnim->getFirstFrameRect();
    
	// create label
	const char* name = getName();
	m_pNameLabel = CCLabelTTF::create(CCLocalizedString(name, name), KJLinXin, FONT_SIZE_NAME / CC_CONTENT_SCALE_FACTOR());
	m_pNameLabel->setColor(ccYELLOW);

	CCSize labelSize = m_pNameLabel->getContentSize();
	CCPoint labelPos = ccp(0, bound.size.height + labelSize.height * 0.5f);

	// create label bkg
	m_pNameBkg = NameBkg::bkgWithParams(labelPos, labelSize.width * 1.2f, labelSize.height * 1.2f, ccBLACK);

	m_pSprite->addChild(m_pNameBkg);
	m_pSprite->addChild(m_pNameLabel);

	// adjust label position
	m_pNameLabel->setPosition(labelPos);
}

// attach sign on the head
void NPC::attachSign()
{
	// attach sign sprite
	int signType = SIGN_NONE;
	if(needChallengeForQuest())
	{
		signType = SIGN_VS;
	}
	else if(m_canSubmitQuest)
	{
		signType = SIGN_QUESTION;
	}
	else if(m_canPublishQuest)
	{
		signType = SIGN_EXCLAMATION;
	}
	else if(m_hasInProgressQuest)
	{
		signType = SIGN_QUESTION_GRAY;
	}

	// remove it firstly
	if(m_pSignSprite)
	{
		m_pSignSprite->removeFromParentAndCleanup(true);
		m_pSignSprite = NULL;
	}

	// create sign sprite
	switch(signType)
	{
	case SIGN_EXCLAMATION:
		m_pSignSprite = CCSprite::createWithSpriteFrameName(IMG_EXCLAMATION);
		break;
	case SIGN_QUESTION:
		m_pSignSprite = CCSprite::createWithSpriteFrameName(IMG_QUESTION);
		break;
	case SIGN_QUESTION_GRAY:
		m_pSignSprite = CCSprite::createWithSpriteFrameName(IMG_QUESTION_GRAY);
		break;
	case SIGN_VS:
		m_pSignSprite = CCSprite::createWithSpriteFrameName(IMG_VS);
		break;
	default:
		break;
	}

	// attach sign sprite
	if(m_pSignSprite)
	{
		m_pSignSprite->setAnchorPoint(ccp(0.5f,0.0f));
		CCRect bound = m_pAnim->getFirstFrameRect();
		m_pSignSprite->setPosition(ccp(0, bound.size.height + m_pNameLabel->getContentSize().height));
		m_pSprite->addChild(m_pSignSprite);
	}
}

// show on the map
void NPC::showOnMap(cocos2d::CCNode* pParent)
{
	if(!m_isShowOnMap)
	{
		// create animation
		createAnim(pParent);

		// attach NPC name
		attachName();

		// attach sign
		attachSign();
	}

	m_isShowOnMap = true;
}

// remove from map
void NPC::removeFromMap()
{
    removeAnim();
    
    m_isShowOnMap = false;
}

// whether this NPC needs challenging because of a quest?
bool NPC::needChallengeForQuest()
{
	return false;
}

// add publish quest
void NPC::addPublishQuest(uint16_t questID)
{
    m_publishQuests.insert(questID);
    m_canPublishQuest = true;
    
    if(m_isShowOnMap)
    {
        // refresh the sign
        attachSign();
    }
}

// some quest has been published
// remove it from the publish list
void NPC::questPublished(uint16_t questID)
{
    // find the quest in the publish list
    set<uint16_t>::iterator it = m_publishQuests.begin();
    for(; it != m_publishQuests.end(); ++it)
    {
        if((*it) == questID)
        {
            // remove the quest ID from the publish list
            m_publishQuests.erase(it);
            break;
        }
    }
    
    // if the publish list becomes empty, NPC's publishing state should change
    if(m_publishQuests.empty())
    {
        m_canPublishQuest = false;
        
        // change the sign over NPC's head
        if(m_isShowOnMap)
        {
            // refresh the sign
            attachSign();
        }
    }
}

// a new quest has been accepted
// add the quest ID to the underway list
void NPC::questAccepted(uint16_t questID)
{
    // add to the underway list
    m_underwayQuests.insert(questID);
    
    // if the underway list becomes not empty, NPC's state should change
    if(m_underwayQuests.size() == 1)
    {
        m_hasInProgressQuest = true;
        
        // change the sign over NPC's head
        if(m_isShowOnMap)
        {
            // refresh the sign
            attachSign();
        }
    }
}

// some underway quest has finished
// move the quest ID to the submit list
void NPC::questFinished(uint16_t questID)
{
    // find the quest in the underway list
    set<uint16_t>::iterator it = m_underwayQuests.begin();
    for(; it != m_underwayQuests.end(); ++it)
    {
        if((*it) == questID)
        {
            // remove the qeust ID from the in-progress list
            m_underwayQuests.erase(it);
            break;
        }
    }
    
    // add to the submit quest list
    m_submitQuests.insert(questID);
    
    // if the underway list becomes empty, or the submit list becomes not empty
    // NPC's state should change
    if(m_underwayQuests.empty() || m_submitQuests.size() == 1)
    {
        m_hasInProgressQuest = !m_underwayQuests.empty();
        m_canSubmitQuest = !m_submitQuests.empty();
        
        // change the sign over NPC's head
        if(m_isShowOnMap)
        {
            // refresh the sign
            attachSign();
        }
    }
}

// some finished quest has been submitted
// remove the quest ID from the submit list
void NPC::questSubmitted(uint16_t questID)
{
    // find the quest in the submit list
    set<uint16_t>::iterator it = m_submitQuests.begin();
    for(; it != m_submitQuests.end(); ++it)
    {
        if((*it) == questID)
        {
            // remove the quest ID from the submit list
            m_submitQuests.erase(it);
            break;
        }
    }
    
    // if the submit list becomes empty, change NPC's state
    if(m_submitQuests.empty())
    {
        // change submit flag
        m_canSubmitQuest = false;
        
        // change the sign over NPC's head
        if(m_isShowOnMap)
        {
            // refresh the sign
            attachSign();
        }
    }
}

// some quest has been canceled
// remove it and add to publish quest
void NPC::questCanceled(uint16_t questID)
{
	// find the quest in the underway list
	set<uint16_t>::iterator it = m_underwayQuests.begin();
	for(; it != m_underwayQuests.end(); ++it)
	{
		if((*it) == questID)
		{
			// remove the qeust ID from the in-progress list
			m_underwayQuests.erase(it);

			// if the underway list becomes empty
			// NPC's state should change
			if(m_underwayQuests.empty())
			{
				m_hasInProgressQuest = false;

				// change the sign over NPC's head
				if(m_isShowOnMap)
				{
					// refresh the sign
					attachSign();
				}
			}
			return;
		}
	}

	// find the quest in the submit list
	it = m_submitQuests.begin();
	for(; it != m_submitQuests.end(); ++it)
	{
		if((*it) == questID)
		{
			// remove the quest ID from the submit list
			m_submitQuests.erase(it);

			// if the submit list becomes empty, change NPC's state
			if(m_submitQuests.empty())
			{
				// change submit flag
				m_canSubmitQuest = false;

				// change the sign over NPC's head
				if(m_isShowOnMap)
				{
					// refresh the sign
					attachSign();
				}
			}
			return;
		}
	}
}

// process touch
bool NPC::processTouch(CCPoint touchPoint)
{
	//play boss words    
	if((m_funcType == NPC_BOSS) && m_canPlayEffect && isTouched(touchPoint))
	{
		//GameAudioManager::sharedManager()->playEffectWithID(m_monsterID, 0);

		m_canPlayEffect = false;
	}        

	
	return true;
}


// whether be touched or not
bool NPC::isTouched(CCPoint touchPoint)
{
    if(!m_pSprite || !m_pSprite->isVisible())
    {
        return false;
    }
    
    // calculate the bound of NPC
    CCPoint myPos   = m_pSprite->getPosition();
    CCRect  bound   = m_pAnim->getFirstFrameRect();
    float   halfW   = bound.size.width * 0.5f;
    float   minX    = myPos.x - halfW;
    float   maxX    = myPos.x + halfW;
    float   minY    = myPos.y;
    float   maxY    = myPos.y + bound.size.height;
    
    bool isTouch = (touchPoint.x > minX && touchPoint.x < maxX && touchPoint.y > minY && touchPoint.y < maxY);
    if(!isTouch && m_pSignSprite)
    {
        // calculate the bound of the sign sprite
        CCPoint signPos = m_pSignSprite->getPosition();
        signPos.x += myPos.x;
        signPos.y += myPos.y;
        CCSize signSize = m_pSignSprite->getContentSize();
        halfW   = signSize.width * 0.5f;
        minX    = signPos.x - halfW;
        maxX    = signPos.x + halfW;
        minY    = signPos.y;
        maxY    = signPos.y + signSize.height;
        isTouch = (touchPoint.x > minX && touchPoint.x < maxX && touchPoint.y > minY && touchPoint.y < maxY);
    }
    
    return isTouch;
}

// show contents talking with player
void NPC::showTalkContent()
{    
    // create the talking layer
    
}

// fight with me! if only it's a BOSS-NPC
void NPC::fightWithMe()
{
	// TODO QUEST: send fight with NPC to server with NPCid
    
}

const char* NPC::getName()
{
    return NPCManager::sharedManager()->getNpcName(m_npcID);
}

void NPC::updatePlayEffectSchedule(float dt)
{
	this->unschedule(schedule_selector(NPC::updatePlayEffectSchedule));
	m_canPlayEffect = true;
}