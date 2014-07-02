#include "OnlineNetworkManager.h"
#include "StoryInstanceDirector.h"
#include "HSJoystick.h"
#include "GameManager.h"
#include "MainMenuLayer.h"
#include "BattleUILayer.h"
#include "StoryDataCenter.h"
#include "LevelManager.h"
#include "InstanceDialogLayer.h"
#include "UserData.h"
#include "LevelLayer.h"
#include "SkeletonAnimRcsManager.h"
#include "CameraController.h"
#include "InstanceManager.h"
#include "XLogicManager.h"
#include "SpriteElfConfigFromLua.h"
#include "GameUILayer.h"
#include "BoneNPCManager.h"
#include "SpriteElfManager.h"

#define AnimationInternal  (1.0f / FRAME_RATES)

static StoryInstanceDirector* _storyInstanceDirector = 0;

StoryInstanceDirector::StoryInstanceDirector()
{	
	ResetData();
}

void StoryInstanceDirector::ResetData()
{
	m_isStart = false;
	m_isPause = false;
	m_isHSJoystickEnable = false;
	m_totalFrames = 0;
	m_curFrame = -1;
	m_preFrame = -1;
	m_curKeyID = 0;
	m_heroIndex = -1;
	m_dialogLayer = 0;
	m_pColorLayer = 0;
	m_cutAnimHappendWhen = 0;
	m_mapRoleIdAndInstance.clear();
	m_pColorLayer = 0;
	m_dialogLayer = 0;
	mID = 0;
	m_IsFirstComeInInstance = false;
}

StoryInstanceDirector* StoryInstanceDirector::Get()
{
	if (_storyInstanceDirector == 0)
	{
		_storyInstanceDirector = new StoryInstanceDirector();
	}
	return _storyInstanceDirector;
}

void StoryInstanceDirector::Destroy()
{
	if (_storyInstanceDirector)
	{
		delete _storyInstanceDirector;
		_storyInstanceDirector = 0;
	}
}

void StoryInstanceDirector::Resume()
{
	if (m_isStart)
	{
		m_isPause = false;
	}
}

void StoryInstanceDirector::Begin(unsigned int id,unsigned int map_id,int nWhen)
{	
	//if (IsOneInstanceExist(id))
	//{
	//	// Note: 已经播放过 无需重复播放
	//	return ;
	//}
	mID = id;
	m_cutAnimHappendWhen = nWhen;
	m_mapRoleIdAndInstance.clear();

	// Note: 初始化数据中心
	StoryDataCenter::Get()->LoadOneDataItem(id,map_id,nWhen);	

	// Note: 设置摄像机对准点模式
	CCPoint cameraPoint = StoryDataCenter::Get()->GetCameraPoint();
	CameraController::sharedCameraController()->SetFollowType(CameraController::E_FixPoint);
	CameraController::sharedCameraController()->SetFollowPoint(cameraPoint);

	// Note: 获取总帧数
	m_totalFrames = StoryDataCenter::Get()->GetTotalFrames();
	m_curFrame = -1;
	m_preFrame = -1;
	m_curKeyID = id;

	//// Note: 战斗UI面板隐藏
	m_isHSJoystickEnable = HSJoystick::sharedJoystick()->getIsEnable();
	if (m_isHSJoystickEnable)
	{
		HSJoystick::sharedJoystick()->setVisible(false);
		HSJoystick::sharedJoystick()->setIsEnable(false);
	}

	// Note: 隐藏战斗中ＵＩ
	if (nWhen == 0 || nWhen == 1)
	{
		ShowBattleUILayer(false);
	}	
	else if (nWhen == 2)
	{
		ShowMainLandUILayer(false);
		BoneNPCManager::getInstance()->ShowAllNpc(false);
	}

	// Note: 加载所有需要资源
	LoadAllNeedRcs();
	LoadAllRoles();

	// Note: 显示对话界面
	m_dialogLayer = InstanceDialogLayer::create();
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{
		mLayer->addChild(m_dialogLayer);
		mLayer->setVisible(true);
	}

	// Note: 黑屏Layer
	if (mLayer != 0)
	{
		m_pColorLayer = CCLayerColor::create(ccc4(0,0,0,255));
		m_pColorLayer->setVisible(false);
		mLayer->addChild(m_pColorLayer,0,1000);
	}

	// Note: 禁用主角的状态机
	SpriteSeer* pHero = GameManager::Get()->getHero();
	if (pHero)
	{
		pHero->PauseStateMachine();
	}

	if (m_cutAnimHappendWhen == 1)
	{
		PlayBecomeDarkEffect();
	}

	m_isStart = true;
}

