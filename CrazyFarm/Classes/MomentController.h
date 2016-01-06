#pragma once
#include "cocos2d.h"
#include "config/ConfigOnemoment.h"
using namespace cocos2d;



struct  FishItem
{
	int fishgroup_id;
	float start_time;
	float costTime;
	Vec2 startPos;
	Vec2 endPos;
	int move_type;
};
class MomentController {

public:
	virtual void initController(std::list<OneMoment> oneMoment) = 0;
	virtual bool updata(float dt) = 0;
protected:
	std::list<FishItem> items;
	
};
