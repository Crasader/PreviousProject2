#ifndef __PLAYER_RIGHT__
#define __PLAYER_RIGHT__
#include "cocos2d.h"
#include "game/playerinfo/PlayerInfo.h"
#include "game/mahjong/player/base/PlayerBase.h"
#include "game/mahjong/Jong.h"
USING_NS_CC;

class PlayerRight : public PlayerBase{

public:

	virtual bool init();

	CREATE_FUNC(PlayerRight);

private:

	const int RIGHT_POS_X = 820;

	const int RIGHT_POS_Y = 475;

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