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
#include "PPVEMessage.h"
#include "PVPMessage.h"
#include "MessageHandler.h"
#include "BoneNPCManager.h"
#include "LevelDefine.h"
#include "UserData.h"
#include "TaskConfigFromLuaManager.h"
#include "GameConfigFromLuaManager.h"
//#include "iAd.cs.pb.h"

#include "cocos2d.h"
#include "tolua++.h"
#include "CCLuaEngine.h"
#include "SceneLayer.h"
#include "GameManager.h"
#include "GameResourceManager.h"
#include "cs_basic.pb.h"
#include "cs_core.pb.h"
#include "cs_battle.pb.h"
#include "errcode.pb.h"
#include "XLogicManager.h"
#include "LevelManager.h"
#include "SpriteMonsterMgr.h"
#include "MonsterData.h"
#include "SpriteSeer.h"
#include "ParticleManager.h"
#include "InstanceListLayer.h"
#include "EquipmentUpgradeUILayer.h"
#include "MainMenuLayer.h"
#include "AlchemyUILayer.h"
#include "ItemManager.h"
#include "InstanceManager.h"
#include <time.h>
#include "TaskManager.h"
#include "NetStateChecker.h"
#include "Localization.h"
#include "SpriteElfDataCenter.h"
#include "OnlineNetworkManager.h"
#include "SpriteElfManager.h"
#include "HelloWorldScene.h"
#include "SpriteElfConfigFromLua.h"
#include "FrontCoverLayer.h"
#include "MainLandManager.h"
#include "GMessage.h"
#include "NotificationCenter.h"
#include "StoryDataCenter.h"
#include "StoryInstanceDirector.h"
#include "TimeManager.h"
#include "BattleUILayer.h"
#include "MessageBoxLayer.h"
#include "SkillDispMgr.h"
#include "GameDataManager.h"
#include "GameAudioManager.h"
#include "EquipMixLayer.h"
#include "GemStonesFromLua.h"
#include "PvAIManager.h"
#include "LuaTinkerManager.h"

using namespace cocos2d;

//using namespace iAdCSProto;

void SetUserInfo( USERINFO& userInfo, const BasicUserInfo& info );
void SetUserInfo( USERINFO& userInfo, const MonsterInfo& info );

MessageHandler* MessageHandler::sInstance = NULL;



MessageHandler::MessageHandler()
	:mCurWildMsgPackage(NULL)
	,mCurNormMsgPackage(NULL)
	,m_bShowPPVEPanel(false)
{
	/// init external handler
	PPVEMessage::Get()->InitHandler(this);
    PVPMessage::Get()->InitHandler(this);
    
	registerMessageHandlerFunction();
}


MessageHandler::~MessageHandler()
{
	mCmd2HandlerFunctionList.clear();
}


MessageHandler* MessageHandler::sShareInstance()
{
	if (sInstance == NULL)
	{
		sInstance = new MessageHandler();
	}

	return sInstance;
}

void MessageHandler::Destroy()
{
	if (sInstance)
	{
		delete sInstance;
		sInstance = NULL;
	}
}


void MessageHandler::handleMessage(NORMAL_MSG_PACKAGE* package)
{	
	mCurNormMsgPackage = package;

	std::string cmd = mCurNormMsgPackage->header.cmd;
	HANDLER_FUNCTION_LIST::iterator itor = mCmd2HandlerFunctionList.find(cmd);
	if (itor != mCmd2HandlerFunctionList.end())
	{
		handlerFunc func = itor->second;
		(this->*func)();
	}
	else
	{
		/// find external message handler to handle the message
		map<std::string, BaseMsgHandler*>::iterator it = mExternalHandler.find(cmd);
		if (it != mExternalHandler.end())
		{
			BaseMsgHandler* pHandler = it->second;
			pHandler->HandlerMessage(cmd, mCurNormMsgPackage);
		}
	}

	postHandleMsg();
}


void MessageHandler::handleMessage(WILD_MSG_PACKAGE* package)
{	
	mCurWildMsgPackage = package;

	std::string luaScriptName = "Script/handleMessage.lua";
	CCLuaEngine* luaEngine = (CCLuaEngine*)CCScriptEngineManager::sharedManager()->getScriptEngine();
	if (luaEngine)
	{
		lua_State *lua_S = luaEngine->getLuaState();		
		tolua_pushusertype(lua_S,(void*)this,"MessageHandler");
	}

	//execute the script
	const char *path = GameResourceManager::sharedManager()->storedFullPathFromRelativePath(luaScriptName.c_str());
	CCScriptEngineManager::sharedManager()->getScriptEngine()->executeScriptFile(path);


	mCurWildMsgPackage = NULL;
}

////////////////////////////
///  register external message handler
void MessageHandler::registerExternalMsgHandler()
{
    ///////////////PPVE Rsp///////////////////
    
	/// register PPve message handler class
	mExternalHandler["CSPVEQueryRoomRsp"] = PPVEMessage::Get();
	mExternalHandler["CSPVEBaseInfoRsp"] = PPVEMessage::Get();
	mExternalHandler["CSPVEExitRoomRsp"] = PPVEMessage::Get();
	mExternalHandler["CSPVECloseRoomRsp"] = PPVEMessage::Get();
	mExternalHandler["CSPVEKickoffRsp"] = PPVEMessage::Get();
	mExternalHandler["CSPVEStartRsp"] = PPVEMessage::Get();
	mExternalHandler["CSPVEJoinRoomFailureRsp"] = PPVEMessage::Get();
	mExternalHandler["CSPVEJoinRoomRsp"] = PPVEMessage::Get();
    
    ///////////////PVP Rsp///////////////////
    mExternalHandler["CSPVPQueryRoomRsp"] = PVPMessage::Get();
    mExternalHandler["CSPVPBaseInfoRsp"] = PVPMessage::Get();
    mExternalHandler["CSPVPJoinRoomRsp"] = PVPMessage::Get();
    mExternalHandler["CSPVPExitRoomRsp"] = PVPMessage::Get();
    mExternalHandler["CSPVPCloseRoomRsp"] = PVPMessage::Get();
    mExternalHandler["CSPVPKickoffRsp"] = PVPMessage::Get();
    mExternalHandler["CSPVPStartRsp"] = PVPMessage::Get();
    
    ////////////Talent Rsp////////////////////
    mExternalHandler["CSQueryDowerRsp"] = PVPMessage::Get();
    mExternalHandler["CSDowerInfoRsp"] = PVPMessage::Get();
    mExternalHandler["CSDowerRsp"] = PVPMessage::Get();
    mExternalHandler["CSAccelerateDowerRsp"] = PVPMessage::Get();
    
    ///////////OnHook Rsp/////////////////////
    mExternalHandler["CSABMonsterRsp"] = PVPMessage::Get();
    mExternalHandler["CSAutoBattleRsp"] = PVPMessage::Get();
    mExternalHandler["CSABRewardRsp"] = PVPMessage::Get();
    mExternalHandler["CSExchangeParameterRsp"] = PVPMessage::Get();
    mExternalHandler["CSCancelAutoBattleRsp"] = PVPMessage::Get();
    mExternalHandler["CSAttributesRsp"] = PVPMessage::Get();
    
    //////////ShopUI Rsp///////////////////////
    mExternalHandler["CSGetShopItemsRsp"] = PVPMessage::Get();
}

//----------------------------------------------------------------------
//		register all message hander functions here
//----------------------------------------------------------------------
void MessageHandler::registerMessageHandlerFunction()
{
	//error msg
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("ErrorCode", 
		&MessageHandler::handleMsgError));
	//login msg
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSLoginRsp", 
		&MessageHandler::handleMsgLoginIn));
	//player enter map
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSEnterMapRsp",
		&MessageHandler::handleMsgPlayerEnterMap));
	////player leave map
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSLeaveMapRsp",
		&MessageHandler::handleMsgPlayerLeaveMap));
	////player walk
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSWalkRsp",
		&MessageHandler::handleMsgPlayerWalk));
	////get other players
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSGetMapUsersRsp",
		&MessageHandler::handleMsgGetOtherPlayers));

	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSBattleCreateRsp",
		&MessageHandler::handleMsgBattleCreate));

	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSMonsterMoveRsp",
		&MessageHandler::handleMsgMonsterMove));



	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSMonsterAttackRsp",
		&MessageHandler::handleMsgMonsterAttack));

	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSMonsterHitRsp",
		&MessageHandler::handleMsgMonsterHit));

	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSMonsterDieRsp",
		&MessageHandler::handleMsgMonsterDie));

	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSMonsterBloodRsp",
		&MessageHandler::handleMsgPlayerAttackMonster));

	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSBattleLeaveRsp",
		&MessageHandler::handleLeaveBattle));

	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSInstanceRsp",
		&MessageHandler::handleMsgInstanceList));

	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSAllItemsRsp",
		&MessageHandler::handleBackPackItems));
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSItemMoveRsp",
		&MessageHandler::handleBackPackMove));
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSItemRemoveRsp",
		&MessageHandler::handleBackPackItemRemove));
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSItemUpdateRsp",
		&MessageHandler::handleBackPackItemUpdate));	
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSItemAddRsp",
		&MessageHandler::handleAddItem));	
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSGetEquipLvUpCDRsp",
		&MessageHandler::handleEquipnetList));
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSEquipmentStrengthRsp",
		&MessageHandler::handleEquipmentStrength));
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSEquipmentComposeRsp",
		&MessageHandler::handleEquipCompose));
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSSearchSpiritStoneRsp",
		&MessageHandler::handleSearchSpriteStoneRsp));
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSSpiritStoneMoveBagRsp",
		&MessageHandler::handleSpriteStoneMoveStorageRsp));
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSSpiritStoneLevelUpRsp",
		&MessageHandler::handleSpriteUpgradeRsp));
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSSpiritStoneToSPRsp",
		&MessageHandler::handleSpriteTransToEnergy));
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSGetExchangeSSInfoRsp",
		&MessageHandler::handleSpriteExchangeRsp));
	
	//宝石镶嵌
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSEquipInlayGemRsp",
		&MessageHandler::handleEquipInlayGemRsp));

	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSResetGemAttrRsp",
		&MessageHandler::handleGemRecastRsp));
	
	//diamond
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSExchangeParameterRsp",
		&MessageHandler::handleExchangeParameterRsp));
	
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSAttributesRsp",
		&MessageHandler::handleAttributesRsp));
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSGetUserInfoRsp",
		&MessageHandler::handleUserInfoRsp));
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSLevelUpRsp",
		&MessageHandler::handleLevelUpRsp));
	
	
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSCrtRoleRsp",
		&MessageHandler::handleAckMsgCreateRole));	

	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSPlayerAttackRsp",
		&MessageHandler::handlePlayerAttack));	

	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSSkillBeginRsp",
		&MessageHandler::handleSkillBegin));	

	// Note: TASK
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSTaskInfoRsp",
		&MessageHandler::handleRsqTaskInfoMessage));	
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSTaskLogRsp",
		&MessageHandler::handleRsqTaskLogMessage));	
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSTaskDoStepRsp",
		&MessageHandler::handleRsqTaskStepMessage));	

	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSPingRsp",
		&MessageHandler::handleRsqNetStateMessage));		

	// Note: Elf
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSMonListRsp",
		&MessageHandler::handleRsqElfListMessage));
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSSetMonStatusRsp",
		&MessageHandler::handleRsqElfStateMessage));	

	//多人副本
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSBattleUserJoinRsp",
		&MessageHandler::handleMsgUserJoin));

	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSBattleUserLeaveRsp",
		&MessageHandler::handleMsgUserLeave));	

	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSBattleMoveRsp",
		&MessageHandler::handleMsgBattleMove));

	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSQueryShardRsp",
		&MessageHandler::handleQuerySharedRsp));

	// PVP
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSPlayerHitPlayerRsp", &MessageHandler::handlePVPPlayerHitPlayer));

	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSOnceRsp", &MessageHandler::handleOnceRspMessage));

	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSBattleLoadCompleteRsp",
		&MessageHandler::handleMsgLoadComplete));

	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSBattleTimeoutRsp",
		&MessageHandler::handleMsgBattleTimeout));

	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSBattlePlayerDelRsp",
		&MessageHandler::handleMsgPlayerDie));

	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSPlayerHPRsp",
		&MessageHandler::handleMsgPlayerHP));

	// Skill UI
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSGetUserSkillRsp",
		&MessageHandler::handleMsgGetUserSkillRsp));

	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSUserSkillDiffRsp",
		&MessageHandler::handleMsgUserSkillDiffRsp));

	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSAddUserSkillRsp",
		&MessageHandler::handleMsgAddUserSkillRsp));

	// Note: SpriteElf UI
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSTrainDetermineRsp",
		&MessageHandler::handleMsgTrainDetermineRsp));

	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSTrainRsp",
		&MessageHandler::handleMsgTrainRsp));

	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSBattleMonsterCreateRsp",
		&MessageHandler::handleMsgBattleMonsterCreateRsp));

	// Note: 云游系统
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSExploreRsp",
		&MessageHandler::handleExploreRsp));

	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSExploreDetermineRsp",
		&MessageHandler::handleExploreDetermineRsp));

	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSNotifyMoneyConfInfoRsp",
		&MessageHandler::handleNotifyMoneyConfigInfo));

	// pvai
	mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("CSPVAIInfoRsq",
		&MessageHandler::handleMsgPvAIInfoRsq));
			
	//// handle message echo
	//mCmd2HandlerFunctionList.insert(std::pair<std::string, handlerFunc>("iAdCSProto.cli_echo_rsp_t",
	//	&MessageHandler::handleMsgEcho));

	registerExternalMsgHandler();
}

