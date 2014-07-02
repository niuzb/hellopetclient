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
#ifndef MESSAGE_HANDER_H
#define MESSAGE_HANDER_H


#include <map>
#include <string>

using namespace std;


#include "message.h"

#include "BaseMsgHandler.h"

class BaseMsgHandler;
//------------------------------------------------------------------------
//				message handler
//------------------------------------------------------------------------

class MessageHandler
{
	friend class PPVEMessage;
    friend class PVPMessage;

public:

	static MessageHandler*			sShareInstance();
	static void Destroy();


	//------------------------------------------------------------------------
	//				handle message
	//------------------------------------------------------------------------
	void							handleMessage(NORMAL_MSG_PACKAGE* package);
	void							handleMessage(WILD_MSG_PACKAGE* package);

	//------------------------------------------------------------------------
	//				only valid at cur frame
	//------------------------------------------------------------------------
	WILD_MSG_PACKAGE*				getWildMsgPackage()			{return mCurWildMsgPackage;}


protected:

	MessageHandler();
	~MessageHandler();

	//------------------------------------------------------------------------
	//				deal with message
	//------------------------------------------------------------------------
	void							registerMessageHandlerFunction();
	/// register external message handler
	void  registerExternalMsgHandler();

	//
	typedef void					(MessageHandler::*handlerFunc)();

	//------------------------------------------------------------------------
	//				handler function
	//------------------------------------------------------------------------
	

	//
	void							postHandleMsg();

	//------------------------------------------------------------------------
	//				handler all message error
	//------------------------------------------------------------------------	
	void							handleMsgError();

	//
	void							handleMsgPlayerEnterMap();
	//
	void							handleMsgPlayerLeaveMap();
	//
	void							handleMsgPlayerWalk();
	//
	void							handleMsgGetOtherPlayers();
	//
	void							handleMsgBattleCreate();

	void							handleMsgMonsterMove();	

	void							handleMsgMonsterAttack();

	void							handleMsgMonsterDie();

	void							handleMsgInstanceList();

	// login related
	void							handleMsgLoginIn();
	void							handleAckMsgCheckSession();
	void							handleAckMsgCreateRole();
	void							handleQuerySharedRsp();

	void							handleMsgMonsterHit();
	void							handleMsgPlayerAttackMonster();
	void							handleLeaveBattle();

	// Item related
	void							handleBackPackItems();
	void							handleAddItem();
	void							handleBackPackMove();
	void							handleBackPackItemRemove();
	void							handleBackPackItemUpdate();
	void							handleEquipnetList();
	void							handleEquipmentStrength();
	void							handleEquipCompose();

	// 宝石镶嵌
	void							handleEquipInlayGemRsp();
	void							handleGemRecastRsp();

	// diamond
	void							handleExchangeParameterRsp();

	// attributes

	void							handleAttributesRsp();
	void							handleLevelUpRsp();
	void							handleUserInfoRsp();

	void							handleSearchSpriteStoneRsp();
	void							handleSpriteStoneMoveStorageRsp();
	void							handleSpriteUpgradeRsp();
	void							handleSpriteTransToEnergy();
	void							handleSpriteExchangeRsp();
	////////////////////////////////////////////////////////////////////////
	//add more later : battle server message

    
	//  These function to handle response message of PVE request from client
	void		handleMsgBattlePVE();

	// These function to handle echo message received from battle server
	void        handleMsgEcho();

	void	setNeedShowPPVEAfterBacktoTown(bool bShowPPve);

	void	checkNeedShowPPVEPanel();

	/// <summary>
	//	Task related
	/// </summary>
	// Note: 请求任务数据 回复
	void							handleRsqTaskInfoMessage();
	// Note: 请求任务Log 回复
	void							handleRsqTaskLogMessage();
	// Note: 设置任务步骤 回复
	void							handleRsqTaskStepMessage();

	void							handleRsqNetStateMessage();

	/// <summary>
	//	精灵相关
	/// </summary>
	/**
	* Instruction : 获取精灵信息回包
	* @param 
	*/	
	void							handleRsqElfListMessage();
	/**
	* Instruction : 获取设置精灵状态回包
	* @param 
	*/
	void							handleRsqElfStateMessage();

	//多人副本
	void							handleMsgUserJoin();
	void							handleMsgUserLeave();
	void							handleMsgBattleMove();
	void							handlePlayerAttack();
	void							handleSkillBegin();

	// PVP
	void							handlePVPPlayerHitPlayer();

	void							handleOnceRspMessage();

	void							handleMsgLoadComplete();

	void							handleMsgBattleTimeout();
	void							handleMsgPlayerDie();
	void							handleMsgPlayerHP();

	//Skill UI
	void							handleMsgGetUserSkillRsp();
	void							handleMsgUserSkillDiffRsp();
	void							handleMsgAddUserSkillRsp();

	// Note: 
	void							handleMsgTrainRsp();
	void							handleMsgTrainDetermineRsp();

	// Note: 精灵探索系统
	void							handleExploreRsp();
	void							handleExploreDetermineRsp();

	//防守
	void							handleMsgBattleMonsterCreateRsp();
	
	void							handleNotifyMoneyConfigInfo();

	// pvai
	void							handleMsgPvAIInfoRsq();
protected:

	static MessageHandler*			sInstance;

	WILD_MSG_PACKAGE*				mCurWildMsgPackage;
	NORMAL_MSG_PACKAGE*				mCurNormMsgPackage;

	typedef std::map<std::string, handlerFunc> HANDLER_FUNCTION_LIST;
	HANDLER_FUNCTION_LIST			mCmd2HandlerFunctionList;

	/// external handlers, handle extra message which defined in other source code file
	map<std::string, BaseMsgHandler*> mExternalHandler;

	/// ppve panel show flag
	bool	m_bShowPPVEPanel;
};



#endif