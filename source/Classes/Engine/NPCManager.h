//
//  NPCManager.h
//  iSeer
//
//  Created by wuwei on 3/7/12.
//  Copyright 2012 Taomee.Inc. All rights reserved.
//

#ifndef _NPC_MANAGER_H_
#define _NPC_MANAGER_H_

#include "NPC.h"
#include "cocos2d.h"

// currently only NPC_BATI publishes daily quests
// if later another NPC publishes daily quests too, the logic of daily quests should be modified
// see "void checkPublishQuest()"
#define DAILY_QUEST_NPC 4
#define SPECIAL_NPC_ID_RAYE  200
#define SPECIAL_BOSS_ID_RAYE 90

#define NPC_QIQI    19
#define NPC_DORO    3
#define NPC_SEER    6

class NPCManager
{
public:
    // constructor and destructor
    NPCManager();
    ~NPCManager();
    
    // get unique instance
    static NPCManager* sharedManager();
    static void purgeInstance();
    
    // initialize
    void initialize();
    
    // initialize NPC names
    void initNpcNames();
    
    // initialize NPC data
    void initNpcData();
    
    // remove all NPCs
	void removeAllNPCs();

	// remove a specific NPC
	void removeNPC(uint8_t npcID);
    
    // show NPC on the specified map
    void showNpcOnMap(uint16_t mapID, cocos2d::CCNode* pParent);
    
    // remove NPCs from map
	void removeNpcsFromMap(uint16_t mapID);

	void removeNpcFromMap(uint8_t npcID);

	// get NPC by boss ID
	NPC* getNpcByBossID(uint16_t bossID);
    
    // process touch
	bool processTouch(cocos2d::CCPoint touchPoint);

	// inline methods
	inline void setIsTalking(bool isTalking)    { m_isTalking = isTalking; }
	inline void setCanTouch(bool bTouch)        { m_canTouch = bTouch; }
	inline bool getIsTalking()                  { return m_isTalking; }
	inline void setIsPVPTalking(bool isPVPTalking) {m_isPVPTalking = isPVPTalking;}
	inline bool getIsPVPTalking()               {return m_isPVPTalking;}


	inline NPC* getNpcByID(int npcID)           { return m_npcMap[npcID]; }
	inline int  getNpcCount()                   { return m_npcMap.size(); }
	inline const char* getNpcName(uint8_t npcID){ return m_npcName[npcID].c_str();}
	inline std::map<uint8_t, NPC*>& getNpcMap() { return m_npcMap; }

	bool isSpecialNpc(int npcID) { return SPECIAL_NPC_ID_RAYE == npcID; }
    
private:
	static NPCManager* pSharedManager;

	bool m_isTalking;
	bool m_canTouch;
	bool m_isPVPTalking;

	std::map<uint8_t, NPC*> m_npcMap;
	std::map<uint8_t, std::string> m_npcName;
};

#endif