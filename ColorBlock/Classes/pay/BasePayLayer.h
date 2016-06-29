#pragma once
#include "cocos2d.h"
#include "PayUiConfig.h"
#include "ui/UIButton.h"  
using namespace ui;
USING_NS_CC;
class BasePayLayer :public cocos2d::Layer
{
public:
	static BasePayLayer*create(std::vector<ImageElement> items);
protected:
	virtual bool init(std::vector<ImageElement> items);
	void quedingButton(Ref* psender, Widget::TouchEventType type);
	void quxiaoButton(Ref* psender, Widget::TouchEventType type);
private:
	Size visisize;
	CC_SYNTHESIZE(int, _eventid, EventId);
};

