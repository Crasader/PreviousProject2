#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"


using namespace cocos2d;
USING_NS_CC_EXT;


class RedPackCell : public Sprite{
public:
	static RedPackCell*create(int type);
private:
	virtual bool init(int type);
	void btCallback(Ref*psend);
	int _type;


};