//----------------------------------------------------------------------
void MessageHandler::postHandleMsg()
{
	mCurNormMsgPackage = NULL;
}

//----------------------------------------------------------------------
//		all message hander functions here
//----------------------------------------------------------------------
void MessageHandler::handleMsgError()
{

	db_errcode_t errorId = (db_errcode_t)mCurNormMsgPackage->header.ret;
	CCLog("handleMsgError: %d",errorId);
	{
		std::string content = "";
		switch(errorId)
		{
		case olerr_enter_manor_times_max:			
			content = Localizatioin::getLocalization("S_EnterMonorTimesMax_Content");
			break;
		case olerr_warm_sport_lv_max:
			content = Localizatioin::getLocalization("S_WarmSportLvMax_Content");
			break;
		case olerr_not_enough_diamond:
			content = Localizatioin::getLocalization("S_Gh_Diamond_Content");
			break;
		case olerr_not_enough_coin:
			content = Localizatioin::getLocalization("S_Not_Enough_Coin_Content");
			break;
		case olerr_not_enough_exploit:
			content = Localizatioin::getLocalization("S_Not_Enough_Exploit_Content");
			break;
		case olerr_not_enough_level:
			content = Localizatioin::getLocalization("S_Not_Enough_Level_Content");
			break;
		case dberr_role_notfound:
		case dberr_role_exists:
		case dberr_crtrole_time_limit:
		case dberr_duplicated_nickname:
		case olerr_can_transfer_next:
			XLogicManager::sharedManager()->logInError(errorId);
			break;
		case olerr_nofound_explore_id:
			break;
		case olerr_not_enough_explore_times:
			break;
		default:
			break;
		}

		if (content != "")
		{
			ShowMessage(content.c_str());
		}
	}

}

//----------------------------------------------------------------------
void MessageHandler::handleMsgBattleCreate()
{
    CCLog("handleMsgBattleCreate callback!\n");
    
	CSBattleCreateRsp* msg = dynamic_cast<CSBattleCreateRsp*>(mCurNormMsgPackage->msg);	
	
	MonsterData::GetMonsterInfo()->reset();

	 UserData::Get()->clearOtherUserInfo();
	EntityInfo::Get()->Clear();

	int monsterCount = msg->monsterinfo_size();
	for (int i = 0; i < monsterCount; ++i)
	{
		USERINFO* pMonsterInfo = new USERINFO();
		SetUserInfo(*pMonsterInfo, msg->monsterinfo(i));
		CCAssert(pMonsterInfo->id != UserData::getUserId(),"monster = userID");
		EntityInfo::Get()->Set(pMonsterInfo);
		MonsterData::GetMonsterInfo()->addMonser(msg->monsterinfo(i));
	}

	int userCount = msg->userinfo_size();
	USERINFO mUserData = UserData::GetUserInfo();
	for(int i=0;i<userCount;i++)
	{
		BasicUserInfo info = msg->userinfo(i);

		if(info.uid() == mUserData.id)
		{
			SetUserInfo(mUserData, info);
			unsigned int cell_x = info.xpos();
			unsigned int cell_y = info.ypos();
			CCPoint point = LevelManager::sShareInstance()->pointCellToPixel(ccp(cell_x,cell_y));
			mUserData.xPos = point.x;
			mUserData.yPos = point.y;
			UserData::SetUserInfo(mUserData);
			InstanceManager::Get()->setPlayerPosition(point);
			break;
		}
		//else
		//{
		//	unsigned int side = 0;
		//	if(info.has_battle_side())
		//		side = info.battle_side();
		//}
	}

	unsigned int mapId = msg->map_id();
	unsigned int battleId = msg->battle_id();
	InstanceManager::Get()->setCurInstanceId(battleId);
	LevelManager::sShareInstance()->SetBattleLevel(battleId);

	int portalX = msg->portal().xpos();
	int portalY = msg->portal().ypos();
	CCPoint portalPos =  LevelManager::sShareInstance()->pointCellToPixel(ccp(portalX,portalY));
	InstanceManager::Get()->setPortalPosition(portalPos);

	unsigned int portalId = msg->portal_map_id();
	InstanceManager::Get()->setPortalId(portalId);	

	if (msg->has_timeout())
	{
		int instanceTime = msg->timeout();
		InstanceManager::Get()->setInstanceTime(instanceTime);
	}

	int birthCount = msg->monsterbirth_size();
	vector<CCPoint> points;
	for (int i = 0; i < msg->monsterbirth_size(); i++)
	{
		CCPoint monsterBornPoint = LevelManager::sShareInstance()->pointCellToPixel(ccp(msg->monsterbirth(i).xpos(), msg->monsterbirth(i).ypos()));
		points.push_back(monsterBornPoint);
	}
	InstanceManager::Get()->setMonsterBornPoints(points);
	
	XLogicManager::sharedManager()->goToFb(mapId, battleId);
}

void MessageHandler::handleMsgBattleMonsterCreateRsp()
{
	CSBattleMonsterCreateRsp* msg = dynamic_cast<CSBattleMonsterCreateRsp*>(mCurNormMsgPackage->msg);	
	
	int monsterCount = msg->monsterinfo_size();
	for (int i = 0; i < monsterCount; ++i)
	{		
		MonsterInfo info = msg->monsterinfo(i);
		MonsterInitInfo mInitInfo;
		mInitInfo.uid = info.id();
		mInitInfo.typeId = info.type_id();
		CSPoint position = info.point();
		mInitInfo.totalHp = info.blood();
		mInitInfo.speed = info.speed();
		mInitInfo.isBoss = info.boss();
		mInitInfo.pos = LevelManager::sShareInstance()->pointCellToPixel(ccp(position.xpos(), position.ypos()));
		mInitInfo.monsterName = "monster";
		mInitInfo.isElite = info.elite();

		USERINFO* pMonsterInfo = new USERINFO();
		SetUserInfo(*pMonsterInfo, msg->monsterinfo(i));
		CCAssert(pMonsterInfo->id != UserData::getUserId(),"monster = userID");
		EntityInfo::Get()->Set(pMonsterInfo);

		LevelLayer * layer = LevelManager::sShareInstance()->getCurrentLevelLayer();
		if (layer)
		{
			layer->addMonster(mInitInfo);	
		}
		else
		{			
			MonsterData::GetMonsterInfo()->addMonser(msg->monsterinfo(i));
		}
		//LevelManager::sShareInstance()->getCurrentLevelLayer()->addMonster(uid, nick.c_str(), typeId,totalHp, pixPoint, speed, isBoss);		
	}
}

void MessageHandler::handleMsgMonsterMove()
{
	CSMonsterMoveRsp* msg = dynamic_cast<CSMonsterMoveRsp*>(mCurNormMsgPackage->msg);	

	int moveCount = msg->moves_size();
	for (int i = 0; i < moveCount; ++i)
	{
		MonsterMoveValue moves = msg->moves(i);
		int pathCount = moves.paths_size();
		int uid = moves.id();

		if(pathCount > 0)
		{
			SpriteMonster * monster = SpriteMonsterMgr::Get()->GetMonster(uid);
			//CCAssert(monster != NULL, "can't find the monster when try to move it!");
			if (monster)
			{
				CCPoint pos = monster->getPosition();
				CCPoint cellPos =  LevelManager::sShareInstance()->pointPixelToCell(pos);
				//CCLOG("now pos: %f, %f", cellPos.x, cellPos.y);

				std::vector<CCPoint> points;
				for(int j = 0; j < pathCount; ++j)
				{
					CSPoint path = moves.paths(j);	
					CCPoint pixPoint = LevelManager::sShareInstance()->pointCellToPixel(ccp(path.xpos(), path.ypos()));
					bool isReachable = LevelManager::sShareInstance()->getCurrentLevelLayer()->getPhysicsLayer()->isPointReachable(pixPoint);
					if (!isReachable)
					{
						//ASSERT(0, "Point unreachable");
					}
					//CCLOG("points: %d, %d", path.xpos(), path.ypos());
					points.push_back(pixPoint);
				}

				//CCLOG("move monster");
				monster->onEventMsgMove(points);
			}

		}
	}
}

void MessageHandler::handleMsgMonsterDie()
{
	CSMonsterDieRsp* msg = dynamic_cast<CSMonsterDieRsp*>(mCurNormMsgPackage->msg);	
	int deadCount = msg->monsters_size();
	for(int i=0;i<deadCount;i++)
	{
		unsigned int uid = msg->monsters(i);	
		SpriteMonster* monster = SpriteMonsterMgr::Get()->GetMonster(uid);
		if(monster)
		{
			monster->onEventMsgDead();
		}
	}
}

void MessageHandler::handleMsgMonsterHit()
{
	CSMonsterHitRsp* msg = dynamic_cast<CSMonsterHitRsp*>(mCurNormMsgPackage->msg);	
	int userCount = msg->users_size();
	for(int i=0;i<userCount;i++)
	{
		unsigned int uid = msg->users(i).userid();
		unsigned int blood = msg->users(i).blood();		
		unsigned int type = msg->users(i).hurt_type();

		LevelLayer* pLevelLayer = LevelManager::sShareInstance()->getCurrentLevelLayer();
		if(pLevelLayer)
		{
			SpriteSeer* hero = pLevelLayer->getPlayer(uid);
			if(hero)
			{
				switch(type)
				{
				case 1: // 闪避
					GameManager::Get()->GetSceneLayer()->getMainMenuLayer()->HandleAttackMissEffect(hero->getPosition());
					break;
				case 2: // 格挡
					hero->ByAttacked(blood);
					GameManager::Get()->GetSceneLayer()->getMainMenuLayer()->HandleAttackBlockEffect(hero->getPosition());
					break;
				case 3: // 暴击
					hero->ByAttacked(blood, true);
					break;
				default:
					hero->ByAttacked(blood);
					break;
				}
				
			}
		}

		
	}
}

void MessageHandler::handleMsgPlayerAttackMonster()
{
	CSMonsterBloodRsp* msg = dynamic_cast<CSMonsterBloodRsp*>(mCurNormMsgPackage->msg);
		unsigned int count = msg->monsters_size();
		for(size_t i=0;i<count;i++)
		{
			CSAttackMonsterBackInfo monsterInfo = msg->monsters(i);
			SpriteMonster* monster = SpriteMonsterMgr::Get()->GetMonster(monsterInfo.id());
			if(!monster)
				continue;
			unsigned int curBlood = monster->getBlood();
			if(curBlood != monsterInfo.blood())
			{
				monster->setBlood(monsterInfo.blood());					
			}
		}

		if(count > 0)
		{
			// UI血条只显示最后一个怪
			CSAttackMonsterBackInfo currentMonsterInfo = msg->monsters(count -1);
			unsigned int monsterId = currentMonsterInfo.id();
			unsigned int monsterType = currentMonsterInfo.monster_type();
			SpriteMonster* monster = SpriteMonsterMgr::Get()->GetMonster(monsterId);
			if(monster)
			{
				const char* mosterNameIndex = LuaTinkerManager::Get()->getLuaConfig<const char *>("MonsterBasicInfomation", "MonsterBasicInfomation", monsterType, "Name");
				unsigned int isBoss = LuaTinkerManager::Get()->getLuaConfig<unsigned int>("MonsterBasicInfomation", "MonsterBasicInfomation", monsterType, "IsBoss");
				CCAssert(mosterNameIndex,"monster name index is null");
				const char* monsterName = Localizatioin::getLocalization(mosterNameIndex);
				CCAssert(monsterName,"monster name is null");
				unsigned int nameType = 0;
				if(currentMonsterInfo.elite())
				{
					nameType = 1;
				}
				if(isBoss > 0)
				{
					nameType = 2;
				}

				ParticleManager::Get()->SetEnemyHpLable(monsterId,currentMonsterInfo.blood(),monster->getTotalBlood(),monsterName,nameType);
			}
		}
}

