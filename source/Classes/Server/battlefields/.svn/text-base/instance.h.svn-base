#ifndef INSTANCE_HPP_
#define INSTANCE_HPP_

// 3rd-party lib headers go here
#include <google/protobuf/message.h>
// project-specific headers go here
#include "../frontend/virtualplayer.h"

#include "../entities/monster.h"
#include "../common/fwd_decl.h"
#include "../base/Manager.hpp"
#include "../base/EventableObject.hpp"
#include "../base/Singleton.hpp"
#include "../proto/protocodec.h"
#include "battlefield.h"

#define JOINTWAITTIMEOUT (5)

#define LOADWAITTIMEOUT (5)

class Instance: public base::Manager<Player>, public base::EventableObject {
public:
	Instance(uint32_t instance_id, InstanceType type);

	int init();
	
	int join_timeout(uint32_t& map_id);
	
	int start_battle(uint32_t& map_id);
	
	void transfer_next(Player* pPlayer);

	void on_player_leave(base::Manager<Player>*, Player* pPlayer);	

	void on_battle_leave(base::Object<uint32_t>* pbattle);

	void load_complete(Player* pPlayer);

private:
	uint32_t m_instance_id;

	uint32_t m_current_map_id;	

	base::Manager<Battlefield> m_battlefields;

typedef std::map<Player*, bool> CompleteMap;
	CompleteMap m_user_complete;

	InstanceType m_type;
};

class sInstanceManager: public base::GManager<Player>, public Singleton <sInstanceManager> 
{
public:
	int create_instance(Player* pPlayer, uint32_t instance_id);

	int load_complete(Player* pPlayer);
	
	int transfer_next(Player* pPlayer);

	int join_instance(Player* pPlayer, Player* owner);
	
	int init_instance(Player* owner);

	int leave_instance(Player* pPlayer);
};

#define	sInstance sInstanceManager::get_singleton()

#endif
