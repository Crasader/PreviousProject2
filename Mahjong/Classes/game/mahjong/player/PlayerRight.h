#ifndef __PLAYER_RIGHT__
#define __PLAYER_RIGHT__
#include "cocos2d.h"
#include "game/domian/HeadPortrait.h"
USING_NS_CC;

class PlayerRight : public Sprite{

public:
	virtual bool init();
	void drawHeadPortrait(HeadPortrait* headPortrait);
	CREATE_FUNC(PlayerRight);
};
#endif 