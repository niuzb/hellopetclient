#ifndef RU_FORWARD_DECLARATION_H_
#define RU_FORWARD_DECLARATION_H_

#include "../base/TimerEvent.hpp"
#include "../base/Singleton.hpp"

class MsgHandlerMgr;  // 消息处理函数管理器
class BattleField;    // 战场地图


class Globle: public Singleton<Globle>
{
    public:
    Globle(){
	}
	base::TimerManager Timer;
};

#define sGloble Globle::get_singleton()

#endif // RU_FORWARD_DECLARATION_H_
