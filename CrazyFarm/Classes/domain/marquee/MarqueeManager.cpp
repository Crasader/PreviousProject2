#include "domain/magnate/MagnateManager.h"

MagnateManager* MagnateManager::_instance = NULL;

MagnateManager::MagnateManager(){
    this->init();
}


void MagnateManager::init(){
    diamandConfig = ConfigMagnate::getInstance()->getDiamandMagnate();
    itemConfig = ConfigMagnate::getInstance()->getItemMagnate();
}

MagnateManager* MagnateManager::getInstance(){
    if(_instance == NULL){
        _instance = new MagnateManager();
    }
    return _instance;
}


MagnateEvent MagnateManager::getDiamandMagnateEvent(){
    MagnateEvent magnateEvent;
    magnateEvent.fireTimes = diamandConfig.fire_time_from +
            rand()%(diamandConfig.fire_time_to - diamandConfig.fire_time_from);
    magnateEvent.itemId = 1002;
    magnateEvent.num = 1;
    return magnateEvent;
}

MagnateEvent MagnateManager::getItemMagnateEvent(){
    MagnateEvent magnateEvent;
    magnateEvent.fireTimes = itemConfig.fire_time_from +
    rand()%(itemConfig.fire_time_to - itemConfig.fire_time_from);
    int random = rand()%100;
    if(random < 33) {
        magnateEvent.itemId = 1003;
    }else if(random < 66) {
        magnateEvent.itemId = 1004;
    }else {
        magnateEvent.itemId = 1005;
    }
    magnateEvent.num = 1;
    return magnateEvent;
}

void MagnateEvent::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}
	if (!response->isSucceed())
	{
		log("error buffer: %s", response->getErrorBuffer());
		bIsGetDataSuccess = false;
		return;
	}

	long statusCode = response->getResponseCode();
	char statusString[64] = {};
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());

	today = doc["today"].GetString();
	auto &itemlists = doc["item_lists"];
	for (size_t i = 0; i < itemlists.Size(); i++)
	{
		auto &dayrewards = itemlists[i];
		std::vector<SignRewardItem> temp;
		for (size_t j = 0; j < dayrewards.Size(); j++)
		{
			SignRewardItem item;
			item.probability = dayrewards[j]["probability"].GetInt();
			item.propNum = dayrewards[j]["num"].GetInt();
			item.propID = dayrewards[j]["item_id"].GetInt();
			temp.push_back(item);
		}
		dayToRewards[i + 1] = temp;
	}
	if (dayToRewards.size() == 7)
	{
		bIsGetDataSuccess = true;
	}
}
