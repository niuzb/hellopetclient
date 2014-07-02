#include "CBone.h"
#include <math.h>
#include "CConnectionData.h"
#include "DressUpManager.h"


CCBone* CCBone::create(bool _isRadian /* = false */,CCArmature *pArmature /* = NULL */)
{
	CCBone *pBone = new CCBone();
	if (pBone && pBone->init(_isRadian,pArmature))
	{
		pBone->autorelease();
		return pBone;
	}
	CC_SAFE_DELETE(pBone);
	return NULL;

}

void CCBone::recycle(CCBone* _bone) {
	//sPoolIndex--;
}

void CCBone::removePoolObject(){
	//if( sObjectPool ){
	//	sObjectPool->removeAllObjects();
	//	CC_SAFE_DELETE( sObjectPool );
	//}
}


CCBone::CCBone() 
	: 	mDisplay(NULL),
	mNode(NULL)
{
	reset();
	mNode = NULL;
	mTweenNode = NULL;
	mName = NULL;
	mIsFrames = false;
	mAttachTweenNode = NULL;
	mDependArmature = NULL;
}



CCBone::~CCBone(void){
	CC_SAFE_DELETE( mNode );
	CC_SAFE_DELETE( mTweenNode );	
}


bool CCBone::init(bool _isRadian,CCArmature *pArmature)
{
	bool bRet = false;
	do{
		mIsRadian	= _isRadian;
		mDependArmature = pArmature;

		if( !mNode ){
			mNode		= new CCBaseNode();
		}
		if( !mTweenNode ){
			mTweenNode	= new CCTweenNode();
		}

		bRet		= true;
	} while (0);

	return bRet;
}


void CCBone::remove() {
	reset();
	CCBone::recycle(this);
}


void CCBone::reset(){
	mIsRadian	= false;
	mTransformX	= 0;
	mTransformY	= 0;
	mTransformSkewX = 0;
	mTransformSkewY = 0;
	mTransformRotation = 0;
	mParentX	= 0;
	mParentY	= 0;
	mParentR	= 0;
	mLockX		= 0;
	mLockY		= 0;
	mLockR		= 0;

	mDisplay		= NULL;
	mParent		= NULL;

	if (mNode != 0)
	{
		mNode->reset();
	}
	/*CC_SAFE_DELETE(mNode);
	CC_SAFE_DELETE(mTweenNode);*/
}

bool CCBone::isBoneFrames()
{
	if (0 != mName && "" != mName)
	{
		int length = strlen(mName);
		char keyChar = '~';
		if (keyChar == mName[length-1])
		{
			setIsFrames(true);
			if( mTweenNode )
			{
				mTweenNode->setIsFrames(true);
			}
			return true;
		}
		else
		{
			setIsFrames(false);
			if( mTweenNode )
			{
				mTweenNode->setIsFrames(false);
			}
		}
	}

	return false;
}

void CCBone::addBoneChild(CCBone* _child){
	_child->mParent = this;
}

void CCBone::setLockPosition(float _x, float _y, float _skewX, float _skewY) {
	mLockX = _x;
	mLockY = _y;
	mLockSkewX = _skewX;
	mLockSkewY = _skewY;
}

void CCBone::update( float dt ) {
	if( !mTweenNode->active || !mTweenNode->visible){
		if(mDisplay && mDisplay->isVisible()){
			mDisplay->setVisible(false);
		}
		return;
	}else{
		if( mDisplay && !mDisplay->isVisible()){
			mDisplay->setVisible(true);
		}
	}

	mTransformX = mNode->x + mLockX + mTweenNode->x;
	mTransformY = mNode->y + mLockY + mTweenNode->y;
	mTransformRotation = mNode->rotation + mTweenNode->rotation;
	mTransformSkewX = mNode->skewX + mLockSkewX + mTweenNode->skewX + mTransformRotation;
	mTransformSkewY = mNode->skewY + mLockSkewY + mTweenNode->skewY - mTransformRotation;

	//CCXLOG("%s, %f, %f", mName, mTransformX, mTransformY);
	if (mParent) {
		mParentX = mParent->getGlobalX();
		mParentY = mParent->getGlobalY();
		mParentR = mParent->getGlobalR();
		mParentSkewX = mParent->getGlobalSkewX();
		mParentSkewY = mParent->getGlobalSkewY();


		//atan2f(-_dY, _dX) 与 atan2f(_dY, _dX) 产生不一样的结果
		float _r = atan2f(-mTransformY, mTransformX) + (mParentSkewX + mParentR) * ANGLE_TO_RADIAN;
		_r = -_r;
		//CCXLOG("%s: %f, %f, %f, %f", name.c_str(), _dY, _dX, mParentR, _r);
		float _len = sqrt(mTransformX * mTransformX + mTransformY * mTransformY);
		mTransformX = _len * cos(_r) + mParentX;
		mTransformY = _len * sin(_r) + mParentY;

		//mTransformRotation += mParentR; 

		mTransformSkewX = mTransformSkewX + mParentSkewX + mParentR;
		mTransformSkewY = mTransformSkewY + mParentSkewY - mParentR;
		//CCXLOG("%s, %f, %f, %f, %f", mName, mTransformX , mParentX, mTransformY , mParentY);
	}

	updateDisplay();

}

