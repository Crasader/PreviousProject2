#include "AIManager.h"


AIManager* AIManager::_instance = NULL;

AIManager::AIManager(){
    this->init();
}

void AIManager::init(){
}

AIManager* AIManager::getInstance(){
    if(_instance == NULL){
        _instance = new AIManager();
    }
    return _instance;
}

AI* AIManager::getAI(int aiType, int aiLevel, int maxTurrentLevel) {
    AI* molo = new AIMolo();
    if(maxTurrentLevel > 0) {
        molo->setMaxTurrentLevel(maxTurrentLevel);
    }else {
        molo->setMaxTurrentLevel(1);
    }
    
    molo->setReqSteps(1.0f);
    return molo;
}


