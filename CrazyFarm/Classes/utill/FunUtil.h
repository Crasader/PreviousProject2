#pragma once
#include "cocos2d.h"
#include "fish/Fish.h"
USING_NS_CC;

//Åö×²¼ì²â
bool collision(Sprite*spA, Sprite*spB);
swimDirection getDirectionByPosition(Vec2 pos);
float  getAngleByPos(Vec2 pos);

Vec2 CalculateDiffMarginPos(Vec2 pos,float diff);
