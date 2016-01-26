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
	this->speed = fishdata.move_speed;
	this->experience = getFishExperienceByType(fishType);
	initFishAnim(fishdata.uiId);
	LogEventFish::getInstance()->addFishCreateTimes(fishType);
}
void FishArrangeOne::initFishAnim(int fishType)
{
	//主鱼
	int id = rand() % 8 + 30;
	initWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	auto acName = String::createWithFormat("swim_%d", id);
	auto ac = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
	runAction(ac);
	auto maggiceff = MagicEffect::create(2, true);
	maggiceff->setPosition(getContentSize() / 2);
	maggiceff->setScale(getContentSize().width / maggiceff->getContentSize().width);
	addChild(maggiceff,-1);
	pushBackFigureVec(id, Point(0, 0));
	


	////TODO ： 挂载光圈 下班处理 需计算每只鱼大小，缩小放大光圈
	//副鱼
	id = rand() % 10 + 1;
	auto mainSize = getContentSize();
	auto AffiliateSize = FishAniMannage::getInstance()->getSpriteById(id)->getOriginalSize();
	acName = String::createWithFormat("swim_%d", id);
	auto ac1 = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
	auto ac2 = ac1->clone();


	auto sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE);	
	sp->setPosition(-mainSize.width *0 - AffiliateSize.width / 2, mainSize.height / 2);
	sp->runAction(ac1);
	addChild(sp);
	maggiceff = MagicEffect::create(2, true);
	maggiceff->setPosition(sp->getContentSize() / 2);
	maggiceff->setScale(sp->getContentSize().width / maggiceff->getContentSize().width);
	sp->addChild(maggiceff, -1);
	pushBackFigureVec(id, sp->getPosition() - sp->getContentSize() / 2);

	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sp->setPosition(mainSize.width *1.0 + AffiliateSize.width/2, mainSize.height/2);
	sp->runAction(ac2);
	addChild(sp);
	pushBackFigureVec(id, sp->getPosition() - sp->getContentSize() / 2);
	maggiceff = MagicEffect::create(2, true);
	maggiceff->setPosition(sp->getContentSize() / 2);
	maggiceff->setScale(sp->getContentSize().width / maggiceff->getContentSize().width);
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