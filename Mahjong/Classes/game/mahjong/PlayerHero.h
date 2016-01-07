#ifndef __PLAYER_HERO__
#define __PLAYER_HERO__
#include "cocos2d.h"
#include "game/headportrait/HeadPortrait.h"
#include "game/mahjong/Jong.h"
USING_NS_CC;
using namespace std;




class PlayerHero : public cocos2d::Layer
{
public:
	const int JONG_POS_Y = 100;
	const int JONG_SEL_POS_Y = 150;
	virtual bool init();
	bool onTouchBegan(Touch *touch, Event  *event);
	void onTouchMoved(Touch *touch, Event  *event);
	void onTouchEnded(Touch *touch, Event  *event);
	CREATE_FUNC(PlayerHero);
private:
	Vector<Jong*> selfHandJongs;//�Լ�������
	Vector<Jong*> selfSmallJongs;//�Լ��ĳ����ƶ�
	Vector<Jong*> selfSpecialJongs;//�Լ������ͳ��ƶ�
	Jong* selectJong;//ѡ�е���
	Jong* virtualJong;//����(�ֵ��Լ�����ʱ�Ż����)
	void drawPlayerHero();//�����Լ�
	void drawHeadPortrait(HeadPortrait* headPortrait);//����ͷ��
	void resetJongPos();//�ظ���ѡ���������Ƶ�λ��
	void resetAllJong();//�ظ������Ƶ�λ��
	float distance(Point pos1, Point pos2);//����2���ļ��
	Point getSmallJongsPos(int index);//��ô��ȥ���Ƶ�ͣ������
	Vector<Jong*>  sortJongs(Vector<Jong*> jongs);//�����ƽ�������
	Vector<Jong*>  upsetJongs(Vector<Jong*> jongs);//��������
	void addCoustomListener();//����Զ�������¼�
	void addTouchListener();//�����Ļ�Ĵ����¼�
};
#endif