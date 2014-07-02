#pragma once

#include "cocos2d.h"
#include "UIButton.h"
#include "UILayout.h"
#include "UIPicture.h"
#include "TXGUIHeader.h"
#include "StoryData.h"

using namespace std;
using namespace cocos2d;

class InstanceDialogLayer : public CCLayer
{    
public:
	InstanceDialogLayer();
	virtual ~InstanceDialogLayer();

	CREATE_FUNC(InstanceDialogLayer);
	virtual bool init();

	void skipDialogEvent(CCObject* pObj);
	void setStoryDialogData(StoryDialogData data);
public:
	virtual void setTouchEnabled(bool value);
	void ShowPanel();
	void ClearPanel();
protected:
	TXGUI::UILayout* m_pLayer;
	TXGUI::UILabel*  m_pContentLabel;
	TXGUI::UIPicture* m_leftHeroLogoPic;
	StoryDialogData mStoryDialogData;
};