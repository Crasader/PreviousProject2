#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;

struct MomentOrderBaseItem {
    int moment_id;
    int per;
};

struct MomentOrderItem {
    std::vector<MomentOrderBaseItem> momentOrderBaseItems;
};


class ConfigMomentOrder {
    
public:
	ConfigMomentOrder();
	static ConfigMomentOrder* getInstance();
    
	std::vector<MomentOrderItem> LoadConfig();

    
private:
	static ConfigMomentOrder* _instance;
    std::vector<MomentOrderItem> momentOrderItems;
};

