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
#include "OnlineNetworkManager.h"
#include "cmdDefine.h"
#include "UserData.h"
#include "cs_basic.pb.h"
#include "cs_core.pb.h"
#include "cs_battle.pb.h"
#include "LevelManager.h"

#include "PPVEMessage.h"
#include "PVPMessage.h"
#include "NetStateChecker.h"
#include "MessageFilter.h"
#include "UserData.h"


OnlineNetworkManager* OnlineNetworkManager::sInstance = NULL;

#ifdef WIN32
	const float PKG_TIMEOUT = 30.0f;
#else
	const float PKG_TIMEOUT = 60.0f;
#endif


OnlineNetworkManager* OnlineNetworkManager::sShareInstance()
{
	if (sInstance == NULL)
	{
		sInstance = new OnlineNetworkManager();
	}

	return sInstance;
}

void OnlineNetworkManager::Destroy()
{
	if (sInstance )
	{
		delete sInstance;
		sInstance = NULL;
	}
}



OnlineNetworkManager::OnlineNetworkManager()
{
	m_serverIP = ONLINE_SERVER_IP;
	m_serverPort = ONLINE_SERVER_PORT;
	m_bserverSelect = false;
	/// init ppve message handler
	PPVEMessage::Create();
    PVPMessage::Create();

	MessageFilter::Create();
}



OnlineNetworkManager::~OnlineNetworkManager()
{
	/// destroy message filter
	MessageFilter::Destroy();

	/// uninit ppve message handler
	PPVEMessage::Destroy();
    PVPMessage::Destroy();

	NetStateChecker::Destroy();

}

//------------------------------------------------------------------
//				events
//------------------------------------------------------------------
void OnlineNetworkManager::LostConnection2Server()
{
	this->onConnectResult(KSocketTimeout, 0);
}

void OnlineNetworkManager::onConnectResult(KSocketStatus status, int tag)
{
	NetWorkUtil::onConnectResult(status, tag);	
	CCLog("OnlineNetworkManager::onConnectResult: %d,%d",status,tag);
	if(status == KSocketConnecting)
	{
		if(m_bserverSelect)
		{
			sendQueryShardReq();
		}
		else
		{
			sendLoginMessage();
		}
	}
}


void OnlineNetworkManager::onSockectError(KSocketError error, int tag)
{
	NetWorkUtil::onSockectError(error, tag);
	CCLog("OnlineNetworkManager::onSockectError: %d,%d",error,tag);
	//
	FireEvent(&ISocketEvent::OnSocketError, (int)error);
}

void OnlineNetworkManager::onTimeOut(std::string cmd,int tag)
{
	NetWorkUtil::onTimeOut(cmd, tag);

	//
	if (tag == NETWORK_TAG_CONNECT)
		NetWorkUtil::cleanServerConnect(true);
	
}

void OnlineNetworkManager::setServerIP(const uint32_t serverIP)
{
	in_addr tmpInAddr;
	tmpInAddr.s_addr = serverIP;
	m_serverIP = inet_ntoa(tmpInAddr);
}

void OnlineNetworkManager::setServerIP(const char *serverIP)
{
	//m_serverIP = serverIP;
}

void OnlineNetworkManager::setServerPort(const uint32_t serverPort)
{
	//m_serverPort = serverPort;
}

void OnlineNetworkManager::setServerSelect(bool isSelect)
{
//jackniu	m_bserverSelect = isSelect;
    m_bserverSelect=false;
}

//------------------------------------------------------------------
//				gameLogic
//------------------------------------------------------------------
void OnlineNetworkManager::startConnect()
{
	CCLog("server IP: %s", m_serverIP);
	CCLog("server port: %u", m_serverPort);
	NetWorkUtil::connect2Server(m_serverIP, m_serverPort, 2, NETWORK_TAG_CONNECT);	
}

//------------------------------------------------------------------
void OnlineNetworkManager::sendBattleCreateMessage(int battleId, int mapId)
{
	CCLog("sendBattleCreateMessage()");
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSBattleCreateReq");
	CSBattleCreateReq* bodyMsg = (CSBattleCreateReq*)msg;
	bodyMsg->set_battle_id(battleId);
	bodyMsg->set_map_id(mapId);
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_BATTLE_CREATE, true, true);
}

//------------------------------------------------------------------
void OnlineNetworkManager::sendLoginMessage()
{
	CCLog("sendLoginMessage()");
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSLoginReq");
	CSLoginReq* bodyMsg = (CSLoginReq*)msg;
	char cSession[SESSION_LENGTH];
	memcpy(cSession, UserData::getUserSession(), SESSION_LENGTH);
	bodyMsg->set_sid(cSession, SESSION_LENGTH);
	bodyMsg->set_uid(UserData::getUserId());
	NetWorkUtil::sendMessage(bodyMsg, 120.0f, NETWORK_TAG_LOGIN, true, true);
}