void MessageHandler::handleLeaveBattle()
{
	setNeedShowPPVEAfterBacktoTown(false);
	TimeManager::Get()->stopTimer(TIMER_INSTANCE_COUNTDOWN);
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{				
		BattleCoverLayer* battleCoverLayer = mLayer->GetBattleCoverLayer();
		battleCoverLayer->closeBattleCoverLayer(NULL);
	}

	if (LevelManager::sShareInstance()->isCurrentPVAILevel())
	{
		PvAIManager::Get()->setAIAutoAttack(false);
	}
	//GameDataManager::Get()->setHeroAutoAttack(false);
	CSBattleLeaveRsp* msg = dynamic_cast<CSBattleLeaveRsp*>(mCurNormMsgPackage->msg);
	//InstanceManager::Get()->setOneInstanceStarts(InstanceManager::Get()->getCurInstanceId(),msg->star());
	if(msg != NULL)
	{
		if(msg->initiative())
		{ // 玩家主动离开
			XLogicManager::sharedManager()->backToTown();
		}
		else
		{ 
			// 怪杀光，离开FB
			/// get current map type
			bool bPPveMap = LevelManager::sShareInstance()->isCurrentPPVELevel();
			
			if (bPPveMap)
			{
				setNeedShowPPVEAfterBacktoTown(true);
			}

			// Note: 判断此处是否有剧情动画触发
			bool bCutAnimation = false;
			bool bMainLandLevel = MainLandManager::Get()->isMainLand(LevelManager::sShareInstance()->getCurMapId());
			bool bPVEMode = LevelManager::sShareInstance()->isCurrentPVELevel();
			bool bStoryMode = false;
			unsigned int nStoryType = 0;
			//bPVEMode = false;
			int nInstanceStars = InstanceManager::Get()->getOneInstanceStarts(InstanceManager::Get()->getCurInstanceId());
			if(bPVEMode && false == bMainLandLevel && nInstanceStars <= 0)
			{
				unsigned int mapId = LevelManager::sShareInstance()->getCurMapId();
				bStoryMode = StoryDataCenter::Get()->IsOneItemHasStory(InstanceManager::Get()->getCurInstanceId(),mapId,1,nStoryType);
				if (bStoryMode)
				{
					// Note: 进入副本时触发剧情
					if (nStoryType == 1)
					{
						StoryInstanceDirector::Get()->Begin(InstanceManager::Get()->getCurInstanceId(),mapId,nStoryType);
						bCutAnimation = true;
					}
				}
			}
			if (false == bCutAnimation)
			{
				XLogicManager::sharedManager()->FinishBattle();
				//if (bPVEMode)
				//{
				//	OnlineNetworkManager::sShareInstance()->sendOnceSetReqMessage(InstanceManager::Get()->getCurInstanceId());
				//}
			}
		}		
	}
}

void MessageHandler::handleMsgMonsterAttack()
{
	CSMonsterAttackRsp* msg = dynamic_cast<CSMonsterAttackRsp*>(mCurNormMsgPackage->msg);	

	int attackCount = msg->attacks_size();
	for (int i = 0; i < attackCount; ++i)
	{
		CSMonsterAttackInfo attack = msg->attacks(i);
		
		int uid = attack.id();
		int animId = attack.action_id();
		CSPoint position = attack.pos();
		CSPoint direct = attack.direct();		
		int userId = attack.userid();
		int skillType = attack.type();

		CCPoint attackDir = ccp(direct.xpos(), direct.ypos());
		
		SkillInfo info;
		info.effectId = 0;
		
		//if (skillType != 1)
		{
			int effectId = attack.effect_id();
			CSPoint spos = attack.start_pos();
			CSPoint epos = attack.end_pos();
			CCPoint startPos = LevelManager::sShareInstance()->pointCellToPixel(ccp(spos.xpos(), spos.ypos()));
			CCPoint endPos = LevelManager::sShareInstance()->pointCellToPixel(ccp(epos.xpos(), epos.ypos()));
			float speed = attack.skill_speed();
			float delayTime = attack.delay_time();

		
			info.effectId = effectId;
			info.startPosition = startPos;
			info.endPosition = endPos;
			info.speed = speed;
			info.delayTime = delayTime;
		}


		CCPoint pixPosition = LevelManager::sShareInstance()->pointCellToPixel(ccp(position.xpos(), position.ypos()));
		
		SpriteMonster * monster = SpriteMonsterMgr::Get()->GetMonster(uid);
		if(monster)
		{
			if(monster->fsm_rule.GetState() == MONSTER_STATE_HURT)
			{
				continue;
			}

			monster->onEventMsgAttack(pixPosition, attackDir, animId, info);
			//CCLOG("monster attack");
			//SpriteSeer * seer = LevelManager::sShareInstance()->getCurrentLevelLayer()->getPlayer(userId);
			//if(seer)
			//{
			//	//根据画面上位置调整方向
			//	CCPoint seerPos = seer->getPosition();
			//	CCPoint seerCell = LevelManager::sShareInstance()->pointPixelToCell(seerPos);

			//	CCPoint monsterPos = monster->getPosition();
			//	CCPoint monsterCell = LevelManager::sShareInstance()->pointPixelToCell(monsterPos);

			//	//CCLOG("player position: %f, %f, server monster position: %d, %d, local monster position: %f, %f", 
			//	//	seerCell.x, seerCell.y, position.xpos(), position.ypos(), monsterCell.x, monsterCell.y);


			//	float delayDistance = ccpDistance(monsterPos, pixPosition);
			//	//CCLOG("--------------------------------attack delay: %f", delayDistance);				
			//}		
		}
	}
}
//----------------------------------------------------------------------
void MessageHandler::handleMsgLoginIn()
{
	//XLogicManager::sharedManager()->createRole("welseyTest6",0);
	//return;

	CSLoginRsp* msg = dynamic_cast<CSLoginRsp*>(mCurNormMsgPackage->msg);	
	
	//XLogicManager::sharedManager()->onConnectToSever();

	USERINFO mUserData = UserData::GetUserInfo();
	mUserData.tokenId = msg->tokenid();
	mUserData.level = msg->lv();
	//mUserData.exp = msg->exp();
	mUserData.type = msg->type();
	strcpy(mUserData.szName,msg->name().c_str());
	UserData::SetUserInfo(mUserData);

	CCLog("tokenid: %d",msg->tokenid());
	CCLog("name: %s",msg->name().c_str());
	CCLog("lv: %d",msg->lv());
	CCLog("exp: %d",msg->exp());

	MonsterData::GetMonsterInfo()->reset();
	XLogicManager::sharedManager()->loginSuccess();
	
}

//----------------------------------------------------------------------
void MessageHandler::handleMsgPlayerEnterMap()
{
	if(LevelManager::sShareInstance()->getCurrentLevelStatus() == EChangeMap)
	{
		return;
	}

	CSEnterMapRsp* msg = dynamic_cast<CSEnterMapRsp*>(mCurNormMsgPackage->msg);

	BasicUserInfo infor = msg->userinfo();
	USERINFO mUserData = UserData::GetUserInfo();

	//ASSERT(infor.uid() == mUserData.id,"Not a Same UUID");
	if(infor.uid() == mUserData.id)
	{
		SetUserInfo(mUserData, infor);

		mUserData.level = infor.lv();
		mUserData.mapId = msg->mapid();
		mUserData.xPos = infor.xpos();
		mUserData.yPos = infor.ypos();
		
		// 这个时候还没有物理层。
		//CCPoint pixelPos = LevelManager::sShareInstance()->pointCellToPixel(ccp(infor.xpos(), infor.ypos()));
		//mUserData.xPos = pixelPos.x;
		//mUserData.yPos = pixelPos.y;

		mUserData.orient = infor.orient();
		strcpy(mUserData.szName,infor.name().c_str());
		UserData::SetUserInfo(mUserData);
		MonsterData::GetMonsterInfo()->reset();

		if(!XLogicManager::sharedManager()->isAlreadyLogin())
		{	// first login ,player enter map
			XLogicManager::sharedManager()->goToFrontend();
			MainLandManager::Get()->setCurCityId(mUserData.mapId);
		}
		else
		{
			XLogicManager::sharedManager()->changeMap(mUserData.mapId, KMapFromTransition);

			/// to do , show ppve hall if win in ppve battle.
			checkNeedShowPPVEPanel();
		}
		
	}
	else
	{
		//
		unsigned int uid = infor.uid();
		std::string nick = infor.name();
		int xPos = infor.xpos();
		int yPos = infor.ypos();

		// 这个时候还没有物理层。
		//CCPoint pixelPos = LevelManager::sShareInstance()->pointCellToPixel(ccp(infor.xpos(), infor.ypos()));
		//xPos = pixelPos.x;
		//yPos = pixelPos.y;

		int orient = infor.orient();
		int type = infor.type();
		unsigned int side = infor.battle_side();
		
		USERINFO* pUserInfo = UserData::Get()->GetUserInfo(uid);
		if(pUserInfo)
		{
			SetUserInfo(*pUserInfo, infor);
			UserData::Get()->SetUserInfo(pUserInfo->id, *pUserInfo);
		}
		else
		{
			USERINFO otherUserInfo;		
			SetUserInfo(otherUserInfo, infor);
			UserData::Get()->SetUserInfo(otherUserInfo.id, otherUserInfo);
		}
		
		//
		LevelLayer* layer = LevelManager::sShareInstance()->getCurrentLevelLayer();
		if (layer)
		{
			layer->addOtherPlayer(uid, nick.c_str(), type, ccp(xPos, yPos), orient, side);
		}
		else
		{
			LevelManager::OTHER_PLAYER_INFO playerInfo;
			playerInfo.uid = uid;
			playerInfo.userName = nick;
			playerInfo.type = type;
			playerInfo.pos.x = xPos;
			playerInfo.pos.y = yPos;
			playerInfo.orient = orient;
			playerInfo.battleSide = side;

			LevelManager::sShareInstance()->m_otherPlayerInfo.push(playerInfo);
		}
	}
	CCLog("seer enter map: %s, %d pos: %d, %d ", infor.name().c_str(), msg->mapid(), infor.xpos(), infor.ypos());	
}

//----------------------------------------------------------------------
void MessageHandler::handleMsgPlayerLeaveMap()
{
	CSLeaveMapRsp* msg = dynamic_cast<CSLeaveMapRsp*>(mCurNormMsgPackage->msg);
	//
	//int mapId = msg->map_id();	
	unsigned int uid = msg->uid();
	LevelLayer* layer = LevelManager::sShareInstance()->getCurrentLevelLayer();
	if (layer)
	{
		layer->removeOtherPlayer(uid);
	}
	
	CCLog("seer leave map: %d ", uid);
}

//----------------------------------------------------------------------
void MessageHandler::handleMsgPlayerWalk()
{
	bool isMainLandLevel = MainLandManager::Get()->isMainLand(LevelManager::sShareInstance()->getCurMapId());
	if (!isMainLandLevel)
	{
		return;
	}
	CSWalkRsp* msg = dynamic_cast<CSWalkRsp*>(mCurNormMsgPackage->msg);

	unsigned int uuid = msg->uid();
	unsigned int xPos = msg->xpos();
	unsigned int yPos = msg->ypos();
	unsigned int animID = msg->animid();
	bool bFlip = msg->flip();

	//int xPos = msg->dest_x();
	//int yPos = msg->dest_y();

	LevelLayer* layer = LevelManager::sShareInstance()->getCurrentLevelLayer();
	if (layer)
	{
		//layer->updateOtherPlayer(uuid,ccp(xPos,yPos), animID, bFlip);
		LevelLayer::WAKL_INFO walkInfo;
		walkInfo.walk.uid = uuid;
		walkInfo.walk.pt.x = xPos;
		walkInfo.walk.pt.y = yPos;

		walkInfo.walk.pt = LevelManager::sShareInstance()->pointCellToPixel(walkInfo.walk.pt);

		walkInfo.walk.animID = animID;
		walkInfo.walk.bFlip = bFlip;

		std::map<unsigned int, LevelLayer::WAKL_INFO>::iterator iter;
		iter = layer->m_walkInfo.find(uuid);
		if(iter != layer->m_walkInfo.end())
		{
			iter->second.walk = walkInfo.walk;
		}
		else
		{
			walkInfo.idleTime.time = 0.0f;
			walkInfo.idleTime.curTime = 0.0f;
			layer->m_walkInfo.insert(std::make_pair(uuid, walkInfo));
		}
		
	}

	CCLog("receive: seer walk dest: %d, %d, %d",uuid, xPos, yPos);
}


//----------------------------------------------------------------------
void MessageHandler::handleMsgGetOtherPlayers()
{
	bool isMainLandLevel = MainLandManager::Get()->isMainLand(LevelManager::sShareInstance()->getCurMapId());
	if (!isMainLandLevel)
	{
		return;
	}
	CSGetMapUsersRsp* msg = dynamic_cast<CSGetMapUsersRsp*>(mCurNormMsgPackage->msg);
	int playerCount = msg->userinfo_size();
	CCLog("CSGetMapUsersRsp: size = %d",playerCount);
	for (int i = 0; i < playerCount; ++i)
	{
		BasicUserInfo info = msg->userinfo(i);
		//
		int uid = info.uid();
		std::string nick = info.name();
		int xPos = info.xpos();
		int yPos = info.ypos();
		int type = info.type();
		unsigned int side = info.battle_side();

		
		if(uid != UserData::getUserId())
		{
			USERINFO* pUserInfo = UserData::Get()->GetUserInfo(uid);
			if(pUserInfo)
			{
				SetUserInfo(*pUserInfo, info);
				UserData::Get()->SetUserInfo(uid, *pUserInfo);
			}
			else
			{
				USERINFO otherUserInfo;		
				SetUserInfo(otherUserInfo, info);
				UserData::Get()->SetUserInfo(otherUserInfo.id, otherUserInfo);
			}
			
			LevelLayer* layer = LevelManager::sShareInstance()->getCurrentLevelLayer();
			if (layer)
			{
				layer->addOtherPlayer(uid, nick.c_str(), type, ccp(xPos, yPos), info.orient(), side);
			}
			else
			{
				LevelManager::OTHER_PLAYER_INFO playerInfo;
				playerInfo.uid = uid;
				playerInfo.userName = nick;
				playerInfo.type = type;
				playerInfo.pos.x = xPos;
				playerInfo.pos.y = yPos;
				playerInfo.battleSide = side;

				LevelManager::sShareInstance()->m_otherPlayerInfo.push(playerInfo);
			}
		}

		CCLog("add other seer %d ", uid);
	}
}

