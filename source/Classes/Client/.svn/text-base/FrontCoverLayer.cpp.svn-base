#include "OnlineNetworkManager.h"
#include "XLogicManager.h"
#include "FrontCoverLayer.h"
#include "TXGUIHeader.h"
#include "GameAudioManager.h"

#include "GameResourceManager.h"
#include "GameFontManager.h"
#include "AspriteManager.h"
#include "ASprite.h"

#include "UICreator.h"
#include "resources.h"
#include "AssetsManager.h"
#include "HelloWorldScene.h"
#include "Localization.h"
#include "GameConfigFromLuaManager.h"
#include "GMessage.h"
#include "ParticleManager.h"
#include "MessageBoxLayer.h"
#include "SkeletonAnimRcsManager.h"
#include "UserData.h"
#include "LuaTinkerManager.h"
using namespace TXGUI;

#define LOADINGTIME 10

FrontCoverLayer::FrontCoverLayer()
	:pLoginItem(NULL),
	logOutItem(NULL),
    _downloadTTF(NULL),
    _downloadBar(NULL)
{
	m_severScrollPage = NULL;
	m_selectedSever = NULL;
    this->_barFrame = NULL;
    this->m_accumulator = 0;
    this->m_lastTickTime = 0;
	m_layout = NULL;

	/// register ISocketEvent to online network manager
	OnlineNetworkManager::sShareInstance()->RegisterEvent(this);
}

FrontCoverLayer::~FrontCoverLayer()
{
	UIManager::sharedManager()->RemoveUILayout("SplashLayout");
	OnlineNetworkManager::sShareInstance()->UnRegisterEvent(this);

    CC_SAFE_RELEASE(_downloadBar);
    CC_SAFE_RELEASE(_barFrame);

	for(std::vector<SeverInfo*>::iterator it = m_severList.begin();
		it != m_severList.end(); it++)
	{
		SeverInfo* info = *it;
		CC_SAFE_DELETE(info);
	}
	m_severList.clear();

	m_lstButton.clear();
	
}

