#include "MonsterData.h"

static MonsterData* stMonsterData = NULL;

MonsterData::MonsterData()
{
	pMonsterList = new std::vector<MonsterInfo>();
}

MonsterData::~MonsterData()
{
	if(pMonsterList)
	{
		pMonsterList->clear();
		delete pMonsterList;
		pMonsterList = NULL;
	}
}

void MonsterData::Destroy()
{
	if(stMonsterData)
	{
		delete stMonsterData;
		stMonsterData = 0;
	}
}

MonsterData* MonsterData::GetMonsterInfo()
{
	if(!stMonsterData)
	{
		stMonsterData = new MonsterData();
	}
	return stMonsterData;
}

void MonsterData::reset()
{
	if(pMonsterList)
	{
		pMonsterList->clear();
	}

	m_mapId = 0;
	m_fbId = 0;
}

void MonsterData::addMonser(MonsterInfo info)
{
	pMonsterList->push_back(info);
}

void MonsterData::setMapId(unsigned int mapid)
{
	m_mapId = mapid;
}

void MonsterData::setfbId(unsigned int fbid)
{
	m_fbId = fbid;
}

std::vector<MonsterInfo>* MonsterData::getMonsterList()
{
	return pMonsterList;
}