//------------------------------------------------------------------
void OnlineNetworkManager::sendLogoutMessage()
{
	CCLog("sendLogoutMessage()");
	// currently simply disconnect to online server and set ip and port to login server
	this->cleanServerConnect(false);
	//this->setServerIP(ONLINE_SERVER_IP);
	//this->setServerPort(ONLINE_SERVER_PORT);
}


//------------------------------------------------------------------
void OnlineNetworkManager::sendPlayerEnterMapMessage(int mapId, int xPos, int yPos,int orient)
{
	CCLog("CSEnterMapReq()");
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSEnterMapReq");
	CSEnterMapReq* bodyMsg = (CSEnterMapReq*)msg;
	bodyMsg->set_mapid(mapId);
	bodyMsg->set_xpos(xPos);
	bodyMsg->set_ypos(yPos);
	bodyMsg->set_orient(orient);
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_PLAYER_ENTER_MAP, true, true);
}

//------------------------------------------------------------------
void OnlineNetworkManager::sendPlayerLeaveMapMessage(int mapId)
{
	//Message* msg = MessageUtil::sShareInstance()->createMessageInstance("iAdCSProto.player_leave_map_req_t");
	//player_leave_map_req_t* bodyMsg = (player_leave_map_req_t*)msg;
	//bodyMsg->set_map_id(mapId);	

	//NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_PLAYER_LEAVE_MAP, true, true);
}


//------------------------------------------------------------------
void OnlineNetworkManager::sendPlayerMoveMessage(int xPos, int yPos, unsigned int animID, bool bFlip)
{
	CCLog("sendPlayerMoveMessage()");
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSWalkReq");
	CSWalkReq* bodyMsg = (CSWalkReq*)msg;
	bodyMsg->set_xpos(xPos);
	bodyMsg->set_ypos(yPos);
	bodyMsg->set_animid(animID);
	bodyMsg->set_flip(bFlip);

	//don't cache the walk message if failed
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_PLAYER_WALK, false, true);
}

//------------------------------------------------------------------
void OnlineNetworkManager::sendPlayerBattleMoveMessage(unsigned int id, const cocos2d::CCPoint& pos, const cocos2d::CCPoint& direction, bool bEnd)
{
	static Machtimer machTimer;

	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSBattleMoveReq");
	CSBattleMoveReq* bodyMsg = (CSBattleMoveReq*)msg;
	bodyMsg->set_id(id);
	CSPoint* pPos = bodyMsg->mutable_pos();
	cocos2d::CCPoint phyPos = LevelManager::sShareInstance()->pointPixelToCell(pos);
	pPos->set_xpos(phyPos.x);
	pPos->set_ypos(phyPos.y);
	CSPoint* pDir = bodyMsg->mutable_direct();
	pDir->set_xpos((int)direction.x);
	pDir->set_ypos((int)direction.y);

	if(bEnd)
	{
		bodyMsg->set_time(-1);
	}
	else
	{
		bodyMsg->set_time(machTimer.elapsedMS());
	}
	

	//don't cache the walk message if failed
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_PLAYER_BATTLE_MOVE, true, true);
	//CCLog("Send Move(%f, %f) time : %ld", phyPos.x, phyPos.y, machTimer.elapsedMS());
	machTimer.start();
}

//------------------------------------------------------------------
void OnlineNetworkManager::sendPlayerAttackMessage(const CSPlayerAttackReq& attackReq)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSPlayerAttackReq");
	CSPlayerAttackReq* bodyMsg = (CSPlayerAttackReq*)msg;
	*bodyMsg = attackReq;
	
	KSendMessageResult result = NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_PLAYER_ATTACK, true, true);
}

//------------------------------------------------------------------
void OnlineNetworkManager::sendPlayerAttackOtherPlayerMessage(const CSPlayerHitPlayerReq& attackReq)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSPlayerHitPlayerReq");
	CSPlayerHitPlayerReq* bodyMsg = (CSPlayerHitPlayerReq*)msg;
	*bodyMsg = attackReq;

	KSendMessageResult result = NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_PLAYER_ATTACK, true, true);
}


//------------------------------------------------------------------
void OnlineNetworkManager::sendGetOtherPlayersMessage()
{
	CCLog("sendGetOtherPlayersMessage()");
	Message* msg = 
		MessageUtil::sShareInstance()->createMessageInstance("CSGetMapUsersReq");
	CSGetMapUsersReq* bodyMsg = (CSGetMapUsersReq*)msg;

	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_GET_OTHER_PLAYERS, true, true);
}

//------------------------------------------------------------------
void OnlineNetworkManager::sendGetPlayerItemsMessage()
{
	//Message* msg = 
	//	MessageUtil::sShareInstance()->createMessageInstance("iAdCSProto.get_player_items_req_t");
	//get_player_items_req_t* bodyMsg = (get_player_items_req_t*)msg;

	//NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_GET_PLAYER_ITEMS, true, true);
}


