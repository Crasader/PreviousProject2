#ifndef __DEAL_JONGS__
#define __DEAL_JONGS__
#include "cocos2d.h"
USING_NS_CC;

class DealJongs :public Layer{
public:
	virtual bool init();
	CREATE_FUNC(DealJongs);
	void showDealJong();
	void dealHero();//发牌给自己
	void dealLeft();//发牌给左边的玩家
	void dealRight();//发牌给右边的玩家
	void dealOpposite();//发牌给对面
};
#endif