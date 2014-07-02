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
#include "PVPMessage.h"
#include "BoneNPCManager.h"
#include "LevelDefine.h"
#include "UserData.h"

#include "cocos2d.h"
#include "tolua++.h"
#include "CCLuaEngine.h"
#include "cs_basic.pb.h"
#include "cs_core.pb.h"
#include "cs_battle.pb.h"
#include "errcode.pb.h"

#include "MainMenuLayer.h"
#include "PVPLayer.h"
#include "Localization.h"

#include "OnlineNetworkManager.h"
#include "TalentLayer.h"
#include "AutoOnHook.h"
#include "ShopUILayer.h"
#include "BackPackLayer.h"

PVPMessage::PVPMessage()
{
}

void PVPMessage::InitHandler(MessageHandler * messageHolder)
{
	m_pMessageHolder = messageHolder;
}

void PVPMessage::handleMsgGetRoom(NORMAL_MSG_PACKAGE* pkg)
{
    CCLog("pvp message handleMsgGetRoom\n");
	/// clear all rooms
    
    PVPLayer* pvp = GetPVPLayer();
    if(!pvp)
        return;
    
	GetPVPLayer()->ClearAllRooms();
    
	if (pkg)
	{
		m_lRooms.clear();
		CSPVPQueryRoomRsp* msg = dynamic_cast<CSPVPQueryRoomRsp*>(pkg->msg);
		for(int i = 0; i < msg->rooms_size(); i++)
		{
			const PVPRoomBase& room = msg->rooms(i);
			m_lRooms.push_back(room);
			/// show room list
			GetPVPLayer()->AddNewRoom(room);
		}
	}
    
	/// call global script function
	if (GetMainMenuLayer() && GetMainMenuLayer()->IsInPVPModule())
	{
		CCLuaEngine::defaultEngine()->executeGlobalFunction("UpdatePVPPage");
	}
}

void PVPMessage::pvp_getRoomList()
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSPVPQueryRoomReq");
	//CSPVPQueryRoomRsp* bodyMsg = (CSPVPQueryRoomRsp*)msg;
    CSPVPQueryRoomReq* bodyMsg = (CSPVPQueryRoomReq*)msg;
	OnlineNetworkManager::sShareInstance()->sendMessage(bodyMsg, 2.0, NETWORK_TAG_PLAYER_ENTER_MAP, true, true);
}

void PVPMessage::pvp_createRoom_1vs1()
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSPVPCreateRoomReq");
	CSPVPCreateRoomReq* bodyMsg = (CSPVPCreateRoomReq*)msg;
	const USERINFO& user = UserData::GetUserInfo();
	bodyMsg->set_top_level(user.level);
    bodyMsg->set_type(1);
	OnlineNetworkManager::sShareInstance()->sendMessage(bodyMsg, 2.0, NETWORK_TAG_PLAYER_ENTER_MAP, true, true);
}

void PVPMessage::pvp_createRoom_2vs2()
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSPVPCreateRoomReq");
	CSPVPCreateRoomReq* bodyMsg = (CSPVPCreateRoomReq*)msg;
	const USERINFO& user = UserData::GetUserInfo();
	bodyMsg->set_top_level(user.level);
    bodyMsg->set_type(2);
	OnlineNetworkManager::sShareInstance()->sendMessage(bodyMsg, 2.0, NETWORK_TAG_PLAYER_ENTER_MAP, true, true);
}

/*
 * room closed by host
 */
void PVPMessage::handleMsgCloseRoom(NORMAL_MSG_PACKAGE* pkg)
{
	/// call global script function
	if (GetMainMenuLayer() && GetMainMenuLayer()->IsInPVPModule())
	{
		CCLuaEngine::defaultEngine()->executeGlobalFunction("closePVPRoom");
	}
}

void PVPMessage::pvp_exitRoom()
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSPVPExitRoomReq");
	CSPVPExitRoomReq* bodyMsg = (CSPVPExitRoomReq*)msg;
	OnlineNetworkManager::sShareInstance()->sendMessage(bodyMsg, 2.0, NETWORK_TAG_PLAYER_ENTER_MAP, true, true);
}

