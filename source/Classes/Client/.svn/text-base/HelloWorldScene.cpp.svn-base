#include "OnlineNetworkManager.h"

#include "HelloWorldScene.h"
#include "CConnectionData.h"
#include "CXLog.h"
#include "cocos2d.h"
#include "ASprite.h"
#include "AspriteManager.h"
#include "EnginePlayerManager.h"
#include "GameResourceManager.h"
#include "XLogicManager.h"
#include "RoleBase.h"
#include "RoleActorBase.h"
#include "SkeletonAnimRcsManager.h"
#include "HeroRoleManager.h"
#include "CharacterSelectLayer.h"
#include "ParticleManager.h"
#include "MainLandManager.h"
#include "StoryDataCenter.h"
#include "Localization.h"
#include "MessageBoxLayer.h"
#include "DressUpManager.h"
#include "TutorialsManager.h"

//// errror message cached
static  string g_ErrorMsgCached;

HelloWorld::HelloWorld()
	:pFrontLayer(NULL)
,pUIMessageLayer(NULL)
{

}

HelloWorld::~HelloWorld(){

}

CCScene* HelloWorld::scene(){
    CCScene * scene = NULL;
    do{
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	bool bRet = false;
	do {

		CC_BREAK_IF(! CCLayerColor::initWithColor(ccc4(200, 200, 200, 255)));

		bRet = true;

		setTouchEnabled(true);
		AspriteManager::getInstance()->loadAllAsprite();
		SkeletonAnimRcsManager::getInstance()->LoadAllData();
		StoryDataCenter::Get()->LoadDataFromXML();
		MainLandManager::Create();
		MainLandManager::Get()->LoadData();
		DressUpManager::Get()->LoadXML();
		ParticleManager::Create();
		TutorialsManager::Get()->LoadData();
		//by Stanley
		XLogicManager * logicNode = XLogicManager::sharedManager();
		logicNode->retain();
		logicNode->removeFromParent();
		this->addChild(logicNode);
		logicNode->autorelease();

		this->scheduleUpdate();

		CCDirector::sharedDirector()->setGLDefaultValues();

		pUIMessageLayer = UIMessageLayer::create();
		this->addChild(pUIMessageLayer,100,0);

		pFrontLayer = FrontCoverLayer::create();
		this->addChild(pFrontLayer,1,1);
		schedule(schedule_selector(HelloWorld::update), 1);

	} while (0);
    
    this->setTag(TAG_HELLOWORLD);
    
	return bRet;
}

void HelloWorld::enterCreateRoleLayer()
{
	if(pFrontLayer != NULL)
	{
		this->removeChild(pFrontLayer,true);
		pFrontLayer = NULL;
	}
	CharacterSelectLayer* characterLayer = CharacterSelectLayer::create();
	this->addChild(characterLayer,2,2);
}

void HelloWorld::update(float dt)
{
	left = right = down = false; 
	db_errcode_t step = XLogicManager::sharedManager()->getNetErrorCode();
	if(step != dberr_succ)
	{
		switch(step)
		{
		case dberr_role_notfound:
            case 1002:
			CCLog("dberr_role_notfound");
			enterCreateRoleLayer();
			break;
		default:
			CCLog("ERRORCODE: %d", step);
			break;
		}
	}
}

void HelloWorld::draw()
{
	CCLayerColor::draw();
}

void HelloWorld::receiveNetWorkError(db_errcode_t error)
{

}

void HelloWorld::showMessage(const char* msg)
{
	if(pUIMessageLayer)
	{
		pUIMessageLayer->ShowMessage(msg,KMessageDefaultColor);
	}else{
        g_ErrorMsgCached = msg;
    }
}

FrontCoverLayer* HelloWorld::getFrontLayer()
{
	return pFrontLayer;
}

//void HelloWorld::keyBackClicked()
//{
//	std::string content = Localizatioin::getLocalization("S_Message_common_content");
//	TXGUI::MessageBox::Show(content.c_str(),this,menu_selector(HelloWorld::OkBtnClick),menu_selector(HelloWorld::CancelBtnClick));
//}
//
//void HelloWorld::keyMenuClicked()
//{
//	CCLog("keyMenuClicked");
//}
//
//void HelloWorld::OkBtnClick(CCObject* obj)
//{
//	CCDirector::sharedDirector()->end();
//}
//
//void HelloWorld::CancelBtnClick(CCObject* obj)
//{
//	CCLog("HelloWorld::CancelBtnClick");
//}