#ifndef __PLAYER_LEFT__
#define __PLAYER_LEFT__
#include "cocos2d.h"
#include "game/playerinfo/PlayerInfo.h"
USING_NS_CC;

class PlayerLeft :  public Sprite{

public:
	virtual bool init();
	CREATE_FUNC(PlayerLeft);
	void drawHeadPortrait(PlayerInfo* playerInfo);
};
#endif 