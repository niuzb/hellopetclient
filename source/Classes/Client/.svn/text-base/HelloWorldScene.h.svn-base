#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "CArmature.h"
#include "FrontCoverLayer.h"
#include "errcode.pb.h"
#include "UIMessageLayer.h"
using namespace cocos2d;

enum MoveType{NOTHING, MOVELEFT = -1, MOVERIGHT = 1, STAND, SQUAT, JUMP};

#define TAG_HELLOWORLD    1000


class HelloWorld : public cocos2d::CCLayerColor
{
public:
	HelloWorld();
	virtual ~HelloWorld();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
 

    // implement the "static node()" method manually
	CREATE_FUNC(HelloWorld);
	void update(float dt);

	void draw();

	void receiveNetWorkError(db_errcode_t error);

	void enterCreateRoleLayer();

	void showMessage(const char* msg);

	FrontCoverLayer* getFrontLayer();
	//void menuLoginGameCallback(CCObject* pSender);

	//void menuLogOutCallback(CCObject* pSender);

	//void ReadyToLogin(); // 连接无线平台成功,准备连接后台服务器

	//void onConnectToSuccess(); // 连接服务器成功

	//virtual void	ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);	
	//virtual void keyBackClicked();//监听Android 返回键
	//virtual void keyMenuClicked();//监听Android 菜单键
	//void OkBtnClick(CCObject* obj);
	//void CancelBtnClick(CCObject* obj);	
private:
	bool left;
	bool right;
	bool down;
	CCMenuItemImage *pLoginItem;
	CCLabelTTF* pLabel;
	CCMenuItemImage *logOutItem;
	FrontCoverLayer* pFrontLayer;
	UIMessageLayer* pUIMessageLayer;
};

#endif  // __HELLOWORLD_SCENE_H__