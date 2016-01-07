#include "moment/MomentManager.h"


MomentManager* MomentManager::_instance = NULL;

MomentManager::MomentManager(){
    this->init();
}

void MomentManager::init(){
}

MomentManager* MomentManager::getInstance(){
    if(_instance == NULL){
        _instance = new MomentManager();
    }
    return _instance;
}

Moment* MomentManager::getNewMoment() {
    Moment* moment = new MomentOne();
    moment->init();
    return moment;
}



