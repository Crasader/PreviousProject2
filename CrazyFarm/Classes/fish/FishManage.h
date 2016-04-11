#ifndef __FISHMANAGE_H__
#define __FISHMANAGE_H__

#include "cocos2d.h"
#include "fish/Fish.h"
#include "core/GameLayer.h"
#include "moment/Moment.h"
#include "moment/MomentManager.h"
#include "config/ConfigMomentEight.h"
#include "moment/MonmetEightRoute.h"
#include "turret/PlayerTurret.h"
#include "fish/FishOfAllKilled.h"
using namespace cocos2d;

#define BORDER_LEFT 0
#define BORDER_TOP 1
#define BORDER_RIGHT 2
#define BORDER_BOTTOM 3
class GameLayer;
class FishManage {
public:
	static FishManage* getInstance();
	bool initFishPool();
	void cleanVector();



	void addMomentEightItemFishs(MomentEightItemFishs fishs);
	void clearMomentEightItemFishs();
	Fish* createFishSingle();
	Fish* createFishSingle(int type);
	void createFishGroup(int grouptag);
	Fish* createFishArrange(int type);
	void createFishRand(int fishId);
	void createFishArrangeRand(int fishId);
	void createFishAssign(int fishId, int momentEightroutetag);
	
	void createFishQueue(int fishId, int momentEightroutetag);///队列鱼  同生不共死



	void createFishMonmentInterval(int fishid, int route, Vec2 startPos);

	void createFishMonmentInterval(int fishid,  Vec2 startPos,Vec2 endPos,float  movetime);



	void decideFishPos(Fish* fish);//决定鱼的出生位置
	Vector<Fish*>& getAllFishInPool();
    int getAllFishInPoolCount();
	void removeFishWhichSwimOut();///移除屏幕外的鱼




	void createCycleFish(int count, int Radius, int fishID, Point center, Point curPos, float moveTime);//建立一圈鱼
	
    Point getBestRewardPostion();
    
	void UpdateWhenController(float dt);
	void UpdataCreateFish(float dt);
	void LoadOnement(Moment*monent);
	void onBoomFishDead(Fish*fish, PlayerTurret* pTurret);
	void onAllKilledFishDead(Fish*fish, PlayerTurret*pTurret);

	void onClearFish();   //鱼潮来临，清场


	Fish*getHignSoreInPool();//获得分值最高的鱼
	Fish*getFishByPosInPool(Point pos);//获得点击的鱼
	Fish*getLowDistanceInPool(Point pos);//获得距离某点最近的鱼
	Fish*getLowDistanceGoldFishInPool(Point pos);//获得距离某点最近的黄金鱼
	//sever fish create design;
private:
	std::vector<MsgFishInfo> waitCreateFishes;
public:
	void addServerItemFishs(MsgFishInfo fishs);
	void clearServerItemFishs();
	void UpdateServerWhenController(float dt);
	void UpdataServerCreateFish(float dt);
	//鱼对象池
public:
	void moveFishToCacheFromPool(Fish*fish);
private:
	Fish* getFreeFishInCache();
	Vector<Fish*> fishPool;//屏幕中的鱼
	std::vector<Fish*> cacheFishPool; //没有用到的普通鱼
private :
	FishManage();
	static FishManage* _instance;
	
	std::vector<MomentEightItemFishs> waitCreateMomentEightFishs;
	Moment* m_nowMonent = nullptr;
	CC_SYNTHESIZE(GameLayer*, m_layer, layer);
 };
#endif