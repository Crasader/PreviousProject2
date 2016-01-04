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
	CREATE_FUNC(MahjongView);

	Vector<Jong*> jongs;//Âé½«ÅÆ¶ÓÁÐ
};
#endif