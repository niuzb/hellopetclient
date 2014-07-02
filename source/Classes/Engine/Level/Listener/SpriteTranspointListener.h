
#ifndef SPRITE_TRANSPOINT_LISTENER_H
#define SPRITE_TRANSPOINT_LISTENER_H

#include "BaseListener.h"



class SpriteTranspointListener : public BaseListener
{

public:

	SpriteTranspointListener();
	virtual ~SpriteTranspointListener();

	static SpriteTranspointListener*	sShareInstance();


public:

	virtual void					HandleObjectTouchEvent(SpriteBase* obj, cocos2d::CCPoint pt);
	void							HandleLockedEvent(SpriteBase* obj);
	void							HandleTransformEvent(SpriteBase* obj);
	void							HandleLayerActiveEvent(cocos2d::CCNode* obj, sActiveLevelConfig* data);
private:
	static SpriteTranspointListener*	sInstance;

};





#endif