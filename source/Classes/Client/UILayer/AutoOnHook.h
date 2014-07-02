//
//  AutoOnHook.h
//  HelloLua
//
//  Created by rickycheng  on 13-5-20.
//
//

#ifndef HelloLua_AutoOnHook_h
#define HelloLua_AutoOnHook_h

#include "AspriteManager.h"
#include "cocos2d.h"
#include "UIButton.h"
#include "UILayout.h"
#include "TXGUIHeader.h"
#include "InstanceManager.h"

using namespace std;
using namespace cocos2d;

typedef struct _OnHookA2
{
    int mon_id;
    int mon_num;
}OnHookA2;

class AutoOnHook : public CCLayer
{
public:
	AutoOnHook();
	virtual ~AutoOnHook();
    
	CREATE_FUNC(AutoOnHook);
	virtual bool init();
    
    
public:
	virtual void setTouchEnabled(bool value);
    void startCD(int timeout);
    void setScrollist(const std::vector<OnHookA2>& onHooksA2);
    
    void sendCSABMonsterReq(unsigned int instance_id);
    void setItemIcon(int item_num, int item_id, unsigned int item_index);
    void setIconAllGet(int number_diamand, int number_coin, int number_exploit, int number_exp);

    void clearVecIDs();
    virtual void closeLayerCallBack(void);
	bool IsOnCloseLayerCallBack(void) {return m_bCloseLayerCallBack;}
    
    void setPictureAndWord(int instance_id);
    void hideCloseBtn();
    
    CC_SYNTHESIZE(int, m_musicTime, musicTime)
    CC_SYNTHESIZE(unsigned int, m_instanceId, instanceId)
    
private:
    void setFuBen(const char* fuBenName);
    void setFuBen(int frame, const char* fuBenName);
    void setScrollistH(const std::vector<std::string>& tiles);
    void setupIconButtons();

    void OnClose(CCObject *sender);
    void OnSpeedUpHook(CCObject* sender);
    void OnStopHook(CCObject* sender);
    void OnStartAutoHook(CCObject* sender);
    void onTapCancel(CCObject* sender);
	void onItemTapped(CCObject* sender);
    void OnMasterClickListItem(CCObject* sender);
    
    void OnClickTurn1(CCObject* sender);
    void OnClickTurn2(CCObject* sender);
    void OnClickTurn3(CCObject* sender);
    
    void OnConfirm(CCObject *sender);
    void OnCancle(CCObject *sender);

    
    void update(float dt);
    void setUpCDTime(const char* strtime);
    void setUpCDText(const char* strtxt);
    
    void setupTurns();
    void processVisibleCD(bool visible);
    
    void showSpriteParticleEffect(CCNode* parent,unsigned int id,CCPoint pt);
    void setIconAllGet(bool visible);
    
    void setDiamandTxt();
    void convertSecToMinute(int time);
    void showStartBtn(bool visible);
    void clearItemBtn();
    
    void freshBag();
protected:
    UIScrollList* m_pListV;
    UIScrollList* m_pListH;
    CCSprite* m_FuBenIcon;
    UILabelTTF* m_FuBenName;
    UILabelTTF* m_MasterFuBenName;
    
    UILabel* m_pLabelCDNumber;
    UILabel* m_pLabelCDText;
    UIPicture* m_pCDFrame;
    
    CCLayer* m_pIconButtonLayer;
    TXGUI::UILayout* m_pLayer;
    
    std::vector<IconButton*> m_pIconButtonList;
    std::vector<int> m_VecIDs;
    
    float m_dt;
    int m_cnt;
    
    int m_turnId;
    
    UIButton* m_pCloseBtn;
    
    UIButton* m_pStartBtn;
    UIButton* m_pSpeedUpBtn;
    UIButton* m_pStopBtn;
    
    UILabel* m_pStartLabel;
    UILabel* m_pSpeedupLabel;
    UILabel* m_pStopLabel;

    UIButton* m_pTurnBtn1;
    UIButton* m_pTurnBtn2;
    UIButton* m_pTurnBtn3;
    
    UILabel* m_pTurnText1;
    UILabel* m_pTurnText2;
    
    UILabel* m_pTurnSami1;
    UILabel* m_pTurnSami2;
    UILabel* m_pTurnSami3;
    
    UIPicture* m_pTurnFrame;
    bool m_bCloseLayerCallBack;
    
    bool m_bStopSel;
    
    TXGUI::UILayout* m_pUseDiamand;
    
    int m_num_diamand;
    int m_num_coin;
    int m_num_exploit;
    int m_num_exp;
};

#endif
