#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;

struct Reward {
    int itemId;
    int num;
};

struct Turrent {
    int turrentId;
    std::string showLevel;
    int unlockType;
    int unlockPrice;
    int multiple;
    std::vector<Reward> rewardList;
};


class ConfigTurrent {
    
public:
	ConfigTurrent();
	static ConfigTurrent* getInstance();
    
	bool LoadConfig();
    
	std::map<int, Turrent> getTurrent();
    Turrent getTurrent(int turrentId);

    
private:
	static ConfigTurrent* _instance;
	
    std::map<int, Turrent> turrents;
};

