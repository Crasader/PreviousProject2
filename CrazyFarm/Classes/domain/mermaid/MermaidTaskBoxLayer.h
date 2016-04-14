#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class MermaidTaskBoxLayer :public Layer
{
public:
	CREATE_FUNC(MermaidTaskBoxLayer);
private:
	virtual bool init();
	Sprite* box;
	Sprite* sLight;
	Sprite*tipTxt;
	LayerColor*colorlayer;
	EventListenerTouchOneByOne* listenr1;
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	bool istouched = false;
	CC_SYNTHESIZE(unsigned int, _coins, coins);
};

