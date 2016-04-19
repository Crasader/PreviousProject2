#include "domain/ai/AIMolo.h"
#include "domain/ai/AIManager.h"

PlayerWork AIMolo::nextStep(int currentCoins, Point currentPostion, int AiDoCounts, bool isUsingSkillLockOrLigh, float bulletWidth) {

	if (isUsingSkillLockOrLigh)
	{
		if (_currentFish&&_currentFish->getTag() == -1)
		{
			_currentFish = FishManage::getInstance()->getLowDistanceInPool(currentPostion);
		}
		else if (!_currentFish)
		{
			_currentFish = FishManage::getInstance()->getLowDistanceInPool(currentPostion);
		}
		PlayerWork playerwork;
		playerwork._workeType = Robot_UsingSkill;
		playerwork._lockFish = _currentFish;
		return playerwork;
	}




	PlayerWork playerWork = getUpdataTurrentWork(AiDoCounts);
	if (playerWork._workeType == Invalid)
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
				//增加保护，防止帧数严重降低
				if (FishManage::getInstance()->getAllFishInPoolCount() > 20)
				{
					_currentFish = FishManage::getInstance()->getLowDistanceInPool(currentPostion);
				}
			else
			{
					_currentFish = FishManage::getInstance()->getLowDistanceCouldcatchHighscoreFishInPool(currentPostion,bulletWidth);
			}
				
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
				if (fangle > 85 || fangle < -85)
				{
					break;
				}
				angle = fangle;

				/*CCLOG("AiJun shoot turrentPostion = (%f,%f) _currentPos = (%f,%f)  angle = %f _currentFishId = %d",currentPostion.x,currentPostion.y,currentPos.x, currentPos.y, angle,_currentFish->getFishID());*/
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