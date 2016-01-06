#ifndef __PLAYER_OPPOSSITE__
#define __PLAYER_OPPOSSITE__
#include "cocos2d.h"
#include "game/domian/HeadPortrait.h"
USING_NS_CC;

class PlayerOpposite : public Sprite{

public:
	virtual bool init();
	void drawHeadPortrait(HeadPortrait* headPortrait);
	CREATE_FUNC(PlayerOpposite);
};
#endif 