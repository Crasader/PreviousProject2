#include "domain/bonuspool/BonusPoolManager.h"


BonusPoolManager* BonusPoolManager::_instance = NULL;

BonusPoolManager::BonusPoolManager(){
    this->init();
}


void BonusPoolManager::init(){
}

BonusPoolManager* BonusPoolManager::getInstance(){
    if(_instance == NULL){
        _instance = new BonusPoolManager();
    }
    return _instance;
}

int BonusPoolManager::getAllowCatchFishCounts(){
    return ConfigBonuspool::getInstance()->getBonuspool().allow_draw_fish_counts;
}

int BonusPoolManager::getCoins() {
    return UserDefault::getInstance()->getIntegerForKey(BonusPoolManager::KEY_BONUSPOOL_COINS, 0);
}

int BonusPoolManager::getFishCounts() {
    return UserDefault::getInstance()->getIntegerForKey(BonusPoolManager::KEY_BONUSPOOL_FISHCOUNTS, 0);
}

bool BonusPoolManager::addCoins(int coins) {
    if(coins > 0) {
        UserDefault::getInstance()->setIntegerForKey(BonusPoolManager::KEY_BONUSPOOL_COINS, getCoins() + coins);
        UserDefault::getInstance()->setIntegerForKey(BonusPoolManager::KEY_BONUSPOOL_FISHCOUNTS, getFishCounts() + 1);
        return true;
    }
    return false;

}

bool BonusPoolManager::cleanCoinsAndFishCounts() {
    UserDefault::getInstance()->setIntegerForKey(BonusPoolManager::KEY_BONUSPOOL_COINS, 0);
	UserDefault::getInstance()->setIntegerForKey(BonusPoolManager::KEY_BONUSPOOL_FISHCOUNTS, 0);
    return true;
}

bool BonusPoolManager::allowBonusPool() {
    if( getFishCounts() >= getAllowCatchFishCounts() ) {
        return true;
    }else {
        return false;
    }
}

BonuspoolResult BonusPoolManager::getBonuspoolResult() {
    BonuspoolResult bonuspoolResult; 
	int coins = getCoins();
    if(allowBonusPool()) {
      
        Bonuspool bonuspool = ConfigBonuspool::getInstance()->getBonuspool();
        for(int i=0; i < bonuspool.bonuspoolItems.size(); i++) {
            if( ( coins >= bonuspool.bonuspoolItems.at(i).start_coins ) &&
                    ( coins < bonuspool.bonuspoolItems.at(i).end_coins ) ) {
                bonuspoolResult.reward_list = bonuspool.bonuspoolItems.at(i).reward_list;
				int random = rand() % 100;
				int count = 0;
				for (int j = 0; j < bonuspoolResult.reward_list.size(); j++) {

				count += bonuspoolResult.reward_list.at(j).per;

				if (count >= random) {
					bonuspoolResult.reward_position = j;
					return bonuspoolResult;
				}
				}
            }
        }
    }
	else
	{
		Bonuspool bonuspool = ConfigBonuspool::getInstance()->getBonuspool();
		for (int i = 0; i < bonuspool.bonuspoolItems.size(); i++) {
			if (coins < bonuspool.bonuspoolItems.at(i).start_coins)
			{
				bonuspoolResult.reward_list = bonuspool.bonuspoolItems.at(i).reward_list; 
				bonuspoolResult.reward_position = 0;
				return bonuspoolResult;
			}
		}
	}
   
}

///TODO::缺少保护
BonuspoolItem*  BonusPoolManager::getNextBonuspool() {
	int coins = getCoins();
	Bonuspool bonuspool = ConfigBonuspool::getInstance()->getBonuspool();
	for (int i = 0; i < bonuspool.bonuspoolItems.size(); i++) {
		if ((coins >= bonuspool.bonuspoolItems.at(i).start_coins) &&
			(coins < bonuspool.bonuspoolItems.at(i).end_coins)) {

			if (i+1>=bonuspool.bonuspoolItems.size())
			{
				return nullptr;
			}
			else
			{
				return &bonuspool.bonuspoolItems.at(i + 1);
			}

		}
	}
}



int BonusPoolManager::getRewardByRandVec(std::vector<BonuspoolRewardItem> momentEightItemPers)
{
	std::vector<BonuspoolRewardItem> vec;
	vec.resize(momentEightItemPers.size());
	for (int i = 0; i < momentEightItemPers.size(); i++)
	{
		vec.at(i).item_id = momentEightItemPers[i].item_id;
		if (i == 0)
		{
			vec.at(0).per = 0;
		}
		else
		{
			for (int j = i; j >= 0; j--)
			{
				vec.at(i).per += momentEightItemPers[j].per;
			}
		}

	}
	///error: 概率算法有问题
	int randNum = rand() % 100 + 1;
	for (int i = 0; i<vec.size();i++)
	{
		if (randNum >vec.at(i).per)
		{
			return i;
		}
	}
	return -1;
}

