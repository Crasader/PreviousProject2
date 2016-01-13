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
};
#endif 