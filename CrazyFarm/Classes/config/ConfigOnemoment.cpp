#include "config/ConfigOnemoment.h"

ConfigOnemoment* ConfigOnemoment::_instance = NULL;

ConfigOnemoment::ConfigOnemoment(){
}

ConfigOnemoment* ConfigOnemoment::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigOnemoment();
	}
	return _instance;
}

bool ConfigOnemoment::LoadConfig() {
    bool bRet = false;
    while (!bRet) {
        
        std::string filename = "config/config_onemoment_seq.json";
        rapidjson::Document doc;
        if (!FileUtils::getInstance()->isFileExist(filename))
        {
            break;
        }
        
        std::string data = FileUtils::getInstance()->getStringFromFile(filename);
        doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
        if (doc.HasParseError())
        {
            log("ConfigOnemoment config_onemoment_seq.json get json data err!");
            break;
        }
        
        rapidjson::Value& itemList = doc["item_list"];
        if (!itemList.IsArray())
        {
            log("ConfigOnemoment config_onemoment_seq.json The data is not json");
            break;
        }
        for (unsigned int i = 0; i < itemList.Size(); ++i) {
            const rapidjson::Value &val = itemList[i];
            OnemomentSeq onemomentSeq;
            onemomentSeq.config_file_name = val["config_file_name"].GetString();
            onemomentSeqs.push_back(onemomentSeq);
        }
        return true;
    }
    return true;

}

std::string ConfigOnemoment::getConfigFileName() {
    if(pos >= onemomentSeqs.size()) {
        pos = 0;
    }
    std::string filename = onemomentSeqs.at(pos).config_file_name;
    pos++;
    return filename;
}

OneMomentList ConfigOnemoment::loadOneMomentListConfig() {
    std::string filename = getConfigFileName();
    OneMomentList oneMomentList;
    
	bool bRet = false;
	while (!bRet) {
		
		rapidjson::Document doc;
		if (!FileUtils::getInstance()->isFileExist(filename))
		{
			break;
		}

		std::string data = FileUtils::getInstance()->getStringFromFile(filename);
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		if (doc.HasParseError())
		{
			log("ConfigOnemoment get json data err!");
			break;
		}
        oneMomentList.version = doc["version"].GetInt();
        oneMomentList.life_time = doc["life_time"].GetInt();
        
		rapidjson::Value& itemList = doc["item_list"];
		if (!itemList.IsArray())
		{
			log("ConfigOnemoment The data is not json");
				break;
		}
		for (unsigned int i = 0; i < itemList.Size(); ++i) {

			const rapidjson::Value &val = itemList[i];
            
			OneMoment oneMoment;
			oneMoment.fishgroup_id	= val["fishgroup_id"].GetInt();
            oneMoment.start_time = val["start_time"].GetDouble();
            oneMoment.end_time = val["end_time"].GetDouble();
            oneMoment.start_position_x = val["start_position_x"].GetInt();
            oneMoment.start_position_y = val["start_position_y"].GetInt();
            oneMoment.end_position_x = val["end_position_x"].GetInt();
            oneMoment.end_position_y = val["end_position_y"].GetInt();
            oneMoment.move_type = val["move_type"].GetInt();
			oneMoment.startAngle = val["star_angle"].GetDouble();
			oneMomentList.oneMoments.push_back(oneMoment);
		}
		
		return oneMomentList;
	}
    return oneMomentList;
}

