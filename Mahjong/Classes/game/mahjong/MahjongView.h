#ifndef __MAHJONG_VIEW__
#define __MAHJONG_VIEW__
#include "cocos2d.h"
#include "game/domian/HeadPortrait.h"
#include "game/mahjong/Jong.h"
USING_NS_CC;
using namespace std;




class MahjongView : public cocos2d::Layer
{
public:
	const int JONG_POS_Y = 100;
	const int JONG_SEL_POS_Y = 150;
	virtual bool init();
	void drawPlayerSelf();
	void drawPlayerLeft();
	void drawPlayerRight();
	void drawPlayerOpposite();
	void drawHeadPortrait(HeadPortrait* headPortrait);
	bool onTouchBegan(Touch *touch, Event  *event);
	void onTouchMoved(Touch *touch, Event  *event);
	void onTouchEnded(Touch *touch, Event  *event);
	CREATE_FUNC(MahjongView);
private:
	Vector<Jong*> selfHandJongs;//�Լ�������
	Vector<Jong*> selfSmallJongs;//�Լ��ĳ����ƶ�
	Vector<Jong*> selfSpecialJongs;//�Լ������ͳ��ƶ�
	Jong* selectJong;//ѡ�е���
	Jong* virtualJong;//����(�ֵ��Լ�����ʱ�Ż����)
	void resetJongPos();//�ظ���ѡ���������Ƶ�λ��
	void resetAllJong();//�ظ������Ƶ�λ��
	float distance(Point pos1, Point pos2);
	Point smallJongsPos(int index);//��ô��ȥ���Ƶ�ͣ������
};
#endif