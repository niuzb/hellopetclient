#include "ItemManager.h"
#include "BackPackLayer.h"
#include "AlchemyUILayer.h"
#include "MainMenuLayer.h"
#include "GameConfigFromLuaManager.h"
#include "cs_core.pb.h"
#include "Localization.h"
#include "TipMgr.h"
#include "UserData.h"
#include "GMessage.h"
#include "LuaTinkerManager.h"
ItemManager::ItemManager()
	: m_backPackList(NULL),
	m_storageList(NULL),
	m_equipmentList(NULL),
	m_exchangeItemList(NULL),
	m_maxPackPos(60),
	m_defaultPackPos(15),
	m_maxStoragePos(60),
	m_defaultStoragePos(15),
	b_isLoadExchangeItems(false),
	m_alchemyBagList(NULL),
	m_alchemyStorageList(NULL),
	m_alchemyEquipList(NULL)
{
	m_defaultAlchemyBagPos = AlCHEMYBAGCAPACITY;
	m_defaultAlchemyStoragePos = 10;
	m_alchemyFairyEquipList = NULL;
	m_searchNpcCostMap = NULL;
	m_fairyEquipmentList = NULL;
	m_gemStoneList = NULL;
	m_unlockPackPos = 0;
	m_unlockStoragePos = 0;
	m_unlockAlchemyBagPos = 0;
	m_unlockAlchemyStroragePos = 0;
	m_surplusGemRecastNum = 0;
}

ItemManager::~ItemManager()
{
	if(m_backPackList)
	{
		for(BACKPACK_VECTOR::iterator iter = m_backPackList->begin();
			iter != m_backPackList->end();iter++)
		{
			BackPackItem *item = (*iter).second;
			CC_SAFE_DELETE(item);
		}
		m_backPackList->clear();
		CC_SAFE_DELETE(m_backPackList);
	}
	if(m_storageList)
	{
		for(BACKPACK_VECTOR::iterator iter = m_storageList->begin();
			iter != m_storageList->end();iter++)
		{
			BackPackItem *item = (*iter).second;
			CC_SAFE_DELETE(item);
		}
		m_storageList->clear();
		CC_SAFE_DELETE(m_storageList);
	}
	if(m_equipmentList)
	{
		for(BACKPACK_VECTOR::iterator iter = m_equipmentList->begin();
			iter != m_equipmentList->end();iter++)
		{
			BackPackItem *item = (*iter).second;
			CC_SAFE_DELETE(item);
		}
		m_equipmentList->clear();
		CC_SAFE_DELETE(m_equipmentList);
	}
	if(m_fairyEquipmentList)
	{
		for(BACKPACK_VECTOR::iterator iter = m_fairyEquipmentList->begin();
			iter != m_fairyEquipmentList->end();++iter)
		{
			BackPackItem *item = (*iter).second;
			CC_SAFE_DELETE(item);
		}
		m_fairyEquipmentList->clear();
		CC_SAFE_DELETE(m_fairyEquipmentList);
	}
	if(m_alchemyBagList)
	{
		for(BACKPACK_VECTOR::iterator iter = m_alchemyBagList->begin();
			iter != m_alchemyBagList->end();iter++)
		{
			BackPackItem *item = (*iter).second;
			CC_SAFE_DELETE(item);
		}
		m_alchemyBagList->clear();
		CC_SAFE_DELETE(m_alchemyBagList);
	}
	if(m_alchemyStorageList)
	{
		for(BACKPACK_VECTOR::iterator iter = m_alchemyStorageList->begin();
			iter != m_alchemyStorageList->end();iter++)
		{
			BackPackItem *item = (*iter).second;
			CC_SAFE_DELETE(item);
		}
		m_alchemyStorageList->clear();
		CC_SAFE_DELETE(m_alchemyStorageList);
	}
	if(m_alchemyEquipList)
	{
		for(BACKPACK_VECTOR::iterator iter = m_alchemyEquipList->begin();
			iter != m_alchemyEquipList->end();iter++)
		{
			BackPackItem *item = (*iter).second;
			CC_SAFE_DELETE(item);
		}
		m_alchemyEquipList->clear();
		CC_SAFE_DELETE(m_alchemyEquipList);
	}
	if(m_alchemyFairyEquipList)
	{
		for(BACKPACK_VECTOR::iterator iter = m_alchemyFairyEquipList->begin();
			iter != m_alchemyFairyEquipList->end();iter++)
		{
			BackPackItem *item = (*iter).second;
			CC_SAFE_DELETE(item);
		}
		m_alchemyFairyEquipList->clear();
		CC_SAFE_DELETE(m_alchemyFairyEquipList);
	}
	if(m_gemStoneList)
	{
		for(BACKPACK_VECTOR::iterator iter = m_gemStoneList->begin();
			iter != m_gemStoneList->end();iter++)
		{
			BackPackItem *item = (*iter).second;
			CC_SAFE_DELETE(item);
		}
		m_gemStoneList->clear();
		CC_SAFE_DELETE(m_gemStoneList);
	}
	
	if(m_exchangeItemList)
	{
		for(std::list<ExchangeItem*>::iterator iter = m_exchangeItemList->begin();
			iter != m_exchangeItemList->end();iter++)
		{
			ExchangeItem *item = *iter;
			CC_SAFE_DELETE(item);
		}
		m_exchangeItemList->clear();
		CC_SAFE_DELETE(m_exchangeItemList);
	}

	if(m_equipmentList)
	{
		BACKPACK_VECTOR::iterator iter = m_equipmentList->begin();
		while(iter != m_equipmentList->end())
		{
			BackPackItem* item = (*iter).second;
			delete item;
			iter++;
		}

		m_equipmentList->clear();
		delete m_equipmentList;
		m_equipmentList = NULL;
	}
	
	if(m_searchNpcCostMap)
	{
		m_searchNpcCostMap->clear();
		delete m_searchNpcCostMap;
		m_searchNpcCostMap = NULL;
	}
}

