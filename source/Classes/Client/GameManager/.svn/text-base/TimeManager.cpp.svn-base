#include "OnlineNetworkManager.h"
#include "TimeManager.h"
#include "CCLuaEngine.h"
#include <time.h>

TimeManager::TimeManager()
	:serverMinusLocalTime(0)
    ,latestLocalTime(0)
	,initFlag(false)
{
	CCScheduler * pSchedule = CCDirector::sharedDirector()->getScheduler();
        pSchedule->scheduleSelector(schedule_selector(TimeManager::update), 
                                                         this, 
                                                         0,
                                                         false);
}

TimeManager::~TimeManager()
{
	CCScheduler * pSchedule = CCDirector::sharedDirector()->getScheduler();
		pSchedule->unscheduleSelector(schedule_selector(TimeManager::update), 
			this);
}

void TimeManager::syncServerTime(unsigned int serTime, unsigned int serUTime)
{
	//误差超过10s断开连接，防止修改本地时间
	if (abs((long)serTime - getCurServerTime()) > 10 && initFlag)
	{
		OnlineNetworkManager::sShareInstance()->LostConnection2Server();
		initFlag = false;
		return;
	}
	this->serverMinusLocalTime = serTime - latestLocalTime;
	initFlag = true;
}

long TimeManager::getCurServerTime()
{
	long simuServerTime = latestLocalTime + serverMinusLocalTime;
	return simuServerTime;
}

string TimeManager::secondsToString(long seconds)
{
    string result = "00:00";
    
    if (seconds <= 0) {
        return result;
    }
    char resStr[6];
    long min, sec;
    min = sec = 0;
    
    min = seconds / 60;
    sec = seconds % 60;
    
    sprintf(resStr, "%02ld:%02ld", min, sec);
    
    result = string(resStr);
    
    return result;
}

//C++
bool TimeManager::registerTimer(TimeProtocol * observer, int counterId, long endTime)
{
	bool ret = false;
	if (observer == NULL)
            return ret;
        
    if (timeObMap.end() == timeObMap.find(counterId)
		&& timeObMap[counterId].end() == timeObMap[counterId].find(observer)) 
	{
        TimeObSet timeObSet;
        timeObMap[counterId] = timeObSet;
		timeObMap[counterId].insert(observer);
		counterMap[counterId] = endTime - getCurServerTime();
		ret = true;
    }  
    CCAssert(ret, "TimeManager:registerTimer failed");
	return ret;
}

//C++
bool TimeManager::unregisterTimer(TimeProtocol * observer, int counterId)
{
	bool ret = false;
	if (observer == NULL || timeObMap.end() == timeObMap.find(counterId)) 
        return ret;
    
	if (timeObMap[counterId].find(observer) != timeObMap[counterId].end())
	{
		timeObMap[counterId].erase(observer);
		//无人监听后删除timer
		if (timeObMap[counterId].size() == 0)
		{
			timeObMap.erase(counterId);
			counterMap.erase(counterId);
		}
		ret = true;
	}
	CCAssert(ret, "TimeManager:unregisterTimer failed");
	return ret;
}

//C++
bool TimeManager::attachTimer(TimeProtocol * observer, int counterId)
{
	bool ret = false;
	if (counterMap.end() == counterMap.find(counterId)
		|| timeObMap.end() == timeObMap.find(counterId))
	{
		CCAssert(0, "TimeManager: can't find timer");
	}
	else if (timeObMap[counterId].end() != timeObMap[counterId].find(observer))
	{
		CCAssert(0, "TimeManager: already attached Timer");
	}
	else
	{
		timeObMap[counterId].insert(observer);
		ret = true;
	}
	CCAssert(ret, "TimeManager:attachTimer failed");
	return ret;
}

//Lua
bool TimeManager::registerLuaTimer(int handler, int counterId, long endTime)
{
	bool ret = false;
	if (handler == NULL)
            return ret;
        
    if (luaObMap.end() == luaObMap.find(counterId)
		&& luaObMap[counterId].end() == luaObMap[counterId].find(handler)) 
	{
        LuaObSet luaObSet;
        luaObMap[counterId] = luaObSet;
		luaObMap[counterId].insert(handler);
		counterMap[counterId] = endTime - getCurServerTime();
		ret = true;
    }  
    CCAssert(ret, "TimeManager:registerLuaTimer failed");
	return ret;
}

//Lua
bool TimeManager::unregisterLuaTimer(int handler, int counterId)
{
	bool ret = false;
	if (handler == NULL || luaObMap.end() == luaObMap.find(counterId)) 
        return ret;
    
	if (luaObMap[counterId].find(handler) != luaObMap[counterId].end())
	{
		luaObMap[counterId].erase(handler);
		CCLuaEngine::defaultEngine()->removeScriptHandler(handler);
		//无人监听后删除timer
		if (luaObMap[counterId].size() == 0)
		{
			luaObMap.erase(counterId);
			counterMap.erase(counterId);
		}
		ret = true;
	}
	CCAssert(ret, "TimeManager:unregisterLuaTimer failed");
	return ret;
}

//Lua
bool TimeManager::attachLuaTimer(int handler, int counterId)
{
	bool ret = false;
	if (counterMap.end() == counterMap.find(counterId)
		|| luaObMap.end() == luaObMap.find(counterId))
	{
		CCAssert(0, "TimeManager: can't find lua timer");
	}
	else if (luaObMap[counterId].end() != luaObMap[counterId].find(handler))
	{
		CCAssert(0, "TimeManager: already attached lua Timer");
	}
	else
	{
		luaObMap[counterId].insert(handler);
		ret = true;
	}
	CCAssert(ret, "TimeManager:attachLuaTimer failed");
	return ret;
}

