#include "AIMolo.h"

PlayerWork AIMolo::nextStep(int currentCoins) {
    PlayerWork playerWork;
//    int turrentLevel = rand()%this->getMaxTurrentLevel();
//    playerWork.setTurrentLevel(turrentLevel);
    
    playerWork.setTurrentLevel(this->getMaxTurrentLevel());
    
    int fire = rand()%100;
    if(fire < 40) { // TODO : just test value
        playerWork.setFire(true);
    }else {
        playerWork.setFire(false);
    }
	int angle = rand() % 180 - 90;
    playerWork.setAngle((float)(angle));
    return playerWork;
    
}