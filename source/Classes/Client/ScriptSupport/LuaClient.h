
#ifndef __LUACLIENT_H_
#define __LUACLIENT_H_

extern "C" {
#include "tolua++.h"
#include "tolua_fix.h"
}

#include <map>
#include <string>
#include "tolua_fix.h"
#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"

//Note: Add Client .h Files Here
#include "SpriteFactory.h"
#include "SpriteElfDataCenter.h"
#include "LevelManager.h"
#include "UserData.h"
#include "GMessage.h"
#include "NotificationCenter.h"
#include "GameManager.h"
#include "SkillUIManager.h"
#include "ElfExploreManager.h"
#include "MainMenuLayer.h"
#include "GameAudioManager.h"
#include "particle_manager.h"
#include "ItemManager.h"
#include "TimeManager.h"
#include "GemStonesFromLua.h"
#include "PvAIManager.h"
#include "TutorialsManager.h"
using namespace cocos2d;
using namespace TXGUI;
using namespace CocosDenshion;

TOLUA_API int  tolua_LuaClient_open (lua_State* tolua_S);

#endif // __LUACLIENT_H_