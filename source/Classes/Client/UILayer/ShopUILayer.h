//
//  ShopUILayer.h
//  HelloLua
//
//  Created by rickycheng  on 13-6-18.
//
//

#ifndef HelloLua_ShopUILayer_h
#define HelloLua_ShopUILayer_h

#include "AspriteManager.h"
#include "cocos2d.h"
#include "UIButton.h"
#include "UILayout.h"
#include "TXGUIHeader.h"
#include "InstanceManager.h"

using namespace std;
using namespace cocos2d;

typedef struct _shopItem
{
    int to_id;
    int to_num;
    int from_id;
    int from_num;
    
}shopItem;

class ShopUILayer : public CCLayer
{
public:
	ShopUILayer();
	virtual ~ShopUILayer();
    
	CREATE_FUNC(ShopUILayer);
	virtual bool init();
    
public:
    void sendShopList();
    void setupShopList(std::vector<shopItem>& shoplist);
    void setupIconButtons();
    void setItemIcon(int item_num, int item_id, unsigned int item_index);
    
	virtual void setTouchEnabled(bool value);
    virtual void closeLayerCallBack(void);
	bool IsOnCloseLayerCallBack(void) {return m_bCloseLayerCallBack;}
    
    
private:
    void showSpriteParticleEffect(CCNode* parent,unsigned int id,CCPoint pt);
    
    void OnClose(CCObject *sender);
    void onTapCancel(CCObject* sender);
	void onItemTapped(CCObject* sender);

private:
    TXGUI::UILayout* m_pLayer;
    CCLayer* m_pIconButtonLayer;
    bool m_bCloseLayerCallBack;
    
    std::vector<IconButton*> m_pIconButtonList;
    std::vector<int> m_VecIconIDs;

};

#endif
