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
	void resetJongPos();//回复牌的位置
	void resetAllJong();//回复牌的位置

};
#endif