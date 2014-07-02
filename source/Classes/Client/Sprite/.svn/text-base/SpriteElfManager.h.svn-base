#pragma once

#include "SpriteElf.h"
#include "Singleton_t.h"
#include "SpriteSeer.h"
#include <map>

class SpriteElfManager : public TSingleton<SpriteElfManager>
{
	//friend class SpriteElf;
public:    
	SpriteElfManager();
	virtual ~SpriteElfManager(); 

	/**
	* Instruction : 创建精灵对象
	* @param 
	*/	
	SpriteElf*	CreateInstance(unsigned int s_id,int type);

	/**
	* Instruction : 创建一个精灵对象
	* @param 
	*/
	SpriteElf* CreateInstance(int type);

	/**
	* Instruction : 根据Id获取一个精灵对象
	* @param 
	*/	
	SpriteElf* GetOneInstance(int s_id);

	/**
	* Instruction : 获取所有的精灵实例
	* @param 
	*/	
	const map<int, SpriteElf*>& GetAllInstance(void) const 
	{
		return m_mapElfIdAndInstances;
	}

	/**
	* Instruction : 根据精灵Id删除对象
	* @param 
	*/	
	bool RemoveOneElf(unsigned int s_id,bool bDeleteElf  = true);

	/**
	* Instruction : 绑定精灵岛主角身上
	* @param 
	*/
	void AttachElfToOneHero(unsigned int elfTypeId,unsigned int heroId,SpriteSeer* parent = 0);

	/**
	* Instruction : 清空精灵
	* @param 
	*/
	void ClearAllData();

	/**
	* Instruction : 删除所有的精灵
	* @param 
	*/
	void RemoveAllElfInstance();

	/**
	* Instruction : 插入一个追逐状态
	* @param 
	*/
	void PushOneElfChaseState(SpriteSeer* pHero,int skillId,BaseElfAttachData* pData = 0);

	/**
	* Instruction : 插入一个靠近状态
	* @param 
	*/
	void PushOneElfCloseToState(SpriteSeer* pHero,int skillId,BaseElfAttachData* pData = 0);

	/**
	* Instruction : 插入一个攻击状态
	* @param 
	*/
	void PushOneElfAttackState(SpriteSeer* pHero,int skillId,BaseElfAttachData* pData = 0);

	/**
	* Instruction : called by LevelLayer
	* @param 
	*/	
	void Update(float dt);
protected:
	/**
	* Instruction : 添加一个实例
	* @param 
	*/	
	bool Add(unsigned int id,SpriteElf * instance);
public:
	// Note: 公共数据
	static cocos2d::CCPoint s_fixDistanceToHero;
protected:
	std::map<int, SpriteElf*> m_mapElfIdAndInstances;
};
