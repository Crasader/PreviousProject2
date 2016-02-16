#include "fish/FishArrangeOne.h"
#include "fish/FishAniMannage.h"
#include "utill/MagicEffect.h"
#include "utill/FunUtil.h"
#include "config/ConfigFishCollisionRange.h"

void FishArrangeOne::initFish(int fishType){
	auto fishdata = ConfigFish::getInstance()->getFish(fishType);
	fishGold = getintRandonNumByAtoB(fishdata.baseRewardStart, fishdata.baseRewardEnd);
	this->grabProbability = fishdata.probability;
	this->fishType = fishType;
	this->speed = getRandValueInVec(fishdata.move_speeds);
	this->experience = getFishExperienceByType(fishType);
	initFishAnim(fishdata.uiId);
	LogEventFish::getInstance()->addFishCreateTimes(fishType);
}
void FishArrangeOne::initFishAnim(int fishType)
{
	//Ö÷Óã
	int randarray[7] = { 10, 30, 31, 32, 33, 34, 35 };
	int id = randarray[rand()%7];
	auto acName = String::createWithFormat("swim_%d", id);
	auto ac = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
	auto sp1 = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp1->setAnchorPoint(Point::ZERO);
	sp1->setPosition(0,0);
	sp1->runAction(ac);
	addChild(sp1);
	auto maggiceff = MagicEffect::create(1, true);
	maggiceff->setPosition(sp1->getContentSize() / 2);
	sp1->addChild(maggiceff, -1);
	pushBackFigureVec(id, Point(0, 0));
	

	//¸±Óã
	int randarray1[6] = { 2,3,4,7,8,9 };
	id = randarray1[rand() % 6];
	auto mainSize = sp1->getContentSize();
	auto AffiliateSize = FishAniMannage::getInstance()->getSpriteById(id)->getOriginalSize();
	acName = String::createWithFormat("swim_%d", id);
	auto ac1 = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
	auto ac2 = ac1->clone();


	auto sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE);	
	sp->setPosition(-35, mainSize.height / 2);
	sp->runAction(ac1);
	addChild(sp);
	maggiceff = MagicEffect::create(2, true);
	maggiceff->setPosition(sp->getContentSize() / 2);
	sp->addChild(maggiceff, -1);
	pushBackFigureVec(id, sp->getPosition() - sp->getContentSize() / 2);

	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sp->setPosition(137, mainSize.height/2);
	sp->runAction(ac2);
	addChild(sp);
	pushBackFigureVec(id, sp->getPosition() - sp->getContentSize() / 2);
	maggiceff = MagicEffect::create(2, true);
	maggiceff->setPosition(sp->getContentSize() / 2);
	sp->addChild(maggiceff, -1);
}
void FishArrangeOne::addShader()
{

}
void FishArrangeOne::onDead()
{
	removeFromParentAndCleanup(1);
}

void FishArrangeOne::pushBackFigureVec(int uiid,Point pos)
{
	auto vec = ConfigFishCollisionRange::getInstance()->getFishFigures(uiid);
	for (auto var:vec)
	{
		figures.push_back(var->addposWithFigure(pos));
	}
}