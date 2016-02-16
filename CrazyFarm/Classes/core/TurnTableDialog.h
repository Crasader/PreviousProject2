#pragma once
#include "cocos2d.h"
#include "domain/bonuspool/BonusPoolManager.h"
USING_NS_CC;
class TurnTableDialog : public Layer
{
public:
	CREATE_FUNC(TurnTableDialog);
	virtual bool init();
	void onGetRewards(BonuspoolRewardItem reward);
	void createBottomFrame(bool isFinish);
protected:
	void closeButtonCallBack(Ref*psend);
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent){ return true; };
};

