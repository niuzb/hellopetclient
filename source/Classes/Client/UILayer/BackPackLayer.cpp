#include "OnlineNetworkManager.h"
#include "TXGUIHeader.h"
#include "BackPackLayer.h"
#include "AspriteManager.h"
#include "ASprite.h"
#include "ItemManager.h"
#include "SpriteSeer.h"
#include "DragReceiver.h"
#include "GameFontManager.h"
#include "UserData.h"
#include "MainMenuLayer.h"
#include "EquipMixLayer.h"
#include "HeroRoleManager.h"
#include "SpriteElfConfigFromLua.h"
#include "TipMgr.h"
#include "GMessage.h"
#include "GameAudioManager.h"
#include "ShopUILayer.h"
using namespace TXGUI;

BackPackLayer::BackPackLayer()
{
    this->m_pShopUILayer = NULL;
}

BackPackLayer::~BackPackLayer()
{
	UIManager::sharedManager()->RemoveUILayout("BackPack");
	if(m_backPackReceiver)
	{
		DragReceiverRegister::sharedManager()->unregisterDragReceiver(m_backPackReceiver);
		delete m_backPackReceiver;
		m_backPackReceiver = NULL;
	}
	if(m_storageReceiver)
	{
		DragReceiverRegister::sharedManager()->unregisterDragReceiver(m_storageReceiver);
		delete m_storageReceiver;
		m_storageReceiver = NULL;
	}

	if(m_equipmentReceiver)
	{
		DragReceiverRegister::sharedManager()->unregisterDragReceiver(m_equipmentReceiver);
		delete m_equipmentReceiver;
		m_equipmentReceiver = NULL;
	}

	NotificationCenter::defaultCenter()->unregisterAllMsgObserver(this);
}

bool BackPackLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
    
    m_pShopUILayer = ShopUILayer::create();
    addChild(m_pShopUILayer,100);
    m_pShopUILayer->setVisible(false);
    
	m_curUiAs = AspriteManager::getInstance()->getAsprite("UI/ui.bin");
	UIManager *manager = UIManager::sharedManager();

	backPackLayout = manager->CreateUILayoutFromFile("UIplist/backPackUI.plist", this, "BackPack");

	//manager->CreateUILayoutFromFile("UIplist/equipmentMix.plist", "equipmentMixLayout");

	m_backPackContainer = backPackLayout->FindChildObjectByName<UIContainer>("backPackContainer");
	m_storageContainer = backPackLayout->FindChildObjectByName<UIContainer>("storageContainer");
    m_equipmentContainer = backPackLayout->FindChildObjectByName<UIContainer>("equipmentContainer");
    
	manager->RegisterMenuHandler("BackPack","BackPackLayer::closeBackPack",
		menu_selector(BackPackLayer::closeBackPack), this);

	manager->RegisterMenuHandler("BackPack","BackPackLayer::onItemClicked",
		menu_selector(BackPackLayer::onItemClicked), this);

	manager->RegisterMenuHandler("BackPack","BackPackLayer::openStoreHouse",
		menu_selector(BackPackLayer::openStoreHouse), this);

	manager->RegisterMenuHandler("BackPack","BackPackLayer::closeStorage",
		menu_selector(BackPackLayer::closeStorage), this);

	manager->RegisterMenuHandler("BackPack","BackPackLayer::reOrderBackPackItems",
		menu_selector(BackPackLayer::reOrderBackPackItems), this);
	
	manager->RegisterMenuHandler("BackPack","BackPackLayer::reOrderStorageItems",
		menu_selector(BackPackLayer::reOrderStorageItems), this);

	manager->RegisterMenuHandler("BackPack","BackPackLayer::onItemDoubleClicked",
		menu_selector(BackPackLayer::onItemDoubleClicked), this);
	
    manager->RegisterMenuHandler("BackPack","BackPackLayer::closeEquipment",
                                 menu_selector(BackPackLayer::closeEquipment), this);
	manager->RegisterMenuHandler("BackPack","BackPackLayer::onEquipmentItemDoubleClicked",
		menu_selector(BackPackLayer::onEquipmentItemDoubleClicked), this);

	manager->RegisterMenuHandler("BackPack","BackPackLayer::TrainButtonClicked",
		menu_selector(BackPackLayer::TrainButtonClicked), this);	
	
	manager->RegisterMenuHandler("BackPack","BackPackLayer::openAttributeBoard",
		menu_selector(BackPackLayer::openAttributeBoard), this);	

	manager->RegisterMenuHandler("BackPack","BackPackLayer::closeAttributeBoard",
		menu_selector(BackPackLayer::closeAttributeBoard), this);

	manager->RegisterMenuHandler("BackPack","BackPackLayer::onEquipmentTapped",
		menu_selector(BackPackLayer::onEquipmentTapped), this);
	
	manager->RegisterMenuHandler("BackPack","BackPackLayer::onTapCancel",
		menu_selector(BackPackLayer::onTapCancel), this);

	manager->RegisterMenuHandler("BackPack","BackPackLayer::onItemTapped",
		menu_selector(BackPackLayer::onItemTapped), this);
    
    manager->RegisterMenuHandler("BackPack","BackPackLayer::openShop",
                                 menu_selector(BackPackLayer::openShop), this);


	m_backPackScrollPage = backPackLayout->FindChildObjectByName<UIScrollPage>("backPackScrollPage");
	UIScrollLayer* scrollLayer = m_backPackScrollPage->getScrollLayer();

	m_storageScrollPage = backPackLayout->FindChildObjectByName<UIScrollPage>("storageScrollPage");
	//UIScrollLayer* scrollLayer = m_storageScrollPage->getScrollLayer();

	//scrollLayer->setShowPagesIndicator(false);
	b_isBackPackOpened = false;
	b_isStorageOpened = false;
    b_isEquipmentOpened = false;
	b_isAttributeOpened = false;
	m_lockPicName = "map_ui_FRAME_STORAGE_GRID1_LOCKED";

	setTouchEnabled(true); 
	if(m_backPackContainer && m_backPackContainer->getCurrentNode())
	{
		m_backPackContainer->getCurrentNode()->setVisible(false);
	}
	if(m_storageContainer && m_storageContainer->getCurrentNode())
	{
		m_storageContainer->getCurrentNode()->setVisible(false);
	}
    if(m_equipmentContainer && m_equipmentContainer->getCurrentNode())
    {
        m_equipmentContainer->getCurrentNode()->setVisible(false);
    }

	m_playerExpLable = (CCSprite*)backPackLayout->FindChildObjectByName<UIPicture>("equipmentExpBarPic")->getCurrentNode();
	m_playerExpLable->setAnchorPoint(ccp(0,0.5f));
	CCPoint oldPos = m_playerExpLable->getPosition();
	float scale = UIManager::sharedManager()->getScaleFactor();
	m_playerExpLable->setPosition(ccp(oldPos.x-scale * m_playerExpLable->getContentSize().width/2,oldPos.y));

	UILabelTTF* m_userName = (UILabelTTF*)backPackLayout->FindChildObjectByName<UILabel>("playerNameLabel")->getCurrentNode();
	m_userName->setString(UserData::getUserName());

	initBgTouchArea();
	initButtonPriority();
	m_showModle = NULL;
	NotificationCenter::defaultCenter()->registerAllMsgObserver(this);
	return true;
}

