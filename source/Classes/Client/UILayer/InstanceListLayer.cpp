#include "OnlineNetworkManager.h"
#include "InstanceListLayer.h"
#include "AspriteManager.h"
#include "TXGUIHeader.h"
#include "InstanceManager.h"
#include "GameFontManager.h"
#include "XLogicManager.h"
#include "ResoureUpdate.h"
#include "GameConfigFromLuaManager.h"
#include "MainMenuLayer.h"
#include "GameManager.h"
#include "StoryInstanceDirector.h"
#include "MessageBoxLayer.h"
#include "Localization.h"
#include "AutoOnHook.h"
#include "GameAudioManager.h"
#include "LuaTinkerManager.h"
#include "UserData.h"

#define MAX_ROW 2
#define MAX_COL 4
#define INSTANCE_NODE_TAG 10000
#define TASK_MARK_TAG     12345
#define TASK_MARK_ZORDER  10000

using namespace TXGUI;

InstanceListLayer::InstanceListLayer()	
{
	this->m_FuBenId =  0;
}

InstanceListLayer::~InstanceListLayer()
{
	UIManager::sharedManager()->RemoveUILayout("InstanceList");
}

bool InstanceListLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}

	m_curUiAs = AspriteManager::getInstance()->getAsprite(KUI_BIN);
	UIManager *manager = UIManager::sharedManager();

	instanceListLayout = manager->CreateUILayoutFromFile("UIplist/instanceListUI.plist", this, "InstanceList");	

	manager->RegisterMenuHandler("InstanceList","closeInstanceList",
		menu_selector(InstanceListLayer::closeInstanceList), this);	

	this->setVisible(false);

	taskInstanceId = 0;

	return true;
}

void InstanceListLayer::openInstanceList()
{
	GameAudioManager::sharedManager()->playEffect(350001,false);
	GameManager::Get()->GetSceneLayer()->getMainMenuLayer()->GetBattleCoverLayer()->closeBattleCoverLayer(NULL);
	this->setVisible(true);	
	MainMenuLayer::PushOneLayer(this);
	this->setScale(0);
	CCArray *arrayOfActions = CCArray::create();

	CCActionInterval *scaleIn = CCScaleTo::create(0.1f, 1.0f); 
	CCCallFunc *fun2 = CCCallFunc::create(this, callfunc_selector(InstanceListLayer::refreshInstanceListLayer));
	
	arrayOfActions->addObject(fun2);
	arrayOfActions->addObject(scaleIn);

	CCFiniteTimeAction *sequence = CCSequence::create(arrayOfActions);
	this->runAction(sequence);
}

void InstanceListLayer::closeInstanceList(CCObject* sender)
{
	this->setVisible(false);	
	MainMenuLayer::RemoveOneLayer(this);

	ShowChatBar(true,-1);	
}

void InstanceListLayer::refreshInstanceListLayer()
{	
	UIScrollPage *page = instanceListLayout->FindChildObjectByName<UIScrollPage>("instanceListScrollPage");

	//清除已有的任务标记
	for (int i = 0; i < page->getPageCount(); i++)
	{
		CCLayer * layer = page->getPageLayer(i);
		CCNode * tMark = layer->getChildByTag(TASK_MARK_TAG);
		if (tMark)
		{
			layer->removeChildByTag(TASK_MARK_TAG);
		}
	}


	if (taskInstanceId)
	{
		vector<InstanceInfo> instanceList = InstanceManager::Get()->instanceList;
		int count = instanceList.size();
		ScrollPagePosition position;
		for(int i=0;i < count;i++)
		{
			if (instanceList[i].id == taskInstanceId)
			{
				position = getScrollPagePos(i);
				
				CCLayer * layer = page->getPageLayer(position.page);
				if (!layer)
				{
					break;
				}

				CCPoint pt;
				ASprite * as = AspriteManager::getInstance()->getAsprite(KICON_BIN);
				int taskMarkId = getResourceIDByName("map_ui_system_icon_FRAME_ICON_EXCLAMATORYMARK");
				CCSprite * taskMark = as->getSpriteFromFrame_Middle(taskMarkId, 0, pt);

				taskMark->setPosition(scrollPosToPoint(position));
				taskMark->setTag(TASK_MARK_TAG);
				taskMark->setVisible(true);
				layer->addChild(taskMark);

				page->moveToPage(position.page, false);
				break;
			}	
		}		
	}
	else
	{
		page->moveToPage(page->getPageCount() - 1, false);
	}	
}

void InstanceListLayer::addInstancesFromList(const std::vector<InstanceInfo>& instanceList)
{
	int count = instanceList.size();
	ScrollPagePosition position;
	for(int i=0;i < count;i++)
	{
		position = getScrollPagePos(i);
		addSigleInstance(instanceList[i], position);		
	}
}

