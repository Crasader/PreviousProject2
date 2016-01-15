#pragma once
#include "cocos2d.h"
#include "moment/Moment.h"
#include "fish/FishManage.h"
using namespace cocos2d;

class MomentEight : public Moment {

public:
	virtual void init();
	virtual bool updata(float dt);
private:
	float fInterval = 1;
	float fTemp;
	float nNowTime = 0;
};