void PVPMessage::pvp_JoinRoom(int roomID)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSPVPJoinRoomReq");
	CSPVPJoinRoomReq* bodyMsg = (CSPVPJoinRoomReq*)msg;
	bodyMsg->set_room_id(roomID);
	OnlineNetworkManager::sShareInstance()->sendMessage(bodyMsg, 2.0, NETWORK_TAG_PLAYER_ENTER_MAP, true, true);
}

void PVPMessage::HandleMsgJoinRoom(NORMAL_MSG_PACKAGE* pkg)
{
	m_lSeats.clear();
	CSPVPJoinRoomRsp* msg = (CSPVPJoinRoomRsp*)pkg->msg;
    
	int roomid = msg->room_id();
	int toplevel = msg->top_level();
    int type = msg->type();
    
	for(int i = 0; i < msg->seats_size(); i++)
	{
		const PVPSeatBase& seat = msg->seats(i);
		CCLog("%d-%d,%s, %d", seat.id(), seat.avatar(), seat.name().c_str(), seat.ready());
		m_lSeats.push_back(seat);
	}
    
	lua_State* L_state = CCLuaEngine::defaultEngine()->getLuaState();
    
	/// update all the seat information
	for(int n = 0; n < 4; n++)
	{
		bool bSeatON = false;
        
		for(size_t i = 0; i < m_lSeats.size(); i++)
		{
			if (m_lSeats[i].id() == n)
			{
				lua_getglobal(L_state, "pvp_PlayerOnSeat");
				tolua_pushnumber(L_state, n);
                
				/// seat have player
				lua_newtable(L_state);
				lua_pushstring(L_state, "seat_id");
				lua_pushnumber(L_state, m_lSeats[i].id());
				lua_settable(L_state,-3);
                
				lua_pushstring(L_state, "level");
				lua_pushnumber(L_state, m_lSeats[i].level());
				lua_settable(L_state,-3);
                
				lua_pushstring(L_state, "name");
				lua_pushstring(L_state, m_lSeats[i].name().c_str());
				lua_settable(L_state,-3);
                
				lua_pushstring(L_state, "Avatar");
				lua_pushnumber(L_state, m_lSeats[i].avatar());
				lua_settable(L_state,-3);
                
				lua_pushstring(L_state, "bReady");
				lua_pushboolean(L_state, m_lSeats[i].ready());
				lua_settable(L_state,-3);
				bSeatON = true;
                
				lua_pcall(L_state, 2, LUA_MULTRET, 0);
                
				break;
			}
		}
        
		/// not palyer on this seat
		if (!bSeatON)
		{
			lua_getglobal(L_state, "pvp_PlayerLeaveSeat");
			tolua_pushnumber(L_state, n);
			lua_pcall(L_state, 1, LUA_MULTRET, 0);
		}
	}
    
	/// call global script function
	if (GetMainMenuLayer() && GetMainMenuLayer()->IsInPVPModule())
	{
		lua_getglobal(L_state, "pvp_EnterRoom");
		tolua_pushnumber(L_state, roomid);
		tolua_pushnumber(L_state, toplevel);
        tolua_pushnumber(L_state, type);
		lua_pcall(L_state, 3, LUA_MULTRET, 0);
	}
}

void PVPMessage::pvp_setReady(bool bReady)
{
	if (bReady)
	{
		Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSPVPReadyReq");
		CSPVPReadyReq* bodyMsg = (CSPVPReadyReq*)msg;
		OnlineNetworkManager::sShareInstance()->sendMessage(bodyMsg, 2.0, NETWORK_TAG_PLAYER_ENTER_MAP, true, true);
	}
	else
	{
		Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSPVPCancelReadyReq");
		CSPVPCancelReadyReq* bodyMsg = (CSPVPCancelReadyReq*)msg;
		OnlineNetworkManager::sShareInstance()->sendMessage(bodyMsg, 2.0, NETWORK_TAG_PLAYER_ENTER_MAP, true, true);
	}
}

