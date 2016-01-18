#pragma once
#include "cocos2d.h"
USING_NS_CC;
class  MyMenuItemGainMoney :public MenuItemImage
{
public:
	static MyMenuItemGainMoney * create();
	void setValue();
private:
	void ItemCallBack(Ref* psend);
	void initItem();
	Node* commonNode;
	bool isElongate = false;
	bool isFinish = false;

	
};
