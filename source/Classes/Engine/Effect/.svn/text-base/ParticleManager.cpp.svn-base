#include "ParticleManager.h"
#include "HeroParticleListener.h"
#include "GameResourceManager.h"
#include "UILabelAtlas.h"
#include "UIManager.h"
#include "GameManager.h"
#include "CConnectionData.h"
#include "EnginePlayerManager.h"
#include "MainMenuLayer.h"
#include "BattleUILayer.h"
using namespace TXGUI;

#define EFFECT_DIR "effect/"
static ParticleManager *g_sParticleMgr = NULL;

ParticleManager::ParticleManager()
	:m_currentTarget(0)
{
	mEffectIndex = 0;
	HeroParticleListener::Create();
}

ParticleManager::~ParticleManager()
{
	mParticleList.clear();
	HeroParticleListener::Destroy();
}

AParticleNode* ParticleManager::CreateParticleNode(EffectType type)
{
	AParticleNode* particle = AParticleNode::CreateParticleNode(GetParticlePlist(type),++mEffectIndex);
	AddParticleNodeToList(mEffectIndex,particle);
	return particle; 
}

void ParticleManager::AddParticleNodeToList(unsigned int index,AParticleNode* particle)
{
	std::map<unsigned int, AParticleNode*>::iterator itor = mParticleList.find(index);
	if (itor == mParticleList.end())
	{
		mParticleList.insert(std::pair<unsigned int, AParticleNode*>(index,particle));
	}
}

void ParticleManager::HandleParticleRemoved(unsigned int index)
{
	std::map<unsigned int, AParticleNode*>::iterator itor = mParticleList.find(index);
	if (itor != mParticleList.end())
	{
		mParticleList.erase(itor);
	}
}

char* ParticleManager::GetParticlePlist(EffectType type)
{
	char* plist = NULL;
	switch(type)
	{
		//case kSnowParticle:
		//	plist = "snowTest.plist";
		//	break;
		case NormalAttackEffect:
			break;
		//case kSmokeOne:
		//	plist = "smoke_01.plist";
		//	break;
	}
	return plist;
}

void ParticleManager::DumpParticlesInfor()
{
	std::map<unsigned int, AParticleNode*>::iterator itor = mParticleList.begin();
	if (itor != mParticleList.end())
	{
		CCLog("Particle: totalNum: %ld, texture wide: %ld, high: %d, count: %d",
			itor->second->GetParticle()->getTotalParticles(),
			itor->second->GetParticle()->getTexture()->getPixelsWide(),
			itor->second->GetParticle()->getTexture()->getPixelsHigh());
		itor++;
	}
}

EffectSprite* ParticleManager::createEffectSprite(int type,const char *name)
{
	EffectSprite *pBoneAnimSprite = EffectSprite::effectWithID(type,name);
	EnginePlayerManager::getInstance()->addEffectAsprite(pBoneAnimSprite);
	return pBoneAnimSprite;
}

EffectType ParticleManager::getEffectType(const char* actionTypeStr)
{
	EffectType type = EUnkownEffect;
	if(0 == strcmp(actionTypeStr,"kTypeNormalAttacked"))
	{
		type = NormalAttackEffect;
	}
	else if(0 == strcmp(actionTypeStr,"kTypeMonsterAttacked"))
	{
		type = MonsterAttackEffect;
	}
	else if(0 == strcmp(actionTypeStr,"kTypeCritAttacked"))
	{
		type = CritAttackEffect;
	}
	else if(0 == strcmp(actionTypeStr,"kTypeNormalTranspoint"))
	{
		type = TranspointEffect;
	}
	return type;
}

void ParticleManager::SetEnemyHpLable(unsigned int targetId,float currentHp,float totalHp,const char* targetName,unsigned int nameType,float dt)
{
	bool isPlayAni = true;
	if(targetId != m_currentTarget)
	{
		isPlayAni = false;
		m_currentTarget = targetId;
	}
	SceneLayer* layer = GameManager::Get()->GetSceneLayer();
	if(layer)
	{
		MainMenuLayer* uiLayer = layer->getMainMenuLayer();
		if(uiLayer && uiLayer->GetBattleUILayer())
		{
			uiLayer->GetBattleUILayer()->SetEnemyHpLable(currentHp,totalHp,isPlayAni,m_currentTarget,targetName,dt);
		}
	}
}