// TAOMEE GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Taomee Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 2012-2015 Taomee Game Technologies. 
//      All Rights Reserved.
//
// Taomee Game Technologies, Shanghai, China
// http://www.taomee.com
//

#pragma once

#include "ILogicManager.h"
#include "SceneLayer.h"
#include "errcode.pb.h"
#include "cs_battle.pb.h"
#include "cocos2d.h"

#include "TXGUIHeader.h"
#include "IEvent.h"


using namespace cocos2d;




/*
* @XLogicManager, 	
@/// 逻辑面板的管理器，负责切换到不同的核心游戏模块, 这些模块以游戏步骤为依据进行切分
*
*/
class XLogicManager : 
	public CCNode, 
	public ILogicManager , 
	public TXGUI::ObserverProtocol,
    public ISocketEvent
{
public:
	/// 逻辑面板的枚举变量类型
	typedef enum  
	{
		E_NOE          = 0,
		E_SELECT_ZONE  = 1,		//选择服务器分区功能面板
		E_CREATE_PLAYER_LAYER ,	//创建玩家面板
		E_SELECT_CHARACTER ,    //角色选择界面步骤
		E_MAIN_GAME_LAYER ,		//开始游戏面板
		E_GAME_HELP_LAYER ,		//帮助面板等
		E_PVP_LAYER ,	//pvp战斗面板
		E_PVE_LAYER,	//pve副本面板
		E_TASK_PANEL_LAYER ,

		// add more...

	}GAME_LOGIC_LAYER;

	typedef enum
	{
		E_WAITIN_FOR_COMMOND = 0, // 空闲状态
		E_SENDING_SEVER = 1,	// 已经发送登录/进副本/回主城协议包去服务器，等待回包，不接收类似的操作
	}LOGIC_CHANGE_LAYER_STATUS;

	typedef void (*errFun)(db_errcode_t); 

public:
	XLogicManager();
	virtual ~XLogicManager();

	void  updateFps(float dt);

	void  updateNetChecker(float dt);

	void  WillEnterForeground();

	void  DidEnterBackground();

	//////////////////////////////////////////////////////////////////////////
		/// implement the interface of ILogicManager
	/*
	* @prototype: goToFrontend()
	* @note:
	*     bring the game to the front of the screen. prepare the resources and init all the game components.
	* @param: void
	* @return: void
	*/
	virtual void goToFrontend();

		
	/*
	* @prototype: startGame()
	* @note:
	*     start the game now, bring the player to the hometown.
	* @param: void
	* @return: void
	*/
	virtual void startGame();
	virtual void exitGame();

	// static instance
	static XLogicManager* sharedManager();

	// functions
	// go to a specific scene
	void  goToLayer(GAME_LOGIC_LAYER sceneTag, void *userData = NULL); 

	void connectToServer();

	void onConnectToSever();

	int getLoginStep();

	void logIn();

	void logInError(db_errcode_t error);

	void logOut();

	void networkDisConnected();

	void registerNetErrFun(errFun fun) { pNetErrFun = fun; }

	void unRegisterNetErrFun() {  pNetErrFun = NULL;  }

	void createRole(const std::string nick, const unsigned int type);

	void goToFb(unsigned int mapId, unsigned int battleId);

	void backToTown();

	void LeaveBattle();

	void FinishBattle();

	void createBattle(int battleId, int mapId);

	void changeMap(int mapId, KMapFromType fromMapType);

	void receivedItemsInfo();

	// 游戏启动时向服务器请求必要的信息
	void initUserInfoFromSever(float time);

	db_errcode_t getNetErrorCode();

	void reqPlayerAttributes(int attributeId);

	void reqPlayerAttributes(int attributes[],int length);

	void reqAllPlayerAttributes();

	bool isAlreadyLogin();
	void loginSuccess();
protected:

	/// on messagebox network error!
	void OnNetworkMessageOK(CCObject* pObject);


	/// 消息响应函数
	virtual void onBroadcastMessage(BroadcastMessage* msg);
    
    /// override ISocketEvent
	virtual void OnSocketError(int nError);
	virtual void OnConnected(int nResult);
	virtual void OnDisconnect();

protected:
	GAME_LOGIC_LAYER  m_eCurLayer;
	LOGIC_CHANGE_LAYER_STATUS  m_eCurStatus;
	int m_loginStep;
	errFun pNetErrFun;
	db_errcode_t mErrorCode;
	bool isGameStart;
	bool isRequiredItemsInfo;
	float	m_loginDataTime;
	bool	isInitLoginData;
	bool	b_isLoginGame;
	//// time ticked when application move to background
	long long   m_LastEnterBackgroundTime; 
};

extern "C"{

	extern void playerlogOut();
}