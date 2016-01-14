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


