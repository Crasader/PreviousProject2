#pragma once
#include "cocos2d.h"
USING_NS_CC;


class TwiceSureChangePropDialog : public Layer
{
public:
	virtual bool init(int itemid,int num);
	static TwiceSureChangePropDialog* createTwiceChangeGiftTip(int itemid,int num);
private:
	void showRandonBubbleAni();
	void sureButtonCallBack(Ref*psend);
	void closeButtonCallBack(Ref*psend);
	int _itemid;
	int _num;
};
