#include "GlobalSchedule.h"  
#include "domain/logevent/LogEventMannger.h"
#include "data/GameData.h"
//GlobalSchedule* GlobalSchedule::m_pSchedule = NULL;  
   
GlobalSchedule::GlobalSchedule() {  

} 
GlobalSchedule::~GlobalSchedule()
{}


GlobalSchedule* GlobalSchedule::getInstance(){
	//if (m_pSchedule == NULL){
	//	m_pSchedule = new GlobalSchedule();
	//}
	//return m_pSchedule;
	return nullptr;
}

bool GlobalSchedule::init()
{
	this->schedule(schedule_selector(GlobalSchedule::updataByMin), 1.0f);
	scheduleUpdate();
	return true;
}
void GlobalSchedule::onEnter()
{
	
	/*_running = true;*/
}
void GlobalSchedule::update(float delta)
{
	CCLOG("UPDATA TIME");
}
void GlobalSchedule::updataByMin(float dt)
{
	if (GameData::getInstance()->getisOnGameScene())
	{
		addGameTime(dt);
	}
	else
	{
		addRoomTime(dt);
	}


	if (getGameTime()+getRoomTime()>30)
	{
		LogEventMannger::getInstance()->sendMsg();
	}
}

void GlobalSchedule::addGameTime(float dt)
{
	UserDefault::getInstance()->setFloatForKey(SCHEDULE_GAMETIME, UserDefault::getInstance()->getFloatForKey(SCHEDULE_GAMETIME, 0) + dt);
}

void GlobalSchedule::addRoomTime(float dt)
{
	UserDefault::getInstance()->setFloatForKey(SCHEDULE_ROOMTIME, UserDefault::getInstance()->getFloatForKey(SCHEDULE_ROOMTIME, 0) + dt);
}

float GlobalSchedule::getGameTime()
{
	return UserDefault::getInstance()->getFloatForKey(SCHEDULE_GAMETIME);
}
float GlobalSchedule::getRoomTime()
{
	return UserDefault::getInstance()->getFloatForKey(SCHEDULE_ROOMTIME);
}