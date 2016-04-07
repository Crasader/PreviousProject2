#include "domain/ai/AIJun.h"
#include "domain/ai/AIManager.h"

PlayerWork AIJun::nextStep(int currentCoins, Point currentPostion) {

	PlayerWork playerWork;
	while (1)
	{
		if (!AIManager::getInstance()->allowAiFire() || FishManage::getInstance()->getAllFishInPoolCount()<5) {
			break;
		}

		if (_currentFish&&_currentFish->getTag() != -1)
		{
			angle = getTurretRotation(currentPostion, _currentFish->getPosition());
			if (currentPostion.y > 270)
			{
				angle -= 180;
			}
			playerWork.setFire(true);
			playerWork.setAngle(angle);
			return playerWork;
		}
		else
		{
			_currentFish = FishManage::getInstance()->getLowDistanceInPool(currentPostion);
			if (_currentFish&&_currentFish->getTag() != -1)
			{
				angle = getTurretRotation(currentPostion, _currentFish->getPosition());
				if (currentPostion.y > 270)
				{
					angle -= 180;
				}
				playerWork.setFire(true);
				playerWork.setAngle(angle);
				return playerWork;
			}
			else
			{
				break;
			}
		}
	}
	playerWork.setAngle((float)angle);
	playerWork.setFire(false);
	return playerWork;
}