// TAOMEE GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Taomee Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 2012-2015 Taomee Game Technologies. 
//      All Rights Reserved.
//
// Taomee Game Technologies, Shanghai, China
// http://www.taomee.com
//

#pragma once

#include "SpriteTransPoint.h"
#include "Singleton_t.h"
#include "InstanceListLayer.h"

/*
*   管理所有的副本的信息，存储当前所在的副本的信息，包括多人副本及单人副本
*   
*
*/

/// ppve instance data struct
typedef struct stMapInfo
{
	unsigned int id;
	bool active;
	int  MinLevel;
}InstanceMapInfo;

typedef vector<InstanceMapInfo>MapInfoVector;

class InstanceManager : public TSingleton<InstanceManager>
{
public:
	InstanceManager();
	virtual ~InstanceManager();

	void setMonsterBornPoints(vector<CCPoint> points){this->monsterBornPoints = points;}
	vector<CCPoint> getMonsterBornPoints(){return this->monsterBornPoints;}
	void clearMonsterBornPoints(){this->monsterBornPoints.clear();}

	void setPortalPosition(CCPoint pos){this->portalPosition = pos;}
	CCPoint getPortalPosition(){return this->portalPosition;}

	void setPortalId(unsigned int id){this->portalId = id;}
	unsigned int getPortalId(){return this->portalId;}

	void setCurInstanceId(int id){this->curInstanceId = id;}
	int getCurInstanceId(){return this->curInstanceId;}

	//服务器获得的副本玩家位置
	void setPlayerPosition(CCPoint pos){this->playerPosition = pos;}
	CCPoint getPlayerPosition(){return this->playerPosition;}

	//副本所需通关时间
	void setInstanceTime(int instanceTime){this->instanceTime = instanceTime;}
	int getInstanceTime(){return this->instanceTime;}

	//// ppve instance 
	void  InsertPPVEInstanceId(int id , int reqLevel);

	MapInfoVector& getPPVEInstances();

	void  UpdateData();

	void resetData();

	// Note: 获取某副本的星星数
	int	getOneInstanceStarts(unsigned int instanceId);
	// Note: 设置某副本的星星数
	void setOneInstanceStarts(unsigned int instanceId,unsigned int starts);
public:

	bool isInstanceListChanged(const std::vector<InstanceInfo>& instanceInfos);
	std::vector<InstanceInfo> instanceList;
private:

	CCPoint portalPosition;
	unsigned int portalId;

	int curInstanceId;
	CCPoint playerPosition;

	int instanceTime;

	//// add ppve instance
	MapInfoVector m_vecPPveInstance;	

	vector<CCPoint> monsterBornPoints;
};