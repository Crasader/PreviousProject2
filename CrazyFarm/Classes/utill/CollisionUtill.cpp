#include "utill/CollisionUtill.h"

bool CollisionUtill::isCollisionOBB1AndOBB2(OBBEX *obb1, OBBEX *obb2)
{
	bool isconllision = obb1->isCollidWithOBB(obb2);
	delete obb1;
	delete obb2;
	return isconllision;
}

bool CollisionUtill::isCollisionOBBsAndOBB(std::vector<OBBEX*> obbs, OBBEX *obb)
{
	bool isconllision = false;
	for (auto var:obbs)
	{
		if (var->isCollidWithOBB(obb))
		{
			isconllision =  true;
			break;
		}
	}
	for (auto var:obbs)
	{
		delete var;
	}
	delete obb;
	return isconllision;
}

bool CollisionUtill::isCollisionOBBsAndOBBs(std::vector<OBBEX*> obbs1, std::vector<OBBEX*> obbs2)
{
	bool isconllision = false;
	for (auto var1 : obbs1)
	{
		if (isconllision)
		{
			break;
		}
		for (auto var2:obbs2)
		{
			if (var1->isCollidWithOBB(var2))
			{
				isconllision = true;
				break;
			}
		}
	}
	for (auto var : obbs1)
	{
		delete var;
	}
	for (auto var : obbs2)
	{
		delete var;
	}
	return isconllision;
}

bool CollisionUtill::isCollisionOBBsAndPoint(std::vector<OBBEX*> obbs1, Vec2 pos)
{
	bool isconllision = false;
	for (auto var1 : obbs1)
	{
		if (var1->isCollidWithPoint(pos))
		{
			isconllision = true;
			break;
		}
	}
	for (auto var : obbs1)
	{
		delete var;
	}

	return isconllision;
}