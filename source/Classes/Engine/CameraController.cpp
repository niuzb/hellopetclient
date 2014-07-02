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

#include "CameraController.h"
#include "cocos2d.h"
#include "LevelManager.h"
#include "SpriteSeer.h"
#include "SceneLayer.h"
#include "GameManager.h"
#include "LevelLayer.h"
#include "GameManager.h"
#include "CCShake.h"

USING_NS_CC;

#define SHAKE_FREQUENCY 45

CameraController *CameraController::s_pSharedCameraController = NULL;

CameraController *CameraController::sharedCameraController()
{
	if(s_pSharedCameraController == NULL)
	{
		s_pSharedCameraController = new CameraController();
	}
	return s_pSharedCameraController;
}

void CameraController::purgeInstance()
{
	if (s_pSharedCameraController)
	{
		delete s_pSharedCameraController;
		s_pSharedCameraController = NULL;
	}
}

CameraController::CameraController()
{
	m_fLastUpdateTime = 0;
    
    mShakeTime = 0.0f;
    mShakeMagnitude = 0.0f;
    mShakeOffsetY = 0.0f;

	m_eCameraFollowType = E_FollowHero;
	m_followPoint = CCPointZero;
}

CameraController::~CameraController()
{
}

void CameraController::ResetValue()
{
	m_eCameraFollowType = E_FollowHero;
}


void CameraController::revertArch()
{
    LevelLayer* level =  GameManager::Get()->GetSceneLayer()->getLevelLayer();
    level->setAnchorPoint(ccp(0,0));
    level->setScale(1.0f);
}

void CameraController::shakeAndScale(float shakeTime, float zoomintime, float zoomouttime, float zoominscale, float zoomoutscale)
{
    mShakeTime = shakeTime;
    mShakeMagnitude = 0;
    
    LevelLayer* level =  GameManager::Get()->GetSceneLayer()->getLevelLayer();
    level->setScale(1.0f);
    CCPoint arch = level->getAnchorPoint();
    
    CCSize winsize = CCDirector::sharedDirector()->getWinSize();
    CCSize mapsize = level->getMapSizeInPixel();
    
    CCPoint heroPos = GameManager::Get()->getHero()->getPosition();
    
    float px = heroPos.x / winsize.width;
    float py = heroPos.y / winsize.height;
    
    CCPoint newar = ccp(px, py);
    
    level->setAnchorPoint(ccp(px,py));
    
    CCActionInterval* actionBy1 = CCScaleTo::create(zoomintime, zoominscale);
    CCActionInterval* actionBy2 = CCScaleTo::create(zoomouttime, zoomoutscale);

    CCEaseBounceInOut* a1 = CCEaseBounceInOut::create(actionBy1);
    CCEaseBounceInOut* a2 = CCEaseBounceInOut::create(actionBy2);
    CCCallFunc* f1 = CCCallFunc::create(this, callfunc_selector(CameraController::revertArch));
    CCSequence* seq = (CCSequence*)CCSequence::create(a1,a2,f1,NULL);
    level->runAction(seq);
}

void CameraController::shakeOnly(float shakeTime, float magnitude)
{
    mShakeTime = shakeTime;
    mShakeMagnitude = magnitude;  
}

void CameraController::levelScale()
{
    LevelLayer* level =  GameManager::Get()->GetSceneLayer()->getLevelLayer();
    level->setScale(1.0f);
    CCActionInterval*  actionBy = CCScaleBy::create(0.1, 1.2f, 1.2f);
    level->runAction( CCSequence::create(actionBy, actionBy->reverse(), NULL));
}

void CameraController::Update(float dt)
{
    //CCLog("cameraController update:%f\n", dt);
	if (m_eCameraFollowType == E_FollowHero)
	{
		// update position
		SpriteSeer *seer = GameManager::Get()->getHero();
		if (seer == NULL)
			return;

		followToOnePoint(seer->getPosition(),dt);
	}
	else if(m_eCameraFollowType == E_FixPoint)
	{
		followToOnePoint(m_followPoint,dt);
	}
}

void CameraController::followToOnePoint(CCPoint p,float dt)
{
	mShakeOffsetY = 0.0f;
	if (mShakeTime > 0.0f) {
		mShakeTime -= dt;
		mShakeOffsetY = (float) (sin(mShakeTime * SHAKE_FREQUENCY) * mShakeMagnitude);
	}

	// update position

	//CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	CCSize screenSize = CCDirector::sharedDirector()->getRenderSize();

	CCPoint center = ccp(screenSize.width / 2 , screenSize.height / 2);
	CCRect mapRect = LevelManager::sShareInstance()->getCurrentLevelLayer()->getMapRect();

	float ymin = mapRect.getMinY() + screenSize.height / 2;
	float ymax = mapRect.getMaxY() - screenSize.height / 2;
	float xmin = mapRect.getMinX() + screenSize.width / 2;
	float xmax = mapRect.getMaxX() - screenSize.width / 2; 

	CCPoint seerPos = p;
	seerPos.x = int(seerPos.x);
	seerPos.y = int(seerPos.y);
	CCPoint targetPos = ccpSub(seerPos, center);

	if(seerPos.x < xmin)
	{
		targetPos.x = 0;
	}

	if(seerPos.x > xmax)
	{
		targetPos.x = xmax - xmin;
	}

	if(seerPos.y < ymin)
	{
		targetPos.y = 0;
	}

	if(seerPos.y > ymax)
	{
		targetPos.y = ymax - ymin;
	}

	targetPos.y += mShakeOffsetY;
	CCDirector::sharedDirector()->setLevelRenderCameraOffset(targetPos);
}