/// start game now
void PVPMessage::pvp_startGame()
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSPVPStartReq");
	CSPVPStartReq* bodyMsg = (CSPVPStartReq*)msg;
	OnlineNetworkManager::sShareInstance()->sendMessage(bodyMsg, 2.0, NETWORK_TAG_PLAYER_ENTER_MAP, true, true);
}

void PVPMessage::pvp_kickOffGuest(int seat)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSPVPKickoffReq");
	CSPVPKickoffReq* bodyMsg = (CSPVPKickoffReq*)msg;
	bodyMsg->set_seat(seat);
	OnlineNetworkManager::sShareInstance()->sendMessage(bodyMsg, 2.0, NETWORK_TAG_PLAYER_ENTER_MAP, true, true);
}

void PVPMessage::pvp_changeSeat(int seat)
{
    Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSPVPChangeSeatReq");
	CSPVPKickoffReq* bodyMsg = (CSPVPKickoffReq*)msg;
	bodyMsg->set_seat(seat);
	OnlineNetworkManager::sShareInstance()->sendMessage(bodyMsg, 2.0, NETWORK_TAG_PLAYER_ENTER_MAP, true, true);
}

/////////////////////Talent/////////////////////
void  PVPMessage::getTalentList()
{
    Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSQueryDowerReq");
	CSQueryDowerReq* bodyMsg = (CSQueryDowerReq*)msg;
	OnlineNetworkManager::sShareInstance()->sendMessage(bodyMsg, 2.0, NETWORK_TAG_PLAYER_ENTER_MAP, true, true);
}

void  PVPMessage::getOneTalent(int talent_id, int level)
{
    Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSDowerInfoReq");
	CSDowerInfoReq* bodyMsg = (CSDowerInfoReq*)msg;
    bodyMsg->set_id(talent_id);
    bodyMsg->set_level(level);
    
	OnlineNetworkManager::sShareInstance()->sendMessage(bodyMsg, 2.0, NETWORK_TAG_PLAYER_ENTER_MAP, true, true);
}

void PVPMessage::levelUpTalent(int talent_id)
{
    Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSDowerReq");
	CSDowerReq* bodyMsg = (CSDowerReq*)msg;
    bodyMsg->set_id(talent_id);
	OnlineNetworkManager::sShareInstance()->sendMessage(bodyMsg, 2.0, NETWORK_TAG_PLAYER_ENTER_MAP, true, true);
}

void PVPMessage::HandleMsgTalentList(NORMAL_MSG_PACKAGE* pkg)
{
    TalentLayer *layer  = GetTalentLayer();
    if(!layer)
        return;
    
    layer->clearScrollist();
    CSQueryDowerRsp* msg = (CSQueryDowerRsp*)pkg->msg;
    int downsize = msg->dower_size();
    int timeout = msg->timeout();
    GetTalentLayer()->startCD(timeout);
    
    int first_talentId, first_level;
    
    for(int i=0; i<downsize; i++)
    {
        CSQueryDowerRsp_Dower down =  msg->dower(i);
        unsigned int id = down.id();
        unsigned int level = down.level();
        unsigned int plus = down.plus();
        unsigned int each_plus = down.each_plus();
        
        CCLog("each_plus:%d\n", each_plus);
        layer->addNewTalent(id, level, plus);
        layer->seteachplus(each_plus);
        
        if(i==0)
        {
            first_talentId = id;
            first_level = level;
            getOneTalent(first_talentId, first_level);
            layer->setcurTalentID(first_talentId);
        }
    }
}

