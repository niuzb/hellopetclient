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
#ifndef ONLINE_NETWORK_MANAGER_H
#define ONLINE_NETWORK_MANAGER_H

#include "NetWorkUtil.h"
#include "cs_battle.pb.h"

#include "NetWorkConfigure.h"

#define __OUT_NETWORK__ 

//外网
#ifdef __OUT_NETWORK__
#	define		ONLINE_SERVER_IP		"115.28.224.139"
#	define		ONLINE_SERVER_PORT		7879
#else
// 内网
#	define		ONLINE_SERVER_IP		"10.1.1.155"
#	define		ONLINE_SERVER_PORT		30001
#endif


class OnlineNetworkManager : public NetWorkUtil
{
	friend class PPVEMessage;
    friend class PVPMessage;

public:

	static OnlineNetworkManager*	sShareInstance();
	static void Destroy();

	void			setServerIP(const uint32_t serverIP);
	void			setServerIP(const char *serverIP);
	void			setServerPort(const uint32_t serverPort);
	void			setServerSelect(bool isSelect);

	void	LostConnection2Server();

public:

	//------------------------------------------------------------------
	//				start socket connect to online server
	//------------------------------------------------------------------
	void			startConnect();

	//------------------------------------------------------------------
	//				player enter map message
	//------------------------------------------------------------------
	void			sendPlayerEnterMapMessage(int mapId, int xPos, int yPos,int orient);

	//------------------------------------------------------------------
	//				player leave map message
	//------------------------------------------------------------------
	void			sendPlayerLeaveMapMessage(int mapId);

	//------------------------------------------------------------------
	//				player walk message	
	//------------------------------------------------------------------
	void			sendPlayerMoveMessage(int xPos, int yPos, unsigned int animID, bool bFlip);
	void			sendPlayerBattleMoveMessage(unsigned int id, const cocos2d::CCPoint& pos, const cocos2d::CCPoint& direction, bool bEnd);

	//------------------------------------------------------------------
	//				attack
	//------------------------------------------------------------------
	void			sendPlayerAttackMessage(const CSPlayerAttackReq& attackReq);
	void			sendPlayerAttackOtherPlayerMessage(const CSPlayerHitPlayerReq& attackReq);
	void			sendSkillBeginMessage(const CSSkillBeginReq& req);

	//------------------------------------------------------------------
	//				send get other players message	
	//------------------------------------------------------------------
	void			sendGetOtherPlayersMessage();

	//------------------------------------------------------------------
	//				send get player items message	
	//------------------------------------------------------------------
	void			sendGetPlayerItemsMessage();

	//------------------------------------------------------------------
	//				send use player normal item message	
	//------------------------------------------------------------------
	void			sendUseNormalItemMessage(uint64_t id, uint32_t item_id, int count = 1);

	//------------------------------------------------------------------
	//				send use player sprite item message	
	//------------------------------------------------------------------
	void			sendUseMonsterItemMessage(  uint64_t id, 
												uint32_t item_id, 
												std::string spUUID, 
												int count = 1);

	//------------------------------------------------------------------
	//				send drop items message	
	//------------------------------------------------------------------
	void			sendDropItemsMessage(uint64_t id, uint32_t item_id, int count);

	//------------------------------------------------------------------
	//				send player change nick message	
	//------------------------------------------------------------------
	void			sendPlayerChangeNickMessage(std::string newNick);

	//------------------------------------------------------------------
	//				send send mail message	
	//------------------------------------------------------------------
	void			sendSendMailMessage(uint32_t receiver_id, 
										int32_t receiver_role_tm, 
										std::string mail_title, 
										std::string mail_content);

	//------------------------------------------------------------------
	//				send get mail head list message	
	//------------------------------------------------------------------
	void			sendGetMailHeadListMessage();

	//------------------------------------------------------------------
	//				send get mail body message	
	//------------------------------------------------------------------
	void			sendGetMailBodyMessage(uint64_t mail_id);

	//------------------------------------------------------------------
	//				send delete mail message	
	//------------------------------------------------------------------
	void			sendDeleteMailMessage(uint64_t mail_id);

	//------------------------------------------------------------------
	//				send get mail enclosure message	
	//------------------------------------------------------------------
	void			sendGetMailEnclosureMessage(uint64_t mail_id);

	//------------------------------------------------------------------
	//				quest related message	
	//------------------------------------------------------------------
	void			sendObtainTaskMessage(uint32_t task_id);
	void			sendCancelTaskMessage(uint32_t task_id);
	void			sendFinishTaskMessage(uint32_t task_id);
	void			sendGetTaskFlagListMessage(uint32_t task_id);
	void			sendGetTaskFlagListMessage(std::set<uint32_t> &task_id_set);
	void			sendGetTaskBuffListMessage(uint32_t task_id);
	void			sendGetTaskBuffListMessage(std::set<uint32_t> &task_id_set);
	void			sendGetTaskListMessage();
	void			sendSetTaskStepMessage(uint32_t task_id, uint32_t step);
	void			sendGetInstanceListMessage(uint32_t start, uint32_t end);


