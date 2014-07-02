#include "OnlineNetworkManager.h"
#include "EquipmentUpgradeUILayer.h"
#include "MainMenuLayer.h"
#include "GameManager.h"
#include "ItemManager.h"
#include "AspriteManager.h"
#include "GameConfigFromLuaManager.h"
#include "cs_core.pb.h"
#include "Localization.h"
#include "UserData.h"
#include "GMessage.h"
#include "GameAudioManager.h"
#include "particle_manager.h"
static unsigned int m_coldTime;
static long long m_laststengthTime;

EquipmentUpgradeUILayer::EquipmentUpgradeUILayer()
{
	m_equipmentLayout = NULL;
	m_choosedEquipIndex = 0;
	m_equipLayoutIndex = true;
	m_upTimesBar = NULL;
	m_choosedEquipBt = NULL;
	m_choosedEquipmentPic = NULL;
}

EquipmentUpgradeUILayer::~EquipmentUpgradeUILayer()
{
	unschedule(schedule_selector(EquipmentUpgradeUILayer::updateColdTime));
	UIManager::sharedManager()->RemoveUILayout("equipmentUpgradeLayout");
	NotificationCenter::defaultCenter()->unregisterAllMsgObserver(this);
}

bool EquipmentUpgradeUILayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}

	UIManager *manager = UIManager::sharedManager();
	m_equipmentLayout = manager->CreateUILayoutFromFile("UIplist/equipmentUpgrade.plist", this, "equipmentUpgradeLayout");

	manager->RegisterMenuHandler("equipmentUpgradeLayout","EquipmentUpgradeUILayer::closeEquipUpgradeBt",
		menu_selector(EquipmentUpgradeUILayer::closeEquipUpgradeBt), this);
	manager->RegisterMenuHandler("equipmentUpgradeLayout","EquipmentUpgradeUILayer::chooseOneEquipmentBt",
		menu_selector(EquipmentUpgradeUILayer::chooseOneEquipmentBt), this);
	manager->RegisterMenuHandler("equipmentUpgradeLayout","EquipmentUpgradeUILayer::onClickHeroEquip",
		menu_selector(EquipmentUpgradeUILayer::onClickHeroEquip), this);
	manager->RegisterMenuHandler("equipmentUpgradeLayout","EquipmentUpgradeUILayer::onClickFairyEquip",
		menu_selector(EquipmentUpgradeUILayer::onClickFairyEquip), this);
	manager->RegisterMenuHandler("equipmentUpgradeLayout","EquipmentUpgradeUILayer::onClickStrength",
		menu_selector(EquipmentUpgradeUILayer::onClickStrength), this);
	
	m_equipmentHelmetPic = m_equipmentLayout->FindChildObjectByName<UIPicture>("equipUpgradeHelmetIcon");
	m_equipmentNecklacePic = m_equipmentLayout->FindChildObjectByName<UIPicture>("equipUpgradeNicklaceIcon");
	m_equipmentWeaponPic = m_equipmentLayout->FindChildObjectByName<UIPicture>("equipUpgradeWeaponIcon");
	m_equipmentArmorPic = m_equipmentLayout->FindChildObjectByName<UIPicture>("equipUpgradeArmorIcon");
	m_equipmentRingPic = m_equipmentLayout->FindChildObjectByName<UIPicture>("equipUpgradeRingIcon");
	m_equipmentShoePic = m_equipmentLayout->FindChildObjectByName<UIPicture>("equipUpgradeShoeIcon");
	m_choosedEquipmentPic = m_equipmentLayout->FindChildObjectByName<UIPicture>("equipUpgradechoosedIcon");
	m_heroEquipToggle = m_equipmentLayout->FindChildObjectByName<UIButtonToggle>("heroEquipButtonToggle");
	m_fairyEquipToggle = m_equipmentLayout->FindChildObjectByName<UIButtonToggle>("fairyEquipButtonToggle");
	m_levelUpCostLabel = m_equipmentLayout->FindChildObjectByName<UILabel>("equipUpgradeChoosedCostNumber");
	m_levelLabel = m_equipmentLayout->FindChildObjectByName<UILabel>("equipUpgradeChoosedLevel");
	m_coldTimeLabel = m_equipmentLayout->FindChildObjectByName<UILabel>("equipUpgradeCDText");
	showPlayerEquipment();
	if(m_heroEquipToggle)
	{
		m_heroEquipToggle->selected();
	}
	schedule(schedule_selector(EquipmentUpgradeUILayer::updateColdTime),1);

	m_upTimesBar = (CCSprite*)m_equipmentLayout->FindChildObjectByName<UIPicture>("equipUpgradeBarTime")->getCurrentNode();
	if(m_upTimesBar)
	{
		m_upTimesBar->setAnchorPoint(ccp(0,0.5f));
		CCPoint oldPos = m_upTimesBar->getPosition();
		float scale = UIManager::sharedManager()->getScaleFactor();
		m_upTimesBar->setPosition(ccp(oldPos.x-scale * m_upTimesBar->getContentSize().width/2,oldPos.y));
	}
	showLvUpRemainTimes();
	setDefaultSelectedEquip();
	updateBottomCoinLabel();
	updateBottomDiamondLabel();
	NotificationCenter::defaultCenter()->registerAllMsgObserver(this);
	return true;
}

