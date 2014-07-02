#ifndef EXPLORER_H_
#define EXPLORER_H_

#include "../config/config.h"
#include "../common/fwd_decl.h"
#include "../msg_dispatcher/msg_handler_mgr.h"

#include "errcode.pb.h"
#include "cs_core.pb.h"


class Player;

typedef int (*VirtualHandlerType)(const void* const data, int len);

/// call back of load monster config from server!
typedef void   (*pfnLoadMonsterConfig)(int nResult);

class Explorer {
public:
	Explorer(BasicUserInfo& info, VirtualHandlerType virtual_handler);

	~Explorer();

	void clock();


	/** load config to memory, this should be called when try to load a map
    
    @warning Calling this method could load local configuration that used for server. only call this in pve battle

    @since v0.9
    */
	void	LoadConfigToMem(int level, int mapID);

    void	FreeConfig();

	int dispatch(const void* data, int datalen);

	void registe_handler();

	void virtual_hdlr(const void* const data, int len);

private:
	MsgHandlerMgr m_hdlr_mgr;   // 所有消息的处理函数保存于此

	Player* m_player;

	VirtualHandlerType m_virtual_hdlr;
};


#endif
