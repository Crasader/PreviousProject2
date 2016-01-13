#include "config/ConfigManager.h"

#include "ConfigItem.h"
#include "config/ConfigVipLevel.h"
#include "config/ConfigTurrent.h"
#include "config/ConfigFish.h"
#include "config/ConfigRoom.h"
#include "config/ConfigExp.h"
#include "config/ConfigVipTurrent.h"
#include "config/ConfigNormalTurrent.h"
#include "config/ConfigSkill.h"
#include "config/ConfigBankrupt.h"
#include "config/ConfigOnemoment.h"

ConfigManager* ConfigManager::_instance = NULL;

ConfigManager::ConfigManager(){
}

ConfigManager* ConfigManager::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigManager();
	}
	return _instance;
}

void ConfigManager::LoadConfig() {
    //load json
    ConfigExp::getInstance()->LoadConfig();
    
    ConfigItem::getInstance()->LoadConfig();
    ConfigVipLevel::getInstance()->LoadConfig();
    ConfigTurrent::getInstance()->LoadConfig();
    ConfigFish::getInstance()->LoadConfig();
    
    ConfigRoom::getInstance()->LoadConfig();
    ConfigVipTurrent::getInstance()->LoadConfig();
    ConfigNormalTurrent::getInstance()->LoadConfig();
    ConfigSkill::getInstance()->LoadConfig();
    ConfigBankrupt::getInstance()->LoadConfig();
    
    ConfigOnemoment::getInstance()->LoadConfig();
    
}