void EquipmentUpgradeUILayer::closeEquipUpgradeBt(CCObject* sender)
{
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{
		mLayer->HideEquipmentUpgradeUI();
	}

	MainMenuLayer::RemoveOneLayer(this);
}

void EquipmentUpgradeUILayer::closeLayerCallBack(void)
{
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{
		mLayer->HideEquipmentUpgradeUI();
	}
}

void EquipmentUpgradeUILayer::showEquipLevel(unsigned int index,unsigned int level)
{
	if(m_equipmentLayout)
	{
		char lableName[30];
		sprintf(lableName,"equipUpgradeLevelLabel%d",index);
		UILabel* label = m_equipmentLayout->FindChildObjectByName<UILabel>(lableName);
		if(label)
		{
			char text[10];
			sprintf(text,"lv %d",level);
			label->setString(text);
		}
	}
}

void EquipmentUpgradeUILayer::showEquipName(unsigned int index,const char* name,const ccColor3B& color)
{
	if(m_equipmentLayout)
	{
		char lableName[30];
		sprintf(lableName,"equipUpgradeLabel%d",index);
		UILabel* label = m_equipmentLayout->FindChildObjectByName<UILabel>(lableName);
		if(label)
		{
			label->setString(name);
			label->setColor(color);
		}
	}
}

void EquipmentUpgradeUILayer::showSingleEquip(unsigned int pos,unsigned int index)
{
	BackPackItem* item = ItemManager::Get()->findItemByPos(pos);
	if(item)
	{
		ItemBase* info = item->getItemInfo();
		if(info)
		{
			if(item->isEmpty)
			{
				showEquipLevel(index,0);
				showEquipName(index,"");
				UIPicture* pic = getEquipmentPic(index);
				if(pic)
				{
					pic->setSprite(NULL);
				}
				return;
			}
			else
			{
				UIPicture* pic = getEquipmentPic(index);
				if(pic)
				{
					CCSprite* equipPic = getIconSpriteById(item->getItemId());
					if(equipPic)
					{	
						pic->setSprite(equipPic);
						showEquipLevel(index,item->itemLevel);
						ItemBase* itemInfo = item->getItemInfo();
						if(itemInfo)
						{		
							showEquipName(index,itemInfo->m_name,ItemManager::Get()->getLabelColorByQuality(info->m_quality));
							if(itemInfo->m_quality > 0)
							{
								CCSprite* framePic = getIconFrame(itemInfo->m_quality);
								if(framePic)
								{
									pic->addExtraPic(framePic);
								}
							}	
						}
					}
				}
			}
		}
		else
		{
			showEquipLevel(index,0);
			showEquipName(index,"");
			UIPicture* pic = getEquipmentPic(index);
			if(pic)
			{
				pic->setSprite(NULL);
			}
		}
	}
	else
	{
		showEquipLevel(index,0);
		showEquipName(index,"");
		UIPicture* pic = getEquipmentPic(index);
		if(pic)
		{
			pic->setSprite(NULL);
		}
	}
}

