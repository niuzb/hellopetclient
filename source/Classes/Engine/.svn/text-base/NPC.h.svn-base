//
//  NPC.h
//  iSeer
//
//  Created by wuwei on 3/7/12.
//  Copyright 2012 Taomee.Inc. All rights reserved.
//

#ifndef _NPC_H_
#define _NPC_H_

#include "cocos2d.h"
#include "EnginePlayerManager.h"
//#include "SpriteObject.h"
#include "NameBkg.h"


enum eFuncType
{
	NPC_QUEST = 1,      // 任务 NPC(普通)
	NPC_BOSS,           // BOSS NPC
	NPC_MINE_RECYCLING, // 矿石回收
	NPC_SCORE_EXCHANGE, // 积分兑换
	NPC_PVP,            // PVP
	NPC_MOVIE_QUIZ,     // 电影问答
};

// type of signs over NPC's head
enum eSignType
{
	SIGN_NONE,          // no quest related to this NPC
	SIGN_EXCLAMATION,   // has quest to publish
	SIGN_QUESTION,      // has quest to submit
	SIGN_QUESTION_GRAY, // has quest to submit but not finished yet
	SIGN_VS,            // has quest to challenge this NPC
};

class NPCTalkLayer;

class NPC : public cocos2d::CCNode
{
public:
	// constructor and destructor
	NPC(int npcID);
	NPC(FILE* fp);
	NPC(unsigned char *buffer, int &readSize);
	virtual ~NPC();

	// create animation
	void    createAnim(cocos2d::CCNode* pParent);

	// remove animation
	void    removeAnim();

	// attach NPC name
	void    attachName();

	// attach sign on the head
	void    attachSign();

	// show on the map
	void    showOnMap(cocos2d::CCNode* pParent);

	// remove from map
	void    removeFromMap();

	// whether this NPC needs challenging because of a quest?
	bool    needChallengeForQuest();

	void    addPublishQuest(uint16_t questID);  // add publish quest

	void    questPublished(uint16_t questID);   // some quest has been published, remove it from the publish list
	void    questAccepted(uint16_t questID);    // a new quest has been accepted, add it to the in-progress list
	void    questFinished(uint16_t questID);    // some in-progress quest has finished, move it to the submit list
	void    questSubmitted(uint16_t questID);   // some finished quest has been submitted, remove from the submit list
	void	questCanceled(uint16_t questID);	// some quest is canceled, remove it and add to publish quest

	// process touch
	bool    processTouch(cocos2d::CCPoint touchPoint);
	bool    isTouched(cocos2d::CCPoint touchPoint);

	// user interaction
	void    showTalkContent();      // show contents talking with player

	void    fightWithMe();

	void    updatePlayEffectSchedule(float dt);    

	const char* getName();

	// inline methods
	inline  bool        isBOSS()                { return (m_monsterID != 0); }
	inline  uint8_t     getID()                 { return m_npcID; }
	inline  uint16_t    getMapID()              { return m_mapID; }
	inline  uint8_t     getFuncType()           { return m_funcType; }
	inline  uint16_t    getDefaultDialog()      { return m_defaultDialog; }
	inline  uint16_t    getFightDialog()        { return m_fightDialog; }
	inline  uint8_t     getResourceID()         { return m_resourceID; }
	inline  uint16_t    getMonsterID()          { return m_monsterID; }
	inline  bool        isShowOnMap()           { return m_isShowOnMap; }
	inline  cocos2d::CCSprite* getSprite()      { return m_pSprite; }

	inline const std::set<uint16_t>& getPublishQuests()  { return m_publishQuests; }
	inline const std::set<uint16_t>& getUnderwayQuests() { return m_underwayQuests; }
	inline const std::set<uint16_t>& getSubmitQuests()   { return m_submitQuests; }

private:
	uint8_t     m_npcID;
	uint8_t     m_funcType;
	uint16_t    m_defaultDialog;
	uint16_t    m_fightDialog;
	uint16_t    m_mapID;
	int16_t     m_posX;
	int16_t     m_posY;
	uint8_t     m_resourceID;
	uint16_t    m_monsterID;
	bool    m_isShowOnMap;
	bool    m_canSubmitQuest;       // are there quests that can submit to this NPC?
	bool    m_hasInProgressQuest;   // are there quests that will submit to this NPC but not finished?
	bool    m_canPublishQuest;      // are there quests that can be published by this NPC?

	bool    m_canPlayEffect;

	AnimSprite*             m_pAnim;        // NPC animation
	cocos2d::CCSprite*      m_pSprite;      // NPC sprite
	cocos2d::CCLabelTTF*    m_pNameLabel;   // NPC name label
	cocos2d::CCSprite*      m_pSignSprite;  // NPC sign sprite, e.g. question mark, or exclamation
	NameBkg*                m_pNameBkg;     // NPC name background

	NPCTalkLayer*           m_pTalkLayer;   // NPC talking layer

	std::set<uint16_t>      m_submitQuests;   // to-submit-quest set (reached the finish condition)
	std::set<uint16_t>      m_underwayQuests; // underway-quest set (not reach the finish condition)
	std::set<uint16_t>      m_publishQuests;  // publish-quest set
};

#endif