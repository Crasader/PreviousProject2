#include "config/ConfigExp.h"

using namespace cocos2d;

ConfigExp* ConfigExp::_instance = NULL;

ConfigExp::ConfigExp(){
}

ConfigExp* ConfigExp::getInstance(){
    if(_instance == NULL){
        _instance = new ConfigExp();
    }
    return _instance;
}

bool ConfigExp::LoadConfig() {
    bool bRet = false;
    while (!bRet) {
        
        std::string filename = "config/config_user_exp.json";
        rapidjson::Document doc;
        if (!FileUtils::getInstance()->isFileExist(filename))
        {
            break;
        }
        
        std::string data = FileUtils::getInstance()->getStringFromFile(filename);
        doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
        if (doc.HasParseError())
        {
            log("ConfigExp get json data err!");
            break;
        }
        rapidjson::Value& itemList = doc["item_list"];
        if (!itemList.IsArray())
        {
            log("ConfigExp The data is not json");
            break;
        }
        for (unsigned int i = 0; i < itemList.Size(); ++i) {
            
            const rapidjson::Value &val = itemList[i];
            LevelExp levelExp;
            levelExp.level_id	= val["level_id"].GetInt();
            levelExp.require_exp	= val["require_exp"].GetInt();
            
            levelExps.push_back(levelExp);
        }
        
        return true;
    }
    return true;
}



int ConfigExp::getLevelId(int exp) {
    for(int i = levelExps.size()-1; i>0; i--) {
        if(exp >= levelExps.at(i).require_exp ) {
            return levelExps.at(i).level_id;
        }
    }
    return 1;
}

int ConfigExp::getLevelExp(int levelId) {
    if(levelId <= 0) {
        return 0;
    }
    for(int i = 0; i<levelExps.size(); i++) {
        if(levelId == levelExps.at(i).level_id ) {
            return levelExps.at(i).require_exp;
        }
    }
    return 0;
}


LevelData ConfigExp::getLevelData(int exp) {
    LevelData levelData;
    levelData.levelId = getLevelId(exp);
    levelData.haveExp = exp - getLevelExp(levelData.levelId);
    levelData.passNeedExp = getLevelExp(levelData.levelId+1) - getLevelExp(levelData.levelId);
    return levelData;
}

