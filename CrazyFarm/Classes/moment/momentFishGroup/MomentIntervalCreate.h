#pragma once
#include "cocos2d.h"
#include "moment/Moment.h"
using namespace cocos2d;


class MomentIntervalCreate :public Moment{

public:
	virtual void initData();
	virtual void init();
	virtual bool updata(float dt);
protected:
	int m_groupTag;
	float nNowTime;
	int fishMinSize;
	
};
