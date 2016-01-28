#pragma once
#include "cocos2d.h"
USING_NS_CC;
class TwiceSureDialog : public Layer
{
protected:
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent){ return true; };
	void closeButtonCallBack(Ref*psend);
	MenuItemImage* close;
public:
	static TwiceSureDialog* createDialog(const char* tipStr, const ccMenuCallback& closecallback);
	void setCloseButtonCallback(const ccMenuCallback& surecallback);
	virtual bool init(const char* tipStr, const ccMenuCallback& callback);

};