void ItemManager::init()
{
	if(!m_backPackList)
	{
		m_backPackList = new BACKPACK_VECTOR();
		for(unsigned int i=1;i<= m_maxPackPos;i++)
		{
			BackPackItem* item = new BackPackItem(0);
			if(i <= m_defaultPackPos)
			{
				item->isLocked = false;
			}
			else
			{
				item->isLocked = true;
			}
			item->position = i;
			item->isEmpty = true;

			m_backPackList->insert(std::make_pair(i,item));
		}
	}
	if(!m_storageList)
	{
		m_storageList = new BACKPACK_VECTOR();
		for(unsigned int i=1;i<= m_maxStoragePos;i++)
		{
			BackPackItem* item = new BackPackItem(1);
			if(i <= m_defaultPackPos)
			{
				item->isLocked = false;
			}
			else
			{
				item->isLocked = true;
			}
			item->position = i;
			item->isEmpty = true;

			m_storageList->insert(std::make_pair(i,item));
		}
	}

	if(!m_equipmentList)
	{
		m_equipmentList = new BACKPACK_VECTOR();
		for(unsigned int i=1;i<= 6;i++)
		{
			BackPackItem* item = new BackPackItem(2);

			item->isLocked = false;
			item->position = i;
			item->isEmpty = true;
			m_equipmentList->insert(std::make_pair(i,item));
		}
	}
	if(!m_fairyEquipmentList)
	{
		m_fairyEquipmentList = new BACKPACK_VECTOR();
		for(unsigned int i=1;i<=6;i++)
		{
			BackPackItem* item = new BackPackItem(6);
			item->isLocked = false;
			item->position = i;
			item->isEmpty = true;
			m_fairyEquipmentList->insert(std::make_pair(i,item));
		}
	}

	if(!m_alchemyBagList)
	{
		m_alchemyBagList = new BACKPACK_VECTOR();
		for(unsigned int i=1;i<= AlCHEMYBAGCAPACITY;i++)
		{
			BackPackItem* item = new BackPackItem(3);
			if(i <= m_defaultPackPos)
			{
				item->isLocked = false;
			}
			else
			{
				item->isLocked = true;
			}
			item->position = i;
			item->isEmpty = true;

			m_alchemyBagList->insert(std::make_pair(i,item));
		}
	}

	if(!m_alchemyStorageList)
	{
		m_alchemyStorageList = new BACKPACK_VECTOR();
		for(unsigned int i=1;i<= AlCHEMYSTORAGECAPACITY;i++)
		{
			BackPackItem* item = new BackPackItem(4);
			if(i <= m_defaultPackPos)
			{
				item->isLocked = false;
			}
			else
			{
				item->isLocked = true;
			}
			item->position = i;
			item->isEmpty = true;

			m_alchemyStorageList->insert(std::make_pair(i,item));
		}
	}
	
	if(!m_alchemyEquipList)
	{
		m_alchemyEquipList = new BACKPACK_VECTOR();
		for(unsigned int i=1;i<= 8;i++)
		{
			BackPackItem* item = new BackPackItem(5);

			item->isLocked = false;
			item->position = i;
			item->isEmpty = true;
			m_alchemyEquipList->insert(std::make_pair(i,item));
		}
	}

	if(!m_alchemyFairyEquipList)
	{
		m_alchemyFairyEquipList = new BACKPACK_VECTOR();
		for(unsigned int i=1;i<= 8;i++)
		{
			BackPackItem* item = new BackPackItem(5);

			item->isLocked = false;
			item->position = i;
			item->isEmpty = true;
			m_alchemyFairyEquipList->insert(std::make_pair(i,item));
		}
	}

	if(!m_gemStoneList)
	{
		m_gemStoneList = new BACKPACK_VECTOR();
		for(unsigned int i=1;i<= 10;i++)
		{
			BackPackItem* item = new BackPackItem(5);

			item->isLocked = false;
			item->position = i;
			item->isEmpty = true;
			m_gemStoneList->insert(std::make_pair(i,item));
		}
	}

	
	m_exchangeItemList = new std::list<ExchangeItem*>();

	//// for test
	//if(m_alchemyBagList)
	//{
	//	for(unsigned int i=0;i< 5;i++)
	//	{
	//		BackPackItem* item = findItemByPos(kAlchemyBag + i);
	//		item->setItemId(430001 + i);
	//		item->isEmpty = false;
	//		item->packType = 3;
	//	}
	//}
	//// for test
	//if(m_alchemyStorageList)
	//{
	//	for(unsigned int i=0;i< 5;i++)
	//	{
	//		BackPackItem* item = findItemByPos(kAlchemyStorage+i);
	//		item->setItemId(430001 + i);
	//		item->isEmpty = false;
	//		item->packType = 4;
	//	}
	//}
}

BackPackItem* ItemManager::findItemByPos(unsigned int pos)
{
	unsigned int realPos = pos;
	if(realPos >= kItemGemStone)
	{
		realPos = realPos - kItemGemStone; 
		if(m_gemStoneList)
		{
			BACKPACK_VECTOR::iterator iter = m_gemStoneList->find(realPos);
			if(iter != m_gemStoneList->end())
			{
				BackPackItem* item = (*iter).second;
				return item;
			}
		}
		return NULL;
	}
	else if(realPos >= kAlchemyFairyEquip && realPos < kFairyStartId)
	{
		realPos = realPos - kAlchemyFairyEquip; 
		if(m_alchemyEquipList)
		{
			BACKPACK_VECTOR::iterator iter = m_alchemyFairyEquipList->find(realPos);
			if(iter != m_alchemyFairyEquipList->end())
			{
				BackPackItem* item = (*iter).second;
				return item;
			}
		}
		return NULL;
	}
	else if(realPos >= kAlchemyHeroEquip)
	{
		realPos = realPos - kAlchemyHeroEquip; 
		if(m_alchemyEquipList)
		{
			BACKPACK_VECTOR::iterator iter = m_alchemyEquipList->find(realPos);
			if(iter != m_alchemyEquipList->end())
			{
				BackPackItem* item = (*iter).second;
				return item;
			}
		}
		return NULL;
	}
	else if(realPos >= kAlchemyStorage)
	{
		realPos = realPos - kAlchemyStorage; 
		if(m_alchemyStorageList)
		{
			BACKPACK_VECTOR::iterator iter = m_alchemyStorageList->find(realPos);
			if(iter != m_alchemyStorageList->end())
			{
				BackPackItem* item = (*iter).second;
				return item;
			}
		}
		return NULL;
	}
	else if(realPos >= kAlchemyBag)
	{
		realPos = realPos - kAlchemyBag; 
		if(m_alchemyBagList)
		{
			BACKPACK_VECTOR::iterator iter = m_alchemyBagList->find(realPos);
			if(iter != m_alchemyBagList->end())
			{
				BackPackItem* item = (*iter).second;
				return item;
			}
		}
		return NULL;
	}
	else if(realPos >= kItemFairyEquip)
	{
		realPos = realPos - kItemFairyEquip; 
		if(m_fairyEquipmentList)
		{
			BACKPACK_VECTOR::iterator iter = m_fairyEquipmentList->find(realPos);
			if(iter != m_fairyEquipmentList->end())
			{
				BackPackItem* item = (*iter).second;
				return item;
			}
		}
		return NULL;
	}
	else if(realPos >= kItemHeroEquip)
	{
		realPos = realPos - kItemHeroEquip; 
		if(m_equipmentList)
		{
			BACKPACK_VECTOR::iterator iter = m_equipmentList->find(realPos);
			if(iter != m_equipmentList->end())
			{
				BackPackItem* item = (*iter).second;
				return item;
			}
		}
		return NULL;
	}
	else if(realPos >= kItemStorage)
	{
		realPos = realPos - kItemStorage; 
		if(m_storageList)
		{
			BACKPACK_VECTOR::iterator iter = m_storageList->find(realPos);
			if(iter != m_storageList->end())
			{
				BackPackItem* item = (*iter).second;
				return item;
			}
		}
		return NULL;
	}
	else
	{
		if(m_backPackList)
		{
			BACKPACK_VECTOR::iterator iter = m_backPackList->find(realPos);
			if(iter != m_backPackList->end())
			{
				BackPackItem* item = (*iter).second;
				return item;
			}
		}
		return NULL;
	}
}

