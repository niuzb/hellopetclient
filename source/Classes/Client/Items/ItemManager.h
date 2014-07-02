#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H

#include "Singleton_t.h"
#include "cocos2d.h"

#include <map>
#include <list>
#include "ItemBase.h"
#include "EquipmentItem.h"
#include "cs_core.pb.h"
using namespace cocos2d;

#define AlCHEMYBAGCAPACITY	24
#define AlCHEMYSTORAGECAPACITY	18

/*
// id 0~999 背包格 1000~1999 仓库格 2000~2999 装备格 3000~3999 灵石包 4000~4999 灵石仓库 5000~5999 灵石装备格 7000 ~ 7999 宝石格
*/
enum
{
	kItemBag = 0,
	kItemStorage = 1000,
	kItemHeroEquip = 2000,
	kItemFairyEquip = 2100,
	kAlchemyBag = 3000,
	kAlchemyStorage = 4000,
	kAlchemyHeroEquip = 5000,
	kAlchemyFairyEquip = 5100,
	kFairyStartId = 6000,
	kItemGemStone = 7000
};

typedef struct EquipmetHole
{
	EquipmetHole(){memset(this, 0x00, sizeof(EquipmetHole));}
	unsigned int hole_index;		// 孔编号
	unsigned int item_gem_id;		// 宝石id
	unsigned int attr_key;			// 影响属性的key
	unsigned int attr_value;		// 影响属性的value
	unsigned int max_value;			// 属性可能最小值
	unsigned int min_value;			// 属性可能最大值
}EQUIPHOLE;

typedef struct ItemAttribution
{
	ItemAttribution(){memset(this, 0x00, sizeof(ItemAttribution));}
	unsigned int attr_key;					// 物品属性key
	unsigned int attr_basic_value;			// 物品基本属性对应的value
	unsigned int attr_intensify_value;		// 强化影响物品属性value增量
	unsigned int attr_gem_value;			// 宝石影响物品属性value增量
}ITEMATTR;

typedef struct EquipNextAttribution
{
	EquipNextAttribution(){memset(this, 0x00, sizeof(EquipNextAttribution));}
	unsigned int key;					// 装备强化下一级属性key
	unsigned int value;					// 装备强化下一级属性value
}EQUIPNEXTATTR;

typedef struct EquipmetInfo
{
	EquipmetInfo(){levelUpCost = 0;}
	unsigned int levelUpCost; // 装备升级花费
	std::list<EQUIPNEXTATTR>	m_nextAttribution; // 装备强化下一级属性
	std::map<unsigned int,EQUIPHOLE> m_equipHoles;	// 装备孔
}EQUIPINFO;

typedef struct SpriteStoneInfo
{
	SpriteStoneInfo(){memset(this, 0x00, sizeof(SpriteStoneInfo));}
	unsigned int levelUpCost; // 升级需要的灵能
	unsigned int convertSp;	  // 转化的灵能
}SPRITEINFO;

class BackPackItem
{
	// 背包格
public: 
	BackPackItem(unsigned int packType);
	~BackPackItem();
	ItemBase* getItemInfo();
	void setItemId(unsigned int id);
	void resetEquipInfo();
	void setEquipInfo(EquipmentBase base);
	unsigned int getItemId(){return itemId;}
	void setSpriteInfo(SpiritStoneBase base);
	void resetItem();
public:

	bool isLocked;			// 是否解锁
	bool isEmpty;			// 是否为空	
	unsigned int position;	// 物品位置
	unsigned int amount;	// 物品数量
	unsigned int itemLevel;	// 物品等级
	EQUIPINFO* m_equipInfo;	// 装备强化属性
	unsigned int packType; // 格子类型： 0 背包; 1仓库 ; 2装备栏 ;3 灵石背包;4 灵石仓库 ; 5灵石装备栏 ;6 精灵装备
	std::list<ITEMATTR*>*	m_attribution;
	SPRITEINFO* m_spriteInfo; // 灵石特有属性

private:
	ItemBase* m_itemInfo;	    // 物品基本配置属性
	unsigned int itemId;		// 物品Id	

};

class ExchangeItem
{
// 物品交换表格

public:
	ExchangeItem();
	~ExchangeItem();
	void setFromItems(std::string fromStr);
	void setToItems(std::string toStr);
private:
	std::list<std::pair<unsigned int ,unsigned int> >* initItemsByString(std::string str);
public:
	unsigned int m_exchangeType;
	unsigned int m_exchangeId;
	std::list<std::pair<unsigned int ,unsigned int> >* m_fromItems;
	std::list<std::pair<unsigned int ,unsigned int> >* m_toItems;
	/*std::map<unsigned int ,unsigned int>* m_fromItems;
	std::map<unsigned int ,unsigned int>* m_toItems;*/
};

typedef std::map<unsigned int ,BackPackItem*> BACKPACK_VECTOR;

class ItemManager : public TSingleton<ItemManager>
{
public:
	ItemManager();
	virtual ~ItemManager();

	void init();

