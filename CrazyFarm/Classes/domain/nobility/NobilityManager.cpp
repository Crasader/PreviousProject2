#include "domain/nobility/NobilityManager.h"


NobilityManager* NobilityManager::_instance = NULL;

NobilityManager::NobilityManager(){
    this->init();
}

void NobilityManager::init(){
}

NobilityManager* NobilityManager::getInstance(){
    if(_instance == NULL){
        _instance = new NobilityManager();
    }
    return _instance;
}