void EquipmentUpgradeUILayer::showPlayerEquipment()
{
	for(unsigned int i=1;i<= 6;i++)
	{
		showSingleEquip(kItemHeroEquip + i,i);
	}
}

void EquipmentUpgradeUILayer::showFairyEquipment()
{
	for(unsigned int i=1;i<= 6;i++)
	{
		showSingleEquip(kItemFairyEquip +i,i);
	}
}

CCSprite* EquipmentUpgradeUILayer::getIconFrame(unsigned int level)
{
	string picName = "";
	switch(level)
	{
	case 1:
		picName = "map_ui_system_icon_FRAME_FRAME_GREEN";
		break;
	case 2:
		picName = "map_ui_system_icon_FRAME_FRAME_BLUE";
		break;
	case 3:
		picName = "map_ui_system_icon_FRAME_FRAME_PURPLE";
		break;
	case 4:
		picName = "map_ui_system_icon_FRAME_FRAME_ORANGE";
		break;
	}
	if(picName != "")
	{
		ASprite *as = AspriteManager::getInstance()->getAsprite(KICON_BIN); 
		int idx = getResourceIDByName(picName.c_str());
		CCPoint pt;
		CCSprite * pic = as->getSpriteFromFrame_Middle( idx, 0, pt);
		if(pic != NULL)
		{
			return pic;
		}
	}
	return NULL;
}

CCSprite* EquipmentUpgradeUILayer::getIconSpriteById(unsigned int ItemId)
{
	ASprite *as = AspriteManager::getInstance()->getAsprite(KICON_BIN); 
	int idx = GameConfigFromLuaManager::Get()->getItemResourceId(ItemId);
	CCPoint pt;
	CCSprite * pic = as->getSpriteFromFrame_Middle( idx, 0, pt);
	return pic;
}

TXGUI::UIPicture* EquipmentUpgradeUILayer::getEquipmentPic(int index)
{
	UIPicture* pic;
	switch(index)
	{
	case 1:
		pic = m_equipmentHelmetPic;
		break;
	case 2:
		pic = m_equipmentNecklacePic;
		break;
	case 3:
		pic = m_equipmentWeaponPic;
		break;
	case 4:	
		pic = m_equipmentArmorPic;
		break;
	case 5:
		pic = m_equipmentRingPic;
		break;
	case 6:
		pic = m_equipmentShoePic;
		break;
	default:
		pic = NULL;
		break;
	}
	return pic;
}

TXGUI::UIButton* EquipmentUpgradeUILayer::getEquipmentButton(int index)
{
	if(m_equipmentLayout)
	{
		char btName[30];
		sprintf(btName,"equipUpgradeBt%d",index);
		UIButton* bt = m_equipmentLayout->FindChildObjectByName<UIButton>(btName);
		return bt;
	}
	return NULL;
}

void EquipmentUpgradeUILayer::chooseOneEquipmentBt(CCObject* sender)
{
	CCMenuItem* item = dynamic_cast<CCMenuItem*>(sender);
	if(item && item->getParent())
	{
		CCNode* parent = item->getParent();
		UIMenu* menu = dynamic_cast<UIMenu*>(parent);
		if(menu)
		{
			UIControlBase* control = menu->getControlNode();
			UIButton* button = dynamic_cast<UIButton*>(control);
			if(button)
			{
				unsigned int index = button->getButtonIndex();
				setChoosedEquipment(index);
			}
		}
	}
}

