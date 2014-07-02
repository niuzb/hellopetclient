#include "TutorialsManager.h"
#include "UITutorial.h"

TutorialsManager* TutorialsManager::mInstance = NULL;

TutorialsManager::TutorialsManager()
{
	mTutorialInstance = NULL;	
	mDataCenter = new TutorialDataCenter();
}

TutorialsManager::~TutorialsManager()
{
	if (mDataCenter)
	{
		delete mDataCenter;
		mDataCenter = NULL;
	}
	mTutorialInstance = NULL;
}

void TutorialsManager::ResetValue()
{
}

TutorialsManager* TutorialsManager::Get()
{
	if (mInstance == 0)
	{
		mInstance = new TutorialsManager();
	}
	return mInstance;
}

void TutorialsManager::Destroy()
{
	if (mInstance)
	{
		delete mInstance;
		mInstance = 0;
	}
}

void TutorialsManager::LoadData()
{
	if (mDataCenter)
	{
		mDataCenter->InitXMLData();
	}
}


void TutorialsManager::StartOneTutorial(unsigned int id)
{
	if (mDataCenter)
	{
		ETutorialType tutorialType = (ETutorialType)mDataCenter->GetOneTutorialType(id);
		switch(tutorialType)
		{
		case kTutorialUI:
			{
				StartOneUiTutorial(id);
			}
			break;
		default:
			CCError("TutorialsManager::StartOneTutorial UnKnowTypeTutorial %d",id);
			break;
		};
	}	
}

void TutorialsManager::StartOneUiTutorial(unsigned int id)
{
	mTutorialInstance = new UITutorial(id);
	mTutorialInstance->Start();
}

void TutorialsManager::HandleOneEvent(const char* name,unsigned int type)
{
	CCLog("name %s",name);
	CCLog("type %d",type);
}