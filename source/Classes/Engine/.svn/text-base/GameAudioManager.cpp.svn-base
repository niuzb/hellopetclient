//
//  GameAudioManager.cpp
//  iSeer
//
//  Created by razer tong on 12-3-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "GameAudioManager.h"
#include "XPlatformManager.h"
#include "GameResourceManager.h"
#include "GameConfigFromLuaManager.h"
#include "MainLandManager.h"
USING_NS_CC;
using namespace CocosDenshion;

const char *EFFECT_SWITCH_	= "EFFECT_SWITCH_";
const char *BGM_SWITCH_			= "BGM_SWITCH_";
const char *TRAIN_SWITCH_	= "TRAIN_SWITCH_";
const char *FIRST_START_GAME	= "FIRST_START";
const char *NINE_1_USER_ID_ = "NINE_1_USER_ID_";
const char *NINE_1_NICKNAME_	= "NINE_1_NICKNAME_";

/// all the background music which used by our game are put here! That is all.

GameAudioManager* GameAudioManager::pSharedManager = NULL;

GameAudioManager::GameAudioManager()
{
	m_bIndex = 3;
	m_tempName[0] = NULL;
	m_tempName[1] = NULL;
	m_bBuff = (char *)malloc(30 *sizeof(char));
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(1);
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1);
}


/// do some initialization 
void GameAudioManager::InitDevice()
{
	//第一次启动
	if (!CCUserDefault::sharedUserDefault()->getBoolForKey(FIRST_START_GAME)) 
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey(FIRST_START_GAME, true);

		//初始化并赋值
		m_bEffectSwitch = true;
		m_pBgmSwitch = true;
		m_messageSwitch = true;
		CCUserDefault::sharedUserDefault()->setBoolForKey(EFFECT_SWITCH_, m_bEffectSwitch);
		CCUserDefault::sharedUserDefault()->setBoolForKey(BGM_SWITCH_, m_pBgmSwitch);
		CCUserDefault::sharedUserDefault()->setBoolForKey(TRAIN_SWITCH_, m_messageSwitch);
	}
	else
	{
		m_bEffectSwitch = CCUserDefault::sharedUserDefault()->getBoolForKey(EFFECT_SWITCH_);
		m_pBgmSwitch    = CCUserDefault::sharedUserDefault()->getBoolForKey(BGM_SWITCH_);
		m_messageSwitch    = CCUserDefault::sharedUserDefault()->getBoolForKey(TRAIN_SWITCH_);
	}

}

/// clear audio device
void GameAudioManager::ShutDown()
{
	 
}

GameAudioManager::~GameAudioManager()
{
	ShutDown();

	SimpleAudioEngine::sharedEngine() ->end();
	free(m_bBuff);
}


GameAudioManager* GameAudioManager::sharedManager()
{
	if(!pSharedManager)
	{
		pSharedManager = new GameAudioManager();
	}
	return pSharedManager;
}

void GameAudioManager::Destroy()
{
	if (pSharedManager)
	{
		delete pSharedManager;
		pSharedManager = NULL;
	}
}


void GameAudioManager::setIsEffectSwitchOn(bool isOn) 
{
	m_bEffectSwitch = isOn;
	CCUserDefault::sharedUserDefault()->setBoolForKey(EFFECT_SWITCH_, isOn);
}


void GameAudioManager::setMessageSwitch(bool isOn)
{
	m_messageSwitch = isOn;
	CCUserDefault::sharedUserDefault()->setBoolForKey(TRAIN_SWITCH_, m_messageSwitch);	
}

void GameAudioManager::setNine1UserID(unsigned int userid)
{
	m_userID = userid;
	CCUserDefault::sharedUserDefault()->setIntegerForKey(NINE_1_USER_ID_, (int)m_userID);
}

void GameAudioManager::setNine1Nickname(std::string str)
{
	m_nickName = str;
	CCUserDefault::sharedUserDefault()->setStringForKey(NINE_1_NICKNAME_, m_nickName);
}

