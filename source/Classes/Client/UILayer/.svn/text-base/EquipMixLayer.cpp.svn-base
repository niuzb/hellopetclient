#include "OnlineNetworkManager.h"
#include "EquipMixLayer.h"
#include "ItemManager.h"
#include "AspriteManager.h"
#include "ASprite.h"
#include "GameConfigFromLuaManager.h"
#include "MainMenuLayer.h"
#include "Localization.h"
#include "particle_manager.h"
EquipMixLayer::EquipMixLayer()
	:m_uiLayout(NULL),
	m_itemIndex(0),
	m_itemPos(0),
	b_isMaterialEnough(false),
	b_successCompose(false)
{

}

EquipMixLayer::~EquipMixLayer()
{
	UIManager::sharedManager()->RemoveUILayout("equipmentMixLayout");
}

bool EquipMixLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}

	m_uiLayout = UIManager::sharedManager()->CreateUILayoutFromFile("UIplist/equipmentMix.plist", this, "equipmentMixLayout");

	UIManager::sharedManager()->RegisterMenuHandler("equipmentMixLayout","EquipMixLayer::onClickClosed",
		menu_selector(EquipMixLayer::onClickClosed), this);
	UIManager::sharedManager()->RegisterMenuHandler("equipmentMixLayout","EquipMixLayer::onComposeClickd",
		menu_selector(EquipMixLayer::onComposeClickd), this);

	return true;
}

void EquipMixLayer::ShowMaterials(ExchangeItem* item,unsigned int pos)
{
	if(item)
	{
		m_itemIndex = item->m_exchangeId;
		m_itemPos = pos;
		std::list<pair<unsigned int ,unsigned int> >::iterator it = item->m_toItems->begin();
		if(it != item->m_toItems->end())
		{
			unsigned int equip = (*it).first;
			showMixedEquipIcon(equip);
			ItemBase* info = ItemManager::Get()->getItemInfoById(equip);
			if(info)
			{
				setMatarialLabel(info->m_name,"equipMixEquipNameLable",ItemManager::Get()->getLabelColorByQuality(info->m_quality));
			}
			CC_SAFE_DELETE(info);
		}

		int i =1;
		b_isMaterialEnough = true;
		for(std::list<pair<unsigned int ,unsigned int> >::iterator iter = item->m_fromItems->begin();
			iter != item->m_fromItems->end();iter++)
		{
			unsigned int matarialId = (*iter).first;
			unsigned int ownerNum = ItemManager::Get()->getItemNumberById(matarialId);
			if(ownerNum >= (*iter).second)
			{
				ownerNum = (*iter).second;
			}
			else
			{
				b_isMaterialEnough &= false;
			}
			showMatarial(matarialId,ownerNum,(*iter).second,i++);
		}
	}
	b_successCompose = false;
}

void EquipMixLayer::showMixedEquipIcon(unsigned int itemId)
{
	setMatarailIcon(itemId,"mixxedEquipIcon");
}

void EquipMixLayer::showMatarial(unsigned int itemId,unsigned int ownerNum,unsigned int requiredNum,int index)
{
	setMatarailIcon(itemId,getMatarialPictureName(index));
	ItemBase* info = ItemManager::Get()->getItemInfoById(itemId);
	if(info)
	{
		setMatarialLabel(info->m_name,getMatarialLabelName(index),ItemManager::Get()->getLabelColorByQuality(info->m_quality));
		char numStr[10];
		sprintf(numStr,"%d/%d",ownerNum,requiredNum);
		if(ownerNum >= requiredNum)
		{
			setMatarialLabel(numStr,getMatarialNumberLabelName(index),ccGREEN);
		}
		else
		{
			setMatarialLabel(numStr,getMatarialNumberLabelName(index),ccRED);
		}
		
		CC_SAFE_DELETE(info);
	}
	
}

const char* EquipMixLayer::getMatarialLabelName(int index)
{
	const char* name;
	switch(index)
	{
	case 1:
		name = "equipMixMaterialOneName";
		break;
	case 2:
		name = "equipMixMaterialTwoName";
		break;
	case 3:
		name = "equipMixMaterialThreeName";
		break;
	case 4:
		name = "equipMixMaterialFourName";
		break;
	case 5:
		name = "equipMixMaterialFiveName";
		break;
	default:
		name = "";
		break;
	}
	return name;
}

