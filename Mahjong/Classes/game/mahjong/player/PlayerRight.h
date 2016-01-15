#ifndef __PLAYER_RIGHT__
#define __PLAYER_RIGHT__
#include "cocos2d.h"
#include "game/playerinfo/PlayerInfo.h"
#include "game/mahjong/player/base/PlayerBase.h"
#include "game/mahjong/Jong.h"
USING_NS_CC;

class PlayerRight : public PlayerBase{

public:

	virtual bool init();

	CREATE_FUNC(PlayerRight);

private:

	const int RIGHT_POS_X = 820;

	const int RIGHT_POS_Y = 475;

	int count;//打出去的牌计数

	void drawHandJong();//绘制左边玩家的手牌

	void drawPlayedJong(int ctype);//绘制打出去的牌

	void drawHuaJong(int cType);//绘制左边玩家的花牌

	Point getPlayedJongPos();//获取打出去的牌的位置

	void drawCurrent();//放大当前打出的牌

	void playerTurn();//轮到摸牌

	void addCoustomListener();//添加自定义监听事件

};
#endif 