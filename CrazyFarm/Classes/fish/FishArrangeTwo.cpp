#include "fish/FishArrangeTwo.h"
#include "fish/FishAniMannage.h"
#include "utill/MagicEffect.h"
#include "utill/FunUtil.h"
#include "config/ConfigFishCollisionRange.h"
void FishArrangeTwo::initFish(int fishType){
	auto fishdata = ConfigFish::getInstance()->getFish(fishType);
	fishGold = getintRandonNumByAtoB(fishdata.baseRewardStart, fishdata.baseRewardEnd);
	this->grabProbability = fishdata.probability;
	this->fishType = fishType;
	this->speed = fishdata.move_speed;
	this->experience = getFishExperienceByType(fishType);
	initFishAnim(fishdata.uiId);
}
void FishArrangeTwo::initFishAnim(int fishType)
{
	//Ö÷Óã
	int id = rand() % 8 + 30;
	auto mainfish = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	mainfish->setPosition(0, 0);
	addChild(mainfish);
	auto acName = String::createWithFormat("swim_%d", id);
	auto ac = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
	mainfish->runAction(ac);
	auto maggiceff = MagicEffect::create(1, false);
	maggiceff->setPosition(getContentSize() / 2);
	maggiceff->setScale(getContentSize().width / maggiceff->getContentSize().width);
	addChild(maggiceff, -1);
	pushBackFigureVec(id, mainfish->getPosition() - mainfish->getContentSize() / 2);
	//¸±Óã
	id = rand() % 10 + 1;
	auto mainSize = getContentSize();
	auto AffiliateSize = FishAniMannage::getInstance()->getSpriteById(id)->getOriginalSize();
	acName = String::createWithFormat("swim_%d", id);
	auto ac1 = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
	auto ac2 = ac1->clone();
	auto ac3 = ac1->clone();
	setAnchorPoint(Point::ANCHOR_MIDDLE);

	auto sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE);	
	sp->setPosition(-mainSize.width  - AffiliateSize.width, -mainSize.height -AffiliateSize.height);
	sp->runAction(ac1);
	addChild(sp);
	maggiceff = MagicEffect::create(3, true);
	maggiceff->setPosition(sp->getContentSize() / 2);
	maggiceff->setScale(sp->getContentSize().width / maggiceff->getContentSize().width);
	sp->addChild(maggiceff, -1);
	pushBackFigureVec(id, sp->getPosition() - sp->getContentSize() / 2);

	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sp->setPosition(mainSize.width + AffiliateSize.width , -mainSize.height  - AffiliateSize.height );
	sp->runAction(ac2);
	addChild(sp);
	maggiceff = MagicEffect::create(3, true);
	maggiceff->setPosition(sp->getContentSize() / 2);
	maggiceff->setScale(sp->getContentSize().width / maggiceff->getContentSize().width);
	sp->addChild(maggiceff, -1);
	pushBackFigureVec(id, sp->getPosition() - sp->getContentSize() / 2);
	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sp->setPosition(-mainSize.width  - AffiliateSize.width, mainSize.height+AffiliateSize.height );
	sp->runAction(ac3);
	addChild(sp);
	maggiceff = MagicEffect::create(3, true);
	maggiceff->setPosition(sp->getContentSize() / 2);
	maggiceff->setScale(sp->getContentSize().width / maggiceff->getContentSize().width);
	sp->addChild(maggiceff, -1);
	pushBackFigureVec(id, sp->getPosition() - sp->getContentSize() / 2);
	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sp->setPosition(+mainSize.width  + AffiliateSize.width , mainSize.height  + AffiliateSize.height );
	sp->runAction(ac3);
	addChild(sp);
	maggiceff = MagicEffect::create(3, true);
	maggiceff->setPosition(sp->getContentSize() / 2);
	maggiceff->setScale(sp->getContentSize().width / maggiceff->getContentSize().width);
	sp->addChild(maggiceff, -1);
	pushBackFigureVec(id, sp->getPosition() - sp->getContentSize() / 2);
}

void FishArrangeTwo::onDead()
{
	removeFromParentAndCleanup(1);
}

void FishArrangeTwo::pushBackFigureVec(int uiid, Point pos)
{
	auto vec = ConfigFishCollisionRange::getInstance()->getFishFigures(uiid);
	for (auto var : vec)
	{
		figures.push_back(var->addposWithFigure(pos));
	}
}