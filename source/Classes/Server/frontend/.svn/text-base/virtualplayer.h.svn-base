#ifndef VIRTUALPLAYER_H_
#define VIRTUALPLAYER_H_

#include "../entities/object.h"
#include "../proto/protocodec.h"
#include "cs_core.pb.h"

class Explorer;

class Player : public Entity {
public:
	Player(BasicUserInfo& info, Explorer* explorer);

    void pack_basic_info(BasicUserInfo* info) const;

	void finish_instance(uint32_t instance_id, uint32_t star, CSBattleLeaveRsp& leave_rsp);
	
	int send_msg(const google::protobuf::Message& msg);

	int send_stderr(uint32_t errcode);

private:
	BasicUserInfo m_info;
	Explorer* m_explorer;
};

#endif
