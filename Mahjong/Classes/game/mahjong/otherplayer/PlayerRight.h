#ifndef __PLAYER_RIGHT__
#define __PLAYER_RIGHT__
#include "cocos2d.h"
#include "game/playerinfo/PlayerInfo.h"
#include "game/mahjong/otherplayer/PlayerSprite.h"
USING_NS_CC;

class PlayerRight : public PlayerSprite{

public:

	virtual bool init();

	CREATE_FUNC(PlayerRight);

private:

	const int RIGHT_POS_X = 820;

	const int RIGHT_POS_Y = 475;

	void drawHandJong();//绘制玩家的手牌

	void drawPlayedJong();//绘制打出去的牌

};
#endif 