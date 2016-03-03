#include "utill/CollisionUtill.h"

bool CollisionUtill::isCollisionOBB1AndOBB2(OBBEX obb1, OBBEX obb2)
{
	return obb1.isCollidWithOBB(obb2);
}

bool CollisionUtill::isCollisionOBBsAndOBB(std::vector<OBBEX> obbs, OBBEX obb)
{
	bool isconllision = false;
	for (auto var:obbs)
	{
		if (var.isCollidWithOBB(obb))
		{
			isconllision =  true;
			break;
		}
	}
	return isconllision;
}

bool CollisionUtill::isCollisionOBBsAndOBBs(std::vector<OBBEX> obbs1, std::vector<OBBEX> obbs2)
{
	bool isconllision = false;
	for (auto var1 : obbs1)
	{
		if (isconllision)
		{
			break;
		}
		for (auto var2 : obbs2)
		{
			if (var1.isCollidWithOBB(var2))
			{
				isconllision = true;
				break;
			}
		}
	}
	return isconllision;

}

bool CollisionUtill::isCollisionOBBsAndPoint(std::vector<OBBEX> obbs1, Vec2 pos)
{
	bool isconllision = false;
	for (auto var1 : obbs1)
	{
		if (var1.isCollidWithPoint(pos))
		{
			isconllision = true;
			break;
		}
	}
	return isconllision;
}







bool CollisionUtill::isCollisionOBB1AndOBB2(OBB obb1, OBB obb2)
{
	bool isconllision = obb1.intersects(obb2);
	return isconllision;
}

bool CollisionUtill::isCollisionOBBsAndOBB(std::vector<OBB> obbs, OBB obb)
{
	bool isconllision = false;
	for (auto var : obbs)
	{
		if (var.intersects(obb))
		{
			isconllision = true;
			break;
		}
	}
	return isconllision;
}

bool CollisionUtill::isCollisionOBBsAndOBBs(std::vector<OBB> obbs1, std::vector<OBB> obbs2)
{

	bool isconllision = false;
	for (auto var1 : obbs1)
	{
		if (isconllision)
		{
			break;
		}
		for (auto var2 : obbs2)
		{
			Vec3 verts1[8];
			Vec3 verts2[8];
			var1.getCorners(verts1);

			var2.getCorners(verts2);

			if (var1.intersects(var2))
			{
				isconllision = true;
				break;
			}
		}
	}
	return isconllision;
}

bool CollisionUtill::isCollisionOBBsAndPoint(std::vector<OBB> obbs1, Vec2 pos)
{
	bool isconllision = false;
	for (auto var:obbs1)
	{
		isconllision = var.containPoint(Vec3(pos.x,pos.y,0));
	}
	return isconllision;
}