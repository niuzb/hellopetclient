#include "SpriteOtherSeerListener.h"
#include "SpriteSeer.h"

#include "LevelLayer.h"
#include "GameManager.h"
#include "SpriteElfManager.h"


SpriteOtherSeerListener* SpriteOtherSeerListener::sInstance = NULL;



SpriteOtherSeerListener::SpriteOtherSeerListener()
{

}

SpriteOtherSeerListener::~SpriteOtherSeerListener()
{

}


SpriteOtherSeerListener* SpriteOtherSeerListener::sShareInstance()
{
	if (sInstance == NULL)
	{
		sInstance = new SpriteOtherSeerListener();
	}

	return sInstance;
}



void SpriteOtherSeerListener::HandleLayerTouchBeginEvent(cocos2d::CCNode* obj, cocos2d::CCPoint pt)
{
	
}


void SpriteOtherSeerListener::HandleLayerActiveEvent(cocos2d::CCNode* obj, sActiveLevelConfig* data)
{
	//BaseListener::HandleLayerActiveEvent(obj, data);
}


void SpriteOtherSeerListener::HandleLayerUpdateEvent(cocos2d::CCNode* obj, float dt)
{
	SpriteSeer* seer = dynamic_cast<SpriteSeer*>(obj);
	if (seer)
	{
		LevelLayer* layer = LevelManager::sShareInstance()->getCurrentLevelLayer();
		if(layer)
		{
			if(seer->isCellPosChange())
			{
				layer->getObjectLayer()->reorderChild(seer, LevelLayer::sCalcZorder(seer->getPosition()));
			}
		}
		
	}
}


void SpriteOtherSeerListener::HandleObjectMoveEvent(SpriteBase* obj)
{
	
}


void SpriteOtherSeerListener::HandleObjectEndMoveEvent(SpriteBase* obj)
{
	//TODO 

}



void SpriteOtherSeerListener::HandleNetWorkUpdate(SpriteBase* obj, unsigned int uid, cocos2d::CCPoint pt, unsigned int animID, bool bFlip)
{
	SpriteSeer* seer = (SpriteSeer*)obj;
	if (seer)
	{
		//if(animID != seer->GetAnimID())
		//{
		//	seer->SetAnim(animID, 0);
		//	seer->SetAnimFlipX(bFlip);
		//}
		
		int actionID = kTypeRun_FaceHor_MAIN;
		CCPoint pos = seer->getPosition();
		if(fabs(pos.x - pt.x) > 15.0f || fabs(pos.y - pt.y) > 15.0f)
		{
			CCPoint dir = ccpSub(pt, pos);
			dir = ccpNormalize(dir);
			seer->setDirection(dir);
			// 判断是否在主城中
			m_curfaceDir = seer->getDirection();
			switch(m_curfaceDir)
			{
			case DIRECTION_LEFT:
				actionID = kTypeRun_FaceHor_MAIN;
				if(seer->GetAnimID() != actionID || (seer->GetAnimID() == actionID && seer->IsAnimFlipX()))
					seer->SetAnim(actionID, 1, true);		 
				break;
			case DIRECTION_RIGHT:
				actionID = kTypeRun_FaceHor_MAIN;
				if(seer->GetAnimID() != actionID || (seer->GetAnimID() == actionID && !seer->IsAnimFlipX()))
				{
					seer->SetAnim(actionID, 1, true);
					seer->SetAnimFlipX(true);
				}
				
				break;
			case DIRECTION_UP:
				actionID = kTypeRun_FaceUp_MAIN;
				if(seer->GetAnimID() != actionID )
				{
					seer->SetAnim(actionID, 1, true);
				}
				
				break;

			case DIRECTION_BOTTOM:
				actionID = kTypeRun_FaceDown_MAIN;
				if(seer->GetAnimID() != actionID)
				{
					seer->SetAnim(actionID, 1, true);
				}

				break;

			default:
				actionID = kTypeRun_FaceHor_MAIN;
				if(seer->GetAnimID() != actionID || (seer->GetAnimID() == actionID && seer->IsAnimFlipX()))
				{
					seer->SetAnim(actionID, 1, true);
				}

				break;
			}

			CCCallFunc* endFunc = CCCallFuncND::create(this, 
				callfuncND_selector(SpriteOtherSeerListener::EndMove),
				(void *)uid);

			float speed = 180.0f;//seer->GetSpeed();	//ccpDistance(pos, pt) / 0.8f;
			seer->moveToNoPhysics(pt, speed, endFunc);

			// seer->moveToTarget(pt, seer->getPosition(),NULL, NULL);

			SpriteElfManager::Get()->PushOneElfCloseToState(seer,actionID);
		}
		else
		{
			EndMove(NULL, seer);
		}
	}
}

void SpriteOtherSeerListener::EndMove( CCNode* pNode, void* pData)
{
	LevelLayer* layer = LevelManager::sShareInstance()->getCurrentLevelLayer();
	if (layer)
	{
		unsigned int uid = (unsigned int)(pData);
		std::map<unsigned int, LevelLayer::WAKL_INFO>::iterator iterWalk = layer->m_walkInfo.find(uid);
		if(iterWalk != layer->m_walkInfo.end())
		{
			iterWalk->second.idleTime.time = 1.0f + (float)(rand() % 10) / 10.0f;
			iterWalk->second.idleTime.curTime = 0.0f;
		}

		std::map<uint32_t, OthersPlayerInfo>::iterator itor = layer->m_othersPlayerInfo.find(uid);
		if (itor != layer->m_othersPlayerInfo.end())
		{
			OthersPlayerInfo playerInfo = (*itor).second;

			//update seer
			SpriteSeer* seer = playerInfo.seer;

			if(seer != NULL)
			{
				int actionID = kTypeIdle_FaceHor_Stand_MAIN;

				switch(m_curfaceDir)
				{
				case DIRECTION_LEFT:
					actionID = kTypeIdle_FaceHor_Stand_MAIN;
					if(actionID != seer->GetAnimID() || (actionID == seer->GetAnimID() && seer->IsAnimFlipX() == true))
						seer->SetAnim(actionID, 1, true);		 
					break;
				case DIRECTION_RIGHT:
					actionID = kTypeIdle_FaceHor_Stand_MAIN;
					if(actionID != seer->GetAnimID() || (actionID == seer->GetAnimID() && seer->IsAnimFlipX() == false))
					{
						seer->SetAnim(actionID, 1, true);
						seer->SetAnimFlipX(true);
					}
					break;
				case DIRECTION_UP:
					actionID = kTypeIdle_FaceUp_Stand_MAIN;
					if(actionID != seer->GetAnimID())
						seer->SetAnim(actionID, 1, true);
					break;

				case DIRECTION_BOTTOM:
					actionID = kTypeIdle_FaceDown_Stand_MAIN;
					if(actionID != seer->GetAnimID())
						seer->SetAnim(actionID, 1, true);
					break;

				default:
					actionID = kTypeIdle_FaceHor_Stand_MAIN;
					if(actionID != seer->GetAnimID() || (actionID == seer->GetAnimID() && seer->IsAnimFlipX() == true))
						seer->SetAnim(actionID, 1, true);
					break;
				}

			}
		}
	}

	
}

void SpriteOtherSeerListener::HandleLayerDeactiveEvent( cocos2d::CCNode* obj )
{
}