	BackPackItem* findItemByPos(unsigned int pos);
	//bool addItem()	
	void resetItems();
	unsigned int getBackPackEmptyGridIndex();
	void setBackPackDefaultPos(unsigned int ownerPos);
	void setBackPackUnlockPos(unsigned int pos);
	void setStorageUnlockPos(unsigned int pos);
	void setEquipMaxTimes(unsigned int maxTimes);

	unsigned int getBackPackMaxPos(){return m_maxPackPos;}

	void openBackPack();
	void exchangeItemPos(unsigned int from, unsigned int to);
	BackPackItem* setItem(unsigned int pos,unsigned int id, unsigned int level,unsigned int number);

	void setStorageDefaultPos(unsigned int ownerPos);
	unsigned int getStorageEmptyGridIndex();

	unsigned int getStorageMaxPos(){return m_maxStoragePos;}

	void removeItem(unsigned int pos, unsigned int id);
	bool setEquipItemInfor(unsigned int pos,EquipmentBase equipmetInfo);
	void addExchangeItem(unsigned int exchangeId,std::string fromItems, std::string toItems, unsigned int type);

	ItemBase* getItemInfoById(unsigned int id);
	ExchangeItem* getEquipDrawingById(unsigned int equipId); // 基于查找到from item查找交换表格
	ExchangeItem* getExchageItemById(unsigned int exchangeId);						 // 基于表格id查找表格
	std::list<unsigned int>* getExchangeSpriteStones();

	unsigned int getItemNumberById(unsigned int id);
	CCSprite* getIconSpriteById(unsigned int ItemId);
	void loadExchangeItems();

	// alchemy
	void setAlchemyBagUnlockCapacity(unsigned int value);
	void setAlchemyStorageUnlockCapacity(unsigned int value);
	void setAlchemyBackDefaultCapacity(unsigned int pos);
	void setAlchemyStorageDefaultCapacity(unsigned int pos);
	void reqAlchemyUpgradeSelected(unsigned int pos);
	void reqAlchemyUpgradeUnselected();	
	bool getCurrentAlchemyIndex();

	unsigned int getAlchemySearchNpcCost(unsigned int npcID);
	void showItemTipsByPos(unsigned int pos,CCPoint pt);
	void showItemTipsById(unsigned int itemId,CCPoint pt);

	const char* getAttributionText(unsigned int key,unsigned int value);
	CCSprite* getIconFrame(unsigned int level);
	ccColor3B getLabelColorByQuality(unsigned int quality);

	// weapon id 
	unsigned int getHeroWeaponId();
private: 
	// 显示物品信息
	void showEquipmentTipByPos(BackPackItem* item,CCSprite* icon,CCPoint pt);
	void showEquipDrawingTipByPos(BackPackItem* item,CCSprite* icon,CCPoint pt);
	void showUnusedItemTipByPos(BackPackItem* item,CCSprite* icon,CCPoint pt);
	void showusedItemTipByPos(BackPackItem* item,CCSprite* icon,CCPoint pt);
	void showAlchemyItemTipByPos(BackPackItem* item,CCSprite* icon,CCPoint pt);

	void showEquipDrawingTipByItemid(ItemBase* item,CCSprite* icon,CCPoint pt);
	void showNormalItemTipByItemid(ItemBase* item,CCSprite* icon,CCPoint pt);
	void resetAlchemyBagPacks(unsigned int ownerPos);
	void resetAlchemyStoragePacks(unsigned int ownerPos);
	void resetBagPacks();
	void resetStoragePacks();
private:
	BACKPACK_VECTOR *m_backPackList;
	BACKPACK_VECTOR *m_storageList;
	BACKPACK_VECTOR *m_equipmentList;
	BACKPACK_VECTOR *m_fairyEquipmentList;
	BACKPACK_VECTOR *m_alchemyBagList;
	BACKPACK_VECTOR *m_alchemyStorageList;
	BACKPACK_VECTOR *m_alchemyEquipList;
	BACKPACK_VECTOR *m_alchemyFairyEquipList;
	BACKPACK_VECTOR *m_gemStoneList;
	unsigned int m_maxPackPos;					// 背包格子总数
	unsigned int m_defaultPackPos;				//玩家默认的背包格子数
	unsigned int m_unlockPackPos;				//已解锁的背包格子数
	unsigned int m_maxStoragePos;				//仓库格子总数
	unsigned int m_defaultStoragePos;			//默认的仓库格子数
	unsigned int m_unlockStoragePos;			//已解锁的仓库的格子数
	unsigned int m_defaultAlchemyBagPos;		//默认的炼金桌格子数
	unsigned int m_unlockAlchemyBagPos;			//已解锁的炼金桌格子数
	unsigned int m_defaultAlchemyStoragePos;	//默认的炼金背包格子数
	unsigned int m_unlockAlchemyStroragePos;	//已解锁的炼金背包格子数
	unsigned int m_surplusGemRecastNum;			//默认宝石重铸次数
	std::map<unsigned int ,unsigned int>* m_searchNpcCostMap;
	std::list<ExchangeItem*>* m_exchangeItemList;
	bool b_isLoadExchangeItems;
};

#endif	