void ItemManager::removeItem(unsigned int pos,unsigned int id)
{
	unsigned int realPos = pos;
	BackPackItem* item = findItemByPos(pos);
	if(!item || item->getItemId() != id || item->isLocked)
	{
		CCLog("remove item error");
		return;
	}
	item->setItemId(0);
	item->isEmpty = true;
	item->amount = 0;
	item->itemLevel = 0;

	item->resetItem();

	if(pos < kAlchemyBag)
	{
		if(GetBackPackLayer())
		{
			GetBackPackLayer()->setOneItemIcon(item,pos);
		}
	}
	else if(pos < kFairyStartId)
	{
		AlchemyUILayer* layer = ShowAlchemyUILayer();
		if(layer)
		{
			layer->setItemIcon(item,pos);
		}
	}
}

void ItemManager::setBackPackDefaultPos(unsigned int ownerPos)
{
	m_defaultPackPos = ownerPos;
	resetBagPacks();
}

void ItemManager::setBackPackUnlockPos(unsigned int pos)
{
	m_unlockPackPos = pos;
	resetBagPacks();
}

void ItemManager::resetBagPacks()
{
	unsigned int totalPackPos = m_defaultPackPos + m_unlockPackPos;
	if(m_backPackList)
	{
		for(unsigned int i=1;i<= m_maxPackPos;i++)
		{
			BackPackItem* item = findItemByPos(i);
			if(item)
			{
				if(i <= totalPackPos)
				{
					item->isLocked = false;
				}
				else
				{
					item->isLocked = true;
				}
				item->position = i;

				//m_backPackList->insert(std::make_pair(i,item));
			}
		}
	}
}

void ItemManager::resetStoragePacks()
{
	unsigned int totalPackPos = m_defaultStoragePos + m_unlockStoragePos;
	if(m_storageList)
	{
		for(unsigned int i=1;i<= m_maxStoragePos;i++)
		{
			BackPackItem* item = findItemByPos(i+kItemStorage);
			if(item)
			{
				if(i <= totalPackPos)
				{
					item->isLocked = false;
				}
				else
				{
					item->isLocked = true;
				}
				item->position = i;
			}
		}
	}
}

void ItemManager::setStorageUnlockPos(unsigned int pos)
{
	m_unlockStoragePos = pos;
	resetStoragePacks();
}

void ItemManager::setStorageDefaultPos(unsigned int ownerPos)
{
	m_defaultStoragePos = ownerPos;
	resetStoragePacks();
}

void ItemManager::resetAlchemyBagPacks(unsigned int ownerPos)
{
	if(m_alchemyBagList)
	{
		for(unsigned int i=1;i<= AlCHEMYBAGCAPACITY;i++)
		{
			BackPackItem* item = findItemByPos(i+kAlchemyBag);
			if(item)
			{
				if(i <= ownerPos)
				{
					item->isLocked = false;
				}
				else
				{
					item->isLocked = true;
				}
				item->position = i;
			}
		}
	}
}

void ItemManager::setAlchemyBagUnlockCapacity(unsigned int value)
{
	m_unlockAlchemyBagPos = value;
	unsigned int totalPackPos = m_defaultAlchemyBagPos + m_unlockAlchemyBagPos;
	resetAlchemyBagPacks(totalPackPos);
}

void ItemManager::setAlchemyBackDefaultCapacity(unsigned int pos)
{
	m_defaultAlchemyBagPos = pos;
	unsigned int totalPackPos = m_defaultAlchemyBagPos + m_unlockAlchemyBagPos;
	resetAlchemyBagPacks(totalPackPos);
}

void ItemManager::resetAlchemyStoragePacks(unsigned int ownerPos)
{
	if(m_alchemyStorageList)
	{
		for(unsigned int i=1;i<= AlCHEMYSTORAGECAPACITY;i++)
		{
			BackPackItem* item = findItemByPos(i+kAlchemyStorage);
			if(item)
			{
				if(i <= ownerPos)
				{
					item->isLocked = false;
				}
				else
				{
					item->isLocked = true;
				}
				item->position = i;
			}
		}
	}
}

void ItemManager::setAlchemyStorageDefaultCapacity(unsigned int pos)
{
	m_defaultAlchemyStoragePos = pos;
	unsigned int totalPackPos = m_defaultAlchemyStoragePos + m_unlockAlchemyStroragePos;
	resetAlchemyStoragePacks(totalPackPos);
}

void ItemManager::setAlchemyStorageUnlockCapacity(unsigned int value)
{
	m_unlockAlchemyStroragePos = value;
	unsigned int totalPackPos = m_defaultAlchemyStoragePos + m_unlockAlchemyStroragePos;
	resetAlchemyStoragePacks(totalPackPos);
}

BackPackItem* ItemManager::setItem(unsigned int pos,unsigned int id, unsigned int level,unsigned int number)
{
	unsigned int realPos = pos;
	BackPackItem* existItem = findItemByPos(realPos);
	if(existItem && !existItem->isLocked)
	{
		existItem->setItemId(id);
		existItem->itemLevel = level;
		existItem->amount = number;
		existItem->isEmpty = false;
		
		existItem->resetEquipInfo();

		for(std::list<ITEMATTR*>::iterator iter = existItem->m_attribution->begin();
			iter != existItem->m_attribution->end(); ++iter)
		{
			ITEMATTR* attr = *iter;
			if(attr)
			{
				delete attr;
				attr = NULL;
			}
		}
		existItem->m_attribution->clear();

		if(pos < kAlchemyBag)
		{
			if(GetBackPackLayer())
			{
				GetBackPackLayer()->setOneItemIcon(existItem,pos);
			}
		}
		else
		{
			AlchemyUILayer* layer = GetCurrentAlchemyLayer();
			if(layer)
			{
				layer->setItemIcon(existItem,pos);
			}
		}
		return existItem;
	}
	return NULL;
}

