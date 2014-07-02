#include <cmath>

#include "OnlineNetworkManager.h"
#include "SpriteSeerListener.h"
#include "SpriteSeer.h"

#include "LevelLayer.h"
#include "GameManager.h"
#include "UserData.h"
#include "GameDataManager.h"
#include "InstanceManager.h"
#include "MainLandManager.h"



SpriteSeerListener* SpriteSeerListener::sInstance = NULL;


SpriteSeerListener::SpriteSeerListener()
	:m_bSendMoveMesage(false)
	, m_bSendEndMoveMesage(false)
	, m_endMoveTime(0.0f)
{
	m_lastMoveSyn = 0;
}

SpriteSeerListener::~SpriteSeerListener()
{

}


SpriteSeerListener* SpriteSeerListener::sShareInstance()
{
	if (sInstance == NULL)
	{
		sInstance = new SpriteSeerListener();
	}

	return sInstance;
}



void SpriteSeerListener::HandleLayerTouchBeginEvent(cocos2d::CCNode* obj, cocos2d::CCPoint pt)
{
	SpriteSeer* seer = (SpriteSeer*)obj;
	if (seer)
	{
		if (!MainLandManager::Get()->isMainLand(LevelManager::sShareInstance()->getCurMapId()))
		{
			GameDataManager::Get()->setHeroAutoAttack(false);
		}			

		TaskPosition taskPos;
		taskPos.cityId = 0;
		taskPos.position = ccp(0, 0);
		GameDataManager::Get()->setTaskPosition(taskPos);

		if (MOVE_BY_MOUSE == seer->GetMoveType())
		{
			LevelLayer * layer = LevelManager::sShareInstance()->getCurrentLevelLayer();
			if (layer)
			{
				CPhysicsLayer * mapLayer = layer->getPhysicsLayer();
				CCPoint pixPos = seer->getPosition();
				if (mapLayer)
				{
					if (mapLayer->isPointReachable(pt))
					{
						seer->moveToTarget(pt, pixPos);
					}
					else
					{
						CCPoint vec = ccpNormalize(ccpSub(pt, pixPos));
						do
						{
							pt = ccpSub(pt, vec);
						} while (!mapLayer->isPointReachable(pt));
						seer->moveToTarget(pt, pixPos);
					}
					
					if (mapLayer->isPointReachable(pt))
					{
						layer->showTouchEffect(pt);
					}
				}
			}		
		}
	}

}


void SpriteSeerListener::HandleLayerActiveEvent(cocos2d::CCNode* obj, sActiveLevelConfig* data)
{
	ASSERT(data != NULL, "active level config is NULL");

	SpriteSeer* seer = (SpriteSeer*)obj;
	if (seer)
	{
		LevelLayer* layer = LevelManager::sShareInstance()->getCurrentLevelLayer();
		if (layer)
		{
			CCPoint pt = ccp(UserData::GetUserXPos(),UserData::GetUserYPos());
			data->pos = pt;
			pt = layer->getSeerBornPoint(*data);
			seer->setPosition(pt);
			if (!MainLandManager::Get()->isMainLand(LevelManager::sShareInstance()->getCurMapId()))
			{
				CCPoint point = InstanceManager::Get()->getPlayerPosition();
				seer->setPosition(point);
			}
			layer->getObjectLayer()->reorderChild(seer, LevelLayer::sCalcZorder(pt));

			//
			BaseListener::HandleLayerActiveEvent(obj, data);

			//send enter map message
			if (seer->getType() == MAP_TAG_SEER)
			{
				//OnlineNetworkManager::sShareInstance()->sendPlayerEnterMapMessage(layer->getID(), pt.x, pt.y,0);
			}

			if (!MainLandManager::Get()->isMainLand(LevelManager::sShareInstance()->getCurMapId()))
			{
				OnlineNetworkManager::sShareInstance()->sendPlayerBattleMoveMessage(UserData::Get()->getUserId(), seer->getPosition(), seer->getDirectionVector(), true);
			}
		}
	}
}


void SpriteSeerListener::HandleLayerDeactiveEvent(cocos2d::CCNode* obj)
{
	SpriteSeer* seer = (SpriteSeer*)obj;
	if (seer)
	{
		LevelLayer* layer = LevelManager::sShareInstance()->getCurrentLevelLayer();
		if (layer)
		{
			//send leave map message
			if (seer->getType() == MAP_TAG_SEER)
			{
				//OnlineNetworkManager::sShareInstance()->sendPlayerLeaveMapMessage(layer->getID());
			}
		}

		//
		BaseListener::HandleLayerDeactiveEvent(obj);
	}
}