void BackPackLayer::initBgTouchArea()
{
	UIPicture* bgPic = backPackLayout->FindChildObjectByName<UIPicture>("backPackPic");
	if(bgPic)
	{
		m_packbgPoint = bgPic->getSpritePos();
		m_packbgSize = bgPic->getSpriteSize();
	}
	else
	{
		m_packbgPoint = CCPointZero;
		m_packbgSize = CCSizeZero;
	}

	UIPicture* storagePic = backPackLayout->FindChildObjectByName<UIPicture>("storagePic");
	if(storagePic)
	{
		m_storagebgPoint = storagePic->getSpritePos();
		m_storagebgSize = storagePic->getSpriteSize();
	}
	else
	{
		m_storagebgPoint = CCPointZero;
		m_storagebgSize = CCSizeZero;
	}

	UIPicture* equipmentPic = backPackLayout->FindChildObjectByName<UIPicture>("equipmentBgPic");
	if(equipmentPic)
	{
		m_equipmentbgPoint = equipmentPic->getSpritePos();
		m_equipmentbgSize = equipmentPic->getSpriteSize();
	}
	else
	{
		m_equipmentbgPoint = CCPointZero;
		m_equipmentbgSize = CCSizeZero;
	}

	m_backPackReceiver = new DragReceiver(kCCScrollTouchBgPriority,EUIBg,0);
	m_backPackReceiver->setCheckDragFunc(checkDrag_selector(BackPackLayer::checkInBackPackBg),this);
	DragReceiverRegister::sharedManager()->registerDragReceiver(m_backPackReceiver);

	m_storageReceiver = new DragReceiver(kCCScrollTouchBgPriority,EUIBg,1);
	m_storageReceiver->setCheckDragFunc(checkDrag_selector(BackPackLayer::checkInStoragekBg),this);
	DragReceiverRegister::sharedManager()->registerDragReceiver(m_storageReceiver);

	m_equipmentReceiver = new DragReceiver(kCCScrollTouchBgPriority,EUIBg,2);
	m_equipmentReceiver->setCheckDragFunc(checkDrag_selector(BackPackLayer::checkInEquipmentBg),this);
	DragReceiverRegister::sharedManager()->registerDragReceiver(m_equipmentReceiver);
	
}

void BackPackLayer::initButtonPriority()
{
	// 调整按钮响应优先级，使其高于背景面板和滑动面板
	UIButton* button = backPackLayout->FindChildObjectByName<UIButton>("SortItemsBt");
	if(button)
	{
		button->setMenuInitPriority(kCCScrollMenuPriority);
	}

	button = backPackLayout->FindChildObjectByName<UIButton>("StoreHouseBt");
	if(button)
	{
		button->setMenuInitPriority(kCCScrollMenuPriority);
	}

	button = backPackLayout->FindChildObjectByName<UIButton>("ShopBt");
	if(button)
	{
		button->setMenuInitPriority(kCCScrollMenuPriority);
	}

	button = backPackLayout->FindChildObjectByName<UIButton>("closeBt");
	if(button)
	{
		button->setMenuInitPriority(kCCScrollMenuPriority);
	}

	button = backPackLayout->FindChildObjectByName<UIButton>("storageCloseBt");
	if(button)
	{
		button->setMenuInitPriority(kCCScrollMenuPriority);
	}

	button = backPackLayout->FindChildObjectByName<UIButton>("StorageSortItemsBt");
	if(button)
	{
		button->setMenuInitPriority(kCCScrollMenuPriority);
	}

	button = backPackLayout->FindChildObjectByName<UIButton>("equipmentCloseBt");
	if(button)
	{
		button->setMenuInitPriority(kCCScrollMenuPriority);
	}

	button = backPackLayout->FindChildObjectByName<UIButton>("playerAttributeBt");
	if(button)
	{
		button->setMenuInitPriority(kCCScrollMenuPriority);
	}

	m_equipmentHelmetButton = backPackLayout->FindChildObjectByName<UIButton>("helmetGrid");
	m_equipmentNecklaceButton = backPackLayout->FindChildObjectByName<UIButton>("necklaceGrid");
	m_equipmentWeaponButton = backPackLayout->FindChildObjectByName<UIButton>("weaponGrid");
	m_equipmentArmorButton = backPackLayout->FindChildObjectByName<UIButton>("armorGrid");
	m_equipmentRingButton = backPackLayout->FindChildObjectByName<UIButton>("ringGrid");
	m_equipmentShoeButton = backPackLayout->FindChildObjectByName<UIButton>("shoeGrid");
}