void ItemManager::resetItems()
{
	if(m_backPackList)
	{
		for(BACKPACK_VECTOR::iterator iter = m_backPackList->begin();
			iter != m_backPackList->end();iter++)
		{
			BackPackItem *item = (*iter).second;
			item->isEmpty = true;
			item->isLocked = false;
		}
	}
	if(m_storageList)
	{
		for(BACKPACK_VECTOR::iterator iter = m_storageList->begin();
			iter != m_storageList->end();iter++)
		{
			BackPackItem *item = (*iter).second;
			item->isEmpty = true;
			item->isLocked = false;
		}
	}
}

unsigned int ItemManager::getBackPackEmptyGridIndex()
{
	if(m_backPackList)
	{
		for(BACKPACK_VECTOR::iterator iter = m_backPackList->begin();
			iter != m_backPackList->end();iter++)
		{
			BackPackItem *item = (*iter).second;
			if(item->isEmpty)
			{
				return item->position;
			}
		}
	}

	return 0;
}

unsigned int ItemManager::getStorageEmptyGridIndex()
{
	if(m_storageList)
	{
		for(BACKPACK_VECTOR::iterator iter = m_storageList->begin();
			iter != m_storageList->end();iter++)
		{
			BackPackItem *item = (*iter).second;
			if(item->isEmpty)
			{
				return item->position;
			}
		}
	}

	return 0;
}

void ItemManager::openBackPack()
{
	BackPackLayer* layer = GetBackPackLayer();
	if(layer)
	{
		layer->openBackPack();
	}
}

void ItemManager::exchangeItemPos(unsigned int from, unsigned int to)
{
	BackPackItem* itemFrom = findItemByPos(from);
	BackPackItem* itemTo = findItemByPos(to);
	if(itemFrom && itemTo && !itemFrom->isLocked && !itemTo->isLocked)
	{
		unsigned int tempId = itemFrom->getItemId();
		bool tempIsEmpty = itemFrom->isEmpty;
		unsigned int tempNumber = itemFrom->amount;
		unsigned int tempLevel = itemFrom->itemLevel;

		std::list<ITEMATTR*>* tempAttr = itemFrom->m_attribution;
		EquipmetInfo* tempEquipInfo = itemFrom->m_equipInfo;
		SPRITEINFO* tempSpriteInfo = itemFrom->m_spriteInfo;

		itemFrom->setItemId(itemTo->getItemId());
		itemFrom->itemLevel = itemTo->itemLevel;
		itemFrom->isEmpty = itemTo->isEmpty;
		itemFrom->amount = itemTo->amount;
		itemFrom->m_attribution = itemTo->m_attribution;
		itemFrom->m_equipInfo = itemTo->m_equipInfo;
		itemFrom->m_spriteInfo = itemTo->m_spriteInfo;

		itemTo->setItemId(tempId);
		itemTo->itemLevel = tempLevel;
		itemTo->isEmpty = tempIsEmpty;
		itemTo->amount = tempNumber;
		itemTo->m_attribution = tempAttr;
		itemTo->m_equipInfo = tempEquipInfo;
		itemTo->m_spriteInfo = tempSpriteInfo;

		if(from < kAlchemyBag && to < kAlchemyBag)
		{
			BackPackLayer* layer = GetBackPackLayer();
			if(layer)
			{
				layer->setOneItemIcon(itemFrom,from);
				layer->setOneItemIcon(itemTo,to);
			}
		}
		else if(from >= kAlchemyBag && to >= kAlchemyBag)
		{
			AlchemyUILayer* layer = ShowAlchemyUILayer();
			if(layer)
			{
				layer->setItemIcon(itemFrom,from);
				layer->setItemIcon(itemTo,to);
			}
		}
		else
		{
			CCLog("error exchange  from %d to %d !",from,to);
		}
	}
	else
	{
		CCLog("exchange item pos error!");
	}
}

bool ItemManager::setEquipItemInfor(unsigned int pos,EquipmentBase equipmetInfo)
{
	BackPackItem* item = findItemByPos(pos);
	if(!item || item->isEmpty || item->isLocked || item->packType != 2)
	{
		CCLog("Error Equip item: %d ",pos);
		return false;
	}
	if(!item->m_equipInfo)
	{
		item->m_equipInfo = new EquipmetInfo();
	}
	item->m_equipInfo->levelUpCost = equipmetInfo.cost_levelup();
	item->m_equipInfo->m_nextAttribution.clear();
	unsigned int count = equipmetInfo.incr_attr_next_lv_size();
	for(unsigned int i = 0; i< count; i++)
	{
		EquipmentBase_Item_Attr attr = equipmetInfo.incr_attr_next_lv(i);
		EQUIPNEXTATTR nextAttr;
		nextAttr.key = attr.key();
		nextAttr.value = attr.value();
		item->m_equipInfo->m_nextAttribution.push_back(nextAttr);
	}
	return true;
}

void ItemManager::loadExchangeItems()
{
	if(!b_isLoadExchangeItems)
	{
		GameConfigFromLuaManager::Get()->getExchangeItems();
		b_isLoadExchangeItems = true;
	}
}

void ItemManager::addExchangeItem(unsigned int exchangeId,string fromItems, string toItems, unsigned int type)
{
	ExchangeItem* item = new ExchangeItem();
	item->setFromItems(fromItems);
	item->setToItems(toItems);
	item->m_exchangeType = type;
	item->m_exchangeId = exchangeId;
	m_exchangeItemList->push_back(item);
}

list<unsigned int>* ItemManager::getExchangeSpriteStones()
{
	loadExchangeItems();
	list<unsigned int>* spriteList = new list<unsigned int>();
	if(m_exchangeItemList)
	{
		for(std::list<ExchangeItem*>::iterator it = m_exchangeItemList->begin();
			it != m_exchangeItemList->end(); it++)
		{
			ExchangeItem *item = *it;
			if(item && item->m_exchangeType == 4)
			{
				spriteList->push_back(item->m_exchangeId);	
			}
		}
	}
	return spriteList;
}

ExchangeItem* ItemManager::getExchageItemById(unsigned int exchangeId)
{
	loadExchangeItems();
	if(m_exchangeItemList)
	{
		for(std::list<ExchangeItem*>::iterator it = m_exchangeItemList->begin();
			it != m_exchangeItemList->end(); it++)
		{
			ExchangeItem *item = *it;
			if(item->m_exchangeId == exchangeId)
			{
				return item;
			}
		}
	}
	return NULL;
}