void EquipmentUpgradeUILayer::setChoosedEquipment(unsigned int index)
{
	if(m_choosedEquipIndex == index)
	{
		if(m_choosedEquipBt && m_choosedEquipBt->getMenuItemSprite())
		{
			m_choosedEquipBt->getMenuItemSprite()->selected();
		}
		return;
	}
	
	m_choosedEquipIndex = index;
	if(m_choosedEquipBt && m_choosedEquipBt->getMenuItemSprite())
	{
		m_choosedEquipBt->getMenuItemSprite()->unselected();
	}
	m_choosedEquipBt = getEquipmentButton(index);
	if(m_choosedEquipBt && m_choosedEquipBt->getMenuItemSprite())
	{
		m_choosedEquipBt->getMenuItemSprite()->selected();
	}

	

	if(m_choosedEquipmentPic)
	{
		unsigned int pos = index;
		if(m_equipLayoutIndex)
		{
			pos += kItemHeroEquip;
		}
		else
		{
			pos += kItemFairyEquip;
		}
		BackPackItem* item = ItemManager::Get()->findItemByPos(pos);
		if(item)
		{
			if(item->isEmpty)
			{
				m_choosedEquipmentPic->setSprite(NULL);
				showLevelUpCost(0);
				showCurrentLevel(0);
				showCurrentName("");
				showCurrentAttributeLabel("");
				showSecondAttributeLabel("");
				UILabel* label = m_equipmentLayout->FindChildObjectByName<UILabel>("equipUpgradeChoosedAddNextLevel");
				if(label)
				{
					label->setString("");
				}
				label = m_equipmentLayout->FindChildObjectByName<UILabel>("equipUpgradeChoosedAddNextLevel2");
				if(label)
				{
					label->setString("");
				}
				return;
			}
			if(item->m_attribution)
			{
				std::list<ITEMATTR*>::iterator it = item->m_attribution->begin();
				if(it != item->m_attribution->end())
				{
					ITEMATTR* attr = *it;
					if(attr)
					{
						showCurrentAttribute(attr->attr_key,attr->attr_basic_value,attr->attr_intensify_value);
					}
					if(++it != item->m_attribution->end())
					{
						attr = *it;
						showSecondAttribute(attr->attr_key,attr->attr_basic_value,attr->attr_intensify_value);
					}
					else
					{
						showSecondAttributeLabel("");
					}
				}
				
			}
			if(item->m_equipInfo)
			{
				std::list<EQUIPNEXTATTR>::iterator it = item->m_equipInfo->m_nextAttribution.begin();
				if(it != item->m_equipInfo->m_nextAttribution.end())
				{
					EQUIPNEXTATTR attr = *it;
					showNextLevelAttribution(attr.key,attr.value);
				}
				if(++it != item->m_equipInfo->m_nextAttribution.end())
				{
					EQUIPNEXTATTR attr = *it;
					showSecondNextLevelAttribution(attr.key,attr.value);
				}
				else
				{
					showSecondNextLevelAttributionLabel("");
				}
				showLevelUpCost(item->m_equipInfo->levelUpCost);
			}
			
			CCSprite* equipPic = getIconSpriteById(item->getItemId());
			if(equipPic)
			{	
				
				showCurrentLevel(item->itemLevel);

				m_choosedEquipmentPic->setSprite(equipPic);
				ItemBase* itemInfo = item->getItemInfo();
				if(itemInfo && itemInfo > 0)
				{
					showCurrentName(itemInfo->m_name,ItemManager::Get()->getLabelColorByQuality(itemInfo->m_quality));

					if(itemInfo->m_quality > 0)
					{
						CCSprite* framePic = getIconFrame(itemInfo->m_quality);
						if(framePic)
						{
							m_choosedEquipmentPic->addExtraPic(framePic);
						}
					}
					
				}
			}
		}
		
	}
}

unsigned int EquipmentUpgradeUILayer::GetUpgradeColdTime()
{
	return m_coldTime;
}

void EquipmentUpgradeUILayer::setUpgradeColdTime(unsigned int value)
{
	m_coldTime = value;
	m_laststengthTime = millisecondNow();
	showColdTime(m_coldTime);
}

void EquipmentUpgradeUILayer::onClickHeroEquip(CCObject* sender)
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
		showPlayerEquipment();
		unSelectChoosedEquip();
		setDefaultSelectedEquip();
	}
}

