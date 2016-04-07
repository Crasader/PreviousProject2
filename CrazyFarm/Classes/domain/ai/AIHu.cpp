#include "domain/ai/AIHu.h"
#include "domain/ai/AIManager.h"
#include "bullet/BulletManage.h"
PlayerWork AIHu::nextStep(int currentCoins, Point currentPostion) {


	PlayerWork playerWork;
	while (1)
	{
		if (!AIManager::getInstance()->allowAiFire()||FishManage::getInstance()->getAllFishInPoolCount()<5) {
			break;
		}
		
		if (_currentFish)
		{			
			angle = getTurretRotation(currentPostion, _currentFish->getPosition());
			if (currentPostion.y>270)
			{
				angle -= 180;
			}
			playerWork.setFire(true);
			playerWork.setAngle(angle);
			return playerWork;
		}
		else
		{
			_currentFish = FishManage::getInstance()->getHignSoreInPool();
			if (_currentFish)
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