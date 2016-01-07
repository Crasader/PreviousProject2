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
	CREATE_FUNC(MahjongView);
private:
	void dealJongs();//发牌功能
	void addTouchListener();//添加屏幕的触摸事件
	void addCoustomListener();//添加自定义监听事件
};
#endif