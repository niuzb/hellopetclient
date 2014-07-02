#include "SpriteTransPoint.h"
#include "LevelDefine.h"
#include "SpriteTranspointListener.h"
#include "EnginePlayerManager.h"
#include "AspriteManager.h"
#include "resources.h"
#include "GameFontManager.h"
#include "ParticleManager.h"
#include "EffectSprite.h"
#include "CCDirector.h"
#include "HSJoystick.h"
#include "TaskManager.h"
using namespace cocos2d;


SpriteTransPoint::SpriteTransPoint()
	:SpriteBase(MAP_TAG_TRANSPOINT)
{
	m_fnChangeMap = callfunc_selector(SpriteTransPoint::changeMap);
}

SpriteTransPoint::~SpriteTransPoint()
{
	if (m_anim)
	{
		EnginePlayerManager::getInstance()->removeAsprite(m_anim);
	}

	if(m_effect)
	{
		EnginePlayerManager::getInstance()->removeEffectAsprite(m_effect);
	}
}

SpriteTransPoint* SpriteTransPoint::node(const char *name,CCPoint pos,int mapId)                                       
{
	SpriteTransPoint *spPoint = new SpriteTransPoint();
	if (spPoint && spPoint->initWithName(name,pos,mapId))
	{
		spPoint->autorelease();
		return spPoint;
	}

	CC_SAFE_DELETE(spPoint);
	return NULL;
}

bool SpriteTransPoint::initWithName(const char *name,CCPoint pos,int mapId)                                    
{    
	m_effect = ParticleManager::Get()->createEffectSprite(104,"");
	this->addChild(m_effect);
	m_effect->SetAnim(kType_Play,1,true);
	m_effect->setPosition(pos);
	//m_effect->setPlayerNameLabelPos(m_effect->getAttachPoint(kType_PLAYER_NAME));

	m_pos = pos;
	m_mapId = mapId;

	return true;
}


int SpriteTransPoint::getMapId()
{
	return m_mapId;
}


bool SpriteTransPoint::ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* event)
{
	TaskManager::getInstance()->InterruptAutoGoToInstanceEvent();

	bool ret = false;

	CCPoint point = pTouch->getLocationInView();
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    point = ccp(point.x, screenSize.height - point.y);
	if (HSJoystick::sharedJoystick()->isPointInJoystick(point))
	{
		return false;
	}

	if(canDealWithTouch(pTouch))
	{        
		//MoveToSelfPosTarget();
		ret = true;
	}

	return ret;
}

void SpriteTransPoint::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
	CCPoint point = touch->getLocationInView();
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    point = ccp(point.x, screenSize.height - point.y);
	if (HSJoystick::sharedJoystick()->isPointInJoystick(point))
	{
		return;
	}

	if(canDealWithTouch(touch))
	{        
		MoveToSelfPosTarget();
	}

	return;
}

void SpriteTransPoint::MoveToSelfPosTarget()
{
	SpriteTranspointListener::sShareInstance()->HandleObjectTouchEvent(this, m_effect->getPosition());
}

void SpriteTransPoint::changeMap()
{
	SpriteTranspointListener::sShareInstance()->HandleTransformEvent(this);
}

cocos2d::CCPoint SpriteTransPoint::getPosition()
{
	if (m_effect)
	{
		return m_effect->getPosition();
	}
	return CCPointZero;
}

bool SpriteTransPoint::isTouchSelf(cocos2d::CCPoint pt)
{
	cocos2d::CCRect rect = getRect();

	if((pt.x >= rect.origin.x) && 
		(pt.x <= rect.origin.x + rect.size.width) &&
		(pt.y >= rect.origin.y) && 
		(pt.y <= rect.origin.y + rect.size.height))
	{
		return true;
	}

	return false;	
}

cocos2d::CCRect SpriteTransPoint::getRect()
{
	if(m_effect != NULL)
	{
		cocos2d::CCSize size = m_effect->getColliderRectSize();

		CCPoint pos = m_effect->getPosition();
		return CCRectMake(pos.x - size.width/2,pos.y - size.height/2,size.width ,
			size.height);
	}	

	return CCRectMake(0, 0, 0, 0);	
}



