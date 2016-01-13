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
			log("ConfigFish get json data err!");
			break;
		}
		rapidjson::Value& itemList = doc["item_list"];
		if (!itemList.IsArray())
		{
			log("ConfigFish The data is not json");
				break;
		}
		for (unsigned int i = 0; i < itemList.Size(); ++i) {

			const rapidjson::Value &val = itemList[i];
            
			FishData fish;
			fish.fishId	= val["fish_id"].GetInt();
            fish.fishType = val["fish_type"].GetInt();
            fish.move_speed = val["move_speed"].GetInt();
            fish.probability = val["probability"].GetDouble();
            fish.baseReward = val["baseReward"].GetInt();
            fish.maxHitTime = val["maxHitTime"].GetInt();
            fish.protectedTime = val["protectedTime"].GetInt();
            fish.uiId = val["ui_id"].GetInt();
            fish.catch_ui_type = val["catch_ui_type"].GetInt();
            fish.exp = val["exp"].GetInt();
            fish.be_hit_logic = val["be_hit_logic"].GetInt();
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