void MessageHandler::handleAckMsgCheckSession()
{

}

void MessageHandler::handleQuerySharedRsp()
{
	CSQueryShardRsp* msg = dynamic_cast<CSQueryShardRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
		CCArray* children = scene->getChildren();
		CCObject* child;
		CCARRAY_FOREACH(children, child)
		{
			HelloWorld* layer = dynamic_cast<HelloWorld*>(child);
			if(layer && layer->getFrontLayer())
			{
				layer->getFrontLayer()->onReceiveSeverInfo(msg);
			}
		}
		
	}
}

void MessageHandler::handleAckMsgCreateRole()
{
	CSCrtRoleRsp* msg = dynamic_cast<CSCrtRoleRsp*>(mCurNormMsgPackage->msg);	

	USERINFO mUserData = UserData::GetUserInfo();
	mUserData.tokenId = msg->tokenid();
	mUserData.mapId = msg->mapid();
	mUserData.xPos = msg->xpos();
	mUserData.yPos = msg->ypos();
	mUserData.orient = msg->orient();
	UserData::SetUserInfo(mUserData);

	// to do
}


void MessageHandler::handleMsgBattlePVE()
{
	
}

void MessageHandler::handleMsgEcho()
{
	
}

void MessageHandler::setNeedShowPPVEAfterBacktoTown(bool bShowPPve)
{
	this->m_bShowPPVEPanel = bShowPPve;
}

void MessageHandler::checkNeedShowPPVEPanel()
{
	if (this->m_bShowPPVEPanel)
	{
		GetPPVELayer();
		m_bShowPPVEPanel = false;
	}
}

void MessageHandler::handleBackPackItems()
{
	CSAllItemsRsp* msg = dynamic_cast<CSAllItemsRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		ItemManager* itemManager = ItemManager::Get();
		unsigned int defaultPackPos = msg->def_bag_size();
		unsigned int defaultStoragePos = msg->def_store_size();
		unsigned int defaultAlchemyStoragePos = msg->def_ss_bag_size();
		unsigned int defaultAlchemyBagPos = msg->def_ss_store_size();
		unsigned int defaultEquipUpgradeTimes = msg->def_equip_lvup_max_times();
		unsigned int defaultResetGemsTimes = msg->def_reset_gem_times();
		unsigned int defaultManorTimes = msg->def_enter_manor_times();
		itemManager->resetItems();
		itemManager->setBackPackDefaultPos(defaultPackPos);
		itemManager->setStorageDefaultPos(defaultStoragePos);
		itemManager->setAlchemyBackDefaultCapacity(defaultAlchemyBagPos);
		itemManager->setAlchemyStorageDefaultCapacity(defaultAlchemyStoragePos);
		itemManager->setEquipMaxTimes(defaultEquipUpgradeTimes);
		int count = msg->items_size();
		for(int i=0;i<count;i++)
		{
			CSItemInfo packInfo = msg->items(i);
			BackPackItem* item = itemManager->setItem(packInfo.pos(),packInfo.item_id(),packInfo.item_level(),packInfo.item_num());
			if(item)
			{
				unsigned int attrCount = packInfo.item_attrs_size();
				for(unsigned int j=0; j<attrCount; j++)
				{
					ITEMATTR* attr = new ITEMATTR();
					CSItemAttr cs_attr = packInfo.item_attrs(j);
					attr->attr_basic_value = cs_attr.attr_basic_value();
					attr->attr_key = cs_attr.attr_key();
					if(cs_attr.has_attr_intensify_value())
					{
						attr->attr_intensify_value = cs_attr.attr_intensify_value();
					}
					if(cs_attr.has_attr_gem_value())
					{
						attr->attr_gem_value = cs_attr.attr_gem_value();
					}
					item->m_attribution->push_back(attr);
				}

				if(packInfo.has_equip_info())
				{
					item->setEquipInfo(packInfo.equip_info());
				}

				if(packInfo.has_ss_info())
				{
					item->setSpriteInfo(packInfo.ss_info());
				}
			}
		}
		XLogicManager::sharedManager()->receivedItemsInfo();
		//itemManager->openBackPack();
	}
}

void MessageHandler::handleAddItem()
{
	CSItemAddRsp* msg = dynamic_cast<CSItemAddRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		int count = msg->items_size();
		for(int i=0;i<count;i++)
		{
			CSItemInfo packInfo = msg->items(i);
			BackPackItem* item = ItemManager::Get()->setItem(packInfo.pos(),packInfo.item_id(),packInfo.item_level(),packInfo.item_num());
			if(item)
			{

				unsigned int attrCount = packInfo.item_attrs_size();
				for(unsigned int j=0; j<attrCount; j++)
				{
					ITEMATTR* attr = new ITEMATTR();
					CSItemAttr cs_attr = packInfo.item_attrs(j);
					attr->attr_basic_value = cs_attr.attr_basic_value();
					attr->attr_key = cs_attr.attr_key();
					if(cs_attr.has_attr_intensify_value())
					{
						attr->attr_intensify_value = cs_attr.attr_intensify_value();
					}
					if(cs_attr.has_attr_gem_value())
					{
						attr->attr_gem_value = cs_attr.attr_gem_value();
					}
					item->m_attribution->push_back(attr);
				}

				if(packInfo.has_equip_info())
				{
					item->setEquipInfo(packInfo.equip_info());
				}
				if(packInfo.has_ss_info())
				{
					item->setSpriteInfo(packInfo.ss_info());
				}
			}
		}
	}
}

void MessageHandler::handleMsgInstanceList()
{
	CSInstanceRsp* msg = dynamic_cast<CSInstanceRsp*>(mCurNormMsgPackage->msg);	

	int instanceCount = msg->instances_size();
	std::vector<InstanceInfo> instanceInfos;
	for (int i = 0; i < instanceCount; ++i)
	{
		CSInstanceRsp_CSInstance instance = msg->instances(i);

		InstanceInfo instanceInfo;
		instanceInfo.id = instance.instance_id();
		instanceInfo.active = instance.activate();
		instanceInfo.star = instance.star();	

		instanceInfos.push_back(instanceInfo);		
	}

	if (InstanceManager::Get()->isInstanceListChanged(instanceInfos))
	{
		InstanceManager::Get()->instanceList.clear();
		int count = instanceInfos.size();

		for(int i=0;i < count;i++)
		{
			InstanceManager::Get()->instanceList.push_back(instanceInfos[i]);
		}

		InstanceListLayer * instanceListLayer = GetInstanceListLayer();
		if(instanceListLayer)
		{
			instanceListLayer->onEventMsgInstanceList(instanceInfos);
		}
	}
}

void MessageHandler::handleBackPackItemRemove()
{
	CSItemRemoveRsp* msg = dynamic_cast<CSItemRemoveRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		unsigned int pos = msg->pos();
		unsigned int itemId = msg->item_id();
		ItemManager::Get()->removeItem(pos,itemId);
	}
}

void MessageHandler::handleBackPackMove()
{
	CSItemMoveRsp* msg = dynamic_cast<CSItemMoveRsp*>(mCurNormMsgPackage->msg);

	if(msg)
	{
		unsigned int pos_from = msg->pos_from();
		unsigned int pos_to = msg->pos_to();
		ItemManager::Get()->exchangeItemPos(pos_from,pos_to);
	}
}

void MessageHandler::handleBackPackItemUpdate()
{
	CSItemUpdateRsp* msg = dynamic_cast<CSItemUpdateRsp*>(mCurNormMsgPackage->msg);

	if(msg)
	{
		ItemManager* itemManager = ItemManager::Get();
		int count = msg->item_size();
		for(int i=0;i<count;i++)
		{
			CSItemInfo packInfo = msg->item(i);
			BackPackItem* item = itemManager->setItem(packInfo.pos(),packInfo.item_id(),packInfo.item_level(),packInfo.item_num());
			if(item)
			{
				unsigned int attrCount = packInfo.item_attrs_size();
				for(unsigned int j=0; j<attrCount; j++)
				{
					ITEMATTR* attr = new ITEMATTR();
					CSItemAttr cs_attr = packInfo.item_attrs(j);
					attr->attr_basic_value = cs_attr.attr_basic_value();
					attr->attr_key = cs_attr.attr_key();
					if(cs_attr.has_attr_intensify_value())
					{
						attr->attr_intensify_value = cs_attr.attr_intensify_value();
					}
					if(cs_attr.has_attr_gem_value())
					{
						attr->attr_gem_value = cs_attr.attr_gem_value();
					}
					item->m_attribution->push_back(attr);
				}

				if(packInfo.has_equip_info())
				{
					item->setEquipInfo(packInfo.equip_info());
				}
				if(packInfo.has_ss_info())
				{
					item->setSpriteInfo(packInfo.ss_info());
				}
			}
		}
	}
}

void MessageHandler::handleEquipnetList()
{
	CSGetEquipLvUpCDRsp* msg = dynamic_cast<CSGetEquipLvUpCDRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		ItemManager* itemManager = ItemManager::Get();
		unsigned int coldTime = msg->cold_time();
		if(GameManager::Get()->GetSceneLayer() != NULL)
		{
			MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
			if (mLayer)
			{
				mLayer->ShowEquipmentUpgradeUI(coldTime);
			}
		}
	}
}
void MessageHandler::handleEquipmentStrength()
{
	CSEquipmentStrengthRsp* msg = dynamic_cast<CSEquipmentStrengthRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		ItemManager* itemManager = ItemManager::Get();
		unsigned int coldTime = msg->cold_time();
		unsigned int success = msg->result();
		unsigned int pos = msg->pos();
		if(0 == success)
		{
			if(GetEquipmentUpgradeLayer())
			{
				GetEquipmentUpgradeLayer()->successToStrength(pos,coldTime);
			}
		}
		else
		{
			// 强化失败
			CCLog("EquipmentStrength: result= %d",success);
			const char* errMsg;
			switch(success)
			{
			case 1:
				errMsg = Localizatioin::getLocalization("M_NOT_EQUIP_GRID");
				break;
			case 2:
				errMsg = Localizatioin::getLocalization("M_NOEQUIP");
				break;
			case 3:
				errMsg = Localizatioin::getLocalization("M_NOT_A_EQUIP");
				break;
			case 4:
				errMsg = Localizatioin::getLocalization("M_EQUIPLEVEL_HIGHER");
				break;
			case 5:
				errMsg = Localizatioin::getLocalization("M_NO_MORE_ENHANCETIME");
				break;
			case 6:
				errMsg = Localizatioin::getLocalization("M_ENHANCE_INCD");
				break;
			case 7:
				errMsg = Localizatioin::getLocalization("M_FINDSPIRIT_COINSHORTAGE");
				break;
			default:
				errMsg = Localizatioin::getLocalization("M_UNKNOW_ERROR");
				break;
			}
			ShowMessage(errMsg);
		}
	}
}

