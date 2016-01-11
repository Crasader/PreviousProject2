#include "config/ConfigSign.h"

#define SIGNURL "http://114.119.39.150:1701/sign/config"
ConfigSign* ConfigSign::_instance = NULL;

ConfigSign::ConfigSign(){
}

ConfigSign* ConfigSign::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigSign();
	}
	return _instance;
}

bool ConfigSign::LoadConfig() {
	HttpClientUtill::getInstance()->onGetHttp(SIGNURL, CC_CALLBACK_2(ConfigSign::onHttpRequestCompleted,this));
	return true;
}


void ConfigSign::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
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
 
	today = doc["today"].GetString();
	auto &itemlists = doc["item_lists"];
	for (size_t i = 0; i < itemlists.Size(); i++)
	{
		auto &dayrewards = itemlists[i];
		std::vector<SignRewardItem> temp;
		for (size_t j = 0; j < dayrewards.Size();j++)
		{
			SignRewardItem item;
			item.probability = dayrewards[j]["probability"].GetInt();
			item.propNum = dayrewards[j]["num"].GetInt();
			item.propID = dayrewards[j]["item_id"].GetInt();
			temp.push_back(item);
		}
		dayToRewards[i + 1] = temp;
	}
	if (dayToRewards.size() == 7)
	{
		bIsGetDataSuccess = true;
	}	
}


std::vector<SignRewardItem> ConfigSign::getRewardsByDay(int day)
{
	return dayToRewards[day];
}