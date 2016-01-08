#ifndef __DEAL_JONG_ANIM__
#define __DEAL_JONG_ANIM__
#include "cocos2d.h"
USING_NS_CC;

class DealJongAnim :public Layer{
public:
	virtual bool init();
	CREATE_FUNC(DealJongAnim);
	void showDealJong();
	void dealHero();//发牌给自己
	void dealLeft();//发牌给左边的玩家
	void dealRight();//发牌给右边的玩家
	void dealOpposite();//发牌给对面
private:
	Point heroStarPos;//主角发牌的初始位置
	Point leftStarPos;//左边发牌的初始位置
	Point rightStarPos;//右边发牌的初始位置
	Point oppositeStarPos;//对面发牌的初始位置
	void initPosition();//初始化发牌的起始坐标
	Point caluMove2Pos(int type);//计算牌堆发往的坐标
};

enum Direction
{
	hero,
	left,
	right,
	opposite
};
#endif