#pragma once

#include "map"
#include "string"
#include "cocos2d.h"

USING_NS_CC;

enum ETutorialType
{
	kTutorialUI = 1,
	kTutorialUnKnow
};

typedef struct OneTutorialData
{
	OneTutorialData(){
		nId = 0;
		nType = 0;
		nNextId = 0;
		nTipType = 0;
		isExpansionMainMenu = false;
	}
	unsigned int nId;		// 编号
	unsigned int nType;
	unsigned int nNextId;
	std::string szUiLayoutName;
	std::string szControlType;
	std::string szControlName;
	unsigned int nTipType;
	std::string szControlContent;
	CCPoint relativePoint;
	bool isExpansionMainMenu;

}ONETUTORIALDATA;

class TutorialDataCenter
{
public:
	TutorialDataCenter();
	~TutorialDataCenter();

	void InitXMLData();
	
	/**
	* Instruction : 获取教程类型
	* @param 
	*/	
	unsigned int GetOneTutorialType(unsigned int id);
private:
	bool mIsLoadData;
	std::map<unsigned int ,OneTutorialData> mIdAndTutorialData;
};