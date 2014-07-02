//
//  MineManger.h
//  iSeer
//
//  Created by august on 12-4-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef iSeer_MineManger_h
#define iSeer_MineManger_h

#include "cocos2d.h"

#define UPDATETIME 43200


class MineManager
{
public:
    static MineManager* shareManager();    

    /*判断是否被采，如mapid对应的信息在存档中有记录，则返回该记录对应的信息（已采true，未采false）*/
    bool isMined(int mapid);
    
    /*修改mapid对应的采矿信息，改为isMined*/
    void setIsMined(int mapid,bool isMined);
    
    /*判断是否可以更新了*/
    bool timeOut();
    
    /*如果已经timeOut，将所有的采矿信息设置成未采*/
    void updateMap();
    
};


#endif