bool GameAudioManager::getIsEffectSwitchOn()
{
	return CCUserDefault::sharedUserDefault()->getBoolForKey(EFFECT_SWITCH_);
}

bool GameAudioManager::getIsBgmSwitchOn()
{
	return CCUserDefault::sharedUserDefault()->getBoolForKey(BGM_SWITCH_);
}

void GameAudioManager::playBGM()
{
	if (m_bIndex !=3) 
	{
		if (SimpleAudioEngine::sharedEngine() ->isBackgroundMusicPlaying())
		{
			SimpleAudioEngine::sharedEngine() ->stopBackgroundMusic();
		}
		if (m_bIndex == 1 && m_tempName[0]!=NULL) 
		{
			m_bIndex = 2;
			SimpleAudioEngine::sharedEngine() ->playBackgroundMusic(m_tempName[0],false);
		}else if(m_bIndex ==2 && m_tempName[1]!=NULL)
		{
			m_bIndex = 1;
			SimpleAudioEngine::sharedEngine() ->playBackgroundMusic(m_tempName[1],false);
		}else if(m_bIndex == 4 && m_tempName[0]!=NULL)
		{
			m_bIndex = 4;
			SimpleAudioEngine::sharedEngine() ->playBackgroundMusic(m_tempName[0],true);
		}
	}
}

void GameAudioManager::playBGMWithMap(unsigned int musicId)
{	
	if(musicId == 0)
	{
		return;
	}
	std::string audioPath = "Sound/";
	char musicChar[10];
	sprintf(musicChar,"%d",musicId);
	audioPath.append(musicChar);
	audioPath.append(".mp3");

	std::string pFullFilePath = GameResourceManager::sharedManager()->storedFullPathFromRelativePath(audioPath.c_str());
	SimpleAudioEngine::sharedEngine() ->playBackgroundMusic(pFullFilePath.c_str(),true);
}

void GameAudioManager::playLoadingBGM()
{
	std::string audioPath = "Sound/300000.mp3";
	std::string pFullFilePath = GameResourceManager::sharedManager()->storedFullPathFromRelativePath(audioPath.c_str());
	SimpleAudioEngine::sharedEngine() ->playBackgroundMusic(pFullFilePath.c_str(),true);
}

void GameAudioManager::stopPlayBGM()
{
	m_bIndex =3;
	SimpleAudioEngine::sharedEngine() ->stopBackgroundMusic();
}

bool GameAudioManager::isBGMPlaying()
{
	return SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying();
}

void GameAudioManager::playEffectWithID(const int eid, const float delay) 
{
	if (m_bEffectSwitch) 
	{
		sprintf(m_bBuff,"%u.wav",eid);
		if (delay ==0)
		{
			SimpleAudioEngine::sharedEngine() ->playEffect(m_bBuff);
		}else
		{            
			IPlatform* platform = XPlatformManager::GetPlatformDevice();
			if (platform)
			{
				platform->PlayAudioEffect(m_bBuff, delay);
			}
		}
	}
}

void GameAudioManager::playEffectWithID( const char *fileName,const float delay) 
{
	if (m_bEffectSwitch) 
	{
		sprintf(m_bBuff,"%s.wav",fileName);
		if (delay ==0)
		{
			SimpleAudioEngine::sharedEngine() ->playEffect(m_bBuff);
		}else
		{            
			IPlatform* platform = XPlatformManager::GetPlatformDevice();
			if (platform)
			{
				platform->PlayAudioEffect(m_bBuff, delay);
			}
		}
	}
}

