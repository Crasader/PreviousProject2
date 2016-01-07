#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;

struct MomentOrder {
    int moment_id;
};


class ConfigMomentOrder {
    
public:
	ConfigMomentOrder();
	static ConfigMomentOrder* getInstance();
    
	std::map<int, MomentOrder> LoadConfig();

    
private:
	static ConfigMomentOrder* _instance;
    std::map<int, MomentOrder> momentOrders;
};

