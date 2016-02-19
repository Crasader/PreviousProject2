#include "FishOfAllKilled.h"
#include "config/ConfigFishCollisionRange.h"
void FishOfAllKilled::initFish(int fishID){
	int fishid = rand() % 2 ? rand() % 7 + 4 : rand() % 6 + 30;
	auto fishdata = ConfigFish::getInstance()->getFish(fishid);
	if (fishid == 44)
	{
		fishGold = getintRandonNumByAtoB(fishdata.baseRewardStart, fishdata.baseRewardEnd, 50);
	}
	else
	{
		fishGold = getintRandonNumByAtoB(fishdata.baseRewardStart, fishdata.baseRewardEnd);
	}
	this->grabProbability = fishdata.probability;
	this->fishID = fishID;
	this->speed = getRandValueInVec(fishdata.move_speeds);
	this->experience = getFishExperienceByID(fishid);
	setFishType(getFishTypeByID(fishID));
	initFishAnim(fishdata.uiId);
	setuiId(fishdata.uiId);
	figures = ConfigFishCollisionRange::getInstance()->getFishFigures(fishdata.uiId);


	auto aninode = Sprite::create("game/ui/effect/allkilledEffect.png");
	aninode->setPosition(getContentSize() / 2);
	addChild(aninode, -1);
	aninode->runAction(RepeatForever::create(RotateBy::create(7, 360)));
	LogEventFish::getInstance()->addFishCreateTimes(fishID);
}





