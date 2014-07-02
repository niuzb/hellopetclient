
#include "battlehandlers.h"

#include "../proto/protocodec.h"
#include "cs_battle.pb.h"

int battle_create_cmd(Player* pPlayer, const google::protobuf::Message* msg) {
	const CSBattleCreateReq * req = static_cast<const CSBattleCreateReq*> (msg);
	
	if(req->map_id()) {
		sInstance.transfer_next(pPlayer);
	} else {
		sInstance.create_instance(pPlayer, req->battle_id());
		sInstance.init_instance(pPlayer);
	}
//	sBattlefield.create_battle(pPlayer, req->battle_id());
	return 0;
}

int battle_load_complete_cmd(Player* pPlayer, const google::protobuf::Message* msg) {
	
	sInstance.load_complete(pPlayer);
	return 0;
}

int battle_leave_cmd(Player* pPlayer, const google::protobuf::Message* msg) {
	
	sBattlefield.leave_battle(pPlayer);
	return 0;
}

int battle_move_cmd(Player* pPlayer, const google::protobuf::Message* msg) {
	const CSBattleMoveReq * req = static_cast<const CSBattleMoveReq*> (msg);
	TileWorld<>::Point pos;
	pos.x = req->pos().xpos();
	pos.y = req->pos().ypos();

	TileWorld<>::Point direct;
	direct.x = req->direct().xpos();
	direct.y = req->direct().ypos();
	sBattlefield.move(pPlayer, pos, direct);
	return 0;
}

int player_attack_cmd(Player* pPlayer, const google::protobuf::Message* msg) {
	const CSPlayerAttackReq * req = static_cast<const CSPlayerAttackReq*> (msg);
	sBattlefield.player_attack(pPlayer, req);
	return 0;
}

int skill_begin_cmd(Player* pPlayer, const google::protobuf::Message* msg) {
	const CSSkillBeginReq * req = static_cast<const CSSkillBeginReq*> (msg);
	sBattlefield.skill_begin(pPlayer, req);
	return 0;
}
