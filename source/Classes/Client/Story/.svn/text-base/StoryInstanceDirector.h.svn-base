#pragma once

#include "SpriteSeer.h"
#include "InstanceDialogLayer.h"
#include "cocos2d.h"

class StoryInstanceDirector:public CCNode
{
public:
	StoryInstanceDirector();

	static StoryInstanceDirector* Get();
	static void Destroy();

public:
	void Begin(unsigned int id,unsigned int map_id,int nWhen);
	void Update(float dt);
	void End();
	void Resume();

	void ResetData();
	void CreateMapObjects();

	void DarkEffectOver();

	bool IsStart();

protected:
	void ShowBattleUILayer(bool bShow);
	void ShowMainLandUILayer(bool bShow);
	void ShowOtherPlayers(bool bShow);
	void ShowOtherElf(bool bShow);
	void LoadAllNeedRcs();
	void RemoveAndClearRcs();
	bool TrackDialogAnim();
	bool TrackPlayerAnim();
	SpriteSeer* InsertOneRole(unsigned int indexId,unsigned int roleId,SpriteSeer *pDefaultSeer = 0,CCPoint pt = ccp(-1,-1));
	SpriteSeer* GetOneRole(unsigned int indexId);
	void LoadAllRoles();
	void PlayBecomeDarkEffect();
public:
	CC_SYNTHESIZE(bool, m_IsFirstComeInInstance, IsFirstComeInInstance);
private:
	// Note: m_cutAnimHappendWhen 动画播放时机 0 进入副本 1 打怪完成 2 3 
	int  m_cutAnimHappendWhen;
	unsigned int mID;
	bool m_isHSJoystickEnable;
	bool m_isStart;
	bool m_isPause;
	float m_curFrame;
	float m_preFrame;
	float m_totalFrames;
	unsigned int m_curKeyID;
	int m_heroIndex;
	CCLayerColor* m_pColorLayer;
	InstanceDialogLayer* m_dialogLayer;
	std::map<unsigned int,SpriteSeer*> m_mapRoleIdAndInstance;
};