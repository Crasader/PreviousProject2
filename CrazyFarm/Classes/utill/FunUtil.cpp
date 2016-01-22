#include "utill/FunUtil.h"


bool collision(Rect rectA, Rect rectB)
{
	const float scaleMultiple = 0.7;
	rectA.setRect(rectA.getMinX() + rectA.size.width / 2 * (1 - scaleMultiple), rectA.getMinY() + rectA.size.height / 2 * (1 - scaleMultiple), rectA.size.width*scaleMultiple, rectA.size.height*scaleMultiple);

	rectB.setRect(rectB.getMinX() + rectB.size.width / 2 * (1 - scaleMultiple), rectB.getMinY() + rectB.size.height / 2 * (1 - scaleMultiple), rectB.size.width*scaleMultiple, rectB.size.height*scaleMultiple);

	return rectA.intersectsRect(rectB);
}



bool collision(Sprite*spA, Sprite*spB)
{

	const float scaleMultiple = 0.7;
	auto rect1 = spA->getBoundingBox();
	rect1.setRect(rect1.getMinX() + rect1.size.width / 2 * (1 - scaleMultiple), rect1.getMinY() + rect1.size.height / 2 * (1 - scaleMultiple), rect1.size.width*scaleMultiple, rect1.size.height*scaleMultiple);
	auto rect2 = spB->getBoundingBox();
	rect2.setRect(rect2.getMinX() + rect2.size.width / 2 * (1 - scaleMultiple), rect2.getMinY() + rect2.size.height / 2 * (1 - scaleMultiple), rect2.size.width*scaleMultiple, rect2.size.height*scaleMultiple);

#if 0
	auto draw = DrawNode::create();
	addChild(draw, 10);
	draw->drawRect(rect1.origin, Vec2(rect1.getMaxX(), rect1.getMaxY()), Color4F::YELLOW);
	draw->drawRect(rect1.origin, Vec2(rect1.getMaxX(), rect1.getMaxY()), Color4F::RED);
#endif
	return rect1.intersectsRect(rect2);
}


swimDirection getDirectionByPosition(Vec2 pos)
{
	int x = pos.x;
	int y = pos.y;
	if (x<=0)
	{
		return RIGHT;
	}
	if (x>=960)
	{
		return LEFT;
	}
	if (y>=540)
	{
		return DOWN;
	}
	if (y <= 0)
	{
		return UP;
	}

}

float  getAngleByPos(Vec2 pos)
{
	auto k = (pos.y - 270.0) / (pos.x - 480);
	if (pos.x>480)
	{
		return 180+CC_RADIANS_TO_DEGREES(atan(k));
	}
	return CC_RADIANS_TO_DEGREES(atan(k));
}


Vec2 CalculateDiffMarginPos(Vec2 pos,float diff)
{
	if (pos.x<=0)
	{
		return Vec2(pos.x - diff, pos.y);
	}
	if (pos.x>=960)
	{
		return Vec2(pos.x + diff, pos.y);
	}
	if (pos.y>=540)
	{
		return Vec2(pos.x, pos.y + diff);
	}
	if (pos.y<=0)
	{
		return Vec2(pos.x, pos.y - diff);
	}

	return pos;
}



float getRandonNumByAtoB(float A, float B)
{	
	return  A + (B - A)*rand() / (float)RAND_MAX;
}


int getCurrencyRankByRange(int startRank, int endRank, int startValue, int endValue, int curValue)
{
	float fTemp = ((float)curValue) / ((float)(endValue - startValue));
	auto currrRank = endRank - (endRank - startRank)*fTemp;
	return currrRank;
}

std::string SpliceDataForPostHttp(std::vector<std::string> strs)
{
	std::string s;
	for (auto var:strs)
	{
		s += "&";
		s += var.c_str();
	}
	return s;
}

std::string  SpliceDataForPostHttp(std::string str1, ...)
{
//	std:string s;
//	va_list args;
//	va_start(args, str1);
//
//	while (1){
//		auto s1 = va_arg(args, std::string);
//		if (s1 == "-1")
//		{
//			return s;
//		}
//		s += "&";
//		s += s1.c_str();
//	}
	return "";
}

std::string NewAtoI(int num)
{
	auto str = String::createWithFormat("%d", num);
	return str->getCString();
}
std::string NewAtoI(long num)
{
	auto str = String::createWithFormat("%ld", num);
	return str->getCString();
}