void BackPackLayer::checkPlayerModle()
{
	if(NULL == m_showModle)
	{
		if(m_equipmentContainer && m_equipmentContainer->getCurrentNode())
		{
			CCSprite* backPic = (CCSprite*)backPackLayout->FindChildObjectByName<UIPicture>("equipmentBgPic")->getCurrentNode();
			if(backPic)
			{
				m_showModle = HeroRoleManager::Get()->createRole(10000, "", UserData::GetUserType(), false);

				m_showModle->SetAnim(kTypeIdle_FaceDown_Stand_MAIN,0,true);
				CCPoint pt = backPic->getPosition();
				float scale = UIManager::sharedManager()->getScaleFactor();
				m_showModle->getRoot()->setScale(1.5f * scale);
				CCPoint modePt = ccp(pt.x ,pt.y - 20 * scale);
				//CCPoint modePt = ccp(pt.x,pt.y);
				m_showModle->setPosition(modePt);
				m_equipmentContainer->getCurrentNode()->addChild(m_showModle,m_equipmentContainer->getCurrentNode()->getZOrder()+1);
			}
		}
	}
}

void BackPackLayer::showPlayerLevel()
{
	if(m_equipmentContainer && m_equipmentContainer->getCurrentNode())
	{
		UILabel* label = backPackLayout->FindChildObjectByName<UILabel>("playerLevelLabel");
		if(label)
		{
			char levelStr[10];
			sprintf(levelStr,"lv. %d",UserData::GetUserLevel());
			label->setString(levelStr);
		}
	}
}

void BackPackLayer::showPlayerExp()
{
	USERINFO userInfo = UserData::GetUserInfo();
	float percent = 1.0f;
	if(userInfo.nextExp != 0)
	{
		percent = (1.0f * userInfo.exp) / userInfo.nextExp;
	}
	if(m_playerExpLable)
	{
		float scale = UIManager::sharedManager()->getScaleFactor();
		m_playerExpLable->setScaleX(percent * scale);
		m_playerExpLable->setScaleY(scale);
	}
	if(backPackLayout)
	{
		UILabel* label = backPackLayout->FindChildObjectByName<UILabel>("equipExpLabel");
		if(label)
		{
			char exp[20];
			sprintf(exp,"exp %.2f%%",percent*100);
			label->setString(exp);
		}
	}
}

void BackPackLayer::showPlayerAttri()
{
	USERINFO info = UserData::GetUserInfo();
	if(backPackLayout)
	{
		UILabel* label = backPackLayout->FindChildObjectByName<UILabel>("LifeNumberLable");
		if(label)
		{
			char text[20];
			sprintf(text,"%d",info.total_hp);
			label->setString(text);
		}

		label = backPackLayout->FindChildObjectByName<UILabel>("PowerNumberLable");
		if(label)
		{
			char text[20];
			sprintf(text,"%d",info.courage);
			label->setString(text);
		}

		label = backPackLayout->FindChildObjectByName<UILabel>("SkillNumberLable");
		if(label)
		{
			char text[20];
			sprintf(text,"%d",info.trick);
			label->setString(text);
		}

		label = backPackLayout->FindChildObjectByName<UILabel>("IntellectNumberLable");
		if(label)
		{
			char text[20];
			sprintf(text,"%d",info.charm);
			label->setString(text);
		}
	}
}

void BackPackLayer::openBackPack()
{
	if(!isVisible())
	{
		setVisible(true);
	}
	if(!b_isBackPackOpened)
	{
		if(m_backPackContainer && m_backPackContainer->getCurrentNode())
		{
			GameAudioManager::sharedManager()->playEffect(350001,false);
			m_backPackContainer->getCurrentNode()->setVisible(true);
			b_isBackPackOpened = true;
			unsigned int maxPos = ItemManager::Get()->getBackPackMaxPos();
			for(unsigned int i=1;i<= maxPos;i++)
			{
				BackPackItem* item = ItemManager::Get()->findItemByPos(i);
				if(item)
				{
					setOneBackPackIcon(item,i);
				}
			}
		}
	}
    if(!b_isEquipmentOpened)
    {
		checkPlayerModle();
		showPlayerLevel();
		showPlayerExp();
		showPlayerAttri();
        if(m_equipmentContainer && m_equipmentContainer->getCurrentNode())
        {
            m_equipmentContainer->getCurrentNode()->setVisible(true);
        }
		b_isEquipmentOpened = true;
		GameAudioManager::sharedManager()->playEffect(350001,false);
		for(unsigned int i=1;i<= 6;i++)
		{
			BackPackItem* item = ItemManager::Get()->findItemByPos(kItemHeroEquip + i);
			if(item)
			{
				setEquipmentIcon(item,i);
			}
		}
    }

	if(b_isStorageOpened)
	{
		if(m_storageContainer && m_storageContainer->getCurrentNode())
		{
			m_storageContainer->getCurrentNode()->setVisible(false);
		}
		b_isStorageOpened = false;
	}
	if(b_isAttributeOpened)
	{
		UIContainer* attributeContainer = backPackLayout->FindChildObjectByName<UIContainer>("attributeContainer");
		if(attributeContainer && attributeContainer->getCurrentNode())
		{
			attributeContainer->getCurrentNode()->setVisible(false);
		}
		b_isAttributeOpened = false;
	}
	MainMenuLayer::PushOneLayer(this);
}

