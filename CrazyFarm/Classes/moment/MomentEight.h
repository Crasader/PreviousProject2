#pragma once
#include "cocos2d.h"
#include "moment/Moment.h"
#include "fish/FishManage.h"
#include "config/ConfigMomentEight.h"
using namespace cocos2d;

class MomentEight : public Moment {

public:
	virtual void init();
	virtual bool updata(float dt);
private:
	//MomentEightItemPer getFishByRandVec(std::vector<MomentEightItemPer> momentEightItemPers);
	float nNowTime = 0;
	float life_time;
	std::map<int, std::vector<MomentEightItem>> momentEightItemTypes;

};