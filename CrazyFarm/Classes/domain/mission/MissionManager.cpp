#include "MissionManager.h"
#include "server/HttpClientUtill.h"
#include "utill/FunUtil.h"
#include "domain/user/User.h"
MissionManager* MissionManager::_instance = NULL;

MissionManager::MissionManager(){

}
MissionManager* MissionManager::getInstance(){
    if(_instance == NULL){
		_instance = new MissionManager();
    }
    return _instance;
}
void MissionManager::loadConfig()
{
	
	EventListenerCustom* _listener2 = EventListenerCustom::create("get_mission_info", [=](EventCustom* event1){


			Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("get_mission_info");
			MissionListValue*value = static_cast<MissionListValue*>(event1->getUserData());
			if (value->_errorcode==0)
			{
				_missionList = value->MissionItems;
			}
			delete value;
			

		
	});

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listener2, 1);
	HttpMannger::getInstance()->HttpToPostRequestGetMissionList();



	EventListenerCustom* _listener1 = EventListenerCustom::create("get_achieve_info", [=](EventCustom* event1){


		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("get_achieve_info");
		AchieveListValue*value = static_cast<AchieveListValue*>(event1->getUserData());
		if (value->_errorcode == 0)
		{
			_achieveList = value->AchieveItems;
		}
		delete value;
	});

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listener1, 1);
	HttpMannger::getInstance()->HttpToPostRequestToGetAchieveInfo();
}