ExchangeItem* ItemManager::getEquipDrawingById(unsigned int equipId)
{
	loadExchangeItems();
	if(m_exchangeItemList)
	{
		for(std::list<ExchangeItem*>::iterator it = m_exchangeItemList->begin();
			it != m_exchangeItemList->end(); it++)
		{
			ExchangeItem *item = *it;
			if(item)
			{
				if(item->m_fromItems)
				{
					for (std::list<std::pair<unsigned int ,unsigned int> >::iterator iter = item->m_fromItems->begin();
					iter != item->m_fromItems->end();iter++)
					{
						if((*iter).first == equipId)
						{
							return item;
						}
					}	
				}
			}
		}
	}

	return NULL;
}

CCSprite* ItemManager::getIconSpriteById(unsigned int ItemId)
{
	ASprite *as = AspriteManager::getInstance()->getAsprite(KICON_BIN); 
	int idx = GameConfigFromLuaManager::Get()->getItemResourceId(ItemId);
	CCPoint pt;
	CCSprite * pic = as->getSpriteFromFrame_Middle( idx, 0, pt);
	return pic;
}

ItemBase* ItemManager::getItemInfoById(unsigned int id)
{
	ItemBase* info = NULL;
	EquipmentItem* equipmentInfo = new EquipmentItem();
	if(GameConfigFromLuaManager::Get()->getEquipmentItem(id,equipmentInfo))
	{
		info = equipmentInfo;
	}
	else
	{
		CC_SAFE_DELETE(equipmentInfo);
		ItemBase* itemInfo = new ItemBase();
		if(GameConfigFromLuaManager::Get()->getItem(id,itemInfo))
		{
			info = itemInfo;
		}
		else
		{
			CC_SAFE_DELETE(itemInfo);
		}
	}
	return info;
}

unsigned int ItemManager::getItemNumberById(unsigned int id)
{
	unsigned int sum = 0;
	if(m_backPackList)
	{
		for(BACKPACK_VECTOR::iterator iter = m_backPackList->begin();
			iter != m_backPackList->end();iter++)
		{
			BackPackItem *item = (*iter).second;
			if(item && item->getItemId() == id)
			{
				sum += item->amount;
			}
		}
	}
	if(m_storageList)
	{
		for(BACKPACK_VECTOR::iterator iter = m_storageList->begin();
			iter != m_storageList->end();iter++)
		{
			BackPackItem *item = (*iter).second;
			if(item && item->getItemId() == id)
			{
				sum += item->amount;
			}
		}
	}
	if(m_equipmentList)
	{
		for(BACKPACK_VECTOR::iterator iter = m_equipmentList->begin();
			iter != m_equipmentList->end();iter++)
		{
			BackPackItem *item = (*iter).second;
			if(item && item->getItemId() == id)
			{
				sum += item->amount;
			}
		}
	}
	if(m_gemStoneList)
	{
		for(BACKPACK_VECTOR::iterator iter = m_gemStoneList->begin();
			iter != m_gemStoneList->end();iter++)
		{
			BackPackItem *item = (*iter).second;
			if(item && item->getItemId() == id)
			{
				sum += item->amount;
			}
		}
	}
	return sum;
}

void ItemManager::reqAlchemyUpgradeSelected(unsigned int pos)
{
	AlchemyUILayer* layer = ShowAlchemyUILayer();
	if(layer)
	{
		layer->selectUpgradeItem(pos);
	}
}

void ItemManager::reqAlchemyUpgradeUnselected()
{
	AlchemyUILayer* layer = ShowAlchemyUILayer();
	if(layer)
	{
		layer->unselectUpgradeItem();
	}
}

bool ItemManager::getCurrentAlchemyIndex()
{
	AlchemyUILayer* layer = ShowAlchemyUILayer();
	if(layer)
	{
		return layer->getCurrentAlchemyIndex();
	}
	return true;
}

unsigned int ItemManager::getAlchemySearchNpcCost(unsigned int npcID)
{
	if(!m_searchNpcCostMap)
	{
		m_searchNpcCostMap = new std::map<unsigned int ,unsigned int>();
	}

	map<unsigned int ,unsigned int>::iterator it = m_searchNpcCostMap->find(npcID);
	if(it != m_searchNpcCostMap->end())
	{
		return it->second;
	}
	else
	{
		int res = GameConfigFromLuaManager::Get()->getSearchSpiritNpcCost(npcID);

		CCAssert(res >= 0,"Alchemy Search Spirit Data Error");
		m_searchNpcCostMap->insert(make_pair(npcID,res));

		return res;
	}

}

ccColor3B ItemManager::getLabelColorByQuality(unsigned int quality)
{
	ccColor3B color;
	switch(quality)
	{
	
	case  1:
		color =  KQualityGreenColor;
		break;
	case  2:
		color =  KQualityBlueColor;
		break;
	case  3:
		color =  KQualityPurpleColor;
		break;
	case  4:
		color =  ccYELLOW;
		break;
	case  5:
		color =  KQualityOrangeColor;
		break;
	default:
		color =  KQualityWhiteColor;
		break;
	}
	return color;
}

CCSprite* ItemManager::getIconFrame(unsigned int level)
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

unsigned int ItemManager::getHeroWeaponId()
{
	BackPackItem* backItem = findItemByPos(kItemHeroEquip + 3);
	if(backItem)
	{
		return backItem->getItemId();
	}
	else
	{
		return 0;
	}
}

void ItemManager::showItemTipsByPos(unsigned int pos,CCPoint pt)
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
				EquipmentItem* equipInfo = dynamic_cast<EquipmentItem*>(itemInfo);
				if(equipInfo)
				{
					showEquipmentTipByPos(item,icon,pt);
					return;
				}
				switch(itemInfo->m_type)
				{
				case 2:
					showEquipDrawingTipByPos(item,icon,pt);
					break;
				case 3:
					showUnusedItemTipByPos(item,icon,pt);
					break;
				case 7:
					showAlchemyItemTipByPos(item,icon,pt);
					break;
				default:
					showusedItemTipByPos(item,icon,pt);
					break;
				}
			}
		}

	}
}

void ItemManager::showItemTipsById(unsigned int itemId,CCPoint pt)
{
	ItemBase* itemInfo = getItemInfoById(itemId);
	if(itemInfo)
	{
		CCSprite* icon = getIconSpriteById(itemId);
		if(icon)
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
			EquipmentItem* equipInfo = dynamic_cast<EquipmentItem*>(itemInfo);
			if(equipInfo)
			{
				return;
			}
			else
			{
				switch(itemInfo->m_type)
				{
				case 2:
					showEquipDrawingTipByItemid(itemInfo,icon,pt);
					break;
				default:
					showNormalItemTipByItemid(itemInfo,icon,pt);
					break;
				}
			}
		}
	}
	CC_SAFE_DELETE(itemInfo);
}

