//
//  TipMgr.h
//  HelloLua
//
//  Created by rickycheng  on 13-5-6.
//
//

#ifndef HelloLua_TipMgr_h
#define HelloLua_TipMgr_h

#include "Singleton_t.h"
#include "cocos2d.h"

class TipMgr : public TSingleton<TipMgr>
{
public:
	TipMgr();
	virtual ~TipMgr();
    
    void createTip(cocos2d::CCSprite* icon, cocos2d::CCPoint pt);
    void add(cocos2d::CCSprite* labelIcon, const char* message, cocos2d::ccColor3B color, int fontsize);
    void add(const char* message,cocos2d::ccColor3B color, int fontsize);
    void addNodeDone();
    void destroyTip();
private:
    void divMessage(const char* message);
    void posNode();
    void computerPt(cocos2d::CCPoint pt);
    
private:
    cocos2d::CCLayerColor* m_pColorLayer;
    cocos2d::CCSprite* m_pIcon;
    cocos2d::CCArray* m_pChildNode;
    cocos2d::CCSprite* m_bkSprite;
    cocos2d::CCPoint m_pt;
    
    int m_childcnt;
    float m_maxWidth;
    float m_maxHeight;
    float m_tapx, m_tapy;
};

#endif
