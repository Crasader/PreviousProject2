#ifndef __PLAYER_OPPOSSITE__
#define __PLAYER_OPPOSSITE__
#include "cocos2d.h"
#include "game/playerinfo/PlayerInfo.h"
#include "game/mahjong/player/base/PlayerBase.h"
#include "game/mahjong/Jong.h"
USING_NS_CC;

class PlayerOpposite : public PlayerBase{

public:
	virtual bool init();
	CREATE_FUNC(PlayerOpposite);

private:
	const int OPPOSITE_POS_X = 400;

	const int OPPOSITE_POS_Y = 510;

	int count;//���ȥ���Ƽ���

	void drawHandJong();//���������ҵ�����

	void drawPlayedJong(int ctype);//���ƴ��ȥ����

	void drawHuaJong(int cType);//���������ҵĻ���

	Point getPlayedJongPos();//��ȡ���ȥ���Ƶ�λ��

	void drawCurrent();//�Ŵ�ǰ�������

	void playerTurn();//�ֵ�����

	void addCoustomListener();//����Զ�������¼�
};
#endif 