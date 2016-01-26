#pragma once
#include "cocos2d.h"
#include "server/HttpMannger.h"
#include "LogEventFish.h"
#include "LogEventMagnate.h"
#include "LogEventMermaid.h"
#include "LogEventBankrupt.h"
#include "LogEventUseSkill.h"
using namespace cocos2d;


class LogEventMannger {

public:
	static LogEventMannger* getInstance();
	void init(int roomid);
private:
	LogEventMannger();
    
	static LogEventMannger* _instance;
};


