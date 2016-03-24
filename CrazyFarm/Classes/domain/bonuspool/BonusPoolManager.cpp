#include "domain/bonuspool/BonusPoolManager.h"
#include "utill/FunUtil.h"

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


bool BonusPoolManager::allowBonusPool() {
    if( getBounsFishCounts() >= getAllowCatchFishCounts() ) {
        return true;
    }else {
        return false;
    }
}

BonuspoolResult BonusPoolManager::getBonuspoolResult() {
    BonuspoolResult bonuspoolResult; 
	int coins = getBounsCoins();
        Bonuspool bonuspool = ConfigBonuspool::getInstance()->getBonuspool();
        for(int i=0; i < bonuspool.bonuspoolItems.size(); i++) {
            if( ( coins >= bonuspool.bonuspoolItems.at(i).start_coins ) &&
                    ( coins < bonuspool.bonuspoolItems.at(i).end_coins ) ) {
				bonuspoolResult.bouns_position = i;
                bonuspoolResult.reward_list = bonuspool.bonuspoolItems.at(i).reward_list;
				return bonuspoolResult;
				}
            }
		return bonuspoolResult;
}
   


///TODO::È±ÉÙ±£»¤
BonuspoolItem*  BonusPoolManager::getNextBonuspool() {
	int coins = getBounsCoins();
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
				BonuspoolItem* item = new BonuspoolItem();
				item->start_coins = bonuspool.bonuspoolItems.at(i + 1).start_coins;
				item->end_coins = bonuspool.bonuspoolItems.at(i + 1).end_coins;
				item->reward_list = bonuspool.bonuspoolItems.at(i + 1).reward_list;
				return item;
			}

		}
	}
}



unsigned long BonusPoolManager::getBounsCoins()
{
	return _coins;
}
void BonusPoolManager::setBounsCoins(unsigned long coins)
{
	_coins = coins;
}
void BonusPoolManager::addBounsCoins(int coins)
{
	_coins += ((unsigned long)coins);
}

int BonusPoolManager::getBounsFishCounts()
{
	return _fishCounts;
}
void BonusPoolManager::setBounsFishCounts(int fishcounts)
{
	_fishCounts = fishcounts;
}
void BonusPoolManager::addBounsFishCounts(int fishcounts)
{
	_fishCounts += fishcounts;
}
