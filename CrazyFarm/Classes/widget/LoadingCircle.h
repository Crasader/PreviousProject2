#pragma once
#include "cocos2d.h"
USING_NS_CC;
class LoadingCircle : public Sprite
{
public:
	static LoadingCircle* create();
	static void showLoadingCircle();
	static void RemoveLoadingCircle();
private:
	bool init();
	static LoadingCircle*_circle;
};