//------------------------------------------------------------------
void OnlineNetworkManager::sendUseNormalItemMessage(uint64_t id, uint32_t item_id, int count /* = 1 */)
{
	//Message* msg = MessageUtil::sShareInstance()->createMessageInstance("iAdCSProto.use_normal_item_req_t");
	//use_normal_item_req_t *bodyMsg = (use_normal_item_req_t*)msg;
	//bodyMsg->set_id(id);
	//bodyMsg->set_item_id(item_id);
	//bodyMsg->set_item_count(count);

	//NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_USE_NORMAL_ITEM, true, true);
}


//------------------------------------------------------------------
void OnlineNetworkManager::sendUseMonsterItemMessage(uint64_t id, uint32_t item_id, std::string spUUID, int count /* = 1 */)
{
	//Message* msg = MessageUtil::sShareInstance()->createMessageInstance("iAdCSProto.use_monster_item_req_t");
	//use_monster_item_req_t *bodyMsg = (use_monster_item_req_t*)msg;
	//bodyMsg->set_id(id);
	//bodyMsg->set_item_id(item_id);
	//bodyMsg->set_monster_uuid(spUUID);
	//bodyMsg->set_item_count(count);

 //   NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_USE_MONSTER_ITEM, true, true);
}

//------------------------------------------------------------------
void OnlineNetworkManager::sendDropItemsMessage(uint64_t id, uint32_t item_id, int count)
{
	//Message* msg = MessageUtil::sShareInstance()->createMessageInstance("iAdCSProto.cli_drop_items_req_t");
	//cli_drop_items_req_t* bodyMsg = (cli_drop_items_req_t*)msg;
	//bodyMsg->add_drop_items();
	//player_item_info_t* playerItemInfoBody = bodyMsg->mutable_drop_items(0);
	//playerItemInfoBody->set_id(id);
	//playerItemInfoBody->set_item_id(item_id);
	//playerItemInfoBody->set_item_count(count);
	//playerItemInfoBody->set_item_bag_flag(1); // TODO:currently server don't need this information

	//NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_DROP_ITEM, true, true);
}

//------------------------------------------------------------------
void OnlineNetworkManager::sendPlayerChangeNickMessage(std::string newNick)
{
	//Message* msg = MessageUtil::sShareInstance()->createMessageInstance("iAdCSProto.player_change_nick_req_t");
	//player_change_nick_req_t* bodyMsg = (player_change_nick_req_t*)msg;
	//bodyMsg->set_new_nick(newNick);

	//NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_PLAYER_CHANGE_NICK, true, true);
}

//------------------------------------------------------------------
void OnlineNetworkManager::sendSendMailMessage( uint32_t receiver_id,
												int32_t receiver_role_tm, 
												std::string mail_title, 
												std::string mail_content)
{
	//Message* msg = MessageUtil::sShareInstance()->createMessageInstance("iAdCSProto.send_mail_req_t");
	//send_mail_req_t* bodyMsg = (send_mail_req_t*)msg;
	//bodyMsg->set_receiver_id(receiver_id);
	//bodyMsg->set_receiver_role_tm(receiver_role_tm);
	//bodyMsg->set_mail_title(mail_title);
	//bodyMsg->set_mail_content(mail_content);

	//NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_SEND_MAIL, true, true);
}

//------------------------------------------------------------------
void OnlineNetworkManager::sendGetMailHeadListMessage()
{
	//Message* msg = MessageUtil::sShareInstance()->createMessageInstance("iAdCSProto.get_mail_head_list_req_t");
	//get_mail_head_list_req_t* bodyMsg = (get_mail_head_list_req_t*)msg;

	//NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_GET_MAIL_HEAD_LIST, true, true);
}

//------------------------------------------------------------------
void OnlineNetworkManager::sendGetMailBodyMessage(uint64_t mail_id)
{
	//Message* msg = MessageUtil::sShareInstance()->createMessageInstance("iAdCSProto.get_mail_body_req_t");
	//get_mail_body_req_t* bodyMsg = (get_mail_body_req_t*)msg;
	//bodyMsg->set_mail_id(mail_id);

	//NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_GET_MAIL_BODY, true, true);
}

//------------------------------------------------------------------
void OnlineNetworkManager::sendDeleteMailMessage(uint64_t mail_id)
{
	//Message* msg = MessageUtil::sShareInstance()->createMessageInstance("iAdCSProto.del_mail_req_t");
	//del_mail_req_t* bodyMsg = (del_mail_req_t*)msg;
	//bodyMsg->set_mail_id(mail_id);

	//NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_DELETE_MAIL, true, true);
}