void BackPackLayer::openAttributeBoard(CCObject* sender)
{
	if(b_isBackPackOpened)
	{
		b_isBackPackOpened = false;
		if(m_backPackContainer && m_backPackContainer->getCurrentNode())
		{
			m_backPackContainer->getCurrentNode()->setVisible(false);
		}
	}
	UIContainer* attributeContainer = backPackLayout->FindChildObjectByName<UIContainer>("attributeContainer");
	b_isAttributeOpened = true;
	GameAudioManager::sharedManager()->playEffect(350001,false);
	if(attributeContainer && attributeContainer->getCurrentNode())
	{
		attributeContainer->getCurrentNode()->setVisible(true);
	}
	SpriteElfConfigFromLuaManager::getInstance()->CloseElfPotientionPanel();
}

void BackPackLayer::closeAttributeBoard(CCObject* sender)
{
	UIContainer* attributeContainer = backPackLayout->FindChildObjectByName<UIContainer>("attributeContainer");
	b_isAttributeOpened = false;
	if(attributeContainer && attributeContainer->getCurrentNode())
	{
		attributeContainer->getCurrentNode()->setVisible(false);
	}
}

void BackPackLayer::resetBackPackItemIcon(unsigned int index)
{
	ItemManager* manager = ItemManager::Get();
	BackPackItem* item = manager->findItemByPos(index);
	if(item)
	{
		setOneBackPackIcon(item,index);
	}
}

void BackPackLayer::resetStorageItemIcon(unsigned int index)
{
	ItemManager* manager = ItemManager::Get();
	BackPackItem* item = manager->findItemByPos(index+kItemStorage);
	if(item)
	{
		setOneStorageIconn(item,index);
	}
}

void BackPackLayer::setVisible(bool visible)
{
	CCLayer::setVisible(visible);
	if(!visible)
	{
		b_isBackPackOpened = false;
		b_isStorageOpened = false;
        b_isEquipmentOpened = false;
		b_isAttributeOpened = false;
		if(m_backPackContainer && m_backPackContainer->getCurrentNode())
		{
			m_backPackContainer->getCurrentNode()->setVisible(false);
		}
		if(m_storageContainer && m_storageContainer->getCurrentNode())
		{
			m_storageContainer->getCurrentNode()->setVisible(false);
		}
        if(m_equipmentContainer && m_equipmentContainer->getCurrentNode())
        {
            m_equipmentContainer->getCurrentNode()->setVisible(false);
        }
		UIContainer* attributeContainer = backPackLayout->FindChildObjectByName<UIContainer>("attributeContainer");
		if(attributeContainer && attributeContainer->getCurrentNode())
		{
			attributeContainer->getCurrentNode()->setVisible(false);
		}
		if(m_showModle)
		{
			m_showModle->removeFromParentAndCleanup(true);
			m_showModle = NULL;
		}
	}
}

void BackPackLayer::resetItemIcon(unsigned int index)
{
	//ItemManager* manager = ItemManager::Get();
	//BackPackItem* item = manager->findStorageItemByPos(index);
	//if(item)
	//{
	//	setOneItemIcon(item,index);
	//}
}

void BackPackLayer::setEquipmentIcon(BackPackItem* item,unsigned int index)
{
	if(b_isEquipmentOpened)
	{
		if(item->isEmpty)
		{
			UIButton* button = getEquipmentButton(index);
			if(button)
			{
				button->setIconSprite(NULL);
				button->setFrameSprite(NULL);
			}
		}
		else
		{
			CCSprite* pic = getIconSpriteById(item->getItemId());
			if(pic)
			{
				UIButton* button = getEquipmentButton(index);
				if(button)
				{
					button->setIconSprite(pic);
					ItemBase* itemInfo = item->getItemInfo();
					if(itemInfo && itemInfo > 0)
					{
						CCNode* node = CCNode::create();
						CCSprite* framePic = getIconFrame(itemInfo->m_quality);
						if(framePic)
						{
							node->addChild(framePic);
						}
						CCSprite* upgradePic = getEquipmentUpgradeIcon(item->getItemId());
						if(upgradePic)
						{
							upgradePic->setAnchorPoint(ccp(1,0));
							float x = pic->getContentSize().width * 0.5f;
							float y = pic->getContentSize().height * 0.5f;
							upgradePic->setPosition(ccp(x,-y));
							node->addChild(upgradePic);
						}
						button->setFrameSprite(node);
					}
					//button->setDragMove(true);
				}
			}
		}
	}
}

CCSprite* BackPackLayer::getEquipmentUpgradeIcon(unsigned int itemId)
{
	ExchangeItem* exchangeItem = ItemManager::Get()->getEquipDrawingById(itemId);
	if(exchangeItem && exchangeItem->m_fromItems)
	{
		bool isDrawingExist = false;
		for(std::list<pair<unsigned int ,unsigned int> >::iterator it = exchangeItem->m_fromItems->begin();
			it != exchangeItem->m_fromItems->end(); ++it)
		{
			unsigned int equip = (*it).first;
			ItemBase* info = ItemManager::Get()->getItemInfoById(equip);
			if(info)
			{
				if(info->m_type == 2)
				{
					unsigned int drawingNum = ItemManager::Get()->getItemNumberById(equip);
					if(drawingNum > 0)
					{
						isDrawingExist = true;
					}
					else
					{
						isDrawingExist = false;
					}
					break;
				}
			}
			CC_SAFE_DELETE(info);
		}
		
		if(isDrawingExist)
		{
			ASprite *as = AspriteManager::getInstance()->getAsprite(KICON_BIN); 
			int idx = TXGUI::getResourceIDByName("map_ui_system_icon_FRAME_ICON_UPGRADE");
			CCPoint pt;
			CCSprite * pic = as->getSpriteFromFrame_Middle( idx, 0, pt);
			return pic;
		}
	}
	return NULL;
}

