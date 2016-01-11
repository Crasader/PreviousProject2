#ifndef __MAHJONG_VIEW__
#define __MAHJONG_VIEW__
#include "cocos2d.h"
#include "game/headportrait/HeadPortrait.h"
#include "game/mahjong/Jong.h"
USING_NS_CC;
using namespace std;




class MahjongView : public cocos2d::Layer
{
public:
	virtual bool init();
	void drawPlayerHero();
	void drawPlayerLeft();
	void drawPlayerRight();
	void drawPlayerOpposite();
	void drawMenu();
	CREATE_FUNC(MahjongView);
private:
	void addTouchListener();//�����Ļ�Ĵ����¼�
	void addCoustomListener();//����Զ�������¼�
	void dealJongs();//����
	void chatButton();//���찴ť
	void billingButton();//�˵���ť
	void packageButton();//������ť
	//���Է���
	void testButton();
	void testEvent();

};
#endif