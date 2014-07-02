#include "OnlineNetworkManager.h"
#include "AlchemyUILayer.h"
#include "MainMenuLayer.h"
#include "AspriteManager.h"
#include "ASprite.h"
#include "resources.h"
#include "DragReceiver.h"
#include "GameFontManager.h"
#include "UserData.h"
#include "NotificationCenter.h"
#include "GMessage.h"
#include "particle_manager.h"
#include "TipMgr.h"
#include "Localization.h"
#include "GameAudioManager.h"

AlchemyUILayer::AlchemyUILayer()
{
	m_uiLayout = NULL;
	m_alchemistStoneLayer = NULL;
	m_alchemyEquipLayout = NULL;
	m_alchemistStorageLayer = NULL;
	m_alchemyExchangeLayout = NULL;
	m_exchangeItemList = NULL;
	m_selectedExchangeIndex = 0;
	m_selectedUpgradeItemPos = 0;
	m_selectedButton = NULL;
	m_heroEquipToggle = NULL;
	m_fairyEquipToggle = NULL;
	m_equipLayoutIndex = true;
	m_heroEquipPic = NULL;
	m_fairyEquipPic = NULL;
	m_selectedNpcIndex = 0;
}

AlchemyUILayer::~AlchemyUILayer()
{
	UIManager::sharedManager()->RemoveUILayout("alchemyLayout");
	UIManager::sharedManager()->RemoveUILayout("alchemyEquipLayout");
	UIManager::sharedManager()->RemoveUILayout("alchemyExchangeLayout");
	if(m_exchangeItemList)
	{
		m_exchangeItemList->clear();
		delete m_exchangeItemList;
		m_exchangeItemList = NULL;
	}
	m_bagListButton.clear();
	m_storageListButton.clear();
	m_exchangeItemInfo.clear();

	NotificationCenter::defaultCenter()->unregisterAllMsgObserver(this);
}

bool AlchemyUILayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}

	NotificationCenter::defaultCenter()->registerAllMsgObserver(this);

	m_uiLayout = UIManager::sharedManager()->CreateUILayoutFromFile("UIplist/alchemyUI.plist", this, "alchemyLayout");

	UIManager::sharedManager()->RegisterMenuHandler("alchemyLayout","AlchemyUILayer::onClosedBtClicked",
		menu_selector(AlchemyUILayer::onClosedBtClicked), this);
	UIManager::sharedManager()->RegisterMenuHandler("alchemyLayout","AlchemyUILayer::onEnterAlchemyBagClicked",
		menu_selector(AlchemyUILayer::onEnterAlchemyBagClicked), this);
	UIManager::sharedManager()->RegisterMenuHandler("alchemyLayout","AlchemyUILayer::onAlchemyExchangeClicked",
		menu_selector(AlchemyUILayer::onAlchemyExchangeClicked), this);
	UIManager::sharedManager()->RegisterMenuHandler("alchemyLayout","AlchemyUILayer::onClickFindSoul",
		menu_selector(AlchemyUILayer::onClickFindSoul), this);
	UIManager::sharedManager()->RegisterMenuHandler("alchemyLayout","AlchemyUILayer::onClickTransAllStoneEnergy",
		menu_selector(AlchemyUILayer::onClickTransAllStoneEnergy), this);
	UIManager::sharedManager()->RegisterMenuHandler("alchemyLayout","AlchemyUILayer::onTapCancel",
		menu_selector(AlchemyUILayer::onTapCancel), this);
	UIManager::sharedManager()->RegisterMenuHandler("alchemyLayout","AlchemyUILayer::onItemTapped",
		menu_selector(AlchemyUILayer::onItemTapped), this);
	initAlchemistStone();
	initNpcIcon();
	initAlchemyExItemInfo();
	updateBottomSpLabel();
	updateBottomDiamondLabel();
	updateBottomPieceLabel();
	updateBottomCoinLabel();
	return true;
}

void AlchemyUILayer::initAlchemyExItemInfo()
{
	if(m_exchangeItemInfo.size() == 0)
	{
		OnlineNetworkManager::sShareInstance()->sendSpriteExchangeMessage();
	}
}

bool AlchemyUILayer::initAlchemistStone()
{
	m_alchemistStoneLayer = CCLayer::create();
	if(m_uiLayout)
	{
		UIPicture* frame = m_uiLayout->FindChildObjectByName<UIPicture>("alchemyGridBg");
		if(frame)
		{
			int row = 4;
			int column = 6;
			CCSize size = frame->getSpriteSize();
			float width = size.width / column;
			float height = size.height / row;
			ASprite* as = AspriteManager::getInstance()->getAsprite(KUI_BIN);
			for(int i=0; i<row; i++)
			{
				for(int j=0; j<column; j++)
				{
					CCSprite* pEmptyItem = CCSprite::create();
					pEmptyItem->setContentSize(CCSize(width,height));
					CCPoint pt;
					CCSprite* pSelectItem = as->getSpriteFromFrame_Middle(map_ui_FRAME_ALCHEMY_ICON_CLICKED,0,pt);
					float scale = UIManager::sharedManager()->getScaleFactor();
					pSelectItem->setScale(scale);
					IconButton * pIcon = new IconButton(pEmptyItem, NULL, pSelectItem, this, 
						menu_selector(AlchemyUILayer::onItemClicked));
					pIcon->autorelease();
					int index = i * column + j;
					pIcon->SetButtonIndex(index+1);
					pIcon->setContentSize(pEmptyItem->getContentSize());
					pIcon->creatDragReceiver(EAlchemyBag);
					pIcon->SetTappedHandler(this,menu_selector(AlchemyUILayer::onItemTapped),menu_selector(AlchemyUILayer::onTapCancel));
					float x = (j - column /2 + 0.5f) * width;
					float y = (-i + row /2 - 0.5f) * height;
					pIcon->setPosition(ccp(x, y));

					m_bagListButton.push_back(pIcon);
					m_alchemistStoneLayer->addChild(pIcon,index+1);				
				}
				
			}
			m_alchemistStoneLayer->setPosition(frame->getWorldPosition());
			m_uiLayout->getCurrentNode()->addChild(m_alchemistStoneLayer);

			for(unsigned int i=1;i<=AlCHEMYBAGCAPACITY;i++)
			{
				unsigned int pos = i+kAlchemyBag;
				BackPackItem* item = ItemManager::Get()->findItemByPos(pos);
				if(item)
				{
					setItemIcon(item,pos);
				}
			}

			return true;
		}
	}
	return false;
}

