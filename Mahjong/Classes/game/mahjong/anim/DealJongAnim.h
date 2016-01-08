#ifndef __DEAL_JONG_ANIM__
#define __DEAL_JONG_ANIM__
#include "cocos2d.h"
USING_NS_CC;

class DealJongAnim :public Layer{
public:
	virtual bool init();
	CREATE_FUNC(DealJongAnim);
	void showDealJong();
	void dealHero();//���Ƹ��Լ�
	void dealLeft();//���Ƹ���ߵ����
	void dealRight();//���Ƹ��ұߵ����
	void dealOpposite();//���Ƹ�����
private:
	Point heroStarPos;//���Ƿ��Ƶĳ�ʼλ��
	Point leftStarPos;//��߷��Ƶĳ�ʼλ��
	Point rightStarPos;//�ұ߷��Ƶĳ�ʼλ��
	Point oppositeStarPos;//���淢�Ƶĳ�ʼλ��
	void initPosition();//��ʼ�����Ƶ���ʼ����
	Point caluMove2Pos(int type);//�����ƶѷ���������
};

enum Direction
{
	hero,
	left,
	right,
	opposite
};
#endif