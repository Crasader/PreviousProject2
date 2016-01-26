#include "LogEventUseSkill.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "server/HttpMannger.h"
LogEventUseSkill* LogEventUseSkill::_instance = NULL;

LogEventUseSkill::LogEventUseSkill(){
    
}

void LogEventUseSkill::init(){
	items.clear();
}

LogEventUseSkill* LogEventUseSkill::getInstance(){
    if(_instance == NULL){
		_instance = new LogEventUseSkill();
    }
    return _instance;
}



std::string LogEventUseSkill::getDataForJson()
{
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value array(rapidjson::kArrayType);

	for (auto var : items)
	{
		if (var.nums <= 0)
		{
			continue;
		}
		rapidjson::Value object(rapidjson::kObjectType);
		object.AddMember("skill_id", var.skillID, allocator);
		object.AddMember("type", var.type, allocator);
		object.AddMember("price", var.prices, allocator);
		object.AddMember("nums", var.nums, allocator);
		array.PushBack(object, allocator);
	}
	document.AddMember("skills", array, allocator);
	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	std::string result = buffer.GetString();
	init();
	return result;
}

void LogEventUseSkill::sendDataToServer()
{
	HttpMannger::getInstance()->HttpToPostRequestLogEvent(getDataForJson(),5);
}
void LogEventUseSkill::addUseSkillData(int skillID, int type, int prices)
{

	for (auto &var:items)
	{
		if (var.skillID == skillID&&var.prices == prices&&var.type==type)
		{
			var.nums++;
			var.prices += prices;
			return;
		}
	}
		EventSkillCell item;
		item.skillID = skillID;
		item.prices = prices;
		item.nums = 1;
		item.type = type;
		items.push_back(item);

}
