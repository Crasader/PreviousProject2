#include "domain/ai/AIMolo.h"
#include "domain/ai/AIManager.h"

PlayerWork AIMolo::nextStep(int currentCoins, Point currentPostion, int AiDoCounts) {
	PlayerWork playerWork = getUpdataTurrentWork(AiDoCounts);
	if (playerWork._workeType == Invalid)
	{
		playerWork._workeType = Robot_Fire;
		while (1)
		{
			if (!AIManager::getInstance()->allowAiFire() || FishManage::getInstance()->getAllFishInPoolCount() < 5) {
				break;
			}
				_currentFish = FishManage::getInstance()->getLowDistanceCouldcatchHighscoreFishInPool(currentPostion);
			if (_currentFish&&_currentFish->getTag() != -1)
			{
				auto currentPos = _currentFish->convertToWorldSpace(_currentFish->getCentrenPos());
				float fangle = getTurretRotation(currentPostion, currentPos);
				if (currentPostion.y > 270)
				{
					fangle -= 180;
				}
				angle = fangle;
				/*CCLOG("aimolo shoot turrentPostion = (%f,%f) _currentPos = (%f,%f)  angle = %f _currentFishId = %d", currentPostion.x, currentPostion.y, currentPos.x, currentPos.y, angle, _currentFish->getFishID());*/
				playerWork._isFire = true;
				playerWork._angle = angle;
				return playerWork;
			}
			else
			{
				break;
			}
		}
		playerWork._isFire = false;
		playerWork._angle = angle;
		return playerWork;
	}
	else
	{
		return playerWork;
	}
    
}