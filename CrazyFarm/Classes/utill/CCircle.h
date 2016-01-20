#pragma once
#include "cocos2d.h"
USING_NS_CC;

class CCircle
{
public:
	CCircle(void);
	CCircle(Point& center, float radius); //提供圆心与半径 初始化圆
	~CCircle(void);

	bool intersectsRect(Rect& rect) const;//是否与长方形区域相交
	bool intersectsCircle(CCircle& circle) const;//是否与圆形区域相交
	static CCircle  CCCircMake(Point pos, float radius)
	{
		return CCircle(pos, (float)(radius));
	}
private:
	CC_SYNTHESIZE(Point, m_center, MCenter);//圆心
	CC_SYNTHESIZE(float, m_radius, MRadius);//半径
};


