#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;

struct VipLevel {
    int level;
    int chargeMoney;
    std::string title;
    std::string descTitle;
    std::string descContent;
};


class ConfigVipLevel {
    
public:
	ConfigVipLevel();
	static ConfigVipLevel* getInstance();
    
	bool LoadConfig();
    
	std::map<int, VipLevel> getVipLevels();
    VipLevel getVipLevel(int level);
    
    int getLevel(int chargeMoney);
    
private:
	static ConfigVipLevel* _instance;
	
    std::map<int, VipLevel> vipLevels;
};

