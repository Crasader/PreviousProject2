#ifndef __PLAYER_OPPOSSITE__
#define __PLAYER_OPPOSSITE__
#include "cocos2d.h"
#include "game/playerinfo/PlayerInfo.h"
#include "game/mahjong/otherplayer/PlayerSprite.h"
USING_NS_CC;

class PlayerOpposite : public PlayerSprite{

public:
	virtual bool init();
	CREATE_FUNC(PlayerOpposite);
};
#endif 