void ItemManager::showEquipmentTipByPos(BackPackItem* item,CCSprite* icon,CCPoint pt)
{
	if(item && !item->isEmpty && !item->isLocked)
	{
		ItemBase* itemInfo = item->getItemInfo();
		EquipmentItem* equipInfo = dynamic_cast<EquipmentItem*>(itemInfo);
		if(equipInfo)
		{
			TipMgr::Get()->createTip(icon,pt);
			TipMgr::Get()->add(equipInfo->m_name,getLabelColorByQuality(equipInfo->m_quality),22);
			TipMgr::Get()->add("",ccWHITE ,20);
			char levelStr[30];
			sprintf(levelStr,"%s%d",Localizatioin::getLocalization("M_EQUIPMENT_UPGRADELEVEL"),item->itemLevel);
			TipMgr::Get()->add(levelStr,ccORANGE ,20);
			if(item->m_attribution)
			{
				for(std::list<ITEMATTR*>::iterator it = item->m_attribution->begin();
					it != item->m_attribution->end(); ++it)
				{
					ITEMATTR* attr = *it;
                    const char* text = getAttributionText(attr->attr_key,(attr->attr_basic_value+attr->attr_intensify_value));
                    if(text)
                    {
                        TipMgr::Get()->add(text,ccORANGE ,20);
                    }
					
				}
			}
			TipMgr::Get()->add(Localizatioin::getLocalization("M_EQUIPMENT_WEARREQUIREMENT"),ccWHITE ,20);
			char levelRequiredStr[30];
			sprintf(levelRequiredStr,"%s%d",Localizatioin::getLocalization("M_EQUIPMENT_ROLELEVEL"),equipInfo->m_requiredLevel);
			TipMgr::Get()->add(levelRequiredStr,ccWHITE ,20);
			char typeRequiredStr[40];
			if(equipInfo->m_type != 0)
			{
				sprintf(typeRequiredStr,"%s%s",Localizatioin::getLocalization("M_EQUIPMENT_OCCUPATION"),LuaTinkerManager::Get()->getLuaConfig<const char *>("characterString", "Characters", equipInfo->m_type, "Name"));
			}
			else
			{
				sprintf(typeRequiredStr,"%s%s",Localizatioin::getLocalization("M_EQUIPMENT_OCCUPATION"),Localizatioin::getLocalization("M_ALLOCCUPTATION"));
			}
			TipMgr::Get()->add(typeRequiredStr,ccWHITE ,20);
			TipMgr::Get()->add(Localizatioin::getLocalization("M_EQUIPMENT_DESCRIPTION"),ccORANGE ,20);
			//TipMgr::Get()->add(Localizatioin::getLocalization("M_EQUIPMENT_METARIALNEED"),ccWHITE ,20);
			char priceStr[20];
			sprintf(priceStr,"%s%d",Localizatioin::getLocalization("M_PRICE"),equipInfo->m_sellprice);
			TipMgr::Get()->add(priceStr,ccYELLOW ,20);
			TipMgr::Get()->addNodeDone();
		}
	}
}

void ItemManager::showEquipDrawingTipByPos(BackPackItem* item,CCSprite* icon,CCPoint pt)
{
	if(item && !item->isEmpty && !item->isLocked)
	{
		ItemBase* itemInfo = item->getItemInfo();
		if(itemInfo && itemInfo->m_type == 2)
		{
			ExchangeItem* exchangeItem = getEquipDrawingById(itemInfo->m_id);
			if(exchangeItem)
			{
				TipMgr::Get()->createTip(icon,pt);
				TipMgr::Get()->add(itemInfo->m_name,getLabelColorByQuality(itemInfo->m_quality),22);
				TipMgr::Get()->add(Localizatioin::getLocalization("M_DOUBLECLICK"),ccWHITE ,20);
				TipMgr::Get()->add(Localizatioin::getLocalization("M_EQUIPMENT_DESCRIPTION"),ccORANGE ,20);
				TipMgr::Get()->add(Localizatioin::getLocalization("M_EQUIPMENT_METARIALNEED"),ccWHITE ,20);
				for(std::list<pair<unsigned int ,unsigned int> >::iterator iter = exchangeItem->m_fromItems->begin();
					iter != exchangeItem->m_fromItems->end();iter++)
				{
					ccColor3B color;
					unsigned int matarialId = (*iter).first;
					unsigned int ownerNum = getItemNumberById(matarialId);
					if(ownerNum >= (*iter).second)
					{
						ownerNum = (*iter).second;
						color = ccGREEN;
					}
					else
					{
						color = ccRED;
					}
					ItemBase* info = getItemInfoById(matarialId);
					if(info)
					{
						char numStr[50];
						sprintf(numStr,"%s%d/%d",info->m_name,ownerNum,(*iter).second);
						TipMgr::Get()->add(numStr,color ,20);
					}
					
				}
				char priceStr[20];
				sprintf(priceStr,"%s%d",Localizatioin::getLocalization("M_PRICE"),itemInfo->m_sellprice);
				TipMgr::Get()->add(priceStr,ccYELLOW ,20);
				TipMgr::Get()->addNodeDone();
			}
			
		}
	}
}

void ItemManager::showUnusedItemTipByPos(BackPackItem* item,CCSprite* icon,CCPoint pt)
{
	if(item && !item->isEmpty && !item->isLocked)
	{
		ItemBase* itemInfo = item->getItemInfo();
		if(itemInfo)
		{
			TipMgr::Get()->createTip(icon,pt);
			TipMgr::Get()->add(itemInfo->m_name,getLabelColorByQuality(itemInfo->m_quality),22);
			TipMgr::Get()->add(Localizatioin::getLocalization("M_EQUIPMENT_DESCRIPTION"),ccWHITE ,20);
			char priceStr[20];
			sprintf(priceStr,"%s%d",Localizatioin::getLocalization("M_PRICE"),itemInfo->m_sellprice);
			TipMgr::Get()->add(priceStr,ccYELLOW ,20);
			TipMgr::Get()->addNodeDone();
		}
	}
}

void ItemManager::showusedItemTipByPos(BackPackItem* item,CCSprite* icon,CCPoint pt)
{
	if(item && !item->isEmpty && !item->isLocked)
	{
		ItemBase* itemInfo = item->getItemInfo();
		if(itemInfo)
		{
			TipMgr::Get()->createTip(icon,pt);
			TipMgr::Get()->add(itemInfo->m_name,getLabelColorByQuality(itemInfo->m_quality),22);
			TipMgr::Get()->add(Localizatioin::getLocalization("M_DOUBLECLICK"),ccWHITE ,20);
			TipMgr::Get()->add(Localizatioin::getLocalization("M_EQUIPMENT_DESCRIPTION"),ccWHITE ,20);
			char priceStr[20];
			sprintf(priceStr,"%s%d",Localizatioin::getLocalization("M_PRICE"),itemInfo->m_sellprice);
			TipMgr::Get()->add(priceStr,ccYELLOW ,20);
			TipMgr::Get()->addNodeDone();
		}
	}
}

