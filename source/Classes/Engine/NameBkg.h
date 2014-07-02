//
//  NameBkg.h
//  iSeer
//
//  Created by wuwei on 7/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iSeer_NameBkg_h
#define iSeer_NameBkg_h

#include "cocos2d.h"

class NameBkg : public cocos2d::CCNode
{
public:
    NameBkg(cocos2d::CCPoint pos, float width, float height, cocos2d::ccColor3B color);
    virtual ~NameBkg();
    
    virtual void draw();
    
    static NameBkg* bkgWithParams(cocos2d::CCPoint pos, float width, float height, cocos2d::ccColor3B color);
    
private:
    cocos2d::CCPoint    m_pos;
    cocos2d::ccColor3B  m_color;
    float   m_width;
    float   m_height;
};

#endif
