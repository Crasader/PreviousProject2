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
    
	bool LoadConfig();
	std::vector<Room> getRooms();
	Room getRoombyId(int nId);
    
    int getPlayerCounts(int currentHour, int roomId);
    
private:
	static ConfigRoom* _instance;
    std::vector<Room> rooms;
    
    int room1Players;
    int room2Players;
    int room3Players;
    int room4Players;
};

