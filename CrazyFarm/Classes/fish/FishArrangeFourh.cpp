#include "fish/FishArrangeFourh.h"
#include "fish/FishAniMannage.h"
#include "utill/MagicEffect.h"
#include "utill/FunUtil.h"
#include "config/ConfigFishCollisionRange.h"
void FishArrangeFourh::initFish(int fishType){
	auto fishdata = ConfigFish::getInstance()->getFish(fishType);
	fishGold = getintRandonNumByAtoB(fishdata.baseRewardStart, fishdata.baseRewardEnd);
	this->grabProbability = fishdata.probability;
	this->fishType = fishType;
	this->speed = fishdata.move_speed;
	this->experience = getFishExperienceByType(fishType);
	initFishAnim(fishdata.uiId);
	LogEventFish::getInstance()->addFishCreateTimes(fishType);
}
void FishArrangeFourh::initFishAnim(int fishType)
{
	//Ö÷Óã
	int id = rand()%2? rand() % 8 + 30:rand() % 10 + 1;
	auto mainfish = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	mainfish->setPosition(0, 0);
	addChild(mainfish);
	auto acName = String::createWithFormat("swim_%d", id);
	auto ac = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
	mainfish->runAction(ac);
	auto maggiceff = MagicEffect::create(3, true);
	maggiceff->setPosition(mainfish->getContentSize() / 2);
	maggiceff->setScale(mainfish->getContentSize().width / maggiceff->getContentSize().width);
	mainfish->addChild(maggiceff, -1);
	pushBackFigureVec(id, mainfish->getPosition()-mainfish->getContentSize()/2);

	//¸±Óã
	
	auto mainSize = mainfish->getContentSize();
	acName = String::createWithFormat("swim_%d", id);
	auto ac1 = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
	auto ac2 = ac1->clone();
	auto ac3 = ac1->clone();
	setAnchorPoint(Point::ANCHOR_MIDDLE);

	auto sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sp->setPosition(-mainSize.width*0.5, -mainSize.height*1);
	sp->runAction(ac1);
	addChild(sp);
	maggiceff = MagicEffect::create(3, true);
	maggiceff->setPosition(sp->getContentSize() / 2);
	maggiceff->setScale(sp->getContentSize().width / maggiceff->getContentSize().width);
	sp->addChild(maggiceff, -1);
	pushBackFigureVec(id, sp->getPosition()-sp->getContentSize()/2);

	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sp->setPosition(-mainSize.width *1.0 , 0);
	sp->runAction(ac2);
	addChild(sp);
	maggiceff = MagicEffect::create(3, true);
	maggiceff->setPosition(sp->getContentSize() / 2);
	maggiceff->setScale(sp->getContentSize().width / maggiceff->getContentSize().width);
	sp->addChild(maggiceff, -1);
	pushBackFigureVec(id, sp->getPosition() - sp->getContentSize() / 2);
	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sp->setPosition(mainSize.width *-1.5 , -mainSize.height *1);
	sp->runAction(ac3);
	addChild(sp);
	maggiceff = MagicEffect::create(3, true);
	maggiceff->setPosition(sp->getContentSize() / 2);
	maggiceff->setScale(sp->getContentSize().width / maggiceff->getContentSize().width);
	sp->addChild(maggiceff, -1);
	pushBackFigureVec(id, sp->getPosition() - sp->getContentSize() / 2);
}

void FishArrangeFourh::onDead()
{
	removeFromParentAndCleanup(1);
}

void FishArrangeFourh::pushBackFigureVec(int uiid, Point pos)
{
	auto vec = ConfigFishCollisionRange::getInstance()->getFishFigures(uiid);
	for (auto var : vec)
	{
		figures.push_back(var->addposWithFigure(pos));
	}
}