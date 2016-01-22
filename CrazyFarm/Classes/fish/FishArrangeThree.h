#pragma once
#include "cocos2d.h"
#include "fish/Fish.h"
using namespace cocos2d;


class FishArrangeThree :public Fish{
public:
	CREATE_FUNC(FishArrangeThree);
	virtual void initFish(int fishType);
	virtual void initFishAnim(int fishType);
	void addShader(){};
};
