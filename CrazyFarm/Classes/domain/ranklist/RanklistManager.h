#pragma once

#include "cocos2d.h"
#include "server/HttpClientUtill.h"
using namespace cocos2d;

struct rankListItem
{
	std::string name;
	int vipLevel;
	double exp;
	double coin;
};

struct  rankRange
{
	int value_start;
	int value_end;
	int rank_start;
	int rank_end;
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
private:
	RanklistManager();
	std::vector<rankListItem > rankItemsByCoin;
	std::vector<rankListItem > rankItemsByExp;
	rankRange rankCoinRange;
	rankRange rankExpRange;
	static RanklistManager* _instance;
	bool bIsGetDataSuccess = false;

    
};