void GameAudioManager::playEffect(const KEffectID eid,bool isLoop,const bool isStopBGM) 
{
	if (m_bEffectSwitch) 
	{
		if (isStopBGM)
		{
			m_bIndex = 3;
			SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		}
		const char * audioPath = this->getFileName(eid);
		std::string pFullFilePath = GameResourceManager::sharedManager()->storedFullPathFromRelativePath(audioPath);
		unsigned int uHash = SimpleAudioEngine::sharedEngine()->playEffect(pFullFilePath.c_str(),isLoop);

		std::map<unsigned int, unsigned int>::iterator iter = m_soundIDMap.find((unsigned int)eid);
		if(iter != m_soundIDMap.end())
		{
			iter->second = uHash;
		}
		else
		{
			m_soundIDMap.insert(std::make_pair((unsigned int)eid, uHash));
		}
	}
}

void GameAudioManager::playEffect(unsigned int soundID,bool isLoop,const float delay) 
{
	if (m_bEffectSwitch) 
	{
		sprintf(m_bBuff,"%u.wav",soundID);
		std::string path = "Sound/";


		path.append(m_bBuff);
		std::string pFullFilePath = GameResourceManager::sharedManager()->storedFullPathFromRelativePath(path.c_str());
		
		if (delay ==0)
		{
			unsigned int uHash = SimpleAudioEngine::sharedEngine()->playEffect(pFullFilePath.c_str(),isLoop);
            std::map<unsigned int, unsigned int>::iterator iter = m_soundIDMap.find(soundID);
			if(iter != m_soundIDMap.end())
			{
				iter->second = uHash;
			}
			else
			{
				m_soundIDMap.insert(std::make_pair(soundID, uHash));
			}
            
            //CCLog("GameAudioManager::playEffect: %s, soundID : %u", pFullFilePath.c_str(), soundID);
            

		}/*else
		 {            
			IPlatform* platform = XPlatformManager::GetPlatformDevice();
			if (platform)
			{
				platform->PlayAudioEffect(m_bBuff, delay);
			}
		 }*/
	}
}

void GameAudioManager::stopEffect(unsigned int soundID)
{

	if (m_bEffectSwitch) 
	{
		//sprintf(m_bBuff,"%u.wav",soundID);
		//std::string path = "Sound/";
		//path.append(m_bBuff);
		//std::string pFullFilePath = GameResourceManager::sharedManager()->storedFullPathFromRelativePath(path.c_str());

		//unsigned int hash = CocosDenshion::getHashCodeByString(pFullFilePath.c_str());
		//CCLog("GameAudioManager::stopEffect: %s| hash= %d, soundID : %u", pFullFilePath.c_str(), hash, soundID);

		std::map<unsigned int, unsigned int>::iterator iter = m_soundIDMap.find(soundID);
		if(iter != m_soundIDMap.end())
		{
			//CCLog("GameAudioManager::stopEffect :  hash= %d, soundID : %u", iter->second, soundID);

			SimpleAudioEngine::sharedEngine()->stopEffect(iter->second);

		}
		
	}
}

//判断当前音效是否已经播放完
bool GameAudioManager::isEffectIsPlaying(unsigned int nSoundId)
{
	//sprintf(m_bBuff,"%u.wav",nSoundId);
	//std::string path = "Sound/";
	//path.append(m_bBuff);
	//std::string pFullFilePath = GameResourceManager::sharedManager()->storedFullPathFromRelativePath(path.c_str());
	//unsigned int hash = CocosDenshion::getHashCodeByString(pFullFilePath.c_str());
	std::map<unsigned int, unsigned int>::iterator iter = m_soundIDMap.find(nSoundId);
	if(iter != m_soundIDMap.end())
	{
		return SimpleAudioEngine::sharedEngine()->getEffectIsPlaying(iter->second);
	}
	return false;
	
}

const char *GameAudioManager::getFileName(KEffectID eid) const
{
	if(eid == NORMAL_ATTACK) 
		return "Sound/321000.mp3";
	return "";
}

void GameAudioManager::stopAllEffect()
{
	SimpleAudioEngine::sharedEngine()->stopAllEffects();
}

