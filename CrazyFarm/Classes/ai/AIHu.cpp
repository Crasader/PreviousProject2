#include "ai/AIHu.h"

PlayerWork AIHu::nextStep(int currentCoins) {
    
    
    PlayerWork playerWork;
    
    playerWork.setTurrentLevel(this->getMaxTurrentLevel());
    
    if(FishManage::getInstance()->getAllFishInPoolCount() < 2) {
        playerWork.setAngle((float)angle);
        playerWork.setFire(false);
        return playerWork;
    }
    
    int fire = rand()%100;
    
    if(fire < 10) { // TODO : just test value
        angle = 60 - rand()%120;
        
        playerWork.setAngle((float)angle);
        if(fire < 5) {
            playerWork.setFire(true);
        }else {
            playerWork.setFire(false);
        }
        return playerWork;
    }else {
        playerWork.setFire(false);
        playerWork.setAngle(angle);
        return playerWork;
    }
    
    
    
}