bool AlchemyUILayer::initAlchemistStorage()
{
	m_alchemistStorageLayer = CCLayer::create();
	if(m_alchemyEquipLayout)
	{
		UIPicture* frame = m_alchemyEquipLayout->FindChildObjectByName<UIPicture>("alchemyEquipGridBg");
		if(frame)
		{
			int row = 3;
			int column = 6;
			CCSize size = frame->getSpriteSize();
			float width = size.width / column;
			float height = size.height / row;
			ASprite* as = AspriteManager::getInstance()->getAsprite(KUI_BIN);
			for(int i=0; i<row; i++)
			{
				for(int j=0; j<column; j++)
				{
					CCSprite* pEmptyItem = CCSprite::create();
					pEmptyItem->setContentSize(CCSize(width,height));
					CCPoint pt;
					CCSprite* pSelectItem = as->getSpriteFromFrame_Middle(map_ui_FRAME_ALCHEMY_ICON_CLICKED,0,pt);
					float scale = UIManager::sharedManager()->getScaleFactor();
					pSelectItem->setScale(scale);
					IconButton * pIcon = new IconButton(pEmptyItem, NULL, pSelectItem, this, 
						menu_selector(AlchemyUILayer::onItemClicked));
					pIcon->autorelease();
					int index = i * column + j;
					pIcon->SetButtonIndex(index+1);
					pIcon->setContentSize(pEmptyItem->getContentSize());
					pIcon->creatDragReceiver(EAlchemyStorage);
					pIcon->SetTappedHandler(this,menu_selector(AlchemyUILayer::onItemTapped),menu_selector(AlchemyUILayer::onTapCancel));

					float x = (j - column /2 + 0.5f) * width;
					float y = (-i + row /2) * height;
					pIcon->setPosition(ccp(x, y));

					m_storageListButton.push_back(pIcon);
					m_alchemistStorageLayer->addChild(pIcon,index+1);			
				}

			}
			m_alchemistStorageLayer->setPosition(frame->getWorldPosition());
			m_alchemyEquipLayout->getCurrentNode()->addChild(m_alchemistStorageLayer);

			for(unsigned int i=1;i<=AlCHEMYSTORAGECAPACITY;i++)
			{
				unsigned int pos = i+kAlchemyStorage;
				BackPackItem* item = ItemManager::Get()->findItemByPos(pos);
				if(item)
				{
					setItemIcon(item,pos);
				}
			}

			m_heroEquipToggle = m_alchemyEquipLayout->FindChildObjectByName<UIButtonToggle>("heroAlchemyButtonToggle");
			m_fairyEquipToggle = m_alchemyEquipLayout->FindChildObjectByName<UIButtonToggle>("fairyAlchemyButtonToggle");
			m_heroEquipPic = m_alchemyEquipLayout->FindChildObjectByName<UIPicture>("alchemyDecorationHero");
			m_fairyEquipPic = m_alchemyEquipLayout->FindChildObjectByName<UIPicture>("alchemyDecorationFairy");

			if(m_fairyEquipPic)
			{
				m_fairyEquipPic->setVisible(false);
			}

			m_equipLayoutIndex = true;
			showHeroEquipItems();
			setStoneEnergyLabel();
			if(m_heroEquipToggle)
			{
				m_heroEquipToggle->selected();
			}
			return true;
		}
	}
	return false;
}

bool AlchemyUILayer::initAlchemistExchange()
{
	if(m_alchemyExchangeLayout)
	{
		if(!m_exchangeItemList)
		{
			m_exchangeItemList = new std::map<unsigned int,unsigned int>();
			list<unsigned int>* exchangeIds = ItemManager::Get()->getExchangeSpriteStones();
			if(exchangeIds)
			{
				for(std::list<unsigned int>::iterator it = exchangeIds->begin();
					it != exchangeIds->end();it++)
				{
					unsigned int exchangeId = *it;
					ExchangeItem* item = ItemManager::Get()->getExchageItemById(exchangeId);
					if(item && item->m_toItems && item->m_toItems->size() == 1)
					{
						for (std::list<std::pair<unsigned int ,unsigned int> >::iterator iter = item->m_toItems->begin();
							iter != item->m_toItems->end();iter++)
						{
							m_exchangeItemList->insert(make_pair((*iter).first,exchangeId));
						}	
					}
				}

				exchangeIds->clear();
				delete exchangeIds;
				exchangeIds = NULL;
			}		

		}

		unsigned int defaultIndex = 0;
		m_exchangeList = m_alchemyExchangeLayout->FindChildObjectByName<UIScrollList>("clchemyList");
		if(m_exchangeList)
		{
			m_exchangeList->clearChildrens();
			for(std::map<unsigned int,unsigned int>::iterator it = m_exchangeItemList->begin();
				it != m_exchangeItemList->end();it++)
			{
				addExchangeItem((*it).first,(*it).first);
				if(defaultIndex == 0)
				{
					defaultIndex = (*it).first;
				}
			}

		}
		showSelectecdExchangeItem(defaultIndex);
		setStoneEnergyLabel();
		setSpiritChipLabel();
	}
	return false;
}

void AlchemyUILayer::initNpcIcon()
{
	setNpcHeadIcon("alchemyNpcPic1","map_ui_system_icon_FRAME_ICON_NPC_501");
	setNpcHeadIcon("alchemyNpcPic2","map_ui_system_icon_FRAME_ICON_NPC_502");
	setNpcHeadIcon("alchemyNpcPic3","map_ui_system_icon_FRAME_ICON_NPC_503");
	setNpcHeadIcon("alchemyNpcPic4","map_ui_system_icon_FRAME_ICON_NPC_501");
	setNpcHeadIcon("alchemyNpcPic5","map_ui_system_icon_FRAME_ICON_NPC_502");
	USERINFO info = UserData::GetUserInfo();
	unsigned int npc = info.m_searchSpriteNpc;
	setNpcSelected(npc+1);
}

void AlchemyUILayer::onReceivedExchangeInfo(CSGetExchangeSSInfoRsp* msg)
{
	if(msg)
	{
		m_exchangeItemInfo.clear();
		unsigned int count = msg->ss_list_size();
		for(unsigned int i=0;i<count;++i)
		{
			ExchangeSSInfo ssInfo = msg->ss_list(i);
			stAlchemyExchangeInfo info;
			info.ss_id = ssInfo.ss_id();
			info.consume = ssInfo.consume();
			info.convert = ssInfo.convert();
			info.key = ssInfo.key();
			info.need_chip = ssInfo.need_chip();
			info.value = ssInfo.value();
			m_exchangeItemInfo.insert(make_pair(info.ss_id,info));
		}
	}
}

