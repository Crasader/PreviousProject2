#include "domain/gameConfig/gameConfig.h"
#include "utill/JniFunUtill.h"
#include "config/ConfigDefine.h"
GameConfig* GameConfig::_instance = NULL;

GameConfig::GameConfig(){
 ;
}

bool GameConfig::loadConfig(){
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
	filename += "config/config_game.json";
		rapidjson::Document doc;
		if (!FileUtils::getInstance()->isFileExist(filename))
		{
			break;
		}

		std::string data = FileUtils::getInstance()->getStringFromFile(filename);
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		if (doc.HasParseError())
		{
			log("ConfigRoom get json data err!");
			break;
		}
		rapidjson::Value& itemList = doc["shootList"];
		shootData.shootInterval = itemList["shootInterval"].GetDouble();
		shootData.shootSpeed = itemList["bulletSpeed"].GetInt();
		bRet = true;
	}
	return bRet;

}

GameConfig* GameConfig::getInstance(){
    if(_instance == NULL){
		_instance = new GameConfig();
    }
    return _instance;
}

