#include "domain/bankrupt/BankruptManager.h"


BankruptManager* BankruptManager::_instance = NULL;

BankruptManager::BankruptManager(){
    this->init();
}


void BankruptManager::init(){
}

BankruptManager* BankruptManager::getInstance(){
    if(_instance == NULL){
        _instance = new BankruptManager();
    }
    return _instance;
}

Bankrupt BankruptManager::getBankrupt() {
    if( getTodayRequestTimes() < ConfigBankrupt::getInstance()->getBankrupts().size() ) {
        return ConfigBankrupt::getInstance()->getBankrupts().at( getTodayRequestTimes() );
    }else {
        Bankrupt bankrupt;
        bankrupt.coins = 0;
        bankrupt.wait_time = 0;
    }
}

int BankruptManager::getTodayRequestTimes() {
    // TODO : wait impl
    // get once add auto
    return 0;
}


