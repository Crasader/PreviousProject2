#pragma once
#include "cocos2d.h"
#include "moment/Moment.h"
#include "fish/FishManage.h"
using namespace cocos2d;

class MomentOne	:	public Moment {

public:
	virtual void init();
    virtual bool updata(float dt);
	std::list<OneMoment> m_oneMoment;
private:
	float nNowTime = 0;
};
