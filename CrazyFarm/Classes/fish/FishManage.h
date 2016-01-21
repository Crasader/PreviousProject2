#ifndef __FISHMANAGE_H__
#define __FISHMANAGE_H__

#include "cocos2d.h"
#include "fish/Fish.h"
#include "core/GameLayer.h"
#include "config/ConfigOnemoment.h"
#include "moment/Moment.h"
#include "moment/MomentManager.h"
#include "config/ConfigMomentEight.h"
#include "moment/MonmetEightRoute.h"
using namespace cocos2d;

#define BORDER_LEFT 0
#define BORDER_TOP 1
#define BORDER_RIGHT 2
#define BORDER_BOTTOM 3
class GameLayer;
class FishManage {
public:
	static FishManage* getInstance();
	void cleanVector();
	void createFishByEightMonment(MomentEightItemPer per);
	Fish* createFishSingle();
	Fish* createFishSingle(int type);
	void createFishGroup(int grouptag);
	Fish* createFishArrange(int type);
	void createFishRand(int fishId);
	void createFishArrangeRand(int fishId);

	void createFishAssign(int fishId, int momentEightroutetag);

	void removeFish(Fish* fish,bool);
	void decideFishPos(Fish* fish);//决定鱼的出生位置
	Vector<Fish*> getAllFishInPool();
    int getAllFishInPoolCount();
	void removeFishWhichSwimOut();///移除屏幕外的鱼




	void createCycleFish(int count, int Radius, int fishID, Point center, Point curPos, float moveTime);//建立一圈鱼
	Fish*getFishByPosInPool(Point pos);
    Point getBestRewardPostion();
    
	void UpdateWhenController(float dt);
	void LoadOnement();
	void createFishByOneMonet(OneMoment onemonent);
private :
	FishManage();
	static FishManage* _instance;
	Vector<Fish*> fishPool;
	Moment* m_nowMonent;
	CC_SYNTHESIZE(GameLayer*, m_layer, layer);
 };
#endif