void ItemManager::showEquipDrawingTipByItemid(ItemBase* itemInfo,CCSprite* icon,CCPoint pt)
{
	ExchangeItem* exchangeItem = getEquipDrawingById(itemInfo->m_id);
	if(exchangeItem)
	{
		TipMgr::Get()->createTip(icon,pt);
		TipMgr::Get()->add(itemInfo->m_name,getLabelColorByQuality(itemInfo->m_quality),22);
		TipMgr::Get()->add(Localizatioin::getLocalization("M_EQUIPMENT_DESCRIPTION"),ccORANGE ,20);
		TipMgr::Get()->add(Localizatioin::getLocalization("M_EQUIPMENT_METARIALNEED"),ccWHITE ,20);
		for(std::list<pair<unsigned int ,unsigned int> >::iterator iter = exchangeItem->m_fromItems->begin();
			iter != exchangeItem->m_fromItems->end();iter++)
		{
			ccColor3B color;
			unsigned int matarialId = (*iter).first;
			unsigned int ownerNum = getItemNumberById(matarialId);
			if(ownerNum >= (*iter).second)
			{
				ownerNum = (*iter).second;
				color = ccGREEN;
			}
			else
			{
				color = ccRED;
			}
			ItemBase* info = getItemInfoById(matarialId);
			if(info)
			{
				char numStr[50];
				sprintf(numStr,"%s%d/%d",info->m_name,ownerNum,(*iter).second);
				TipMgr::Get()->add(numStr,color ,20);
			}

		}
		char priceStr[20];
		sprintf(priceStr,"%s%d",Localizatioin::getLocalization("M_PRICE"),itemInfo->m_sellprice);
		TipMgr::Get()->add(priceStr,ccYELLOW ,20);
		TipMgr::Get()->addNodeDone();
	}
}

void ItemManager::showNormalItemTipByItemid(ItemBase* itemInfo,CCSprite* icon,CCPoint pt)
{
	TipMgr::Get()->createTip(icon,pt);
	TipMgr::Get()->add(itemInfo->m_name,getLabelColorByQuality(itemInfo->m_quality),22);
	TipMgr::Get()->add(Localizatioin::getLocalization("M_EQUIPMENT_DESCRIPTION"),ccWHITE ,20);
	char priceStr[20];
	sprintf(priceStr,"%s%d",Localizatioin::getLocalization("M_PRICE"),itemInfo->m_sellprice);
	TipMgr::Get()->add(priceStr,ccYELLOW ,20);
	TipMgr::Get()->addNodeDone();
}

void ItemManager::showAlchemyItemTipByPos(BackPackItem* item,CCSprite* icon,CCPoint pt)
{
	if(item && !item->isEmpty && !item->isLocked)
	{
		ItemBase* itemInfo = item->getItemInfo();
		if(itemInfo)
		{
			TipMgr::Get()->createTip(icon,pt);
			TipMgr::Get()->add(itemInfo->m_name,getLabelColorByQuality(itemInfo->m_quality),22);
			char levelStr[50];
			sprintf(levelStr,"%s%d",Localizatioin::getLocalization("M_EQUIPMENT_LEVEL"),item->itemLevel);
			TipMgr::Get()->add(levelStr,ccORANGE ,20);
			if(item->m_attribution)
			{
				for(std::list<ITEMATTR*>::iterator it = item->m_attribution->begin();
					it != item->m_attribution->end(); ++it)
				{
					ITEMATTR* attr = *it;
					const char* text = getAttributionText(attr->attr_key,(attr->attr_basic_value+attr->attr_intensify_value));
                    if(text)
                    {
                        TipMgr::Get()->add(text,ccORANGE ,20);
                    }
				}
			}
			if(item->m_spriteInfo)
			{
				char priceStr[50];
				if(item->m_spriteInfo != 0)
				{
					sprintf(priceStr,"%s%d",Localizatioin::getLocalization("M_ELITE_NEXTLEVEL"),item->m_spriteInfo->levelUpCost);
				}
				else
				{
					sprintf(priceStr,"%s",Localizatioin::getLocalization("M_REACH_HIGHESTLEVEL"));
				}
				TipMgr::Get()->add(priceStr,ccGREEN ,20);
				
			}
			TipMgr::Get()->addNodeDone();
		}
	}
}

const char* ItemManager::getAttributionText(unsigned int key,unsigned int value)
{
	const char* str;
	switch(key)
	{
	case PB_ITEM_ATTR_PHYATK:
		str = Localizatioin::getLocalization("M_ATTRIBUTE_PHYATTACK");
		break;
	case PB_ITEM_ATTR_MAGATK:
		str = Localizatioin::getLocalization("M_ATTRIBUTE_MAGATTACK");
		break;
	case PB_ITEM_ATTR_SKIATK:
		str = Localizatioin::getLocalization("M_ATTRIBUTE_SKIATTACK");
		break;
	case PB_ITEM_ATTR_PHYDEF:
		str = Localizatioin::getLocalization("M_ATTRIBUTE_PHYDEFENCE");
		break;
	case PB_ITEM_ATTR_MAGDEF:
		str = Localizatioin::getLocalization("M_ATTRIBUTE_MAGDEFENCE");
		break;
	case PB_ITEM_ATTR_SKIDEF:
		str = Localizatioin::getLocalization("M_ATTRIBUTE_SKIDEFENCE");
		break;
	case PB_ITEM_ATTR_HP:
		str = Localizatioin::getLocalization("M_ATTRIBUTE_LIFE");
		break;
	case PB_ITEM_ATTR_ACCU:
		str = Localizatioin::getLocalization("M_ATTRIBUTE_ACCURATE");
		break;
	case PB_ITEM_ATTR_DODG:
		str = Localizatioin::getLocalization("M_ATTRIBUTE_DODGE");
		break;
	case PB_ITEM_ATTR_WRK:
		str = Localizatioin::getLocalization("M_ATTRIBUTE_WRECK");
		break;
	case PB_ITEM_ATTR_PARRY:
		str = Localizatioin::getLocalization("M_ATTRIBUTE_BLOCK");
		break;
	case PB_ITEM_ATTR_CRIT:
		str = Localizatioin::getLocalization("M_ATTRIBUTE_CRITICAL");
		break;
	case PB_ITEM_ATTR_TENA:
		str = Localizatioin::getLocalization("M_ATTRIBUTE_TENACITY");
		break;
	case PB_ITEM_ATTR_SLY:
		str = Localizatioin::getLocalization("M_ATTRIBUTE_SLAY");
		break;
	case PB_ITEM_ATTR_SPEED:
		str = Localizatioin::getLocalization("M_ATTRIBUTE_SPEED");
		break;
	default:
		str = NULL;
		break;
	}
	if(str != NULL)
	{
		char* text = new char[50];
		sprintf(text,"%s+%d",str,value);
		CCString* pRet = CCString::create(text);
		return pRet->m_sString.c_str();
	}
	return NULL;
}

