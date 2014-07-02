#include "LevelBuilderCreator.h"
#include "LevelBuilderNormalScene.h"
#include "LevelBuilderRoom.h"
#include "BaseLevelBuilder.h"

#include "LevelDefine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <direct.h>
#include <io.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "SystemInfoJni.h"
#include <sys/stat.h>
#include <sys/types.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

//////////////////////////////////////////////////////////////////////////
//Now hack the builder type by level id, later will update by config file
//////////////////////////////////////////////////////////////////////////

BaseLevelBuilder*	LevelBuilderCreator::sCreateLevelBuilder(int levelId, LevelLayer* levelLayer)
{
	BaseLevelBuilder* levelBuilder = NULL;

	char buffer[64];	
	sprintf(buffer, "luaScript/Level/%d.lua", levelId);

	//script builder
	if(access(buffer, 0) == 0)
	//if(CCFileUtils::isFileExist(buffer))
	{
		levelBuilder = new BaseLevelBuilder(levelLayer);
	}
	else
	{
		//custom builder
		if (levelId == 10000)
		{
			levelBuilder = new LevelBuilderRoom(levelLayer);
		}
		else
		{
			levelBuilder = new LevelBuilderNormalScene(levelLayer);
		}	
	}

	return levelBuilder;
}