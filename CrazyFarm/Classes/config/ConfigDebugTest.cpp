#include "config/ConfigDebugTest.h"
#include "User.h"
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
			log("ConfigDebugTest get json data err!");
			break;
		}
		
		auto isReset = doc["isResetData"].GetBool();
		if (isReset)
		{
			User::getInstance()->resetInfo();
		}
		
		return true;
	}
    return true;
}

