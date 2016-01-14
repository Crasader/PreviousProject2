#ifndef __PLAYER_BASE__
#define __PLAYER_BASE__
#include "cocos2d.h"
#include "game/playerinfo/PlayerInfo.h"

USING_NS_CC;

class PlayerBase :public Layer{
public:
	const int jongNum = 13;

	virtual bool init();

	void drawHeadPortrait(PlayerInfo* playerInfo);

	void setHeadPostion(Point pos);

	CREATE_FUNC(PlayerBase);
private:
	Sprite* head_bg;
	Label* nickName;
	Sprite* headimage;
	Sprite* diamond;
	LabelAtlas* diamondNum;
};
#endif