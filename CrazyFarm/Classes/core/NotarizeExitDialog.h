#pragma once
#include "cocos2d.h"
#include "widget/MyDialog.h"
USING_NS_CC;
class NotarizeExitDialog : public MyDialog
{
public:
	CREATE_FUNC(NotarizeExitDialog);
	virtual bool init();
protected:
	void querenCallback(Ref*psend);
	void closeButtonCallBack(Ref*psend);
};

