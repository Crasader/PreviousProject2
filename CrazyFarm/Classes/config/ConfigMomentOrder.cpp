#include "config/ConfigMomentOrder.h"

ConfigMomentOrder* ConfigMomentOrder::_instance = NULL;

ConfigMomentOrder::ConfigMomentOrder(){
}

ConfigMomentOrder* ConfigMomentOrder::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigMomentOrder();
	}
	return _instance;
}

std::map<int, MomentOrder> ConfigMomentOrder::LoadConfig() {
    
	bool bRet = false;
	while (!bRet) {

        std::string filename = "config/config_moment_order.json";
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
            
			MomentOrder momentOrder;
			momentOrder.moment_id	= val["moment_id"].GetInt();
            
			momentOrders[i] = momentOrder;
		}
		
		return momentOrders;
	}
    return momentOrders;
}

