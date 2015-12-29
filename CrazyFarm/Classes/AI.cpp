#include "AI.h"

PlayerWork AI::nextStep(int currentCoins){
	PlayerWork playerWork;
	//    int turrentLevel = rand()%this->getMaxTurrentLevel();
	//    playerWork.setTurrentLevel(turrentLevel);

	playerWork.setTurrentLevel(this->getMaxTurrentLevel());

	int fire = rand() % 100;
	if (fire < 40) { // TODO : just test value
		playerWork.setFire(true);
	}
	else {
		playerWork.setFire(false);
	}

	playerWork.setAngle(0);
	return playerWork;
}