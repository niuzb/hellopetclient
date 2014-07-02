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
#include "UserData.h"

// -------------------------------------------------------------------------------------------------

USERINFO::USERINFO()
{
	memset(this, 0x00, sizeof(USERINFO));
}

BATTLEINFO::BATTLEINFO()
{
	memset(this, 0x00, sizeof(BATTLEINFO));

}
// -------------------------------------------------------------------------------------------------

UserData::UserData()
{
	memset(&m_stUserinfo, 0, sizeof(m_stUserinfo));
	string str = cocos2d::CCUserDefault::sharedUserDefault()->getStringForKey("lastIp");
	sprintf(m_stUserinfo.ip,"%s",str.c_str());
	string server = cocos2d::CCUserDefault::sharedUserDefault()->getStringForKey("lastServerName");
	sprintf(m_stUserinfo.lastServerName,"%s",server.c_str());
	m_stUserinfo.port = cocos2d::CCUserDefault::sharedUserDefault()->getIntegerForKey("lastPort");
}



const USERINFO& UserData::GetUserInfo()
{
	return UserData::Get()->m_stUserinfo;
}

USERINFO* UserData::GetUserInfo( unsigned int id )
{
	if(id == m_stUserinfo.id)
		return &m_stUserinfo;

	std::map<unsigned int, USERINFO>::iterator iter = m_userInfoList.find(id);
	if(iter != m_userInfoList.end())
	{
		return &iter->second;
	}
	return NULL;
}

std::list<unsigned int>* UserData::GetOtherUserId()
{
	std::list<unsigned int>* otherUsers = new std::list<unsigned int>();
	for(std::map<unsigned int, USERINFO>::iterator iter = m_userInfoList.begin();
		iter != m_userInfoList.end();iter++)
	{
		if(m_stUserinfo.id != iter->first)
		{
			otherUsers->push_back(iter->first);
		}
	}
	return otherUsers;
}

void UserData::clearOtherUserInfo()
{
	m_userInfoList.clear();
}

void UserData::removeOtherUser(unsigned int id)
{
	std::map<unsigned int, USERINFO>::iterator iter = m_userInfoList.find(id);
	if(iter != m_userInfoList.end())
	{
		m_userInfoList.erase(iter);
	}
}

unsigned int UserData::getUserId()
{
	return UserData::Get()->m_stUserinfo.id;
}


const char * UserData::getUserName()
{
	return UserData::Get()->m_stUserinfo.szName;
}

const char*	UserData::getUserSession()
{
	return UserData::Get()->m_stUserinfo.userSession;
}

void UserData::SetUserInfo(USERINFO info)
{
	cocos2d::CCLog("UserData::SetUserInfo(){ %d, %s }",info.id,info.userSession);
	UserData::Get()->m_stUserinfo = info;
}

void UserData::SetUserInfo( unsigned int id, USERINFO& info )
{
	if(m_stUserinfo.id == id)
		return;

	m_userInfoList[id] = info;
}

unsigned int UserData::getTokenId()
{
	return UserData::Get()->m_stUserinfo.tokenId;
}

unsigned int UserData::GetUserLevel()
{
	return UserData::Get()->m_stUserinfo.level;
}

unsigned int UserData::GetUserExp()
{
	return UserData::Get()->m_stUserinfo.exp;
}

unsigned int UserData::GetUserMapId()
{
	return UserData::Get()->m_stUserinfo.mapId;
}

unsigned int UserData::GetUserXPos()
{
	return UserData::Get()->m_stUserinfo.xPos;
}

unsigned int UserData::GetUserYPos()
{
	return UserData::Get()->m_stUserinfo.yPos;
}

unsigned int UserData::GetUserOrient()
{
	return UserData::Get()->m_stUserinfo.orient;
}

unsigned int UserData::GetUserType()
{
	return UserData::Get()->m_stUserinfo.type;
}

unsigned int UserData::GetSpriteEnergy()
{
	return UserData::Get()->m_stUserinfo.m_spriteEnergy;
}

unsigned int UserData::GetGold()
{
	return UserData::Get()->m_stUserinfo.m_gold;
}

unsigned int UserData::GetDiamond()
{
	return UserData::Get()->m_stUserinfo.m_diamond;
}

unsigned int UserData::GetUserChip()
{
	return UserData::Get()->m_stUserinfo.m_spriteChip;
}

unsigned int UserData::GetLastPort()
{
	return UserData::Get()->m_stUserinfo.port;
}

const char* UserData::GetLastIP()
{
	return UserData::Get()->m_stUserinfo.ip;
}

const char* UserData::GetLastServerName()
{
	return UserData::Get()->m_stUserinfo.lastServerName;
}

unsigned int UserData::getHeroHp()
{
	return UserData::Get()->m_stUserinfo.health_point;
}

unsigned int UserData::getHeroTotalHp()
{
	return UserData::Get()->m_stUserinfo.total_hp;
}


// -------------------------------------------------------------------------------------------------

void EntityInfo::Set( INFOID* pInfo )
{
	if(pInfo)
	{
		std::map<unsigned int, INFOID*>::iterator iter = m_infoList.find(pInfo->id);
		if(iter != m_infoList.end())
		{
			delete iter->second;
			iter->second = NULL;
		}
		m_infoList[pInfo->id] = pInfo;
	}
}

INFOID* EntityInfo::GetInfo( unsigned int id )
{
	std::map<unsigned int, INFOID*>::iterator iter = m_infoList.find(id);
	if(iter != m_infoList.end())
	{
		return iter->second;
	}
	return NULL;
}

void EntityInfo::Clear( void )
{
	for(std::map<unsigned int, INFOID*>::iterator iter = m_infoList.begin(); iter != m_infoList.end(); iter++)
	{
		delete iter->second;
		iter->second = NULL;
	}

	m_infoList.clear();
}
