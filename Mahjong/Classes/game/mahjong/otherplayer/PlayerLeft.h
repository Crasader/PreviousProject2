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
	const int LEFT_POS_X = 130;

	const int LEFT_POS_Y = 510;

	void drawHandJong();//������ҵ�����

	void drawPlayedJong();//���ƴ��ȥ����

	void getPlayedJongPos();//��ȡ���ȥ���Ƶ�λ��

	void drawCurrent();//�Ŵ�ǰ�������

};
#endif 