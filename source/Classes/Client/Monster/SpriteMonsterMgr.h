#ifndef SPRITE_MONSTER_MGR_H
#define SPRITE_MONSTER_MGR_H

#include "SpriteMonster.h"
#include "SpriteMonsterArcher.h"
#include "MonsterSingleEffect.h"
#include "Singleton_t.h"

#include <map>
using namespace std;

class SpriteMonsterMgr : public TSingleton<SpriteMonsterMgr>
{
	friend class SpriteMonster;
public:    
	SpriteMonsterMgr();
	virtual ~SpriteMonsterMgr(); 

	///  create monster with parameters
    SpriteMonster*	CreateMonster(MonsterInitInfo info);
    
	/// called by LevelLayer
	void Update(float dt);

	/// get a monster from its id
	SpriteMonster* GetMonster(int s_id);

	/// for debug
	void DumpInf();

	const map<int, SpriteMonster*>& GetAllMonster(void) const {return m_tabMonsters;}

	//×Ô¶¯¹¥»÷
	SpriteMonster * getNearestMonster();

	int getAroundMonsterCount(CCPoint pos, float distance);

	CCPoint getSafePoint(CCPoint nowPos, float distance);

	/// remove one monster
	void Remove(SpriteMonster * monster);

	void resetData();

protected:

	/// add monster to the table
	bool Add(SpriteMonster * monster);

protected:
	map<int, SpriteMonster*> m_tabMonsters;
};


#endif
