#ifndef __JONG_H__
#define __JONG_H__
#include "cocos2d.h"
USING_NS_CC;

class Jong :public Node{
public:
	virtual bool init();
	void showJong(int bType,int cType);
	Rect getJongBoundingBox();
	CC_SYNTHESIZE(int, jongType, JongType);
	CC_SYNTHESIZE(int, bType, BType);
	CREATE_FUNC(Jong);
private:
	Sprite* content;
	Sprite* backGround;
	void drawContent(int cType);
	void drawBackGround(int bType);
	void setJongScale(int bType);
	void setJongPosition(int bType);
};


enum JongEnum
{
	wan_1 = 1, wan_2, wan_3, wan_4, wan_5, wan_6, wan_7, wan_8, wan_9,
	tong_1,tong_2,tong_3,tong_4,tong_5,tong_6,tong_7,tong_8,tong_9,
	tiao_1,tiao_2,tiao_3,tiao_4,tiao_5,tiao_6,tiao_7,tiao_8,tiao_9,
	east,south,west,north,zhong,fa,bai,
	spring, summer, autumn, winter, mei, lan, zhu, ju
};


//视觉类型
enum JongView
{
	hand,//手牌
	selfSmall,//自己打出的牌
	selfSpec//自己吃碰的牌
};

#endif