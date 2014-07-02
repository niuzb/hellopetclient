//
//  FloatHint.h
//  iSeer
//
//  Created by wuwei on 3/31/12.
//  Copyright (c) 2012 Taomee.Inc. All rights reserved.
//
//  FloatHint: this class generates word hints on the screen for kinds of events, e.g. finishing a quest, get something

#ifndef iSeer_FloatHint_h
#define iSeer_FloatHint_h

#include "cocos2d.h"

enum eHintType
{
    HINT_GET_ITEM,
    HINT_GET_SPRITE,
    HINT_ACCEPT_QUEST,
    HINT_FINISH_QUEST,
    HINT_SUBMIT_QUEST,
    HINT_SPRITE_TO_BAG,
    HINT_SPRITE_TO_STORAGE,
    HINT_EXTEND_STORAGE,
    HINT_MINE_RECYCLING,
};

class FloatHintBkg;

class FloatHint : public cocos2d::CCNode
{
public:
    FloatHint();
    virtual ~FloatHint();
    
    static FloatHint* sharedInstance();
    static void purgeInstance();
    
    // push a hint
    void pushHint(int type, const char* key = NULL, int count = 0);
    void pushHint_getItem(int type, const char* key = NULL, int count = 0);
    void pushHint_quest(int type, const char* key = NULL);
    void pushHint_getSprite(int type, const char* key = NULL);
    void pushHint_extendStorage();
    
    void setLabels(const char* strPre, const char* strKey, const char* strPost);
    
    void fadeIn(cocos2d::CCNode* pNode);
    void fadeOut(cocos2d::CCNode* pNode);
    void hintEnd(cocos2d::CCNode* pNode);
    
private:
    static FloatHint* pSharedInstance;

    float m_maxWidth;
    FloatHintBkg* m_pHintBkg;
    std::vector<cocos2d::CCNode*>   m_hintNodes;
};

class FloatHintBkg : public cocos2d::CCNode
{
public:
    FloatHintBkg():m_width(0),m_height(0) {}
    
    inline void setWidth(float w)   { m_width = w; }
    inline void setHeight(float h)  { m_height = h; }
    inline void setLeftTop(cocos2d::CCPoint p) { m_leftTop = p; }
    
    // override draw
    virtual void draw();
    
private:
    float   m_width;
    float   m_height;
    cocos2d::CCPoint m_leftTop;
};

#endif
