#include "InstanceManager.h"
#include "GameConfigFromLuaManager.h"
#include "CCLuaEngine.h"
#include "LuaTinkerManager.h"


#ifndef NULL
#define NULL 0
#endif

#include <algorithm>
using namespace std;

InstanceManager::InstanceManager()
	:portalPosition(ccp(0,0)),
	 portalId(0),
	 curInstanceId(0),
	 instanceTime(0)
{   
	
}

InstanceManager::~InstanceManager()
{
	
}

void InstanceManager::UpdateData()
{
	/// clear data
	m_vecPPveInstance.clear();

	/// load instance script file
	//GameConfigFromLuaManager::Get()->checkConfigLoadFile("InstanceConfigTable");
	LuaTinkerManager::Get()->checkAnyLoadFile("Script/ppveUILayer.lua");

	/// call InitAllInstance in InstanceConfigTable.lua
	CCLuaEngine::defaultEngine()->executeGlobalFunction("InitAllInstance");
}

void  InstanceManager::InsertPPVEInstanceId(int id, int reqLevel)
{
     MapInfoVector::iterator it = m_vecPPveInstance.begin();
	 for(; it != m_vecPPveInstance.end(); it++)
	 {
		 InstanceMapInfo& data = *it;
		 if (data.id == id)
		 {
			 return;
		 }
	 }

	 InstanceMapInfo data;
	 data.active = true;
	 data.id = id;
	 data.MinLevel = reqLevel;

	 m_vecPPveInstance.push_back(data);
}

MapInfoVector& InstanceManager::getPPVEInstances()
{
	return m_vecPPveInstance;
}

void InstanceManager::resetData()
{
	portalPosition = playerPosition = ccp(0, 0);
	portalId = 0;

	curInstanceId = 0;

	instanceTime = 0;

	m_vecPPveInstance.clear();
	instanceList.clear();
}

int	InstanceManager::getOneInstanceStarts(unsigned int instanceId)
{
	size_t count = instanceList.size();
		 
	for (size_t index = 0;index<count;index++)
	{
		if (instanceList[index].id == instanceId)
		{
			return instanceList[index].star;
		}
	}

	return -1;
}

void InstanceManager::setOneInstanceStarts(unsigned int instanceId,unsigned int starts)
{
	std::vector<InstanceInfo>::iterator iter = instanceList.begin();
	for (iter;iter != instanceList.end();iter++)
	{
		if ((*iter).id == instanceId)
		{
			(*iter).star = starts;
			return ;
		}
	}
}

bool InstanceManager::isInstanceListChanged(const std::vector<InstanceInfo>& instanceInfos)
{
	bool ret = false;
	if (instanceList.size() != instanceInfos.size())
	{
		ret = true;
		return ret;
	}

	for (size_t i = 0; i < instanceList.size(); i++)
	{
		if (instanceList[i].id != instanceInfos[i].id
			|| instanceList[i].active != instanceInfos[i].active
			|| instanceList[i].star != instanceInfos[i].star)
		{
			ret = true;
			break;
		}
	}

	return ret;
}