#include "OnlineNetworkManager.h"

#include "CityListLayer.h"
#include "TXGUIHeader.h"
#include "MainMenuLayer.h"
#include "MainLandManager.h"
#include "GameFontManager.h"
#include "LevelManager.h"
#include "UserData.h"
#include "GameManager.h"
#include "GameAudioManager.h"

using namespace TXGUI;

CityListLayer::CityListLayer()	
{
	
}

CityListLayer::~CityListLayer()
{
	UIManager::sharedManager()->RemoveUILayout("CityList");
}

bool CityListLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}

	//读取城市列表
	initCityList();

	UIManager *manager = UIManager::sharedManager();
	cityListLayout = manager->CreateUILayoutFromFile("UIplist/cityListUI.plist", this, "CityList");	

	//添加背景图片
	CCSprite * bgImg = CCSprite::create("game.png");

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSize bgSize = bgImg->getContentSize();

	float scaleX = visibleSize.width / bgSize.width;
	float scaleY = visibleSize.height / bgSize.height;

	bgImg->setScaleX(scaleX);
	bgImg->setScaleY(scaleY);
	
	bgImg->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));

	this->addChild(bgImg, -1);

	//添加主城
	for (size_t i = 0; i < cityInfoList.size(); i++)
	{
		addCityBtn(i+1);
	}


	//添加关闭按钮
	UIButton *btn = cityListLayout->FindChildObjectByName<UIButton>("cityListCloseBtn");
	CCPoint closePoint = btn->getPosition();
	closePoint = ccpAdd(ccp(visibleSize.width / 2, visibleSize.height / 2), closePoint);

	CCPoint pt1;
	ASprite * as1 = AspriteManager::getInstance()->getAsprite(KUI_BIN);

	int normalCloseId = getResourceIDByName("map_ui_FRAME_INSTANCE_CLOSE");
	int selectCloseId = getResourceIDByName("map_ui_FRAME_INSTANCE_CLOSE_CLICKED");

	CCSprite * normalCloseBtn = as1->getSpriteFromFrame_Middle(normalCloseId, 0, pt1);
	CCSprite * selectCloseBtn = as1->getSpriteFromFrame_Middle(selectCloseId, 0, pt1);

	IconButton * closeBtn = new IconButton(normalCloseBtn, NULL, selectCloseBtn, this, 
					menu_selector(CityListLayer::closeCityList));

	closeBtn->setPosition(closePoint);

	this->addChild(closeBtn);

	//初始化玩家头像资源
	CCPoint pt;
    ASprite * as = AspriteManager::getInstance()->getAsprite(KICON_BIN);

	int playerType = UserData::Get()->GetUserType();

	stringstream playerResStream;
	playerResStream << "map_ui_system_icon_FRAME_ICON_ROLEONMAP_" << playerType;
	string playerResName = playerResStream.str();

	int playerResourceId = getResourceIDByName(playerResName.c_str());
    playerImg = as->getSpriteFromFrame_Middle(playerResourceId, 0, pt);
	playerImg->setVisible(false);	

	this->addChild(playerImg);


	playerMoving = false;
	return true;
}

void CityListLayer::openCityList()
{
	GameAudioManager::sharedManager()->playEffect(350001,false);
	this->setVisible(true);	
	MainMenuLayer::PushOneLayer(this);
	this->setScale(0);
	CCArray *arrayOfActions = CCArray::create();

	CCActionInterval *scaleIn = CCScaleTo::create(0.2f, 1.0f); 
	
	arrayOfActions->addObject(scaleIn);

	CCFiniteTimeAction *sequence = CCSequence::create(arrayOfActions);
	this->runAction(sequence);

	curCityId = MainLandManager::Get()->getCurCityId();
	for (size_t i = 0; i < cityInfoList.size(); i++)
	{
		if (cityInfoList[i].cityId == curCityId)
		{
			playerImg->setPosition(cityInfoList[i].playerPos);
			playerImg->setVisible(true);

			CCPoint nowPos = playerImg->getPosition();
			CCPoint desPos = ccpAdd(nowPos, ccp(0, 10));

			CCArray *arrayOfActions = CCArray::create();
			
			CCMoveTo * move1 = CCMoveTo::create(0.3f, desPos);
			CCMoveTo * move2 = CCMoveTo::create(0.3f, nowPos);			

			arrayOfActions->addObject(move1);
			arrayOfActions->addObject(move2);

			CCFiniteTimeAction *sequence = CCSequence::create(arrayOfActions);

			CCRepeatForever * repeat = CCRepeatForever::create(static_cast<CCSequence *>(sequence));
			playerImg->runAction(repeat);	

			break;
		}
	}
}

void CityListLayer::closeCityList(CCObject* sender)
{
	this->setVisible(false);	
	playerImg->setVisible(false);
	MainMenuLayer::RemoveOneLayer(this);

}