void AlchemyUILayer::setNpcHeadIcon(const char* name,const char* resoureName)
{
	UIButton* bt = m_uiLayout->FindChildObjectByName<UIButton>(name);
	if(bt)
	{
		CCMenuItemSprite*  item = bt->getMenuItemSprite();
		if(item)
		{
			ASprite *as = AspriteManager::getInstance()->getAsprite(KICON_BIN); 
			int idx = getResourceIDByName(resoureName);
			CCPoint pt;
			CCSprite * sprite = as->getSpriteFromFrame_Middle( idx, 0, pt);
			if(sprite)
			{
				float scale = 1;
				if(sprite->getContentSize().width != 0)
				{
					scale = item->getNormalImage()->getContentSize().width / sprite->getContentSize().width;
					sprite->setScale(scale);
				}

				bt->setIconSprite(sprite);

				ASprite *as = AspriteManager::getInstance()->getAsprite(KUI_BIN); 
				int idx = getResourceIDByName("map_ui_FRAME_FRAME_HEADSHOT");
				CCPoint pt;
				CCSprite * frame = as->getSpriteFromFrame_Middle( idx, 0, pt);
				if(frame)
				{
					if(frame->getContentSize().width != 0)
					{
						CCSize imageSize = item->getNormalImage()->getContentSize();
						float frameScale = imageSize.width / frame->getContentSize().width;
						frame->setScale(1.2f*frameScale);
						frame->setContentSize(CCSize(imageSize.width * 1.2f,imageSize.height * 1.2f));
					}
					item->setNormalImage(frame);
				}

				idx = getResourceIDByName("map_ui_FRAME_ALCHEMY_CHARACTER_ICON_SELECTED");
				CCSprite * clickedFrame = as->getSpriteFromFrame_Middle( idx, 0, pt);
				if(clickedFrame)
				{
					if(clickedFrame->getContentSize().width != 0)
					{
						CCSize imageSize = item->getSelectedImage()->getContentSize();
						float frameScale = imageSize.width / clickedFrame->getContentSize().width;
						clickedFrame->setScale(1.2f*frameScale);
						clickedFrame->setContentSize(CCSize(imageSize.width * 1.2f,imageSize.height * 1.2f));
					}
					item->setSelectedImage(clickedFrame);
				}
			}	
		}
	}
	
}

void AlchemyUILayer::onEquipmentTapped(CCObject* sender)
{
	UIMenu* menu = dynamic_cast<UIMenu*>(sender);
	if(menu)
	{
		UIControlBase* controller = menu->getControlNode();
		UIButton* button = dynamic_cast<UIButton*>(controller);
		if(button)
		{
			unsigned int pos = button->getButtonIndex();
			if(m_equipLayoutIndex)
			{
				pos += kAlchemyHeroEquip;
			}
			else
			{
				pos += kAlchemyFairyEquip;
			}
			ItemManager::Get()->showItemTipsByPos(pos,menu->getTouchPoint());
		}
	}
}
void AlchemyUILayer::onTapCancel(CCObject* sender)
{
	TipMgr::Get()->destroyTip();
}

void AlchemyUILayer::onItemTapped(CCObject* sender)
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
				if(type == EAlchemyBag)
				{
					pos += kAlchemyBag;
				}
				else if(type == EAlchemyStorage)
				{
					pos += kAlchemyStorage;
				}
				ItemManager::Get()->showItemTipsByPos(pos,menu->getTouchPoint());
			}
		}
	}
}

void AlchemyUILayer::onClosedBtClicked(CCObject* sender)
{
	MainMenuLayer::RemoveOneLayer(this);
	HideAlchemyUILayer();
}

void AlchemyUILayer::onClosedEquipBtClicked(CCObject* sender)
{
	hideAlchemyEquipLayer();
	showAlchemyLayer();
}

void AlchemyUILayer::onEnterAlchemyBagClicked(CCObject* sender)
{
	hideAlchemyLayer();
	showAlchemyEquipLayer();
}

void AlchemyUILayer::onClosedExchangeBtClicked(CCObject* sender)
{
	hideAlchemyExchangeLayer();
	showAlchemyLayer();
}

void AlchemyUILayer::onAlchemyExchangeClicked(CCObject* sender)
{
	hideAlchemyLayer();
	showAlchemyExchangeLayer();
}

void AlchemyUILayer::onItemClicked(CCObject* sender)
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
			}
		}
	}
}

void AlchemyUILayer::onExchangeListItemClicked(CCObject* sender)
{
	CCMenuItem* item = dynamic_cast<CCMenuItem*>(sender);
	if(item)
	{
		CCNode* node = item->getParent();
		UIMenu* menu = dynamic_cast<UIMenu*>(node);
		if(menu)
		{
			UIControlBase* controller = menu->getControlNode();
			UIButton* button = dynamic_cast<UIButton*>(controller);
			if(button)
			{				
				unsigned int type = button->getButtonIndex();
				showSelectecdExchangeItem(type);

				if(m_selectedButton)
				{
					CCMenuItem* lastItem = m_selectedButton->getMenuItemSprite();
					if(lastItem)
					{
						lastItem->unselected();
					}
				}
				m_selectedButton = button;
				item->selected();
			}
		}
	}
}

void AlchemyUILayer::onDragInAlchemyBtClicked(CCObject* sender)
{
	unselectUpgradeItem();
}

void AlchemyUILayer::onClickFairyEquip(CCObject* sender)
{
	if(m_heroEquipToggle)
	{
		m_heroEquipToggle->unselected();
	}
	if(m_fairyEquipToggle)
	{
		m_fairyEquipToggle->selected();
	}
	if(m_equipLayoutIndex)
	{
		m_equipLayoutIndex = false;
		showEquipItems(m_equipLayoutIndex);
		if(m_heroEquipPic)
		{
			m_heroEquipPic->setVisible(false);
		}
		if(m_fairyEquipPic)
		{
			m_fairyEquipPic->setVisible(true);
		}
	}
}

