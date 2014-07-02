#include "OnlineNetworkManager.h"
#include "SpriteTranspointListener.h"
#include "SpriteTransPoint.h"
#include "SpriteSeer.h"
#include "GameManager.h"
#include "MapDataManager.h"
#include "UIDefine.h"
#include "InstanceManager.h"
#include "InstanceListLayer.h"
#include "MainMenuLayer.h"
#include "XLogicManager.h"
SpriteTranspointListener* SpriteTranspointListener::sInstance = NULL;


SpriteTranspointListener::SpriteTranspointListener()
{

}

SpriteTranspointListener::~SpriteTranspointListener()
{

}


SpriteTranspointListener* SpriteTranspointListener::sShareInstance()
{
	if (sInstance == NULL)
	{
		sInstance = new SpriteTranspointListener();
	}

	return sInstance;
}

void SpriteTranspointListener::HandleLayerActiveEvent(cocos2d::CCNode* obj, sActiveLevelConfig* data)
{
	BaseListener::HandleLayerActiveEvent(obj,data);
}


void SpriteTranspointListener::HandleObjectTouchEvent(SpriteBase* obj, cocos2d::CCPoint pt)
{
	SpriteTransPoint* transpoint = (SpriteTransPoint*)obj;
	
	if (transpoint)
	{
		int transId = transpoint->getMapId();
		//主城临时入口响应
		if(200101 == transId)
		{
			InstanceListLayer * layer = GetInstanceListLayer();
			if(layer)
			{
				OnlineNetworkManager::sShareInstance()->sendGetInstanceListMessage(0, 0);

				SpriteSeer * seer = GameManager::Get()->getHero();
				if (seer && MOVE_BY_MOUSE == seer->GetMoveType())
				{
					SEL_CallFunc cfOpenInstanceList = callfunc_selector(InstanceListLayer::openInstanceList);
					seer->moveToTarget(transpoint->getPosition(), seer->getPosition(), layer, cfOpenInstanceList);
				}
				else
				{
					layer->openInstanceList();
				}
			}	
			return;
		}

		SpriteSeer * seer = GameManager::Get()->getHero();
		if (seer && MOVE_BY_MOUSE == seer->GetMoveType())
		{
			SEL_CallFunc cfTransToNext = callfunc_selector(SpriteSeer::activePortal);
			seer->moveToTarget(transpoint->getPosition(), seer->getPosition(), seer, cfTransToNext);
		}			
	}
}


void SpriteTranspointListener::HandleLockedEvent(SpriteBase* obj)
{
	//show message notice here

}


void SpriteTranspointListener::HandleTransformEvent(SpriteBase* obj)
{
	SpriteTransPoint* transpoint = (SpriteTransPoint*)obj;
	if (transpoint)
	{
		//MapInfo* info = MapDataManager::sharedManager()->getMapInfoByMapId(transpoint->getMapId());

		int x = 0;
		int y = 0;

		/*if(info != null)
		{
			x = info->initX;
			y = info->initY;
		}*/
		OnlineNetworkManager::sShareInstance()->sendPlayerEnterMapMessage(transpoint->getMapId(),x,y,0);		
		//GameManager::Get()->changeMap(transpoint->getMapId(), KMapFromTransition);
	}
}