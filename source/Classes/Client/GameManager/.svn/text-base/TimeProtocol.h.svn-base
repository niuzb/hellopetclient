#pragma once

class TimeProtocol
{
    friend class TimeManager;
public:
    virtual void onUpdateRemainTime(long remainTime) = 0;
};

//计时器编号，与后台协同确定
#define TIMER_INSTANCE_COUNTDOWN 20001
#define TIMER_PVAI_COOLDOWN 20002
#define TIMER_PVAI_REWARD   20003