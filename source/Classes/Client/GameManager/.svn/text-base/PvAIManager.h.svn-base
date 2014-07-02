#pragma once

#include "Singleton_t.h"
#include "SpriteSeer.h"
#include "UILayout.h"

typedef struct AIPlayerInfo
{
	string name;
	int level;
	int rank;
	int type;
	int id;
}AIPlayerInfo;

typedef struct AILogInfo
{
	string name;
	bool direct;//true 主动，false被动
	bool win;
}AILogInfo;

typedef struct AILayerBasicInfo
{
	int remainCount;
	long coolDownTime;
	long rewardGetTime;
	int rewardCoin;
	int rewardReputation;
}AILayerBasicInfo;

class PvAIManager : public TSingleton<PvAIManager>
{
public:
	PvAIManager();
	~PvAIManager();

	//网络请求中转
	void sendPvAIReq(int buttonIndex);
	void sendPvAIInfoReq();

	//设置主角信息
	void setHeroRank(int rank){this->heroRank = rank;}

	void setAIPlayerId(int uid){this->aiPlayerId = uid;}
	int getAIPlayerId(){return aiPlayerId;}

	void setAIPlayerVec(vector<AIPlayerInfo> infos){this->aiPlayerVec = infos;}
	void setAILogInfoVec(vector<AILogInfo> logs){this->aiLogInfoVec = logs;}

	void setAISkillsId(vector<int> equipSkills){this->skills = equipSkills;}

	void setAIAutoAttack(bool autoAttack);

	//辅助函数
	void refreshPvAILayer();
	void Update(float dt);
private:
	void moveToHero();

	int getBestSkill();

private:
	//主角相关信息
	int heroRank;

	SpriteSeer * aiPlayer;

	vector<int> skills;

	float aiAutoAttackCDTime;
	bool aiAutoAttack;
	int aiPlayerId;

	vector<AIPlayerInfo> aiPlayerVec;
	vector<AILogInfo> aiLogInfoVec;
	AILayerBasicInfo basicInfo;

	TXGUI::UILayout * pvaiLayout;
};