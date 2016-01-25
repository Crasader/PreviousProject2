#pragma once
#include "cocos2d.h"
#include "utill/Chinese.h"
#include "config/ConfigItem.h"
USING_NS_CC;





class ShowPropLayer : public cocos2d::Layer
{
public:

    virtual bool init(int itemId);

	static ShowPropLayer*create(int itemId);


private:
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void quedingcallback(Ref*);
	void closeButtonCallBack(Ref*psend);
	Item Iitem;
	int itemId;
};
