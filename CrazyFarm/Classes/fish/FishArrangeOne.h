#pragma once
#include "cocos2d.h"
#include "fish/Fish.h"
using namespace cocos2d;


class FishArrangeOne :public Fish{
public:
	CREATE_FUNC(FishArrangeOne);
	virtual void initFish(int fishType);
	virtual void initFishAnim(int fishType);
	void addShader();
	virtual void onDead();
};
