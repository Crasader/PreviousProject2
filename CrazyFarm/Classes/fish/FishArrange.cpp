#include "FishArrange.h"
#include "config/ConfigFishCollisionRange.h"
void FishArrange::initFish(int fishType){
	auto fishdata = ConfigFish::getInstance()->getFish(fishType);
	fishGold = getintRandonNumByAtoB(fishdata.baseRewardStart, fishdata.baseRewardEnd);
	this->grabProbability = fishdata.probability;
	this->fishType = fishType;
	this->speed = getRandValueInVec(fishdata.move_speeds);
	this->experience = getFishExperienceByType(fishType);
	initFishAnim(fishdata.uiId);
	LogEventFish::getInstance()->addFishCreateTimes(fishType);
}
void FishArrange::addShader()
{

}
void FishArrange::onDead()
{
	removeFromParentAndCleanup(1);
}

void FishArrange::pushBackFigureVec(int uiid, Point pos)
{
	auto vec = ConfigFishCollisionRange::getInstance()->getFishFigures(uiid);
	for (auto var:vec)
	{
		figures.push_back(var->addposWithFigure(pos));
	}
}

void FishArrange::onHeart()
{
	for (auto child : getChildren())
	{
		auto action = Sequence::create(
			TintTo::create(0.1f, 255, 0, 0),
			TintTo::create(0.1f, 255, 255, 255),
			nullptr);
		child->runAction(action);
	}
}