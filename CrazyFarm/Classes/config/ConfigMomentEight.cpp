#include "config/ConfigMomentEight.h"
#include "utill/JniFunUtill.h"
#include "ConfigDefine.h"
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



std::vector<MomentEightItem> ConfigMomentEight::getMomentEightItemByTypeId(int typeId) {
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

		std::string filename;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (ISDEBUGCONFIG)
		{	
			filename += JniFunUtill::getInstance()->getSDcardpath();
			filename += "/CrazyFarm/";
		}
#endif
		filename += "config/config_eight_type1.json";
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
		lifetime = doc["life_time"].GetInt();
		auto &launching_points = doc["launching_points"];
		for (unsigned int i = 0; i < launching_points.Size(); i++)
		{
			MomentEightItem item;
			item.interval_time_start = launching_points[i]["interval_time_start"].GetDouble();
			item.interval_time_end = launching_points[i]["interval_time_end"].GetDouble();
			item.fish_startcount = launching_points[i]["count_start"].GetInt();
			item.fish_endcount = launching_points[i]["count_end"].GetInt();
			rapidjson::Value& itemList = launching_points[i]["item_list"];
			if (!itemList.IsArray())
			{
				log("ConfigMomentEight The data is not json");
				break;
			}
			for (unsigned int i = 0; i < itemList.Size(); ++i) {
				const rapidjson::Value &val = itemList[i];

				MomentEightItemPer itemper;
				itemper.fish_id = val["fish_id"].GetInt();
				itemper.per = val["per"].GetInt();
				if (val["fishRoute"].IsInt())
				{
					itemper.fishRoute = val["fishRoute"].GetInt();
				}

				item.momentEightItemPers.push_back(itemper);
			}
			momentEightItemType1.push_back(item);
		}


		return true;
	}
	return true;
}

bool ConfigMomentEight::LoadConfigType2() {
	bool bRet = false;
	while (!bRet) {

		std::string filename;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (ISDEBUGCONFIG)
		{	
			filename += JniFunUtill::getInstance()->getSDcardpath();
			filename += "/CrazyFarm/";
		}
#endif
		filename += "config/config_eight_type2.json";
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
		auto &launching_points = doc["launching_points"];
		for (unsigned int i = 0; i < launching_points.Size(); i++)
		{
			MomentEightItem item;
			item.interval_time_start = launching_points[i]["interval_time_start"].GetDouble();
			item.interval_time_end = launching_points[i]["interval_time_end"].GetDouble();
			item.fish_startcount = launching_points[i]["count_start"].GetInt();
			item.fish_endcount = launching_points[i]["count_end"].GetInt();
			rapidjson::Value& itemList = launching_points[i]["item_list"];
			if (!itemList.IsArray())
			{
				log("ConfigMomentEight The data is not json");
				break;
			}
			for (unsigned int i = 0; i < itemList.Size(); ++i) {
				const rapidjson::Value &val = itemList[i];

				MomentEightItemPer itemper;
				itemper.fish_id = val["fish_id"].GetInt();
				itemper.per = val["per"].GetInt();
				if (val["fishRoute"].IsInt())
				{
					itemper.fishRoute = val["fishRoute"].GetInt();
				}

				item.momentEightItemPers.push_back(itemper);
			}
			momentEightItemType2.push_back(item);
		}


		return true;
	}
	return true;
}

