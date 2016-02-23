#include "utill/CollisionUtill.h"


bool CollisionUtill::isCollisionRect(std::vector<CFigure*> figures, Rect rect)
{
	for (auto var :figures)
	{
		if (var->intersectsRect(rect))
		{
			return true;
		}
	}
	return false;
}

bool CollisionUtill::isCollisionCircle(std::vector<CFigure*> figures, CCircle circle)
{
	for (auto var : figures)
	{
		if (var->intersectsCircle(circle))
		{
			return true;
		}
	}
	return false;
}

bool CollisionUtill::isCollisionPoint(std::vector<CFigure*> figures, Point pos)
{
	for (auto var : figures)
	{
		if (var->intersectsPoint(pos))
		{
			return true;
		}
	}
	return false;
}