#ifndef BATTLEHANDLERS_H_
#define BATTLEHANDLERS_H_

#include <google/protobuf/message.h>
#include "battlefield.h"
#include "instance.h"

int battle_create_cmd(Player*, const google::protobuf::Message* msg);

int battle_load_complete_cmd(Player*, const google::protobuf::Message* msg);

int battle_move_cmd(Player*, const google::protobuf::Message* msg);

int player_attack_cmd(Player*, const google::protobuf::Message* msg); 

int skill_begin_cmd(Player*, const google::protobuf::Message* msg); 

int battle_leave_cmd(Player*, const google::protobuf::Message* msg); 

#endif
