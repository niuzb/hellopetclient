#include "UITutorial.h"
#include "GameManager.h"
#include "MainMenuLayer.h"

//extern enum EUiZOrder;

UITutorial::UITutorial()
{
	m_eTutorialType = kTutorialUI;
	mTutorialLayer = NULL;
}

UITutorial::UITutorial(unsigned int id):TutorialBase(id)
{
	mTutorialLayer = NULL;
	m_eTutorialType = kTutorialUI;
}

UITutorial::~UITutorial()
{

}

void UITutorial::Start()
{
	//CCLog("void UITutorial::Start() %d",m_nTutorialID);
	if (NULL == mTutorialLayer)
	{
		mTutorialLayer = TutorialLayer::create();
		MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
		if (mLayer)
		{
			mLayer->addChild(mTutorialLayer,Z_Order_TutorialLayer);
			mTutorialLayer->ShowLayer();
		}
	}
}

void UITutorial::End()
{
	if (mTutorialLayer)
	{
		mTutorialLayer->removeFromParentAndCleanup(true);
		mTutorialLayer = NULL;
	}
	// Note: 下一帧的时候销毁
	this->autorelease();
}