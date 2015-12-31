#include "config/ConfigFish.h"

ConfigFish* ConfigFish::_instance = NULL;

ConfigFish::ConfigFish(){
}

ConfigFish* ConfigFish::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigFish();
	}
	return _instance;
}

bool ConfigFish::LoadConfig() {
	bool bRet = false;
	while (!bRet) {

		std::string filename = "config/config_fish.json";
		rapidjson::Document doc;
		if (!FileUtils::getInstance()->isFileExist(filename))
		{
			break;
		}

		std::string data = FileUtils::getInstance()->getStringFromFile(filename);
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		if (doc.HasParseError())
		{
			log("get json data err!");
			break;
		}
		rapidjson::Value& itemList = doc["item_list"];
		if (!itemList.IsArray())
		{
			log("The data is not json");
				break;
		}
		for (unsigned int i = 0; i < itemList.Size(); ++i) {

			const rapidjson::Value &val = itemList[i];
            
			FishData fish;
			fish.fishId	= val["fish_id"].GetInt();
            fish.fishType = val["fish_type"].GetInt();
            fish.probability = val["probability"].GetDouble();
            fish.baseReward = val["baseReward"].GetInt();

			fishes[fish.fishId] = fish;
		}
		
		return true;
	}
    return true;
}


std::map<int, FishData> ConfigFish::getFishes() {
    return fishes;
}

FishData ConfigFish::getFish(int fishId) {
    return fishes[fishId];
}

