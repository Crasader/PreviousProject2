#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "HttpClientUtill.h"
USING_NS_CC;



struct SignRewardItem 
{
	int propID;
	int propNum;
	int probability;
};


class ConfigSign {
    
public:
	ConfigSign();
	static ConfigSign* getInstance();
   	bool LoadConfig();
	std::string getToday(){ return today; };
	std::vector<SignRewardItem> getRewardsByDay(int day);
	void onHttpRequestCompleted(HttpClient *sender, HttpResponse *response);
	bool isGetDataSuccess(){ return bIsGetDataSuccess; };
private:
	static ConfigSign* _instance;
	bool bIsGetDataSuccess = false;
	std::string today;
	std::map<int, std::vector<SignRewardItem>> dayToRewards;
};

