#include "config/ConfigItem.h"

ConfigItem* ConfigItem::_instance = NULL;

ConfigItem::ConfigItem(){
}

ConfigItem* ConfigItem::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigItem();
	}
	return _instance;
}

bool ConfigItem::LoadConfig() {
	bool bRet = false;
	while (!bRet)
	{

		std::string filename = "config_item.json";
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
			Item item;
			item.itemId	= val["item_id"].GetInt();
            item.itemName = val["item_name"].GetString();
            item.itemDesc = val["item_desc"].GetString();
            item.buyType = val["buy_type"].GetInt();
            item.buyPrice = val["buy_price"].GetInt();

			items[item.itemId] = item;
		}
		
		return true;
	}
    return true;
}

Item ConfigItem::getItemById(int itemId) {
    return items[itemId];
}