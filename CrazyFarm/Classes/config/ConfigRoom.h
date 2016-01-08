#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;

struct Room {
    int room_id;
    int ui_id;
    int unlock_turrent_level;
};


class ConfigRoom {
    
public:
	ConfigRoom();
	static ConfigRoom* getInstance();
    
	void LoadConfig();
    std::map<int, Room> getRooms();

    
private:
	static ConfigRoom* _instance;
    std::map<int, Room> rooms;
};

