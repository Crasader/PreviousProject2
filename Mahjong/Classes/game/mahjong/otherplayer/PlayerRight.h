#ifndef __PLAYER_RIGHT__
#define __PLAYER_RIGHT__
#include "cocos2d.h"
#include "game/playerinfo/PlayerInfo.h"
USING_NS_CC;

class PlayerRight : public Sprite{

public:
	virtual bool init();
	void drawHeadPortrait(PlayerInfo* playerInfo);
	CREATE_FUNC(PlayerRight);
};
#endif 