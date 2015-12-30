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

		std::string filename = "config/config_user_viplevel.json";
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
			VipLevel viplevel;
			viplevel.level	= val["vip_level"].GetInt();
            viplevel.chargeMoney = val["charge_money"].GetInt();
            viplevel.title = val["title"].GetString();
            viplevel.descTitle = val["desc_title"].GetString();
            viplevel.descContent = val["desc_content"].GetString();

			vipLevels[viplevel.level] = viplevel;
		}
		
		return true;
	}
    return true;
}

std::map<int, VipLevel> ConfigVipLevel::getVipLevels() {
    return vipLevels;
}

VipLevel ConfigVipLevel::getVipLevel(int level) {
    return vipLevels[level];
}

int ConfigVipLevel::getLevel(int chargeMoney) {
    if(chargeMoney <= 0) {
        return 0;
    }
    
    for( auto item = vipLevels.end(); item != vipLevels.begin(); item-- ) {
        if(chargeMoney > item->second.chargeMoney) {
            return item->second.level;
        }
    }
}
