#include "AIMolo.h"

PlayerWork AIMolo::nextStep(int currentCoins) {
    PlayerWork playerWork;
//    int turrentLevel = rand()%this->getMaxTurrentLevel();
//    playerWork.setTurrentLevel(turrentLevel);
    
    playerWork.setTurrentLevel(this->getMaxTurrentLevel());
    
    int fire = rand()%100;
    if(fire < 20) { // TODO : just test value
        angle = 90 - rand()%180;
        playerWork.setAngle((float)angle);
        playerWork.setFire(true);
    }else {
        playerWork.setFire(false);
        int turn = rand()%100;
        if(turn < 20) {
            angle = 90 - rand()%180;
            playerWork.setAngle((float)angle);
        }else {
            playerWork.setAngle(angle);
        }
    }
	int angle = rand() % 180 - 90;
    playerWork.setAngle((float)(angle));

    return playerWork;
    
}