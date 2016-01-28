#include "LogEventPageChange.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "server/HttpMannger.h"
LogEventPageChange* LogEventPageChange::_instance = NULL;

LogEventPageChange::LogEventPageChange(){
    
}

void LogEventPageChange::init(){
	items.clear();
}

LogEventPageChange* LogEventPageChange::getInstance(){
    if(_instance == NULL){
		_instance = new LogEventPageChange();
    }
    return _instance;
}



std::string LogEventPageChange::getDataForJson()
{

	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value array(rapidjson::kArrayType);

	for (auto var : items)
	{
		if (var.num<= 0)
		{
			continue;
		}
		rapidjson::Value object(rapidjson::kObjectType);
		object.AddMember("from_page", var.from_page, allocator);
		object.AddMember("to_page", var.to_page, allocator);
		object.AddMember("channel", var.channel, allocator);
		object.AddMember("nums", var.num, allocator);
		array.PushBack(object, allocator);
	}
	document.AddMember("pagechanges", array, allocator);
	document.AddMember("data_type", 6, allocator);

	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	std::string result = buffer.GetString();
	return result;
}

void LogEventPageChange::sendDataToServer()
{
	addEventItems(1, 2, 3);
	addEventItems(3, 2, 1);
	addEventItems(2, 2, 1);
	addEventItems(3, 2, 1);
	addEventItems(5, 1, 1);
	addEventItems(2, 1, 1);
	addEventItems(1, 3, 2);
	HttpMannger::getInstance()->HttpToPostRequestLogEvent(getDataForJson());
}

void LogEventPageChange::addEventItems(int from_page, int to_page, int channel)
{
	EventPageChange var;
	var.channel = channel;
	var.from_page = from_page;
	var.to_page = to_page;
	for (auto &var2:items)
	{
		if (var2.channel == var.channel&&var2.from_page == var.from_page&&var.to_page==var2.to_page)
		{
			var2.num++;
			return;
		}
	}
	var.num = 1;
	items.push_back(var);
}