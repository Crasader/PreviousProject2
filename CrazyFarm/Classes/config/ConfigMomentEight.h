#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;


struct MomentEightItemFishs {
	std::vector<int> fish_ids;
	float  fish_wait_time_start;
	float  fish_wait_time_end;
	int fish_startcount;
	int fish_endcount;
	float wait_time; //�����ĵȴ�ʱ��
	int fishRoute = -1; ///-1�������
};


struct MomentEightItem {
	float fTempTime; ///////////////�������ʱ�� ����start��end����
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
	float lifetime;//ֻ��json1�ж�ȡ

	std::map<int, std::vector<MomentEightItem>> momentEightItemTypes;
	bool LoadConfigByType(int type);

};

