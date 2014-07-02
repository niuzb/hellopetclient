#include "OnlineNetworkManager.h"

#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "script_support/CCScriptSupport.h"
#include "CCLuaEngine.h"
#include "HelloWorldScene.h"
#include "GameManager.h"
#include "XLogicManager.h"
#include "UserData.h"
#include "GameResourceManager.h"

/// support lua inteface file
#include "LuaTXGUI.h"
#include "LuaNetwork.h"
#include "LuaLevelCreator.h"
#include "LuaGameAPI.h"
#include "LuaClient.h"
#include "LuaEngine.h"
#include "LuaTinkerManager.h"
#include "NetStateChecker.h"

USING_NS_CC;
using namespace CocosDenshion;

extern "C" int luaopen_protobuf_c(lua_State *L);

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
    // end simple audio engine here, or it may crashed on win32
    SimpleAudioEngine::sharedEngine()->end(); 

	CCScriptEngineManager::purgeSharedManager();

	// Optional:  Delete all global objects allocated by libprotobuf.
	google::protobuf::ShutdownProtobufLibrary();
	UserData::Destroy();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // register lua engine and init game lua interface!
    CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
    CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);

	tolua_TXGUI_open(pEngine->getLuaState());
	tolua_Network_open(pEngine->getLuaState());
	tolua_LevelCreator_open(pEngine->getLuaState());
	tolua_GameApi_open(pEngine->getLuaState());
	tolua_LuaClient_open(pEngine->getLuaState());
	tolua_LuaEngine_open(pEngine->getLuaState());
	luaopen_protobuf_c(pEngine->getLuaState());

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	// set resource folder
	std::string exeWin32Path = CCFileUtils::sharedFileUtils()->getWriteablePath();
	exeWin32Path = exeWin32Path + "..\\..\\Resources";
	this->setResourceRootPath(exeWin32Path);
	// test network
	UserData::Create();
	USERINFO mUserData = UserData::GetUserInfo();
	string id = "1001";
	mUserData.id = atoi(id.c_str());
	string session = "G8679U4nnapsjI6e6syR";
	strcpy(mUserData.userSession,session.c_str());
	UserData::SetUserInfo(mUserData);
	XLogicManager::sharedManager()->connectToServer();

#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID 
    string path = GameResourceManager::sharedManager()->storedFullPathFromRelativePath("Script/main.lua");
	string scriptPath = path.substr(0, path.find_last_of("S"));
	pEngine->addSearchPath(scriptPath.c_str());
	
	//unsigned long fileSize = 0;
	//unsigned char* buffer = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &fileSize);
	//pEngine->executeString((char*)buffer, fileSize);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    string path = GameResourceManager::sharedManager()->storedFullPathFromRelativePath("Script/main.lua");
	pEngine->addSearchPath(path.substr(0, path.find_last_of("S")).c_str());

	//unsigned long fileSize = 0;
	//unsigned char* buffer = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &fileSize);
	//pEngine->executeString((char*)buffer, fileSize);
#else
	std::string path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("Script/main.lua");
	//unsigned long fileSize = 0;
	//unsigned char* buffer = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &fileSize);
	//pEngine->executeString((char*)buffer, fileSize);
	pEngine->addSearchPath(path.substr(0, path.find_last_of("S")).c_str());
	//std::string scriptpath = path.substr(0, path.find_last_of("/"));
	//pEngine->addSearchPath(scriptpath.c_str());
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		string pbfiles[]=
		{"cs_basic.bin", "cs_core.bin", "db.bin", "errcode.bin", "cs_battle.bin", "cs_config.bin"};
		unsigned long buffsize;
	
		lua_State* L_state = CCLuaEngine::defaultEngine()->getLuaState();
		//this failed on android. cause lua io library can not read file from apk  
		LuaTinkerManager::Get()->callLuaFunc<bool>("Script/handleMessage.lua", "registerAllfile");
	
		for(int i = 0; i < 6; i++)
		{
			const char* fullFilePath = GameResourceManager::sharedManager()->storedFullPathFromRelativePath((string("Script/Pbc/")+pbfiles[i]).c_str());
			const char * buff = (const char * )CCFileUtils::
				sharedFileUtils()->getFileData((fullFilePath), 
				"r",&buffsize);
			CCAssert(buff!=NULL, "faile to read file");
			lua_getglobal(L_state,"registerfile");
			lua_pushlstring(L_state, (const char *)(buff ), buffsize);
			lua_pcall(L_state,1,0,0);
			//LuaTinkerManager::Get()->callLuaFunc<bool>("Script/handleMessage.lua", "registerfile", buff);
			CC_SAFE_DELETE_ARRAY(buff);
		}
		
#else
		LuaTinkerManager::Get()->callLuaFunc<bool>("Script/handleMessage.lua", "registerAllfile");
#endif

	// create a scene. it's an autorelease object
	CCScene *pScene = HelloWorld::scene();
	pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->pauseAllEffects();
    
    NetStateChecker::getInstance()->QuickSendRqsToServer();
    
	static bool bInit = false;
	if (bInit)
	{
		/// skip the start up the application
		XLogicManager::sharedManager()->DidEnterBackground(); 
	}
	bInit = true;
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->resumeAllEffects();
	static bool bInit = false;
	if (bInit)
	{
		/// skip the start up the application
		XLogicManager::sharedManager()->WillEnterForeground();
	}
	
	bInit = true;
}
