#pragma once
#include "cocos2d.h"
#include "MomentController.h"
#include "fish/FishManage.h"
using namespace cocos2d;

class MomentControllerOne	:	public MomentController {

public:
	virtual void initController(std::list<OneMoment> oneMoment);
	std::list<OneMoment> m_oneMoment;
	virtual bool updata(float dt);
private:
	float nNowTime = 0;
};
