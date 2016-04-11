#pragma once
#include "cocos2d.h"
#include "server/HttpMannger.h"
#include "RoomCell.h"
USING_NS_CC;




class RoomLayer : public cocos2d::Layer
{
public:
	static RoomLayer * createLayer();

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);



	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event){ return; };
	virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event){ return; };
	virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event){ return; };
private:
	void update(float delta);
	virtual bool init();
	void createRoomLayer();
	std::vector<RoomItem> sortRoomByMaxlevel(int maxLevel);
	void closeButtonCallBack(Ref*psend);
	Vector<RoomCell*> roomCells;
	void moveRoomRight();
	void moveRoomLeft();
	float touchtime = 0;
	bool isTouchMove = false;
	Node* touchnode;
	int diffx;

	std::vector<RoomItem> _roomitems;
	bool isMove = false;
};
