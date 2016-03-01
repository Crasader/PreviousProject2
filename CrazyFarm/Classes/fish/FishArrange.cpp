#include "FishArrange.h"
#include "config/ConfigFishCollisionOBB.h"
void FishArrange::initFish(int fishID){
	auto fishdata = ConfigFish::getInstance()->getFish(fishID);
	fishGold = getintRandonNumByAtoB(fishdata.baseRewardStart, fishdata.baseRewardEnd);
	this->grabProbability = fishdata.probability;
	this->fishID = fishID;
	this->speed = getRandValueInVec(fishdata.move_speeds);
	this->experience = getFishExperienceByID(fishID);
	setFishType(getFishTypeByID(fishID));
	setuiId(fishdata.uiId);
	initFishAnim(fishdata.uiId);
	rewards = fishdata.rewards;
	LogEventFish::getInstance()->addFishCreateTimes(fishID);
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
	auto data = ConfigFishCollisionOBB::getInstance()->getFishFOBBPoints(uiid);
	for (auto var:data)
	{
		ObbData val;
		val.leftBottom = var.leftBottom + pos;
		val.rightBottom = var.rightBottom + pos;
		val.leftTop = var.leftTop + pos;
		val.rightTop = var.rightTop + pos;
		obbdatas.push_back(val);
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