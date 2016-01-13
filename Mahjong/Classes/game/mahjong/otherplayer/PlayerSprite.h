#ifndef __PLAYER_SPRITE__
#define __PLAYER_SPRITE__
#include "cocos2d.h"
#include "game/playerinfo/PlayerInfo.h"

USING_NS_CC;

class PlayerSprite:public Sprite{
public:
	virtual bool init();
	void drawHeadPortrait(PlayerInfo* playerInfo);
	void setHeadPostion(Point pos);
	CREATE_FUNC(PlayerSprite);
private:
	Sprite* head_bg;
	Label* nickName;
	Sprite* headimage;
	Sprite* diamond;
	LabelAtlas* diamondNum;
};
#endif