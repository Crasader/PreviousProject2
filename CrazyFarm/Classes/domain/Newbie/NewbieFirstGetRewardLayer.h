#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class NewbieFirstGetRewardLayer :public Layer
{
public:
	CREATE_FUNC(NewbieFirstGetRewardLayer);
private:
	virtual bool init();
	Sprite* box;
	Sprite* sPoint;
	Sprite* sLight;
	Sprite*tipTxt;
	LayerColor*colorlayer;
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
};

