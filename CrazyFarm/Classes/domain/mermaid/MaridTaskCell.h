#pragma once
#include "cocos2d.h"
USING_NS_CC;


class MaridTaskCell : public Sprite
{
public:
	static MaridTaskCell*create(int fishid,int totalnum);
	void addfish();
private:
	void onFinish();
	CC_SYNTHESIZE(int, _fishid, fishid);
	int _totalnum;
	int _curnum = 0;
	virtual bool init(int fishid, int totalnum);
	bool isFinish = false;
};