bool FrontCoverLayer::init()
{	
	bool bRet = false;
	do {

		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		CCSprite* pSprite = CCSprite::create("frontCover.png");
		// position the sprite on the center of the screen
		float scaleX = visibleSize.width/pSprite->getTexture()->getPixelsWide();
		float scaleY = visibleSize.height/pSprite->getTexture()->getPixelsHigh();
		float scale = (scaleX > scaleY) ? scaleX : scaleY;
		pSprite->setScaleX(scale);
		pSprite->setScaleY(scale);
		pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
		this->addChild(pSprite, 0);

		//SkeletonAnimRcsManager::getInstance()->LoadOneRoleRcsOnly(201);
		SkeletonAnimRcsManager::getInstance()->LoadOneRoleRcsOnly(202);
		SkeletonAnimRcsManager::getInstance()->LoadOneRoleRcsOnly(203);

		EffectSprite* effect1 = ParticleManager::Get()->createEffectSprite(202,"");
		if(effect1)
		{
			effect1->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
			effect1->getRoot()->setScale(scale);
			this->addChild(effect1, 1);
			effect1->SetAnim(kType_Play,1,true);
		}
		
		//effect1 = ParticleManager::Get()->createEffectSprite(201,"");
		//if(effect1)
		//{
		//	effect1->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
		//	effect1->getRoot()->setScale(scale);
		//	this->addChild(effect1, 1);
		//	effect1->SetAnim(kType_Play,1,true);
		//}

		effect1 = ParticleManager::Get()->createEffectSprite(203,"");
		if(effect1)
		{
			effect1->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
			effect1->getRoot()->setScale(scale);
			this->addChild(effect1, 1);
			effect1->SetAnim(kType_Play,1,true);
		}

		CCSprite* spriteFrame = CCSprite::create("frontCoverFrame.png");	
		spriteFrame->setScaleX(scale);
		spriteFrame->setScaleY(scale);
		spriteFrame->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
		this->addChild(spriteFrame, 2);

		schedule(schedule_selector(FrontCoverLayer::update), 1);
        //ASprite *as = AspriteManager::getInstance()->getAsprite(KUI_BIN);
        //CCPoint pt;
        //CCSprite* bar = as->getSpriteFromFrame_Middle(map_ui_FRAME_EQUIPMENT_BAR_EXP, 0, pt);
        //CCSprite* barFrame = as->getSpriteFromFrame_Middle(map_ui_FRAME_EQUIPMENT_FRAME_EXP, 0, pt);
        
        CCSprite* barFrame = CCSprite::create("load0001.png");
        barFrame->setPosition(ccp(visibleSize.width/2, visibleSize.height/6));
        addChild(barFrame);
        
        CCSprite* sp = CCSprite::create("load0002.png");
        CCProgressTimer *progressBar = CCProgressTimer::create(sp);
        barFrame->addChild(progressBar,-1);
        progressBar->setPosition(ccp(6, barFrame->getContentSize().height/2-4));
        
        progressBar->setType(kCCProgressTimerTypeBar);
        progressBar->setAnchorPoint(ccp(0,0));
        progressBar->setMidpoint(ccp(0,0));
        progressBar->setBarChangeRate(ccp(1,0));
        progressBar->setPercentage(0.0f);

        _downloadTTF = CCLabelTTF::create("0%", KJLinXin, 15);
        _downloadTTF->setColor(ccORANGE);
        barFrame->addChild(_downloadTTF);
        _downloadTTF->setPosition(ccp(barFrame->getContentSize().width/2,barFrame->getContentSize().height/2));

        _downloadBar = progressBar;
        //_downloadBar->retain();
        
        _barFrame = barFrame;
        _barFrame->retain();
        
        
        GameResourceManager::sharedManager()->updateResource();
        
		GameAudioManager::sharedManager()->playLoadingBGM();
        
		const char* vision = LuaTinkerManager::Get()->callLuaFunc<char *>("Script/main.lua", "getVisionNum");
		m_visionLabel = CCLabelTTF::create(vision,KJLinXin,20);
		if(m_visionLabel)
		{
			float scale = UIManager::sharedManager()->getScaleFactor();
			m_visionLabel->setColor(ccWHITE);
			m_visionLabel->setScale(scale);
			addChild(m_visionLabel);
			m_visionLabel->setPosition(ccp(visibleSize.width -m_visionLabel->getContentSize().width/2,
				visibleSize.height -m_visionLabel->getContentSize().height/2));
		}

		m_layout = UIManager::sharedManager()->CreateUILayoutFromFile("UIplist/splashUI.plist", this, "SplashLayout");
		UIManager::sharedManager()->RegisterMenuHandler("SplashLayout","FrontCoverLayer::menuLoginGameCallback",
			menu_selector(FrontCoverLayer::menuLoginGameCallback), this);
		UIManager::sharedManager()->RegisterMenuHandler("SplashLayout","FrontCoverLayer::onClickedMoreSever",
			menu_selector(FrontCoverLayer::onClickedMoreSever), this);
		UIManager::sharedManager()->RegisterMenuHandler("SplashLayout","FrontCoverLayer::onCLickedSeverCloseBt",
			menu_selector(FrontCoverLayer::onCLickedSeverCloseBt), this);
		UIManager::sharedManager()->RegisterMenuHandler("SplashLayout","FrontCoverLayer::onClickedLatestSever",
			menu_selector(FrontCoverLayer::onClickedLatestSever), this);
		
		if(m_layout)
		{
			m_severScrollPage = m_layout->FindChildObjectByName<UIScrollPage>("severScrollPage");
			setLastServerLabel();
			m_layout->setVisible(false);
		}
		
		/// response to keyboard
		this->setKeypadEnabled(true);
		
		bRet = true;
	}while (0);
	return bRet;
}

