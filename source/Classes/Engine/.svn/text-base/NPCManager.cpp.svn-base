//
//  NPCManager.cpp
//  iSeer
//
//  Created by wuwei on 3/7/12.
//  Copyright 2012 Taomee.Inc. All rights reserved.
//

#include "NPCManager.h"
#include "NPC.h"
#include "GameResourceManager.h"

using namespace cocos2d;

#define NPC_BIN "Actor/npc.bin"
#define NPC_NAME_PLIST  "Data/NpcName.plist"

NPCManager* NPCManager::pSharedManager = NULL;

NPCManager::NPCManager()
	:m_isTalking(false)
	,m_canTouch(true)
	,m_isPVPTalking(false)
{
    m_npcMap.clear();
    m_npcName.clear();
    initialize();
}

NPCManager::~NPCManager()
{
    removeAllNPCs();
}

NPCManager* NPCManager::sharedManager()
{
    if(!pSharedManager)
    {
        pSharedManager = new NPCManager();
    }
    return pSharedManager;
}

void NPCManager::purgeInstance()
{
    if(pSharedManager)
    {
        delete pSharedManager;
        pSharedManager = NULL;
    }
}

// initialize all NPCs
void NPCManager::initialize()
{
    // initialize NPC names
    initNpcNames();
    
    // initialize NPC data
    //initNpcData();
}

// initialize NPC names
void NPCManager::initNpcNames()
{
	// read NpcName.plist
	const char* pszPath = GameResourceManager::sharedManager()->storedFullPathFromRelativePath(NPC_NAME_PLIST);
	CCDictionary *pNameDict = CCFileUtils::dictionaryWithContentsOfFile(pszPath);

	CCDictElement* pElement = NULL;
	CCDICT_FOREACH(pNameDict, pElement)
	{
		if (pNameDict->objectForKey(pElement->getStrKey()))
		{
			string strNpcID = pElement->getStrKey();
			string strName = ((CCString*)pElement->getObject())->toStdString();
			uint8 npcID = atoi(strNpcID.c_str());
			m_npcName[npcID] = strName;
		}
	}

}

// initialize NPC data
void NPCManager::initNpcData()
{
    //by Stanley
    CCFileData data(GameResourceManager::sharedManager()->storedFullPathFromRelativePath(NPC_BIN), "rb");
    unsigned char* buffer = data.getBuffer();
    int fileSize = data.getSize();
    int readSize = 0;
    
    if (fileSize > 0)
    {
        uint16_t numNpcs = 0;
        memcpy(&numNpcs, buffer + readSize, sizeof(numNpcs));
        readSize += sizeof(numNpcs);
        for(uint16_t i = 0; i < numNpcs; ++i)
        {
            // create NPC
			NPC* pNPC = new NPC(buffer, readSize);

			// TODO
            m_npcMap[pNPC->getID()] = pNPC;
        }
    }

}

// remove all NPCs
void NPCManager::removeAllNPCs()
{
    map<uint8_t, NPC*>::iterator it = m_npcMap.begin();
    for(; it != m_npcMap.end(); ++it)
    {
        delete it->second;
        it->second = NULL;
    }
    m_npcMap.clear();
}

// remove a specific NPC
void NPCManager::removeNPC(uint8_t npcID)
{
	map<uint8_t, NPC*>::iterator it = m_npcMap.find(npcID);
	if(it != m_npcMap.end())
	{
		delete it->second;
		m_npcMap.erase(it);
	}
}

// show NPC on the specified map
void NPCManager::showNpcOnMap(uint16_t mapID, CCNode* pParent)
{
    map<uint8_t, NPC*>::iterator iter = m_npcMap.begin();
    for(; iter != m_npcMap.end(); ++iter)
    {
        NPC* pNPC = iter->second;
        if(pNPC->getMapID() == mapID)
        {
            pNPC->showOnMap(pParent);
        }
    }
}

// remove all NPCs from the map
void NPCManager::removeNpcsFromMap(uint16_t mapID)
{
    map<uint8_t, NPC*>::const_iterator iter = m_npcMap.begin();
    for(; iter != m_npcMap.end(); ++iter)
    {
        NPC* pNPC = iter->second;
        if(pNPC->getMapID() == mapID)
        {
            pNPC->removeFromMap();
        }
    }
}

void NPCManager::removeNpcFromMap(uint8_t npcID)
{
	map<uint8_t, NPC*>::const_iterator iter = m_npcMap.begin();
	for(; iter != m_npcMap.end(); ++iter)
	{
		NPC* pNPC = iter->second;
		if(pNPC->getID() == npcID)
		{
			pNPC->removeFromMap();
		}
	}
}

// get NPC by boss ID
NPC* NPCManager::getNpcByBossID(uint16_t bossID)
{
	map<uint8_t, NPC*>::const_iterator iter = m_npcMap.begin();
	for(; iter != m_npcMap.end(); ++iter)
	{
		NPC* pNPC = iter->second;
		if(pNPC->getMonsterID() == bossID)
		{
			return pNPC;
		}
	}

	return NULL;
}

// process touch
bool NPCManager::processTouch(CCPoint touchPoint)
{
	if(m_canTouch)
	{
        float deviceScale = CC_CONTENT_SCALE_FACTOR();
        CCPoint tPoint = CCPoint(touchPoint.x / deviceScale, touchPoint.y / deviceScale);
		map<uint8_t, NPC*>::const_iterator iter = m_npcMap.begin();
		for(; iter != m_npcMap.end(); ++iter)
		{
			NPC* pNPC = iter->second;
			if(pNPC->isShowOnMap() && pNPC->processTouch(tPoint))
			{
				return true;
			}
		}
	}

	return false;
}