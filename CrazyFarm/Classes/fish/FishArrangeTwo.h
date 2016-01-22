#pragma once
#include "cocos2d.h"
#include "fish/Fish.h"
using namespace cocos2d;






class FishArrangeTwo :public Fish{
public:
	CREATE_FUNC(FishArrangeTwo);
	virtual void initFish(int fishType);
	virtual void initFishAnim(int fishType);
	void addShader(){};
	virtual void onDead();
};
