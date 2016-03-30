#pragma once
#include "cocos2d.h"
USING_NS_CC;
class SexHead :public Sprite
{
public:
	static SexHead* create(int sex, int isChoose);
	bool init(int sex, int isChoose);
	void setIsChoose(bool isChoose);
};