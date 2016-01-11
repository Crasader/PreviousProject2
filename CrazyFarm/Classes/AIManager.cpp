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

    int who = rand()%100;
    if(who < 60) {
		AI* molo = new AIMolo();
        int randomCoins = 1037 + rand()%20000;
        molo->setCoins(randomCoins);
        int randomDiamonds = 3 + rand()%33;
        molo->setDiamonds(randomDiamonds);
        if(maxTurrentLevel > 0) {
            molo->setMaxTurrentLevel(maxTurrentLevel);
        }else {
            molo->setMaxTurrentLevel(1);
        }
        
        molo->setReqSteps(0.4f);
        return molo;
    }else {
        AI* hu = new AIHu();
        int randomCoins = 107 + rand()%5000;
        hu->setCoins(randomCoins);
        int randomDiamonds = 1 + rand()%9;
        hu->setDiamonds(randomDiamonds);
        if(maxTurrentLevel > 0) {
            hu->setMaxTurrentLevel(maxTurrentLevel);
        }else {
            hu->setMaxTurrentLevel(1);
        }
        
        hu->setReqSteps(0.4f);
        return hu;
    }
    
    
}


