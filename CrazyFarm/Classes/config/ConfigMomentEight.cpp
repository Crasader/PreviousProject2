#include "config/ConfigMomentEight.h"

ConfigMomentEight* ConfigMomentEight::_instance = NULL;

ConfigMomentEight::ConfigMomentEight(){
}

ConfigMomentEight* ConfigMomentEight::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigMomentEight();
	}
	return _instance;
}

bool ConfigMomentEight::LoadConfig() {
	bool bRet = false;
	while (!bRet) {

		std::string filename = "config/config_eight_type1.json";
		rapidjson::Document doc;
		if (!FileUtils::getInstance()->isFileExist(filename))
		{
			break;
		}

		std::string data = FileUtils::getInstance()->getStringFromFile(filename);
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		if (doc.HasParseError())
		{
			log("ConfigMomentEight get json data err!");
			break;
		}
        
        momentEightItem.life_time = doc["life_time"].GetInt();
        momentEightItem.interval_time_start = doc["interval_time_start"].GetDouble();
        momentEightItem.interval_time_end = doc["interval_time_end"].GetDouble();
        
		rapidjson::Value& itemList = doc["item_list"];
		if (!itemList.IsArray())
		{
			log("ConfigMomentEight The data is not json");
				break;
		}
		for (unsigned int i = 0; i < itemList.Size(); ++i) {
			const rapidjson::Value &val = itemList[i];
            
			MomentEightItemPer momentEightItemPer;
			momentEightItemPer.fish_id_start	= val["fish_id_start"].GetInt();
            momentEightItemPer.fish_id_end	= val["fish_id_end"].GetInt();
            momentEightItemPer.per = val["per"].GetInt();
            
            momentEightItem.momentEightItemPers.push_back(momentEightItemPer);
		}
		
		return true;
	}
    return true;
}

MomentEightItem ConfigMomentEight::getMomentEightItemByTypeId(int typeId) {
    return momentEightItem;
}


