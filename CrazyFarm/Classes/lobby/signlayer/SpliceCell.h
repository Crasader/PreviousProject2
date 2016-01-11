#pragma once

#include "cocos2d.h"
#include "config/ConfigSign.h"
#include "SignCell.h"
USING_NS_CC;
class SpliceCell :public Node
{
public:
	virtual bool init(std::vector<SignRewardItem> rewards);

	static SpliceCell* create(std::vector<SignRewardItem> rewards);


private:
	Vector<SpliceCell*> cells;
	void update(float delta);

	CC_SYNTHESIZE(int, nTumbleTime, TumbleTime);
	
};


class SpliceCellView :public Node
{
public:
	virtual bool init(std::vector<SignRewardItem> rewards);

	static SpliceCell* create(std::vector<SignRewardItem> rewards);

	void update(float delta);

	CC_SYNTHESIZE(int, nTumbleTime, TumbleTime);

};

