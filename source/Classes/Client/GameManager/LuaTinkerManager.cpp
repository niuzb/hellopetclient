#include "LuaTinkerManager.h"
#include "CCLuaEngine.h"
#include "GameResourceManager.h"


LuaTinkerManager::LuaTinkerManager()
{
	curLuaState = CCLuaEngine::defaultEngine()->getLuaState();
}

LuaTinkerManager::~LuaTinkerManager()
{
	loadedFiles.clear();
}

bool LuaTinkerManager::checkAnyLoadFile(string filePath)
{
	
	if (loadedFiles.find(filePath) == loadedFiles.end())
	{
		const char *path = GameResourceManager::sharedManager()->storedFullPathFromRelativePath(filePath.c_str());

		unsigned long fileSize = 0;
		unsigned char* buffer = CCFileUtils::sharedFileUtils()->getFileData(path, "rt", &fileSize);
		int ret = luaL_dostringEx(this->curLuaState, (char*)buffer, fileSize);

		if (ret != 0) {
			CCLOG("load %s file error: %s", filePath.c_str(), lua_tostring(this->curLuaState, -1));
			lua_pop(this->curLuaState, 1);
			return false;
		}

		loadedFiles.insert(filePath);
		return true;
	}

	return true;
}
