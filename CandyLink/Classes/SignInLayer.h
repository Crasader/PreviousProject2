#ifndef __SIGNINLAYER_H__
#define __SIGNINLAYER_H__
#include "cocos2d.h"

USING_NS_CC;
////proptype  1��ʾ   2��ʱ    3����
////signtype  1����ǩ 2��ǩ��  3����ǩ
struct SignCellDate 
{
	int day;
	int proptype;
	int num;
	Point pos;
};

class SignInLayer : public Layer
{
public:
	void update(float dt);
	static SignInLayer* getInstance();
	virtual bool init();

	void geteveryGift(Ref* psender);
	bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	void hideSelf();
	void initsigndate();
	CREATE_FUNC(SignInLayer);

private:
	SignInLayer();
	int signDay;
	int refresh;
	int tip;
	int time;
	Sprite* background;
	int currentDay;
	std::vector<SignCellDate> cells;
	Size bgsize;
	static SignInLayer* _instance;
};


class SignCell : public Node
{
public:
	SignCell();
	virtual bool init(int day, int proptype, int propnum, int signtype);

	static SignCell* create(int day, int proptype, int propnum, int signtype);
	Sprite* bg;
	void SetBlind();

};

#endif