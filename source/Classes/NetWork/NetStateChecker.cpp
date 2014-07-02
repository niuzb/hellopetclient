#include "OnlineNetworkManager.h"
#include "NetStateChecker.h"
#include "GameConfigFromLuaManager.h"
#include "cocos2d.h"

USING_NS_CC;
#define ENABLE_CHECK_NETWORK

class OnlineNetworkManager;

static NetStateChecker* _netStateChecker = 0;

NetStateChecker* NetStateChecker::getInstance(void)
{
	if(_netStateChecker == 0)
	{
		_netStateChecker = new NetStateChecker();
	}
	return _netStateChecker;
}

void NetStateChecker::Destroy()
{
	if (_netStateChecker)
	{
		delete _netStateChecker;
		_netStateChecker = NULL;
	}
}

NetStateChecker::~NetStateChecker()
{

}

NetStateChecker::NetStateChecker()
{
	mDeltaTime = 0;
	bStartTesting = true;
	mTimeInMs = GetTimeWithLua();
	bSendContent = false;
}

long NetStateChecker::GetTimeWithLua()
{
	struct cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now,0);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void NetStateChecker::Start()
{
	if (bStartTesting)
	{
		CCDirector::sharedDirector()->getScheduler()->scheduleSelector(SEL_SCHEDULE(&NetStateChecker::update), 
			this, 
			10.0f, 
			false);

		SendRqsToServer();
	}
}

void NetStateChecker::Stop()
{
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(SEL_SCHEDULE(&NetStateChecker::update), this);
}


void NetStateChecker::QuickSendRqsToServer()
{
    OnlineNetworkManager::sShareInstance()->sendReqNetStateMessage();
    bSendContent = true;
    mTimeInMs = GetTimeWithLua();
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(SEL_SCHEDULE(&NetStateChecker::quick_udpate),
                                                                   this,
                                                                   1.0f,
                                                                   false);
    m_fLifeHelloTime = -10.f;
}


void NetStateChecker::SendRqsToServer()
{
	//if(false == bSendContent)
	{
		OnlineNetworkManager::sShareInstance()->sendReqNetStateMessage();
		bSendContent = true;
		mTimeInMs = GetTimeWithLua();
		m_fLifeHelloTime = -10.f;
	}
}

void NetStateChecker::RecieveRqsFromServer()
{	
	long time = GetTimeWithLua();
	mDeltaTime = abs(time - mTimeInMs);
	CCDirector::sharedDirector()->SetNetDelayTime(mDeltaTime);
	bSendContent = false;
    
	m_fLifeHelloTime = 10.f;
}


void NetStateChecker::update(float dt)
{
    checkNetWork();
}

void NetStateChecker::quick_udpate(float dt)
{
    checkNetWork();
}

void NetStateChecker::checkNetWork()
{
#ifdef ENABLE_CHECK_NETWORK
	if (m_fLifeHelloTime < 0)
	{
		//// wrong , missing hello package!
		OnlineNetworkManager::sShareInstance()->LostConnection2Server();
	}
#endif
	SendRqsToServer();
}

void NetStateChecker::stopQuickCheck()
{
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(SEL_SCHEDULE(&NetStateChecker::quick_udpate), this);
}



