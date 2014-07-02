#include "OnlineNetworkManager.h"
#include "ItemDragLayer.h"
#include "UIDefine.h"
#include "ItemManager.h"
#include "TXGUIHeader.h"
#include "MessageBoxLayer.h"
#include "Localization.h"
#include "GameConfigFromLuaManager.h"
using namespace TXGUI;

ItemDragLayer::ItemDragLayer()
	:m_pDragUILayer(NULL),
	m_currentDeletePos(-1)
{

}

ItemDragLayer::~ItemDragLayer()
{
}

bool ItemDragLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}

	m_pDragUILayer = UIDragLayer::create();
	this->addChild(m_pDragUILayer);
	m_pDragUILayer->setDragDealTarget(this,dragMove_selector(ItemDragLayer::dealWithDragAction),
		dragDelete_selector(ItemDragLayer::dragEndWithoutUI));
	return true;
}

void ItemDragLayer::registerDragReceiver(DragReceiver* receiver)
{
	if(!receiver)
	{
		return;
	}

	if(m_pDragUILayer)
	{
		m_pDragUILayer->registerDragReceiver(receiver);
	}
}

void ItemDragLayer::unregisterDragReceiver(DragReceiver* receiver)
{
	if(!receiver)
	{
		return;
	}

	if(m_pDragUILayer)
	{
		m_pDragUILayer->unregisterDragReceiver(receiver);
	}
}

void ItemDragLayer::startDrag(DragReceiver* handler,CCTouch* pTouch,CCEvent *pEvent)
{
	if(m_pDragUILayer)
	{
		m_pDragUILayer->startDrag(handler,pTouch,pEvent);
	}
}

void ItemDragLayer::dealWithDragAction(DragReceiver* from,DragReceiver* to)
{
	if(!from || !to)
	{
		return;
	}

	if(from == to)
	{
		return;
	}

	if(to->GetDragItemType() == EUIBg || to->GetDragItemType() == EUnKowned)
	{
		return;
	}

	int from_pos = getReceiverIndex(from->GetDragItemType(),from->GetHandlerPosition());
	int to_pos = getReceiverIndex(to->GetDragItemType(),to->GetHandlerPosition());

	//for test
	if(from->GetDragItemType() == EAlchemyBag)
	{
		if(to->GetDragItemType() == EAlchemyBag)
		{
			//ItemManager::Get()->exchangeItemPos(from_pos,to_pos);
			OnlineNetworkManager::sShareInstance()->sendBackPackMove(from_pos,to_pos);
			return;
		}
		else if(to->GetDragItemType() == EALchemyToStorage)
		{
			CCLog("alchemy stone drag into storage");
			OnlineNetworkManager::sShareInstance()->sendSoulStoneToStorage(from_pos);
			return;
		}
	}

	//for test
	if(from->GetDragItemType() == EAlchemyStorage && to->GetDragItemType() == EAlchemyStorage)
	{
		//ItemManager::Get()->exchangeItemPos(from_pos,to_pos);
		OnlineNetworkManager::sShareInstance()->sendBackPackMove(from_pos,to_pos);
		ItemManager::Get()->reqAlchemyUpgradeUnselected();
		return;
	}

	if(from->GetDragItemType() == EAlchemyStorage || from->GetDragItemType() == EAlchemyEquip)
	{
		if(to->GetDragItemType() == EAlchemyUpgrade)
		{
			ItemManager::Get()->reqAlchemyUpgradeSelected(from_pos);
			return;
		}
		else if(to->GetDragItemType() == EAlchemyButton)
		{
			CCLog("alchemy stone drag into energy");
			OnlineNetworkManager::sShareInstance()->sendTranStoneToEnergy(false,from_pos);
			return;
		}
		else
		{
			ItemManager::Get()->reqAlchemyUpgradeUnselected();
			//ItemManager::Get()->exchangeItemPos(from_pos,to_pos);
			OnlineNetworkManager::sShareInstance()->sendBackPackMove(from_pos,to_pos);
			return;
		}
	}

	if(from->GetDragItemType() == ESkillEquipItem && to->GetDragItemType() == ESlotItem)
	{
		CCLOG("from pos %d ",from_pos);
		CCLOG("to pos %d ",to_pos);
		GameConfigFromLuaManager::Get()->ListItemDragToSLotItem(from_pos,to_pos);
	}

	if(from->GetDragItemType() == ESlotItem && to->GetDragItemType() == ESlotItem)
	{
		CCLOG("from pos %d ",from_pos);
		CCLOG("to pos %d ",to_pos);
		GameConfigFromLuaManager::Get()->SlotItemToSelf(from_pos,to_pos);
	}

	if(from_pos != -1 && to_pos != -1)
	{
		OnlineNetworkManager::sShareInstance()->sendBackPackMove(from_pos,to_pos);
	}

}

void ItemDragLayer::onClickConfigDeleteItem(CCObject* sender)
{
	BackPackItem* item = ItemManager::Get()->findItemByPos(m_currentDeletePos);
	if(item)
	{
		OnlineNetworkManager::sShareInstance()->sendBackPackRemoveItem(m_currentDeletePos,item->getItemId());
	}
	m_currentDeletePos = -1;
}

void ItemDragLayer::onClickCancellDeleteItem(CCObject* sender)
{
	m_currentDeletePos = -1;
}

int ItemDragLayer::getReceiverIndex(DragHandlerType type, unsigned int pos)
{
	int index = -1;
	switch(type)
	{
	case EBackPackItem:
	case ESkillEquipItem:
	case ESlotItem:
		index = pos;
		break;
	case EStorageItem:
		index = pos + kItemStorage;
		break;
	case EEquipmentItem:
		index = pos + kItemHeroEquip;
		break;
	case EAlchemyBag:
		index = pos + kAlchemyBag;
		break;
	case EAlchemyStorage:
		index = pos + kAlchemyStorage;
		break;
	case EAlchemyEquip:
		if(ItemManager::Get()->getCurrentAlchemyIndex())
		{
			index = pos + kAlchemyHeroEquip;
		}
		else
		{
			index = pos + kAlchemyFairyEquip;
		}
		break;
	default:
		break;
	}
	return index;
}

void ItemDragLayer::dragEndWithoutUI(DragReceiver* from)
{
	if(!from)
	{
		return;
	}

	int pos = -1;
	if(from->GetDragItemType() == EBackPackItem)
	{
		pos = from->GetHandlerPosition();
	}
	else if(from->GetDragItemType() == EStorageItem)
	{
		pos = from->GetHandlerPosition() + kItemStorage;
	}

	if(m_currentDeletePos == -1)
	{
		BackPackItem* item = ItemManager::Get()->findItemByPos(pos);
		if(item)
		{
			const char* msg = Localizatioin::getLocalization("M_CONFIRM_DISCARD");
			MessageBox::Show(msg,this,menu_selector(ItemDragLayer::onClickConfigDeleteItem),menu_selector(ItemDragLayer::onClickCancellDeleteItem));	
			m_currentDeletePos = pos;
		}
	}
	
}