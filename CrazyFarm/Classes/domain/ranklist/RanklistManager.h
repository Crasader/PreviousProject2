#pragma once

#include "cocos2d.h"
#include "server/HttpClientUtill.h"
using namespace cocos2d;

struct rankListItem
{
	std::string name;
	int vipLevel;
	long int exp;
	long int coin;
	int gender;//ÐÔ±ð 0 ÄÐ 1Å®
};

struct  rankRange
{
	long int value_start;
	long int value_end;
	long int rank_start;
	long int rank_end;
};

class RanklistManager {

public:
	static RanklistManager* getInstance();
	void loadConfig();
	void onHttpRequestCompletedForCoin(HttpClient *sender, HttpResponse *response);
	void onHttpRequestCompletedForExp(HttpClient *sender, HttpResponse *response);
	std::vector<rankListItem > getCoinRankListData(){ return rankItemsByCoin; };
	std::vector<rankListItem > getExpRankListData(){ return rankItemsByExp; };
	bool IsSuccess(){ return bIsGetDataSuccess; };
	int getRankByCoin(int coin);
	int getRankByExp(int exp);
	int getRankByCoinForMyself(int coin);
private:
	RanklistManager();
	std::vector<rankListItem > rankItemsByCoin;
	std::vector<rankListItem > rankItemsByExp;
    std::vector<rankRange> rankCoinRange;
	std::vector<rankRange> rankExpRange;
	static RanklistManager* _instance;
	bool bIsGetDataSuccess = false;

    
};

