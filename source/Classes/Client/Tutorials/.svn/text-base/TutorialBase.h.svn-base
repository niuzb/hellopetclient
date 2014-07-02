#pragma once

#include "TutorialsDataCenter.h"
#include "cocos2d.h"

class TutorialBase:public CCObject
{
public:
	TutorialBase();
	TutorialBase(unsigned int id);
	virtual ~TutorialBase();

	virtual void Start() = 0;
	virtual void End() = 0;
protected:
	ETutorialType m_eTutorialType;
	unsigned int m_nTutorialID;	
private:
};