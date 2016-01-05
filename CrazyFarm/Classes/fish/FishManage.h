#ifndef __FISHMANAGE_H__
#define __FISHMANAGE_H__

#include "cocos2d.h"
#include "fish/Fish.h"
using namespace cocos2d;

#define BORDER_LEFT 0
#define BORDER_TOP 1
#define BORDER_RIGHT 2
#define BORDER_BOTTOM 3

class FishManage {
public:
	static FishManage* getInstance();
	Fish* createFishSingle();
	Fish* createFishSingle(int type);
	Vector<Fish*> createFishGroup(int grouptag);
	void removeFish(Fish* fish);
	void decideFishPos(Fish* fish);//决定鱼的出生位置
	Vector<Fish*> getAllFishInPool();
	void removeFishWhichSwimOut();///移除屏幕外的鱼
private :
	FishManage();
	static FishManage* _instance;
	Vector<Fish*> fishPool;
 };
#endif