void FrontCoverLayer::menuLoginGameCallback(CCObject* pSender)
{
	const char* ip = ONLINE_SERVER_IP;
	unsigned int port = ONLINE_SERVER_PORT;
	if(*ip == '\0' || port == 0)
	{
		showmsg(Localizatioin::getLocalization("M_SELECTSERVER"));
		return;
	}
	 XLogicManager::sharedManager()->logIn();
}

void FrontCoverLayer::menuLogOutCallback(CCObject* pSender)
{
	XLogicManager::sharedManager()->logOut();
}

void FrontCoverLayer::update(float dt)
{
    
    processLoadTime();
    
    if(AssetsManager::_downloadPercent < 100)
    {
        char buf[10];
        sprintf(buf, "%d", AssetsManager::_downloadPercent);
        std::string str = "";
        str += buf;
		str += "%";
        
        if(_downloadTTF)
           _downloadTTF->setString(str.c_str());
        
        if(_downloadBar)
           _downloadBar->setPercentage(AssetsManager::_downloadPercent);
    }
    
    else
    {
        if(_downloadBar)
            _downloadBar->setPercentage(100);
        
        if(_downloadTTF)
            _downloadTTF->setString("100%");
        
        unschedule(schedule_selector(FrontCoverLayer::update));
        schedule(schedule_selector(FrontCoverLayer::readyLogin_func), 0.5f);
    }
}

void FrontCoverLayer::readyLogin_func(float dt)
{    
    int step = XLogicManager::sharedManager()->getLoginStep();
    if( step >= 1 )
    {
        ReadyToLogin();
        unschedule(schedule_selector(FrontCoverLayer::readyLogin_func));
    }
    
    if(_barFrame)
    {
        _barFrame->removeFromParentAndCleanup(true);
		_barFrame->release();
        _barFrame = NULL;
		
        _downloadBar = NULL;
        _downloadTTF = NULL;
    }
}

void FrontCoverLayer::ReadyToLogin()
{
//	if(logOutItem == NULL)
//	{
//		CCLog("HelloWorld::ReadyToLogin()");
//		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
//		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
//		logOutItem = CCMenuItemImage::create(
//			"CloseNormal.png",
//			"CloseSelected.png",
//			this,
//			menu_selector(FrontCoverLayer::menuLogOutCallback));
//
//		logOutItem->setPosition(ccp(origin.x + visibleSize.width - logOutItem->getContentSize().width/2 ,
//			origin.y + logOutItem->getContentSize().height/2));
//		float scale = UIManager::sharedManager()->getScaleFactor();
//		logOutItem->setScale(scale);
//		// create menu, it's an autorelease object
//		CCMenu* logOutMenu = CCMenu::create(logOutItem, NULL);
//		logOutMenu->setPosition(CCPointZero);
//		this->addChild(logOutMenu, 5);
//
//	}

	if(m_layout)
	{
		m_layout->setVisible(true);
	}

	const char* ip = UserData::GetLastIP();
	unsigned int port = UserData::GetLastPort();

	if(*ip == '\0' || port == 0)
	{
		onClickedMoreSever(NULL);
	}

	//if(pLoginItem == NULL)
	//{
	//	CCLog("HelloWorld::onConnectToSuccess()");
	//	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	//	pLoginItem = CCMenuItemImage::create(
	//		"coverTitle.png",
	//		"coverTitle.png",
	//		this,
	//		menu_selector(FrontCoverLayer::menuLoginGameCallback));
	//	float scale = UIManager::sharedManager()->getScaleFactor();
	//	pLoginItem->setScale(scale);
	//	//pLoginItem->setPosition(0,0);
	//	pLoginItem->setPosition(ccp(visibleSize.width/2 + origin.x ,
	//		visibleSize.height/4 + origin.y));
	//	// 修改按键响应区的大小，便于点击
	//	CCSize originSize = pLoginItem->getContentSize();	
	//	pLoginItem->setContentSize(CCSize(originSize.width * 2,originSize.height *2));
	//	CCNode* normalNode = pLoginItem->getNormalImage();
	//	CCNode* selectedNode = pLoginItem->getSelectedImage();
	//	normalNode->setPosition(ccpAdd(normalNode->getPosition(),ccp(originSize.width * 0.5f,originSize.height *0.5f)));
	//	selectedNode->setPosition(ccpAdd(selectedNode->getPosition(),ccp(originSize.width * 0.5f,originSize.height *0.5f)));

	//	CCActionInterval* action1 = CCFadeIn::create(2.0f);
	//	CCActionInterval* action1Back = action1->reverse();
	//	pLoginItem->runAction(CCRepeatForever::create(static_cast<CCSequence *>(CCSequence::create( action1, action1Back,NULL))));

	//	// create menu, it's an autorelease object
	//	CCMenu* pMenu = CCMenu::create(pLoginItem, NULL);
	//	pMenu->setPosition(CCPointZero);
	//	this->addChild(pMenu, 4);
	//}
}