void CCBone::updateDisplay(){
	if (mDisplay) {
		

		float _ckx = cos( CC_DEGREES_TO_RADIANS(mTransformSkewX)); 
		float _cky = cos( CC_DEGREES_TO_RADIANS(mTransformSkewY));
		float _skx = sin( CC_DEGREES_TO_RADIANS(mTransformSkewX)); 
		float _sky = sin( CC_DEGREES_TO_RADIANS(mTransformSkewY));

		ccColor3B color = ((CCSprite*)mDisplay)->getColor();
		GLubyte var = ((CCSprite*)mDisplay)->getOpacity();

		if( mTweenNode->getIsImageChange() && mTweenNode->img.compare("") != 0 )
		{			
			// Note: 得到需要显示的装备
			std::string ImageName = mTweenNode->img;
			//if (std::string::npos != ImageName.find("wuqi_"))
			//{
			//	ImageName = "swordsman_common_move:wuqi_80.pvr.ccz";
			//	CCLOG("");
			//}

			std::string tmpImageName = "";
			if (DressUpManager::Get()->GetAdaptedImageName(mTweenNode->img,mDependArmature->GetEquipItemData(),tmpImageName))
			{
				ImageName = tmpImageName;
			}

			CCSprite *_newSprite = CCSprite::createWithSpriteFrameName(ImageName.c_str());
			_newSprite->setAnchorPoint(CCConnectionData::sharedConnectionData()->getOneImageAnchorPoint(mTweenNode->img));

			mDisplay->getParent()->addChild(_newSprite,mTweenNode->z);
			mDisplay->removeFromParentAndCleanup(true);
			
			mDisplay = _newSprite;
		}
		else
		{
			mDisplay->setZOrder(mTweenNode->z);
		}

		mDisplay->setPositionX	( mTransformX );
		mDisplay->setPositionY	( mTransformY );
		mDisplay->setScaleX		( mTweenNode->scaleX * _cky );
		mDisplay->setScaleY		( mTweenNode->scaleY * _ckx );
		mDisplay->setSkewX		( CC_RADIANS_TO_DEGREES(atanf(mTweenNode->scaleY * _skx / mDisplay->getScaleX())) );
		mDisplay->setSkewY		( CC_RADIANS_TO_DEGREES(atanf(mTweenNode->scaleX * _sky / mDisplay->getScaleY())) );
	
		

		if( static_cast<CCSprite*>(mDisplay) ){
			( (CCSprite*)mDisplay )->setColor( color );
			( (CCSprite*)mDisplay )->setOpacity( var );
		}		
	}

	//CCLOG("%s: x:%f, y:%f, scaleX:%f, scaleY:%f, alpha:%d", name.c_str(), mDisplay->getPositionX(), mDisplay->getPositionY(), mDisplay->getScaleX(), mDisplay->getScaleY(), mDisplay->getOpacity());
}

float CCBone::getGlobalX() {
	return mTransformX;
}

float CCBone::getGlobalY() {
	return mTransformY;
}

float CCBone::getGlobalR(){
	return mTransformRotation;
}

float CCBone::getGlobalSkewX(){
	return mTransformSkewX;
}

float CCBone::getGlobalSkewY(){
	return mTransformSkewY;
}