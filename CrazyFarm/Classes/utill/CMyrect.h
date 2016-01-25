#pragma once
#include "cocos2d.h"
#include "utill/CFigure.h"
#include "utill/CCircle.h"
USING_NS_CC;

class CMyrect:public Rect,public CFigure
{
public:
	CMyrect();
	CMyrect(Rect rect);
	CMyrect(Point orgin,Size ssize);
	virtual bool intersectsRect(Rect rect);
	virtual bool intersectsPoint(Point pos);
	virtual bool intersectsCircle(CCircle circle);
	virtual CFigure*clone();
	CFigure* ApplyAffineTransform(const CFigure* figure, const AffineTransform& anAffineTransform);
	CFigure* addposWithFigure(Point pos);
	void draw(Node*parent);
};


