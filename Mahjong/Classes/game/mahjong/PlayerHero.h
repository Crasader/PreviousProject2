#ifndef __PLAYER_HERO__
#define __PLAYER_HERO__
#include "cocos2d.h"
#include "game/headportrait/HeadPortrait.h"
#include "game/mahjong/Jong.h"
USING_NS_CC;
using namespace std;




class PlayerHero : public cocos2d::Layer
{
public:
	const int JONG_POS_Y = 100;
	const int JONG_SEL_POS_Y = 150;
	virtual bool init();
	bool onTouchBegan(Touch *touch, Event  *event);
	void onTouchMoved(Touch *touch, Event  *event);
	void onTouchEnded(Touch *touch, Event  *event);
	CREATE_FUNC(PlayerHero);
private:
	Vector<Jong*> selfHandJongs;//自己的手牌
	Vector<Jong*> selfSmallJongs;//自己的出牌牌堆
	Vector<Jong*> selfSpecialJongs;//自己的碰和吃牌堆
	Jong* selectJong;//选中的牌
	Jong* virtualJong;//虚牌(轮到自己打牌时才会出现)
	void drawPlayerHero();//绘制自己
	void drawHeadPortrait(HeadPortrait* headPortrait);//绘制头像
	void resetJongPos();//回复除选中牌以外牌的位置
	void resetAllJong();//回复所有牌的位置
	float distance(Point pos1, Point pos2);//计算2点间的间距
	Point getSmallJongsPos(int index);//获得打出去的牌的停留坐标
	Vector<Jong*>  sortJongs(Vector<Jong*> jongs);//对手牌进行排序
	Vector<Jong*>  upsetJongs(Vector<Jong*> jongs);//打乱排序
	void addCoustomListener();//添加自定义监听事件
	void addTouchListener();//添加屏幕的触摸事件
};
#endif