#include "PayUiConfig.h"
#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"



PayUiConfig* PayUiConfig::_instance = 0;
PayUiConfig::PayUiConfig(){

}
PayUiConfig* PayUiConfig::getInstance(){
	if (_instance == 0){
		_instance = new PayUiConfig();
	}
	return _instance;
}

bool PayUiConfig::LoadConfig()
{
	bool bRet = false;
	while (!bRet)
	{
		std::string filename = "pui/ppointui.json";
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
		////PayPoint ����
		unsigned int i;
		unsigned int j;
		rapidjson::Value& PayPoints = doc["ppoints"];
		if (!PayPoints.IsArray())
		{
			log("The data is not json");
			break;
		}
		for (  i = 0; i < PayPoints.Size(); ++i)
		{

			rapidjson::Value &val = PayPoints[i];
			int id = val["id"].GetInt();
			rapidjson::Value &elements = val["elements"];
			std::vector<ImageElement> vecImage;
			for ( j = 0; j < elements.Size(); ++j)
			{
				rapidjson::Value &elementj = elements[j];
				ImageElement element;

				if (elementj["defaultname"].IsString())
				{
					element.defaultname = elementj["defaultname"].GetString();
				}
				else
				{
					auto str = String::createWithFormat("id=%d�ĵ�%d��Ԫ���е� ����'defaultname' �����д��� ", i+1, j+1);
					log("%s",str->getCString());
				}

				if (elementj["specialname"].IsString())
				{
					element.specialname = elementj["specialname"].GetString();
				}
				else
				{
					auto str = String::createWithFormat("id=%d�ĵ�%d��Ԫ���е� ����'specialname' �����д��� ", i + 1, j + 1);
					log("%s",str->getCString());
				}

				if (elementj["type"].IsString())
				{
					element.type = elementj["type"].GetString();
				}
				else
				{
					auto str = String::createWithFormat("id=%d�ĵ�%d��Ԫ���е� ����'type' �����д��� ", i + 1, j + 1);
					log("%s",str->getCString());
				}
				if (elementj["width"].IsNumber())
				{
					element.width = elementj["width"].GetDouble();
				}
				else
				{
					auto str = String::createWithFormat("id=%d�ĵ�%d��Ԫ���е� ����'width' �����д��� ", i + 1, j + 1);
					log("%s",str->getCString());
				}

				if (elementj["height"].IsNumber())
				{
					element.height = elementj["height"].GetDouble();
				}
				else
				{
					auto str = String::createWithFormat("id=%d�ĵ�%d��Ԫ���е� ����'height' �����д��� ", i + 1, j + 1);
					log("%s",str->getCString());
				}


				if (elementj["x"].IsNumber())
				{
					element.xx = elementj["x"].GetDouble();
				}
				else
				{
					auto str = String::createWithFormat("id=%d�ĵ�%d��Ԫ���е� ����'x' �����д��� ", i + 1, j + 1);
					log("%s",str->getCString());
				}
				
				if (elementj["y"].IsNumber())
				{
					element.yy = elementj["y"].GetDouble();
				}
				else
				{
					auto str = String::createWithFormat("id=%d�ĵ�%d��Ԫ���е� ����'y' �����д��� ", i + 1, j + 1);
					log("%s",str->getCString());
				}
				vecImage.push_back(element);
			}
			PayUiPoints[id] = vecImage;
		}

		return true;
	}
}
std::vector<ImageElement>  PayUiConfig::getPayUiConfigByPoint(int point)
{
	return PayUiPoints[point];
}
