#include "config/ConfigManager.h"

#include "ConfigItem.h"
#include "config/ConfigVipLevel.h"
#include "config/ConfigTurrent.h"
#include "config/ConfigFish.h"
#include "config/ConfigRoom.h"

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
    ConfigItem::getInstance()->LoadConfig();
    ConfigVipLevel::getInstance()->LoadConfig();
    ConfigTurrent::getInstance()->LoadConfig();
    ConfigFish::getInstance()->LoadConfig();
    
//    ConfigRoom::getInstance()->LoadConfig();
}

