#include "domain/ranklist//RanklistManager.h"
#include "server/HttpClientUtill.h"
#include "utill/FunUtil.h"
#include "domain/user/User.h"
#define RANKLISTINCOIN "http://114.119.39.150:1701/player/rank/coin"
#define RANKLISTINEXP "http://114.119.39.150:1701/player/rank/exp"
RanklistManager* RanklistManager::_instance = NULL;

RanklistManager::RanklistManager(){

}
RanklistManager* RanklistManager::getInstance(){
    if(_instance == NULL){
		_instance = new RanklistManager();
    }
    return _instance;
}
void RanklistManager::loadConfig()
{
	bIsGetDataSuccess = false;
	HttpClientUtill::getInstance()->onGetHttp(RANKLISTINCOIN, CC_CALLBACK_2(RanklistManager::onHttpRequestCompletedForCoin,this));
	HttpClientUtill::getInstance()->onGetHttp(RANKLISTINEXP, CC_CALLBACK_2(RanklistManager::onHttpRequestCompletedForExp,this));
}



void RanklistManager::onHttpRequestCompletedForExp(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}
	if (!response->isSucceed())
	{
		log("error buffer: %s", response->getErrorBuffer());
		bIsGetDataSuccess = false;
		return;
	}

	long statusCode = response->getResponseCode();
	char statusString[64] = {};
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
	auto &vec = doc["ranklist"];
	for (unsigned int i = 0; i < vec.Size(); i++)
	{
		rankListItem item;
		item.name = vec[i]["name"].GetString();
		item.vipLevel = vec[i]["vip"].GetInt(); 
		item.exp = vec[i]["exp"].GetDouble();
		item.coin = vec[i]["coins"].GetDouble();
		item.gender = vec[i]["gender"].GetInt();
		rankItemsByExp.push_back(item);
	}
	vec = doc["rankrule"];
	for (unsigned int i = 0; i < vec.Size(); i++)
	{
		rankRange item;
		item.rank_start = vec[i]["rank_start"].GetDouble();
		item.rank_end = vec[i]["rank_end"].GetDouble();
		item.value_start = vec[i]["coin_start"].GetDouble();
		item.value_end = vec[i]["coin_end"].GetDouble();
		rankExpRange.push_back(item);
	}
	bIsGetDataSuccess = true;
	
}

void RanklistManager::onHttpRequestCompletedForCoin(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}
	if (!response->isSucceed())
	{
		log("error buffer: %s", response->getErrorBuffer());
		bIsGetDataSuccess = false;
		return;
	}

	long statusCode = response->getResponseCode();
	char statusString[64] = {};
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
	auto &vec = doc["ranklist"];
	for (unsigned int i = 0; i < vec.Size(); i++)
	{
		rankListItem item;
		item.name = vec[i]["name"].GetString();
		item.vipLevel = vec[i]["vip"].GetInt();
		item.exp = vec[i]["exp"].GetDouble();
		item.coin = vec[i]["coins"].GetDouble();
		item.gender = vec[i]["gender"].GetInt();
		rankItemsByCoin.push_back(item);
	}
	vec = doc["rankrule"];
	for (unsigned int i = 0; i < vec.Size(); i++)
	{
		rankRange item;
		item.rank_start = vec[i]["rank_start"].GetDouble();
		item.rank_end = vec[i]["rank_end"].GetDouble();
		item.value_start = vec[i]["coin_start"].GetDouble();
		item.value_end = vec[i]["coin_end"].GetDouble();
		rankCoinRange.push_back(item);
	}
	bIsGetDataSuccess = true;
}
int RanklistManager::getRankByCoinForMyself(int coin)
{
	
	return getRankByCoin(coin);
}

int RanklistManager::getRankByCoin(int coin)
{
	///如果下达排行榜中有自己
	auto name = User::getInstance()->getUserName();
	for (int i = 0; i < rankItemsByCoin.size(); i++)
	{
		if (!rankItemsByCoin[i].name.compare(name))
		{
			return i+1;
		}
	}
	//没自己
	rankRange range;
    for (auto var:rankCoinRange)
    {
		if (coin>=var.value_start&&coin<=var.value_end)
		{
			range = var;
			break;
		}
    }
	return getCurrencyRankByRange(range.rank_start, range.rank_end, range.value_start, range.value_end, coin);

}
int RanklistManager::getRankByExp(int exp)
{
	///如果下达排行榜中有自己
	auto name = User::getInstance()->getUserName();
	for (int i = 0; i < rankItemsByExp.size(); i++)
	{
		if (!rankItemsByExp[i].name.compare(name))
		{
			return i+1;
		}
	}
	///没自己
	rankRange range;
	for (auto var : rankExpRange)
	{
		if (exp >= var.value_start&&exp <= var.value_end)
		{
			range = var;
			break;
		}
	}
	return getCurrencyRankByRange(range.rank_start, range.rank_end, range.value_start, range.value_end, exp);
}