void PVPMessage::HandleMsgOneTalent(NORMAL_MSG_PACKAGE* pkg)
{
    CSDowerInfoRsp* msg = (CSDowerInfoRsp*)pkg->msg;
    
    unsigned int id = msg->id();
    unsigned int level = msg->level();
    unsigned int plus = msg->plus();
    unsigned int next_exploit = msg->next_exploit();
    unsigned int next_time = msg->next_time();
    
    unsigned int diff_physical_attack = msg->diff_physical_attack();
    unsigned int diff_magic_attack = msg->diff_magic_attack();
    unsigned int diff_skill_attack = msg->diff_skill_attack();
    unsigned int diff_physical_defence = msg->diff_physical_defence();
    unsigned int diff_magic_defence = msg->diff_magic_defence();
    unsigned int diff_skill_defence = msg->diff_skill_defence();
    unsigned int diff_hp = msg->diff_hp();

    
    CCLog("id:%d\n", id);
    CCLog("level:%d\n", level);
    CCLog("plus:%d\n", plus);
    CCLog("next_exploit:%d\n", next_exploit);
    CCLog("next_time:%d\n", next_time);
    
    CCLog("diff_physical_attack:%d\n", diff_physical_attack);
    CCLog("diff_magic_attack:%d\n", diff_magic_attack);
    CCLog("diff_skill_attack:%d\n", diff_skill_attack);
    CCLog("diff_physical_defence:%d\n", diff_physical_defence);
    CCLog("diff_magic_defence:%d\n", diff_magic_defence);
    CCLog("diff_skill_defence:%d\n", diff_skill_defence);
    CCLog("diff_hp:%d\n", diff_hp);

    GetTalentLayer()->showOne(
                  id,
                  level,
                  plus,
                  next_exploit,
                  next_time,
                              
                  diff_physical_attack,
                  diff_magic_attack,
                  diff_skill_attack,
                              
                  diff_physical_defence,
                  diff_magic_defence,
                  diff_skill_defence,
                  diff_hp);
}

void PVPMessage::HandleMsgLevelUpTalent(NORMAL_MSG_PACKAGE* pkg)
{
    CSDowerRsp* msg = (CSDowerRsp*)pkg->msg;
    unsigned int level = msg->level();
    unsigned int timeout = msg->timeout();
    unsigned int next_exploit = msg->next_exploit();
    unsigned int plus = msg->plus();
    GetTalentLayer()->updateLevel(level, plus, next_exploit);
    GetTalentLayer()->startCD(timeout);
}


////////////////////////////AutoOnHook//////////////////////////////

void PVPMessage::sendCSABMonsterReq(unsigned int instance_id)
{
    Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSABMonsterReq");
	CSABMonsterReq* bodyMsg = (CSABMonsterReq*)msg;
    //required uint32 instance_id = 1; // 副本ID
    bodyMsg->set_instance_id(instance_id);
	OnlineNetworkManager::sShareInstance()->sendMessage(bodyMsg, 2.0, NETWORK_TAG_PLAYER_ENTER_MAP, true, true);
}

void PVPMessage::sendCSAutoBattleReq(unsigned int instance_id, int turn_num)
{
    Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSAutoBattleReq");
	CSAutoBattleReq* bodyMsg = (CSAutoBattleReq*)msg;
    //required uint32 instance_id = 1; // 副本ID
	//required uint32 turn_num 	= 2; // 轮数(=0时表示消耗所有体力值)
    bodyMsg->set_instance_id(instance_id);
    bodyMsg->set_turn_num(turn_num);
	OnlineNetworkManager::sShareInstance()->sendMessage(bodyMsg, 2.0, NETWORK_TAG_PLAYER_ENTER_MAP, true, true);
}

void PVPMessage::sendCSCancelAutoBattleReq()
{
    Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSCancelAutoBattleReq");
	CSCancelAutoBattleReq* bodyMsg = (CSCancelAutoBattleReq*)msg;
	OnlineNetworkManager::sShareInstance()->sendMessage(bodyMsg, 2.0, NETWORK_TAG_PLAYER_ENTER_MAP, true, true);
}

void PVPMessage::sendSpeedUpReq(int diamand_id)
{
    Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSExchangeParameterReq");
	CSExchangeParameterReq* bodyMsg = (CSExchangeParameterReq*)msg;
    bodyMsg->set_id(diamand_id);
	OnlineNetworkManager::sShareInstance()->sendMessage(bodyMsg, 2.0, NETWORK_TAG_PLAYER_ENTER_MAP, true, true);
}

