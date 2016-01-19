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
	LoadConfigType1();
	LoadConfigType2();
	LoadConfigType3();
	LoadConfigType4();
	LoadConfigType5();
    return true;
}



MomentEightItem ConfigMomentEight::getMomentEightItemByTypeId(int typeId) {
	switch (typeId)
	{
	case 1:
		return momentEightItemType1;
		break;
	case 2:
		return momentEightItemType2;
		break;
	case 3:
		return momentEightItemType3;
		break;
	case 4:
		return momentEightItemType4;
		break;
	case 5:
		return momentEightItemType5;
		break;
	default:
		break;
	}
	return momentEightItemType1;
}

bool ConfigMomentEight::LoadConfigType1() {
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
        
        momentEightItemType1.life_time = doc["life_time"].GetInt();
        momentEightItemType1.interval_time_start = doc["interval_time_start"].GetDouble();
        momentEightItemType1.interval_time_end = doc["interval_time_end"].GetDouble();
        
        rapidjson::Value& itemList = doc["item_list"];
        if (!itemList.IsArray())
        {
            log("ConfigMomentEight The data is not json");
            break;
        }
        for (unsigned int i = 0; i < itemList.Size(); ++i) {
            const rapidjson::Value &val = itemList[i];
            
            MomentEightItemPer momentEightItemPer;
            momentEightItemPer.fish_id	= val["fish_id"].GetInt();
			momentEightItemPer.fish_startcount = val["count_start"].GetInt();
			momentEightItemPer.fish_endcount = val["count_end"].GetInt();
            momentEightItemPer.per = val["per"].GetInt();
            
            momentEightItemType1.momentEightItemPers.push_back(momentEightItemPer);
        }
        
        return true;
    }
    return true;
}

bool ConfigMomentEight::LoadConfigType2() {
    bool bRet = false;
    while (!bRet) {
        
        std::string filename = "config/config_eight_type2.json";
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
        
        momentEightItemType2.interval_time_start = doc["interval_time_start"].GetDouble();
        momentEightItemType2.interval_time_end = doc["interval_time_end"].GetDouble();
        
        rapidjson::Value& itemList = doc["item_list"];
        if (!itemList.IsArray())
        {
            log("ConfigMomentEight The data is not json");
            break;
        }
        for (unsigned int i = 0; i < itemList.Size(); ++i) {
            const rapidjson::Value &val = itemList[i];
            
            MomentEightItemPer momentEightItemPer;
            momentEightItemPer.fish_id	= val["fish_id"].GetInt();
			momentEightItemPer.fish_startcount = val["count_start"].GetInt();
			momentEightItemPer.fish_endcount = val["count_end"].GetInt();
            momentEightItemPer.per = val["per"].GetInt();
            
            momentEightItemType2.momentEightItemPers.push_back(momentEightItemPer);
        }
        
        return true;
    }
    return true;
}

bool ConfigMomentEight::LoadConfigType3() {
    bool bRet = false;
    while (!bRet) {
        
        std::string filename = "config/config_eight_type3.json";
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
        
        momentEightItemType3.interval_time_start = doc["interval_time_start"].GetDouble();
        momentEightItemType3.interval_time_end = doc["interval_time_end"].GetDouble();
        
        rapidjson::Value& itemList = doc["item_list"];
        if (!itemList.IsArray())
        {
            log("ConfigMomentEight The data is not json");
            break;
        }
        for (unsigned int i = 0; i < itemList.Size(); ++i) {
            const rapidjson::Value &val = itemList[i];
            
            MomentEightItemPer momentEightItemPer;
            momentEightItemPer.fish_id	= val["fish_id"].GetInt();
			momentEightItemPer.fish_startcount = val["count_start"].GetInt();
			momentEightItemPer.fish_endcount = val["count_end"].GetInt();
            momentEightItemPer.per = val["per"].GetInt();
            
            momentEightItemType3.momentEightItemPers.push_back(momentEightItemPer);
        }
        
        return true;
    }
    return true;
}

bool ConfigMomentEight::LoadConfigType4() {
	bool bRet = false;
	while (!bRet) {

		std::string filename = "config/config_eight_type4.json";
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

		momentEightItemType4.interval_time_start = doc["interval_time_start"].GetDouble();
		momentEightItemType4.interval_time_end = doc["interval_time_end"].GetDouble();

		rapidjson::Value& itemList = doc["item_list"];
		if (!itemList.IsArray())
		{
			log("ConfigMomentEight The data is not json");
			break;
		}
		for (unsigned int i = 0; i < itemList.Size(); ++i) {
			const rapidjson::Value &val = itemList[i];

			MomentEightItemPer momentEightItemPer;
			momentEightItemPer.fish_id = val["fish_id"].GetInt();
			momentEightItemPer.fish_startcount = val["count_start"].GetInt();
			momentEightItemPer.fish_endcount = val["count_end"].GetInt();
			momentEightItemPer.per = val["per"].GetInt();

			momentEightItemType4.momentEightItemPers.push_back(momentEightItemPer);
		}

		return true;
	}
	return true;
}


bool ConfigMomentEight::LoadConfigType5() {
	bool bRet = false;
	while (!bRet) {

		std::string filename = "config/config_eight_type5.json";
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

		momentEightItemType5.interval_time_start = doc["interval_time_start"].GetDouble();
		momentEightItemType5.interval_time_end = doc["interval_time_end"].GetDouble();

		rapidjson::Value& itemList = doc["item_list"];
		if (!itemList.IsArray())
		{
			log("ConfigMomentEight The data is not json");
			break;
		}
		for (unsigned int i = 0; i < itemList.Size(); ++i) {
			const rapidjson::Value &val = itemList[i];

			MomentEightItemPer momentEightItemPer;
			momentEightItemPer.fish_id = val["fish_id"].GetInt();
			momentEightItemPer.fish_startcount = val["count_start"].GetInt();
			momentEightItemPer.fish_endcount = val["count_end"].GetInt();
			momentEightItemPer.per = val["per"].GetInt();

			momentEightItemType5.momentEightItemPers.push_back(momentEightItemPer);
		}

		return true;
	}
	return true;
}