void MessageHandler::handleEquipCompose()
{
	CSEquipmentComposeRsp* msg = dynamic_cast<CSEquipmentComposeRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		unsigned int ret = msg->result();
		unsigned int exchangeId = msg->exchange_item_id();
		if(ret != 0)
		{
			switch(ret)
			{
			case 1:
				// 错误的交换信息
				ShowMessage(Localizatioin::getLocalization("M_EQUIPMENT_CHANGEINFORMATIONFALI"));
				break;
			case 2:
				// 交换与物品不符
				ShowMessage(Localizatioin::getLocalization("M_EQUIPMENT_CHANGEGOODSNOTMATCH"));
				break;
			case 3:
				// 物品不足
				ShowMessage(Localizatioin::getLocalization("M_EQUIPMENT_GOODSSHORTAGE"));
				break;
			case 4:
				{
					// 空格不够
					ExchangeItem* item = ItemManager::Get()->getExchageItemById(exchangeId);
					if(item && item->m_exchangeType == 4)
					{
						ShowMessage(Localizatioin::getLocalization("M_FINDSPIRIT_SPIRITWAREHOUSE_FULL"));
					}
					else
					{
						ShowMessage(Localizatioin::getLocalization("M_EQUIPMENT_SPACESHORTAGE"));
					}
					break;
				}
			case 5:
				{
					std::string content = Localizatioin::getLocalization("S_Not_Enough_Level_Content");
					if (content != "")
					{
						ShowMessage(content.c_str());
					}
					break;
				}
			default:
				ShowMessage(Localizatioin::getLocalization("M_UNKNOW_ERROR"));
				break;
			}
			
		}
		else
		{
			ExchangeItem* item = ItemManager::Get()->getExchageItemById(exchangeId);
			if(item && item->m_exchangeType == 4)
			{ // 灵感兑换成功
				ShowMessage(Localizatioin::getLocalization("M_FINDSPIRIT_SPIRITCHANGE_SUCCESS"));
			}
			else if(item && item->m_exchangeType == 5)
			{
				std::list<std::pair<unsigned int ,unsigned int> >::iterator iter = item->m_toItems->begin();
				if (iter != item->m_toItems->end())
				{
					unsigned int key = (*iter).first;
					SpriteElfConfigFromLuaManager::getInstance()->PushExchangeElfRet(key);
				}
			}
			else if(item && item->m_exchangeType == 3)
			{
				// Note: 更改人物的装备
				SpriteSeer* pSeer = GameManager::Get()->getHero();
				if (pSeer)
				{
					unsigned int weaponId = ItemManager::Get()->getHeroWeaponId();
					pSeer->SetEquipItemsData(weaponId);
				}
			}
			else if(item && item->m_exchangeType == 6)
			{
				// Note: 镶嵌宝石兑换碎片
				GemStonesFromLua::getInstance()->GemAnimaExchangeRsp(0);
			}
			else
			{	
				GameAudioManager::sharedManager()->playEffect(350005,false);
				ShowMessage(Localizatioin::getLocalization("M_FINDSPIRIT_SPIRITCHANGE_SUCCESS"));
			}
			
			if(GetCurrentEquipMixLayer())
			{
				GetCurrentEquipMixLayer()->onReceivedComposeSuccess();
			}
		}
	}
}

void MessageHandler::handleSearchSpriteStoneRsp()
{
	CSSearchSpiritStoneRsp* msg = dynamic_cast<CSSearchSpiritStoneRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		AlchemyUILayer* layer = ShowAlchemyUILayer();

		unsigned int ret = msg->ret();
		if(ret == 0)
		{
			unsigned int costCoin = msg->cost_coin();
			unsigned int npcIndex = msg->mon_id();
			unsigned int itemId = 0;
			if(msg->has_item_id())
			{
				itemId = msg->item_id();
			}
			if(layer)
			{
				layer->onReceivedSearchResult(costCoin,npcIndex+1,itemId);
			}
		}
		else
		{
			if(ret == 1)
			{
				ShowMessage(Localizatioin::getLocalization("M_FINDSPIRIT_COINSHORTAGE"));
			}
			else if(ret == 2)
			{
				ShowMessage(Localizatioin::getLocalization("M_FINDSPIRIT_SPIRITSTONEFALL"));
			}
			else
			{
				ShowMessage(Localizatioin::getLocalization("M_UNKNOW_ERROR"));
			}
			CCLog("Search Sprite Error %d",ret);
			
		}
	}
}

void MessageHandler::handleSpriteStoneMoveStorageRsp()
{
	CSSpiritStoneMoveBagRsp* msg = dynamic_cast<CSSpiritStoneMoveBagRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		unsigned int ret = msg->ret();
		if(ret != 0)
		{
			if(ret == 1)
			{
				ShowMessage("error pos");
			}
			else if(ret == 2)
			{
				ShowMessage(Localizatioin::getLocalization("M_FINDSPIRIT_BACKPACKFULL"));
			}
			else
			{
				ShowMessage(Localizatioin::getLocalization("M_UNKNOW_ERROR"));
			}
		}
		//else
		//{
		//	XLogicManager::sharedManager()->reqPlayAttributes();
		//}
	}
}

void MessageHandler::handleSpriteUpgradeRsp()
{
	CSSpiritStoneLevelUpRsp* msg = dynamic_cast<CSSpiritStoneLevelUpRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		unsigned int ret = msg->ret();
		if(ret == 0)
		{
			//unsigned int costEnergy = msg->cost_sp();
			ShowMessage(Localizatioin::getLocalization("M_FINDSPIRIT_SPIRITPROMOTE_SUCCESS"));
			AlchemyUILayer* layer = ShowAlchemyUILayer();
			if(layer)
			{
				layer->onReceivedUpgradeSuccess();
			}
		}
		else
		{
			switch(ret)
			{
			case 1:
				ShowMessage(Localizatioin::getLocalization("M_ALCHEMY_SOULNOTINBAG"));
				break;
			case 2:
				ShowMessage(Localizatioin::getLocalization("M_ALCHEMY_NOSOULHERE"));
				break;
			case 3:
				ShowMessage(Localizatioin::getLocalization("M_ALCHEMY_NOTENOUGH_ENERGY"));
				break;
			case 4:
				ShowMessage(Localizatioin::getLocalization("M_REACH_HIGHESTLEVEL"));
				break;
			default:
				ShowMessage(Localizatioin::getLocalization("M_UNKNOW_ERROR"));
				break;
			}
			
		}
	}
}

void MessageHandler::handleSpriteTransToEnergy()
{
	CSSpiritStoneToSPRsp* msg = dynamic_cast<CSSpiritStoneToSPRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		unsigned int ret = msg->ret();
		if(ret == 0)
		{
			unsigned int key = msg->sp_key();
			unsigned int num = msg->sp_value();
			CCLog("success to trans soul energy: [key: %d ,value: %d]",key,num);
			AlchemyUILayer* layer = GetCurrentAlchemyLayer();
			if(layer)
			{
				layer->onReceiveSpriteTrans();
			}
		}
		else
		{
			switch(ret)
			{
			case 1:
				ShowMessage(Localizatioin::getLocalization("M_ALCHEMY_SOULNOTINBAG"));
				break;
			case 2:
				ShowMessage(Localizatioin::getLocalization("M_ALCHEMY_NOSOULHERE"));
				break;
			default:
				ShowMessage(Localizatioin::getLocalization("M_UNKNOW_ERROR"));
				break;
			}
		}
	}
}

void MessageHandler::handleSpriteExchangeRsp()
{
	CSGetExchangeSSInfoRsp* msg = dynamic_cast<CSGetExchangeSSInfoRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		AlchemyUILayer* layer = GetCurrentAlchemyLayer();
		if(layer)
		{
			layer->onReceivedExchangeInfo(msg);
		}
	}
}

void MessageHandler::handleEquipInlayGemRsp()
{
	CSEquipInlayGemRsp* msg = dynamic_cast<CSEquipInlayGemRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		GemStonesFromLua::getInstance()->EquipInlayGemRsp(msg->ret());
	}
}

void MessageHandler::handleGemRecastRsp()
{
	CSResetGemAttrRsp* msg = dynamic_cast<CSResetGemAttrRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		GemStonesFromLua::getInstance()->GemRecastRsp(msg->ret());
	}
}

void MessageHandler::handleExchangeParameterRsp()
{
	CSExchangeParameterRsp* msg = dynamic_cast<CSExchangeParameterRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		bool success = msg->succ();
		unsigned int exchangeId = msg->id();
		if(exchangeId >= 40090 && exchangeId <= 40120)
		{
			GemStonesFromLua::getInstance()->GemHoleUnlockRsp(success);
		}
	}
}

/// <summary>
//	Task related
/// </summary>
void MessageHandler::handleRsqTaskInfoMessage()
{
    
	CSTaskInfoRsp* msg = dynamic_cast<CSTaskInfoRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		int acceptable_tasks_count = msg->acceptable_tasks_size();
		int accept_tasks = msg->accept_tasks_size();
		// Note: 可接任务部分
		for(int i=0;i<acceptable_tasks_count;i++)
		{
			unsigned int acceptable_task_id = msg->acceptable_tasks(i);
			TaskManager::getInstance()->AddOneAcceptableTask(acceptable_task_id);
		}
		// Note: 进行中任务
		for(int i=0;i<accept_tasks;i++)
		{
			TaskInfo taskInfo = msg->accept_tasks(i);

			unsigned int task_id = taskInfo.task_id();
			unsigned int step_id = taskInfo.step_id();
			unsigned int step_value = taskInfo.step_value();

			tTaskStepData taskData;
			taskData.t_step = step_id;
			taskData.t_step_value = step_value;
			TaskManager::getInstance()->AddOneAcceptedTask(task_id,taskData);
		}
		
		TaskManager::getInstance()->UpdateTaskData();
		TaskManager::getInstance()->UpdateUI();
		
		TaskManager::getInstance()->RqsTaskLogFromServer();

		eTaskGlobleState taskState = TaskManager::getInstance()->getTaskState();
		if (taskState == E_ACCEPT_TASK)
		{
			TaskManager::getInstance()->DisplayOneNpcChatLayer(TaskManager::getInstance()->getDialogNpcId());
			TaskManager::getInstance()->setTaskState(E_TASK_STATE_UNKNOW);
		}
		else if (taskState == E_OVER_TASK)
		{
			TaskManager::getInstance()->DisplayOneNpcChatLayer(TaskManager::getInstance()->getDialogNpcId());
			TaskManager::getInstance()->setTaskState(E_TASK_STATE_UNKNOW);
		}
	}
}

void MessageHandler::handleRsqNetStateMessage()
{
	CSPingRsp* msg = dynamic_cast<CSPingRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		unsigned int serTime = msg->time();
		unsigned int serUTime = msg->utime();
		//CCLOG("==================Server Time: %d.%d=============", serTime, serUTime);
		TimeManager::Get()->syncServerTime(serTime, serUTime);       
		NetStateChecker::getInstance()->RecieveRqsFromServer();
	}
}

void MessageHandler::handleRsqTaskLogMessage()
{
	CSTaskLogRsp* msg = dynamic_cast<CSTaskLogRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		std::vector<unsigned int> vecTaskIds;
		int tasks_count = msg->tasks_size();
		for(int i=0;i<tasks_count;i++)
		{
			TaskInfo task_info = msg->tasks(i);
			unsigned int task_id = task_info.task_id();
			vecTaskIds.push_back(task_id);
		}		
		TaskManager::getInstance()->ShowRewardTaskMessage(vecTaskIds);
	}
}

void MessageHandler::handleRsqTaskStepMessage()
{
	CSTaskDoStepRsp* msg = dynamic_cast<CSTaskDoStepRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		unsigned int task_id = msg->task_id();
		unsigned int step_id = msg->step_id();
		unsigned int step_value = msg->step_value();

		if (step_id == 1)
		{
			//// TODO:显示任务已经领取的特效
			CCLog("One Task Accepted %d ",task_id);
			TaskManager::getInstance()->setTaskState(E_ACCEPT_TASK);
		}
		else
		{
			// Note: 判断任务是否完成
			unsigned int totalStep = TaskConfigFromLuaManager::getInstance()->GetOneTaskStepNums(task_id);
			if (step_id >= totalStep)
			{
				// TODO:播放完成的特效
				CCLog("One Task Compelte %d ",task_id);
				// Note: 分析得到的奖励
				unsigned int elfId = TaskConfigFromLuaManager::getInstance()->GetOneTaskRewardElfID(task_id);
				if (elfId != 0)
				{
					// Note: New State
					SpriteElfDataCenter::Get()->SendSetElfStateMessage(elfId,2);
				}
				TaskManager::getInstance()->setTaskState(E_OVER_TASK);
			}
		}

		// Note: 刷新任务状态
		TaskManager::getInstance()->RqsTaskFromServer();
	}
}

void MessageHandler::handleMsgUserJoin()
{
	CSBattleUserJoinRsp* msg = dynamic_cast<CSBattleUserJoinRsp*>(mCurNormMsgPackage->msg);	

	USERINFO mUserData = UserData::GetUserInfo();

	int userCount = msg->userinfo_size();
	for (int i = 0; i < userCount; i++)
	{
		BasicUserInfo info = msg->userinfo(i);
		if(info.uid() != mUserData.id)
		{
			unsigned int uid = info.uid();
			std::string nick = info.name();
			int xPos = info.xpos();
			int yPos = info.ypos();
			int orient = info.orient();
			int type = info.type();

			unsigned int side = 0;
			if(info.has_battle_side())
				side = info.battle_side();

			USERINFO* pUserInfo = UserData::Get()->GetUserInfo(uid);
			if(pUserInfo)
			{
				SetUserInfo(*pUserInfo, info);
				UserData::Get()->SetUserInfo(pUserInfo->id, *pUserInfo);
			}
			else
			{
				USERINFO otherUserInfo;		
				SetUserInfo(otherUserInfo, info);
				UserData::Get()->SetUserInfo(otherUserInfo.id, otherUserInfo);
			}
			

			CCPoint pixPos = LevelManager::sShareInstance()->pointCellToPixel(ccp(xPos, yPos));

			LevelLayer* layer = LevelManager::sShareInstance()->getCurrentLevelLayer();
			if (layer)
			{
				layer->addOtherPlayer(uid, nick.c_str(), type, pixPos, orient, side);
				if (LevelManager::sShareInstance()->isCurrentPVAILevel())
				{
					PvAIManager::Get()->setAIPlayerId(uid);
				}
			}			
		}

	}
}

