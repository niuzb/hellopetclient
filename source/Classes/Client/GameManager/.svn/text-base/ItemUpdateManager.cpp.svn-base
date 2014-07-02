#include "ItemUpdateManager.h"

ItemUpdateManager::ItemUpdateManager()
{
	
}

ItemUpdateManager::~ItemUpdateManager()
{
	
}

void ItemUpdateManager::Update(float dt)
{
	CCPoint cameraOffset = CCDirector::sharedDirector()->getLevelRenderCameraOffset();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();	

	CCRect cameraRect = CCRectMake(cameraOffset.x,cameraOffset.y,visibleSize.width,visibleSize.height);			 
	map<AreaItemNode *, bool>::iterator itor;
	for (itor = itemNodeMap.begin(); itor != itemNodeMap.end(); itor++)
	{
		if (!itor->first)
		{
			continue;
		}


		CCRect rect = (*itor).first->GetABBox();
		if (false == AreaItemNode::IsTwoRectsOverlapped(cameraRect,rect))
		{
			itor->first->SetUpdateOrNot(false);
			itor->second = false;
		}
		else
		{
			itor->first->SetUpdateOrNot(true);
			itor->second = true;
		}
	}
}

bool ItemUpdateManager::addToUpdateManager(AreaItemNode * itemNode)
{
	bool ret = false;
	if (itemNodeMap.find(itemNode) == itemNodeMap.end())
	{
		itemNodeMap.insert(make_pair(itemNode, true));
		ret = true;
	}
	return ret;
}

bool ItemUpdateManager::removeFromUpdateManager(AreaItemNode * itemNode)
{
	bool ret = false;
	if (itemNodeMap.find(itemNode) != itemNodeMap.end())
	{
		itemNodeMap.erase(itemNode);
		ret = true;
	}
	return ret;
}

void ItemUpdateManager::resetData()
{
	itemNodeMap.clear();
}