#include "LogEventSpcEvent.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "server/HttpMannger.h"
LogEventSpcEvent* LogEventSpcEvent::_instance = NULL;

LogEventSpcEvent::LogEventSpcEvent(){
    
}

void LogEventSpcEvent::init(){

}

LogEventSpcEvent* LogEventSpcEvent::getInstance(){
    if(_instance == NULL){
		_instance = new LogEventSpcEvent();
    }
    return _instance;
}



std::string LogEventSpcEvent::getDataForJson()
{

	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value array(rapidjson::kArrayType);

	for (auto var : datas)
	{
		if (var.nums<= 0)
		{
			continue;
		}
		rapidjson::Value object(rapidjson::kObjectType);
		object.AddMember("event_desc", var.event_desc, allocator);
		object.AddMember("event_id", var.event_id, allocator);
		object.AddMember("nums", var.nums, allocator);
		array.PushBack(object, allocator);
	}
	document.AddMember("events", array, allocator);
	document.AddMember("data_type", 7, allocator);

	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	std::string result = buffer.GetString();
	return result;
}

void LogEventSpcEvent::sendDataToServer()
{
	addEventItems(1, 2);
	addEventItems(3, 2);
	addEventItems(2, 2);
	addEventItems(3, 2);
	addEventItems(5, 1);
	addEventItems(2, 1);
	addEventItems(1, 3);
	HttpMannger::getInstance()->HttpToPostRequestLogEvent(getDataForJson());
}

void LogEventSpcEvent::addEventItems(int event_id, int event_desc)
{
	SpcEvent var;
	var.event_id = event_id;
	var.event_desc = event_desc;
	for (auto &var2:datas)
	{
		if (var2.event_id == var.event_id&&var2.event_desc == var.event_desc)
		{
			var2.nums++;
			return;
		}
	}
	var.nums = 1;
	datas.push_back(var);
}