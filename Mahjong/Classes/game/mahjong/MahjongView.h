#ifndef __MAHJONG_VIEW__
#define __MAHJONG_VIEW__
#include "cocos2d.h"
#include "game/domian/HeadPortrait.h"
#include "game/mahjong/Jong.h"
USING_NS_CC;
using namespace std;




class MahjongView : public cocos2d::Layer
{
public:
	const int JONG_POS_Y = 100;
	const int JONG_SEL_POS_Y = 150;
	virtual bool init();
	void drawPlayerSelf();
	void drawPlayerLeft();
	void drawPlayerRight();
	void drawPlayerOpposite();
	void drawHeadPortrait(HeadPortrait* headPortrait);
	bool onTouchBegan(Touch *touch, Event  *event);
	void onTouchMoved(Touch *touch, Event  *event);
	void onTouchEnded(Touch *touch, Event  *event);
	CREATE_FUNC(MahjongView);
private:
	Vector<Jong*> selfJongs;//麻将牌队列
	Jong* selectJong;//选中的牌
	Jong* virtualJong;//虚牌(轮到自己打牌时才会出现)
	bool isNeedCheck;
	int playerTurn;
	void resetJongPos();//回复牌的位置
	void resetAllJong();//回复牌的位置
	float distance(Point pos1, Point pos2);

};
#endif