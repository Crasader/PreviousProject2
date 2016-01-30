#pragma once
#include "cocos2d.h"
#include "utill/Chinese.h"

USING_NS_CC;





class ChangeGiftLayer : public cocos2d::Layer
{
public:

    virtual bool init();

	CREATE_FUNC(ChangeGiftLayer);

private:
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void quedingcallback(Ref*);
	void closeButtonCallBack(Ref*psend);
	bool checkTheName(const char* name);
};
