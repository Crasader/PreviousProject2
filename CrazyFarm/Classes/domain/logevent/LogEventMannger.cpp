#include "LogEventMannger.h"


LogEventMannger* LogEventMannger::_instance = NULL;

LogEventMannger::LogEventMannger(){
    
}

void LogEventMannger::init(){

}

LogEventMannger* LogEventMannger::getInstance(){
    if(_instance == NULL){
		_instance = new LogEventMannger();
    }
    return _instance;
}
void LogEventMannger::sendMsg()
{
	CCLOG("send logevnt msg");
	LogEventFish::getInstance()->sendDataToServer();
	LogEventMagnate::getInstance()->sendDataToServer();
	LogEventUseSkill::getInstance()->sendDataToServer();
	LogEventPageChange::getInstance()->sendDataToServer();
	LogEventSpcEvent::getInstance()->sendDataToServer();
}
void LogEventMannger::clearData(int type)
{
	switch (type)
	{
	case 1:
		LogEventFish::getInstance()->clearLocalData();
		break;
	case 3:
		LogEventMagnate::getInstance()->clearLocalData();
		break;
	case 5:
		LogEventUseSkill::getInstance()->clearLocalData();
		break;
	case 6:
		LogEventPageChange::getInstance()->clearLocalData();
		break;
	case 7:
		LogEventSpcEvent::getInstance()->clearLocalData();
		break;
	case 8:
	case 2:
	case 4:
	default:
		break;
	}
}