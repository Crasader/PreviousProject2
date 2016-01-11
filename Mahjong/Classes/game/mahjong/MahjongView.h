#ifndef __MAHJONG_VIEW__
#define __MAHJONG_VIEW__
#include "cocos2d.h"
#include "game/headportrait/HeadPortrait.h"
#include "game/mahjong/Jong.h"
USING_NS_CC;
using namespace std;




class MahjongView : public cocos2d::Layer
{
public:
	virtual bool init();
	void drawPlayerHero();
	void drawPlayerLeft();
	void drawPlayerRight();
	void drawPlayerOpposite();
	void drawMenu();
	CREATE_FUNC(MahjongView);
private:
	void addTouchListener();//添加屏幕的触摸事件
	void addCoustomListener();//添加自定义监听事件
	void dealJongs();//发牌
	void chatButton();//聊天按钮
	void billingButton();//账单按钮
	void packageButton();//背包按钮
	//测试方法
	void testButton();
	void testEvent();

};
#endif