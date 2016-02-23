#include "domain/ai/AIJun.h"
#include "domain/ai/AIManager.h"

PlayerWork AIJun::nextStep(int currentCoins, Point currentPostion) {
    PlayerWork playerWork;
//    int turrentLevel = rand()%this->getMaxTurrentLevel();
//    playerWork.setTurrentLevel(turrentLevel);
    
    if(! AIManager::getInstance()->allowAiFire()) {
        playerWork.setAngle((float)angle);
        playerWork.setFire(false);
        lastFire = false;
        return playerWork;
    }
    
    if(FishManage::getInstance()->getAllFishInPoolCount() < 20) {
        playerWork.setAngle((float)angle);
        playerWork.setFire(false);
        lastFire = false;
        return playerWork;
    }
	else
	{
		angle = CC_RADIANS_TO_DEGREES(currentPostion.getAngle(FishManage::getInstance()->getBestRewardPostion()));
		playerWork.setAngle((float)angle);
		playerWork.setFire(true);
		lastFire = true;
		return playerWork;
	}
}