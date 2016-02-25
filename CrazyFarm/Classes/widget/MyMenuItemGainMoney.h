#pragma once
#include "cocos2d.h"
USING_NS_CC;
class  MyMenuItemGainMoney :public MenuItemImage
{
public:
	static MyMenuItemGainMoney * create();
	void setValue();
	void showPopup();
private:
	void ItemCallBack(Ref* psend);
	void initItem();
	void showBlinkAni();
	Node* commonNode;
	Sprite*txt;
	Sprite* exeBarFrame;
	bool isElongate = false;
	bool isFinish = false;

	
};
