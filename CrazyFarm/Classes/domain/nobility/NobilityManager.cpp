#include "domain/nobility/NobilityManager.h"


NobilityManager* NobilityManager::_instance = NULL;

NobilityManager::NobilityManager(){
    this->init();
}


void NobilityManager::init(){
    NobilityRewadItem item1;
    item1.item_id = 1001;
    item1.num = 20000;
    this->nobilityRewadItems.push_back(item1);
    NobilityRewadItem item2;
    item2.item_id = 1002;
    item2.num = 20;
    this->nobilityRewadItems.push_back(item2);
    NobilityRewadItem item3;
    item3.item_id = 1004;
    item3.num = 5;
    this->nobilityRewadItems.push_back(item3);
    NobilityRewadItem item4;
    item4.item_id = 1003;
    item4.num = 2;
    this->nobilityRewadItems.push_back(item4);
}

NobilityManager* NobilityManager::getInstance(){
    if(_instance == NULL){
        _instance = new NobilityManager();
    }
    return _instance;
}

bool NobilityManager::isNobility() {
    return false;   // TODO : wait impl
}

std::vector<NobilityRewadItem> NobilityManager::getNobilityRewadItems() {
    return nobilityRewadItems;
}

