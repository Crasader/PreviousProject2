#pragma once
#include "cocos2d.h"
#include "moment/Moment.h"
#include "utill/Audio.h"
#include "fish/FishGroupData.h"
using namespace cocos2d;


struct MomentIntervalCreateFishInfo
{
	int  _fishid;
	int  _route;
	Vec2 _startPos;
	Vec2 _endPos;
	float  _moveTime;
	float _time;
};


class MomentIntervalCreate :public Moment{

public:
	virtual void initData();
	virtual void init(float FFOneTime);
	virtual bool updata(float dt);
protected:
	int m_groupTag;
	float nNowTime;
	int fishMinSize;

	std::vector<MomentIntervalCreateFishInfo> info;
	FishGroup gp;
	
};
