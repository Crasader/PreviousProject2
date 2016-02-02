#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;


struct  MomentEightItemPer
{
	int fish_id;
	int fish_startcount;
	int fish_endcount;
	int per;
	int fishRoute = -1; ///-1代表随机
};

struct MomentEightItemFishs {
    int fish_id;
	int fish_startcount;
	int fish_endcount;
	float wait_time;
	int fishRoute = -1; ///-1代表随机
};


struct MomentEightItem {
	float fTempTime; ///////////////随机产生时间 根据start和end产生
    double interval_time_start;
	double interval_time_end;	
	std::vector<MomentEightItemFishs> momentEightItemFishs;
};


class ConfigMomentEight {
    
public:
	ConfigMomentEight();
	static ConfigMomentEight* getInstance();
    
	bool LoadConfig();
	std::map<int, std::vector<MomentEightItem>> getMomentEightItemTypes();
	float getLifeTime(){ return lifetime; };
    
private:
	static ConfigMomentEight* _instance;
	float lifetime;//只从json1中读取

	std::map<int, std::vector<MomentEightItem>> momentEightItemTypes;
	bool LoadConfigByType(int type);

};

