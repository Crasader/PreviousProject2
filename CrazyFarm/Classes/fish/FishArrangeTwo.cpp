#include "fish/FishArrangeTwo.h"
#include "fish/FishAniMannage.h"


void FishArrangeTwo::initFish(int fishType){
	auto fishdata = ConfigFish::getInstance()->getFish(fishType);
	fishGold = fishdata.baseReward;
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
	initWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	auto acName = String::createWithFormat("swim_%d", id);
	auto ac = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
	runAction(ac);

	
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
	sp->setPosition(-mainSize.width *0.5 - AffiliateSize.width / 2, -mainSize.height / 2-AffiliateSize.height/2);
	sp->runAction(ac1);
	addChild(sp);

	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sp->setPosition(mainSize.width *0.5 + AffiliateSize.width / 2, -mainSize.height / 2 - AffiliateSize.height / 2);
	sp->runAction(ac2);
	addChild(sp);

	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sp->setPosition(-mainSize.width *0.5 - AffiliateSize.width / 2, mainSize.height / 2 +AffiliateSize.height / 2);
	sp->runAction(ac3);
	addChild(sp);

	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sp->setPosition(+mainSize.width *0.5 + AffiliateSize.width / 2, mainSize.height / 2 + AffiliateSize.height / 2);
	sp->runAction(ac3);
	addChild(sp);
}