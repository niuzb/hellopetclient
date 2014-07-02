#include "StoryData.h"

bool StroyData::InsertRolePosAtFrame(unsigned int roleIndex,unsigned int frameIndex,CCPoint pos)
{
	std::map<unsigned int,StoryRoleBasicData>::iterator iter = mMapStoryRolesBasicData.find(roleIndex);
	if (iter == mMapStoryRolesBasicData.end())
	{
		StoryRoleBasicData roleBasicData;

		StoryFrameData frameData;
		frameData.setFrameIndex(frameIndex);
		frameData.setRolePos(pos);

		roleBasicData.mMapStoryFramesData.insert(std::make_pair(frameIndex,frameData));

		mMapStoryRolesBasicData.insert(std::make_pair(roleIndex,roleBasicData));
	}
	else
	{
		std::map<unsigned int,StoryFrameData>::iterator frameIter = (*iter).second.mMapStoryFramesData.find(frameIndex);
		if (frameIter != (*iter).second.mMapStoryFramesData.end())
		{
			(*frameIter).second.setRolePos(pos);
		}
		else
		{
			StoryFrameData frameData;
			frameData.setFrameIndex(frameIndex);
			frameData.setRolePos(pos);

			(*iter).second.mMapStoryFramesData.insert(std::make_pair(frameIndex,frameData));
		}
	}

	return true;
}

bool StroyData::InsertRoleActorAtFrame(unsigned int roleIndex,unsigned int frameIndex,unsigned int actorId)
{
	std::map<unsigned int,StoryRoleBasicData>::iterator iter = mMapStoryRolesBasicData.find(roleIndex);
	if (iter == mMapStoryRolesBasicData.end())
	{
		StoryRoleBasicData roleBasicData;

		StoryFrameData frameData;
		frameData.setFrameIndex(frameIndex);
		frameData.setActorId(actorId);

		roleBasicData.mMapStoryFramesData.insert(std::make_pair(frameIndex,frameData));

		mMapStoryRolesBasicData.insert(std::make_pair(roleIndex,roleBasicData));
	}
	else
	{
		std::map<unsigned int,StoryFrameData>::iterator frameIter = (*iter).second.mMapStoryFramesData.find(frameIndex);
		if (frameIter != (*iter).second.mMapStoryFramesData.end())
		{
			(*frameIter).second.setActorId(actorId);
		}
		else
		{
			StoryFrameData frameData;
			frameData.setFrameIndex(frameIndex);
			frameData.setActorId(actorId);

			(*iter).second.mMapStoryFramesData.insert(std::make_pair(frameIndex,frameData));
		}
	}

	return true;
}

bool StroyData::InsertIsFlipAtFrame(unsigned int roleIndex,unsigned int frameIndex,int nFlip)
{
	std::map<unsigned int,StoryRoleBasicData>::iterator iter = mMapStoryRolesBasicData.find(roleIndex);
	if (iter == mMapStoryRolesBasicData.end())
	{
		StoryRoleBasicData roleBasicData;

		StoryFrameData frameData;
		frameData.setFrameIndex(frameIndex);
		frameData.setFlip(nFlip);

		roleBasicData.mMapStoryFramesData.insert(std::make_pair(frameIndex,frameData));

		mMapStoryRolesBasicData.insert(std::make_pair(roleIndex,roleBasicData));
	}
	else
	{
		std::map<unsigned int,StoryFrameData>::iterator frameIter = (*iter).second.mMapStoryFramesData.find(frameIndex);
		if (frameIter != (*iter).second.mMapStoryFramesData.end())
		{
			(*frameIter).second.setFlip(nFlip);
		}
		else
		{
			StoryFrameData frameData;
			frameData.setFrameIndex(frameIndex);
			frameData.setFlip(nFlip);

			(*iter).second.mMapStoryFramesData.insert(std::make_pair(frameIndex,frameData));
		}
	}

	return true;
}

bool StroyData::InsertDialogTextIdAtFrame(unsigned int roleIndex,unsigned int frameIndex,std::string textId)
{
	std::map<unsigned int,StoryDialogData>::iterator iter = mMapStroyDialogsData.find(frameIndex);
	if (iter != mMapStroyDialogsData.end())
	{
		CCError("ERROR: StroyData::InsertDialogTextIdAtFrame repeat frame index %d ",frameIndex);
		mMapStroyDialogsData.erase(iter);
	}

	StoryDialogData dialogData;
	dialogData.setFrameIndex(frameIndex);
	dialogData.setRoleIndex(roleIndex);
	dialogData.setTextID(textId);

	mMapStroyDialogsData.insert(std::make_pair(frameIndex,dialogData));

	return true;
}

bool StroyData::SetRoleIdAtIndex(unsigned int roleIndex,unsigned int roleId)
{
	std::map<unsigned int,StoryRoleBasicData>::iterator iter = mMapStoryRolesBasicData.find(roleIndex);
	if (iter == mMapStoryRolesBasicData.end())
	{
		StoryRoleBasicData roleBasicData;
		roleBasicData.setRoleId(roleId);

		mMapStoryRolesBasicData.insert(std::make_pair(roleIndex,roleBasicData));
	}
	else
	{
		(*iter).second.setRoleId(roleId);
	}
	return true;
}

bool StroyData::SetRoleLeftIcon(unsigned int roleIndex,std::string iconName)
{
	std::map<unsigned int,StoryRoleBasicData>::iterator iter = mMapStoryRolesBasicData.find(roleIndex);
	if (iter == mMapStoryRolesBasicData.end())
	{
		StoryRoleBasicData roleBasicData;
		roleBasicData.setRoleLogoIcon(iconName);

		mMapStoryRolesBasicData.insert(std::make_pair(roleIndex,roleBasicData));
	}
	else
	{
		(*iter).second.setRoleLogoIcon(iconName);
	}
	return true;
}