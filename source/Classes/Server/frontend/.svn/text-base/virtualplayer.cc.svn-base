#include "virtualplayer.h"
#include "explorer.h"

#define LOCAL_PLAYER_ID   2

Player::Player(BasicUserInfo& info, Explorer* explorer):
Entity(info.uid()),
m_info(info),
m_explorer(explorer)
{

}	

void Player::pack_basic_info(BasicUserInfo* info) const
{
	*info = m_info;
	info->set_xpos(m_pos.x);
	info->set_ypos(m_pos.y);
	return;
}

void Player::finish_instance(uint32_t instance_id, uint32_t star, CSBattleLeaveRsp& leave_rsp)
{

}

int Player::send_msg(const google::protobuf::Message& msg)
{
	const FullPacket* fp = encode(msg);
	if (fp) {
		m_explorer->virtual_hdlr(fp->packet, fp->len);
		return 0;
	}
	return -1;
}

int Player::send_stderr(uint32_t errcode)
{
	return 0;
}