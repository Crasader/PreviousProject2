#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;

struct OneMoment {
    int fishgroup_id;
    double start_time;
    double end_time;
    int start_position_x;
    int start_position_y;
    int end_position_x;
    int end_position_y;
    int move_type;
//  TODO : wait impl move_parameter read
};


class ConfigOnemoment {
    
public:
	ConfigOnemoment();
	static ConfigOnemoment* getInstance();
    
	std::map<int, OneMoment> LoadConfig(std::string filename);

    
private:
	static ConfigOnemoment* _instance;
};