void StoryInstanceDirector::ShowOtherPlayers(bool bShow)
{
	std::map<unsigned int, OthersPlayerInfo>& otherPlayer = LevelManager::sShareInstance()->getCurrentLevelLayer()->m_othersPlayerInfo;
	for(std::map<unsigned int, OthersPlayerInfo>::const_iterator iter = otherPlayer.begin(); iter != otherPlayer.end(); iter++)
	{
		BoneSpriteBase* pOtherHero = dynamic_cast<BoneSpriteBase*>(iter->second.seer); 
		pOtherHero->setVisible(bShow);
	}
}

void StoryInstanceDirector::ShowOtherElf(bool bShow)
{
	const map<int, SpriteElf*>& elfMap = SpriteElfManager::Get()->GetAllInstance();
	for(map<int, SpriteElf*>::const_iterator iter = elfMap.begin(); iter != elfMap.end(); iter++)
	{
		unsigned int id = (*iter).first;
		if (id != UserData::Get()->getUserId())
		{
			(*iter).second->setVisible(bShow);
		}
	}
}

void StoryInstanceDirector::Update(float dt)
{
	if (m_isStart)
	{
		if (m_cutAnimHappendWhen == 2)
		{
			ShowOtherPlayers(false);
			ShowOtherElf(false);
		}
	}

	if (false == m_isStart || true == m_isPause)
	{
		return ;
	}

	float deltaFrames = (dt/AnimationInternal);
	m_curFrame += deltaFrames;
	// Note: 处理跳帧现象
	if (fabs(m_curFrame - m_preFrame) > 1)
	{
		m_curFrame = m_preFrame + 1;
	}
	else
	{
		return ;
	}
	m_preFrame = m_curFrame;

	if (m_curFrame >= m_totalFrames)
	{
		End();
		return ;
	}

	if (TrackDialogAnim())
	{
		//return ;
	}
	if (TrackPlayerAnim())
	{
		//return;
	}
}

void StoryInstanceDirector::End()
{
	if (m_cutAnimHappendWhen == 0)
	{
		PlayBecomeDarkEffect();
	}	

	// Note: 清空资源
	RemoveAndClearRcs();

	if (m_isHSJoystickEnable)
	{
		HSJoystick::sharedJoystick()->setVisible(true);
		HSJoystick::sharedJoystick()->setIsEnable(true);
	}
	
	if (m_cutAnimHappendWhen == 0 || m_cutAnimHappendWhen == 1)
	{
		ShowBattleUILayer(true);
	}	
	else if (m_cutAnimHappendWhen == 2)
	{
		ShowMainLandUILayer(true);
		BoneNPCManager::getInstance()->ShowAllNpc(true);
		ShowOtherPlayers(true);
		ShowOtherElf(true);
		StoryDataCenter::Get()->SetOneMainLandStoryOver(mID);
	}

	if (m_dialogLayer != 0)
	{
		m_dialogLayer->removeFromParent();
	}	

	CameraController::sharedCameraController()->SetFollowType(CameraController::E_FollowHero);

	if (m_cutAnimHappendWhen == 0)
	{
		// Note: 重置主角的位置
		CCPoint playerPos = InstanceManager::Get()->getPlayerPosition();
		SpriteSeer* pHero = GameManager::Get()->getHero();
		if (pHero)
		{
			pHero->setPosition(playerPos);
		}

		LevelManager::sShareInstance()->ShowMonsterOrNot(true);
		OnlineNetworkManager::sShareInstance()->sendLoadCompleteMessage();
	}
	else if (m_cutAnimHappendWhen == 1)
	{
		XLogicManager::sharedManager()->FinishBattle();
		//OnlineNetworkManager::sShareInstance()->sendOnceSetReqMessage(InstanceManager::Get()->getCurInstanceId());
	}

	SpriteSeer* pHero = GameManager::Get()->getHero();
	if (pHero)
	{
		pHero->ResumeStateMachine();
	}

	ResetData();
}

void StoryInstanceDirector::CreateMapObjects()
{
	if (m_pColorLayer)
	{
		m_pColorLayer->removeFromParentAndCleanup(true);
		m_pColorLayer = 0;
	}
	m_isPause = false;
}

void StoryInstanceDirector::PlayBecomeDarkEffect()
{
	// Note: 播放黑屏特效
	if (m_pColorLayer != 0)
	{
		m_pColorLayer->setVisible(true);

		float duration = 1.1f;
		CCFadeOut *fadeout = CCFadeOut::create(duration);
		m_pColorLayer->runAction(fadeout);

		MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
		CCCallFunc *rc = CCCallFunc::create(mLayer,callfunc_selector(MainMenuLayer::DarkEffectOver));
		CCSequence *seq = (CCSequence*)CCSequence::create(CCDelayTime::create(duration),rc,NULL);		
		if (mLayer)
		{
			mLayer->runAction(seq);
		}

		m_isPause = true;
	}
}

