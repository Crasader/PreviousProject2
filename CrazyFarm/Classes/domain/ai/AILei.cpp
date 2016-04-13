#include "domain/ai/AILei.h"
#include "domain/ai/AIManager.h"
#include "bullet/BulletManage.h"
PlayerWork AILei::nextStep(int currentCoins, Point currentPostion, int AiDoCounts) {
	PlayerWork playerWork = getUpdataTurrentWork(AiDoCounts);
	if (playerWork._workeType==Invalid)
	{
		playerWork._workeType = Robot_Fire;
		while (1)
		{
			if (!AIManager::getInstance()->allowAiFire() || FishManage::getInstance()->getAllFishInPoolCount() < 5) {
				break;
			}

			if (_currentFish&&_currentFish->getTag() != -1)
			{

			}
			else
			{
				_currentFish = FishManage::getInstance()->getLowDistanceGoldFishInPool(currentPostion);
			}
			if (_currentFish&&_currentFish->getTag() != -1)
			{
				auto currentPos = _currentFish->convertToWorldSpace(_currentFish->getCentrenPos());
				float fangle = getTurretRotation(currentPostion, currentPos);
				if (currentPostion.y > 270)
				{
					fangle -= 180;
				}
				else
				{
					fangle -= 360;
				}
				if (fangle>85||fangle<-85)
				{
					break;
				}
				angle = fangle;
				CCLOG("ailei shoot turrentPostion = (%f,%f) _currentPos = (%f,%f)  angle = %f _currentFishId = %d", currentPostion.x, currentPostion.y, currentPos.x, currentPos.y, angle, _currentFish->getFishID());
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