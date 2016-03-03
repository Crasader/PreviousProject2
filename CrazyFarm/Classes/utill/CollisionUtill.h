#pragma once
#include "cocos2d.h"
#include "utill/OBB.h"
USING_NS_CC;

class CollisionUtill
{
public:
	static bool isCollisionOBB1AndOBB2(OBBEX obb1, OBBEX obb2);

	static bool isCollisionOBBsAndOBB(std::vector<OBBEX> obbs, OBBEX obb);
	static bool isCollisionOBBsAndOBBs(std::vector<OBBEX> obbs1, std::vector<OBBEX> obbs2);

	static bool isCollisionOBBsAndPoint(std::vector<OBBEX> obbs1, Vec2 pos);





	static bool isCollisionOBB1AndOBB2(OBB obb1, OBB obb2);

	static bool isCollisionOBBsAndOBB(std::vector<OBB> obbs, OBB obb);
	static bool isCollisionOBBsAndOBBs(std::vector<OBB> obbs1, std::vector<OBB> obbs2);

	static bool isCollisionOBBsAndPoint(std::vector<OBB> obbs1, Vec2 pos);
};