void StoryInstanceDirector::DarkEffectOver()
{
	m_isPause = false;
	CreateMapObjects();	
}

void StoryInstanceDirector::ShowBattleUILayer(bool bShow)
{
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer != 0)
	{
		mLayer->GetBattleUILayer()->setVisible(bShow);
	}	
}

void StoryInstanceDirector::ShowMainLandUILayer(bool bShow)
{
	MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer != 0)
	{
		mLayer->GetGameUILayer()->setVisible(bShow);
	}	
}

void StoryInstanceDirector::LoadAllNeedRcs()
{
	std::vector<unsigned int> vecOut;
	if (StoryDataCenter::Get()->GetOneItemOwnRoleIds(vecOut))
	{
		size_t count = vecOut.size();
		for (size_t index = 0;index<count;index++)
		{
			unsigned int roleId = vecOut[index];
			if (roleId != 0)
			{
				// Note: 加载相应的资源文件
				SkeletonAnimRcsManager::getInstance()->LoadOneHeroRcs(roleId,true);
			}
		}
	}
}

void StoryInstanceDirector::LoadAllRoles()
{
	std::vector<unsigned int> vecOut;
	if (StoryDataCenter::Get()->GetOneItemAllRoleIds(vecOut))
	{
		size_t count = vecOut.size();
		for (size_t index = 0;index<count;index++)
		{
			unsigned int roleId = vecOut[index];
			SpriteSeer* pSeer = 0;
			if (roleId != 0)
			{
				pSeer = InsertOneRole(index+1,roleId);

				unsigned int seerTypeId = pSeer->GetTypeId();
				if (false == SpriteElfConfigFromLuaManager::getInstance()->TellIsElfId(seerTypeId))
				{
					ASprite* pAsprite = AspriteManager::getInstance()->getAsprite("spriteBin/shadow.bin");
					if(pAsprite != NULL)
					{
						CCPoint cp;
						CCSpriteBatchNode* pBatchNode = pAsprite->getSpriteBatchNodeFromFrame_Middle(0, 0, cp);
						if(pBatchNode != NULL)
						{
							pSeer->addChildToRoot(pBatchNode);
						}
					}
				}
			}
			else
			{
				pSeer = GameManager::Get()->getHero();
				pSeer = InsertOneRole(index+1,roleId,pSeer);
				if (pSeer)
				{
					m_heroIndex = index+1;
				}
			}
			if (pSeer)
			{
				pSeer->getRoot()->setVisible(false);
			}
		}
	}	
}

void StoryInstanceDirector::RemoveAndClearRcs()
{
	std::map<unsigned int,SpriteSeer*>::iterator iter = m_mapRoleIdAndInstance.begin();
	while(iter != m_mapRoleIdAndInstance.end())
	{
		SpriteSeer* pSeer = (*iter).second;
		if (m_heroIndex == (*iter).first)
		{
			pSeer->getRoot()->setVisible(true);
		}
		else
		{
			//pSeer->getParent()->removeChild(pSeer,true);
			pSeer->getRoot()->setVisible(false);
		}		

		iter ++;
	}

	m_mapRoleIdAndInstance.clear();
}

bool StoryInstanceDirector::TrackDialogAnim()
{
	// Note: 判断当前帧是否有对话动画
	StoryDialogData dialogData;
	if (StoryDataCenter::Get()->IsOneFrameHasDialog((int)m_curFrame,dialogData))
	{
		if (m_dialogLayer)
		{
			m_dialogLayer->setStoryDialogData(dialogData);
			m_dialogLayer->ShowPanel();
		}

		m_isPause = true;

		return true;
	}
	else
	{
		if (m_dialogLayer)
		{
			m_dialogLayer->ClearPanel();
		}
	}
	return false;
}

SpriteSeer* StoryInstanceDirector::InsertOneRole(unsigned int indexId,unsigned int roleId,SpriteSeer *pDefaultSeer /* = 0 */,CCPoint pt /* = ccp */)
{
	std::map<unsigned int,SpriteSeer*>::iterator iter = m_mapRoleIdAndInstance.find(indexId);
	if (iter != m_mapRoleIdAndInstance.end())
	{
		return (*iter).second;
	}
	
	SpriteSeer* pSeer = 0;
	if (pDefaultSeer == 0)
	{
		pSeer = SpriteSeer::seerWithID(0,"",roleId,false,false);
		if (pSeer)
		{
			// Note: Add To Obj Layer
			LevelLayer* pLayer = LevelManager::sShareInstance()->getCurrentLevelLayer();
			if (pLayer)
			{
				CCNode* pObjLayer = pLayer->getObjectLayer();
				if (pObjLayer)
				{
					if (pt.x != -1 && pt.y != -1)
					{
						pObjLayer->addChild(pSeer,LevelLayer::sCalcZorder(pt));
					}
					else
					{
						pObjLayer->addChild(pSeer);
					}
					
					m_mapRoleIdAndInstance.insert(std::make_pair(indexId,pSeer));
				}
			}
		}
	}
	else
	{
		pSeer = pDefaultSeer;
		m_mapRoleIdAndInstance.insert(std::make_pair(indexId,pSeer));
	}

	return pSeer;
}

