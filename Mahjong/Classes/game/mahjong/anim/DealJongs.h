#ifndef __DEAL_JONGS__
#define __DEAL_JONGS__
#include "cocos2d.h"
USING_NS_CC;

class DealJongs :public Layer{
public:
	virtual bool init();
	CREATE_FUNC(DealJongs);
	void showDealJong();
	void dealHero();//���Ƹ��Լ�
	void dealLeft();//���Ƹ���ߵ����
	void dealRight();//���Ƹ��ұߵ����
	void dealOpposite();//���Ƹ�����
};
#endif