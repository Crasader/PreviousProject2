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
			viplevel.vip_level	= val["vip_level"].GetInt();
            viplevel.charge_money = val["charge_money"].GetInt();
            viplevel.title = val["title"].GetString();
            viplevel.desc_title = val["desc_title"].GetString();
            viplevel.desc_content = val["desc_content"].GetString();
            viplevel.vip_turrent_id = val["vip_turrent_id"].GetDouble();   // VIP炮ID
            viplevel.double_login_reward = val["double_login_reward"].GetDouble();  // 登陆奖励翻倍系�?
            viplevel.pay_reward = val["pay_reward"].GetDouble();          // 充值奖励百分比
            viplevel.kill_per_add = val["kill_per_add"].GetDouble();           // 击杀概率系数
            viplevel.send_coins_over = val["send_coins_over"].GetInt();         // 金币补足金额
            viplevel.send_coins_over_day_time = val["send_coins_over_day_time"].GetInt(); // 每日金币补足次数

			vipLevels[i] = viplevel;
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
    for( auto item = vipLevels.rbegin(); item != vipLevels.rend(); item++ ) {
        if(chargeMoney >= item->second.charge_money) {
            return item->second.vip_level;
        }
    }
}
