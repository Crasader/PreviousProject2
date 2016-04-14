#pragma once
#include "cocos2d.h"
#include "MaridTaskCell.h"
#include "server/Msg/MsgOnBeginMarried.h"
USING_NS_CC;


class maridTaskPlane : public Sprite
{
public:
	static maridTaskPlane*create(int lefttime,std::vector<MarriedTaskFishItem> items);
	void addMaridTaskfish(int fishid);
	void onFinishSecuss();
private:
	virtual bool init(int lefttime, std::vector<MarriedTaskFishItem> items);
	virtual void onExit();
	void update(float delta);
	float nNowtime = 0;
	int _lefttime;
	LabelTTF* labelNum;
	CC_SYNTHESIZE(std::vector<MarriedTaskFishItem>, _items, MarriedTaskFishItems);
	std::vector<MaridTaskCell*> _cells;
};