void FrontCoverLayer::showmsg(const char *msg)
{
    CCNode* parent = this->getParent();
    HelloWorld* helloworld = dynamic_cast<HelloWorld*>(parent);
    if(helloworld)
    {
        helloworld->showMessage(msg);
    }
}

void FrontCoverLayer::processLoadTime()
{
    if(AssetsManager::_downloadPercent > 0)
        return;
    
    struct cc_timeval currentTimeX;
	CCTime::gettimeofdayCocos2d(&currentTimeX, NULL);
    
    // get current time
	double currentTime = (currentTimeX.tv_sec) + (currentTimeX.tv_usec / 1000000.0);

	if(!m_lastTickTime )
		m_lastTickTime = currentTime;
    
	//determine the amount of time elapsed since our last update
	double frameTime = currentTime - m_lastTickTime;
	m_accumulator += frameTime;
    
	//update the world with the same seconds per update
	int tickCount = 0;
	while( m_accumulator > LOADINGTIME )
	{
		m_accumulator -= LOADINGTIME;
        std::string msg = Localizatioin::getLocalization("M_UPDATEFULL_NETWORKFAILURE");
        showmsg(msg.c_str());
		NotificationCenter::defaultCenter()->broadcast(GM_DOWNLOAD_MAP_FAIL, this);
        tickCount++;
	}
	m_lastTickTime = currentTime;
	CCLog("accumlator:%f\n", m_accumulator);
}

void FrontCoverLayer::OnConnected(int nResult)
{

}

void FrontCoverLayer::OnDisconnect()
{
	std::string msg = Localizatioin::getLocalization("M_UPDATEFULL_NETWORKFAILURE");
	showmsg(msg.c_str());
    
    /// reset XLogicManager status
    XLogicManager::sharedManager()->networkDisConnected();
}

