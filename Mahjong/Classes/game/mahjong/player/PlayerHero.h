#ifndef __PLAYER_HERO__
#define __PLAYER_HERO__
#include "cocos2d.h"
#include "game/playerinfo/PlayerInfo.h"
#include "game/mahjong/player/base/PlayerBase.h"
#include "game/mahjong/Jong.h"
USING_NS_CC;
using namespace std;




class PlayerHero : public PlayerBase
{
public:
	const int JONG_POS_Y = 90;
	const int JONG_SEL_POS_Y = 150;
	virtual bool init();
	bool onTouchBegan(Touch *touch, Event  *event);
	void onTouchMoved(Touch *touch, Event  *event);
	void onTouchEnded(Touch *touch, Event  *event);
	CREATE_FUNC(PlayerHero);
private:
	void initData();
	bool isAllowPlay;//�Ƿ��������
	Jong* currentJong;//��ǰ��õ���
	Vector<Jong*> selfHandJongs;//�Լ�������
	Vector<Jong*> selfSmallJongs;//�Լ��ĳ����ƶ�
	Vector<Jong*> selfSpecialJongs;//�Լ������ͳ��ƶ�
	Jong* selectJong;//ѡ�е���
	Jong* virtualJong;//����(�ֵ��Լ�����ʱ�Ż����)
	void drawPlayerHero();//�����Լ�
	void resetJongPos();//�ظ���ѡ���������Ƶ�λ��
	void resetAllJong();//�ظ������Ƶ�λ��
	float distance(Point pos1, Point pos2);//����2���ļ��
	Point getSmallJongsPos(int index);//��ô��ȥ���Ƶ�ͣ������
	Vector<Jong*>  sortJongs(Vector<Jong*> jongs);//�����ƽ�������
	Vector<Jong*>  upsetJongs(Vector<Jong*> jongs);//��������
	void addCoustomListener();//����Զ�������¼�
	void addTouchListener();//�����Ļ�Ĵ����¼�
	void reArrangeJongs();//����������
	void drawReady();
	void readyGo();//���׼��
	void drawActionCpg();//��,��,�ܰ�ť
	void actionCpg();//��,��,�ܲ���
};
#endif