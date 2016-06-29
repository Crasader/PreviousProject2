#include "UiToPayConfig.h"
#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"



UiToPayConfig* UiToPayConfig::_instance = 0;
UiToPayConfig::UiToPayConfig(){

}
UiToPayConfig* UiToPayConfig::getInstance(){
	if (_instance == 0){
		_instance = new UiToPayConfig();
	}
	return _instance;
}

bool UiToPayConfig::LoadConfig()
{
	bool bRet = false;
	while (!bRet)
	{
		std::string filename = "pui/uitop.json";
		log("read json =%s",filename.c_str());
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
		////PayPoint ╪сть
		unsigned int i;
		unsigned int j;
		rapidjson::Value& uipoints = doc["uipoints"];
		if (!uipoints.IsArray())
		{
			log("The data is not json");
			break;
		}
		for (i = 0; i < uipoints.Size(); ++i)
		{
			UitopayData data;
			rapidjson::Value &val = uipoints[i];
			data.uiPoint = val["uipoint"].GetInt();
			data.pluginType = val["type"].GetString();
			data.payPoint = val["ppoint"].GetInt();
		}

		return true;
	}
}
int UiToPayConfig::getUiPointByPayPointAndPluginType(int point, std::string pluginType)
{
	for (auto var : _Uitopaydatas)
	{
		if (var.payPoint==point&&var.pluginType==pluginType)
		{
			return var.uiPoint;
		}
	}
	return -1;
}