void PVPMessage::HandleMsgCSABMonsterRsp(NORMAL_MSG_PACKAGE* pkg)
{
    AutoOnHook* hook = GetAutoOnHook();
    if(!hook)
        return;
    
    CSABMonsterRsp* msg = (CSABMonsterRsp*)pkg->msg;
    int monsize = msg->mon_infos_size();
    
    std::vector<OnHookA2> vecs;
    for(int i=0; i<monsize; i++)
    {
        CSABMonsterRsp_MonInfo info = msg->mon_infos(i);
        //required uint32 mon_id	= 1; // 怪物id
		//required uint32 mon_num	= 2; // 怪物num
        unsigned int mon_id = info.mon_id();
        unsigned int mon_num = info.mon_num();
        OnHookA2 a2;
        a2.mon_id = mon_id;
        a2.mon_num = mon_num;
        vecs.push_back(a2);
    }
    GetAutoOnHook()->setScrollist(vecs);
}

void PVPMessage::HandleMsgCSABRewardRsp(NORMAL_MSG_PACKAGE* pkg)
{
    AutoOnHook* hook = GetAutoOnHook();
    if(!hook)
        return;
    
    CSABRewardRsp* msg = (CSABRewardRsp*)pkg->msg;
    const CSReward reward = msg->rewards();
    int size = reward.rewards_size();
    
    CCLog("hand reward size:%d\n", size);
    
    hook->clearVecIDs();
    for(int item_index=0; item_index<size; item_index++)
    {
        CSReward_RewardInfo info = reward.rewards(item_index);
        unsigned int item_id = info.item_id();
        unsigned int item_level = info.item_level();
        unsigned int item_num = info.item_num();
        GetAutoOnHook()->setItemIcon(item_num, item_id, item_index);
        CCLog("item_id:%d\n", item_id);
    }
    
    unsigned int diamand_number = 0;
    unsigned int coin_number = reward.add_coin();
    unsigned int exploit_number = reward.add_exploit();
    unsigned int exp_number = reward.add_exp();
    GetAutoOnHook()->setIconAllGet(diamand_number,coin_number,exploit_number,exp_number);
}

void PVPMessage::HandleMsgAutoBattleRsp(NORMAL_MSG_PACKAGE* pkg)
{
    //required uint32 ret			= 1; // 0 成功 !0 失败(1:上个战斗自动战斗未完成 2:地图不能自动战斗 3...)
	//required uint32 cd			= 2; // 自动战斗完成需要的时间
	//required uint32 instance_id	= 3; // 自动战斗副本
    
    AutoOnHook* hook = GetAutoOnHook();
    if(!hook)
        return;
    
    CSAutoBattleRsp* msg = (CSAutoBattleRsp*)pkg->msg;
    unsigned int ret = msg->ret();
    unsigned int cd = msg->cd();
    unsigned int instance_id = msg->instance_id();
    hook->setinstanceId(instance_id);
    
    if(ret == 0)
        GetAutoOnHook()->startCD(cd);
    if(ret == 1)
        GetAutoOnHook()->startCD(cd);
    
    hook->hideCloseBtn();
}

void PVPMessage::HandleMsgCSCancelAutoBattleRsp(NORMAL_MSG_PACKAGE* pkg)
{
}

void PVPMessage::HandleMsgSpeedUpRsp(NORMAL_MSG_PACKAGE* pkg)
{
    CSExchangeParameterRsp* msg = (CSExchangeParameterRsp*)pkg->msg;
    int suc = msg->succ();
    int id = msg->id();
    
    if(suc && id == 10100)
    {
       GetTalentLayer()->startCD(0);
    }
    else if(suc && id == 10400)
    {
        GetAutoOnHook()->startCD(0);
    }
}

void PVPMessage::HandleMsgCSAttributesRsp(NORMAL_MSG_PACKAGE* pkg)
{
    
}


