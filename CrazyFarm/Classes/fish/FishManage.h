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
	
	void createFishQueue(int fishId, int momentEightroutetag);///������  ͬ��������



	void createFishMonmentInterval(int fishid, int route, Vec2 startPos);

	void createFishMonmentInterval(int fishid,  Vec2 startPos,Vec2 endPos,float  movetime);



	void decideFishPos(Fish* fish);//������ĳ���λ��
	Vector<Fish*>& getAllFishInPool();
    int getAllFishInPoolCount();
	void removeFishWhichSwimOut();///�Ƴ���Ļ�����




	void createCycleFish(int count, int Radius, int fishID, Point center, Point curPos, float moveTime);//����һȦ��
	
    Point getBestRewardPostion();
    
	void UpdateWhenController(float dt);
	void UpdataCreateFish(float dt);
	void LoadOnement(Moment*monent);
	void onBoomFishDead(Fish*fish, PlayerTurret* pTurret);
	void onAllKilledFishDead(Fish*fish, PlayerTurret*pTurret);

	void onClearFish();   //�㳱���٣��峡


	Fish*getHignSoreInPool();//��÷�ֵ��ߵ���
	Fish*getFishByPosInPool(Point pos);//��õ������
	Fish*getLowDistanceInPool(Point pos);//��þ���ĳ���������
	Fish*getLowDistanceGoldFishInPool(Point pos);//��þ���ĳ������Ļƽ���
	//sever fish create design;
private:
	std::vector<MsgFishInfo> waitCreateFishes;
public:
	void addServerItemFishs(MsgFishInfo fishs);
	void clearServerItemFishs();
	void UpdateServerWhenController(float dt);
	void UpdataServerCreateFish(float dt);
	//������
public:
	void moveFishToCacheFromPool(Fish*fish);
private:
	Fish* getFreeFishInCache();
	Vector<Fish*> fishPool;//��Ļ�е���
	std::vector<Fish*> cacheFishPool; //û���õ�����ͨ��
private :
	FishManage();
	static FishManage* _instance;
	
	std::vector<MomentEightItemFishs> waitCreateMomentEightFishs;
	Moment* m_nowMonent = nullptr;
	CC_SYNTHESIZE(GameLayer*, m_layer, layer);
 };
#endif