void MessageHandler::handleMsgUserLeave()
{
	CSBattleUserLeaveRsp* msg = dynamic_cast<CSBattleUserLeaveRsp*>(mCurNormMsgPackage->msg);	

	USERINFO mUserData = UserData::Get()->GetUserInfo();	

	if(msg->userid() != mUserData.id)
	{
		LevelLayer* layer = LevelManager::sShareInstance()->getCurrentLevelLayer();
		if (layer)
		{
			layer->removeOtherPlayer(msg->userid());
			CCLog("player leave battle: %d ", msg->userid());
		}			
		UserData::Get()->removeOtherUser(msg->userid());
	}	
}

void MessageHandler::handleMsgBattleMove()
{
	CSBattleMoveRsp* msg = dynamic_cast<CSBattleMoveRsp*>(mCurNormMsgPackage->msg);	

	unsigned int uid = msg->id();
	CSPoint directPos = msg->direct();
	CSPoint pos = msg->pos();
	float timeSend = msg->time() / 1000.0f;

	static Machtimer machTimer;

	CCPoint direct = ccp(directPos.xpos(), directPos.ypos());	
	CCPoint position = LevelManager::sShareInstance()->pointCellToPixel(ccp(pos.xpos(), pos.ypos()));
	
	LevelLayer* layer = LevelManager::sShareInstance()->getCurrentLevelLayer();
	if (layer)
	{
		int userId = UserData::Get()->getUserId();
		if (userId != uid)
		{
			SpriteSeer * seer = layer->getPlayer(uid);

			if (seer)
			{
				CCPoint nowPos = seer->getPosition();
				seer->SetMoveType(MOVE_BY_MOUSE);
				seer->setCanMove(true);
				seer->setDirection(direct);

				///calculate the time spent
				float distance = ccpDistance(position, seer->getLastPosition());
				float curDistance = ccpDistance(position, seer->getPosition());
				
				float d = curDistance - distance;
				float rate = 0.0f;


				if(curDistance > 0.2f * seer->GetMoveRate())
				{
					seer->SetAcceleratiion(360.0f);
					
				}
				else
				{
					seer->SetAcceleratiion(0.0f);
					seer->SetAdditionMoveRate(0.0f);
				}
	

				
				seer->setLastPosition(position);


				seer->moveToTarget(position, seer->getPosition(), NULL, NULL, rate);
				

				// CCLog("handleMsgBattleMove additionRate : %f , distance : %f : time : %f", rate, ccpDistance(seer->getPosition(), seer->getLastPosition()), machTimer.elapsedMS() / 1000.0f);
				machTimer.start();

			}
		}

	}
}

void MessageHandler::handlePlayerAttack()
{
	


}

void MessageHandler::handleSkillBegin()
{
	CSSkillBeginRsp* msg = dynamic_cast<CSSkillBeginRsp*>(mCurNormMsgPackage->msg);	

	USERINFO mUserData = UserData::Get()->GetUserInfo();	

	if(msg->userid() != mUserData.id )
	{
		LevelLayer* layer = LevelManager::sShareInstance()->getCurrentLevelLayer();
		if (layer)
		{
			CCPoint rolePos(msg->pos().xpos(), msg->pos().ypos());
			rolePos = LevelManager::sShareInstance()->pointCellToPixel(rolePos);

			CCPoint roleDir(msg->start_dir_x(), msg->start_dir_y());

			CCPoint monsterPos(msg->target_pos().xpos(), msg->target_pos().ypos());
			monsterPos = LevelManager::sShareInstance()->pointCellToPixel(monsterPos);

			CCPoint aimDir(msg->direct_x(), msg->direct_y());
			bool bAimMonster = msg->aim();

			if(SkillDispMgr::Get()->GetSkillInfo(msg->action_id()))
				layer->DoOtherPlayerSkill(msg->userid(), msg->action_id(), rolePos, roleDir, aimDir, monsterPos,  bAimMonster);
			else
				layer->DoElfSkill(msg->userid(), msg->action_id(), rolePos, roleDir, aimDir, monsterPos,  bAimMonster);

			//static Machtimer ttime;
			//CCLog("CSSkillBeginRsp: %d, %ld els : %ld", msg->userid(), msg->action_id(), ttime.elapsedMS());
			//ttime.start();
			
		}			
	}	
}

void MessageHandler::handleRsqElfListMessage()
{
	CSMonListRsp* msg = dynamic_cast<CSMonListRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		unsigned int roleId = msg->uid();
		std::string roleName = msg->name();
		int elf_count = msg->mon_info_size();

		for(int i=0;i<elf_count;i++)
		{
			MonInfo monInfo = msg->mon_info(i);

			unsigned int mon_id = monInfo.mon_id();
			unsigned int mon_state = monInfo.mon_status();

			SpriteElfConfigFromLuaManager::getInstance()->PushElfListMessageToLua(roleId,mon_id,mon_state);
		}
	}
}

void MessageHandler::handleRsqElfStateMessage()
{
	CSSetMonStatusRsp* msg = dynamic_cast<CSSetMonStatusRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		unsigned int result = msg->ret();
		if (result == 0)	//成功
		{
			unsigned int mon_id = msg->mon_id();
			unsigned int mon_state = msg->mon_status();

			SpriteElfConfigFromLuaManager::getInstance()->PushElfStateMessageToLua(mon_id,mon_state);
		}
	}
}

void MessageHandler::handleLevelUpRsp()
{
	CSLevelUpRsp* msg = dynamic_cast<CSLevelUpRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		unsigned int newLevel = msg->level();
		USERINFO info = UserData::GetUserInfo();
		info.level = newLevel;
		UserData::SetUserInfo(info);
		NotificationCenter::defaultCenter()->broadcast(GM_ATTR_HERO_LEVEL_UPDATE,this);

		// Note: 重新拉取任务信息
		TaskManager::getInstance()->RqsTaskFromServer();
	}
}

void MessageHandler::handleUserInfoRsp()
{
	CSGetUserInfoRsp* msg = dynamic_cast<CSGetUserInfoRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		if(msg->userid() == UserData::getUserId())
		{
			BasicUserInfo userInfo = msg->userinfo();
			USERINFO info = UserData::GetUserInfo();
			info.level = userInfo.lv();
			info.nextExp = userInfo.next_lv();
			UserData::SetUserInfo(info);

			if(userInfo.has_battle_info())
			{
				BasicUserBattleInfo battleInfo = userInfo.battle_info();
				if(battleInfo.physical_attack() != info.physical_attack)
				{
					info.physical_attack = battleInfo.physical_attack();
					UserData::SetUserInfo(info);
					NotificationCenter::defaultCenter()->broadcast(GM_ATTR_PHYSICAL_ATTACK_UPDATE,this);
				}
				if(battleInfo.magic_attack() != info.magic_attack)
				{
					info.magic_attack = battleInfo.magic_attack();
					UserData::SetUserInfo(info);
					NotificationCenter::defaultCenter()->broadcast(GM_ATTR_MAGIC_ATTACK_UPDATE,this);
				}
				if(battleInfo.skill_attack() != info.skill_attack)
				{
					info.skill_attack = battleInfo.skill_attack();
					UserData::SetUserInfo(info);
					NotificationCenter::defaultCenter()->broadcast(GM_ATTR_SKILL_ATTACK_UPDATE,this);
				}
				if(battleInfo.physical_defence() != info.physical_defence)
				{
					info.physical_defence = battleInfo.physical_defence();
					UserData::SetUserInfo(info);
					NotificationCenter::defaultCenter()->broadcast(GM_ATTR_PHYSICAL_DEFENCE_UPDATE,this);
				}
				if(battleInfo.magic_defence() != info.magic_defence)
				{
					info.magic_defence = battleInfo.magic_defence();
					UserData::SetUserInfo(info);
					NotificationCenter::defaultCenter()->broadcast(GM_ATTR_MAGIC_DEFENCE_UPDATE,this);
				}
				if(battleInfo.skill_defence() != info.skill_defence)
				{
					info.skill_defence = battleInfo.skill_defence();
					UserData::SetUserInfo(info);
					NotificationCenter::defaultCenter()->broadcast(GM_ATTR_SKILL_DEFENCE_UPDATE,this);
				}
				if(battleInfo.health_point() != info.total_hp)
				{
					info.total_hp = battleInfo.health_point();
					UserData::SetUserInfo(info);
					NotificationCenter::defaultCenter()->broadcast(GM_ATTR_HEALTH_POINT_UPDATE,this);
				}
				if(battleInfo.accurate() != info.accurate)
				{
					info.accurate = battleInfo.accurate();
					UserData::SetUserInfo(info);
					NotificationCenter::defaultCenter()->broadcast(GM_ATTR_ACCURATE_UPDATE,this);
				}
				if(battleInfo.dodge() != info.dodge)
				{
					info.dodge = battleInfo.dodge();
					UserData::SetUserInfo(info);
					NotificationCenter::defaultCenter()->broadcast(GM_ATTR_DODGE_UPDATE,this);
				}
				if(battleInfo.wreck() != info.wreck)
				{
					info.wreck = battleInfo.wreck();
					UserData::SetUserInfo(info);
					NotificationCenter::defaultCenter()->broadcast(GM_ATTR_WRECK_UPDATE,this);
				}
				if(battleInfo.parry() != info.parry)
				{
					info.parry = battleInfo.parry();
					UserData::SetUserInfo(info);
					NotificationCenter::defaultCenter()->broadcast(GM_ATTR_PARRY_UPDATE,this);
				}
				if(battleInfo.critical_strike() != info.critical_strike)
				{
					info.critical_strike = battleInfo.critical_strike();
					UserData::SetUserInfo(info);
					NotificationCenter::defaultCenter()->broadcast(GM_ATTR_CRITICAL_STRIKE_UPDATE,this);
				}
				if(battleInfo.tenacity() != info.tenacity)
				{
					info.tenacity = battleInfo.tenacity();
					UserData::SetUserInfo(info);
					NotificationCenter::defaultCenter()->broadcast(GM_ATTR_TENACITY_UPDATE,this);
				}
				if(battleInfo.slay() != info.slay)
				{
					info.slay = battleInfo.slay();
					UserData::SetUserInfo(info);
					NotificationCenter::defaultCenter()->broadcast(GM_ATTR_SLAY_UPDATE,this);
				}
				if(battleInfo.speed() != info.speed)
				{
					info.speed = battleInfo.speed();
					UserData::SetUserInfo(info);
					NotificationCenter::defaultCenter()->broadcast(GM_ATTR_SPEED_UPDATE,this);
				}
				if(battleInfo.proficiency() != info.proficiency)
				{
					info.proficiency = battleInfo.proficiency();
					UserData::SetUserInfo(info);
					NotificationCenter::defaultCenter()->broadcast(GM_ATTR_PROFICIENCY_UPDATE,this);
				}
				if(battleInfo.courage() != info.courage)
				{
					info.courage = battleInfo.courage();
					UserData::SetUserInfo(info);
					NotificationCenter::defaultCenter()->broadcast(GM_ATTR_COURAGE_UPDATE,this);
				}
				if(battleInfo.charm() != info.charm)
				{
					info.charm = battleInfo.charm();
					UserData::SetUserInfo(info);
					NotificationCenter::defaultCenter()->broadcast(GM_ATTR_CHARM_UPDATE,this);
				}
				if(battleInfo.trick() != info.trick)
				{
					info.trick = battleInfo.trick();
					UserData::SetUserInfo(info);
					NotificationCenter::defaultCenter()->broadcast(GM_ATTR_TRICK_UPDATE,this);
				}
			}
		}
		else
		{
			
			USERINFO otherUserInfo;		
			SetUserInfo(otherUserInfo, msg->userinfo());
		}
	}
}

