#include "domain/ranklist//RanklistManager.h"
#include "server/HttpClientUtill.h"
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
		rankItemsByExp.push_back(item);
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
		rankItemsByCoin.push_back(item);
	}
	bIsGetDataSuccess = true;
}
