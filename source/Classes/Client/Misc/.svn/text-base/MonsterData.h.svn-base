#pragma once
#include "cs_battle.pb.h"
using namespace std;

class MonsterData
{
public:
	MonsterData();
	virtual ~MonsterData();
	static MonsterData* GetMonsterInfo();
	static void   Destroy();
	void reset();
	void addMonser(MonsterInfo info);
	void setMapId(unsigned int mapid);
	void setfbId(unsigned int fbid);
	std::vector<MonsterInfo>* getMonsterList();
	unsigned int getMapId();
	unsigned int getFbId();
private:
	std::vector< MonsterInfo>* pMonsterList;
	unsigned int m_mapId;
	unsigned int m_fbId;
};