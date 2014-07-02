#include "SpriteElfManager.h"
#include "cocos2d.h"
#include "SpriteElf.h"
#include "LevelManager.h"
#include "SkeletonAnimRcsManager.h"
#include "LevelLayer.h"
#include "SpriteElfConfigFromLua.h"
#include "LevelManager.h"

USING_NS_CC;

cocos2d::CCPoint SpriteElfManager::s_fixDistanceToHero = CCPointZero;

SpriteElfManager::SpriteElfManager()
{
	// Note: Get s_fixDistanceToHero
	SpriteElfConfigFromLuaManager::getInstance()->GetElfToHeroFixedDistance(s_fixDistanceToHero.x,s_fixDistanceToHero.y);
}

SpriteElfManager::~SpriteElfManager()
{
	m_mapElfIdAndInstances.clear();
}

void SpriteElfManager::ClearAllData()
{
	m_mapElfIdAndInstances.clear();
}

SpriteElf* SpriteElfManager::CreateInstance(int type)
{
	// Note: 检测动画资源是否已经加载
	SkeletonAnimRcsManager::getInstance()->LoadOneSpriteElfRcs(type,true);

	SpriteElf * instance = NULL;

	instance = new SpriteElf();
	if (instance && instance->initWithId(type))
	{
		instance->autorelease();
		return  instance;
	}
	CC_SAFE_DELETE(instance);
	return NULL;
}

void SpriteElfManager::RemoveAllElfInstance()
{
	std::map<int, SpriteElf*>::iterator iter = m_mapElfIdAndInstances.begin();
	if (iter != m_mapElfIdAndInstances.end())
	{
		SpriteElf* pElf = (*iter).second;
		pElf->removeFromParentAndCleanup(true);

		iter++;
	}
	m_mapElfIdAndInstances.clear();
}

SpriteElf* SpriteElfManager::CreateInstance(unsigned int s_id,int type)
{
	std::map<int, SpriteElf*>::iterator iter = m_mapElfIdAndInstances.find(s_id);
	if (iter != m_mapElfIdAndInstances.end())
	{
		SpriteElf* pElf = (*iter).second;
		pElf->removeFromParentAndCleanup(true);
		m_mapElfIdAndInstances.erase(iter);
	}

	SpriteElf * instance = CreateInstance(type);
	if (Add(s_id,instance) == false)
	{
		CCLOGERROR("create SpriteElf id:%d failed, it's already existed" , s_id);
		CC_SAFE_DELETE(instance);
		instance = NULL;
	}
	return instance;
}

SpriteElf* SpriteElfManager::GetOneInstance(int s_id)
{
	SpriteElf * instance = null;
	std::map<int, SpriteElf*>::iterator it = m_mapElfIdAndInstances.find(s_id) ;
	if (it != m_mapElfIdAndInstances.end())
	{
		instance = it->second;
	}
	return instance;
}


bool SpriteElfManager::Add(unsigned int id,SpriteElf * instance)
{    
	if (instance == 0)
	{
		return false;
	}

	if (m_mapElfIdAndInstances.find(id) != m_mapElfIdAndInstances.end())
	{
		return false;
	}

	m_mapElfIdAndInstances.insert(std::make_pair(id,instance));

	return true;
}

bool SpriteElfManager::RemoveOneElf(unsigned int s_id,bool bDeleteElf /* = true */)
{
	std::map<int, SpriteElf*>::iterator it = m_mapElfIdAndInstances.find(s_id) ;
	if (it != m_mapElfIdAndInstances.end())
	{	
		SpriteElf* instance = (*it).second;
		m_mapElfIdAndInstances.erase(it);
		if (bDeleteElf)
		{
			instance->removeFromParentAndCleanup(true);
		}		
		return true;
	}
	return false;
}

void SpriteElfManager::Update(float dt)
{
	std::map<int, SpriteElf*>::iterator it = m_mapElfIdAndInstances.begin();
	for(; it != m_mapElfIdAndInstances.end(); )
	{
		SpriteElf* instance = it->second;
		if (instance)
		{
			instance->Update(dt);
		}		
		it++;
	}
}

void SpriteElfManager::AttachElfToOneHero(unsigned int elfTypeId,unsigned int heroId,SpriteSeer* parent)
{
	// Note: 找到需要绑定的 spriteseer
	SpriteSeer * seer = parent;
	if (seer == 0)
	{
		LevelLayer* layer = LevelManager::sShareInstance()->getCurrentLevelLayer();
		if (layer)
		{
			seer = layer->getPlayer(heroId);
		}
	}

	if (seer != 0)
	{
		SpriteElf* pElf = CreateInstance(heroId,elfTypeId);
		if (pElf)
		{
			pElf->AttachToOneHero(seer);
		}			
	}
}


void SpriteElfManager::PushOneElfChaseState(SpriteSeer* pHero,int skillId,BaseElfAttachData* pData /* = 0 */)
{
	unsigned int heroId = pHero->GetID();
	
	std::map<int, SpriteElf*>::iterator iter = m_mapElfIdAndInstances.find(heroId);
	if (iter != m_mapElfIdAndInstances.end())
	{
		SpriteElf* pElf = (*iter).second;
		if (pElf)
		{
			pElf->PushOneElfChaseState(pHero,skillId,pData);
		}
	}
}

void SpriteElfManager::PushOneElfCloseToState(SpriteSeer* pHero,int skillId,BaseElfAttachData* pData /* = 0 */)
{
	unsigned int heroId = pHero->GetID();

	std::map<int, SpriteElf*>::iterator iter = m_mapElfIdAndInstances.find(heroId);
	if (iter != m_mapElfIdAndInstances.end())
	{
		SpriteElf* pElf = (*iter).second;
		if (pElf)
		{
			pElf->PushOneElfCloseToState(pHero,skillId,pData);
		}
	}
}

void SpriteElfManager::PushOneElfAttackState(SpriteSeer* pHero,int skillId,BaseElfAttachData* pData /* = 0 */)
{
	unsigned int heroId = pHero->GetID();

	std::map<int, SpriteElf*>::iterator iter = m_mapElfIdAndInstances.find(heroId);
	if (iter != m_mapElfIdAndInstances.end())
	{
		SpriteElf* pElf = (*iter).second;
		if (pElf)
		{
			pElf->PushOneElfAttackState(pHero,skillId,pData);
		}
	}
}