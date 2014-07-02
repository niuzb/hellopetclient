#ifndef EQUIPMENT_UPGRADE_UILAYER_H
#define EQUIPMENT_UPGRADE_UILAYER_H

#include "cocos2d.h"
#include "TXGUIHeader.h"
using namespace cocos2d;
using namespace TXGUI;
class EquipmentUpgradeUILayer : public cocos2d::CCLayer,
								public TXGUI::ObserverProtocol
{
public:
	EquipmentUpgradeUILayer();
	virtual ~EquipmentUpgradeUILayer();

	CREATE_FUNC(EquipmentUpgradeUILayer);
	virtual bool init();

public:
	void closeEquipUpgradeBt(CCObject* sender);
	void chooseOneEquipmentBt(CCObject* sender);
	void onClickHeroEquip(CCObject* sender);
	void onClickFairyEquip(CCObject* sender);
	void onClickStrength(CCObject* sender);
	static unsigned int GetUpgradeColdTime();
	void setUpgradeColdTime(unsigned int value);
	void successToStrength(unsigned int pos,unsigned int coldTime);
	void updateColdTime(float time);

	virtual void closeLayerCallBack(void);
protected:
	/// 消息响应函数
	virtual void onBroadcastMessage(BroadcastMessage* msg);
private:
	void setDefaultSelectedEquip();
	void showPlayerEquipment();
	void showFairyEquipment();
	CCSprite* getIconSpriteById(unsigned int ItemId);
	TXGUI::UIPicture* getEquipmentPic(int index);
	TXGUI::UIButton* getEquipmentButton(int index);
	CCSprite* getIconFrame(unsigned int level);
	void setChoosedEquipment(unsigned int index);
	void showLevelUpCost(unsigned int cost);
	void showColdTime(unsigned int time);
	void showCurrentLevel(unsigned int level);
	void showCurrentName(const char* name,const ccColor3B& color = ccWHITE);
	void showCurrentAttribute(unsigned int key,unsigned int basicValue,unsigned int strenghValue);
	void showCurrentAttributeLabel(const char* text);
	void showSecondAttribute(unsigned int key,unsigned int basicValue,unsigned int strenghValue);
	void showSecondAttributeLabel(const char* text);
	void unSelectChoosedEquip();
	void showEquipLevel(unsigned int index,unsigned int level);
	void showEquipName(unsigned int index,const char* name,const ccColor3B& color = ccWHITE);
	void showNextLevelAttribution(unsigned int key,unsigned int strenghValue);
	void showSecondNextLevelAttribution(unsigned int key,unsigned int strenghValue);
	void showSecondNextLevelAttributionLabel(const char* text);
	void showSingleEquip(unsigned int pos,unsigned int index);
	void showLvUpRemainTimes();
	bool checkLvUp();
	void updateBottomDiamondLabel();
	void updateBottomCoinLabel();
	void playUpgradeEffect();
private:
	UILayout* m_equipmentLayout;
	UIPicture* m_equipmentHelmetPic;
	UIPicture* m_equipmentNecklacePic;
	UIPicture* m_equipmentWeaponPic;
	UIPicture* m_equipmentArmorPic;
	UIPicture* m_equipmentRingPic;
	UIPicture* m_equipmentShoePic;
	UIButtonToggle* m_heroEquipToggle;
	UIButtonToggle* m_fairyEquipToggle;
	UIPicture* m_choosedEquipmentPic;
	TXGUI::UIButton* m_choosedEquipBt;
	UILabel* m_levelUpCostLabel;
	UILabel* m_coldTimeLabel;
	UILabel* m_levelLabel;
	unsigned int m_choosedEquipIndex;
	bool m_equipLayoutIndex; // 装备列表显示的是玩家或者精灵的标签: true 玩家, false 精灵
	CCSprite* m_upTimesBar;
};

long long millisecondNow();
#endif