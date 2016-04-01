#pragma once

#include "cocos2d.h"
#include "server/HttpMannger.h"
using namespace cocos2d;





class MissionManager {

public:
	static MissionManager* getInstance();
	void loadConfig();
	std::vector<MissionListItem> getMissionListData(){ return _missionList; };
	std::vector<AchieveListItem> getAchieveListData(){ return _achieveList; };
private:
	MissionManager();
	std::vector<MissionListItem> _missionList;
	std::vector<AchieveListItem> _achieveList;
	static MissionManager* _instance;


    
};