void BackPackLayer::setOneStorageIconn(BackPackItem* item,unsigned int index)
{
	CCAssert(index != 0, "Storage Pos Error");
	if(b_isStorageOpened)
	{
		unsigned int page = (index-1) / EACH_PAGE_NUMBER;
		unsigned int row = ((index-1) % EACH_PAGE_NUMBER) / EACH_ROW_NUMBER;
		unsigned int colmun = ((index-1) % EACH_PAGE_NUMBER) % EACH_ROW_NUMBER;
		if(item->isLocked)
		{
			ASprite *as = AspriteManager::getInstance()->getAsprite(KUI_BIN); 
			int idx = getResourceIDByName(m_lockPicName.c_str());
			CCPoint pt;
			CCSprite * lockPic = as->getSpriteFromFrame_Middle( idx, 0, pt);
			if(m_storageScrollPage)
			{
				m_storageScrollPage->SetPageItemIconWithSprite(page,colmun,row,lockPic);
			}
		}
		else if(item->isEmpty)
		{
			if(m_storageScrollPage)
			{
				m_storageScrollPage->SetPageItemIconWithSprite(page,colmun,row,NULL);
				IconButton* button = m_storageScrollPage->GetIconButton(page,colmun,row);
				if(button)
				{
					button->removeItemLabel();
                    button->setFrameSprite(NULL);
				}
			}
		}
		else
		{
			CCSprite* pic = getIconSpriteById(item->getItemId());
			if(pic)
			{
				if(m_storageScrollPage)
				{
					m_storageScrollPage->SetPageItemIconWithSprite(page,colmun,row,pic);
					IconButton* button = m_storageScrollPage->GetIconButton(page,colmun,row);
					if(button)
					{
						if(item->amount > 1)
						{

							char amountString[10];
							sprintf(amountString,"%d",item->amount);
							float labelFontSize = GameFontManager::smallFontSize();  
							button->setItemLabel(amountString,labelFontSize,KJLinXin);
						}
						else
						{
							button->removeItemLabel();
						}
						button->creatDragReceiver(EStorageItem);
						ItemBase* itemInfo = item->getItemInfo();
						if(itemInfo && itemInfo > 0)
						{
							CCSprite* framePic = getIconFrame(itemInfo->m_quality);
							if(framePic)
							{
								button->setFrameSprite(framePic);
							}
						}
						button->setDragMove(true);
					}
				}
			}
		}
	}

}

void BackPackLayer::setOneBackPackIcon(BackPackItem* item,unsigned int index)
{
	CCAssert(index != 0, "Storage Pos Error");
	if(b_isBackPackOpened)
	{
		unsigned int page = (index-1) / EACH_PAGE_NUMBER;
		unsigned int row = ((index-1) % EACH_PAGE_NUMBER) / EACH_ROW_NUMBER;
		unsigned int colmun = ((index-1) % EACH_PAGE_NUMBER) % EACH_ROW_NUMBER;
		if(item->isLocked)
		{
			ASprite *as = AspriteManager::getInstance()->getAsprite(KUI_BIN); 
			int idx = getResourceIDByName(m_lockPicName.c_str());
			CCPoint pt;
			CCSprite * lockPic = as->getSpriteFromFrame_Middle( idx, 0, pt);
			if(m_backPackScrollPage)
			{
				m_backPackScrollPage->SetPageItemIconWithSprite(page,colmun,row,lockPic);
			}
		}
		else if(item->isEmpty)
		{
			if(m_backPackScrollPage)
			{
				m_backPackScrollPage->SetPageItemIconWithSprite(page,colmun,row,NULL);
				IconButton* button = m_backPackScrollPage->GetIconButton(page,colmun,row);
				if(button)
				{
					button->removeItemLabel();
					button->setFrameSprite(NULL);
				}
			}
		}
		else
		{
			CCSprite* pic = getIconSpriteById(item->getItemId());
			if(pic)
			{
				if(m_backPackScrollPage)
				{
					m_backPackScrollPage->SetPageItemIconWithSprite(page,colmun,row,pic);
					IconButton* button = m_backPackScrollPage->GetIconButton(page,colmun,row);
					if(item->amount > 1)
					{

						char amountString[10];
						sprintf(amountString,"%d",item->amount);
						float labelFontSize = GameFontManager::smallFontSize();  
						button->setItemLabel(amountString,labelFontSize,KJLinXin);
					}
					else
					{
						button->removeItemLabel();
					}
					ItemBase* itemInfo = item->getItemInfo();
					if(itemInfo && itemInfo > 0)
					{
						CCSprite* framePic = getIconFrame(itemInfo->m_quality);
						if(framePic)
						{
							button->setFrameSprite(framePic);
						}
					}

					button->creatDragReceiver(EBackPackItem);
					button->setDragMove(true);
				}
			}
		}
	}

}

void BackPackLayer::setOneItemIcon(BackPackItem* item,unsigned int index)
{
	/*if(index == 0)
	{
		CCAssert(index,"error item index");
		return;
	}*/
	unsigned int pos = index;
	if(pos >= kItemFairyEquip)
	{
		pos = pos - kItemFairyEquip;
		// fairy equip show
	}
	else if(pos >= kItemHeroEquip)
	{
		pos = pos - kItemHeroEquip;
		setEquipmentIcon(item,pos);
	}
	else if(pos >= kItemStorage)
	{
		pos = pos - kItemStorage;
		setOneStorageIconn(item,pos);
	}
	else
	{
		setOneBackPackIcon(item,pos);
	}
}

