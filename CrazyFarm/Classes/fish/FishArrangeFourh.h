#pragma once
#include "cocos2d.h"
#include "fish/Fish.h"
using namespace cocos2d;


class FishArrangeFourh :public Fish{
public:
	CREATE_FUNC(FishArrangeFourh);
	virtual void initFish(int fishType);
	virtual void initFishAnim(int fishType);
	void addShader(){};
	virtual void onDead();
	void pushBackFigureVec(int uiid, Point pos);
};
