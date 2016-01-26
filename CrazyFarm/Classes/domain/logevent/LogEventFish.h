#pragma once
#include "cocos2d.h"
using namespace cocos2d;


struct FishStatInfo
{
	int nFishID;
	int nCreateTimes;
	int nCatchTimes;
	int nHitTimes;
	int nUserCatchTimes;
	int nUserCostCoin;
};
struct FishEventData
{
	int room_id;
	std::vector<FishStatInfo> fishes;

};
class LogEventFish {

public:
	static LogEventFish* getInstance();
	void init(int roomid);
	void addFishCreateTimes(int fishid);
	void addFishCatchTimes(int fishid);
	void addFishHitTimes(int fishid);
	void addFishUserCatchTimes(int fishid);
	void addFishUserCostCoin(int fishid, int coin);
	void sendDataToServer();
private:
	LogEventFish();
	std::string getDataForJson();
	int m_roomid;
	std::vector<FishStatInfo> fishes;
	static LogEventFish* _instance;
};