CCSprite* BackPackLayer::getIconSpriteById(unsigned int ItemId)
{
	ASprite *as = AspriteManager::getInstance()->getAsprite(KICON_BIN); 
	int idx = GameConfigFromLuaManager::Get()->getItemResourceId(ItemId);
	CCPoint pt;
	CCSprite * pic = as->getSpriteFromFrame_Middle( idx, 0, pt);
	return pic;
}

CCSprite* BackPackLayer::getIconFrame(unsigned int level)
{
	return ItemManager::Get()->getIconFrame(level);
}

void BackPackLayer::closeBackPack(CCObject* sender)
{
	if(b_isBackPackOpened)
	{
		if(m_backPackContainer && m_backPackContainer->getCurrentNode())
		{
			m_backPackContainer->getCurrentNode()->setVisible(false);
		}
		//UIManager::sharedManager()->SetOtherUILayoutTouchEnableExcept(true,"BackPack");
		b_isBackPackOpened = false;		
	}

	checkLayerHide();
}

void BackPackLayer::closeEquipment(cocos2d::CCObject *sender)
{
    if(b_isEquipmentOpened)
	{
		if(m_equipmentContainer && m_equipmentContainer->getCurrentNode())
		{
			m_equipmentContainer->getCurrentNode()->setVisible(false);
		}
		//UIManager::sharedManager()->SetOtherUILayoutTouchEnableExcept(true,"BackPack");
		b_isEquipmentOpened = false;

		if(m_showModle)
		{
			m_showModle->removeFromParentAndCleanup(true);
			m_showModle = NULL;
		}

		SpriteElfConfigFromLuaManager::getInstance()->CloseElfPotientionPanel();
		closeAttributeBoard(sender);
	}
	checkLayerHide();
}

void BackPackLayer::openShop(CCObject* sender)
{
    CCLog("BackPackLayer::openShop\n");
    closeEquipment(NULL);
    m_pShopUILayer->setVisible(true);
}

void BackPackLayer::openStoreHouse(CCObject* sender)
{
	if(!isVisible())
	{
		setVisible(true);
	}
	if(!b_isStorageOpened)
	{
        closeEquipment(NULL);
		if(m_storageContainer && m_storageContainer->getCurrentNode())
		{
			m_storageContainer->getCurrentNode()->setVisible(true);
		}
		GameAudioManager::sharedManager()->playEffect(350001,false);
		b_isStorageOpened = true;
		unsigned int maxPos = ItemManager::Get()->getStorageMaxPos();
		for(unsigned int i=1;i<=maxPos;i++)
		{
			BackPackItem* item = ItemManager::Get()->findItemByPos(i+kItemStorage);
			if(item)
			{
				setOneStorageIconn(item,i);
			}
		}
	}
}

void BackPackLayer::closeStorage(CCObject* sender)
{
	if(b_isStorageOpened)
	{
		if(m_storageContainer && m_storageContainer->getCurrentNode())
		{
			m_storageContainer->getCurrentNode()->setVisible(false);
		}
		b_isStorageOpened = false;
	}
	checkLayerHide();
}

void BackPackLayer::onItemClicked(CCObject* sender)
{
	if(m_backPackScrollPage)
	{
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
					int buttonIndex = button->GetButtonIndex();
					// to do
				}
			}
		}
	}
}

void BackPackLayer::onEquipmentItemDoubleClicked(CCObject* sender)
{
	CCMenu* menu = dynamic_cast<CCMenu*>(sender);
	if(menu)
	{
		for(int i =1;i<=6;i++)
		{
			UIButton* button = getEquipmentButton(i);
			if(button->getCurrentNode() == menu)
			{
				DragReceiver* receiver = button->getDragReceiver();
				if(receiver)
				{
					unsigned int pos = receiver->GetHandlerPosition();
					DragHandlerType type = receiver->GetDragItemType();
					if(type != EEquipmentItem)
					{
						return;
					}
					pos += kItemHeroEquip;
					BackPackItem* item = ItemManager::Get()->findItemByPos(pos);
					if(item)
					{
						if(getEquipmentUpgradeIcon(item->getItemId()) != NULL)
						{
							ExchangeItem* exchangeItem = ItemManager::Get()->getEquipDrawingById(item->getItemId());
							if(exchangeItem)
							{
								EquipMixLayer* layer = ShowEquipMixLayer();
								if(layer)
								{
									layer->ShowMaterials(exchangeItem,pos);
								}
							}
						}
					}
				}
				break;
			}
		}
	}
}

void BackPackLayer::onEquipmentTapped(CCObject* sender)
{
	UIMenu* menu = dynamic_cast<UIMenu*>(sender);
	if(menu)
	{
		for(int i =1;i<=6;i++)
		{
			UIButton* button = getEquipmentButton(i);
			if(button->getCurrentNode() == menu)
			{
				DragReceiver* receiver = button->getDragReceiver();
				if(receiver)
				{
					unsigned int pos = receiver->GetHandlerPosition();
					DragHandlerType type = receiver->GetDragItemType();
					if(type != EEquipmentItem)
					{
						return;
					}
					pos += kItemHeroEquip;
					ItemManager::Get()->showItemTipsByPos(pos,menu->getTouchPoint());
				}
				break;
			}
		}
	}
}
void BackPackLayer::onTapCancel(CCObject* sender)
{
	TipMgr::Get()->destroyTip();
}

