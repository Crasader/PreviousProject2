#ifndef __EXIT_LAYER_H__
#define __EXIT_LAYER_H__

#include "PopupLayer.h"

class ExitLayer : public PopupLayer
{
public:	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(ExitLayer);

private:
	void buttonExitCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event);	//Exit按钮回调函数
	void buttonCancelCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event);	//Cancel按钮回调函数
};

#endif // __EXIT_LAYER_H__