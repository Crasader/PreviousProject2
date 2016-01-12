#pragma once
#include "cocos2d.h"
#include "NobilityLayer.h"
USING_NS_CC;

class NobilityLayer : public Layer
{
public:
	virtual bool init();
	static NobilityLayer * createLayer();
	virtual bool onTouchBegan(Touch *touch, Event *unused_event){ return true; };
	void updata(float dt);
private:
	
};

