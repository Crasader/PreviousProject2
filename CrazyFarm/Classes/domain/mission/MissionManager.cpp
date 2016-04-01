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
	
	EventListenerCustom* _listener2 = EventListenerCustom::create("get_mission_info", [=](EventCustom* event){


			Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("get_mission_info");
			MissionListValue*value = static_cast<MissionListValue*>(event->getUserData());
			if (value->_errorcode==0)
			{
				_missionList = value->MissionItems;
				


				AchieveListItem item;
				item.current_level = 3;
				item.max_level = 3;
				item.current_nums = 50;
				item.require_nums = 150;
				item.isReceive = false;
				item.mission_id = 5;
				item.rewards.push_back(RewardValue(1001, 1000));
				item.task_content = "test achievel 1";
				item.tast_content_url_pic = "CrazyFarm_achieve_content_1.png";
				item.tast_icon_url_pic = "CrazyFarm_achieve_icon_1.png";
				_achieveList.push_back(item);

				
				item.current_level = 5;
				item.current_nums = 50;
				item.isReceive = false;
				item.max_level = 4;
				item.mission_id = 5;
				item.require_nums = 150;
				item.rewards.at(0) = RewardValue(1002, 1000);
				item.task_content = "test achievel 2";
				item.tast_content_url_pic = "CrazyFarm_achieve_content_2.png";
				item.tast_icon_url_pic = "CrazyFarm_achieve_icon_2.png";
				_achieveList.push_back(item);
			
				item.current_level = 2;
				item.current_nums = 0;
				item.isReceive = false;
				item.max_level = 2;
				item.mission_id = 5;
				item.require_nums = 150;
				item.rewards.at(0) = RewardValue(1001, 1000);
				item.task_content = "test achievel 3";
				item.tast_content_url_pic = "CrazyFarm_achieve_content_3.png";
				item.tast_icon_url_pic = "CrazyFarm_achieve_icon_3.png";
				_achieveList.push_back(item);

				item.current_level = 1;
				item.current_nums = 50;
				item.isReceive = false;
				item.max_level = 3;
				item.mission_id = 5;
				item.require_nums = 50;
				item.rewards.at(0) = RewardValue(1004, 1000);
				item.task_content = "test achievel 4";
				item.tast_content_url_pic = "CrazyFarm_achieve_content_4.png";
				item.tast_icon_url_pic = "CrazyFarm_achieve_icon_4.png";
				_achieveList.push_back(item);









			}
			delete value;
			

		
	});

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listener2, 1);
	HttpMannger::getInstance()->HttpToPostRequestGetMissionList();
	
}

