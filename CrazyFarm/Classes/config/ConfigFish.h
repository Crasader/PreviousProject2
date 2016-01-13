#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;

struct FishData {
    int fishId;
    int fishType;   // 0 基础鱼；1 礼品鱼；2 Boss鱼;
    int move_speed; // 移动速度
    double probability; // [0, 0.5]
    int baseReward;
    int maxHitTime;
    int protectedTime;
    int uiId;
    int catch_ui_type;  // 捕获鱼的效果
    int exp;            // 捕获鱼的经验
    int be_hit_logic;   // 受击中反应
};


class ConfigFish {
    
public:
	ConfigFish();
	static ConfigFish* getInstance();
    
	bool LoadConfig();
    
	std::map<int, FishData> getFishes();
	FishData getFish(int fishId);

    
private:
	static ConfigFish* _instance;
	
	std::map<int, FishData> fishes;
};

