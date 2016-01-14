#include "domain/ai/AIManager.h"


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

AI* AIManager::getAI( int maxTurrentLevel) {

    int who = rand()%100;
    if(who < 60) {
		AI* molo = new AIMolo();
        if(maxTurrentLevel > 0) {
            molo->setMaxTurrentLevel(maxTurrentLevel);
        }else {
            molo->setMaxTurrentLevel(1);
        }
        
        molo->setReqSteps(0.4f);
        return molo;
    }else {
        AI* hu = new AIHu();
        if(maxTurrentLevel > 0) {
            hu->setMaxTurrentLevel(maxTurrentLevel);
        }else {
            hu->setMaxTurrentLevel(1);
        }
        
        hu->setReqSteps(0.4f);
        return hu;
    }
    
    
}

bool AIManager::allowAiFire() {
    return aiFire;
}

void AIManager::setAiFire(bool allow) {
     aiFire = allow;
}