void MessageHandler::handleAttributesRsp()
{
	CSAttributesRsp* msg = dynamic_cast<CSAttributesRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		unsigned int count = msg->values_size();
		for(unsigned int i=0;i< count; ++i)
		{
			CSAttributesRsp_KeyValue attribute = msg->values(i);
			switch(attribute.key())
			{
                case PB_ATTR_DOWER_LVUP_CD:
                {
                    int value = attribute.value();
                    break;
                }
                    
				case PB_ATTR_PLAYER_COIN:
				{
					USERINFO info = UserData::GetUserInfo();
					if(attribute.value() != info.m_gold)
					{
						info.m_gold = attribute.value();
						UserData::SetUserInfo(info);
						NotificationCenter::defaultCenter()->broadcast(GM_ATTR_COIN_UPDATE,this);
					}
					
					break;
				}
				case PB_ATTR_PLAYER_SP:
				{
					USERINFO info = UserData::GetUserInfo();
					if(attribute.value() != info.m_spriteEnergy)
					{
						info.m_spriteEnergy = attribute.value();
						UserData::SetUserInfo(info);
						NotificationCenter::defaultCenter()->broadcast(GM_ATTR_SP_UPDATE,this);
					}
					break;
				}
				case PB_ATTR_PLAYER_DIAMOND:
				{
					USERINFO info = UserData::GetUserInfo();
					if(attribute.value() != info.m_diamond)
					{
						info.m_diamond = attribute.value();
						UserData::SetUserInfo(info);
						NotificationCenter::defaultCenter()->broadcast(GM_ATTR_SP_DIAMOND_UPDATE,this);
					}
					break;
				}
				case PB_ATTR_BUY_BAG_CAPACITY:
				{
					unsigned int unlockbagCapacity = attribute.value();
					ItemManager::Get()->setBackPackUnlockPos(unlockbagCapacity);
					break;
				}
				case PB_ATTR_BUY_STORE_CAPACITY:
					{
						unsigned int unlockbagCapacity = attribute.value();
						ItemManager::Get()->setStorageUnlockPos(unlockbagCapacity);
						break;
					}
				case PB_ATTR_BUY_SS_BAG_CAPACITY:
				{
					USERINFO info = UserData::GetUserInfo();
					if(attribute.value() != info.m_alchemyStorageUnlockPos)
					{
						if(attribute.value() != 0)
						{
							info.m_alchemyStorageUnlockPos = attribute.value();
							UserData::SetUserInfo(info);
							ItemManager::Get()->setAlchemyStorageUnlockCapacity(info.m_alchemyStorageUnlockPos);
						}
					}
					break;
				}
				case PB_ATTR_EXP:
				{
					USERINFO info = UserData::GetUserInfo();
					if(attribute.value() != info.exp)
					{
						info.exp = attribute.value();
						UserData::SetUserInfo(info);
						NotificationCenter::defaultCenter()->broadcast(GM_ATTR_EXP_UPDATE,this);
					}
					break;
				}
				case PB_ATTR_PLAYER_SS_CHIP:
				{
					USERINFO info = UserData::GetUserInfo();
					if(attribute.value() != info.m_spriteChip || 0 == info.m_spriteChip )
					{
						info.m_spriteChip = attribute.value();
						UserData::SetUserInfo(info);
						NotificationCenter::defaultCenter()->broadcast(GM_ATTR_SP_CHIP_UPDATE,this);
					}
					break;
				}
				case PB_ATTR_PLAYER_SS_MOD_ID:
				{
					USERINFO info = UserData::GetUserInfo();
					if(attribute.value() != info.m_searchSpriteNpc)
					{
						info.m_searchSpriteNpc = attribute.value();
						UserData::SetUserInfo(info);
					}
					break;
				}
				case PB_ATTR_PLAYER_GEM_ANIMA:
				{
					USERINFO info = UserData::GetUserInfo();
					if(attribute.value() != info.m_playerGemAnima)
					{
						info.m_playerGemAnima = attribute.value();
						UserData::SetUserInfo(info);
						NotificationCenter::defaultCenter()->broadcast(GM_ATTR_PLAYER_GEM_ANIMA,this);
					}
					break;
				}
				case PB_ATTR_EQUIP_LVUP_USED_TIMES:
				{
					USERINFO info = UserData::GetUserInfo();
					if(attribute.value() != info.m_equipLvUsedTimes)
					{
						info.m_equipLvUsedTimes = attribute.value();
						UserData::SetUserInfo(info);
						NotificationCenter::defaultCenter()->broadcast(GM_ATTR_EQUIP_LVUP_UESED_TIMES,this);
					}
					break;
				}
				/*case PB_ATTR_EQUIP_LVUP_MAX_TIMES:
				{
					USERINFO info = UserData::GetUserInfo();
					if(attribute.value() != info.m_equipLvUpTotalTimes)
					{
						info.m_equipLvUpTotalTimes = attribute.value();
						UserData::SetUserInfo(info);
						NotificationCenter::defaultCenter()->broadcast(GM_ATTR_EQUIP_LVUP_MAX_TIMES,this);
					}
					break;
				}*/
				case PB_ATTR_PLAYER_PRESTIGE:
					{
						USERINFO info = UserData::GetUserInfo();
						if(attribute.value() != info.m_reputation)
						{
							info.m_reputation = attribute.value();
							UserData::SetUserInfo(info);
							NotificationCenter::defaultCenter()->broadcast(GM_ATTR_STAMINA_UPDATE,this);
						}
						break;
					}
				case PB_ATTR_PLAYER_STAMINA:
					{
						USERINFO info = UserData::GetUserInfo();
						if(attribute.value() != info.m_stamina)
						{
							info.m_stamina = attribute.value();
							UserData::SetUserInfo(info);
							NotificationCenter::defaultCenter()->broadcast(GM_ATTR_REPUTATION_UPDATE,this);
						}
						break;
					}
				case PB_ATTR_PLAYER_RESET_GEM_TIMES:
					{
						USERINFO info = UserData::GetUserInfo();
						if(attribute.value() != info.m_gemRecastTimes)
						{
							info.m_gemRecastTimes = attribute.value();
							UserData::SetUserInfo(info);
							NotificationCenter::defaultCenter()->broadcast(GM_ATTR_GEM_RECAST,this);
						}
						break;
					}
				case PB_ATTR_EFFECTIVENESS:
					{
						USERINFO info = UserData::GetUserInfo();
						if(attribute.value() != info.effectiveness)
						{
							info.effectiveness = attribute.value();
							UserData::SetUserInfo(info);
							NotificationCenter::defaultCenter()->broadcast(GM_ATTR_ABILITY_ALL_UPDATE,this);
						}
						break;
					}
				case PB_ATTR_PLAYER_EXPLOIT:
					{
						USERINFO info = UserData::GetUserInfo();
						if(attribute.value() != info.m_player_exploit)
						{
							info.m_player_exploit = attribute.value();
							UserData::SetUserInfo(info);
							NotificationCenter::defaultCenter()->broadcast(GM_ATTR_PLAYER_EXPOLIT,this);
						}
						break;
					}
				case PB_ATTR_PLAYER_EXPLORE_TIMES:
					{
						unsigned int leftNums = attribute.value();
						SpriteElfConfigFromLuaManager::getInstance()->PushExploreLeftNums(leftNums);
						break;
					}
				case PB_ATTR_PLAYER_EXPLORE_EXP:
					{
						USERINFO info = UserData::GetUserInfo();
						if(attribute.value() != info.m_playerExploerExperience)
						{
							info.m_playerExploerExperience = attribute.value();
							UserData::SetUserInfo(info);
							NotificationCenter::defaultCenter()->broadcast(GM_ATTR_PLAYER_EXPLOER_EXP,this);
						}
						break;
					}
				case SKILL_SLOT_1:
					{
						unsigned int skillId = attribute.value();
						GameConfigFromLuaManager::Get()->PushSkillSlotInfoToLua(attribute.key(),skillId);
						SkillDispMgr::Get()->PushOneSlotInfoToTable(1,skillId);
						break;
					}
				case SKILL_SLOT_2:
					{
						unsigned int skillId = attribute.value();
						GameConfigFromLuaManager::Get()->PushSkillSlotInfoToLua(attribute.key(),skillId);
						SkillDispMgr::Get()->PushOneSlotInfoToTable(2,skillId);
						break;
					}
				case SKILL_SLOT_3:
					{
						unsigned int skillId = attribute.value();
						GameConfigFromLuaManager::Get()->PushSkillSlotInfoToLua(attribute.key(),skillId);
						SkillDispMgr::Get()->PushOneSlotInfoToTable(3,skillId);
						break;
					}
				case SKILL_SLOT_4:
					{
						unsigned int skillId = attribute.value();
						GameConfigFromLuaManager::Get()->PushSkillSlotInfoToLua(attribute.key(),skillId);
						SkillDispMgr::Get()->PushOneSlotInfoToTable(4,skillId);
						break;
					}
				case SKILL_SLOT_5:
					{
						unsigned int skillId = attribute.value();
						GameConfigFromLuaManager::Get()->PushSkillSlotInfoToLua(attribute.key(),skillId);
						SkillDispMgr::Get()->PushOneSlotInfoToTable(5,skillId);
						break;
					}
			}
		}
	}
}

void MessageHandler::handleMsgPlayerHP()
{
	CSPlayerHPRsp* msg = dynamic_cast<CSPlayerHPRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		unsigned int uid = msg->userid();
		unsigned int blood = msg->blood();
		USERINFO* info = UserData::Get()->GetUserInfo(uid);
		if(info)
		{
			info->health_point = blood;
			UserData::Get()->SetUserInfo(uid,*info);

			USERINFO playerInfo = UserData::GetUserInfo();
			if(uid != playerInfo.id)
			{
				if(info->battleSide % 2 !=  playerInfo.battleSide % 2)
				{
					if(info->health_point != info->total_hp)
					{
						ParticleManager::Get()->SetEnemyHpLable(uid,info->health_point,info->total_hp,info->szName,2);
					}
				}
			}
		}
	}
}

void MessageHandler::handlePVPPlayerHitPlayer()
{
	CSPlayerHitPlayerRsp* msg = dynamic_cast<CSPlayerHitPlayerRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		for(int i = 0; i < msg->users_size(); i++)
		{
			const AttackPlayerInfo& info = msg->users(i);
			
			unsigned int uid = info.userid();
			unsigned int blood = info.blood();
			unsigned int type = info.hurt_type();

			SpriteSeer* pHero = GameManager::Get()->getHero();
			if(pHero)
			{
				if(pHero->GetID() == uid)
				{
					switch(type)
					{
					case 1: // 闪避
						GameManager::Get()->GetSceneLayer()->getMainMenuLayer()->HandleAttackMissEffect(pHero->getPosition());
						break;
					case 2: // 格挡
						pHero->ByAttacked(blood);
						GameManager::Get()->GetSceneLayer()->getMainMenuLayer()->HandleAttackBlockEffect(pHero->getPosition());
						break;
					case 3: // 暴击
						pHero->ByAttacked(blood, true);
						break;
					default:
						pHero->ByAttacked(blood);
						break;
					}

					continue;
				}
			}

			LevelLayer* layer = LevelManager::sShareInstance()->getCurrentLevelLayer();
			if (layer)
			{
				std::map<uint32_t, OthersPlayerInfo>::iterator iter = layer->m_othersPlayerInfo.find(uid);
				if(iter != layer->m_othersPlayerInfo.end())
				{
					pHero = iter->second.seer;
					switch(type)
					{
					case 1: // 闪避
						GameManager::Get()->GetSceneLayer()->getMainMenuLayer()->HandleAttackMissEffect(pHero->getPosition());
						break;
					case 2: // 格挡
						pHero->ByAttacked(blood);
						GameManager::Get()->GetSceneLayer()->getMainMenuLayer()->HandleAttackBlockEffect(pHero->getPosition());
						break;
					case 3: // 暴击
						pHero->ByAttacked(blood, true);
						break;
					default:
						pHero->ByAttacked(blood);
						break;
					}
				}
			}
		}
	}
}

void SetUserInfo( USERINFO& userInfo, const BasicUserInfo& info )
{
	userInfo.id = info.uid();

	memcpy(userInfo.szName,  info.name().c_str(), info.name().length());

	
	CCPoint pos =  LevelManager::sShareInstance()->pointCellToPixel(ccp(info.xpos(), info.ypos()));

	userInfo.xPos = pos.x;
	userInfo.yPos = pos.y;


	userInfo.orient = info.orient();
	userInfo.type = info.type();
	
	if(info.has_battle_side())
		userInfo.battleSide = info.battle_side();

	if(info.has_battle_info())
	{
		const BasicUserBattleInfo& bi = info.battle_info();
		userInfo.physical_attack = bi.physical_attack();

		CCLog("id : %u , physical_attack : %u", userInfo.id, userInfo.physical_attack );

		userInfo.magic_attack = bi.magic_attack();
		userInfo.skill_attack = bi.skill_attack();
		userInfo.physical_defence = bi.physical_defence();
		userInfo.magic_defence = bi.magic_defence();
		userInfo.skill_defence = bi.skill_defence();
		userInfo.total_hp = bi.health_point();
		userInfo.accurate = bi.accurate();
		userInfo.dodge = bi.dodge();
		userInfo.wreck = bi.wreck();
		userInfo.parry = bi.parry();
		userInfo.critical_strike = bi.critical_strike();
		userInfo.tenacity = bi.tenacity();
		userInfo.slay = bi.slay();
		userInfo.proficiency = bi.proficiency();
		userInfo.speed = bi.speed();
		userInfo.courage = bi.courage();
		userInfo.trick = bi.trick();
		userInfo.charm = bi.charm();

		if(bi.has_current_hp())
		{
			userInfo.health_point = bi.current_hp();
		}
		else
		{
			userInfo.health_point = bi.health_point();
		}
	}

}