void BackPackLayer::onItemTapped(CCObject* sender)
{
	if(m_backPackScrollPage)
	{
		UIMenu* menu = dynamic_cast<UIMenu*>(sender);
		if(menu)
		{
			CCNode* parent = menu->getParent();
			IconButton* button = dynamic_cast<IconButton*>(parent);
			if(button)
			{
				DragReceiver* receiver = button->getDragReceiver();
				if(receiver)
				{
					unsigned int pos = receiver->GetHandlerPosition();
					DragHandlerType type = receiver->GetDragItemType();
					if(type == EStorageItem)
					{
						pos += kItemStorage;
					}
					else if(type != EBackPackItem)
					{
						return;
					}
					ItemManager::Get()->showItemTipsByPos(pos,menu->getTouchPoint());
					//showItemTip(pos,menu->getTouchPoint());
				}
			}
		}
	}
}

void BackPackLayer::onItemDoubleClicked(CCObject* sender)
{
	if(m_backPackScrollPage)
	{
		CCMenu* menu = dynamic_cast<CCMenu*>(sender);
		if(menu)
		{
			CCNode* parent = menu->getParent();
			IconButton* button = dynamic_cast<IconButton*>(parent);
			if(button)
			{
				DragReceiver* receiver = button->getDragReceiver();
				if(receiver)
				{
					unsigned int pos = receiver->GetHandlerPosition();
					DragHandlerType type = receiver->GetDragItemType();
					if(type == EStorageItem)
					{
						pos += kItemStorage;
					}
					else if(type != EBackPackItem)
					{
						return;
					}
					BackPackItem* item = ItemManager::Get()->findItemByPos(pos);
					if(item)
					{
						ItemBase* info = item->getItemInfo();
						if(info)
						{
							switch(info->m_type)
							{
							case 1:
								{
									OnlineNetworkManager::sShareInstance()->sendUseItem(pos,info->m_id);
									break;
								}						
							case 2:
								{
									// 装备图纸
									ShowMessage(info->m_name);
									ExchangeItem* exchangeItem = ItemManager::Get()->getEquipDrawingById(info->m_id);
									if(exchangeItem)
									{
										EquipMixLayer* layer = ShowEquipMixLayer();
										if(layer)
										{
											layer->ShowMaterials(exchangeItem,pos);
										}
									}
									break;
								}
								
							}
													
						}	
					}
				}
			}
		}
	}
}

bool BackPackLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if(isVisible() && (b_isBackPackOpened || b_isStorageOpened || b_isEquipmentOpened || b_isAttributeOpened))
	{
		return true;
	}
	return false;
	/*bool isInBackPack = checkInBackPackBg(pTouch);
	bool isInEquipment = checkInEquipmentBg(pTouch);
	bool isInStorage = checkInStoragekBg(pTouch);
	return (isInBackPack || isInEquipment || isInStorage);*/
}

void BackPackLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	CCLayer::ccTouchMoved(pTouch, pEvent);
}

void BackPackLayer::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	CCLayer::ccTouchCancelled(pTouch, pEvent);
}

void BackPackLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCLayer::ccTouchEnded(pTouch, pEvent);
}

void BackPackLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCScrollTouchBgPriority, true);
}

void BackPackLayer::closeLayerCallBack(void)
{
	this->setVisible(false);
}

void BackPackLayer::checkLayerHide()
{
	bool isHide = false;

	if(!this->isVisible())
	{
		isHide = true;
	}
	else if(!b_isBackPackOpened && !b_isStorageOpened && !b_isEquipmentOpened && !b_isAttributeOpened)
	{
		isHide = true;
	}

	if(isHide)
	{
		MainMenuLayer::RemoveOneLayer(this);
	}
	

}

void BackPackLayer::reOrderBackPackItems(CCObject* sender)
{
	OnlineNetworkManager::sShareInstance()->sendBackPackReOrder(1);
}

void BackPackLayer::reOrderStorageItems(CCObject* sender)
{
	OnlineNetworkManager::sShareInstance()->sendBackPackReOrder(2);
}

bool BackPackLayer::checkInBackPackBg(CCTouch *pTouch)
{
	if(this->isVisible())
	{
		if(b_isBackPackOpened)
		{
			CCPoint point = pTouch->getLocation();
			if((point.x >= m_packbgPoint.x - m_packbgSize.width /2) && (point.x <= m_packbgPoint.x + m_packbgSize.width /2)
				&& (point.y >= m_packbgPoint.y - m_packbgSize.height /2) && (point.y <= m_packbgPoint.y + m_packbgSize.height /2))
			{
				return true;
			}
		}

	}
	return false;
}

bool BackPackLayer::checkInStoragekBg(CCTouch *pTouch)
{
	if(this->isVisible())
	{
		if(b_isStorageOpened)
		{
			CCPoint point = pTouch->getLocation();
			if((point.x >= m_storagebgPoint.x - m_storagebgSize.width /2) && (point.x <= m_storagebgPoint.x + m_storagebgSize.width /2)
				&& (point.y >= m_storagebgPoint.y - m_storagebgSize.height /2) && (point.y <= m_storagebgPoint.y + m_storagebgSize.height /2))
			{
				return true;
			}
		}

	}
	return false;
}

bool BackPackLayer::checkInEquipmentBg(CCTouch *pTouch)
{
	if(this->isVisible())
	{
		if(b_isEquipmentOpened)
		{
			CCPoint point = pTouch->getLocation();
			if((point.x >= m_equipmentbgPoint.x - m_equipmentbgSize.width /2) && (point.x <= m_equipmentbgPoint.x + m_equipmentbgSize.width /2)
				&& (point.y >= m_equipmentbgPoint.y - m_equipmentbgSize.height /2) && (point.y <= m_equipmentbgPoint.y + m_equipmentbgSize.height /2))
			{
				return true;
			}
		}

	}
	return false;
}

