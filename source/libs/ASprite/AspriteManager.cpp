//
//  AspriteManager.cpp
//
//  Created by arthurgong on 11-11-29.
//  Copyright 2011Äê __MyCompanyName__. All rights reserved.
//

#include "AspriteManager.h"
#include "spriteDataList.h"
#include "TXGUI.h"

static AspriteManager* _iserInstance = null;

AspriteManager* AspriteManager::getInstance()
{
    if(_iserInstance == null)
    {
        _iserInstance = new AspriteManager();
    }
    return _iserInstance;
}

void AspriteManager::purgeInstance()
{
    SAFE_DEL(_iserInstance);
}

AspriteManager::AspriteManager()
{
    m_init = false;
}

AspriteManager::~AspriteManager()
{
    clearAllAsprite();
}

void AspriteManager::loadAllAsprite()
{    
	if(!m_init)
	{
		for(int i = 0; i < SPRITE_NUM; i++)
		{
			ASprite* asprite = new ASprite();
			char binPath[255] = {'\0'};
			char pngPath[255] = {'\0'};
			strcat(binPath, spriteDataList[i*2]);
			strcat(pngPath, spriteDataList[i*2+1]);
			asprite->loadFile(binPath, pngPath);
			addAsprite(spriteDataList[i*2], asprite);
		}
		m_init = true;
	}
}

void AspriteManager::addAsprite(string key, ASprite * asprite)
{
    m_asMap.insert( map<string, ASprite*>::value_type(key, asprite) );
}

ASprite* AspriteManager::getAsprite(string key)
{      
    MAP_ASPRITE_ITER iter = m_asMap.find(key);
    
	if(iter != m_asMap.end())
		return iter->second;

    return NULL;
}

void AspriteManager::clearAllAsprite()
{
    MAP_ASPRITE_ITER iter = m_asMap.begin();   
    for (; iter != m_asMap.end(); iter++) {
        SAFE_DEL(iter->second);
    }

    m_asMap.clear();
	m_init = false;
}

CCSprite* AspriteManager::getOneFrame(std::string key,std::string frameName)
{
	int iSpriteFrame = TXGUI::getResourceIDByName(frameName.c_str());

	ASprite *as = AspriteManager::getInstance()->getAsprite(key); 
	if (as == 0)
	{
		return 0;
	}
	CCPoint pos;
	CCSprite * pSprite = as->getSpriteFromFrame_Middle(iSpriteFrame, 0,pos);
	return pSprite;
}

CCSprite* AspriteManager::getFramesRelativePos(std::string key,std::string parentFrame,std::string childFrame,
	CCPoint childFrameAnchorPoint,CCPoint &pos)
{
	int iParentSpriteFrame = TXGUI::getResourceIDByName(parentFrame.c_str());
	int iChildSpriteFrame = TXGUI::getResourceIDByName(childFrame.c_str());

	ASprite *as = AspriteManager::getInstance()->getAsprite(key); 
	if (as == 0)
	{
		return 0;
	}
	CCPoint parent_pos;
	CCPoint child_pos;
	CCSprite * pParentSprite = as->getSpriteFromFrame_Middle(iParentSpriteFrame, 0,parent_pos);
	if (pParentSprite == 0)
	{
		return 0;
	}
	CCSprite * pChildSprite = as->getSpriteFromFrame_Middle(iChildSpriteFrame, 0,child_pos);
	if (pChildSprite == 0)
	{
		return 0;
	}
	pos = ccpSub(child_pos,parent_pos);
	CCPoint offsetAnchorPoint = ccpSub(childFrameAnchorPoint,ccp(0.5,0.5));
	CCSize size = pChildSprite->getContentSize();
	pos.x += size.width*offsetAnchorPoint.x;
	pos.y += size.height*offsetAnchorPoint.y;

	return pChildSprite;
}