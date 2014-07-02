//
//  MineManager.cpp
//  iSeer
//
//  Created by august on 12-4-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "MineManager.h"

#include "FloatHint.h"
#include "GameManager.h"
#include "cocos2d.h"

static MineManager *mineInstance = NULL;

MineManager* MineManager::shareManager()
{
    if(mineInstance == NULL)
    {
        mineInstance = new MineManager();
    }
    return mineInstance;
}

bool MineManager::isMined(int mapid)
{
    //true 表示已经挖了，false表示没有挖
    return false;
}

void MineManager::setIsMined(int mapid, bool isMined)
{
    // to do...

}


bool MineManager::timeOut()
{
    long lastFrefreshTime = 0;
    
    long nowTimes;
    time((time_t*)&nowTimes);
    time_t timeNow = time(NULL);  
    struct tm* p = localtime(&timeNow); 
    if ((nowTimes - lastFrefreshTime) > UPDATETIME) 
    {
        if (p->tm_hour >= 12) //记录12点的秒数
        {
            long seconds = nowTimes - (p->tm_hour - 12)*3600 - (p->tm_min)*60 - p->tm_sec;
            
        }else                //记录0点秒数
        {
            long seconds = nowTimes - (p->tm_hour)*3600 - (p->tm_min)*60 - p->tm_sec;           
        }
        return true;
    }
    return false;
}

void MineManager::updateMap()
{
    if (timeOut()) 
    {
        // refresh the mine

    }
}

