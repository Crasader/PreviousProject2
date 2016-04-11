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
	
		}
		else
		{
			_currentFish = FishManage::getInstance()->getLowDistanceInPool(currentPostion);
		}
		if (_currentFish&&_currentFish->getTag() != -1)
		{
			auto currentPos = _currentFish->convertToWorldSpace(_currentFish->getCentrenPos());
			angle = getTurretRotation(currentPostion, currentPos);
			if (currentPostion.y > 270)
			{
				angle -= 180;
			}
			if (angle > 85 || angle < -85)
			{
				break;
			}

			CCLOG("AiJun shoot _currentPos = (%f,%f)  angle = %f _currentFishId = %d", currentPos.x, currentPos.y, angle,_currentFish->getFishID());
			playerWork.setFire(true);
			playerWork.setAngle(angle);
			return playerWork;
		}
		else
		{
			break;
		}
	}
	playerWork.setAngle((float)angle);
	playerWork.setFire(false);
	return playerWork;
}