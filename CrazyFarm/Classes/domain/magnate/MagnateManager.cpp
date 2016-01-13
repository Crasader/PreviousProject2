#include "domain/magnate/MagnateManager.h"

MagnateManager* MagnateManager::_instance = NULL;

MagnateManager::MagnateManager(){
    this->init();
}


void MagnateManager::init(){
}

MagnateManager* MagnateManager::getInstance(){
    if(_instance == NULL){
        _instance = new MagnateManager();
    }
    return _instance;
}


MagnateEvent MagnateManager::getDiamandMagnateEvent(){
    MagnateEvent magnateEvent;
    magnateEvent.fireTimes = 100 + rand()%300;
    magnateEvent.itemId = 1002;
    magnateEvent.num = 1;
    return magnateEvent;
}

MagnateEvent MagnateManager::getItemMagnateEvent(){
    MagnateEvent magnateEvent;
    magnateEvent.fireTimes = 200 + rand()%500;
    magnateEvent.itemId = 1003;
    magnateEvent.num = 1;
    return magnateEvent;
}