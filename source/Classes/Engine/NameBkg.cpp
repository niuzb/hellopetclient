//
//  NameBkg.cpp
//  iSeer
//
//  Created by wuwei on 7/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "NameBkg.h"
#include "Painter.h"

using namespace cocos2d;

NameBkg::NameBkg(CCPoint pos, float width, float height, ccColor3B color)
:m_pos(pos)
,m_color(color)
,m_width(width)
,m_height(height)
{
    
}

NameBkg::~NameBkg()
{
    
}

NameBkg* NameBkg::bkgWithParams(CCPoint pos, float width, float height, ccColor3B color)
{
    NameBkg* pBkg = new NameBkg(pos, width, height, color);
    if(pBkg)
    {
        pBkg->autorelease();
        return pBkg;
    }
    
    return NULL;
}

void NameBkg::draw()
{
    Painter::drawNameBkg(m_pos, m_width, m_height, m_color);
}