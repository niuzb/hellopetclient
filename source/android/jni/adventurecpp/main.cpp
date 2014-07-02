#include "AppDelegate.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>

#include "stdlib.h"
#include "HelloWorldScene.h"
#include "UserData.h"
#include "XLogicManager.h"
#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

extern "C"
{

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JniHelper::setJavaVM(vm);

    return JNI_VERSION_1_4;
}

void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h)
{
    if (!CCDirector::sharedDirector()->getOpenGLView())
    {
        CCEGLView *view = CCEGLView::sharedOpenGLView();
        view->setFrameSize(w, h);

        AppDelegate *pAppDelegate = new AppDelegate();
        CCApplication::sharedApplication()->run();
    }
	else
    {
        ccDrawInit();
        ccGLInvalidateStateCache();
        
        CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
        CCTextureCache::reloadAllTextures();
        CCNotificationCenter::sharedNotificationCenter()->postNotification(EVNET_COME_TO_FOREGROUND, NULL);
        CCDirector::sharedDirector()->setGLDefaultValues(); 
    }
}

void Java_com_taomee_adventure_adventure_loginSuccess(JNIEnv*  env, jobject thiz,jstring session,jstring uuid)
{
	UserData::Create();

	USERINFO mUserData = UserData::GetUserInfo();
    const char *uuidChar = env->GetStringUTFChars(uuid, NULL);
	mUserData.id = atoi(uuidChar);
	env->ReleaseStringUTFChars(uuid, uuidChar);

	const char *sessionChar = env->GetStringUTFChars(session, NULL);
	strcpy(mUserData.userSession,sessionChar);
	env->ReleaseStringUTFChars(session, sessionChar);

	UserData::SetUserInfo(mUserData);

	XLogicManager::sharedManager()->connectToServer();
}



}
