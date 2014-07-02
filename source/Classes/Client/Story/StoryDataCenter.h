#pragma once

/// <summary>
//	剧情系统数据管理模块
/// </summary>

#include "StoryData.h"
#include "tinystr.h"
#include "tinyxml.h"
#include "map"
#include "vector"

#define INSTANCE_ID_HEADER (200000)

class StoryDataCenter
{
public:    	
	StoryDataCenter();
	virtual ~StoryDataCenter(); 

	static StoryDataCenter* Get();
	static void Destroy();

	void LoadOneDataItem(unsigned int id,unsigned int map_id,unsigned int nWhen);

	bool LoadDataFromXML();

	// Note: 依赖于id
	bool IsOneItemHasStory(unsigned int Id,unsigned int map_id,unsigned int when,unsigned int &type);
	bool IsMainLandHasStory(unsigned int mapId,unsigned int when,std::vector<unsigned int> &vecId);
	bool IsOneMainLandStoryPlayed(unsigned int mapId);
	unsigned int GetTotalFrames(unsigned int Id);
	bool IsOneFrameHasDialog(unsigned int taskId,unsigned int frameIndex,StoryDialogData & dialogData);
	bool GetOneItemOwnRoleIds(unsigned int taskId,std::vector<unsigned int> &vecOut);
	bool GetOneItemOneFrameRoleInfo(unsigned int taskId,unsigned int frameIndex,
		std::vector<unsigned int> &vecPlayerId,std::vector<StoryFrameData>& vecStoryData);
	bool IsOneRoleVisible(unsigned int taskId,unsigned int roleId);
	bool SetOneRoleVisibleOrNot(unsigned int taskId,unsigned int roleId,bool bVisible);

	// Note: 依赖iter
	unsigned int GetTotalFrames();
	bool IsOneFrameHasDialog(unsigned int frameIndex,StoryDialogData & dialogData);
	bool GetOneItemOwnRoleIds(std::vector<unsigned int> &vecOut);
	bool GetOneItemAllRoleIds(std::vector<unsigned int> &vecOut);
	bool GetOneItemOneFrameRoleInfo(unsigned int frameIndex,
		std::vector<unsigned int> &vecPlayerId,std::vector<StoryFrameData>& vecStoryData);
	bool IsOneRoleVisible(unsigned int roleId);
	bool SetOneRoleVisibleOrNot(unsigned int roleId,bool bVisible);
	bool GetNextEndPointFrameAndPos(unsigned int roleIndex,unsigned int curFrameIndex,unsigned int& nextFrameIndex,CCPoint &nextPoint);
	bool GetPreAndNextPointFrameData(unsigned int roleIndex,unsigned int curFrameIndex,unsigned int &preFrameIndex,unsigned int &nextFrameIndex,CCPoint &prePoint,CCPoint &nextPoint);
	bool GetOneRoleLeftIcon(unsigned int roleIndex,std::string &iconName);
	CCPoint GetCameraPoint();
	std::map<unsigned int,StoryRoleBasicData>& GetStoryRoleBasicData();

	void SetMainLandStoryState(unsigned int id,bool value);
	void SendMainLandStoryStateRqsMessage();	
	bool IsOneMainLandStoryOver(unsigned int id);
	void SetOneMainLandStoryOver(unsigned int id);
protected:
	TiXmlElement* initXML(const char * filePath);
	bool ReadOneXmlItem(TiXmlElement* pElement);
	bool SplitPosFromContent(std::string content,float &posx,float &posy);
	bool SplitFrameAndPosFromContent(std::string content,unsigned int &frame,float &posx,float &posy);
	bool SplitRoleID(std::string content,unsigned int &roleId);
	bool SplitFrameAndActorIdFromContent(std::string content,unsigned int &frame,int &actorId);
	bool SplitFrameAndTextIdFromContent(std::string content,std::vector<unsigned int> &vecFrameIndex,std::vector<std::string> &vecTextId);
	bool SplitContent(std::string content,std::vector<std::string> &vecOutContent);

	void GetMainLandStoryData();
private:
	bool mIsLoadAllData;
	std::vector<StroyData> mVecTaskIdAndStoryData;
	std::vector<StroyData>::iterator mCurIterator;

	std::map<unsigned int ,bool > mMapMainLandStoryStates;
};