bool ConfigMomentEight::LoadConfigType3() {
	bool bRet = false;
	while (!bRet) {

		std::string filename;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (ISDEBUGCONFIG)
		{	
			filename += JniFunUtill::getInstance()->getSDcardpath();
			filename += "/CrazyFarm/";
		}
#endif
		filename += "config/config_eight_type3.json";
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
		auto &launching_points = doc["launching_points"];
		for (unsigned int i = 0; i < launching_points.Size(); i++)
		{
			MomentEightItem item;
			item.interval_time_start = launching_points[i]["interval_time_start"].GetDouble();
			item.interval_time_end = launching_points[i]["interval_time_end"].GetDouble();
			item.fish_startcount = launching_points[i]["count_start"].GetInt();
			item.fish_endcount = launching_points[i]["count_end"].GetInt();
			rapidjson::Value& itemList = launching_points[i]["item_list"];
			if (!itemList.IsArray())
			{
				log("ConfigMomentEight The data is not json");
				break;
			}
			for (unsigned int i = 0; i < itemList.Size(); ++i) {
				const rapidjson::Value &val = itemList[i];

				MomentEightItemPer itemper;
				itemper.fish_id = val["fish_id"].GetInt();
				itemper.per = val["per"].GetInt();
				if (val["fishRoute"].IsInt())
				{
					itemper.fishRoute = val["fishRoute"].GetInt();
				}

				item.momentEightItemPers.push_back(itemper);
			}
			momentEightItemType3.push_back(item);
		}


		return true;
	}
	return true;
}

bool ConfigMomentEight::LoadConfigType4() {
	bool bRet = false;
	while (!bRet) {

		std::string filename;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (ISDEBUGCONFIG)
		{	
			filename += JniFunUtill::getInstance()->getSDcardpath();
			filename += "/CrazyFarm/";
		}
#endif
		filename += "config/config_eight_type4.json";
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
			auto &launching_points = doc["launching_points"];
		for (unsigned int i = 0; i < launching_points.Size(); i++)
		{
			MomentEightItem item;
			item.interval_time_start = launching_points[i]["interval_time_start"].GetDouble();
			item.interval_time_end = launching_points[i]["interval_time_end"].GetDouble();
			item.fish_startcount = launching_points[i]["count_start"].GetInt();
			item.fish_endcount = launching_points[i]["count_end"].GetInt();
			rapidjson::Value& itemList = launching_points[i]["item_list"];
			if (!itemList.IsArray())
			{
				log("ConfigMomentEight The data is not json");
				break;
			}
			for (unsigned int i = 0; i < itemList.Size(); ++i) {
				const rapidjson::Value &val = itemList[i];

				MomentEightItemPer itemper;
				itemper.fish_id = val["fish_id"].GetInt();
				itemper.per = val["per"].GetInt();
				if (val["fishRoute"].IsInt())
				{
					itemper.fishRoute = val["fishRoute"].GetInt();
				}

				item.momentEightItemPers.push_back(itemper);
			}
			momentEightItemType4.push_back(item);
		}


		return true;
	}
	return true;
}


bool ConfigMomentEight::LoadConfigType5() {
	bool bRet = false;
	while (!bRet) {

		std::string filename;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (ISDEBUGCONFIG)
		{	
			filename += JniFunUtill::getInstance()->getSDcardpath();
			filename += "/CrazyFarm/";
		}
#endif
		filename += "config/config_eight_type5.json";
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
		auto &launching_points = doc["launching_points"];
		for (unsigned int i = 0; i < launching_points.Size(); i++)
		{
			MomentEightItem item;
			item.interval_time_start = launching_points[i]["interval_time_start"].GetDouble();
			item.interval_time_end = launching_points[i]["interval_time_end"].GetDouble();
			item.fish_startcount = launching_points[i]["count_start"].GetInt();
			item.fish_endcount = launching_points[i]["count_end"].GetInt();
			rapidjson::Value& itemList = launching_points[i]["item_list"];
			if (!itemList.IsArray())
			{
				log("ConfigMomentEight The data is not json");
				break;
			}
			for (unsigned int i = 0; i < itemList.Size(); ++i) {
				const rapidjson::Value &val = itemList[i];

				MomentEightItemPer itemper;
				itemper.fish_id = val["fish_id"].GetInt();
				itemper.per = val["per"].GetInt();
				if (val["fishRoute"].IsInt())
				{
					itemper.fishRoute = val["fishRoute"].GetInt();
				}

				item.momentEightItemPers.push_back(itemper);
			}
			momentEightItemType5.push_back(item);
		}


		return true;
	}
	return true;
}