//------------------------------------------------------------------
void OnlineNetworkManager::sendGetMailEnclosureMessage(uint64_t mail_id)
{
	//Message* msg = MessageUtil::sShareInstance()->createMessageInstance("iAdCSProto.get_mail_enclosure_req_t");
	//get_mail_enclosure_req_t* bodyMsg = (get_mail_enclosure_req_t*)msg;
	//bodyMsg->set_mail_id(mail_id);

	//NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_GET_MAIL_ENCLOSURE, true, true);
}

//------------------------------------------------------------------
void OnlineNetworkManager::sendObtainTaskMessage(uint32_t task_id)
{
	//Message* msg = MessageUtil::sShareInstance()->createMessageInstance("iAdCSProto.obtain_task_req_t");
	//obtain_task_req_t* bodyMsg = (obtain_task_req_t*)msg;
	//bodyMsg->set_task_id(task_id);

	//NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_OBTAIN_TASK, true, true);
}

//------------------------------------------------------------------
void OnlineNetworkManager::sendCancelTaskMessage(uint32_t task_id)
{
	//Message* msg = MessageUtil::sShareInstance()->createMessageInstance("iAdCSProto.cancel_task_req_t");
	//cancel_task_req_t* bodyMsg = (cancel_task_req_t*)msg;
	//bodyMsg->set_task_id(task_id);

	//NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_CANCEL_TASK, true, true);
}

//------------------------------------------------------------------
void OnlineNetworkManager::sendFinishTaskMessage(uint32_t task_id)
{
	//Message* msg = MessageUtil::sShareInstance()->createMessageInstance("iAdCSProto.finish_task_req_t");
	//finish_task_req_t* bodyMsg = (finish_task_req_t*)msg;
	//bodyMsg->set_task_id(task_id);

	//NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_FINISH_TASK, true, true);
}

//------------------------------------------------------------------
void OnlineNetworkManager::sendGetTaskFlagListMessage(uint32_t task_id)
{
	//Message* msg = MessageUtil::sShareInstance()->createMessageInstance("iAdCSProto.get_task_flag_list_req_t");
	//get_task_flag_list_req_t* bodyMsg = (get_task_flag_list_req_t*)msg;
	//bodyMsg->add_task_id_list(task_id);

	//NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_GET_TASK_FLAG_LIST, true, true);
}

//------------------------------------------------------------------
void OnlineNetworkManager::sendGetTaskFlagListMessage(std::set<uint32_t> &task_id_set)
{
	//Message* msg = MessageUtil::sShareInstance()->createMessageInstance("iAdCSProto.get_task_flag_list_req_t");
	//get_task_flag_list_req_t* bodyMsg = (get_task_flag_list_req_t*)msg;
	//
	//for(std::set<uint32_t>::iterator iter = task_id_set.begin(); iter != task_id_set.end(); iter++)
	//{
	//	bodyMsg->add_task_id_list(*iter);
	//}

	//NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_GET_TASK_FLAG_LIST, true, true);
}

//------------------------------------------------------------------
void OnlineNetworkManager::sendGetTaskBuffListMessage(uint32_t task_id)
{	
	//Message* msg = MessageUtil::sShareInstance()->createMessageInstance("iAdCSProto.get_task_buff_list_req_t");
	//get_task_buff_list_req_t* bodyMsg = (get_task_buff_list_req_t*)msg;
	//bodyMsg->add_task_id_list(task_id);

	//NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_GET_TASK_BUFF_LIST, true, true);
}

//------------------------------------------------------------------
void OnlineNetworkManager::sendGetTaskBuffListMessage(std::set<uint32_t> &task_id_set)
{	
	//Message* msg = MessageUtil::sShareInstance()->createMessageInstance("iAdCSProto.get_task_buff_list_req_t");
	//get_task_buff_list_req_t* bodyMsg = (get_task_buff_list_req_t*)msg;
	//
	//for(std::set<uint32_t>::iterator iter = task_id_set.begin(); iter != task_id_set.end(); iter++)
	//{
	//	bodyMsg->add_task_id_list(*iter);
	//}

	//NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_GET_TASK_BUFF_LIST, true, true);
}

//------------------------------------------------------------------
void OnlineNetworkManager::sendGetTaskListMessage()
{
	//Message* msg = MessageUtil::sShareInstance()->createMessageInstance("iAdCSProto.get_task_list_req_t");
	//get_task_list_req_t* bodyMsg = (get_task_list_req_t*)msg;

	//NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_GET_TASK_LIST, true, true);
}

//------------------------------------------------------------------
void OnlineNetworkManager::sendSetTaskStepMessage(uint32_t task_id, uint32_t step)
{
	//Message* msg = MessageUtil::sShareInstance()->createMessageInstance("iAdCSProto.set_task_step_req_t");
	//set_task_step_req_t* bodyMsg = (set_task_step_req_t*)msg;
	//bodyMsg->set_task_id(task_id);
	//bodyMsg->set_step(step);

	//NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_SET_TASK_STEP, true, true);
}

