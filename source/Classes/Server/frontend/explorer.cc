#include "explorer.h"
#include "../battlefields/battlehandlers.h"
#include "./virtualplayer.h"
#include "../battlefields/battlefield.h"
	
Explorer::Explorer(BasicUserInfo& info, VirtualHandlerType virtual_handler) :
	m_virtual_hdlr(virtual_handler)
{
	m_player = new Player(info, this);
	registe_handler();
	g_mapcontent_config = new MapContentConfig;
	g_range_config = new RangeConfig;
	g_skill_config = new SkillConfig;
	g_monster_config = new MonsterConfig;
}
	


Explorer::~Explorer() {
	g_monster_config->clear();
	g_skill_config->clear();
	g_mapcontent_config->clear();
	g_range_config->clear();

	delete g_monster_config;
	delete g_skill_config;
	delete g_mapcontent_config;
	delete g_range_config;
	
	if(m_player) {
		delete m_player;
	}
}

/// load config to memory, this should be called when try to load a map
void  Explorer::LoadConfigToMem(int level, int mapID)
{
	static bool bLoad = false;
	if (!bLoad)
	{		
		g_range_config->load();
		g_skill_config->load();
		g_monster_config->load();

		bLoad = true;
	}

	g_mapcontent_config->clear();  
	g_mapcontent_config->load(mapID, level);
}

void Explorer::FreeConfig()
{
	/// only free map config
	g_mapcontent_config->clear(); 

	/// release monster 
	Battlefield* battle = sBattlefield.get_battle(m_player);
	if (battle)
	{
		delete battle;
	}
}

	
void Explorer::clock() {
	sGloble.Timer.process_events();	
}
	
int Explorer::dispatch(const void* data, int datalen) {
	// 分解出包头和包体
	CSMessageHeader msghdr;
	Message* msgpayload;
	if (decode(data, &msghdr, &msgpayload) == false) {
        ERROR_LOG("invalid package len=%d",
					 datalen);
		return -1;
	}
	// 通过scoped_ptr自动释放msgpayload的内存，避免到处delete。
	scoped_ptr<Message> auto_del_msg(msgpayload);
	
	DEBUG_LOG("DISPATCH :%s", msghdr.msg_name().c_str());

	// 查找对应的处理函数对消息进行处理
	MsgHandlerMgr::HandlerType hdlr = m_hdlr_mgr.find_handler(msghdr.msg_name());
	if (hdlr) {
		return hdlr(m_player, msgpayload);
	}
	m_player->send_stderr(olerr_invalid_req);
        ERROR_LOG("invalid req=%s len=%d",
                  msghdr.msg_name().c_str(), datalen);
	return -1;
}

void Explorer::registe_handler() {
	m_hdlr_mgr.register_handler(CSBattleCreateReq::descriptor()->name(), battle_create_cmd );
	m_hdlr_mgr.register_handler(CSBattleLoadCompleteReq::descriptor()->name(), battle_load_complete_cmd );
	m_hdlr_mgr.register_handler(CSBattleLeaveReq::descriptor()->name(), battle_leave_cmd );
	m_hdlr_mgr.register_handler(CSPlayerAttackReq::descriptor()->name(), player_attack_cmd );
	m_hdlr_mgr.register_handler(CSBattleMoveReq::descriptor()->name(), battle_move_cmd );
}
void Explorer::virtual_hdlr(const void* const data, int len) {
	m_virtual_hdlr(data, len);
}
