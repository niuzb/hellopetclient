#ifndef BACKPACK_LAYER_H
#define BACKPACK_LAYER_H

#include "ASprite.h"
#include "UILayout.h"
#include "ItemManager.h"
#include "UIScrollPage.h"
#include "DragReceiver.h"
#include "UIContainer.h"
#include "UIButton.h"
#include "GameConfigFromLuaManager.h"
using namespace std;
using namespace cocos2d;

#define UI_BOARD "UI/ui_board.bin"
#define EACH_ROW_NUMBER 3
#define EACH_COLUMN_NUMBER 4
#define EACH_PAGE_NUMBER (EACH_ROW_NUMBER * EACH_COLUMN_NUMBER)

class SpriteSeer;
class ShopUILayer;

class BackPackLayer : public cocos2d::CCLayer,
					  public TXGUI::ObserverProtocol
{
public:
	BackPackLayer();
	virtual ~BackPackLayer();

	CREATE_FUNC(BackPackLayer);
	virtual bool init();
    
    CC_SYNTHESIZE(ShopUILayer*, m_pShopUILayer, pShopUILayer);
    
	void openBackPack();
    void openEquipment();
    
    
    void openShop(CCObject* sender);
	void openStoreHouse(CCObject* sender);
	void openAttributeBoard(CCObject* sender);
	void closeStorage(CCObject* sender);
	void closeBackPack(CCObject* sender);
    void closeEquipment(CCObject* sender);
	void closeAttributeBoard(CCObject* sender);
	void reOrderBackPackItems(CCObject* sender);
	void reOrderStorageItems(CCObject* sender);
	void onItemClicked(CCObject* sender);
	void onItemDoubleClicked(CCObject* sender);
	void resetBackPackItemIcon(unsigned int index);
	void resetStorageItemIcon(unsigned int index);
	void resetItemIcon(unsigned int index);
	void setOneItemIcon(BackPackItem* item,unsigned int index);

	// 判定点击是否在对应面板框内
	bool checkInBackPackBg(CCTouch *pTouch);
	bool checkInStoragekBg(CCTouch *pTouch);
	bool checkInEquipmentBg(CCTouch *pTouch);
	virtual void setVisible(bool visible);
	void onBagButtonClicked();
	// 双击装备栏button
	void onEquipmentItemDoubleClicked(CCObject* sender);
	void onEquipmentTapped(CCObject* sender);
	void onTapCancel(CCObject* sender);
	void onItemTapped(CCObject* sender);

	virtual void closeLayerCallBack(void);
	/**
	* Instruction : 点击特训按钮
	* @param 
	*/	
	void TrainButtonClicked(CCObject* sender);
	/**
	* Instruction : 隐藏右侧的面板
	* @param 
	*/
	void HideRightPanel();
	/**
	* Instruction : 显示精灵潜能加强面板
	* @param 
	*/
	void ShowElfStrengthenPanel();
	/**
	* Instruction : 同时显示背包界面&精灵界面
	* @param 
	*/
	void ShowElfPanelWithBackPackLayer();
protected:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	
	/// 消息响应函数
	virtual void onBroadcastMessage(BroadcastMessage* msg);
private:
	
	void setOneBackPackIcon(BackPackItem* item,unsigned int index);
	void setOneStorageIconn(BackPackItem* item,unsigned int index);
	void setEquipmentIcon(BackPackItem* item,unsigned int index);
	CCSprite* getEquipmentUpgradeIcon(unsigned int ItemId);
	CCSprite* getIconSpriteById(unsigned int ItemId);
	CCSprite* getIconFrame(unsigned int level);
	TXGUI::UIButton* getEquipmentButton(int index);
	void initBgTouchArea();
	void initButtonPriority();
	void checkPlayerModle();
	void showPlayerLevel();
	void showPlayerExp();
	void showPlayerAttri();
	void showEquipmentTip(unsigned int pos,CCPoint pt);
	void showItemTip(unsigned int pos,CCPoint pt);

	void checkLayerHide();
private:
	ASprite*    m_curUiAs;
	TXGUI::UILayout *backPackLayout;
	bool b_isBackPackOpened;
	bool b_isStorageOpened;
    bool b_isEquipmentOpened;
	bool b_isAttributeOpened;
	string m_lockPicName;
	TXGUI::UIScrollPage * m_backPackScrollPage;
	TXGUI::UIScrollPage * m_storageScrollPage;
	TXGUI::UIContainer* m_backPackContainer;
	TXGUI::UIContainer* m_storageContainer;
    TXGUI::UIContainer* m_equipmentContainer;
	CCPoint		m_packbgPoint;
	CCSize		m_packbgSize;
	CCPoint		m_storagebgPoint;
	CCSize		m_storagebgSize;
	CCPoint		m_equipmentbgPoint;
	CCSize		m_equipmentbgSize;
	DragReceiver* m_backPackReceiver;
	DragReceiver* m_storageReceiver;
	DragReceiver* m_equipmentReceiver;
	TXGUI::UIButton* m_equipmentHelmetButton;
	TXGUI::UIButton* m_equipmentNecklaceButton;
	TXGUI::UIButton* m_equipmentWeaponButton;
	TXGUI::UIButton* m_equipmentArmorButton;
	TXGUI::UIButton* m_equipmentRingButton;
	TXGUI::UIButton* m_equipmentShoeButton;
	SpriteSeer* m_showModle;
	CCSprite* m_playerExpLable;
    //ShopUILayer* m_pShopUILayer;
};

#endif