//------------------------------------------------------------------
void OnlineNetworkManager::sendCheckSessionMessage()
{
	
}

//------------------------------------------------------------------
void OnlineNetworkManager::sendCreateRoleMessage(const std::string &nick, const uint32_t type)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSCrtRoleReq");
	CSCrtRoleReq* bodyMsg = (CSCrtRoleReq*)msg;
	bodyMsg->set_name(nick);
	bodyMsg->set_role_type(type);
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_CREATE_ROLE, true, true);
}

//------------------------------------------------------------------
                           // battle server 

//------------------------------------------------------------------
void OnlineNetworkManager::battleWithWildMon(uint32_t mapID)
{
	//Message* msg = MessageUtil::sShareInstance()->createMessageInstance("iAdCSProto.start_battle_pve_in_t");
	//start_battle_pve_in_t* bodyMsg = (start_battle_pve_in_t*)msg;
	//bodyMsg->set_region(mapID);

	//NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_START_PVE_BATTLE, true, true);
}

void OnlineNetworkManager::battleFinishLoading() {
	//Message* msg = MessageUtil::sShareInstance()->createMessageInstance("iAdCSProto.player_ready_in_t");
	//player_ready_in_t* bodyMsg = (player_ready_in_t*)msg;

	//NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_BATTLE_FINISH_LOADING, true, true);
}

void OnlineNetworkManager::sendUseSkill(const uint32_t skillId) {
	//Message* msg = MessageUtil::sShareInstance()->createMessageInstance("iAdCSProto.select_move_in_t");
	//select_move_in_t* bodyMsg = (select_move_in_t*)msg;
	//bodyMsg->set_move_id(skillId);

	//NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_BATTLE_USE_SKILL, true, true);
}


void OnlineNetworkManager::TestEcho()
{
	//Message* msg = 
	//	MessageUtil::sShareInstance()->createMessageInstance("iAdCSProto.cli_echo_req_t");
	//cli_echo_req_t* bodyMsg = (cli_echo_req_t*)msg;

	//NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, BATTLE_TAG_ECHO, true, true);
}

void OnlineNetworkManager::sendBackPackMessage()
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSAllItemsReq");
	CSAllItemsReq* bodyMsg = (CSAllItemsReq*)msg;
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_ITEM_REQ, true, true);
}

void OnlineNetworkManager::sendLoadCompleteMessage()
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSBattleLoadCompleteReq");
	CSBattleLoadCompleteReq* bodyMsg = (CSBattleLoadCompleteReq*)msg;
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_LOAD_COMPLETE, true, true);
}

void OnlineNetworkManager::sendLeaveBattleReqMessage()
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSBattleLeaveReq");
	CSBattleLeaveReq* bodyMsg = (CSBattleLeaveReq*)msg;
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_PLAYER_LEAVE_BATTLE, true, true);
}

//------------------------------------------------------------------
void OnlineNetworkManager::sendGetInstanceListMessage(uint32_t start, uint32_t end)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSInstanceReq");
	CSInstanceReq* bodyMsg = (CSInstanceReq*)msg;
	bodyMsg->set_start(start);
	bodyMsg->set_end(end);

	//don't cache the walk message if failed
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_GET_BATTLE_LIST, true, true);
}

void OnlineNetworkManager::sendBackPackMove(unsigned int from,unsigned int to)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSItemMoveReq");
	CSItemMoveReq* bodyMsg = (CSItemMoveReq*)msg;
	bodyMsg->set_pos_from(from);
	bodyMsg->set_pos_to(to);
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_ITEM_MOVE, true, true);
}

void OnlineNetworkManager::sendBackPackReOrder(unsigned int type)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSItemOrderReq");
	CSItemOrderReq* bodyMsg = (CSItemOrderReq*)msg;
	bodyMsg->set_target(type);
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_ITEM_REORDER, true, true);
}

void OnlineNetworkManager::sendBackPackRemoveItem(unsigned int pos, unsigned int itemId)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSItemRemoveReq");
	CSItemRemoveReq* bodyMsg = (CSItemRemoveReq*)msg;
	bodyMsg->set_pos(pos);
	bodyMsg->set_item_id(itemId);
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_ITEM_REMOVE, true, true);
}
void OnlineNetworkManager::sendUseItem(unsigned int pos, unsigned int itemId)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSItemUseReq");
	CSItemUseReq* bodyMsg = (CSItemUseReq*)msg;
	bodyMsg->set_pos(pos);
	bodyMsg->set_item_id(itemId);
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_ITEM_USE, true, true);
}

