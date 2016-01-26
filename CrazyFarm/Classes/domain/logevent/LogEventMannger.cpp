#include "LogEventMannger.h"


LogEventMannger* LogEventMannger::_instance = NULL;

LogEventMannger::LogEventMannger(){
    
}

void LogEventMannger::init(int roomid){
	LogEventFish::getInstance()->init(roomid);
	LogEventMagnate::getInstance()->init();
	LogEventMermaid::getInstance()->init();
	LogEventBankrupt::getInstance()->init(roomid);
	LogEventUseSkill::getInstance()->init();

}

LogEventMannger* LogEventMannger::getInstance(){
    if(_instance == NULL){
		_instance = new LogEventMannger();
    }
    return _instance;
}

