#include "OnlineNetworkManager.h"
#include "GameFontManager.h"

#include "MainMenuLayer.h"
#include "GameDataManager.h"
#include "Localization.h"
#include "BattleCoverLayer.h"
#include "SpriteSeer.h"
#include "GameManager.h"

using namespace TXGUI;

BattleCoverLayer::BattleCoverLayer()	
{
	
}

BattleCoverLayer::~BattleCoverLayer()
{
	UIManager::sharedManager()->RemoveUILayout("BattleCover");
}

bool BattleCoverLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}

	setTouchEnabled(true);
	UIManager *manager = UIManager::sharedManager();

	manager->CreateUILayoutFromFile("UIplist/battleCover.plist", this, "BattleCover");

	//初始化标签
	int fontSize = 28;
	float factor = manager->getScaleFactor();
	CCSize nameLabelSize = CCSizeMake(500 / CC_CONTENT_SCALE_FACTOR(), fontSize * factor * 2.0f);
	infoLabel = UILabelTTF::create("", KJLinXin, fontSize * factor, 
		nameLabelSize, kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);	

	//初始化文本
	waitText = Localizatioin::getLocalization("M_WAITOTHERPLAYER");
	autoAttackText = Localizatioin::getLocalization("M_AUTOMATIC_AUXILIARYCOMBAT");
	autoSearchText = Localizatioin::getLocalization("M_AUTOMATIC_ROUTING");	

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	infoLabel->setPosition(ccp(visibleSize.width * 0.5f, visibleSize.height * 0.8f));
	infoLabel->setVisible(false);
	infoLabel->setColor(KMessageDefaultColor);

	this->addChild(infoLabel);
	this->setVisible(false);

	return true;
}

void BattleCoverLayer::openBattleCoverLayer(COVER_TYPE coverType)
{
	this->setVisible(true);	
	
	this->layerType = coverType;
	switch (coverType)
	{
	case COVER_AUTOATTACK:
		infoLabel->setString(autoAttackText.c_str());
		break;

	case COVER_WAITINGOTHER:
		infoLabel->setString(waitText.c_str());
		break;

	case COVER_AUTOSEARCH:
		infoLabel->setString(autoSearchText.c_str());
		break;

	case COVER_NONE:
		infoLabel->setString("");
		break;

	default:
		infoLabel->setString("");
		break;
	}
	infoLabel->setVisible(true);
}

void BattleCoverLayer::closeBattleCoverLayer(CCObject* sender)
{
	this->setVisible(false);
	infoLabel->setVisible(false);
	layerType = COVER_NONE;
}

void BattleCoverLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCScrollTouchPriority, true);
}

bool BattleCoverLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	bool ret = false;
	SpriteSeer * hero = GameManager::Get()->getHero();
	if (this->isVisible())
	{
		switch (layerType)
		{
		case COVER_AUTOATTACK:
			GameDataManager::Get()->setHeroAutoAttack(false);
			closeBattleCoverLayer(this);
			ret = true;
			break;

		case COVER_WAITINGOTHER:
			ret = true;
			break;

		case COVER_AUTOSEARCH:			
			if (hero)
			{
				hero->moveToTarget(hero->getPosition(), hero->getPosition());
			}
			closeBattleCoverLayer(this);
			ret = true;
			break;

		case COVER_NONE:
			break;

		default:
			break;
		}		
	}
	return ret;
}

