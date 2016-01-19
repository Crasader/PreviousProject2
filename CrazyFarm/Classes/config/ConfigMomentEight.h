#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;

struct MomentEightItemPer {
    int fish_id;
	int fish_count;
    int per;
};

struct MomentEightItem {
    int life_time;
    double interval_time_start;
    double interval_time_end;
    std::vector<MomentEightItemPer> momentEightItemPers;
};


class ConfigMomentEight {
    
public:
	ConfigMomentEight();
	static ConfigMomentEight* getInstance();
    
	bool LoadConfig();
    MomentEightItem getMomentEightItemByTypeId(int typeId);
    
private:
	static ConfigMomentEight* _instance;
    
    bool LoadConfigType1();
    bool LoadConfigType2();
    bool LoadConfigType3();
	bool LoadConfigType4();
	bool LoadConfigType5();
    
    MomentEightItem momentEightItemType1;
    MomentEightItem momentEightItemType2;
    MomentEightItem momentEightItemType3;
	MomentEightItem momentEightItemType4;
	MomentEightItem momentEightItemType5;
};

