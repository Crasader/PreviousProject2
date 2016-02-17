#pragma once

#include "cocos2d.h"

USING_NS_CC;
class TurntableCell : public Sprite
{
public:
	virtual bool init(int propID,int propNum);
	static TurntableCell* create(int propID, int propNum);

};