//通用
bool TimeManager::startTimer(int counterId, long endTime)
{
	bool ret = false;
	if (counterMap.end() == counterMap.find(counterId))
	{
		counterMap[counterId] = endTime - getCurServerTime();
		ret = true;
	}
	CCAssert(ret, "TimeManager:startTimer failed");
	return ret;
}

//通用
bool TimeManager::stopTimer(int counterId)
{
	bool ret = false;
	if (counterMap.end() != counterMap.find(counterId))
	{
		counterMap.erase(counterId);
		timeObMap.erase(counterId);		
		//停止?模仿下面写		
		//for(ObserverHandlers::iterator it = m_scriptHandler.begin();
		//	it != m_scriptHandler.end();++it)
		//{
		//	if(*it)
		//	{
		//		CCLuaEngine::defaultEngine()->removeScriptHandler(*it);
		//	}
		//}
		//m_scriptHandler.clear();
		luaObMap.erase(counterId);
		ret = true;
	}
	//CCAssert(ret, "TimeManager:stopTimer failed");
	return ret;
}

//通用
bool TimeManager::renewTimer(int counterId, long endTime)
{
	bool ret = false;
	if (counterMap.end() != counterMap.find(counterId))
	{
		counterMap[counterId] = endTime - getCurServerTime();
		ret = true;
	}
	CCAssert(ret, "TimeManager:renewTimer failed");
	return ret;
}

//通用
bool TimeManager::hasTimer(int counterId)
{
	bool ret = false;
	if (counterMap.end() != counterMap.find(counterId))
	{		
		ret = true;
	}
	return ret;
}

//C++
bool TimeManager::hasObserver(TimeProtocol * observer, int counterId)
{
	bool ret = false;
	if (hasTimer(counterId) && timeObMap[counterId].end() != timeObMap[counterId].find(observer))
	{
		ret = true;
	}
	return ret;
}

//Lua
bool TimeManager::hasLuaObserver(int handler, int counterId)
{
	bool ret = false;
	if (hasTimer(counterId) && luaObMap[counterId].end() != luaObMap[counterId].find(handler))
	{
		ret = true;
	}
	return ret;
}

void TimeManager::update(float dt)
{
	time_t nowTime;
	time(&nowTime);
	if (nowTime > latestLocalTime)
	{
		long delta = nowTime - latestLocalTime;
		latestLocalTime = nowTime;

		//更新计时数据
		for (CounterMap::iterator iter = counterMap.begin();iter != counterMap.end(); ++iter) {
			(*iter).second -= delta;
		}

		updateObservers(delta);
		updateLuaObservers(delta);
	}
}

void TimeManager::updateObservers(long delta)
{
	vector<int> finishedTimer;
	for (TimeObMap::iterator iter = timeObMap.begin();iter != timeObMap.end(); ++iter) {
        int counterId = (*iter).first;
		if (counterMap.find(counterId) != counterMap.end())
		{
			CounterMap::iterator counterIter = counterMap.find(counterId);
			long remainTime = (*counterIter).second;

			//更新每个observer
			TimeObSet obSet = (*iter).second;
			TimeObSet::iterator obSetIter = obSet.begin();
			for (TimeObSet::iterator obSetIter = obSet.begin(); obSetIter != obSet.end(); obSetIter++)
			{
				if(NULL != *obSetIter)
				{
					(*obSetIter)->onUpdateRemainTime(remainTime >= 0 ? remainTime : 0);
				}
			}

			//倒计时已为负值，加入删除vector，不能直接删除
			if (remainTime < 0)
			{
				finishedTimer.push_back(counterId);
			}
		}
    }

	//清除已结束的timer
	for (size_t i = 0; i < finishedTimer.size(); i++)
	{
		counterMap.erase(finishedTimer[i]);
		timeObMap.erase(finishedTimer[i]);
	}
}

void TimeManager::updateLuaObservers(long delta)
{
	vector<int> finishedTimer;
	for (LuaObMap::iterator iter = luaObMap.begin();iter != luaObMap.end(); ++iter) {
        int counterId = (*iter).first;
		if (counterMap.find(counterId) != counterMap.end())
		{
			CounterMap::iterator counterIter = counterMap.find(counterId);
			long remainTime = (*counterIter).second;

			//更新每个observer
			LuaObSet obSet = (*iter).second;
			LuaObSet::iterator obSetIter = obSet.begin();
			for (LuaObSet::iterator obSetIter = obSet.begin(); obSetIter != obSet.end(); obSetIter++)
			{
				if(NULL != *obSetIter)
				{
					CCLuaEngine* engine = CCLuaEngine::defaultEngine();
					engine->cleanStack();
					engine->pushInt(remainTime >= 0 ? remainTime : 0);
					engine->executeFunctionByHandler(*obSetIter,1);
				}
			}

			//倒计时已为负值，加入删除vector，不能直接删除
			if (remainTime < 0)
			{
				finishedTimer.push_back(counterId);
			}
		}
    }

	//清除已结束的timer
	for (size_t i = 0; i < finishedTimer.size(); i++)
	{
		counterMap.erase(finishedTimer[i]);
		luaObMap.erase(finishedTimer[i]);
	}
}

void TimeManager::ResetData()
{
	serverMinusLocalTime = 0;

	latestLocalTime = 0;

	//是否同步过系统时间
	initFlag = false;

	timeObMap.clear();	
	luaObMap.clear();

	counterMap.clear();
}