void ItemManager::setEquipMaxTimes(unsigned int maxTimes)
{
	USERINFO info = UserData::GetUserInfo();
	if(maxTimes != info.m_equipLvUpTotalTimes)
	{
		info.m_equipLvUpTotalTimes = maxTimes;
		UserData::SetUserInfo(info);
		NotificationCenter::defaultCenter()->broadcast(GM_ATTR_EQUIP_LVUP_MAX_TIMES,this);
	}
}

/*
背包格
*/
BackPackItem::BackPackItem(unsigned int type)
{
	packType = type;
	m_itemInfo = NULL;
	m_attribution = new std::list<ITEMATTR*>();
	m_equipInfo = NULL;
	m_spriteInfo = NULL;
}

BackPackItem::~BackPackItem()
{	
	if(m_attribution)
	{
		for(std::list<ITEMATTR*>::iterator iter = m_attribution->begin();
			iter != m_attribution->end(); ++iter)
		{
			ITEMATTR* attr = *iter;
			if(attr)
			{
				delete attr;
				attr = NULL;
			}
		}
		m_attribution->clear();
		delete m_attribution;
		m_attribution = NULL;
	}
	
	resetEquipInfo();
	CC_SAFE_DELETE(m_spriteInfo);
	CC_SAFE_DELETE(m_itemInfo);
}

ItemBase* BackPackItem::getItemInfo()
{
	if(NULL == m_itemInfo)
	{
		m_itemInfo = ItemManager::Get()->getItemInfoById(itemId);
	}

	return m_itemInfo;

}

void BackPackItem::setItemId(unsigned int id)
{
	if(id != itemId)
	{
		if(m_itemInfo != NULL)
		{
			CC_SAFE_DELETE(m_itemInfo);
		}
		itemId = id;
	}
}

void BackPackItem::resetEquipInfo()
{
	if(this->m_equipInfo)
	{
		this->m_equipInfo->m_equipHoles.clear();
		this->m_equipInfo->m_nextAttribution.clear();
		delete m_equipInfo;
		m_equipInfo = NULL;
	}
}

void BackPackItem::setEquipInfo(EquipmentBase equipmentInfo)
{
	resetEquipInfo();
	if(!m_equipInfo)
	{
		m_equipInfo = new EquipmetInfo();
	}
	m_equipInfo->levelUpCost = equipmentInfo.cost_levelup();
	unsigned int count = equipmentInfo.incr_attr_next_lv_size();
	for(unsigned int i = 0; i< count; i++)
	{
		EquipmentBase_Item_Attr attr = equipmentInfo.incr_attr_next_lv(i);
		EQUIPNEXTATTR nextAttr;
		nextAttr.key = attr.key();
		nextAttr.value = attr.value();
		m_equipInfo->m_nextAttribution.push_back(nextAttr);
	}

	unsigned int holeCount = equipmentInfo.equip_holes_size();
	for(unsigned int j=0; j<holeCount; j++)
	{
		EQUIPHOLE hole;
		CSEquipHole cs_hole = equipmentInfo.equip_holes(j);
		hole.attr_key = cs_hole.attr_key();
		hole.attr_value = cs_hole.attr_value();
		hole.hole_index = cs_hole.hole_index();
		hole.item_gem_id = cs_hole.item_gem_id();
		if(cs_hole.has_attr_max_v())
		{
			hole.max_value = cs_hole.attr_max_v();
		}
		else
		{
			hole.max_value = 0;
		}
		if(cs_hole.has_attr_min_v())
		{
			hole.min_value = cs_hole.attr_min_v();
		}
		else
		{
			hole.min_value = 0;
		}
		if(m_equipInfo->m_equipHoles.find(hole.hole_index) == m_equipInfo->m_equipHoles.end())
		{
			m_equipInfo->m_equipHoles.insert(std::make_pair(hole.hole_index,hole));
		}
	}
}

void BackPackItem::setSpriteInfo(SpiritStoneBase base)
{
	if(m_spriteInfo == NULL)
	{
		m_spriteInfo = new SPRITEINFO();
	}
	m_spriteInfo->levelUpCost = base.consume();
	m_spriteInfo->convertSp = base.convert();
}

void BackPackItem::resetItem()
{
	resetEquipInfo();
	CC_SAFE_DELETE(m_spriteInfo);
	CC_SAFE_DELETE(m_itemInfo);
	if(m_attribution)
	{
		for(std::list<ITEMATTR*>::iterator iter = m_attribution->begin();
			iter != m_attribution->end(); ++iter)
		{
			ITEMATTR* attr = *iter;
			if(attr)
			{
				delete attr;
				attr = NULL;
			}
		}
		m_attribution->clear();
	}
}

/*
物品交换列表
*/
ExchangeItem::ExchangeItem()
{
	m_exchangeType = 0;
	m_fromItems = NULL;
	m_toItems = NULL;
}

ExchangeItem::~ExchangeItem()
{
	if(m_fromItems)
	{
		m_fromItems->clear();
		CC_SAFE_DELETE(m_fromItems);
	}

	if(m_toItems)
	{
		m_toItems->clear();
		CC_SAFE_DELETE(m_toItems);
	}
}

void ExchangeItem::setFromItems(std::string fromStr)
{
	m_fromItems = initItemsByString(fromStr);
}

void ExchangeItem::setToItems(std::string toStr)
{
	m_toItems = initItemsByString(toStr);
}

std::list<pair<unsigned int ,unsigned int> >* ExchangeItem::initItemsByString(std::string str)
{
	std::list<pair<unsigned int ,unsigned int> >* items = new std::list<pair<unsigned int ,unsigned int> >();
	int currentPos = 0;
	while(currentPos != str.npos)
	{
		int pos = str.find_first_of(';',currentPos);

			std::string itemStr = str.substr(currentPos,pos-currentPos);
			int dashPos = itemStr.find_first_of("/");
			if(dashPos != itemStr.npos)
			{
				std::string idStr = itemStr.substr(0,dashPos);
				std::string numStr = itemStr.substr(dashPos+1,pos-1);
				int id = atoi(idStr.c_str());
				int num = atoi(numStr.c_str());
				items->push_back(std::make_pair(id,num));
				//items->insert(std::make_pair(id,num));
			}		
			if(pos != str.npos)
			{
				currentPos = pos+1;
			}
			else
			{
				currentPos = pos;
			}
	}
	return items;
}

