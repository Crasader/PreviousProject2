#include "config/ConfigFishCollisionRange.h"

ConfigFishCollisionRange* ConfigFishCollisionRange::_instance = NULL;

ConfigFishCollisionRange::ConfigFishCollisionRange(){

}

ConfigFishCollisionRange* ConfigFishCollisionRange::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigFishCollisionRange();
	}
	return _instance;
}

bool ConfigFishCollisionRange::LoadConfig() {
	bool bRet = false;
	
	while (!bRet) {

		std::string filename = "config/config_fishCollisionRange.json";
		rapidjson::Document doc;
		if (!FileUtils::getInstance()->isFileExist(filename))
		{
			break;
		}

		std::string data = FileUtils::getInstance()->getStringFromFile(filename);
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		if (doc.HasParseError())
		{
			log("ConfigFish get json data err!");
			break;
		}
		rapidjson::Value& itemList = doc["item_list"];
		if (!itemList.IsArray())
		{
			log("ConfigFish The data is not json");
				break;
		}
		for (unsigned int i = 0; i < itemList.Size(); ++i) {

			const rapidjson::Value &val = itemList[i];
			auto &figures = val["figures"];
			std::vector<CFigure*> vec;
			for (unsigned int i = 0; i < figures.Size();i++)
			{
				auto &figure = figures[i];
				if (figure["figureType"].GetInt() == 1)
				{
					vec.push_back(new CMyrect(Point(figure["origin"]["x"].GetDouble(), figure["origin"]["y"].GetDouble()), Size(figure["size"]["weith"].GetDouble(), figure["size"]["high"].GetDouble())));
				}
				else
				{
					vec.push_back(new CCircle(Point(figure["origin"]["x"].GetDouble(), figure["origin"]["y"].GetDouble()), figure["radius"].GetDouble()));
				}
			}
			uiidToFigures[val["fish_UiId"].GetInt()] = vec;
		}
		
		return true;
	}
    return true;
}


std::vector<CFigure*> ConfigFishCollisionRange::getFishFigures(int uiId)
{
	return uiidToFigures[uiId];
}
