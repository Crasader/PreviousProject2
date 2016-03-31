#pragma once

#include "cocos2d.h"
#include "server/HttpMannger.h"
using namespace cocos2d;





class MissionManager {

public:
	static MissionManager* getInstance();
	void loadConfig();
	std::vector<MissionListItem> getMissionListData(){ return _missionList; };
private:
	MissionManager();
	std::vector<MissionListItem> _missionList;
	static MissionManager* _instance;


    
};

