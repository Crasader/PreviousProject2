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

int BonusPoolManager::getCoins() {
    return UserDefault::getInstance()->getIntegerForKey(BonusPoolManager::KEY_BONUSPOOL_COINS, 0);
}

bool BonusPoolManager::addCoins(int coins) {
    if(coins > 0) {
        UserDefault::getInstance()->setIntegerForKey(BonusPoolManager::KEY_BONUSPOOL_COINS, getCoins() + coins);
        return true;
    }
    return false;

}
bool BonusPoolManager::cleanCoins() {
    UserDefault::getInstance()->setIntegerForKey(BonusPoolManager::KEY_BONUSPOOL_COINS, 0);
    return true;
}


