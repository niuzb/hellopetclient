#ifndef INSTANCELIST_LAYER_H
#define INSTANCELIST_LAYER_H

#include "ASprite.h"
#include "UILayout.h"

using namespace std;
using namespace cocos2d;

typedef struct InstanceInfo
{
	unsigned int id;
	bool active;
	unsigned int star;
}InstanceInfo;

typedef struct ScrollPagePosition
{
	int index;
	int page;
	int row;
	int col;
}ScrollPagePosition;

class InstanceListLayer : public cocos2d::CCLayer
{
public:
	InstanceListLayer();
	virtual ~InstanceListLayer();

	CREATE_FUNC(InstanceListLayer);
	virtual bool init();

	//打开关闭副本列表
	void openInstanceList();
	void closeInstanceList(CCObject* sender);
	void setInstanceId(unsigned int id){taskInstanceId = id;}

	//界面生成
	void refreshInstanceListLayer();
	void addInstancesFromList(const std::vector<InstanceInfo>& instanceList);
	void addSigleInstance(InstanceInfo info, ScrollPagePosition position);
	void removeSigleInstance(ScrollPagePosition position);

	//按键响应
	void onPressInstanceBtn(CCObject *pObject);

    void OnAutoOnHook(CCObject* sender);
    void OnFight(CCObject* sender);
    void Fight(int id);
    
	//消息处理
	void onEventMsgInstanceList(const std::vector<InstanceInfo>& instanceInfos);

	//辅助计算函数
	ScrollPagePosition getScrollPagePos(int index);
	CCPoint scrollPosToPoint(ScrollPagePosition position);

	virtual void closeLayerCallBack(void);
private:
	ASprite*    m_curUiAs;
	TXGUI::UILayout *instanceListLayout;	
	unsigned int taskInstanceId;
    int m_FuBenId;
};

#endif