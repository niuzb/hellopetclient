#ifndef ALCHEMY_UI_LAYER_H
#define ALCHEMY_UI_LAYER_H

#include "cocos2d.h"
#include "TXGUIHeader.h"
#include "ItemManager.h"
#include "cs_core.pb.h"
#include <vector>
using namespace cocos2d;
using namespace TXGUI;

typedef struct stAlchemyExchangeInfo
{
	stAlchemyExchangeInfo(){memset(this, 0x00, sizeof(stAlchemyExchangeInfo));}
	unsigned int ss_id;				// 灵石id
	unsigned int consume;				// 升级消耗精华数量
	unsigned int convert;				// 兑换成精华数量
	unsigned int need_chip;			// 需要的碎片数量
	unsigned int key;					// 灵石对应属性key
	unsigned int value;				// 灵石对应属性value
}AlchemyExInfo;

class AlchemyUILayer : public cocos2d::CCLayer,
					   public TXGUI::ObserverProtocol
{
public:
	AlchemyUILayer();
	virtual ~AlchemyUILayer();
	CREATE_FUNC(AlchemyUILayer);
	virtual bool init(); 

	// button callback 
	virtual void onClosedBtClicked(CCObject* sender);
	virtual void onClosedEquipBtClicked(CCObject* sender);
	virtual void onItemClicked(CCObject* sender);
	virtual void onEnterAlchemyBagClicked(CCObject* sender);
	virtual void onClosedExchangeBtClicked(CCObject* sender);
	virtual void onAlchemyExchangeClicked(CCObject* sender);
	virtual void onExchangeListItemClicked(CCObject* sender);
	virtual void onDragInAlchemyBtClicked(CCObject* sender);
	void onClickHeroEquip(CCObject* sender);
	void onClickFairyEquip(CCObject* sender);
	void onClickFindSoul(CCObject* sender);
	void onClickTransAllStoneEnergy(CCObject* sender);
	void onClickUpgradeStone(CCObject* sender);
	void onClickExchangeBt(CCObject* sender);

	void onEquipmentTapped(CCObject* sender);
	void onTapCancel(CCObject* sender);
	void onItemTapped(CCObject* sender);

	void setItemIcon(BackPackItem* item,unsigned int index);
	void selectUpgradeItem(unsigned int position,bool isEffect = false);
	void unselectUpgradeItem();
	bool getCurrentAlchemyIndex(){return m_equipLayoutIndex;}
	void setNpcSelected(unsigned int index,bool isEffect = false);
	void onReceivedSearchResult(unsigned int coin,unsigned int npcIndex,unsigned int itemId);
	void onReceivedUpgradeSuccess();
	void onReceivedExchangeInfo(CSGetExchangeSSInfoRsp* msg);

	virtual void closeLayerCallBack(void);
	void onReceiveSpriteTrans();
protected:
	/// 消息响应函数
	virtual void onBroadcastMessage(BroadcastMessage* msg);

private:
	virtual bool initAlchemistStone();
	virtual bool initAlchemistStorage();
	virtual bool initAlchemistExchange();
	virtual void initNpcIcon();
	virtual void initAlchemyExItemInfo();
	virtual void setNpcHeadIcon(const char* name,const char* resoureName);

	virtual void addExchangeItem(unsigned int itemId,unsigned int index);
	void showSelectecdExchangeItem(unsigned int index);

	virtual void hideAlchemyLayer();
	virtual void showAlchemyLayer();
	virtual void hideAlchemyEquipLayer();
	virtual void showAlchemyEquipLayer();
	virtual void hideAlchemyExchangeLayer();
	virtual void showAlchemyExchangeLayer();

	void setBagItemIcon(BackPackItem* item,unsigned int position);
	void setStorageItemIcon(BackPackItem* item,unsigned int position);
	void setEquipItemIcon(BackPackItem* item,unsigned int position);
	void showEquipItems(bool isHero);
	void showHeroEquipItems();
	void showFairyEquipItems();

	void setStoneEnergyLabel();
	void setSpiritChipLabel();
	void showSpriteParticleEffect(CCNode* parent,unsigned int id,CCPoint pt = CCPointZero);
	void setEnergyIconVisible(bool isVisible);

	void updateBottomDiamondLabel();
	void updateBottomCoinLabel();
	void updateBottomPieceLabel();
	void updateBottomSpLabel();
	bool checkPlayerEquipUnlock(int index);
	void setUnlockEqiupLabel(int index,bool isVisible);

	void playTransEffect(UIButton* parentPt);
private:
	UILayout* m_uiLayout;
	UILayout* m_alchemyEquipLayout;
	UILayout* m_alchemyExchangeLayout;
	CCLayer* m_alchemistStoneLayer;
	CCLayer* m_alchemistStorageLayer;
	UIScrollList* m_exchangeList;
	std::map<unsigned int,unsigned int>* m_exchangeItemList;
	std::map<unsigned int,AlchemyExInfo> m_exchangeItemInfo;
	unsigned int m_selectedExchangeIndex;
	UIButton* m_selectedButton;
	unsigned int m_selectedUpgradeItemPos;	// 准备升级的灵石在背包中的位置
	std::vector<IconButton*> m_bagListButton; 
	std::vector<IconButton*> m_storageListButton;
	bool m_equipLayoutIndex; // 装备列表显示的是玩家或者精灵的标签: true 玩家, false 精灵
	UIButtonToggle* m_heroEquipToggle;
	UIButtonToggle* m_fairyEquipToggle;
	UIPicture* m_heroEquipPic;
	UIPicture* m_fairyEquipPic;
	unsigned int m_selectedNpcIndex; // 寻灵的NPC
};

#endif