void OnlineNetworkManager::sentEquipUpgradeMessage()
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSGetEquipLvUpCDReq");
	CSGetEquipLvUpCDReq* bodyMsg = (CSGetEquipLvUpCDReq*)msg;
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_EQUIPUPGRADE_REQ, true, true);
}

void OnlineNetworkManager::sentEquipUpgradeStrength(unsigned int pos)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSEquipmentStrengthReq");
	CSEquipmentStrengthReq* bodyMsg = (CSEquipmentStrengthReq*)msg;
	bodyMsg->set_pos(pos);
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_EQUIPUPGRADE_STRENGTH, true, true);
}

void OnlineNetworkManager::sendEquipComposeReq(unsigned int exchangeId,unsigned int pos,unsigned int multi)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSEquipmentComposeReq");
	CSEquipmentComposeReq* bodyMsg = (CSEquipmentComposeReq*)msg;
	bodyMsg->set_exchange_item_id(exchangeId);
	if(pos != 0)
	{
		bodyMsg->add_from_item_pos(pos);
	}
	bodyMsg->set_multi(multi);
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_EQUIPCOMPOSE_REQ, true, true);
}

void OnlineNetworkManager::sendItemExchangeReq(unsigned int exchangeId,unsigned int pos[],int length)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSEquipmentComposeReq");
	CSEquipmentComposeReq* bodyMsg = (CSEquipmentComposeReq*)msg;
	bodyMsg->set_exchange_item_id(exchangeId);
	for(int i =0;i< length;i++)
	{
		bodyMsg->add_from_item_pos(pos[i]);
	}
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_EQUIPCOMPOSE_REQ, true, true);
}

//宝石镶嵌

void OnlineNetworkManager::sendEquipInlayGemReq(unsigned int equip,unsigned int hole,unsigned int gemId)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSEquipInlayGemReq");
	CSEquipInlayGemReq* bodyMsg = (CSEquipInlayGemReq*)msg;
	bodyMsg->set_equip_pos(equip);
	bodyMsg->set_hole_index(hole);
	bodyMsg->set_gem_id(gemId);
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_EQUIPINLAYGEM_REQ, true, true);
}

void OnlineNetworkManager::sendGemRecastReq(unsigned int equip,unsigned int holes[],unsigned int holeNum,unsigned int key)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSResetGemAttrReq");
	CSResetGemAttrReq* bodyMsg = (CSResetGemAttrReq*)msg;
	bodyMsg->set_equip_pos(equip);
	for(unsigned int i=0;i < holeNum;i++)
	{
		if(holes[i] != 0)
		{
			bodyMsg->add_holes_index(holes[i]);
		}
	}
	if(key != 0)
	{
		bodyMsg->set_cost_attr_key(key);
	}
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_GEMRECAST_REQ, true, true);
}

void OnlineNetworkManager::sendExchangeParameterReq(unsigned int exchangeId,unsigned int param)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSExchangeParameterReq");
	CSExchangeParameterReq* bodyMsg = (CSExchangeParameterReq*)msg;
	bodyMsg->set_id(exchangeId);
	if(param != 0)
	{
		bodyMsg->set_param(param);
	}

	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_EXCHANGEPARAM_REQ, true, true);
}

void OnlineNetworkManager::sendElfExchangeReq(unsigned int elfId)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSEquipmentComposeReq");
	CSEquipmentComposeReq* bodyMsg = (CSEquipmentComposeReq*)msg;
	bodyMsg->set_exchange_item_id(elfId);

	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_EQUIPCOMPOSE_REQ, true, true);
}

void OnlineNetworkManager::sendFindSoulStoneMessage()
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSSearchSpiritStoneReq");
	CSSearchSpiritStoneReq* bodyMsg = (CSSearchSpiritStoneReq*)msg;
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_SEARCH_SPRITE_STONE, true, true);
}

void OnlineNetworkManager::sendSoulStoneToStorage(unsigned int pos)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSSpiritStoneMoveBagReq");
	CSSpiritStoneMoveBagReq* bodyMsg = (CSSpiritStoneMoveBagReq*)msg;
	bodyMsg->set_pos(pos);
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_MOVE_SPRITE_STONE_TO_STORAGE, true, true);
}

void OnlineNetworkManager::sendUpgradeSoulStone(unsigned int pos)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSSpiritStoneLevelUpReq");
	CSSpiritStoneLevelUpReq* bodyMsg = (CSSpiritStoneLevelUpReq*)msg;
	bodyMsg->set_pos(pos);
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_UPGRADE_SPRITE_STONE, true, true);
}

void OnlineNetworkManager::sendTranStoneToEnergy(bool isAll,unsigned int pos)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSSpiritStoneToSPReq");
	CSSpiritStoneToSPReq* bodyMsg = (CSSpiritStoneToSPReq*)msg;
	if(!isAll)
	{
		bodyMsg->set_pos(pos);
	}
	else
	{
		bodyMsg->set_pos(0);
	}
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_TRANS_SPRITE_TO_ENERGE, true, true);
}

