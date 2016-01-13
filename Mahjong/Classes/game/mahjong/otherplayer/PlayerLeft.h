#ifndef __PLAYER_LEFT__
#define __PLAYER_LEFT__
#include "cocos2d.h"
#include "game/playerinfo/PlayerInfo.h"
#include "game/mahjong/otherplayer/PlayerSprite.h"
USING_NS_CC;

class PlayerLeft :  public PlayerSprite{

public:
	virtual bool init();
	CREATE_FUNC(PlayerLeft);
private:
	const int jongNum = 13;
	void drawHandJong();//������ҵ�����
	void drawPlayedJong();//���ƴ��ȥ����
};
#endif 