#ifndef __PLAYER_OPPOSSITE__
#define __PLAYER_OPPOSSITE__
#include "cocos2d.h"
#include "game/playerinfo/PlayerInfo.h"
#include "game/mahjong/player/base/PlayerBase.h"
USING_NS_CC;

class PlayerOpposite : public PlayerBase{

public:
	virtual bool init();
	CREATE_FUNC(PlayerOpposite);

private:
	const int OPPOSITE_POS_X = 400;

	const int OPPOSITE_POS_Y = 510;

	void drawHandJong();//绘制玩家的手牌

	void drawPlayedJong();//绘制打出去的牌

	void drawHuaJong();//绘制玩家的花牌

	void getPlayedJongPos();//获取打出去的牌的位置

	void drawCurrent();//放大当前打出的牌
};
#endif 