TXGUI::UIButton* BackPackLayer::getEquipmentButton(int index)
{
	UIButton* button;
	switch(index)
	{
		case 1:
			button = m_equipmentHelmetButton;
			break;
		case 2:
			button = m_equipmentNecklaceButton;
			break;
		case 3:
			button = m_equipmentWeaponButton;
			break;
		case 4:	
			button = m_equipmentArmorButton;
			break;
		case 5:
			button = m_equipmentRingButton;
			break;
		case 6:
			button = m_equipmentShoeButton;
			break;
		default:
			button = NULL;
			break;
	}
	return button;
}

void BackPackLayer::onBagButtonClicked()
{
	if(b_isBackPackOpened || b_isEquipmentOpened || b_isStorageOpened || b_isAttributeOpened)
	{
		if(b_isBackPackOpened && b_isEquipmentOpened)
		{
			setVisible(false);
			checkLayerHide();
		}
		else
		{
			openBackPack();
		}
	}
	else
	{
		openBackPack();
		//OnlineNetworkManager::sShareInstance()->sendBackPackMessage();
	}
}

void BackPackLayer::TrainButtonClicked(CCObject* sender)
{
	CCLog("TrainButtonClicked");
	// Note: 隐藏右侧的边框
	HideRightPanel();
	ShowElfStrengthenPanel();
}

void BackPackLayer::HideRightPanel()
{
	b_isBackPackOpened = false;
	b_isStorageOpened = false;
	if(m_backPackContainer && m_backPackContainer->getCurrentNode())
	{
		m_backPackContainer->getCurrentNode()->setVisible(false);
	}
	if(m_storageContainer && m_storageContainer->getCurrentNode())
	{
		m_storageContainer->getCurrentNode()->setVisible(false);
	}
	closeAttributeBoard(NULL);
}

void BackPackLayer::ShowElfStrengthenPanel()
{
	SpriteElfConfigFromLuaManager::getInstance()->EquipElfPotientionPanelToBackPackLayer(this);
}

void BackPackLayer::ShowElfPanelWithBackPackLayer()
{
	openBackPack();
	TrainButtonClicked(0);
}

void BackPackLayer::onBroadcastMessage(BroadcastMessage* msg)
{
	switch(msg->message)
	{
	case GM_ATTR_HEALTH_POINT_UPDATE:
		{
			USERINFO info = UserData::GetUserInfo();
			UILabel* label = backPackLayout->FindChildObjectByName<UILabel>("LifeNumberLable");
			if(label)
			{
				char text[20];
				sprintf(text,"%d",info.total_hp);
				label->setString(text);
			}
			break;
		}
	case GM_ATTR_COURAGE_UPDATE:
		{
			USERINFO info = UserData::GetUserInfo();
			UILabel* label = backPackLayout->FindChildObjectByName<UILabel>("PowerNumberLable");
			if(label)
			{
				char text[20];
				sprintf(text,"%d",info.courage);
				label->setString(text);
			}
			break;
		}
	case GM_ATTR_CHARM_UPDATE:
		{
			USERINFO info = UserData::GetUserInfo();
			UILabel* label = backPackLayout->FindChildObjectByName<UILabel>("SkillNumberLable");
			if(label)
			{
				char text[20];
				sprintf(text,"%d",info.trick);
				label->setString(text);
			}
			break;
		}
	case GM_ATTR_TRICK_UPDATE:
		{
			USERINFO info = UserData::GetUserInfo();
			UILabel* label = backPackLayout->FindChildObjectByName<UILabel>("IntellectNumberLable");
			if(label)
			{
				char text[20];
				sprintf(text,"%d",info.charm);
				label->setString(text);
			}
			break;
		}
	case GM_ATTR_HERO_LEVEL_UPDATE:
		{
			showPlayerLevel();
			break;
		}
	case GM_ATTR_EXP_UPDATE:
		{
			showPlayerExp();
			break;
		}
	}
	
}

void BackPackLayer::showEquipmentTip(unsigned int pos,CCPoint pt)
{
	BackPackItem* item = ItemManager::Get()->findItemByPos(pos);
	if(item && !item->isEmpty && !item->isLocked)
	{
		CCSprite* icon = getIconSpriteById(item->getItemId());
		if(icon)
		{
			ItemBase* itemInfo = item->getItemInfo();
			if(itemInfo)
			{
				if(itemInfo->m_quality > 0)
				{
					CCSprite* framePic = getIconFrame(itemInfo->m_quality);
					if(framePic)
					{
						icon->addChild(framePic);
						framePic->setPosition(ccp(icon->getContentSize().width * 0.5f,icon->getContentSize().height * 0.5f));
					}
				}
				TipMgr::Get()->createTip(icon,pt);
				TipMgr::Get()->addNodeDone();
			}
		}
		
	}
}

void BackPackLayer::showItemTip(unsigned int pos,CCPoint pt)
{
	BackPackItem* item = ItemManager::Get()->findItemByPos(pos);
	if(item && !item->isEmpty && !item->isLocked)
	{
		CCSprite* icon = getIconSpriteById(item->getItemId());
		if(icon)
		{
			ItemBase* itemInfo = item->getItemInfo();
			if(itemInfo)
			{
				if(itemInfo->m_quality > 0)
				{
					CCSprite* framePic = getIconFrame(itemInfo->m_quality);
					if(framePic)
					{
						icon->addChild(framePic);
						framePic->setPosition(ccp(icon->getContentSize().width * 0.5f,icon->getContentSize().height * 0.5f));
					}
				}
				TipMgr::Get()->createTip(icon,pt);
				TipMgr::Get()->addNodeDone();
			}
		}

	}
}