void AlchemyUILayer::onClickHeroEquip(CCObject* sender)
{
	if(m_heroEquipToggle)
	{
		m_heroEquipToggle->selected();
	}
	if(m_fairyEquipToggle)
	{
		m_fairyEquipToggle->unselected();
	}
	if(!m_equipLayoutIndex)
	{
		m_equipLayoutIndex = true;
		showEquipItems(m_equipLayoutIndex);
		if(m_heroEquipPic)
		{
			m_heroEquipPic->setVisible(true);
		}
		if(m_fairyEquipPic)
		{
			m_fairyEquipPic->setVisible(false);
		}
	}
}

void AlchemyUILayer::onClickFindSoul(CCObject* sender)
{
	OnlineNetworkManager::sShareInstance()->sendFindSoulStoneMessage();
	/*unsigned int index = m_selectedNpcIndex;
	if(index < 5)
	{
		index++;
	}
	else
	{
		index = 1;
	}
	setNpcSelected(index);*/
}

void AlchemyUILayer::onClickTransAllStoneEnergy(CCObject* sender)
{
	OnlineNetworkManager::sShareInstance()->sendTranStoneToEnergy(true);
}

void AlchemyUILayer::onClickUpgradeStone(CCObject* sender)
{
	if(m_selectedUpgradeItemPos == 0)
	{
		return;
	}

	BackPackItem* item = ItemManager::Get()->findItemByPos(m_selectedUpgradeItemPos);
	if(item)
	{
		OnlineNetworkManager::sShareInstance()->sendUpgradeSoulStone(m_selectedUpgradeItemPos);
	}
}

void AlchemyUILayer::onClickExchangeBt(CCObject* sender)
{
	ItemBase* info = ItemManager::Get()->getItemInfoById(m_selectedExchangeIndex);
	if(info && m_exchangeItemList)
	{
		unsigned int exchangeId = (*m_exchangeItemList)[m_selectedExchangeIndex];
		ExchangeItem* item = ItemManager::Get()->getExchageItemById(exchangeId);
		if(item && item->m_fromItems && item->m_fromItems->size() == 1)
		{
			std::list<std::pair<unsigned int ,unsigned int> >::iterator iter = item->m_fromItems->begin();
			unsigned int count = iter->second;
			if(count <= UserData::GetUserChip())
			{
				OnlineNetworkManager::sShareInstance()->sendItemExchangeReq(exchangeId,NULL,0);
			}
			else
			{
				ShowMessage(Localizatioin::getLocalization("M_FINDSPIRIT_SPIRITPIECESTORE"));
			}
		}
		else
		{
			ShowMessage("Error exchange item id");
		}
	}
	else
	{
		ShowMessage("Error exchange item");
	}
}

