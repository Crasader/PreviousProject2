#pragma once
#include "cocos2d.h"
#include "utill/CCircle.h"
#include "utill/CMyrect.h"
USING_NS_CC;

class CollisionUtill
{
public:
	static bool isCollisionRect(std::vector<CFigure*> figures, Rect rect);
	static bool isCollisionCircle(std::vector<CFigure*> figures, CCircle circle);
};