void OnlineNetworkManager::sendSpriteExchangeMessage()
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSGetExchangeSSInfoReq");
	CSGetExchangeSSInfoReq* bodyMsg = (CSGetExchangeSSInfoReq*)msg;
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_SPRITE_EXCHANGE, true, true);
}

/// <summary>
//	Task 请求相关的协议
/// </summary>
void OnlineNetworkManager::sendRqsTaskInfoMessage()
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSTaskInfoReq");
	CSTaskInfoReq* bodyMsg = (CSTaskInfoReq*)msg;	
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_TASK, true, true);
}

void OnlineNetworkManager::sendRqsTaskLogMessage()
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSTaskLogReq");
	CSTaskLogReq* bodyMsg = (CSTaskLogReq*)msg;	
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_TASK, true, true);	
}

void OnlineNetworkManager::sendRqsTaskDoStepMessage(unsigned int task_id,unsigned int step_id,unsigned int step_value)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSTaskDoStepReq");
	CSTaskDoStepReq* bodyMsg = (CSTaskDoStepReq*)msg;	
	bodyMsg->set_task_id(task_id);
	bodyMsg->set_step_id(step_id);
	bodyMsg->set_step_value(step_value);
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_TASK, true, true);	
}

void OnlineNetworkManager::sendReqNetStateMessage()
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSPingReq");
	CSPingReq* bodyMsg = (CSPingReq*)msg;	
	NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_TASK, true, true);
}

void OnlineNetworkManager::sendSkillBeginMessage( const CSSkillBeginReq& req )
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSSkillBeginReq");
	CSSkillBeginReq* bodyMsg = (CSSkillBeginReq*)msg;
	*bodyMsg = req;

	KSendMessageResult result = NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_PLAYER_ATTACK, true, true);
}

/// <summary>
//	精灵相关协议
/// </summary>
void OnlineNetworkManager::sendReqOneHeroElfMessage(unsigned int roleId,const char* roleName)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSMonListReq");
	CSMonListReq* bodyMsg = (CSMonListReq*)msg;
	bodyMsg->set_uid(roleId);
	bodyMsg->set_name(roleName);

	KSendMessageResult result = NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_ELF, true, true);
}

void OnlineNetworkManager::sendReqSetElfStateMessage(unsigned int elfId,unsigned int state)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSSetMonStatusReq");
	CSSetMonStatusReq* bodyMsg = (CSSetMonStatusReq*)msg;
	bodyMsg->set_mon_id(elfId);
	bodyMsg->set_mon_status(state);

	KSendMessageResult result = NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_ELF, true, true);
}

void OnlineNetworkManager::sendQueryShardReq()
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSQueryShardReq");
	CSQueryShardReq* bodyMsg = (CSQueryShardReq*)msg;

	KSendMessageResult result = NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_QUERY_REQ, true, true);
}

void OnlineNetworkManager::sendAttributesReq(int attributes[],int length)
{
	if(length == 0)
	{
		return;
	}
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSAttributesReq");
	CSAttributesReq* bodyMsg = (CSAttributesReq*)msg;
	for(int i =0;i<length;i++)
	{
		bodyMsg->add_keys(attributes[i]);
	}
	KSendMessageResult result = NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_ATTRIBUTESREQ, true, true);
}

void OnlineNetworkManager::sendUserInfoReq(unsigned int id)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSGetUserInfoReq");
	CSGetUserInfoReq* bodyMsg = (CSGetUserInfoReq*)msg;
	bodyMsg->set_userid(id);
	KSendMessageResult result = NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_USERINFO, true, true);
}

void OnlineNetworkManager::sendOnceSetReqMessage(unsigned int index)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSOnceSetReq");
	CSOnceSetReq* bodyMsg = (CSOnceSetReq*)msg;
	bodyMsg->set_index(index);

	KSendMessageResult result = NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_SET, true, true);
}

void OnlineNetworkManager::sendOnceReqMessage(int indexs[],int length)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSOnceReq");
	CSOnceReq* bodyMsg = (CSOnceReq*)msg;

	for(int i =0;i<length;i++)
	{
		bodyMsg->add_indexs(indexs[i]);
	}

	KSendMessageResult result = NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_SET, true, true);
}

void OnlineNetworkManager::sendOnceReqMessage(std::vector<int> &vec)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSOnceReq");
	CSOnceReq* bodyMsg = (CSOnceReq*)msg;

	int length = vec.size();
	for(int i =0;i<length;i++)
	{
		bodyMsg->add_indexs(vec[i]);
	}

	KSendMessageResult result = NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_SET, true, true);
}