////////////////ShopUI///////////////
void PVPMessage::sendShopItems()
{
    Message* msg = MessageUtil::sShareInstance()->createMessageInstance("CSGetShopItemsReq");
	CSGetShopItemsReq* bodyMsg = (CSGetShopItemsReq*)msg;
	OnlineNetworkManager::sShareInstance()->sendMessage(bodyMsg, 2.0, NETWORK_TAG_PLAYER_ENTER_MAP, true, true);
}

void PVPMessage::HandleMsgShopItems(NORMAL_MSG_PACKAGE* pkg)
{
    CSGetShopItemsRsp* msg = (CSGetShopItemsRsp*)pkg->msg;
    int size = msg->items_size();
    std::vector<shopItem> vecs;
    
    ShopUILayer *shopUI = GetBackPackLayer()->getpShopUILayer();
    if(shopUI)
    {
        for(int i=0; i<size; i++)
        {
            ShopItemInfo info = msg->items(i);
            ShopItemInfo_Item to_item = info.to_item();
            ShopItemInfo_Item from_item = info.from_item();
            
            shopItem  item;
            
            item.to_id = to_item.item_id();
            item.to_num= to_item.item_num();
            
            item.from_id = from_item.item_id();
            item.from_num = from_item.item_num();
            
            vecs.push_back(item);
        }
        shopUI->setupShopList(vecs);
    }
}

void PVPMessage::HandlerMessage(string cmd, NORMAL_MSG_PACKAGE* package)
{
    if(cmd == "CSPVPQueryRoomRsp")
	{
		handleMsgGetRoom(package);
	}
    
	else if (cmd == "CSPVPCloseRoomRsp")
	{
		handleMsgCloseRoom(package);
	}
    
	else if (cmd == "CSPVPJoinRoomRsp")
	{
		HandleMsgJoinRoom(package);
	}
    
	else if (cmd == "CSPVPKickoffRsp")
	{
		/// call global script function
		if (GetMainMenuLayer() && GetMainMenuLayer()->IsInPVPModule())
		{
			CCLuaEngine::defaultEngine()->executeGlobalFunction("pvp_kickOffFromRoom");
		}
	}
    
	else if (cmd == "CSPVPJoinRoomFailureRsp")
	{
		string strMsgError = Localizatioin::getLocalization("M_JOINROOM_FAIL");;
		ShowMessage(strMsgError.c_str());
	}
    
	else if (cmd == "CSPVPBaseInfoRsp")
	{
        CSPVEBaseInfoRsp* msg = (CSPVEBaseInfoRsp*)package->msg;
        if (msg)
        {
            lua_State* L_state = CCLuaEngine::defaultEngine()->getLuaState();
            lua_getglobal(L_state, "PlayerBaseInfo");
            tolua_pushnumber(L_state, msg->countdown());
            tolua_pushnumber(L_state, msg->remain_times());
            lua_pcall(L_state, 2, LUA_MULTRET, 0);
        }
	}
    
    /////////////talent message Rsp/////////////////////
    else if(cmd == "CSQueryDowerRsp")
    {
        HandleMsgTalentList(package);
    }
    else if(cmd == "CSDowerInfoRsp")
    {
        HandleMsgOneTalent(package);
    }
    else if(cmd == "CSDowerRsp")
    {
        HandleMsgLevelUpTalent(package);
    }
    else if(cmd == "CSABMonsterRsp")
    {
        HandleMsgCSABMonsterRsp(package);
    }
    else if(cmd == "CSAutoBattleRsp")
    {
        HandleMsgAutoBattleRsp(package);
    }
    else if(cmd == "CSABRewardRsp")
    {
        HandleMsgCSABRewardRsp(package);
    }
    else if(cmd == "CSCancelAutoBattleRsp")
    {
        HandleMsgCSCancelAutoBattleRsp(package);
    }
    else if(cmd == "CSExchangeParameterRsp")
    {
        HandleMsgSpeedUpRsp(package);
    }
    else if(cmd == "CSAttributesRsp")
    {
        HandleMsgCSAttributesRsp(package);
    }
}