SpriteSeer* StoryInstanceDirector::GetOneRole(unsigned int indexId)
{
	std::map<unsigned int,SpriteSeer*>::iterator iter = m_mapRoleIdAndInstance.find(indexId);
	if (iter != m_mapRoleIdAndInstance.end())
	{
		return (*iter).second;
	}
	return 0;
}

bool StoryInstanceDirector::TrackPlayerAnim()
{
	// Note: Add To Obj Layer
	LevelLayer* pLayer = LevelManager::sShareInstance()->getCurrentLevelLayer();
	CCNode* pObjLayer = pLayer->getObjectLayer();

	std::map<unsigned int,StoryRoleBasicData> storyData = StoryDataCenter::Get()->GetStoryRoleBasicData();
	std::map<unsigned int,StoryRoleBasicData>::iterator iter = storyData.begin();
	while(iter != storyData.end())
	{
		bool bPosChanged = false;
		SpriteSeer* pCurHero = GetOneRole((*iter).first);

		std::map<unsigned int,StoryFrameData>::iterator frameIter = (*iter).second.mMapStoryFramesData.find((int)m_curFrame);
		if (frameIter != (*iter).second.mMapStoryFramesData.end())
		{
			//// Note: 当前帧存在
			StoryFrameData frameData = (*frameIter).second;
			CCPoint pos = frameData.getRolePos();						

			// Note: 位置发生变化，移动位置，或者新创建角色
			if (StoryFrameData::IsPosChanged(pos))
			{
				bPosChanged = true;

				bool bVisiable = pCurHero->getRoot()->isVisible();
				if (bVisiable == false)
				{
					pCurHero->getRoot()->setVisible(true);
				}
				pCurHero->setPosition(pos);
				pObjLayer->reorderChild(pCurHero,LevelLayer::sCalcZorder(pos));
			}

			int actorId = frameData.getActorId();
			if (actorId != -1)
			{
				pCurHero->SetAnim(actorId,0);
			}

			int nFlip = frameData.getFlip();
			if (nFlip != -1)
			{
				if (nFlip == 0)
				{
					pCurHero->SetAnimFlipX(false);
				}
				else if (nFlip == 1)
				{
					pCurHero->SetAnimFlipX(true);
				}
			}
		}

		if (false == bPosChanged)
		{
			// Note: 不存在的情况下处理移动
			if (false == bPosChanged)
			{
				unsigned int preFrameIndex = 0;
				unsigned int nextFrameIndex = 0;
				CCPoint prePoint = CCPointZero;
				CCPoint nextPoint = CCPointZero;
				if(StoryDataCenter::Get()->GetPreAndNextPointFrameData((*iter).first,(int)m_curFrame,preFrameIndex,nextFrameIndex,prePoint,nextPoint))
				{
					// Note: 处理移动

					unsigned int sumMoveFrames = (nextFrameIndex - preFrameIndex);
					unsigned int runningFrames = (int)m_curFrame - preFrameIndex;
					if (runningFrames >= sumMoveFrames)
					{
						return false;
					}
					// Note: 运动速率
					CCPoint dir = ccpSub(nextPoint,prePoint);
					float distance = sqrt(ccpLengthSQ(dir));
					float vPerFrame = distance/sumMoveFrames;
					if(dir.x == 0 && dir.y == 0)
					{
						return false;
					}
					dir = ccpNormalize(dir);

					CCPoint nowPoint = ccpAdd(prePoint,ccp(vPerFrame*runningFrames*dir.x,vPerFrame*runningFrames*dir.y));
					pCurHero->setPosition(nowPoint);
					pObjLayer->reorderChild(pCurHero,LevelLayer::sCalcZorder(nowPoint));
				}
			}
		}

		iter++;
	}

	return true;
}

bool StoryInstanceDirector::IsStart()
{
	return m_isStart;
}

//void StoryInstanceDirector::ClearInstanceIds()
//{
//	m_setAnimOverInstanceIds.clear();
//}
//
//void StoryInstanceDirector::AddOneInstanceId(unsigned int instanceId)
//{
//	m_setAnimOverInstanceIds.insert(instanceId);
//}
//
//bool StoryInstanceDirector::IsOneInstanceExist(unsigned int instanceId)
//{
//	std::set<unsigned int>::iterator iter = m_setAnimOverInstanceIds.find(instanceId);
//	if (iter != m_setAnimOverInstanceIds.end())
//	{
//		return true;
//	}
//	return false;
//}