#pragma once
#include "cocos2d.h"
#include "MomentIntervalCreate.h"
#include "fish/FishManage.h"
using namespace cocos2d;

class MomentTwo : public MomentIntervalCreate {

public:
	virtual void initData();
	virtual bool updata(float dt);
	virtual void init(float ffonetime);
};