void EquipmentUpgradeUILayer::onClickFairyEquip(CCObject* sender)
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
		showFairyEquipment();
		unSelectChoosedEquip();
		setDefaultSelectedEquip();
	}
}

void EquipmentUpgradeUILayer::onClickStrength(CCObject* sender)
{
	if(checkLvUp())
	{
		unsigned int pos = m_choosedEquipIndex;
		if(m_equipLayoutIndex)
		{
			pos += kItemHeroEquip;
		}
		else
		{
			pos += kItemFairyEquip;
		}
		OnlineNetworkManager::sShareInstance()->sentEquipUpgradeStrength(pos);
	}
}

void EquipmentUpgradeUILayer::unSelectChoosedEquip()
{
	m_choosedEquipIndex = 0;
	if(m_choosedEquipmentPic)
	{
		m_choosedEquipmentPic->setSprite(NULL);
	}
	showCurrentLevel(0);
	showCurrentName("");
	showCurrentAttributeLabel("");
	showSecondAttributeLabel("");
	showLevelUpCost(0);
	UILabel* label = m_equipmentLayout->FindChildObjectByName<UILabel>("equipUpgradeChoosedAddNextLevel");
	if(label)
	{
		label->setString("");
	}
	label = m_equipmentLayout->FindChildObjectByName<UILabel>("equipUpgradeChoosedAddNextLevel2");
	if(label)
	{
		label->setString("");
	}
}

void EquipmentUpgradeUILayer::successToStrength(unsigned int pos,unsigned int coldTime)
{
	GameAudioManager::sharedManager()->playEffect(350006,false);
	m_coldTime = coldTime;
	m_laststengthTime = millisecondNow();
	BackPackItem* item = ItemManager::Get()->findItemByPos(pos);
	playUpgradeEffect();
	bool bHeroEquip = true;
	unsigned int index = pos;
	if(index >= kItemFairyEquip)
	{
		bHeroEquip = false; 
		index -= kItemFairyEquip;
	}
	else
	{
		index -= kItemHeroEquip;
	}

	if(m_equipLayoutIndex == bHeroEquip && m_choosedEquipIndex == index)
	{
		if(item)
		{
			showColdTime(m_coldTime);
			showCurrentLevel(item->itemLevel);

			showSingleEquip(pos,index);
			if(item->m_attribution)
			{
				std::list<ITEMATTR*>::iterator it = item->m_attribution->begin();
				if(it != item->m_attribution->end())
				{
					ITEMATTR* attr = *it;
					if(attr)
					{
						showCurrentAttribute(attr->attr_key,attr->attr_basic_value,attr->attr_intensify_value);
					}
					if(++it != item->m_attribution->end())
					{
						attr = *it;
						showSecondAttribute(attr->attr_key,attr->attr_basic_value,attr->attr_intensify_value);
					}
					else
					{
						showSecondAttributeLabel("");
					}
				}

			}
			if(item->m_equipInfo)
			{
				std::list<EQUIPNEXTATTR>::iterator it = item->m_equipInfo->m_nextAttribution.begin();
				if(it != item->m_equipInfo->m_nextAttribution.end())
				{
					EQUIPNEXTATTR attr = *it;
					showNextLevelAttribution(attr.key,attr.value);
				}
				if(++it != item->m_equipInfo->m_nextAttribution.end())
				{
					EQUIPNEXTATTR attr = *it;
					showSecondNextLevelAttribution(attr.key,attr.value);
				}
				else
				{
					showSecondNextLevelAttributionLabel("");
				}
				showLevelUpCost(item->m_equipInfo->levelUpCost);
			}
		}
		
	}
}

void EquipmentUpgradeUILayer::showLevelUpCost(unsigned int cost)
{
	if(m_levelUpCostLabel)
	{
		char costString[10];
		sprintf(costString,"%d",cost);
		m_levelUpCostLabel->setString(costString);
	}
}

