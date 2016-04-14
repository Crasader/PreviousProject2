#pragma once
#include "cocos2d.h"
USING_NS_CC;
class  MyMenuItemUpgrade :public MenuItemImage
{
public:
	static MyMenuItemUpgrade * create();
	void setValue();
	void showPopup();
	void anastole();
private:
	void ItemCallBack(Ref* psend);
	void initItem();
	void showBlinkAni();
	void removeBlinkAni();
	virtual void update(float delta);
	Node* nodeZeng;
	Node*unfinishedNode;
	Node* commonNode;
	bool isElongate = false;
	bool isFinish = false;


};
