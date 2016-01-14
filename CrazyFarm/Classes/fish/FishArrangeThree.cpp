#include "fish/FishArrangeThree.h"
#include "fish/FishAniMannage.h"
#include "utill/MagicEffect.h"

void FishArrangeThree::initFish(int fishType){
	auto fishdata = ConfigFish::getInstance()->getFish(fishType);
	fishGold = fishdata.baseReward;
	this->grabProbability = fishdata.probability;
	this->fishType = fishType;
	this->speed = fishdata.move_speed;
	this->experience = getFishExperienceByType(fishType);
	initFishAnim(fishdata.uiId);
}
void FishArrangeThree::initFishAnim(int fishType)
{
	//主鱼
	int id = rand() % 8 + 30;
	initWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	auto acName = String::createWithFormat("swim_%d", id);
	auto ac = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
	runAction(ac);
	auto maggiceff = MagicEffect::create(2, true);
	maggiceff->setPosition(getContentSize() / 2);
	addChild(maggiceff,-1);
	

	////TODO ： 挂载光圈 下班处理 需计算每只鱼大小，缩小放大光圈
	//副鱼
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
	sp->setPosition(- AffiliateSize.width / 2, mainSize.height / 2);
	sp->runAction(ac1);
	addChild(sp);
	maggiceff = MagicEffect::create(2, true);
	maggiceff->setPosition(getContentSize() / 2);
	addChild(maggiceff, -1);


	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sp->setPosition(mainSize.width *1.0 , mainSize.height+mainSize.height/2);
	sp->runAction(ac2);
	addChild(sp);

	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sp->setPosition(mainSize.width *1.0 , -mainSize.height / 2);
	sp->runAction(ac3);
	addChild(sp);
}