void EquipmentUpgradeUILayer::showCurrentLevel(unsigned int level)
{
	if(m_levelLabel)
	{
		char levelString[10];
		sprintf(levelString,"lv %d",level);
		m_levelLabel->setString(levelString);
	}
}

void EquipmentUpgradeUILayer::showCurrentName(const char* name,const ccColor3B& color)
{
	if(m_equipmentLayout)
	{
		UILabel* label = m_equipmentLayout->FindChildObjectByName<UILabel>("equipUpgradeChoosedName");
		if(label)
		{
			label->setString(name);
			label->setColor(color);
		}
	}
}

void EquipmentUpgradeUILayer::showCurrentAttribute(unsigned int key,unsigned int basicValue,unsigned int strenghValue)
{
	unsigned int value = basicValue + strenghValue;
	const char* text = ItemManager::Get()->getAttributionText(key,value);
	if(text)
	{
		showCurrentAttributeLabel(text);
	}
}

void EquipmentUpgradeUILayer::showCurrentAttributeLabel(const char* text)
{
	if(m_equipmentLayout)
	{
		UILabel* label = m_equipmentLayout->FindChildObjectByName<UILabel>("equipUpgradeChoosedAddSkill");
		if(label)
		{
			label->setString(text);
		}
	}
}

void EquipmentUpgradeUILayer::showSecondAttribute(unsigned int key,unsigned int basicValue,unsigned int strenghValue)
{
	unsigned int value = basicValue + strenghValue;
	const char* text = ItemManager::Get()->getAttributionText(key,value);
	if(text)
	{
		showSecondAttributeLabel(text);
	}
}

void EquipmentUpgradeUILayer::showSecondAttributeLabel(const char* text)
{
	if(m_equipmentLayout)
	{
		UILabel* label = m_equipmentLayout->FindChildObjectByName<UILabel>("equipUpgradeChoosedAddSkill2");
		if(label)
		{
			label->setString(text);
		}
	}
}

void EquipmentUpgradeUILayer::showNextLevelAttribution(unsigned int key,unsigned int strenghValue)
{
	const char* text = ItemManager::Get()->getAttributionText(key,strenghValue);
	if(text)
	{
		if(m_equipmentLayout)
		{
			UILabel* label = m_equipmentLayout->FindChildObjectByName<UILabel>("equipUpgradeChoosedAddNextLevel");
			if(label)
			{
				char nextAttr[80];
				sprintf(nextAttr,"%s%s",Localizatioin::getLocalization("M_NEXTLEVEL"),text);
				label->setString(nextAttr);
			}
		}
	}
}

void EquipmentUpgradeUILayer::showSecondNextLevelAttribution(unsigned int key,unsigned int strenghValue)
{
	const char* text = ItemManager::Get()->getAttributionText(key,strenghValue);
	if(text)
	{
		if(m_equipmentLayout)
		{
			UILabel* label = m_equipmentLayout->FindChildObjectByName<UILabel>("equipUpgradeChoosedAddNextLevel2");
			if(label)
			{
				char nextAttr[80];
				sprintf(nextAttr,"%s%s",Localizatioin::getLocalization("M_NEXTLEVEL"),text);
				label->setString(nextAttr);
			}
		}
	}
}

void EquipmentUpgradeUILayer::showSecondNextLevelAttributionLabel(const char* text)
{
	if(m_equipmentLayout)
	{
		UILabel* label = m_equipmentLayout->FindChildObjectByName<UILabel>("equipUpgradeChoosedAddNextLevel2");
		if(label)
		{
			label->setString(text);
		}
	}
}

void EquipmentUpgradeUILayer::showColdTime(unsigned int time)
{
	if(m_coldTimeLabel)
	{
		char timeString[30];
		unsigned int hour = time / 3600;
		unsigned int min = (time - hour * 3600) / 60;
		unsigned int second = time % 60;
		if(hour > 0)
		{
			sprintf(timeString,"%02d : %02d : %02d",hour,min,second);
		}
		else 
		{
			sprintf(timeString,"%02d : %02d",min,second);
		}
		m_coldTimeLabel->setString(timeString);
	}
}

