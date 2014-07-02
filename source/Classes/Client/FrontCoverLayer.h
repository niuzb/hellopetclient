#ifndef FRONT_COVER_LAYER_H
#define FRONT_COVER_LAYER_H

#include "cocos2d.h"
#include "TXGUIHeader.h"
#include "cs_basic.pb.h"
#include <vector>
using namespace std;
using namespace cocos2d;

#include "IEvent.h"

class SeverInfo
{
public:
	char name[30];
	char severIp[30];
	unsigned int port;
	unsigned int online;
	unsigned int newSever;
};

class FrontCoverLayer :
	public cocos2d::CCLayer, 
	public ISocketEvent
{
public:
	FrontCoverLayer();
	virtual ~FrontCoverLayer();

	CREATE_FUNC(FrontCoverLayer);
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	void menuLoginGameCallback(CCObject* pSender);
    
	void menuLogOutCallback(CCObject* pSender);

	void onClickedMoreSever(CCObject* pSender);

	void onCLickedSeverCloseBt(CCObject* pSender);
	
	void onClickedOneSever(CCObject* pSender);

	void onClickedLatestSever(CCObject* pSender);

	void update(float dt);

	void ReadyToLogin(); // 连接无线平台成功,准备连接后台服务器
    
	void onReceiveSeverInfo(CSQueryShardRsp* rsp);

	/// override ISocketEvent
	virtual void OnSocketError(int nError);
	virtual void OnConnected(int nResult);
	virtual void OnDisconnect();
    
protected:
	virtual void keyBackClicked();//监听Android 返回键
	virtual void keyMenuClicked();//监听Android 菜单键

	void OkBtnClick(CCObject* obj);
	void CancelBtnClick(CCObject* obj);	


    void readyLogin_func(float dt);
    void showmsg(const char* msg);
    void processLoadTime();
private:

	void addNewSever();
	void clearSeverList();
	void setLastLoginSever();
	void setLastServerLabel();
private:
	CCMenuItemImage *pLoginItem;
	CCMenuItemImage *logOutItem;
    
    CCLabelTTF * _downloadTTF;
    CCProgressTimer* _downloadBar;
    CCSprite* _barFrame;
    CCLabelTTF*	m_visionLabel;

    double m_accumulator;
    double m_lastTickTime;

	SeverInfo* m_selectedSever;
	std::vector<SeverInfo*> m_severList;
	UIScrollPage* m_severScrollPage;
	std::vector<IconButton*> m_lstButton;
	UILayout* m_layout;
};

#endif