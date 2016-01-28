#pragma once
#include "cocos2d.h"
#include "RoomCell.h"
USING_NS_CC;




class RoomLayer : public cocos2d::Layer
{
public:
	static RoomLayer * createLayer();

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);

private:
	void update(float delta);
	virtual bool init();
	void createRoomLayer();
	std::vector<Room> sortRoomByMaxlevel(int maxLevel);
	void closeButtonCallBack(Ref*psend);
	Vector<RoomCell*> roomCells;
	void moveRoomRight();
	void moveRoomLeft();
};
