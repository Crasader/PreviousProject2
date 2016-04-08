#pragma once
#include "cocos2d.h"
#include "utill/Chinese.h"
USING_NS_CC;
class ReloginDialog : public Layer
{
protected:
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent){ return true; };
	void reloginCB(Ref*psend);
public:
	static ReloginDialog* createDialog(const char* tipStr);
	virtual bool init(const char* tipStr);
	void showRandonBubbleAni();
};

