#pragma once
#include "cocos2d.h"
USING_NS_CC;
class  MyMenuItemUpgrade :public MenuItemImage
{
public:
	static MyMenuItemUpgrade * create();
	void setValue();
private:
	void ItemCallBack(Ref* psend);
	void initItem();
	Node* nodeZeng;
	Node*unfinishedNode;
	Node* commonNode;
	bool isElongate = false;
	bool isFinished = false;
	
};