void SpriteSeerListener::HandleLayerUpdateEvent(cocos2d::CCNode* obj, float dt)
{
	static float s_time = 0.0f;
	s_time += dt;

	
	static unsigned int s_count = 0;

	SpriteSeer* seer = (SpriteSeer*)obj;
	if (seer)
	{
		if (MOVE_BY_JOY == seer->GetMoveType())
		{
			seer->DoRun();
		}	

		
		LevelLayer* layer = LevelManager::sShareInstance()->getCurrentLevelLayer();
		CCPoint pos = seer->getPosition();
		if (layer)
		{
			if(seer->isPosChange())
			{
				layer->getObjectLayer()->reorderChild(seer, LevelLayer::sCalcZorder(seer->getPosition()));
			}

			if(seer->isCellPosChange())
			{
				if(MainLandManager::Get()->isMainLand(LevelManager::sShareInstance()->getCurMapId()))
				{
					m_lastSendPos = pos;
					m_bSendMoveMesage = true;
				}
				else
				{
					m_bSendEndMoveMesage = true;
					m_endMoveTime = 0.0f;

					s_count++;
					OnlineNetworkManager::sShareInstance()->sendPlayerBattleMoveMessage(UserData::Get()->getUserId(), seer->getPosition(), seer->getDirectionVector(), false);
					//CCPoint pyPos = LevelManager::sShareInstance()->pointPixelToCell(seer->getPosition());
					//CCLog("pos(%f, %f)", pyPos.x, pyPos.y);

					
				}
			}
			else
			{
				if(m_bSendEndMoveMesage)
				{
					m_endMoveTime += dt;
					float t =  layer->getPhysicsLayer()->getCellWidth() / seer->GetMoveSpeed();
					t = t * 1.5f;
					if(m_endMoveTime > t)
					{
						m_bSendEndMoveMesage = false;
						m_endMoveTime = 0.0f;
						OnlineNetworkManager::sShareInstance()->sendPlayerBattleMoveMessage(UserData::Get()->getUserId(), seer->getPosition(), seer->getDirectionVector(), true);

					}
					

				}
			}
			/*else if(seer->isDirectionChange())
			{
				if(!LevelManager::sShareInstance()->isMainLandLevel())
				{
					OnlineNetworkManager::sShareInstance()->sendPlayerBattleMoveMessage(UserData::Get()->getUserId(), seer->getPosition(), seer->getDirectionVector());

				}

			}*/
			
		}

		if(MainLandManager::Get()->isMainLand(LevelManager::sShareInstance()->getCurMapId()))
		{
			/*if(m_oldAnimID != seer->GetAnimID())
			{
			m_oldAnimID = seer->GetAnimID();
			OnlineNetworkManager::sShareInstance()->sendPlayerMoveMessage(m_lastSendPos.x, m_lastSendPos.y, seer->GetAnimID(), seer->IsAnimFlipX());
			}*/

			if(m_bSendMoveMesage)
			{
				m_lastMoveSyn += dt;
				if(m_lastMoveSyn > 1.0f)
				{
					CCPoint cellPos = LevelManager::sShareInstance()->pointPixelToCell(m_lastSendPos);
					OnlineNetworkManager::sShareInstance()->sendPlayerMoveMessage(cellPos.x, cellPos.y, seer->GetAnimID(), seer->IsAnimFlipX());
					m_lastMoveSyn = 0.0f;
					m_bSendMoveMesage = false;
				}
			}
		}
	}

	if(s_time >= 1.0f)
	{
		
		s_time = 0.0f;
		if(s_count != 0)
		{
			//CCLog("***** Count : %u", s_count);
			s_count = 0;
		}
		
	}
}


void SpriteSeerListener::HandleObjectMoveEvent(SpriteBase* obj)
{
	//CCLog("SpriteSeerListener::HandleObjectMoveEvent");
	SpriteSeer* seer = (SpriteSeer*)obj;
	if (seer)
	{
		//send walk message if player
		if (seer->getType() == MAP_TAG_SEER)
		{
            CCPoint seerPosition = seer->getPosition();
            
			//OnlineNetworkManager::sShareInstance()->sendPlayerMoveMessage(seerPosition.x, seerPosition.y);
		}
	}
}


void SpriteSeerListener::HandleObjectEndMoveEvent(SpriteBase* obj)
{
	//TODO 

}