void SetUserInfo( USERINFO& userInfo, const MonsterInfo& info )
{

	userInfo.id = info.id();


	CCPoint pos =  LevelManager::sShareInstance()->pointCellToPixel(ccp(info.point().xpos(), info.point().ypos()));

	userInfo.xPos = pos.x;
	userInfo.yPos = pos.y;


	userInfo.level = info.level();
	userInfo.type = info.type_id();

	if(info.has_battle_info())
	{
		const MonsterBattleInfo& bi = info.battle_info();
		userInfo.physical_attack = bi.physical_attack();
		userInfo.magic_attack = bi.magic_attack();
		userInfo.skill_attack = bi.skill_attack();
		userInfo.physical_defence = bi.physical_defence();
		userInfo.magic_defence = bi.magic_defence();
		userInfo.skill_defence = bi.skill_defence();
		userInfo.health_point = bi.health_point();
		userInfo.total_hp = bi.health_point();
		userInfo.accurate = bi.accurate();
		userInfo.dodge = bi.dodge();
		userInfo.wreck = bi.wreck();
		userInfo.parry = bi.parry();
		userInfo.critical_strike = bi.critical_strike();
		userInfo.tenacity = bi.tenacity();
		userInfo.slay = bi.slay();
		userInfo.proficiency = bi.proficiency();
	}

}

void MessageHandler::handleOnceRspMessage()
{
	CSOnceRsp* msg = dynamic_cast<CSOnceRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		unsigned int count = msg->values_size();
		for(unsigned int i=0;i< count; ++i)
		{
			 CSOnceRsp_Once once = msg->values(i);

			 unsigned int index	= once.index();
			 // Note: 该区间用于记录剧情副本ID
			 if (index < 10000)
			 {
				 bool is_set = once.is_set();
				 if (is_set)
				 {
					 StoryDataCenter::Get()->SetMainLandStoryState(index+INSTANCE_ID_HEADER,is_set);
				 }
			 }
		}
	}
}

void MessageHandler::handleMsgLoadComplete()
{
	CSBattleLoadCompleteRsp* msg = dynamic_cast<CSBattleLoadCompleteRsp*>(mCurNormMsgPackage->msg);
	CCLOG("==========================load complete================");
	int curInstanceTime = InstanceManager::Get()->getInstanceTime();
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{
		if (curInstanceTime > 0)
		{
			BattleUILayer* battleUILayer = mLayer->GetBattleUILayer();
			battleUILayer->initRemainTime(curInstanceTime);
		}

		if (LevelManager::sShareInstance()->isCurrentPPVELevel() || LevelManager::sShareInstance()->isCurrentPVPLevel())
		{					
			BattleCoverLayer* battleCoverLayer = mLayer->GetBattleCoverLayer();
			battleCoverLayer->closeBattleCoverLayer(NULL);
		}
	}

	if (GameDataManager::Get()->getHeroAutoAttack())
	{
		SpriteSeer * hero = GameManager::Get()->getHero();
		if (hero)
		{
			hero->startAutoAttack();
		}	

		if (mLayer)
		{				
			BattleCoverLayer* battleCoverLayer = mLayer->GetBattleCoverLayer();
			battleCoverLayer->openBattleCoverLayer(COVER_AUTOATTACK);
		}
	}

	if (LevelManager::sShareInstance()->isCurrentPVAILevel())
	{
		PvAIManager::Get()->setAIAutoAttack(true);
	}
}

void MessageHandler::handleMsgBattleTimeout()
{
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{		
		BattleUILayer* battleUILayer = mLayer->GetBattleUILayer();
		const char* msg = Localizatioin::getLocalization("M_TIMEUP");
		MessageBox::Show(msg,battleUILayer,menu_selector(BattleUILayer::onPressTimeoutOK),NULL,MB_OK);	
		GameDataManager::Get()->setHeroAutoAttack(false);
	}	
}

void MessageHandler::handleMsgPlayerDie()
{
	TimeManager::Get()->stopTimer(TIMER_INSTANCE_COUNTDOWN);
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{
		BattleUILayer* battleUILayer = mLayer->GetBattleUILayer();
		const char* msg = Localizatioin::getLocalization("M_FAIL_IN_INSTANCE");
		MessageBox::Show(msg,battleUILayer,menu_selector(BattleUILayer::onPressPlayerDieOK),NULL,MB_OK);	
		GameDataManager::Get()->setHeroAutoAttack(false);
	}	

	if (LevelManager::sShareInstance()->isCurrentPVAILevel())
	{
		PvAIManager::Get()->setAIAutoAttack(false);
	}
}

void MessageHandler::handleMsgGetUserSkillRsp()
{
	CSGetUserSkillRsp* msg = dynamic_cast<CSGetUserSkillRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{
		unsigned int user_id = msg->userid();

		int count = msg->userskills_size();

		vector<int> equipSkills;
		for (int index = 0;index<count;index++)
		{
			UserSkillInfo skillInfo = msg->userskills(index);
			if (user_id == UserData::Get()->getUserId())
			{
				if(SkillDispMgr::Get()->GetSkillInfo(skillInfo.skill_id())->type != ToNormalAttack)
					GameConfigFromLuaManager::Get()->PushSkillItemToLua(skillInfo.skill_id(),skillInfo.skill_level(),skillInfo.max_level());				

			}
			else if (user_id == PvAIManager::Get()->getAIPlayerId())
			{
				equipSkills.push_back(skillInfo.skill_id());
			}
				
			SkillDispMgr::Get()->PushOneSKillUserInfoToTable(user_id, skillInfo.skill_id(),skillInfo);
		}

		if (user_id == PvAIManager::Get()->getAIPlayerId())
		{
			PvAIManager::Get()->setAISkillsId(equipSkills);
		}
		GameConfigFromLuaManager::Get()->SkillLevelUpSucMessage();

	}
}

void MessageHandler::handleMsgUserSkillDiffRsp()
{
	CSUserSkillDiffRsp* msg = dynamic_cast<CSUserSkillDiffRsp*>(mCurNormMsgPackage->msg);
	if (msg)
	{
		unsigned int skill_id = msg->skill_id();
		unsigned int skill_level = msg->skill_level();
		
		unsigned int next_money = msg->money();
		unsigned int next_exploit = msg->exploit();
		unsigned int next_lv = msg->lv();
		float diff_own_cd	= msg->own_cd();
		float continue_time_cd = msg->continue_time();
		unsigned int diff_hurt = msg->hurt();

		BasicUserBattleInfo BattleInfo = msg->battle_info();

		// 物理攻击
		unsigned int physical_attack = BattleInfo.physical_attack();
		// 魔法攻击
		unsigned int magic_attack = BattleInfo.magic_attack();
		// 技能攻击
		unsigned int skill_attack = BattleInfo.skill_attack();
		// 物理防御
		unsigned int physical_defence = BattleInfo.physical_defence();
		// 魔法防御
		unsigned int magic_defence = BattleInfo.magic_defence();
		// 技能防御
		unsigned int skill_defence = BattleInfo.skill_defence();
		// 生命值
		unsigned int health_point = BattleInfo.health_point();
		// 精准 
		unsigned int accurate	= BattleInfo.accurate();
		// 闪避 
		unsigned int dodge		= BattleInfo.dodge();
		// 破击
		unsigned int wreck		= BattleInfo.wreck();
		// 格挡
		unsigned int parry		= BattleInfo.parry();
		// 暴击
		unsigned int critical_strike	= BattleInfo.critical_strike();
		// 韧性
		unsigned int tenacity	= BattleInfo.tenacity();
		// 必杀
		unsigned int slay		= BattleInfo.slay();
		// 极速
		unsigned int speed		= BattleInfo.speed();
		// 潜能
		unsigned int proficiency	= BattleInfo.proficiency();

		GameConfigFromLuaManager::Get()->PushDiffInfoToLua(skill_id,skill_level,next_money,next_exploit,next_lv,diff_own_cd,
			continue_time_cd,diff_hurt,physical_attack,magic_attack,skill_attack,physical_defence,magic_defence,skill_defence,health_point,
			accurate,dodge,wreck,parry,critical_strike,tenacity,slay,speed,proficiency);
	}
}

void MessageHandler::handleMsgAddUserSkillRsp()
{
	CSAddUserSkillRsp* msg = dynamic_cast<CSAddUserSkillRsp*>(mCurNormMsgPackage->msg);
	if (msg)
	{
		unsigned int skill_id = msg->skill_id();
		unsigned int skill_level = msg->skill_level();

		GameConfigFromLuaManager::Get()->AddUserSkillRspToLua(skill_id,skill_level);
	}
}

void MessageHandler::handleMsgTrainRsp()
{
	CSTrainRsp * msg = dynamic_cast<CSTrainRsp*>(mCurNormMsgPackage->msg);
	if (msg)
	{
		int deltaCourage = msg->courage();
		int deltaCharm = msg->charm();
		int deltaTrick = msg->trick();
		bool bSuc = msg->succ();

		SpriteElfConfigFromLuaManager::getInstance()->HandleAwakeSuccessMessage(deltaCourage,deltaCharm,deltaTrick,bSuc);
	}
}

void MessageHandler::handleMsgTrainDetermineRsp()
{
	CSTrainDetermineRsp* msg = dynamic_cast<CSTrainDetermineRsp*>(mCurNormMsgPackage->msg);
	if (msg)
	{
		// Note: Save Suc
		SpriteElfConfigFromLuaManager::getInstance()->HandleSaveAwakeResultMessage();
	}
}

void MessageHandler::handleExploreRsp()
{
	CSExploreRsp* msg = dynamic_cast<CSExploreRsp*>(mCurNormMsgPackage->msg);
	if (msg)
	{
		unsigned int type = msg->option();
		unsigned int map_id = msg->map_id();

		SpriteElfConfigFromLuaManager::getInstance()->PushExploreMapIdToData(type,map_id);
	}
}

void MessageHandler::handleExploreDetermineRsp()
{
	CSExploreDetermineRsp* msg = dynamic_cast<CSExploreDetermineRsp*>(mCurNormMsgPackage->msg);
	if (msg)
	{
		CSReward reward = msg->rewards();
		unsigned int	add_coin = reward.add_coin();
		unsigned int	add_exp = reward.add_exp();
		unsigned int	add_exploit = reward.add_exploit();
		unsigned int	map_id = msg->map_id();

		SpriteElfConfigFromLuaManager::getInstance()->PushExploreBasicRewardInfo(map_id,add_coin,add_exp,add_exploit);

		unsigned int count = reward.rewards_size();
		for (unsigned int index = 0;index<count;index++)
		{
			CSReward_RewardInfo rewardInfo = reward.rewards(index);
			unsigned int item_id = rewardInfo.item_id();
			unsigned int item_level = rewardInfo.item_level();
			unsigned int item_num = rewardInfo.item_num();

			SpriteElfConfigFromLuaManager::getInstance()->PushExploreOtherRewardInfo(item_id,item_level,item_num);
		}

		SpriteElfConfigFromLuaManager::getInstance()->ExploreRewardCommit();
	}
}

void MessageHandler::handleNotifyMoneyConfigInfo()
{
	CSNotifyMoneyConfInfoRsp* msg = dynamic_cast<CSNotifyMoneyConfInfoRsp*>(mCurNormMsgPackage->msg);
	if(msg)
	{		
		unsigned int trainMoney = msg->train();
		SpriteElfConfigFromLuaManager::getInstance()->PushElfStrengthData(trainMoney,2,10,50);
	}
}

void MessageHandler::handleMsgPvAIInfoRsq()
{
	CCLOG("handleMsgPvAIInfoRsq----------------------");
	CSPVAIInfoRsq* msg = dynamic_cast<CSPVAIInfoRsq*>(mCurNormMsgPackage->msg); 
	if (msg)
	{		
		int heroRank = msg->rank();
		PvAIManager::Get()->setHeroRank(heroRank);

		//推荐玩家列表
		vector<AIPlayerInfo> aiPlayerInfos;
		int userCount = msg->infos_size();
		for (int i = 0; i < userCount; i++)
		{
			CSPVAIInfoRsq_CSPVAIInfo playerInfo = msg->infos(i);
			AIPlayerInfo aiPlayerInfo;
			aiPlayerInfo.id = playerInfo.userid();
			aiPlayerInfo.rank = playerInfo.rank();
			aiPlayerInfo.name = playerInfo.name();
			aiPlayerInfo.type = playerInfo.type();
			aiPlayerInfo.level = playerInfo.lv();
			aiPlayerInfos.push_back(aiPlayerInfo);
		}
		PvAIManager::Get()->setAIPlayerVec(aiPlayerInfos);

		//最近日志列表
		vector<AILogInfo> aiLogs;
		int logCount = msg->logs_size();
		for (int i = 0; i < logCount; i++)
		{
			CSPVAIInfoRsq_CSPVAILog logInfo = msg->logs(i);
			AILogInfo aiLogInfo;
			aiLogInfo.name = logInfo.name();
			aiLogInfo.direct = logInfo.direct();
			aiLogInfo.win = logInfo.win();
			aiLogs.push_back(aiLogInfo);
		}
		//临时测试数据
		//AILogInfo aiLogInfo;
		//aiLogInfo.name = "testpp";
		//aiLogInfo.direct = true;
		//aiLogInfo.win = false;
		//aiLogs.push_back(aiLogInfo);

		PvAIManager::Get()->setAILogInfoVec(aiLogs);

		PvAIManager::Get()->refreshPvAILayer();
	}

}