#ifndef __PLAYER_LEFT__
#define __PLAYER_LEFT__
#include "cocos2d.h"
#include "game/playerinfo/PlayerInfo.h"
#include "game/mahjong/otherplayer/PlayerSprite.h"
USING_NS_CC;

class PlayerLeft :  public PlayerSprite{

public:

	virtual bool init();

	CREATE_FUNC(PlayerLeft);

private:
	const int LEFT_POS_X = 130;

	const int LEFT_POS_Y = 510;

	void drawHandJong();//绘制玩家的手牌

	void drawPlayedJong();//绘制打出去的牌

	void getPlayedJongPos();//获取打出去的牌的位置

	void drawCurrent();//放大当前打出的牌

};
#endif 