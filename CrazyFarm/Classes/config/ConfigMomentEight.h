#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;

struct MomentEightItemPer {
    int fish_id;
    int per;
	int fishRoute = -1; ///-1�������
};


struct MomentEightItem {
	float fTempTime; ///////////////�������ʱ�� ����start��end����
    int life_time;
    double interval_time_start;
	double interval_time_end;	
	int fish_startcount;
	int fish_endcount;
    std::vector<MomentEightItemPer> momentEightItemPers;
};


class ConfigMomentEight {
    
public:
	ConfigMomentEight();
	static ConfigMomentEight* getInstance();
    
	bool LoadConfig();
	std::vector<MomentEightItem> getMomentEightItemByTypeId(int typeId);
	float getLifeTime(){ return lifetime; };
    
private:
	static ConfigMomentEight* _instance;
	float lifetime;//ֻ��json1�ж�ȡ
    bool LoadConfigType1();
    bool LoadConfigType2();
    bool LoadConfigType3();
	bool LoadConfigType4();
	bool LoadConfigType5();

	std::vector<MomentEightItem> momentEightItemType1;
	std::vector<MomentEightItem> momentEightItemType2;
	std::vector<MomentEightItem> momentEightItemType3;
	std::vector<MomentEightItem> momentEightItemType4;
	std::vector<MomentEightItem> momentEightItemType5;


};