void CityListLayer::addCityBtn(int index)
{	
	//获得城市按钮位置
	stringstream nameStream;
	nameStream << "cityBtn" << index;
	string cityBtnName = nameStream.str();

	UIButton *btn = cityListLayout->FindChildObjectByName<UIButton>(cityBtnName);
	CCPoint cityPoint = btn->getPosition();

	//初始化各种位置信息
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	cityInfoList[index - 1].cityPos = ccpAdd(ccp(visibleSize.width / 2, visibleSize.height / 2), cityPoint);
	cityInfoList[index - 1].playerPos = ccpAdd(cityInfoList[index - 1].cityPos, ccp(0, -25));
	cityInfoList[index - 1].namePos = ccpAdd(cityInfoList[index - 1].cityPos, ccp(0, -30));

	//获得城市图标资源
	CCPoint pt;
    ASprite * as = AspriteManager::getInstance()->getAsprite(KICON_BIN);

	stringstream resourceNameStream;
	resourceNameStream << "map_ui_system_icon_FRAME_ICON_CITY" << index;
	string cityResourceName = resourceNameStream.str();

	int cityResourceId = getResourceIDByName(cityResourceName.c_str());
    CCSprite* cityIcon = as->getSpriteFromFrame_Middle(cityResourceId, 0, pt);
	CCSprite* citySelectIcon = as->getSpriteFromFrame_Middle(cityResourceId, 0, pt);
	citySelectIcon->setScale(1.2f);

	//创建城市图标
	IconButton * cityBtn = new IconButton(cityIcon, NULL, citySelectIcon, this, 
					menu_selector(CityListLayer::onPressCityBtn));	
	
	cityBtn->setPosition(cityInfoList[index - 1].cityPos);
	cityBtn->SetButtonIndex(index);
	cityBtn->setAnchorPoint(ccp(0.5, 0.5));
	this->addChild(cityBtn);

	//创建城市名称label
	float fontSize = GameFontManager::smallFontSize();
	CCSize nameLabelSize = CCSizeMake(200 / CC_CONTENT_SCALE_FACTOR(), fontSize);
	
	string cityName = MainLandManager::Get()->getCityName(cityInfoList[index - 1].cityId);
	UILabelTTF * cityNameLabel = UILabelTTF::create(cityName.c_str(), KJLinXin, fontSize,
				nameLabelSize, kCCTextAlignmentCenter,kCCVerticalTextAlignmentBottom);
    
	cityNameLabel->setPosition(cityInfoList[index - 1].namePos);
	this->addChild(cityNameLabel);
}


void CityListLayer::onPressCityBtn(CCObject* sender)
{
	if (playerMoving)
	{
		return;
	}

	CCMenuItem* menuItem = dynamic_cast<CCMenuItem*>(sender);
	if(menuItem)
	{
		CCNode* node = menuItem->getParent();
		CCMenu* menu = dynamic_cast<CCMenu*>(node);
		if(menu)
		{
			CCNode* parent = menu->getParent();
			IconButton* button = dynamic_cast<IconButton*>(parent);
			if(button)
			{
				playerMoving = true;
				int index = button->GetButtonIndex();	

				targetCityId = cityInfoList[index - 1].cityId;
				moveToCity(targetCityId, 0);
							
			}
		}
	}
}

void CityListLayer::moveToCity(int cityId, float delayTime)
{
	int index = 0;
	for (size_t i = 0; i < cityInfoList.size(); i++)
	{
		if (cityInfoList[i].cityId == cityId)
		{
			index = i+1;
			break;
		}
	}
	targetCityId = cityInfoList[index - 1].cityId;
	if (curCityId == targetCityId)
	{
		playerMoving = false;
		closeCityList(this);
		return;
	}

	CCPoint startPos;
	for (size_t i = 0; i < cityInfoList.size(); i++)
	{
		if (cityInfoList[i].cityId == curCityId)
		{
			startPos = cityInfoList[i].playerPos;
		}
	}	
	CCPoint endPos = cityInfoList[index - 1].playerPos;
	float distance = ccpDistance(startPos, endPos);

	CCArray *arrayOfActions = CCArray::create();

	CCDelayTime * delayFunc = CCDelayTime::create(delayTime);
	CCMoveTo * move = CCMoveTo::create(distance / 180.0f, endPos);
	CCCallFunc *fun = CCCallFunc::create(this, callfunc_selector(CityListLayer::enterTargetCity));

	arrayOfActions->addObject(delayFunc);
	arrayOfActions->addObject(move);
	arrayOfActions->addObject(fun);

	CCFiniteTimeAction *sequence = CCSequence::create(arrayOfActions);

	playerImg->stopAllActions();
	playerImg->runAction(sequence);	
}

void CityListLayer::enterTargetCity()
{
	curCityId = MainLandManager::Get()->getCurCityId();
	if (curCityId == targetCityId)
	{
		return;
	}
	
	CCPoint bornCell = MainLandManager::Get()->getCityCell(targetCityId, "born");
	CCPoint bornPoint = LevelManager::sShareInstance()->pointCellToPixel(bornCell);
	OnlineNetworkManager::sShareInstance()->sendPlayerEnterMapMessage(targetCityId,bornPoint.x,bornPoint.y,0);
	MainLandManager::Get()->setCurCityId(targetCityId);
	playerMoving = false;
	closeCityList(this);

	if (GameManager::Get()->GetSceneLayer())
	{
		GameManager::Get()->GetSceneLayer()->showLoading(true);
	}

}

void CityListLayer::initCityList()
{
	vector<int> cityIdList = MainLandManager::Get()->getCityIdList();
	for (size_t i = 0; i < cityIdList.size(); i++)
	{
		CityInfo info;
		info.cityId = cityIdList[i];
		cityInfoList.push_back(info);
	}
}