void InstanceListLayer::addSigleInstance(InstanceInfo info, ScrollPagePosition position)
{
	UIScrollPage *page = instanceListLayout->FindChildObjectByName<UIScrollPage>("instanceListScrollPage");
	
	//创建足够的页数
	while(position.page >= page->getPageCount())
	{
		CCLayer* layer = CCLayer::create();
		layer->setAnchorPoint(ccp(0, 0));		
		page->addPage(layer);
	}
	CCLayer * layer = page->getPageLayer(position.page);
	ASSERT(layer != NULL, "InstanceListLayer : addSigleInstance : null layer");

	CCNode * insNode = layer->getChildByTag(position.index);
	ASSERT(insNode == NULL, "InstanceListLayer : addSigleInstance : the instance already added!");

	//读取资源
	ASprite *as = AspriteManager::getInstance()->getAsprite(KUI_BIN);
	//std::string instanceConfigName = GameConfigFromLuaManager::Get()->getInstanceIconName(info.id);
	//std::string instanceConfigName = GameConfigFromLuaManager::Get()->callLuaFunc<const char *>("InstanceConfigTable", "getInstanceIcon", info.id);
	std::string instanceConfigName = LuaTinkerManager::Get()->getLuaConfig<const char *>("InstanceList", "instances", info.id, "Icon");

	std::transform(instanceConfigName.begin(), instanceConfigName.end(), instanceConfigName.begin(), towupper);
	instanceConfigName = std::string("map_ui_system_icon_FRAME_") + instanceConfigName;
    
	int normalBtnId = getResourceIDByName("map_ui_FRAME_INSTANCE_GRID1");
	int selectBtnId = getResourceIDByName("map_ui_FRAME_INSTANCE_GRID1_CLICKED");
	int isStarId = getResourceIDByName("map_ui_FRAME_INSTANCE_STAR");
	int notStarId = getResourceIDByName("map_ui_FRAME_INSTANCE_STAR_BLANK");
	int instanceIconId = getResourceIDByName(instanceConfigName.c_str());
    int taskMarkId = getResourceIDByName("map_ui_system_icon_FRAME_ICON_EXCLAMATORYMARK");
	
	CCPoint pt;
	CCSprite *pNormalBtn = as->getSpriteFromFrame_Middle(normalBtnId, 0, pt);
	CCSprite *pSelectBtn = as->getSpriteFromFrame_Middle(selectBtnId ,0,pt);
    
	//创建副本按钮
	IconButton * pBtn = new IconButton(pNormalBtn, NULL, pSelectBtn, this, 
					menu_selector(InstanceListLayer::onPressInstanceBtn));					
	pBtn->autorelease();		
	pBtn->setContentSize(pNormalBtn->getContentSize());
	pBtn->setPosition(ccp(0,0));
	pBtn->SetButtonIndex(position.index);

	//创建副本星星，位置偏移分别为绕圆周上偏左30度，正上，上偏右30度
	CCSprite * star1 = as->getSpriteFromFrame_Middle(info.star>=1 ? isStarId : notStarId ,0,pt);
	CCSprite * star2 = as->getSpriteFromFrame_Middle(info.star>=2 ? isStarId : notStarId ,0,pt);
	CCSprite * star3 = as->getSpriteFromFrame_Middle(info.star>=3 ? isStarId : notStarId ,0,pt);

	CCPoint offsetStar1 = ccp(-45,77.9);
	CCPoint offsetStar2 = ccp(0,90);
	CCPoint offsetStar3 = ccp(45,77.9);

	star1->setPosition(offsetStar1);
	star2->setPosition(offsetStar2);
	star3->setPosition(offsetStar3);

	//创建副本名称标签
	float fontSize = GameFontManager::smallFontSize();
	CCSize nameLabelSize = CCSizeMake(200 / CC_CONTENT_SCALE_FACTOR(), fontSize * 2.0f);
	//std::string instanceName = GameConfigFromLuaManager::Get()->getInstanceName(info.id);
	std::string instanceName = LuaTinkerManager::Get()->getLuaConfig<const char *>("InstanceList", "instances", info.id, "RaidName");

	UILabelTTF * instanceLabel = UILabelTTF::create(instanceName.c_str(), KJLinXin, fontSize * 1.5f,
				nameLabelSize, kCCTextAlignmentCenter,kCCVerticalTextAlignmentBottom);
    
    //CCPoint p = scrollPosToPoint(position);
	instanceLabel->setPosition(ccp(10, -50));

	//创建副本图标
	ASprite *as1 = AspriteManager::getInstance()->getAsprite(KICON_BIN);
	CCSprite *pIcon = as1->getSpriteFromFrame_Middle(instanceIconId, 0, pt);
	pIcon->setPosition(ccp(0, 0));
    
    


	//创建副本结点
	CCNode * instanceNode = CCNode::create();

	instanceNode->setTag(INSTANCE_NODE_TAG + position.index);	
	instanceNode->setPosition(scrollPosToPoint(position));

	instanceNode->addChild(pIcon);
	instanceNode->addChild(pBtn);	
	instanceNode->addChild(instanceLabel);	
	//if (info.star > 0)
	{
		instanceNode->addChild(star1);
		instanceNode->addChild(star2);
		instanceNode->addChild(star3);
	}
	
	layer->addChild(instanceNode);	
}

