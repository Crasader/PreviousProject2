#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;


class ConfigVipLevel {
    
public:
	ConfigVipLevel();
	static ConfigVipLevel* getInstance();   
	bool LoadConfig();
private:
	static ConfigVipLevel* _instance;

};

