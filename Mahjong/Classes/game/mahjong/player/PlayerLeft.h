#ifndef __PLAYER_LEFT__
#define __PLAYER_LEFT__
#include "cocos2d.h"
#include "game/playerinfo/PlayerInfo.h"
#include "game/mahjong/player/base/PlayerBase.h"
#include "game/mahjong/Jong.h"
USING_NS_CC;

class PlayerLeft : public PlayerBase{

public:

	virtual bool init();

	CREATE_FUNC(PlayerLeft);

private:
	const int LEFT_POS_X = 130;

	const int LEFT_POS_Y = 510;

	int count;//���ȥ���Ƽ���

	void drawHandJong();//���������ҵ�����

	void drawPlayedJong(int ctype);//���ƴ��ȥ����

	void drawHuaJong();//���������ҵĻ���

	Point getPlayedJongPos();//��ȡ���ȥ���Ƶ�λ��

	void drawCurrent();//�Ŵ�ǰ�������

	void playerTurn();//�ֵ�����


	void addCoustomListener();//����Զ�������¼�

};
#endif 