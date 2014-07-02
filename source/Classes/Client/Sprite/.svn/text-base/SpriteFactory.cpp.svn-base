#include "OnlineNetworkManager.h"
#include "SpriteFactory.h"
#include "SpriteElfManager.h"
#include "UserData.h"
#include "SpriteElfConfigFromLua.h"
#include "SpriteElfDataCenter.h"
#include "GameManager.h"
#include "MainMenuLayer.h"
#include "BackPackLayer.h"
#include "LevelLayer.h"

SpriteFactory* SpriteFactory::mFactory = 0;

SpriteFactory::SpriteFactory()
{
	mAttachElf = 0;
}

void SpriteFactory::PrintLog()
{
	CCLOG("SpriteFactory::PrintLog");
}

void SpriteFactory::ResetValue()
{
	mAttachElf = 0;
}

SpriteFactory* SpriteFactory::sharedFactory()
{
	if (mFactory == 0)
	{
		mFactory = new SpriteFactory();
	}
	return mFactory;
}

void SpriteFactory::Destroy()
{
	if (mFactory)
	{
		delete mFactory;
		mFactory = 0;
	}
}

int SpriteFactory::GetValue()
{
	return 2;
}

void SpriteFactory::ShowElfOnLayerAtPoint(CCNode* parentNode,int type,CCPoint pos)
{
	if (parentNode == 0)
	{
		return;
	}
	mAttachElf = (SpriteElf*)parentNode->getChildByTag(MAP_TAG_ELF);
	if (mAttachElf != 0)
	{
		mAttachElf->removeFromParentAndCleanup(true);
		mAttachElf = 0;
	}
	SpriteElf* pElf = SpriteElfManager::Get()->CreateInstance(type);
	if (pElf)
	{
		parentNode->addChild(pElf,1,MAP_TAG_ELF);
		pElf->setPosition(pos);
		pElf->SetAnim(kTypeIdle_FaceDown_Stand_OTH,0);

		mAttachElf = pElf;
	}
}

void SpriteFactory::RemoveElfFromHero(unsigned int roleId,bool bDeleteElf /* = true */)
{
	SpriteElfManager::Get()->RemoveOneElf(roleId,bDeleteElf);
}

//void SpriteFactory::PushElfIdToLuaTable()
//{
//	SpriteElfConfigFromLuaManager::getInstance()->PushElfIdToLuaTable();
//}

//int SpriteFactory::GetOneElfState(int elfId)
//{
//	return (int)SpriteElfDataCenter::Get()->GetOneElfState(elfId);
//}

void SpriteFactory::AttachElfToOneHero(unsigned int elfTypeId,unsigned int heroId)
{
	SpriteElfManager::Get()->AttachElfToOneHero(elfTypeId,heroId,0);
}

CCNode* SpriteFactory::GetMainMenuLayerNode()
{
	return (CCNode*)GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
}

bool SpriteFactory::ShowElfPanelWithBackPackLayer()
{
	MainMenuLayer* pMainMenu = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	BackPackLayer* layer = pMainMenu->GetBackPackLayer();
	if(layer)
	{
		layer->ShowElfPanelWithBackPackLayer();
	}
	return true;
}

void SpriteFactory::SendElfAwakeMessage(unsigned int awakeType)
{
	OnlineNetworkManager::sShareInstance()->SendElfAwakeMessage(awakeType);
}

void SpriteFactory::SendAwakeConfigMessage()
{
	OnlineNetworkManager::sShareInstance()->SendAwakeConfigMessage();
}