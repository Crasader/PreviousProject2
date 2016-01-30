#include "config/ConfigTurrent.h"
#include "domain/user/User.h"
#include "utill/JniFunUtill.h"
ConfigTurrent* ConfigTurrent::_instance = NULL;

ConfigTurrent::ConfigTurrent(){
}

ConfigTurrent* ConfigTurrent::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigTurrent();
	}
	return _instance;
}

bool ConfigTurrent::LoadConfig() {
	bool bRet = false;
	while (!bRet) {
std::string filename;	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID&&configDEBUG) 
filename += JniFunUtill::getInstance()->getSDcardpath();
		filename += "/CrazyFarm/";
	#endif
		filename += "config/config_turrent.json";

		rapidjson::Document doc;
		if (!FileUtils::getInstance()->isFileExist(filename))
		{
			break;
		}

		std::string data = FileUtils::getInstance()->getStringFromFile(filename);
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		if (doc.HasParseError())
		{
			log("ConfigTurrent get json data err!");
			break;
		}
		rapidjson::Value & itemList = doc["item_list"];
		if (!itemList.IsArray())
		{
			log("ConfigTurrent The data is not json");
				break;
		}
		for (unsigned int i = 0; i < itemList.Size(); ++i) {
            
			rapidjson::Value &val = itemList[i];
			Turrent turrent;
			turrent.turrentId	= val["turrent_id"].GetInt();
            turrent.unlockType = val["unlock_type"].GetInt();
            turrent.unlockPrice = val["unlock_price"].GetInt();
            turrent.multiple = val["multiple"].GetInt();
            
            std::vector<Reward> rewardList;
            
            rapidjson::Value & rewards = val["reward_list"];

            for (unsigned int i = 0; i < rewards.Size(); ++i) {
                const rapidjson::Value &rewardConfig = rewards[i];
                Reward reward;
                reward.itemId = rewardConfig["item_id"].GetInt();
                reward.num = rewardConfig["num"].GetInt();
                rewardList.push_back(reward);
            }
            turrent.rewardList = rewardList;
			turrents.push_back(turrent);
		}
		
		return true;
	}
    return true;
}

std::vector<Turrent> ConfigTurrent::getTurrent() {
    return turrents;
}

Turrent ConfigTurrent::getTurrent(int turrentId) {
	for (int i = 0; i < turrents.size();i++)
	{
		if (turrents[i].turrentId == turrentId)
		{
			return turrents[i];
		}
	}
}

Turrent ConfigTurrent::getNextTurrent(int turrentId)
{
	for (int i = 0; i < turrents.size(); i++)
	{
		if (turrents[i].turrentId == turrentId)
		{
			if ((i + 1)<turrents.size())
			{
				return turrents[i+1];
			}
			else
			{
				return turrents[i];
			}
		}
	}
}
Turrent ConfigTurrent::getLastTurrent(int turrentId)
{
	for (int i = 0; i < turrents.size(); i++)
	{
		if (turrents[i].turrentId == turrentId)
		{
			if (i - 1 >= 0)
			{
				return turrents[i - 1];
			}
			else
			{
				Turrent turrent;
				turrent.turrentId = -1;
				return turrent;
			}
		}
	}
}


Turrent ConfigTurrent::getTurrentByIndex(int index)
{
	for (auto var:turrents)
	{
		if (var.turrentId == index)
		{
			return var;
		}
	}
	return Turrent();
}

std::vector<Turrent> ConfigTurrent::getUnUpgradeTurrents()
{
	std::vector<Turrent> vec;
	auto maxlv = User::getInstance()->getMaxTurrentLevel();
	for (auto var : turrents)
	{
		if (var.turrentId>maxlv)
		{
			vec.push_back(var);
		}
	}
	return vec;
}
