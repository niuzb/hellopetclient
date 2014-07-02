#ifndef RU_BATTLEFIELD_H_
#define RU_BATTLEFIELD_H_



// 3rd-party lib headers go here
#include <google/protobuf/message.h>
// project-specific headers go here
#include "../entities/monster.h"
#include "../frontend/virtualplayer.h"

#include "../common/fwd_decl.h"
#include "../base/Manager.hpp"
#include "../base/EventableObject.hpp"
#include "../base/Singleton.hpp"
#include "../proto/protocodec.h"
#include "../battlefields/tileworld.hpp"
#include "../entities/skill.h"

#define WORLDWIDE (0)

#define WAITTIMEOUT (5)

using namespace taomee;

/*
class BattleKey {
public:
typedef uint32_t IdType;
	Player::IdType player_id;
	IdType battle_id;
	bool operator< (const BattleKey& key) const {
		return (player_id < key.player_id || (player_id == key.player_id  && battle_id < key.battle_id ));
	};

	bool operator== (const BattleKey& key) const {
		return (player_id == key.player_id && battle_id == key.battle_id);
	};
};*/

/**
 * @brief 战场
 */
class Battlefield: public base::Object<uint32_t>, public base::Manager<Player>, public base::EventableObject {
public:
	typedef uint32_t Key;

	typedef uint32_t IdType;

	Battlefield(Player* pPlayer, uint32_t battle_id, uint32_t map_id = 0);

	void player_join(Player* pPlayer);

	void attack(Player *pPlayer, const CSPlayerAttackReq * req);
	
	void skill_begin(Player *pPlayer, const CSSkillBeginReq * req);

	void move(Player* pPlayer, TileWorld<>::Point& pos, TileWorld<>::Point& direct);

	int update();

	void on_player_leave(base::Manager<Player>*, Player*);

	void send_to_players(const google::protobuf::Message& msg);
	
	void send_to_players_except(const google::protobuf::Message& msg, Player* pPlayer);

	void init_map(uint32_t map_id = 0 );

	void pack_main_info(CSBattleCreateRsp* rsp);

	bool monster_clear();

public:
	uint32_t get_map_id();
	
	uint32_t get_next_map_id();

	IdType get_battle_id();	

	Player* get_owner();

	bool get_complete();

	void set_complete();

private:
	MonsterManager monsters_;

	IdType  m_battle_id;

	TileWorld<>* m_tile_world;

	Player* owner;
	
	TileWorld<>::Point m_hero_born;

	EffectManager m_effect_manager;
	
/*instance info*/	
	TileWorld<>::Point m_portal;

	uint32_t m_map_id;

	uint32_t m_next_map_id;

	bool m_complete;
};

class BattlefieldManager: public base::GManager<Player>, public Singleton <BattlefieldManager> {
public:
	BattlefieldManager();

	Battlefield* create_battle(Player* pPlayer, uint32_t battle_id, uint32_t map_id = 0);

	Battlefield* get_battle(Player* pPlayer);

	int leave_battle(Player* pPlayer);

	int player_attack(Player* pPlayer, const CSPlayerAttackReq * req);
	
	int skill_begin(Player* pPlayer, const CSSkillBeginReq * req);

	int move(Player* pPlayer, TileWorld<>::Point& pos, TileWorld<>::Point& direct);

	bool exist(const Player* pPlayer);

	uint32_t map_id(Player* pPlayer);

private:
	Battlefield* tmp_battle;
};

#define	sBattlefield BattlefieldManager::get_singleton()

#endif // RU_BATTLEFIELD_H_
