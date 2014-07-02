#pragma once

#include "ASprite.h"
#include "UILayout.h"

using namespace std;
using namespace cocos2d;

typedef struct CityInfo{
	int cityId;
	CCPoint cityPos;
	CCPoint namePos;
	CCPoint playerPos;
}CityInfo;

class CityListLayer : public CCLayer
{
public:
	CityListLayer();
	virtual ~CityListLayer();

	CREATE_FUNC(CityListLayer);
	virtual bool init();

	void openCityList();
	void closeCityList(CCObject* sender);

	void addCityBtn(int index);
	void onPressCityBtn(CCObject* sender);

	void moveToCity(int cityId, float delayTime);
	void enterTargetCity();

	//¸¨Öúº¯Êý
	void initCityList();

private:
	ASprite*    m_curUiAs;
	TXGUI::UILayout *cityListLayout;
	std::vector<CityInfo> cityInfoList;

	CCSprite * playerImg;

	int curCityId;
	int targetCityId;

	bool playerMoving;
};