void FrontCoverLayer::OnSocketError(int nError)
{
	CCLog("socket error!%d", nError);
	if (nError != ES_ERR_CONNECT)
	{
		std::string msg = Localizatioin::getLocalization("M_UPDATEFULL_NETWORKFAILURE");
		showmsg(msg.c_str());
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 响应android键盘
void FrontCoverLayer::keyBackClicked()
{
	std::string content = Localizatioin::getLocalization("S_Message_common_content");
	TXGUI::MessageBox::Show(content.c_str(),
		this,
		menu_selector(FrontCoverLayer::OkBtnClick),
		menu_selector(FrontCoverLayer::CancelBtnClick),
		MB_OKCANCEL);
}

void FrontCoverLayer::keyMenuClicked()
{
	CCLog("keyMenuClicked");
}


void FrontCoverLayer::OkBtnClick(CCObject* obj)
{
	CCDirector::sharedDirector()->end();
}

void FrontCoverLayer::CancelBtnClick(CCObject* obj)
{
	CCLog("FrontCoverLayer::CancelBtnClick");
}

void FrontCoverLayer::onReceiveSeverInfo(CSQueryShardRsp* rsp)
{
	clearSeverList();
	setLastLoginSever();
	UILayout* m_layout = UIManager::sharedManager()->getUILayout("SplashLayout");
	if(m_layout)
	{
		UIContainer* m_splashContainer = m_layout->FindChildObjectByName<UIContainer>("splashContainer");
		if(m_splashContainer)
		{
			m_splashContainer->setVisible(false);
		}
		UIContainer* m_severContainer = m_layout->FindChildObjectByName<UIContainer>("selectServeContainer");
		if(m_severContainer)
		{
			m_severContainer->setVisible(true);

			if(rsp)
			{
				unsigned int count = rsp->shards_size();
				for(unsigned int i = 0; i< count; i++)
				{				
					if(i == 0)
					{
						// 暂时只处理第一个大区

						CSShardBase baseShard = rsp->shards(i);
						unsigned int shardId = baseShard.id();
						unsigned int shardOs = baseShard.os();
						unsigned int shardProvider = baseShard.provider();
						CCLog("shard: [id: %d], [os: %d], [provider: %d]",shardId,shardOs,shardProvider);
						unsigned int severCount = baseShard.svrs_size();
						for(unsigned int j = 0; j< severCount; j++)
						{
							CSServerBase severInfo = baseShard.svrs(j);

							SeverInfo* info = new SeverInfo();

							sprintf(info->name,"%s",severInfo.desc().c_str());
							sprintf(info->severIp,"%s",severInfo.ip().c_str());
							info->port = severInfo.port();
							info->online = severInfo.online();
							info->newSever = severInfo.newsvr();
							CCLog("serve: [name: %s], [ip: %s], [port: %d],[online: %d],[new: %d]",
								info->name,info->severIp,info->port,info->online,info->newSever);
							m_severList.push_back(info);
						}
					}
				}
				addNewSever();
			}
		}
	}
}

void FrontCoverLayer::onClickedOneSever(CCObject* pSender)
{
	CCMenuItem* menuItem = dynamic_cast<CCMenuItem*>(pSender);
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
				int buttonIndex = button->GetButtonIndex();
				// to do
				SeverInfo* info = m_severList[buttonIndex];
				if(info)
				{
					USERINFO data = UserData::GetUserInfo();
					sprintf(data.ip,"%s",info->severIp);
					sprintf(data.lastServerName,"%s",info->name);
					data.port = info->port;
					UserData::SetUserInfo(data);
					//onCLickedSeverCloseBt(pSender);
					XLogicManager::sharedManager()->logIn();
				}
			}
		}
	}
}

void FrontCoverLayer::onClickedMoreSever(CCObject* pSender)
{
	OnlineNetworkManager::sShareInstance()->setServerIP(ONLINE_SERVER_IP);
	OnlineNetworkManager::sShareInstance()->setServerPort(ONLINE_SERVER_PORT);
	OnlineNetworkManager::sShareInstance()->setServerSelect(true);
	OnlineNetworkManager::sShareInstance()->startConnect();	
}

void FrontCoverLayer::onCLickedSeverCloseBt(CCObject* pSender)
{
	UILayout* m_layout = UIManager::sharedManager()->getUILayout("SplashLayout");
	if(m_layout)
	{
		UIContainer* m_splashContainer = m_layout->FindChildObjectByName<UIContainer>("splashContainer");
		if(m_splashContainer)
		{
			m_splashContainer->setVisible(true);
		}
		UIContainer* m_severContainer = m_layout->FindChildObjectByName<UIContainer>("selectServeContainer");
		if(m_severContainer)
		{
			m_severContainer->setVisible(false);
		}
	}
}

void FrontCoverLayer::onClickedLatestSever(CCObject* pSender)
{
	const char* ip = UserData::GetLastIP();
	unsigned int port = UserData::GetLastPort();
	if(*ip == '\0' || port == 0)
	{
		showmsg(Localizatioin::getLocalization("M_SELECTSERVER"));
		return;
	}
	XLogicManager::sharedManager()->logIn();
}

