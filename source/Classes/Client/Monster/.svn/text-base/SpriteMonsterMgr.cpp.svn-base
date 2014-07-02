#include "SpriteMonsterMgr.h"
#include "cocos2d.h"
#include "GameManager.h"
#include "SpriteSeer.h"
#include "MonsterHaozhu.h"
#include "ItemUpdateManager.h"
#include "LevelManager.h"


using namespace cocos2d;

SpriteMonsterMgr::SpriteMonsterMgr()
{
     
}

SpriteMonsterMgr::~SpriteMonsterMgr()
{
	DumpInf();
}


SpriteMonster* SpriteMonsterMgr::CreateMonster(MonsterInitInfo info)
{
	SpriteMonster * monster = NULL;

	switch (info.typeId)
	{
		case (int)MONSTER_TYPE_QINGWA:
		case (int)MONSTER_TYPE_ZHIZHU:
		case (int)MONSTER_TYPE_DAOLONG:
		case (int)MONSTER_TYPE_RENMA:
		case (int)MONSTER_TYPE_JIQIANGBING:
			monster = new SpriteMonsterArcher(info);
			break;

		case (int)MONSTER_TYPE_XIAOHUAYAO:
		case (int)MONSTER_TYPE_HUAYAO:
		case (int)MONSTER_TYPE_FENGYUANSU:
			monster = new MonsterSingleEffect(info);
			break;

		case (int)MONSTER_TYPE_HAOZHU:
		case (int)MONSTER_TYPE_TIEQIU:
			monster = new MonsterHaozhu(info);
			break;

		default:
			monster = new SpriteMonster(info);
			break;
	}

	if (monster && monster->initWithId(info.uid, info.monsterName, info.typeId))
	{
		monster->autorelease();
		if (Add(monster) == false)
		{
			CCLog("create monster id:%d failed, it's already existed" , info.uid);
			CC_SAFE_DELETE(monster);
			monster = NULL;
		}
		else
		{
			//ItemUpdateManager::Get()->addToUpdateManager(monster);
		}
		
		return  monster;
	}
	CC_SAFE_DELETE(monster);
	return NULL;
}

SpriteMonster* SpriteMonsterMgr::GetMonster(int s_id)
{
	SpriteMonster * monster = null;
	map<int, SpriteMonster*>::iterator it = m_tabMonsters.find(s_id) ;
	if (it != m_tabMonsters.end())
	{
		monster = m_tabMonsters[it->first];
	}
	return monster;
}


bool SpriteMonsterMgr::Add(SpriteMonster * monster)
{    
	if (m_tabMonsters.find(monster->GetID()) != m_tabMonsters.end())
	{
		return false;
	}

	m_tabMonsters[monster->GetID()] = monster;

	return true;
}

void SpriteMonsterMgr::Remove(SpriteMonster * monster)
{
	map<int, SpriteMonster*>::iterator it = m_tabMonsters.find(monster->GetID()) ;
	if (it != m_tabMonsters.end())
	{	
		m_tabMonsters.erase(it);				
	}
}


void SpriteMonsterMgr::DumpInf()
{
	map<int, SpriteMonster*>::iterator it = m_tabMonsters.begin();
	for(; it != m_tabMonsters.end(); it++)
	{
		SpriteMonster* monster = it->second;
		CCLog("Monster:%d", monster->GetID());
	}
}


void SpriteMonsterMgr::Update(float dt)
{
	map<int, SpriteMonster*>::iterator it = m_tabMonsters.begin();
	for(; it != m_tabMonsters.end(); )
	{
		SpriteMonster* monster = it->second;
		bool bDeleteSelf = false;
		monster->Update(dt,bDeleteSelf);
		if (bDeleteSelf)
		{
			//ItemUpdateManager::Get()->removeFromUpdateManager(monster);
			m_tabMonsters.erase(it++);
			monster->removeFromParentAndCleanup(true);			
		}
		else
		{
			it++;
		}
	}
}

SpriteMonster * SpriteMonsterMgr::getNearestMonster()
{
	SpriteMonster * nearestMonster = NULL;
	SpriteSeer * hero = GameManager::Get()->getHero();
	if (!hero || m_tabMonsters.size() == 0)
	{
		return NULL;
	}

	map<int, SpriteMonster*>::iterator it = m_tabMonsters.begin();

	SpriteMonster * firstMonster = it->second;
	float distance = ccpDistance(firstMonster->getPosition(), hero->getPosition());
	nearestMonster = firstMonster;

	for(; it != m_tabMonsters.end(); )
	{
		SpriteMonster* monster = it->second;
		float dis = ccpDistance(monster->getPosition(), hero->getPosition());
		if (dis < distance && monster->fsm_rule.GetState() != MONSTER_STATE_DEAD)
		{
			distance = dis;
			nearestMonster = monster;
		}
		it++;		
	}


	return nearestMonster;
}

int SpriteMonsterMgr::getAroundMonsterCount(CCPoint pos, float distance)
{
	int ret = 0;

	map<int, SpriteMonster*>::iterator it = m_tabMonsters.begin();	

	for(; it != m_tabMonsters.end(); it++)
	{
		SpriteMonster* monster = it->second;
		if (ccpDistance(monster->getPosition(), pos) < distance)
		{
			ret++;
		}
	}

	return ret;

}

CCPoint SpriteMonsterMgr::getSafePoint(CCPoint nowPos, float distance)
{
	CCPoint ret = nowPos;

	float moveDis = 500;
	CCPoint upPos = ccp(nowPos.x, nowPos.y + moveDis);
	CCPoint downPos = ccp(nowPos.x, nowPos.y - moveDis);
	CCPoint leftPos = ccp(nowPos.x - moveDis, nowPos.y);
	CCPoint rightPos = ccp(nowPos.x + moveDis, nowPos.y);

	int minCount = getAroundMonsterCount(nowPos, distance);

	if (LevelManager::sShareInstance()->isPointReachable(upPos) && getAroundMonsterCount(upPos, distance) < minCount)
	{
		minCount = getAroundMonsterCount(upPos, distance);
		ret = upPos;
	}

	if (LevelManager::sShareInstance()->isPointReachable(downPos) && getAroundMonsterCount(downPos, distance) < minCount)
	{
		minCount = getAroundMonsterCount(downPos, distance);
		ret = downPos;
	}

	if (LevelManager::sShareInstance()->isPointReachable(leftPos) && getAroundMonsterCount(leftPos, distance) < minCount)
	{
		minCount = getAroundMonsterCount(leftPos, distance);
		ret = leftPos;
	}

	if (LevelManager::sShareInstance()->isPointReachable(rightPos) && getAroundMonsterCount(rightPos, distance) < minCount)
	{
		minCount = getAroundMonsterCount(rightPos, distance);
		ret = rightPos;
	}

	return ret;
}


void SpriteMonsterMgr::resetData()
{
	map<int, SpriteMonster*>::iterator it = m_tabMonsters.begin();
	for(; it != m_tabMonsters.end(); it++)
	{
		SpriteMonster* monster = it->second;
		//ItemUpdateManager::Get()->removeFromUpdateManager(monster);
	}
	m_tabMonsters.clear();
}


