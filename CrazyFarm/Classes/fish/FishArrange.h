#pragma once
#include "cocos2d.h"
#include "fish/Fish.h"
using namespace cocos2d;


class FishArrange :public Fish{
public:
	virtual void initFish(int fishID);
	virtual void addShader();
	virtual void onDead();
	virtual void pushBackFigureVec(int uiid, Point pos);
	virtual void onHeart();
	Vector<Node*> fishes;
};