const char* EquipMixLayer::getMatarialNumberLabelName(int index)
{
	const char* name;
	switch(index)
	{
	case 1:
		name = "equipMixMaterialOneNo";
		break;
	case 2:
		name = "equipMixMaterialTwoNo";
		break;
	case 3:
		name = "equipMixMaterialThreeNo";
		break;
	case 4:
		name = "equipMixMaterialFourNo";
		break;
	case 5:
		name = "equipMixMaterialFiveNo";
		break;
	default:
		name = "";
		break;
	}
	return name;
}

const char* EquipMixLayer::getMatarialPictureName(int index)
{
	const char* name;
	switch(index)
	{
	case 1:
		name = "mixEquipMaterial1Icon";
		break;
	case 2:
		name = "mixEquipMaterial2Icon";
		break;
	case 3:
		name = "mixEquipMaterial3Icon";
		break;
	case 4:
		name = "mixEquipMaterial4Icon";
		break;
	case 5:
		name = "mixEquipMaterial5Icon";
		break;
	default:
		name = "";
		break;
	}
	return name;
}

void EquipMixLayer::setMatarailIcon(unsigned int itemId,const char* name)
{
	if(m_uiLayout)
	{
		UIPicture* pic = m_uiLayout->FindChildObjectByName<UIPicture>(name);
		if(pic)
		{
			CCSprite* icon = getIconSpriteById(itemId);
			if(icon)
			{
				pic->setSprite(icon);
				ItemBase* itemInfo = ItemManager::Get()->getItemInfoById(itemId);
				if(itemInfo && itemInfo > 0)
				{
					CCSprite* framePic = getIconFrame(itemInfo->m_quality);
					if(framePic)
					{
						pic->addExtraPic(framePic);
					}
				}
				CC_SAFE_DELETE(itemInfo);
			}
		}
	}
}

void EquipMixLayer::setMatarialLabel(const char* text, const char* labelName,const ccColor3B& color)
{
	if(m_uiLayout)
	{
		UILabel* label = m_uiLayout->FindChildObjectByName<UILabel>(labelName);
		if(label)
		{
			label->setString(text);
			label->setColor(color);
		}
	}
}

CCSprite* EquipMixLayer::getIconSpriteById(unsigned int ItemId)
{
	ASprite *as = AspriteManager::getInstance()->getAsprite(KICON_BIN); 
	int idx = GameConfigFromLuaManager::Get()->getItemResourceId(ItemId);
	CCPoint pt;
	CCSprite * pic = as->getSpriteFromFrame_Middle( idx, 0, pt);
	return pic;
}

void EquipMixLayer::onClickClosed(CCObject* sender)
{
	MainMenuLayer::RemoveOneLayer(this);
	HideEquipMixLayer();
}

void EquipMixLayer::onReceivedComposeSuccess()
{
	b_successCompose = true;
	UIPicture* pic = m_uiLayout->FindChildObjectByName<UIPicture>("mixxedEquipIcon");
	if(pic && pic->getCurrentNode())
	{
		CCNode* particle = ParticleManagerX::sharedManager()->getParticles_uieffect("particle_effect_mixsuccess");
		if(particle != NULL)
		{
			CCNode* child = pic->getCurrentNode()->getChildByTag(100);
			if(child)
			{
				child->removeFromParentAndCleanup(true);
				child = NULL;
			}
			pic->getCurrentNode()->addChild(particle,100,100);
			particle->setPosition(ccp(pic->getCurrentNode()->getContentSize().width * 0.5,pic->getCurrentNode()->getContentSize().height * 0.5));
		}
	}
	scheduleOnce(schedule_selector(EquipMixLayer::readyToClose),2.0f);
}

void EquipMixLayer::readyToClose(float dt)
{
	onClickClosed(NULL);
	ItemManager::Get()->openBackPack();
}

CCSprite* EquipMixLayer::getIconFrame(unsigned int level)
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

void EquipMixLayer::onComposeClickd(CCObject* sender)
{
	if(b_successCompose)
	{
		return;
	}
	if(b_isMaterialEnough)
	{
		OnlineNetworkManager::sShareInstance()->sendEquipComposeReq(m_itemIndex,m_itemPos);
	}
	else
	{
		const char* msg = Localizatioin::getLocalization("M_NOT_ENOUGH_MATERIAL");
		ShowMessage(msg);
	}
}

void EquipMixLayer::closeLayerCallBack(void)
{
	HideEquipMixLayer();
}