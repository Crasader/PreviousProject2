#ifndef __PLAYER_OPPOSSITE__
#define __PLAYER_OPPOSSITE__
#include "cocos2d.h"
#include "game/playerinfo/PlayerInfo.h"
USING_NS_CC;

class PlayerOpposite : public Sprite{

public:
	virtual bool init();
	void drawHeadPortrait(PlayerInfo* playerInfo);
	CREATE_FUNC(PlayerOpposite);
};
#endif 