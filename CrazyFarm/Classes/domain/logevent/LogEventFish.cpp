#include "LogEventFish.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "server/HttpMannger.h"
#include "data/GameData.h"
LogEventFish* LogEventFish::_instance = NULL;

LogEventFish::LogEventFish(){
    
}

LogEventFish* LogEventFish::getInstance(){
    if(_instance == NULL){
		_instance = new LogEventFish();
    }
    return _instance;
}


void LogEventFish::addFishCreateTimes(int fishid)
{
	int roomid = GameData::getInstance()->getRoomID();
	auto str = String::createWithFormat("%d%d%s", roomid,fishid, FISHCREATETIME);
	auto localdata = UserDefault::getInstance();
	localdata->setIntegerForKey(str->getCString(), localdata->getIntegerForKey(str->getCString(), 0) + 1);
}
void LogEventFish::addFishCatchTimes(int fishid)
{
	int roomid = GameData::getInstance()->getRoomID();
	auto str = String::createWithFormat("%d%d%s", roomid,fishid, FISHCATCHTIME);
	auto localdata = UserDefault::getInstance();
	localdata->setIntegerForKey(str->getCString(), localdata->getIntegerForKey(str->getCString(), 0) + 1);
}
void LogEventFish::addFishHitTimes(int fishid)
{
	int roomid = GameData::getInstance()->getRoomID();
	auto str = String::createWithFormat("%d%d%s", roomid,fishid, FISHHITTIMES);
	auto localdata = UserDefault::getInstance();
	localdata->setIntegerForKey(str->getCString(), localdata->getIntegerForKey(str->getCString(), 0) + 1);
}
void LogEventFish::addFishUserCatchTimes(int fishid)
{
	int roomid = GameData::getInstance()->getRoomID();
	auto str = String::createWithFormat("%d%d%s", roomid,fishid, FISHUSERCATCHTIMES);
	auto localdata = UserDefault::getInstance();
	localdata->setIntegerForKey(str->getCString(), localdata->getIntegerForKey(str->getCString(), 0) + 1);
}

void LogEventFish::addFishUserCostCoin(int fishid, int coin)
{
	int roomid = GameData::getInstance()->getRoomID();
	auto str = String::createWithFormat("%d%d%s", roomid,fishid, FISHUSERCOSTCOIN);
	auto localdata = UserDefault::getInstance();
	localdata->setIntegerForKey(str->getCString(), localdata->getIntegerForKey(str->getCString(), 0) + 1);
}


void LogEventFish::loadLocalData()
{
	auto localdata = UserDefault::getInstance();
	for (int j = 1; j <= 4;j++)
	{
		FishEventData eventdata;
		eventdata.room_id = j;
		for (int i = 1; i <= 10; i++)
		{	
			FishStatInfo fishdata;
			fishdata.nFishID = i;

			auto str = String::createWithFormat("%d%d%s", j, i, FISHCATCHTIME);
			fishdata.nCatchTimes = localdata->getIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHCREATETIME);
			fishdata.nCreateTimes = localdata->getIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHHITTIMES);
			fishdata.nHitTimes = localdata->getIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHUSERCATCHTIMES);
			fishdata.nUserCatchTimes = localdata->getIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHUSERCOSTCOIN);
			fishdata.nUserCostCoin = localdata->getIntegerForKey(str->getCString(), 0);
			if (fishdata.nCreateTimes>0)
			{
				eventdata.fishes.push_back(fishdata);
			}
		}
		for (int i = 30; i <= 37; i++)
		{
			FishStatInfo fishdata;
			fishdata.nFishID = i;

			auto str = String::createWithFormat("%d%d%s", j, i, FISHCATCHTIME);
			fishdata.nCatchTimes = localdata->getIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHCREATETIME);
			fishdata.nCreateTimes = localdata->getIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHHITTIMES);
			fishdata.nHitTimes = localdata->getIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHUSERCATCHTIMES);
			fishdata.nUserCatchTimes = localdata->getIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHUSERCOSTCOIN);
			fishdata.nUserCostCoin = localdata->getIntegerForKey(str->getCString(), 0);
			if (fishdata.nCreateTimes > 0)
			{
				eventdata.fishes.push_back(fishdata);
			}
		}
		for (int i = 40; i <= 44; i++)
		{
			FishStatInfo fishdata;
			fishdata.nFishID = i;

			auto str = String::createWithFormat("%d%d%s", j, i, FISHCATCHTIME);
			fishdata.nCatchTimes = localdata->getIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHCREATETIME);
			fishdata.nCreateTimes = localdata->getIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHHITTIMES);
			fishdata.nHitTimes = localdata->getIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHUSERCATCHTIMES);
			fishdata.nUserCatchTimes = localdata->getIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHUSERCOSTCOIN);
			fishdata.nUserCostCoin = localdata->getIntegerForKey(str->getCString(), 0);
			if (fishdata.nCreateTimes > 0)
			{
				eventdata.fishes.push_back(fishdata);
			}
		}
		for (int i = 50; i <= 52; i++)
		{
			FishStatInfo fishdata;
			fishdata.nFishID = i;

			auto str = String::createWithFormat("%d%d%s", j, i, FISHCATCHTIME);
			fishdata.nCatchTimes = localdata->getIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHCREATETIME);
			fishdata.nCreateTimes = localdata->getIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHHITTIMES);
			fishdata.nHitTimes = localdata->getIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHUSERCATCHTIMES);
			fishdata.nUserCatchTimes = localdata->getIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHUSERCOSTCOIN);
			fishdata.nUserCostCoin = localdata->getIntegerForKey(str->getCString(), 0);
			if (fishdata.nCreateTimes > 0)
			{
				eventdata.fishes.push_back(fishdata);
			}
		}
		for (int i = 101; i <= 104; i++)
		{
			FishStatInfo fishdata;
			fishdata.nFishID = i;

			auto str = String::createWithFormat("%d%d%s", j, i, FISHCATCHTIME);
			fishdata.nCatchTimes = localdata->getIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHCREATETIME);
			fishdata.nCreateTimes = localdata->getIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHHITTIMES);
			fishdata.nHitTimes = localdata->getIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHUSERCATCHTIMES);
			fishdata.nUserCatchTimes = localdata->getIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHUSERCOSTCOIN);
			fishdata.nUserCostCoin = localdata->getIntegerForKey(str->getCString(), 0);
			if (fishdata.nCreateTimes > 0)
			{
				eventdata.fishes.push_back(fishdata);
			}
		}
		for (int i = 201; i <= 201; i++)
		{
			FishStatInfo fishdata;
			fishdata.nFishID = i;

			auto str = String::createWithFormat("%d%d%s", j, i, FISHCATCHTIME);
			fishdata.nCatchTimes = localdata->getIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHCREATETIME);
			fishdata.nCreateTimes = localdata->getIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHHITTIMES);
			fishdata.nHitTimes = localdata->getIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHUSERCATCHTIMES);
			fishdata.nUserCatchTimes = localdata->getIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHUSERCOSTCOIN);
			fishdata.nUserCostCoin = localdata->getIntegerForKey(str->getCString(), 0);
			if (fishdata.nCreateTimes > 0)
			{
				eventdata.fishes.push_back(fishdata);
			}
		}
		if (eventdata.fishes.size() > 0)
		{
			logEventFishes.push_back(eventdata);
		}

	}
}
std::string LogEventFish::getDataForJson(FishEventData data)
{
	auto fishes = data.fishes;
	auto m_roomid = data.room_id;
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
	document.AddMember("data_type", 1, allocator);
	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	std::string result = buffer.GetString();
	return result;
}

