#include "config/ConfigSkill.h"

ConfigSkill* ConfigSkill::_instance = NULL;

ConfigSkill::ConfigSkill(){
}

ConfigSkill* ConfigSkill::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigSkill();
	}
	return _instance;
}

bool ConfigSkill::LoadConfig() {
	bool bRet = false;
	while (!bRet) {

		std::string filename = "config/config_skill.json";
		rapidjson::Document doc;
		if (!FileUtils::getInstance()->isFileExist(filename))
		{
			break;
		}

		std::string data = FileUtils::getInstance()->getStringFromFile(filename);
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		if (doc.HasParseError())
		{
			log("ConfigSkill get json data err!");
			break;
		}
		rapidjson::Value& itemList = doc["item_list"];
		if (!itemList.IsArray())
		{
			log("ConfigSkill The data is not json");
				break;
		}
		for (unsigned int i = 0; i < itemList.Size(); ++i) {
			const rapidjson::Value &val = itemList[i];
            
			SkillConfigInfo skillConfigInfo;
			skillConfigInfo.skill_id	= val["skill_id"].GetInt();
            skillConfigInfo.item_id	= val["item_id"].GetInt();
            skillConfigInfo.unlock_buy_type = val["unlock_buy_type"].GetInt();
            skillConfigInfo.unlock_buy_level = val["unlock_buy_level"].GetInt();
            skillConfigInfo.cd_time = val["cd_time"].GetInt();
            
            skillConfigInfos[i] = skillConfigInfo;
		}
		
		return true;
	}
    return true;
}

SkillConfigInfo ConfigSkill::getskillConfigInfoByItemId(int itemId) {
    for(int i=0; i< skillConfigInfos.size();i++) {
        if(skillConfigInfos[i].item_id == itemId) {
            return skillConfigInfos[i];
        }
    }
    return skillConfigInfos[0];
}

SkillConfigInfo ConfigSkill::getskillConfigInfoBySkillId(int skillId) {
    for(int i=0; i< skillConfigInfos.size();i++) {
        if(skillConfigInfos[i].skill_id == skillId) {
            return skillConfigInfos[i];
        }
    }
    return skillConfigInfos[0];
}


