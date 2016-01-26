#include "LogEventFish.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "server/HttpMannger.h"
LogEventFish* LogEventFish::_instance = NULL;

LogEventFish::LogEventFish(){
    
}

void LogEventFish::init(int roomid){
	m_roomid = roomid;
	fishes.clear();
	for (int i = 1; i <= 10;i++)
	{
		FishStatInfo fishdata;
		fishdata.nCatchTimes = 0;
		fishdata.nCreateTimes = 0;
		fishdata.nFishID = i;
		fishdata.nHitTimes = 0;
		fishdata.nUserCatchTimes = 0;
		fishdata.nUserCostCoin = 0;
		fishes.push_back(fishdata);
	}
	for (int i = 30; i <= 37; i++)
	{
		FishStatInfo fishdata;
		fishdata.nCatchTimes = 0;
		fishdata.nCreateTimes = 0;
		fishdata.nFishID = i;
		fishdata.nHitTimes = 0;
		fishdata.nUserCatchTimes = 0;
		fishdata.nUserCostCoin = 0;
		fishes.push_back(fishdata);
	}
	for (int i = 40; i <= 44; i++)
	{
		FishStatInfo fishdata;
		fishdata.nCatchTimes = 0;
		fishdata.nCreateTimes = 0;
		fishdata.nFishID = i;
		fishdata.nHitTimes = 0;
		fishdata.nUserCatchTimes = 0;
		fishdata.nUserCostCoin = 0;
		fishes.push_back(fishdata);
	}
	for (int i = 50; i <= 52; i++)
	{
		FishStatInfo fishdata;
		fishdata.nCatchTimes = 0;
		fishdata.nCreateTimes = 0;
		fishdata.nFishID = i;
		fishdata.nHitTimes = 0;
		fishdata.nUserCatchTimes = 0;
		fishdata.nUserCostCoin = 0;
		fishes.push_back(fishdata);
	}
	for (int i = 101; i <= 104; i++)
	{
		FishStatInfo fishdata;
		fishdata.nCatchTimes = 0;
		fishdata.nCreateTimes = 0;
		fishdata.nFishID = i;
		fishdata.nHitTimes = 0;
		fishdata.nUserCatchTimes = 0;
		fishdata.nUserCostCoin = 0;
		fishes.push_back(fishdata);
	}
	for (int i = 201; i <= 201; i++)
	{
		FishStatInfo fishdata;
		fishdata.nCatchTimes = 0;
		fishdata.nCreateTimes = 0;
		fishdata.nFishID = i;
		fishdata.nHitTimes = 0;
		fishdata.nUserCatchTimes = 0;
		fishdata.nUserCostCoin = 0;
		fishes.push_back(fishdata);
	}

}

LogEventFish* LogEventFish::getInstance(){
    if(_instance == NULL){
		_instance = new LogEventFish();
    }
    return _instance;
}


void LogEventFish::addFishCreateTimes(int fishid)
{
	for (auto &var : fishes)
	{
		if (var.nFishID == fishid)
		{
			var.nCreateTimes++;
			return;
		}
	}
	return;
}
void LogEventFish::addFishCatchTimes(int fishid)
{
	for (auto &var : fishes)
	{
		if (var.nFishID == fishid)
		{
			var.nCatchTimes++;
			return;
		}
	}
	return;
}
void LogEventFish::addFishHitTimes(int fishid)
{
	for (auto& var : fishes)
	{
		if (var.nFishID == fishid)
		{
			var.nHitTimes++;
			return;
		}
	}
	return;
}
void LogEventFish::addFishUserCatchTimes(int fishid)
{
	for (auto &var : fishes)
	{
		if (var.nFishID == fishid)
		{
			var.nUserCatchTimes++;
			return;
		}
	}
	return;
}

void LogEventFish::addFishUserCostCoin(int fishid,int coin)
{
	for (auto &var : fishes)
	{
		if (var.nFishID == fishid)
		{
			var.nUserCostCoin += coin;
			return;
		}
	}
	return;
}
std::string LogEventFish::getDataForJson()
{

	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value array(rapidjson::kArrayType);
	
	for (auto var : fishes)
	{
		if (var.nCreateTimes<=0)
		{
			continue;
		}
		rapidjson::Value object(rapidjson::kObjectType);
		object.AddMember("fish_id", var.nFishID, allocator);
		object.AddMember("create_times", var.nCreateTimes, allocator);
		object.AddMember("hit_times", var.nHitTimes, allocator);
		object.AddMember("catch_times", var.nCatchTimes, allocator);
		object.AddMember("catch_times_user", var.nUserCatchTimes, allocator);
		object.AddMember("hit_moneys", var.nUserCostCoin, allocator);
		array.PushBack(object, allocator);
	}	
	document.AddMember("fishes", array, allocator);
	document.AddMember("room_id",m_roomid, allocator);
	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	std::string result = buffer.GetString();
	init(m_roomid);
	return result;
}

void LogEventFish::sendDataToServer()
{
	HttpMannger::getInstance()->HttpToPostRequestLogEvent(getDataForJson(),1);
}