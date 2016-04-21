#pragma once
#include "cocos2d.h"
USING_NS_CC;

class RedPackLayer : public cocos2d::Layer
{
public:


    virtual bool init();

	CREATE_FUNC(RedPackLayer);

private:
	void closeButtonCallBack(Ref*psend);
	virtual bool onTouchBegan(Touch *touch, Event *unused_event){ return true; };

};
