#pragma  once
#include "Singleton_t.h"
#include "AParticleNode.h"
#include "tinystr.h"
#include "tinyxml.h"
#include "HeroEffectDefine.h"
#include "DamageValueEffect.h"
#include "cocos2d.h"
#include "SASpriteDefine.h"
#include "RoleActorBase.h"
#include "EffectSprite.h"
USING_NS_CC;

class ParticleManager : public TSingleton<ParticleManager>
{
public :
	ParticleManager();
	virtual ~ParticleManager();

	AParticleNode* CreateParticleNode(EffectType type);
public:
	void HandleParticleRemoved(unsigned int index);
	void DumpParticlesInfor();	
	EffectSprite* createEffectSprite(int type,const char *name);
	void SetEnemyHpLable(unsigned int targetId,float currentHp,float totalHp,const char* targetName,unsigned int nameType,float dt = 0.2f);

private: 
	void AddParticleNodeToList(unsigned int index,AParticleNode* particle);
	char* GetParticlePlist(EffectType type);
	EffectType getEffectType(const char* actionTypeStr);
private: 
	unsigned int mEffectIndex;
	std::map<unsigned int, AParticleNode*> mParticleList;
	unsigned int m_currentTarget;

	set<int> effectIdSet;
};