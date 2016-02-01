#include "config/ConfigMomentOrder.h"
#include "utill/JniFunUtill.h"
#include "ConfigDefine.h"
ConfigMomentOrder* ConfigMomentOrder::_instance = NULL;

ConfigMomentOrder::ConfigMomentOrder(){
}

ConfigMomentOrder* ConfigMomentOrder::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigMomentOrder();
	}
	return _instance;
}

std::vector<MomentOrderItem> ConfigMomentOrder::LoadConfig() {
    
	bool bRet = false;
	while (!bRet) {

        		std::string filename;	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
				if (ISDEBUGCONFIG)
				{	
					filename += JniFunUtill::getInstance()->getSDcardpath();
					filename += "/CrazyFarm/";
	}
#endif
		filename += "config/config_moment_order.json";
		rapidjson::Document doc;
		if (!FileUtils::getInstance()->isFileExist(filename))
		{
			break;
		}

		std::string data = FileUtils::getInstance()->getStringFromFile(filename);
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		if (doc.HasParseError())
		{
			log("ConfigMomentOrder get json data err!");
			break;
		}
		rapidjson::Value& itemList = doc["item_list"];
		if (!itemList.IsArray())
		{
			log("ConfigMomentOrder The data is not json");
				break;
		}
		for (unsigned int i = 0; i < itemList.Size(); i++) {
            MomentOrderItem momentOrderItem;
			const rapidjson::Value &orderItem = itemList[i];
            
            for (unsigned int j = 0; j < orderItem.Size(); j++) {
                const rapidjson::Value &val = orderItem[j];
                MomentOrderBaseItem momentOrderBaseItem;
                momentOrderBaseItem.moment_id = val["moment_id"].GetInt();
                momentOrderBaseItem.per = val["per"].GetInt();
                momentOrderItem.momentOrderBaseItems.push_back(momentOrderBaseItem);
            }
            momentOrderItems.push_back(momentOrderItem);
            
		}
		
		return momentOrderItems;
	}
    return momentOrderItems;
}