void OnlineNetworkManager::sendOnceReqMessage(std::map<unsigned int,bool> &_map,unsigned int attachValue)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSOnceReq");
	CSOnceReq* bodyMsg = (CSOnceReq*)msg;

	for (std::map<unsigned int,bool>::iterator iter = _map.begin();
		 iter != _map.end(); iter++)
	{
		bodyMsg->add_indexs((*iter).first - attachValue);
	}

	KSendMessageResult result = NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_SET, true, true);
}

void OnlineNetworkManager::sendGetUserSkillReqMessage(unsigned int roleId)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSGetUserSkillReq");
	CSGetUserSkillReq * bodyMsg = (CSGetUserSkillReq *)msg;

	bodyMsg->set_userid(roleId);

	KSendMessageResult result = NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_SKILL_UI, true, true);
}

void OnlineNetworkManager::sendAddUserSkillReqMessage(unsigned int skillId,unsigned int levelId)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSAddUserSkillReq");
	CSAddUserSkillReq * bodyMsg = (CSAddUserSkillReq *)msg;

	bodyMsg->set_skill_id(skillId);
	bodyMsg->set_skill_level(levelId);

	KSendMessageResult result = NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_SKILL_UI, true, true);
}

void OnlineNetworkManager::sendUserSkillDiffReqMessage(unsigned int skillId,unsigned int levelId)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSUserSkillDiffReq");
	CSUserSkillDiffReq * bodyMsg = (CSUserSkillDiffReq *)msg;

	bodyMsg->set_skill_id(skillId);
	bodyMsg->set_skill_level(levelId);

	KSendMessageResult result = NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_SKILL_UI, true, true);
}

void OnlineNetworkManager::sendGetSlotReqMessage()
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSAttributesReq");
	CSAttributesReq * bodyMsg = (CSAttributesReq *)msg;

	bodyMsg->add_keys(SKILL_SLOT_1);
	bodyMsg->add_keys(SKILL_SLOT_2);
	bodyMsg->add_keys(SKILL_SLOT_3);
	bodyMsg->add_keys(SKILL_SLOT_4);
	bodyMsg->add_keys(SKILL_SLOT_5);

	KSendMessageResult result = NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_SKILL_UI, true, true);
}

void OnlineNetworkManager::sendSetSlotAttributeMessage(unsigned int slotIndex,unsigned skillId)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSAttributesSetReq");
	CSAttributesSetReq * bodyMsg = (CSAttributesSetReq *)msg;

	bodyMsg->set_key(slotIndex - 1 + SKILL_SLOT_1);
	bodyMsg->set_value(skillId);

	KSendMessageResult result = NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, NETWORK_TAG_SKILL_UI, true, true);
}

// Note: 精灵唤醒相关协议
void OnlineNetworkManager::SendElfAwakeMessage(unsigned int awakeType)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSTrainReq");
	CSTrainReq  * bodyMsg = (CSTrainReq  *)msg;

	bodyMsg->set_type(awakeType);

	KSendMessageResult result = NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, ELF_TAG_AWAKE, true, true);
}

void OnlineNetworkManager::SendAwakeConfigMessage()
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSTrainDetermineReq");
	CSTrainDetermineReq  * bodyMsg = (CSTrainDetermineReq  *)msg;

	KSendMessageResult result = NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, ELF_TAG_AWAKE, true, true);
}

// Note: 精灵探索协议
void OnlineNetworkManager::SendExploreReq(unsigned int type)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSExploreReq");
	CSExploreReq * bodyMsg = (CSExploreReq *)msg;
	bodyMsg->set_option(type);

	KSendMessageResult result = NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, ELF_TAG_EXPLORE, true, true);
}

void OnlineNetworkManager::SendExploreDetermineReq(unsigned int optionId)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSExploreDetermineReq");
	CSExploreDetermineReq  * bodyMsg = (CSExploreDetermineReq  *)msg;
	bodyMsg->set_option(optionId);

	KSendMessageResult result = NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, ELF_TAG_EXPLORE, true, true);
}

void OnlineNetworkManager::SendDelRoleReqMessage()
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSDelRoleReq");
	CSDelRoleReq  * bodyMsg = (CSDelRoleReq  *)msg;

	KSendMessageResult result = NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, DEL_HERO_PLAYER, true, true);
}

void OnlineNetworkManager::sendPvAIReq(unsigned int userId)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSPVAIReq");
	CSPVAIReq  * bodyMsg = (CSPVAIReq  *)msg;
	bodyMsg->set_userid(userId);

	KSendMessageResult result = NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, PVAI_TAG_REQ, true, true);
}

void OnlineNetworkManager::sendPvAIInfoReq()
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSPVAIInfoReq");
	CSPVAIInfoReq  * bodyMsg = (CSPVAIInfoReq  *)msg;

	KSendMessageResult result = NetWorkUtil::sendMessage(bodyMsg, PKG_TIMEOUT, PVAI_TAG_INFO_REQ, true, true);
}