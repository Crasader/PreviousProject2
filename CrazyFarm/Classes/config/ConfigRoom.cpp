#include "config/ConfigRoom.h"

ConfigRoom* ConfigRoom::_instance = NULL;

ConfigRoom::ConfigRoom(){
}

ConfigRoom* ConfigRoom::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigRoom();
	}
	return _instance;
}

bool ConfigRoom::LoadConfig() {
    bool bRet = false;
    while (!bRet) {
        
        std::string filename = "config/config_room.json";
        rapidjson::Document doc;
        if (!FileUtils::getInstance()->isFileExist(filename))
        {
            break;
        }
        
        std::string data = FileUtils::getInstance()->getStringFromFile(filename);
        doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
        if (doc.HasParseError())
        {
            log("get json data err!");
            break;
        }
        rapidjson::Value& itemList = doc["item_list"];
        if (!itemList.IsArray())
        {
            log("The data is not json");
            break;
        }
        for (unsigned int i = 0; i < itemList.Size(); ++i) {
            
            const rapidjson::Value &val = itemList[i];
            Room room;
            room.room_id	= val["room_id"].GetInt();
            room.ui_id	= val["ui_id"].GetInt();
            room.unlock_turrent_level	= val["unlock_turrent_level"].GetInt();
            
            rooms[i] = room;
        }
        
        return true;
    }
    return true;
}

std::map<int, Room> ConfigRoom::getRooms() {
    return rooms;
}

