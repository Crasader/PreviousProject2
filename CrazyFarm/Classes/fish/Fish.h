#ifndef __FISH_H__
#define __FISH_H__
#include "cocos2d.h"
#include "utill/CircleBy.h"
#include "config/ConfigFish.h"
using namespace cocos2d;

#define FISHTYPE_1 1
#define FISHTYPE_2 2
#define FISHTYPE_3 3
#define FISHTYPE_4 4
#define FISHTYPE_5 5
#define FISHTYPE_6 6
#define FISHTYPE_7 7
#define FISHTYPE_8 8

using namespace std;

class Fish :public Sprite{
public:
	virtual bool init();
	CREATE_FUNC(Fish);
	void initFish(int fishType);
	void move(int moveType);
	Sprite* getRectSprite();
	int getFishGold(){ return fishGold; }
	float getGrabProbability(){ return grabProbability; }
private:
	float grabProbability;
	int speed;//鱼的移动速度
	int fishType;//鱼的类型
	int experience;//鱼的经验值
	int fishGold;//鱼的金钱
	float  rotation;//旋转的角度
	string resoureName;//资源名称
	string getSrcByType(int type);
	int getFishGoldByType(int type);
	int getFishExperienceByType(int type);
	float getFishSpeedByType(int type);
	void initFishAnim(string name, int startIndex);
	void moveFishStraight(float dt);//直线移动
	void moveFishCircle(float dt);//圆周运动
	void moveFishRandom(float dt);//随机运动
	Point getNextPostion(Point pos,float speed,float degree);
	bool checkOutBorder();
	Sprite* image;
};

#endif