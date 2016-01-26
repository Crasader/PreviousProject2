#pragma once
#include "cocos2d.h"
#include "utill/CFigure.h"
USING_NS_CC;

class CCircle:public CFigure
{
public:
	CCircle(void);
	CCircle(Point center, float radius); //提供圆心与半径 初始化圆
	~CCircle(void);

	bool intersectsRect(Rect rect) ;//是否与长方形区域相交
	bool intersectsCircle(CCircle circle);//是否与圆形区域相交
	bool intersectsPoint(Point pos);
	virtual CFigure* ApplyAffineTransform(const CFigure* figure, const AffineTransform& anAffineTransform);
	virtual CFigure* addposWithFigure(Point pos);
	virtual void draw(Node*parent);
	CFigure*clone();
private:
	CC_SYNTHESIZE(Point, m_center, MCenter);//圆心
	CC_SYNTHESIZE(float, m_radius, MRadius);//半径
};


