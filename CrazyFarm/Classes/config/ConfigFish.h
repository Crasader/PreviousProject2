#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;

struct Fish {
    int fishId;
    int fishType;   // 0 基础鱼；1 礼品鱼；2 Boss鱼;
    double probability; // [0, 0.5]
    int baseReward;
    // TODO : 等待加入礼品鱼的奖励列表
};


class ConfigFish {
    
public:
	ConfigFish();
	static ConfigFish* getInstance();
    
	bool LoadConfig();
    
	std::map<int, Fish> getFishes();
    Fish getFish(int fishId);

    
private:
	static ConfigFish* _instance;
	
    std::map<int, Fish> fishes;
};