void FrontCoverLayer::clearSeverList()
{
	for(std::vector<SeverInfo*>::iterator it = m_severList.begin();
		it != m_severList.end(); it++)
	{
		SeverInfo* info = *it;
		CC_SAFE_DELETE(info);
	}
	m_severList.clear();

	if(m_severScrollPage)
	{
		m_severScrollPage->removeAllPages();
	}
	m_lstButton.clear();
}

void FrontCoverLayer::addNewSever()
{
	UILayout* m_layout = UIManager::sharedManager()->getUILayout("SplashLayout");
	if(m_severScrollPage)
	{
		CCLayer* layer = CCLayer::create();
		m_severScrollPage->addPage(layer);

		int count = m_severList.size();
		int currentPage = 0;
		int column = 3;
		int row = 2;

		ASprite *as = AspriteManager::getInstance()->getAsprite(KUI_BIN);
		int idx = map_ui_FRAME_SELECTSERVE_BUTTON;
		int selectedId = map_ui_FRAME_SELECTSERVE_BUTTON_CLICKED;
		float scale = UIManager::sharedManager()->getScaleFactor();
		float width = m_severScrollPage->getContentSize().width / scale;
		float height = m_severScrollPage->getContentSize().height / scale;

		CCRect rect = as->getframeRect(idx);

		float deltaWidth = (width - column * rect.size.width )/(column + 1);
		float deltaHeigth = (height - row * rect.size.height )/(row + 1);
		
		for(int i =0; i< count; i++)
		{
			int index = i;
			int page = index / (column * row);
			int rowIndex = (index - page * column * row) / column;
			int columnIndex = (index - page * column * row) % column;
			if(page != currentPage)
			{
				currentPage = page;
				CCLayer* newlayer = CCLayer::create();
				m_severScrollPage->addPage(newlayer);
			}

			CCPoint pt;
			CCSprite *pEmptyItem = as->getSpriteFromFrame_Middle( idx, 0, pt);
			CCSprite *pSelectedItem = as->getSpriteFromFrame_Middle(selectedId ,0,pt); 
			IconButton * pIcon = new IconButton(pEmptyItem, NULL, pSelectedItem, this, 
				menu_selector(FrontCoverLayer::onClickedOneSever));
			pIcon->autorelease();
			pIcon->SetButtonIndex(index);
			pIcon->setContentSize(pEmptyItem->getContentSize());

			float x = -width * 0.5f + deltaWidth * (columnIndex + 1) + (columnIndex + 0.5f) * rect.size.width ;
			float y = height * 0.5f - (rowIndex + 0.5f) * (deltaHeigth + rect.size.height );
			pIcon->setPosition(ccp(x, y));

			UILabelTTF* label = UILabelTTF::create(m_severList[i]->name,KJLinXin,40,pEmptyItem->getContentSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
			pIcon->addChild(label);
			m_lstButton.push_back(pIcon);
			CCLayer* currentLayer = m_severScrollPage->getPageLayer(currentPage);
			currentLayer->addChild(pIcon,index);	
		}
	}
}

void FrontCoverLayer::setLastServerLabel()
{
	if(m_layout)
	{
		UILabel* label = m_layout->FindChildObjectByName<UILabel>("serverLabel");
		if(label)
		{
			const char* name = UserData::GetLastServerName();
			if(*name != '\0')
			{
				label->setString(name);
			}
		}
	}
}

void FrontCoverLayer::setLastLoginSever()
{
	if(m_layout)
	{
		UIButton* button = m_layout->FindChildObjectByName<UIButton>("latestSeverBt");
		if(button)
		{
			const char* ip = UserData::GetLastIP();
			unsigned int port = UserData::GetLastPort();
			const char* name = UserData::GetLastServerName();
			if(*ip == '\0' || port == 0)
			{
				button->setEnabled(false);
			}
			else
			{
				UILabelTTF* label = button->getTextLabel();
				if(label)
				{
					label->setString(name);
				}
			}
		}
	}
}