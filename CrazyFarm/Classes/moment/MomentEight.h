#pragma once
#include "cocos2d.h"
#include "moment/Moment.h"
#include "fish/FishManage.h"
#include "config/ConfigMomentEight.h"
using namespace cocos2d;

class MomentEight : public Moment {

public:
	virtual void init(float FFOneTime);
	virtual bool updata(float dt);
private:
	float nNowTime = 0;
	float life_time;
	std::map<int, std::vector<MomentEightItem>> momentEightItemTypes;

};