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
        _instance->momentOrders = ConfigMomentOrder::getInstance()->LoadConfig();
    }
    return _instance;
}

Moment* MomentManager::getNewMoment() {
    
    return getNewMomentByType(getCurrentType());
}

Moment* MomentManager::getNewMomentByType(int momentType) {
    if(momentType == 1) {
        Moment* moment = new MomentOne();
        moment->init();
        return moment;
    }
    
    Moment* moment = new MomentOne();
    moment->init();
    return moment;
}

int MomentManager::getCurrentType() {
    if(momentOrders.size() > 0) {
        if(currentPos < momentOrders.size()) {
        }else {
            currentPos = 0;
        }
        int type = momentOrders[currentPos].moment_id;
        currentPos++;
        return type;
    }
    return 1;
}