void InstanceListLayer::removeSigleInstance(ScrollPagePosition position)
{
	UIScrollPage *page = instanceListLayout->FindChildObjectByName<UIScrollPage>("instanceListScrollPage");
	ASSERT(position.page < page->getPageCount(), "InstanceListLayer : removeSigleInstance : invalid position");
	
	CCLayer * layer = page->getPageLayer(position.page);
	layer->removeChildByTag(INSTANCE_NODE_TAG + position.index);
}

void InstanceListLayer::onPressInstanceBtn(CCObject *sender)
{	
	CCLOG("InstanceListLayer: onPressInstanceBtn");
	CCMenuItem* menuItem = dynamic_cast<CCMenuItem*>(sender);
	if(menuItem)
	{
		CCNode* node = menuItem->getParent();
		CCMenu* menu = dynamic_cast<CCMenu*>(node);
		if(menu)
		{
			CCNode* parent = menu->getParent();
			IconButton* button = dynamic_cast<IconButton*>(parent);
			if(button)
			{
				//closeInstanceList(NULL);
				int buttonIndex = button->GetButtonIndex();
				InstanceInfo info = InstanceManager::Get()->instanceList[buttonIndex];
                m_FuBenId = info.id;
                int star = info.star;
                if(star > 0)
                {
                    //std::string instanceConfigName = GameConfigFromLuaManager::Get()->getInstanceName(info.id);
					//std::string instanceConfigName = LuaTinkerManager::Get()->getLuaConfig<const char *>("InstanceList", "instances", //info.id, "RaidName");
                    
                    USERINFO info = UserData::GetUserInfo();
                    int staming = info.m_stamina;
                    char buf[10];
                    sprintf(buf, "%d", staming);
                    
                    std::string instanceConfigName = Localizatioin::getLocalization("M_AUTOFIGHT_HINT");
                    const char* msg1 = Localizatioin::getLocalization("M_AUTOFIGHT_FIGHT");
                    const char* msg2 = Localizatioin::getLocalization("M_AUTOFIGHT_AUTOFIGHT");
                    
                    instanceConfigName += " ";
                    instanceConfigName += buf;
                    MessageBox::Show(instanceConfigName.c_str(),this,menu_selector(InstanceListLayer::OnFight), menu_selector(InstanceListLayer::OnAutoOnHook));
                    MessageBox::AdjustStyle(msg1, msg2);
                    MessageBox::showCloseBtn();
                }
                else
                {
                    Fight(info.id);
                }
			}
		}
	}
}

void InstanceListLayer::onEventMsgInstanceList(const std::vector<InstanceInfo>& instanceInfos)
{
	this->addInstancesFromList(InstanceManager::Get()->instanceList);
}

ScrollPagePosition InstanceListLayer::getScrollPagePos(int index)
{
	ScrollPagePosition spPos;
	spPos.index = index;
	spPos.page = index / (MAX_ROW * MAX_COL);
	spPos.row  = index % (MAX_ROW * MAX_COL) / MAX_COL;
	spPos.col  = index % (MAX_ROW * MAX_COL) % MAX_COL;

	return spPos;
}

CCPoint InstanceListLayer::scrollPosToPoint(ScrollPagePosition position)
{	
	//横竖坐标间距的一半
	float halfH = 120.0f;
	float halfV = 100.0f;

	//横竖坐标偏移，左下角为原点
	float offsetH = 0.0f;
	float offsetV = -35.0f;
	float HDelta, VDelta;

	HDelta =   halfH * (2 * position.col + 1 - MAX_COL) + offsetH;
	VDelta = - halfV * (2 * position.row + 1 - MAX_ROW) + offsetV;

	return ccp(HDelta, VDelta);
}

void InstanceListLayer::closeLayerCallBack( void )
{
	this->setVisible(false);	
}

void InstanceListLayer::OnAutoOnHook(CCObject* sender)
{
    MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
	if (mLayer)
	{
        mLayer->ShowAutoOnHook();
        GetAutoOnHook()->sendCSABMonsterReq(m_FuBenId);
	}
}

void InstanceListLayer::OnFight(CCObject* sender)
{
    Fight(m_FuBenId);
}

void InstanceListLayer::Fight(int id)
{
    InstanceManager::Get()->setCurInstanceId(id);
    int instanceId = InstanceManager::Get()->getCurInstanceId();
    
    ASSERT(instanceId != 0, "SpriteTranspointListener: Instance Id not init yet.");
    
    //StoryInstanceDirector::Get()->setIsFirstComeInInstance(true);
    XLogicManager::sharedManager()->createBattle(instanceId,0);
    
    ResoureUpdate::sharedResoureUpdate()->realTimeUpdate(id);
    if (GameManager::Get()->GetSceneLayer())
    {
        GameManager::Get()->GetSceneLayer()->showLoading(true);
    }
}

