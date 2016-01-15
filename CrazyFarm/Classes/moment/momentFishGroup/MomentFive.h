#pragma once
#include "cocos2d.h"
#include "MomentIntervalCreate.h"
#include "fish/FishManage.h"
using namespace cocos2d;

struct MomentFiveData 
{
	int fishID;
	float startTime;
	Vec2 pos;
	MomentFiveData(int id, float time,Vec2 p){ fishID = id, time = startTime; pos=p};
};
class MomentFive : public Moment {

public:
	virtual void init();
	virtual bool updata(float dt);
private:
	float fInterval = 6;
	float fTemp1;
	float nNowTime = 0;
	std::vector<MomentFiveData> datas;
};
