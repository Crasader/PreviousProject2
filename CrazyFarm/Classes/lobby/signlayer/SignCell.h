#pragma once

#include "cocos2d.h"

USING_NS_CC;
class SignCell : public Sprite
{
public:
	virtual bool init(int propID,int propNum);

	static SignCell* create(int propID, int propNum);

};