void EquipmentUpgradeUILayer::updateColdTime(float value)
{
	if(m_coldTime > 0)
	{
		long long currentTime = millisecondNow();
		long long deltaTime = (currentTime - m_laststengthTime)/1000;
		unsigned int time = (deltaTime > m_coldTime ) ?  0 : (m_coldTime - deltaTime);
		showColdTime(time);
	}
}

void EquipmentUpgradeUILayer::showLvUpRemainTimes()
{
	USERINFO userInfo = UserData::GetUserInfo();
	float percent = 1.0f;
	if(0 != userInfo.m_equipLvUpTotalTimes)
	{
		percent = (1.0f * userInfo.m_equipLvUsedTimes) / userInfo.m_equipLvUpTotalTimes;
	}
	if(m_upTimesBar)
	{
		float scale = UIManager::sharedManager()->getScaleFactor();
		m_upTimesBar->setScaleX(percent * scale);
		m_upTimesBar->setScaleY(scale);
	}
}
bool EquipmentUpgradeUILayer::checkLvUp()
{
	USERINFO info = UserData::GetUserInfo();
	if(info.m_equipLvUpTotalTimes - info.m_equipLvUsedTimes > 0)
	{
		return true;
	}
	return false;
}

void EquipmentUpgradeUILayer::onBroadcastMessage(BroadcastMessage* msg)
{
	switch(msg->message)
	{
	case GM_ATTR_EQUIP_LVUP_UESED_TIMES:
	case GM_ATTR_EQUIP_LVUP_MAX_TIMES:
		showLvUpRemainTimes();
		break;
	case GM_ATTR_SP_DIAMOND_UPDATE:
		updateBottomDiamondLabel();
		break;
	case GM_ATTR_COIN_UPDATE:
		updateBottomCoinLabel();
		break;
	}
}

void EquipmentUpgradeUILayer::setDefaultSelectedEquip()
{
	unsigned int pos;
	if(m_equipLayoutIndex)
	{
		pos = kItemHeroEquip;
	}
	else
	{
		pos = kItemFairyEquip;
	}
	for(unsigned int i =0;i < 6;i++)
	{
		BackPackItem* item = ItemManager::Get()->findItemByPos(pos+i+1);
		if(item && !item->isEmpty && !item->isLocked)
		{
			setChoosedEquipment(i);
			break;
		}
	}

}

void EquipmentUpgradeUILayer::updateBottomDiamondLabel()
{
	if(m_equipmentLayout)
	{
		UILabel* label = m_equipmentLayout->FindChildObjectByName<UILabel>("bottomDiamondLable");
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
void EquipmentUpgradeUILayer::updateBottomCoinLabel()
{
	if(m_equipmentLayout)
	{
		UILabel* label = m_equipmentLayout->FindChildObjectByName<UILabel>("bottomCoinLable");
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

void EquipmentUpgradeUILayer::playUpgradeEffect()
{
	if(m_choosedEquipmentPic && m_choosedEquipmentPic->getCurrentNode())
	{
		CCNode* particle = ParticleManagerX::sharedManager()->getParticles_uieffect("particle_effect_upgradesuccess");
		if(particle != NULL)
		{
			CCNode* child = m_choosedEquipmentPic->getCurrentNode()->getChildByTag(100);
			if(child)
			{
				child->removeFromParentAndCleanup(true);
				child = NULL;
			}
			m_choosedEquipmentPic->getCurrentNode()->addChild(particle,100,100);
			particle->setPosition(ccp(m_choosedEquipmentPic->getCurrentNode()->getContentSize().width * 0.5,m_choosedEquipmentPic->getCurrentNode()->getContentSize().height * 0.5));
		}
	}
}

long long millisecondNow()
{ 
	struct cc_timeval now; 
	CCTime::gettimeofdayCocos2d(&now, NULL);
    long long vTime = now.tv_sec;
    vTime  = vTime * 1000;
    vTime = vTime + now.tv_usec / 1000;
	return vTime;
} 