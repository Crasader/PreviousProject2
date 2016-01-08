#include "config/ConfigVipLevel.h"

ConfigVipLevel* ConfigVipLevel::_instance = NULL;

ConfigVipLevel::ConfigVipLevel(){
}

ConfigVipLevel* ConfigVipLevel::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigVipLevel();
	}
	return _instance;
}

bool ConfigVipLevel::LoadConfig() {
	bool bRet = false;
	while (!bRet) {

		std::string filename = "config/config_debugTest.json";
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
		
		auto isReset = doc["isResetData"].GetBool();
		if (isReset)
		{
			UserDefault::getInstance()->
		}
		
		return true;
	}
    return true;
}

