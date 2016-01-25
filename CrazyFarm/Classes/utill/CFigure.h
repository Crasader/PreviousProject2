#pragma once
#include "cocos2d.h"
USING_NS_CC;

class  CCircle;
class CFigure
{
public:
	virtual bool intersectsRect(Rect rect) = 0;
	virtual bool intersectsPoint(Point pos) = 0;
	virtual bool intersectsCircle(CCircle circle)=0;
	virtual CFigure*clone() = 0;
	virtual CFigure* ApplyAffineTransform(const CFigure* rect, const AffineTransform& anAffineTransform) = 0;
	virtual CFigure* addposWithFigure(Point pos) = 0;
	virtual void draw(Node*parent) = 0;
};


