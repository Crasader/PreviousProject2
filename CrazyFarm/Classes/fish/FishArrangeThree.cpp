#include "fish/FishArrangeThree.h"
#include "fish/FishAniMannage.h"
#include "utill/MagicEffect.h"
#include "utill/FunUtil.h"
#include "config/ConfigFishCollisionRange.h"
void FishArrangeThree::initFish(int fishType){
	auto fishdata = ConfigFish::getInstance()->getFish(fishType);
	fishGold = getintRandonNumByAtoB(fishdata.baseRewardStart, fishdata.baseRewardEnd);
	this->grabProbability = fishdata.probability;
	this->fishType = fishType;
	this->speed = fishdata.move_speed;
	this->experience = getFishExperienceByType(fishType);
	initFishAnim(fishdata.uiId);
	LogEventFish::getInstance()->addFishCreateTimes(fishType);

}
void FishArrangeThree::initFishAnim(int fishType)
{
	//主鱼
	int id = rand() % 8 + 30;
	auto mainfish = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	mainfish->setPosition(0, 0);
	addChild(mainfish);
	CCLOG("x:%f;y:%f", mainfish->getPositionX(), mainfish->getPositionY());
	auto acName = String::createWithFormat("swim_%d", id);
	auto ac = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
	mainfish->runAction(ac);
	auto maggiceff = MagicEffect::create(3, true);
	maggiceff->setPosition(mainfish->getContentSize() / 2);
	maggiceff->setScale(mainfish->getContentSize().width / maggiceff->getContentSize().width);
	mainfish->addChild(maggiceff, -1);
	pushBackFigureVec(id, mainfish->getPosition()-mainfish->getContentSize()/2);

	////TODO ： 挂载光圈 下班处理 需计算每只鱼大小，缩小放大光圈
	//副鱼
	id = rand() % 10 + 1;
	auto mainSize = mainfish->getContentSize();
	auto AffiliateSize = FishAniMannage::getInstance()->getSpriteById(id)->getOriginalSize();
	acName = String::createWithFormat("swim_%d", id);
	auto ac1 = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
	auto ac2 = ac1->clone();
	auto ac3 = ac1->clone();
	setAnchorPoint(Point::ANCHOR_MIDDLE);



	auto sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE);	
	sp->setPosition(-AffiliateSize.width/2-mainSize.width/2, mainSize.height / 2+AffiliateSize.height/2);
	sp->runAction(ac1);
	addChild(sp);
	pushBackFigureVec(id, sp->getPosition() - sp->getContentSize() / 2);
	maggiceff = MagicEffect::create(3, true);
	maggiceff->setPosition(sp->getContentSize() / 2);
	maggiceff->setScale(sp->getContentSize().width / maggiceff->getContentSize().width);
	sp->addChild(maggiceff, -1);
	CCLOG("x:%f;y:%f", sp->getPositionX(), sp->getPositionY());
	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sp->setPosition(-AffiliateSize.width / 2-mainSize.width/2 , -mainSize.height / 2 - AffiliateSize.height / 2);
	sp->runAction(ac2);
	addChild(sp);
	pushBackFigureVec(id, sp->getPosition() - sp->getContentSize() / 2);
	maggiceff = MagicEffect::create(3, true);
	maggiceff->setPosition(sp->getContentSize() / 2);
	maggiceff->setScale(sp->getContentSize().width / maggiceff->getContentSize().width);
	sp->addChild(maggiceff, -1);
	CCLOG("x:%f;y:%f", sp->getPositionX(), sp->getPositionY());
	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sp->setPosition(mainSize.width/2+AffiliateSize.width/2 , 0);
	sp->runAction(ac3);
	addChild(sp);
	pushBackFigureVec(id, sp->getPosition() - sp->getContentSize() / 2);
	maggiceff = MagicEffect::create(3, true);
	maggiceff->setPosition(sp->getContentSize() / 2);
	maggiceff->setScale(sp->getContentSize().width / maggiceff->getContentSize().width);
	sp->addChild(maggiceff, -1);
	CCLOG("x:%f;y:%f", sp->getPositionX(), sp->getPositionY());
}

void FishArrangeThree::onDead()
{
	removeFromParentAndCleanup(1);
}

void FishArrangeThree::pushBackFigureVec(int uiid, Point pos)
{
	auto vec = ConfigFishCollisionRange::getInstance()->getFishFigures(uiid);
	for (auto var : vec)
	{
		figures.push_back(var->addposWithFigure(pos));
	}
}