void LogEventFish::sendDataToServer()
{
	loadLocalData();
	for (auto var : logEventFishes)
	{
		HttpMannger::getInstance()->HttpToPostRequestLogEvent(getDataForJson(var),1);
	}
	logEventFishes.clear();
}


void LogEventFish::clearLocalData()
{
	auto localdata = UserDefault::getInstance();
	for (int j = 1; j <= 4; j++)
	{
		for (int i = 1; i <= 10; i++)
		{
			

			auto str = String::createWithFormat("%d%d%s", j, i, FISHCATCHTIME);
			localdata->setIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHCREATETIME);
			localdata->setIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHHITTIMES);
			localdata->setIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHUSERCATCHTIMES);
			localdata->setIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHUSERCOSTCOIN);
			localdata->setIntegerForKey(str->getCString(), 0);
	
		}
		for (int i = 30; i <= 37; i++)
		{

			auto str = String::createWithFormat("%d%d%s", j, i, FISHCATCHTIME);
			localdata->setIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHCREATETIME);
			localdata->setIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHHITTIMES);
			localdata->setIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHUSERCATCHTIMES);
			localdata->setIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHUSERCOSTCOIN);
			localdata->setIntegerForKey(str->getCString(), 0);
		}
		for (int i = 40; i <= 44; i++)
		{
			auto str = String::createWithFormat("%d%d%s", j, i, FISHCATCHTIME);
			localdata->setIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHCREATETIME);
			localdata->setIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHHITTIMES);
			localdata->setIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHUSERCATCHTIMES);
			localdata->setIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHUSERCOSTCOIN);
			localdata->setIntegerForKey(str->getCString(), 0);
		}
		for (int i = 50; i <= 52; i++)
		{
			auto str = String::createWithFormat("%d%d%s", j, i, FISHCATCHTIME);
			localdata->setIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHCREATETIME);
			localdata->setIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHHITTIMES);
			localdata->setIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHUSERCATCHTIMES);
			localdata->setIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHUSERCOSTCOIN);
			localdata->setIntegerForKey(str->getCString(), 0);
	
		}
		for (int i = 101; i <= 104; i++)
		{
			auto str = String::createWithFormat("%d%d%s", j, i, FISHCATCHTIME);
			localdata->setIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHCREATETIME);
			localdata->setIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHHITTIMES);
			localdata->setIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHUSERCATCHTIMES);
			localdata->setIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHUSERCOSTCOIN);
			localdata->setIntegerForKey(str->getCString(), 0);
		
		}
		for (int i = 201; i <= 201; i++)
		{
	
			auto str = String::createWithFormat("%d%d%s", j, i, FISHCATCHTIME);
			localdata->setIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHCREATETIME);
			localdata->setIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHHITTIMES);
			localdata->setIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHUSERCATCHTIMES);
			localdata->setIntegerForKey(str->getCString(), 0);

			str = String::createWithFormat("%d%d%s", j, i, FISHUSERCOSTCOIN);
			localdata->setIntegerForKey(str->getCString(), 0);
		
		}
	}
}