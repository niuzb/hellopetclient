#include "CProcessBase.h"

#define USE_FIX_FRAME_RATES

CCProcessBase::CCProcessBase(void) {
    mScale = 1;
    mIsComplete = true;
    mIsPause = false;
    mCurrentFrame = 0;
	mToFrameID = 0;

#ifdef USE_FIX_FRAME_RATES
	mAnimationInternal = 1.0f / FRAME_RATES;
#else
	mAnimationInternal = CCDirector::sharedDirector()->getAnimationInterval();
#endif	
}


CCProcessBase::~CCProcessBase(void) {
}

void CCProcessBase::resetValue()
{
	mScale = 1;
	mIsComplete = true;
	mIsPause = false;
	mCurrentFrame = 0;
	mToFrameID = 0;
}


void CCProcessBase::remove() {
    mScale = 1;
    mIsComplete = true;
    mIsPause = false;
    mCurrentFrame = 0;
}
void CCProcessBase::pause() {
    mIsPause = true;
}


void CCProcessBase::resume() {
    mIsPause = false;
}

void CCProcessBase::stop() {
    mIsComplete = true;
    mCurrentFrame = 0;
}

void CCProcessBase::playTo(void * _to, int _durationTo, int _durationTween,  bool _loop, int _ease) {
    mIsComplete = false;
    mIsPause = false;
    mCurrentFrame = 0;
    mTotalFrames = 0;
    mEase = _ease;

}

void CCProcessBase::update(float dt) {
    if (mIsComplete || mIsPause) {
        return;
    }
	
    if( mTotalFrames == 0 ) {
        //CCLOG( "mTotalFrames is zero!" );
		mCurrentPrecent = 1;
    }
	else
	{
		mCurrentFrame += 1 * (dt/mAnimationInternal);

		mCurrentPrecent = mCurrentFrame / (mTotalFrames);

		if( mCurrentFrame > mTotalFrames ){
			mCurrentFrame = (int)(mCurrentFrame) % mTotalFrames;
		}
	}
    
    updateHandler();
}

void CCProcessBase::updateHandler() {
}