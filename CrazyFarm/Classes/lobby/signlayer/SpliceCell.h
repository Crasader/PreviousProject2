#pragma once

#include "cocos2d.h"
#include "config/ConfigSign.h"
#include "SignCell.h"
USING_NS_CC;
class SpliceCell :public Node
{
public:
	virtual bool init(int curIndex);

	static SpliceCell* create(int curIndex);

	void setBegin(){ scheduleUpdate(); }
private:
	void update(float delta);
	float nTumbleTime = 0;;
	float speed = 0;
	int curValue = 0;
	Sprite*content1;
	Sprite*content2;
};



