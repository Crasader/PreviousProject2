#pragma once
#include "cocos2d.h"
#include "config/ConfigOnemoment.h"
using namespace cocos2d;


class Moment {

public:
	virtual void init() = 0;
	virtual bool updata(float dt) = 0;

	
};