void AlchemyUILayer::addExchangeItem(unsigned int itemId,unsigned int index)
{
	ItemBase* info = ItemManager::Get()->getItemInfoById(itemId);
	if(info)
	{
		ASprite* pAsprite = AspriteManager::getInstance()->getAsprite(KUI_BIN);
		CCPoint parentPos;
		CCSprite* normal = pAsprite->getSpriteFromFrame_Middle(map_ui_FRAME_ALCHEMY_EXCHANGE_SOUL1 ,0, parentPos);//map_ui_FRAME_ALCHEMY_EXCHANGE_SOUL1
		CCSprite* clicked= pAsprite->getSpriteFromFrame_Middle(map_ui_FRAME_ALCHEMY_EXCHANGE_SOUL1_SELECTED, 0, parentPos);//map_ui_FRAME_ALCHEMY_EXCHANGE_SOUL1_SELECTED
		UIButton* button = m_exchangeList->AddNewItem(normal,
			clicked,
			"AlchemyUILayer::onExchangeListItemClicked",
			"",
			ccWHITE,
			kCCScrollMenuPriority);
		if(button)
		{			
			CCPoint pt;
			CCSprite* sprite = pAsprite->getSpriteFromFrame_Middle(map_ui_FRAME_ALCHEMY_EXCHANGE_TEXT_SOUL1NAME,0,pt);
			CCSize labelSize = sprite->getContentSize();
			UILabelTTF* labelName = UILabelTTF::create(info->m_name,KJLinXin,30,CCSize(300,labelSize.height),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
			labelName->setPosition(ccpSub(pt,parentPos));
			labelName->setColor(ItemManager::Get()->getLabelColorByQuality(info->m_quality));
			button->getAnimationNode()->addChild(labelName,2);

			CCSprite* sprite1 = pAsprite->getSpriteFromFrame_Middle(map_ui_FRAME_ALCHEMY_EXCHANGE_TEXT_SOUL1ADD,0,pt);
			labelSize = sprite1->getContentSize();


			std::map<unsigned int,stAlchemyExchangeInfo>::iterator it = m_exchangeItemInfo.find(itemId);
			if(it != m_exchangeItemInfo.end())
			{
				const char* text = ItemManager::Get()->getAttributionText(it->second.key,it->second.value);
				if(text)
				{
					UILabelTTF* labelAdd = UILabelTTF::create(text,KJLinXin,24,CCSize(300,labelSize.height),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
					labelAdd->setPosition(ccpSub(pt,parentPos));
					button->getAnimationNode()->addChild(labelAdd,3);
				}
			}
			
			
			CCSprite* iconSprite = pAsprite->getSpriteFromFrame_Middle(map_ui_FRAME_ALCHEMY_EXCHANGE_ICON_SOUL1,0,pt);
			CCSprite* icon = ItemManager::Get()->getIconSpriteById(itemId);
			icon->setPosition(ccpSub(pt,parentPos));
			button->getAnimationNode()->addChild(icon,4);

			button->setButtonIndex(index);
			showSpriteParticleEffect(icon,itemId,ccp(icon->getContentSize().width * 0.5,icon->getContentSize().height * 0.5));
		}
	}
	CC_SAFE_DELETE(info);
}

void AlchemyUILayer::showSelectecdExchangeItem(unsigned int index)
{
	m_selectedExchangeIndex = index;
	ItemBase* info = ItemManager::Get()->getItemInfoById(index);
	std::map<unsigned int,stAlchemyExchangeInfo>::iterator it = m_exchangeItemInfo.find(index);
	if(info && it != m_exchangeItemInfo.end())
	{
		if(m_alchemyExchangeLayout)
		{
			UILabel* nameLabel = m_alchemyExchangeLayout->FindChildObjectByName<UILabel>("alchemyExchangeSelectedLabel");
			if(nameLabel)
			{
				nameLabel->setString(info->m_name);
				nameLabel->setColor(ItemManager::Get()->getLabelColorByQuality(info->m_quality));
			}
			UILabel* numberLabel = m_alchemyExchangeLayout->FindChildObjectByName<UILabel>("alchemyExchangeSelectedNumLabel");
			if(numberLabel)
			{
				const char* text = ItemManager::Get()->getAttributionText(it->second.key,it->second.value);
				if(text)
				{
					numberLabel->setString(text);
				}
				else
				{
					numberLabel->setString("");
				}
			}

			UILabel* needLabel = m_alchemyExchangeLayout->FindChildObjectByName<UILabel>("alchemyExchangeEnergy2Label");
			if(needLabel)
			{
				char text[20];
				sprintf(text,"%d",it->second.consume);
				needLabel->setString(text);
			}

			UIPicture* pic = m_alchemyExchangeLayout->FindChildObjectByName<UIPicture>("alchemyExchangeSelectedIcon");
			if(pic)
			{
				CCSprite* sprite = ItemManager::Get()->getIconSpriteById(info->m_id);
				if(sprite)
				{
					pic->setSprite(sprite);
					showSpriteParticleEffect(sprite,index,ccp(sprite->getContentSize().width * 0.5,sprite->getContentSize().height * 0.5));
			
				}
			}
			//if(m_exchangeItemList)
			//{
			//	ExchangeItem* item = ItemManager::Get()->getExchageItemById(exchangeId);
			//	if(item && item->m_fromItems && item->m_fromItems->size() == 1)
			//	{
			//		std::list<std::pair<unsigned int ,unsigned int> >::iterator iter = item->m_fromItems->begin();
			//		unsigned int count = iter->second;
					
					UILabel* spriteLabel = m_alchemyExchangeLayout->FindChildObjectByName<UILabel>("alchemyExchangePiece2NumberLabel");
					if(spriteLabel)
					{
						char text[10];
						sprintf(text,"%d",it->second.need_chip);
						spriteLabel->setString(text);
					}
			//	}
			//}
		}
	}
	CC_SAFE_DELETE(info);
}

void AlchemyUILayer::closeLayerCallBack(void)
{
	HideAlchemyUILayer();
}


void AlchemyUILayer::showAlchemyLayer()
{
	if(m_uiLayout)
	{
		m_uiLayout->setVisible(true);
	}
	GameAudioManager::sharedManager()->playEffect(350001,false);
}

void AlchemyUILayer::hideAlchemyLayer()
{
	if(m_uiLayout)
	{
		m_uiLayout->setVisible(false);
	}
}

void AlchemyUILayer::showAlchemyEquipLayer()
{
	if(!m_alchemyEquipLayout)
	{
		m_alchemyEquipLayout = UIManager::sharedManager()->CreateUILayoutFromFile("UIplist/alchemyEquipUI.plist", this, "alchemyEquipLayout");
		UIManager::sharedManager()->RegisterMenuHandler("alchemyEquipLayout","AlchemyUILayer::onClosedEquipBtClicked",
			menu_selector(AlchemyUILayer::onClosedEquipBtClicked), this);
		UIManager::sharedManager()->RegisterMenuHandler("alchemyEquipLayout","AlchemyUILayer::onDragInAlchemyBtClicked",
			menu_selector(AlchemyUILayer::onDragInAlchemyBtClicked), this);
		UIManager::sharedManager()->RegisterMenuHandler("alchemyEquipLayout","AlchemyUILayer::onClickFairyEquip",
			menu_selector(AlchemyUILayer::onClickFairyEquip), this);
		UIManager::sharedManager()->RegisterMenuHandler("alchemyEquipLayout","AlchemyUILayer::onClickHeroEquip",
			menu_selector(AlchemyUILayer::onClickHeroEquip), this);
		UIManager::sharedManager()->RegisterMenuHandler("alchemyEquipLayout","AlchemyUILayer::onClickUpgradeStone",
			menu_selector(AlchemyUILayer::onClickUpgradeStone), this);
		UIManager::sharedManager()->RegisterMenuHandler("alchemyEquipLayout","AlchemyUILayer::onClosedBtClicked",
			menu_selector(AlchemyUILayer::onClosedBtClicked), this);
		UIManager::sharedManager()->RegisterMenuHandler("alchemyEquipLayout","AlchemyUILayer::onEquipmentTapped",
			menu_selector(AlchemyUILayer::onEquipmentTapped), this);
		UIManager::sharedManager()->RegisterMenuHandler("alchemyEquipLayout","AlchemyUILayer::onTapCancel",
			menu_selector(AlchemyUILayer::onTapCancel), this);
		initAlchemistStorage();
	}
	if(m_alchemyEquipLayout)
	{
		m_alchemyEquipLayout->setVisible(true);
	}
	GameAudioManager::sharedManager()->playEffect(350001,false);
}

void AlchemyUILayer::hideAlchemyEquipLayer()
{
	if(m_alchemyEquipLayout)
	{
		m_alchemyEquipLayout->setVisible(false);
	}
}

void AlchemyUILayer::showAlchemyExchangeLayer()
{
	if(!m_alchemyExchangeLayout)
	{
		m_alchemyExchangeLayout = UIManager::sharedManager()->CreateUILayoutFromFile("UIplist/alchemyExchangeUI.plist", this, "alchemyExchangeLayout");
		UIManager::sharedManager()->RegisterMenuHandler("alchemyExchangeLayout","AlchemyUILayer::onClosedExchangeBtClicked",
			menu_selector(AlchemyUILayer::onClosedExchangeBtClicked), this);
		UIManager::sharedManager()->RegisterMenuHandler("alchemyExchangeLayout","AlchemyUILayer::onExchangeListItemClicked",
			menu_selector(AlchemyUILayer::onExchangeListItemClicked), this);
		UIManager::sharedManager()->RegisterMenuHandler("alchemyExchangeLayout","AlchemyUILayer::onClickExchangeBt",
			menu_selector(AlchemyUILayer::onClickExchangeBt), this);
		UIManager::sharedManager()->RegisterMenuHandler("alchemyExchangeLayout","AlchemyUILayer::onClosedBtClicked",
			menu_selector(AlchemyUILayer::onClosedBtClicked), this);
		initAlchemistExchange();
	}
	if(m_alchemyExchangeLayout)
	{
		m_alchemyExchangeLayout->setVisible(true);
	}
	GameAudioManager::sharedManager()->playEffect(350001,false);
}

void AlchemyUILayer::hideAlchemyExchangeLayer()
{
	if(m_alchemyExchangeLayout)
	{
		m_alchemyExchangeLayout->setVisible(false);
	}
}

void AlchemyUILayer::setItemIcon(BackPackItem* item,unsigned int index)
{
	if(index >= kAlchemyFairyEquip)
	{
		if(!m_equipLayoutIndex)
		{
			unsigned int pos = index - kAlchemyFairyEquip;
			setEquipItemIcon(item,pos);
		}
	}
	if(index >= kAlchemyHeroEquip)
	{
		if(m_equipLayoutIndex)
		{
			unsigned int pos = index - kAlchemyHeroEquip;
			setEquipItemIcon(item,pos);
		}
	}
	else if(index >= kAlchemyStorage)
	{
		unsigned int pos = index - kAlchemyStorage;
		setStorageItemIcon(item,pos);
	}
	else if(index >= kAlchemyBag)
	{
		unsigned int pos = index - kAlchemyBag;
		setBagItemIcon(item,pos);
	}
	else
	{
		CCLog("AlchemyUILayer ,error item index :%d",index);
	}
}

void AlchemyUILayer::setBagItemIcon(BackPackItem* item,unsigned int position)
{
	if(item)
	{
		CCAssert(position != 0,"Error alchemy position");
		if(m_uiLayout && m_uiLayout->isVisible())
		{
			IconButton* button = m_bagListButton[position - 1];
			if(button)
			{
				if(item->isLocked)
				{
					ASprite *as = AspriteManager::getInstance()->getAsprite(KUI_BIN); 
					CCPoint pt;
					CCSprite * lockPic = as->getSpriteFromFrame_Middle(map_ui_FRAME_STORAGE_GRID1_LOCKED, 0, pt);
					if(lockPic)
					{
						lockPic->setScale(UIManager::sharedManager()->getScaleFactor());
						button->SetNormalIcon(lockPic);
					}
				}
				else if(item->isEmpty)
				{
					button->SetNormalIcon(NULL);
				}
				else
				{
					CCSprite* sprite = ItemManager::Get()->getIconSpriteById(item->getItemId());
					sprite->setScale(UIManager::sharedManager()->getScaleFactor());
					button->SetNormalIcon(sprite);
					button->creatDragReceiver(EAlchemyBag);
					button->setDragMove(true);
					showSpriteParticleEffect(sprite,item->getItemId(),ccp(sprite->getContentSize().width * 0.5,sprite->getContentSize().height * 0.5));
				}

			}
		}
	}
	
}

void AlchemyUILayer::setStorageItemIcon(BackPackItem* item,unsigned int position)
{
	if(item)
	{
		CCAssert(position != 0,"Error alchemy position");
		if(m_alchemyEquipLayout && m_alchemyEquipLayout->isVisible())
		{
			IconButton* button = m_storageListButton[position-1];
			if(button)
			{
				if(item->isLocked)
				{
					ASprite *as = AspriteManager::getInstance()->getAsprite(KUI_BIN); 
					CCPoint pt;
					CCSprite * lockPic = as->getSpriteFromFrame_Middle(map_ui_FRAME_STORAGE_GRID1_LOCKED, 0, pt);
					if(lockPic)
					{
						lockPic->setScale(UIManager::sharedManager()->getScaleFactor());
						button->SetNormalIcon(lockPic);
					}
				}
				else if(item->isEmpty)
				{
					button->SetNormalIcon(NULL);
				}
				else
				{
					CCSprite* sprite = ItemManager::Get()->getIconSpriteById(item->getItemId());
					sprite->setScale(UIManager::sharedManager()->getScaleFactor());
					button->SetNormalIcon(sprite);
					showSpriteParticleEffect(sprite,item->getItemId(),ccp(sprite->getContentSize().width * 0.5,sprite->getContentSize().height * 0.5));
					button->creatDragReceiver(EAlchemyBag);
					button->setDragMove(true);
					
				}

			}
		}
	}
}

void AlchemyUILayer::setEquipItemIcon(BackPackItem* item,unsigned int position)
{
	if(m_alchemyEquipLayout && m_alchemyEquipLayout->isVisible())
	{
		char buttonName[30];
		sprintf(buttonName,"alchemyEquipGrid%d",position);
		UIButton* button = m_alchemyEquipLayout->FindChildObjectByName<UIButton>(buttonName);
		if(!button)
		{
			return;
		}
		if(item)
		{
			if(item->isLocked)
			{
				ASprite *as = AspriteManager::getInstance()->getAsprite(KUI_BIN); 
				CCPoint pt;
				CCSprite * lockPic = as->getSpriteFromFrame_Middle( map_ui_FRAME_STORAGE_GRID1_LOCKED, 0, pt);
				if(lockPic)
				{
					button->setIconSprite(lockPic);
				}
				setUnlockEqiupLabel(position,true);
			}
			else 
			{
				setUnlockEqiupLabel(position,false);
				if(item->isEmpty)
				{
					button->setIconSprite(NULL);
				}
				else
				{		
					CCSprite* equipPic = ItemManager::Get()->getIconSpriteById(item->getItemId());
					if(equipPic)
					{	
						button->setIconSprite(equipPic);
						showSpriteParticleEffect(equipPic,item->getItemId(),ccp(equipPic->getContentSize().width * 0.5,equipPic->getContentSize().height * 0.5));
						button->setDragMove(true);
					}
				}
			}
		}
		else
		{
			if(button)
			{
				button->setIconSprite(NULL);
			}
		}
	}
}

void AlchemyUILayer::setUnlockEqiupLabel(int index,bool isVisible)
{
	char labelName[30];
	sprintf(labelName,"alchemyEquipGridLabel%d",index);
	UILabel* label = m_alchemyEquipLayout->FindChildObjectByName<UILabel>(labelName);
	if(label)
	{
		label->setVisible(isVisible);
	}
}

void AlchemyUILayer::selectUpgradeItem(unsigned int position,bool isEffect)
{
	if(position >= (kAlchemyFairyEquip + 900) || position < kAlchemyStorage)
	{
		CCLog("error upgrade item pos : %d",position);
		return;
	}

	BackPackItem* item = ItemManager::Get()->findItemByPos(position);
	if(item)
	{
		UIButton* button = m_alchemyEquipLayout->FindChildObjectByName<UIButton>("alchemyDragInSoulIcon");
		CCSprite* sprite = ItemManager::Get()->getIconSpriteById(item->getItemId());
		if(button && sprite)
		{
			m_selectedUpgradeItemPos = position;
			button->setIconSprite(sprite);

			if(isEffect)
			{
				if(button && button->getAnimationNode())
				{
					CCNode* particle = ParticleManagerX::sharedManager()->getParticles_uieffect("particle_effect_soulupgrade");
					if(particle != NULL)
					{
						CCNode* child = button->getAnimationNode()->getChildByTag(100);
						if(child)
						{
							child->removeFromParentAndCleanup(true);
							child = NULL;
						}
						button->getAnimationNode()->addChild(particle,100,100);
						particle->setPosition(CCPointZero);
					}
				}
			}
		}
		if(item->m_spriteInfo)
		{
			UILabel* label = m_alchemyEquipLayout->FindChildObjectByName<UILabel>("alchemyEnergyNeedLabel");
			if(label)
			{
				if(item->m_spriteInfo->levelUpCost != 0)
				{
					USERINFO info = UserData::GetUserInfo();
					char spNeed[50];
					sprintf(spNeed,"%d",item->m_spriteInfo->levelUpCost);
					label->setString(spNeed);
					if(info.m_spriteEnergy >= item->m_spriteInfo->levelUpCost)
					{
						label->setColor(ccGREEN);	
					}
					else
					{
						label->setColor(ccRED);
					}
				}
				else
				{
					label->setColor(ccGREEN);
					label->setString(Localizatioin::getLocalization("M_REACH_HIGHESTLEVEL"));
				}
			}
			setEnergyIconVisible(true);
		}
	}
}

void AlchemyUILayer::unselectUpgradeItem()
{
	m_selectedUpgradeItemPos = 0;
	UIButton* button = m_alchemyEquipLayout->FindChildObjectByName<UIButton>("alchemyDragInSoulIcon");
	if(button)
	{
		button->setIconSprite(NULL);
		button->setDragMove(false);
	}
	UILabel* label = m_alchemyEquipLayout->FindChildObjectByName<UILabel>("alchemyEnergyNeedLabel");
	if(label)
	{
		label->setString("");
	}
	setEnergyIconVisible(false);
}

void AlchemyUILayer::showEquipItems(bool isHero)
{
	m_equipLayoutIndex = isHero;
	if(m_equipLayoutIndex)
	{
		showHeroEquipItems();
	}
	else
	{
		showFairyEquipItems();
	}
}

void AlchemyUILayer::showHeroEquipItems()
{
	for(unsigned int i=1;i<= 8;i++)
	{
		BackPackItem* item = ItemManager::Get()->findItemByPos(kAlchemyHeroEquip+i);
		if(checkPlayerEquipUnlock(i))
		{
			item->isLocked = false;
		}
		else
		{
			item->isLocked = true;
		}
		setEquipItemIcon(item,i);
	}
}

void AlchemyUILayer::showFairyEquipItems()
{
	for(unsigned int i=1;i<= 8;i++)
	{
		BackPackItem* item = ItemManager::Get()->findItemByPos(kAlchemyFairyEquip+i);
		if(checkPlayerEquipUnlock(i))
		{
			item->isLocked = false;
		}
		else
		{
			item->isLocked = true;
		}
		setEquipItemIcon(item,i);
	}
}

bool AlchemyUILayer::checkPlayerEquipUnlock(int index)
{
	int playerLevel =  UserData::GetUserLevel();
	if((playerLevel - 20)/10 >= index)
	{
		return true;
	}
	return false;
}

void AlchemyUILayer::onReceivedUpgradeSuccess()
{
	selectUpgradeItem(m_selectedUpgradeItemPos,true);
	GameAudioManager::sharedManager()->playEffect(350004,false);
}

void AlchemyUILayer::onReceivedSearchResult(unsigned int coin,unsigned int npcIndex,unsigned int itemId)
{
	unsigned int cost = ItemManager::Get()->getAlchemySearchNpcCost(m_selectedNpcIndex);
	if(cost != coin)
	{
		CCLog("search sprite stone fail return  coin: %d, next npc: %d",(cost - coin),npcIndex);
		char text[50];
		sprintf(text,"%s%d",Localizatioin::getLocalization("M_FINDSPIRIT_FAIL_RESTORE"),cost - coin);
		ShowMessage(text,ccRED);
		GameAudioManager::sharedManager()->playEffect(350003,false);
	}
	else
	{
		ItemBase* info = ItemManager::Get()->getItemInfoById(itemId);
		if(info)
		{
			char text[50];
			sprintf(text,"%s%s",Localizatioin::getLocalization("M_FINDSPIRIT_SUCCESS_GET"),info->m_name);
			ShowMessage(text,ccGREEN);
			GameAudioManager::sharedManager()->playEffect(350002,false);
		}
		CCLog("search sprite stone success cost: %d, next npc: %d,itemId: %d",coin,npcIndex,itemId);
	}
	bool isEffect = npcIndex > m_selectedNpcIndex ? true : false;
	setNpcSelected(npcIndex,isEffect);
}

void AlchemyUILayer::setNpcSelected(unsigned int index,bool isEffect)
{
	if(index == m_selectedNpcIndex)
	{
		return;
	}
	char lastNpcName[30];
	sprintf(lastNpcName,"alchemyNpcPic%d",m_selectedNpcIndex);
	UIButton* bt = m_uiLayout->FindChildObjectByName<UIButton>(lastNpcName);
	if(bt)
	{
		CCMenuItemSprite*  item = bt->getMenuItemSprite();
		if(item)
		{	
			item->unselected();
		}	

	}

	char iconName[30];
	sprintf(iconName,"alchemyNpcPic%d",index);
	bt = m_uiLayout->FindChildObjectByName<UIButton>(iconName);	
	if(bt)
	{
		CCMenuItemSprite*  item = bt->getMenuItemSprite();
		if(item)
		{		
			item->selected();
			if(isEffect)
			{
				CCNode* particle = ParticleManagerX::sharedManager()->getParticles_uieffect("particle_effect_findsoulsuccess");
				if(particle != NULL)
				{
					CCNode* child = bt->getAnimationNode()->getChildByTag(100);
					if(child)
					{
						child->removeFromParentAndCleanup(true);
						child = NULL;
					}
					bt->getAnimationNode()->addChild(particle,100,100);
					particle->setPosition(CCPointZero);
				}
			}
		}		
		
	}

	UILabel* pLabel = m_uiLayout->FindChildObjectByName<UILabel>("costNumberLable");
	if(pLabel)
	{
		unsigned int cost = ItemManager::Get()->getAlchemySearchNpcCost(index);
		char costText[10];
		sprintf(costText,"%d",cost);
		pLabel->setString(costText);
	}

	m_selectedNpcIndex = index;
}

void AlchemyUILayer::setStoneEnergyLabel()
{
	if(m_alchemyEquipLayout && m_alchemyEquipLayout->isVisible())
	{
		UILabel* label = m_alchemyEquipLayout->FindChildObjectByName<UILabel>("alchemyEnergyInallLabel");
		if(label)
		{
			unsigned int sp = UserData::GetSpriteEnergy();
			char spNum[20];
			sprintf(spNum,"%d",sp);
			label->setString(spNum);
		}
	}
	if(m_alchemyExchangeLayout && m_alchemyExchangeLayout->isVisible())
	{
		UILabel* label = m_alchemyExchangeLayout->FindChildObjectByName<UILabel>("alchemyExchangeEnergyLabel");
		if(label)
		{
			unsigned int sp = UserData::GetSpriteEnergy();
			char spNum[20];
			sprintf(spNum,"%d",sp);
			label->setString(spNum);
		}
	}
	
}

void AlchemyUILayer::setSpiritChipLabel()
{
	if(m_alchemyExchangeLayout && m_alchemyExchangeLayout->isVisible())
	{
		UILabel* label = m_alchemyExchangeLayout->FindChildObjectByName<UILabel>("alchemyExchangePieceLabel");
		if(label)
		{
			unsigned int sp = UserData::GetUserChip();
			char spNum[20];
			sprintf(spNum,"%d",sp);
			label->setString(spNum);
		}
	}
}

void AlchemyUILayer::onBroadcastMessage(BroadcastMessage* msg)
{
	switch(msg->message)
	{
	case GM_ATTR_SP_UPDATE:
		setStoneEnergyLabel();
		updateBottomSpLabel();
		break;
	case GM_ATTR_SP_CHIP_UPDATE:
		setSpiritChipLabel();
		updateBottomPieceLabel();
		break;
	case GM_ATTR_SP_DIAMOND_UPDATE:
		updateBottomDiamondLabel();
		break;
	case GM_ATTR_COIN_UPDATE:
		updateBottomCoinLabel();
		break;
	}
}

void AlchemyUILayer::showSpriteParticleEffect(CCNode* parent,unsigned int id,CCPoint pt)
{
	char particleName[30];
	sprintf(particleName,"particle_effect_spirit_%d",id);
	//if(ParticleManagerX::sharedManager()->load("particle/ccb/TestParticleSystems.ccbi"))
	//{
		CCNode* particle = ParticleManagerX::sharedManager()->getParticles(particleName);
		if(particle != NULL)
		{
			CCNode* child = parent->getChildByTag(100);
			if(child)
			{
				child->removeFromParentAndCleanup(true);
				child = NULL;
			}
			parent->addChild(particle,100,100);
			particle->setPosition(pt);
		}
	//}
}

void AlchemyUILayer::playTransEffect(UIButton* parentPt)
{
	if(parentPt && parentPt->getAnimationNode())
	{
		CCNode* particle = ParticleManagerX::sharedManager()->getParticles_uieffect("particle_effect_transformelite");
		if(particle != NULL)
		{
			parentPt->getAnimationNode()->addChild(particle);
			particle->setPosition(CCPointZero);
		}
	}
}

void AlchemyUILayer::onReceiveSpriteTrans()
{
	if(m_uiLayout && m_uiLayout->getCurrentNode() && m_uiLayout->getCurrentNode()->isVisible())
	{
		UIButton* bt = m_uiLayout->FindChildObjectByName<UIButton>("transformBt");
		if(bt)
		{
			playTransEffect(bt);
		}
	}
	if(m_alchemyEquipLayout && m_alchemyEquipLayout->getCurrentNode() && m_alchemyEquipLayout->getCurrentNode()->isVisible())
	{
		UIButton* bt = m_alchemyEquipLayout->FindChildObjectByName<UIButton>("transformBt");
		if(bt)
		{
			playTransEffect(bt);
		}
	}
	GameAudioManager::sharedManager()->playEffect(350009,false);
}

void AlchemyUILayer::setEnergyIconVisible(bool isVisible)
{
	if(m_alchemyEquipLayout)
	{
		UIPicture* pic = m_alchemyEquipLayout->FindChildObjectByName<UIPicture>("alchemyFrameDragInSoul1");
		if(pic)
		{
			pic->setVisible(isVisible);
		}
	}
}

void AlchemyUILayer::updateBottomDiamondLabel()
{
	if(m_uiLayout)
	{
		UILabel* label = m_uiLayout->FindChildObjectByName<UILabel>("bottomDiamondLable");
		if(label)
		{
			unsigned int diamond = UserData::GetDiamond();
			const char* str = MainMenuLayer::GetNumByFormat(diamond);
			if(str)
			{
				label->setString(str);
			}
		}
	}
}
void AlchemyUILayer::updateBottomCoinLabel()
{
	if(m_uiLayout)
	{
		UILabel* label = m_uiLayout->FindChildObjectByName<UILabel>("bottomCoinLable");
		if(label)
		{
			unsigned int coin = UserData::GetGold();
			const char* str = MainMenuLayer::GetNumByFormat(coin);
			if(str)
			{
				label->setString(str);
			}
		}
	}
}
void AlchemyUILayer::updateBottomPieceLabel()
{
	if(m_uiLayout)
	{
		UILabel* label = m_uiLayout->FindChildObjectByName<UILabel>("bottomPieceLable");
		if(label)
		{
			unsigned int coin = UserData::GetUserChip();
			const char* str = MainMenuLayer::GetNumByFormat(coin);
			if(str)
			{
				label->setString(str);
			}
		}
	}
}
void AlchemyUILayer::updateBottomSpLabel()
{
	if(m_uiLayout)
	{
		UILabel* label = m_uiLayout->FindChildObjectByName<UILabel>("bottomSoulLable");
		if(label)
		{
			unsigned int coin = UserData::GetSpriteEnergy();
			const char* str = MainMenuLayer::GetNumByFormat(coin);
			if(str)
			{
				label->setString(str);
			}
		}
	}
}