	//------------------------------------------------------------------
	//				login related message	
	//------------------------------------------------------------------
	void			sendCheckSessionMessage();
	void			sendCreateRoleMessage(const std::string &nick, const uint32_t type);
	void			sendLoginMessage();
	void			sendLogoutMessage();
	void			sendBattleCreateMessage(int battleId, int mapId);

	void			sendLoadCompleteMessage();
	void			sendLeaveBattleReqMessage();
	//////////////////////////////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------
	//				battle with wild monster 
	//------------------------------------------------------------------
	// @param -mapID , current map id 
	void			battleWithWildMon(uint32_t mapID);
	void			battleFinishLoading();
	void			sendUseSkill(const uint32_t skillId);
    void            sendSwitchBattleSprite(const char *spriteUUID);
    void            sendRunawayFromBattle();

	////			items
	void			sendBackPackMessage();
	void			sendBackPackMove(unsigned int from,unsigned int to);
	void			sendBackPackReOrder(unsigned int type);
	void			sendBackPackRemoveItem(unsigned int pos,unsigned int itemId);
	// 使用物品(礼包 ...)	
	void			sendUseItem(unsigned int pos, unsigned int itemId);
	void			sendEquipComposeReq(unsigned int exchangeId,unsigned int pos,unsigned int multi = 1);
	void			sendItemExchangeReq(unsigned int exchangeId,unsigned int pos[],int length);
	void			sendElfExchangeReq(unsigned int exchangeItemId);
	void			sentEquipUpgradeMessage();
	void			sentEquipUpgradeStrength(unsigned int pos);
	void			sendFindSoulStoneMessage();
	void			sendSoulStoneToStorage(unsigned int pos);
	void			sendUpgradeSoulStone(unsigned int pos);
	void			sendTranStoneToEnergy(bool isAll,unsigned int pos = 0);
	void			sendSpriteExchangeMessage();
	
	//宝石镶嵌
	void			sendEquipInlayGemReq(unsigned int equip,unsigned int hole,unsigned int gemId);			// 宝石镶嵌请求
	void			sendGemRecastReq(unsigned int equip,unsigned int holes[],unsigned int holeNum,unsigned int key);	//宝石重铸请求
	void			sendExchangeParameterReq(unsigned int exchangeId,unsigned int param = 0);					// 钻石系统协议

	////		    sever
	void			sendQueryShardReq();

	///				Attributes
	void			sendAttributesReq(int attributes[],int length);
	void			sendUserInfoReq(unsigned int id);
	/// <summary>
	//	Task 请求相关的协议
	/// </summary>
	/**
	* Instruction : 请求任务信息列表
	* @param 
	*/	
	void			sendRqsTaskInfoMessage();
	/**
	* Instruction : 请求获得任务Log
	* @param 
	*/
	void			sendRqsTaskLogMessage();
	/**
	* Instruction : 向服务器发送某一个任务步骤
	* @param 
	*/	
	void			sendRqsTaskDoStepMessage(unsigned int task_id,unsigned int step_id,unsigned int step_value);
	/**
	* Instruction : 
	* @param 
	*/
	void			sendReqNetStateMessage();

	// Note: 精灵相关协议
	/**
	* Instruction : 获取英雄精灵
	* @param 
	*/
	void			sendReqOneHeroElfMessage(unsigned int roleId,const char* roleName);
	/**
	* Instruction : 设置精灵的状态信息
	* @param 
	*/
	void			sendReqSetElfStateMessage(unsigned int elfId,unsigned int state);

	// Note: 设置协议
	void			sendOnceSetReqMessage(unsigned int index);
	void			sendOnceReqMessage(int indexs[],int length);
	void			sendOnceReqMessage(std::vector<int> &vec);
	void			sendOnceReqMessage(std::map<unsigned int,bool> &map,unsigned int attachValue);

	// Note: 技能UI协议
	void			sendGetUserSkillReqMessage(unsigned int roleId);
	void			sendAddUserSkillReqMessage(unsigned int skillId,unsigned int levelId);
	void			sendUserSkillDiffReqMessage(unsigned int skillId,unsigned int levelId);
	void			sendGetSlotReqMessage();
	void			sendSetSlotAttributeMessage(unsigned int slotIndex,unsigned skillId);

	// Note: 精灵唤醒相关协议
	void SendElfAwakeMessage(unsigned int awakeType);
	void SendAwakeConfigMessage();

	// Note: 精灵探索协议
	void SendExploreReq(unsigned int type);
	void SendExploreDetermineReq(unsigned int optionId);

	// Note: 玩家删除账号信息协议
	void SendDelRoleReqMessage();

	// Note: PvAI 相关协议
	void sendPvAIReq(unsigned int userId);

	void sendPvAIInfoReq();
protected:

	OnlineNetworkManager();
	~OnlineNetworkManager();	

protected:

	void			onConnectResult(KSocketStatus status, int tag);
	void			onSockectError(KSocketError error, int tag);
	void			onTimeOut(std::string cmd,int tag);

	void   TestEcho();

private:

	static OnlineNetworkManager*						sInstance;

	const char *										m_serverIP;
	uint32_t											m_serverPort;
	bool												m_bserverSelect;
};



#endif