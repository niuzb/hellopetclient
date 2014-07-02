// TAOMEE GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Taomee Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 2012-2015 Taomee Game Technologies. 
//      All Rights Reserved.
//
// Taomee Game Technologies, Shanghai, China
// http://www.taomee.com
//
#pragma once
#include <stdlib.h>
#include <vector>
#include <map>
#include "cocos2d.h"
#include "cmdDefine.h"

#include "Singleton_t.h"
#include "MonsterInfo.h"
#include "PetInfo.h"
#include "CharacterInfo.h"


using namespace  std;

//////////////////////////////////////////////////////////////////////////

class INFOID
{
public:
	INFOID(void) : id(0){}

	unsigned int  id;
};

class BATTLEINFO
{
public:
	BATTLEINFO();

	unsigned int physical_attack;
	unsigned int magic_attack;
	unsigned int skill_attack;
	unsigned int physical_defence;
	unsigned int magic_defence;
	unsigned int skill_defence;
	unsigned int health_point;
	unsigned int accurate ; // 命中
	unsigned int dodge;		// 闪避
	unsigned int wreck;		// 破击
	unsigned int parry;		// 格挡
	unsigned int critical_strike;	// 暴击
	unsigned int tenacity;			// 任性
	unsigned int slay;				// 必杀
	unsigned int proficiency;
	unsigned int speed;				// 减速
	unsigned int total_hp;
	unsigned int courage; // 勇气
	unsigned int charm; // 魔力
	unsigned int trick; // 技巧
	unsigned int effectiveness; // 战斗力
};

/// user base information
class USERINFO : public INFOID, public BATTLEINFO
{
public:

	USERINFO();

	char			userSession[SESSION_LENGTH];
	char szName[16];	
	char ip[30];
	char lastServerName[30];
	unsigned int port;
	long createdTime;

	unsigned int tokenId;
	unsigned int level;
	unsigned int exp;
	unsigned int nextExp;
	unsigned int mapId;
	unsigned int xPos;
	unsigned int yPos;
	unsigned int orient;
	unsigned int type;
	// add more data parameters
	unsigned int battleId;
	
	unsigned int battleSide;

	unsigned int m_spriteEnergy;	//灵能
	unsigned int m_gold;			//金币
	unsigned int m_diamond;			//钻石
	unsigned int m_spriteChip;		//灵石精华
	unsigned int m_reputation;		//声望
	unsigned int m_stamina;			//体力
	unsigned int m_alchemyBagUnlockPos;		//灵石背包已解锁格子
	unsigned int m_alchemyStorageUnlockPos;	//灵石仓库已解锁格子
	unsigned int m_searchSpriteNpc;	//寻灵NPC
	unsigned int m_equipLvUpTotalTimes;		//装备升级总次数
	unsigned int m_equipLvUsedTimes;		//装备升级已使用次数
	unsigned int m_gemRecastTimes;			//宝石重铸次数
	unsigned int m_player_exploit;			//玩家功勋
	unsigned int m_playerExploerExperience; //玩家阅历
	unsigned int m_playerGemAnima;			//宝石精华
};



class UserData : public TSingleton<UserData>
{
public :
	UserData();

	static const USERINFO & GetUserInfo();
	
	/// get user name
	static const char *  getUserName();

	/// get user id
	static unsigned int getUserId();

	static const char*	getUserSession();

	static unsigned int getTokenId();

	static unsigned int GetUserLevel();

	static unsigned int GetUserExp();

	static unsigned int GetUserMapId();

	static unsigned int GetUserXPos();

	static unsigned int GetUserYPos();

	static unsigned int GetUserOrient();

	static unsigned int GetUserType();

	static unsigned int GetSpriteEnergy();

	static unsigned int GetGold();
	
	static unsigned int GetDiamond();

	static unsigned int GetUserChip();

	static unsigned int GetLastPort();

	static const char* GetLastIP();

	static const char* GetLastServerName();

	static unsigned int getHeroHp();

	static unsigned int getHeroTotalHp();

	static void SetUserInfo(USERINFO info);

	void SetUserInfo(unsigned int id, USERINFO& info);
	USERINFO* GetUserInfo(unsigned int id);

	std::list<unsigned int>* GetOtherUserId();
	void clearOtherUserInfo();
	void removeOtherUser(unsigned int id);
protected:
	USERINFO m_stUserinfo;
	
	std::map<unsigned int, USERINFO> m_userInfoList;
};


// --------------------------------------------------------------------------------------------

class EntityInfo : public TSingleton<EntityInfo>
{
public:
	
	void Set(INFOID* pInfo);
	INFOID* GetInfo(unsigned int id);

	void Clear(void);

protected:
	std::map<unsigned int, INFOID*> m_infoList;
};