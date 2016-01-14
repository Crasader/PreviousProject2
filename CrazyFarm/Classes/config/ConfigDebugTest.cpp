#include "config/ConfigDebugTest.h"
#include "User.h"

#include "AIManager.h"

ConfigDebugTest* ConfigDebugTest::_instance = NULL;

ConfigDebugTest::ConfigDebugTest(){
}

ConfigDebugTest* ConfigDebugTest::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigDebugTest();
	}
	return _instance;
}

bool ConfigDebugTest::LoadConfig() {
	bool bRet = false;
	while (!bRet) {

		std::string filename = "config/config_debug.json";
		rapidjson::Document doc;
		if (!FileUtils::getInstance()->isFileExist(filename))
		{
			break;
		}

		std::string data = FileUtils::getInstance()->getStringFromFile(filename);
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		if (doc.HasParseError())
		{
			log("ConfigDebugTest get json data err!");
			break;
		}
		
		auto isReset = doc["isResetData"].GetBool();
		if (isReset)
		{
			User::getInstance()->resetInfo();
            // TODO : 增加背包重置
            // TODO : 增加奖金池重置
		}
        bool ai_fire = doc["ai_fire"].GetBool();
        AIManager::getInstance()->setAiFire(ai_fire);
		
		return true;
	}
    return true;
}

