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
	MomentEightItemPer getFishByRandVec(std::vector<MomentEightItemPer> momentEightItemPers);
	float fInterval = 1;
	float fTemp1;
	float fTemp2;
	float fTemp3;
	float fTemp4;
	float fTemp5;
	float nNowTime = 0;
	MomentEightItem momentEightItemType1;
	MomentEightItem momentEightItemType2;
	MomentEightItem momentEightItemType3;
	MomentEightItem momentEightItemType4;
	MomentEightItem momentEightItemType5;
};