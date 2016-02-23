#include "fish/FishArrangeThree.h"
#include "fish/FishAniMannage.h"
#include "utill/MagicEffect.h"
#include "utill/FunUtil.h"
#include "config/ConfigFishCollisionRange.h"

void FishArrangeThree::initFishAnim(int fishID)
{
	//Ö÷Óã
	int randarray[7] = { 10, 30, 31, 32, 33, 34, 35 };
	int id = randarray[rand() % 7];

	auto maggiceff = MagicEffect::create(4, false);
	maggiceff->stopAllActions();
	maggiceff->setPosition(0,0);
	maggiceff->setAnchorPoint(Point::ZERO);
	addChild(maggiceff, -1);
	auto mainfish = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	mainfish->setPosition(maggiceff->getContentSize() / 2);
	addChild(mainfish);
	auto acName = String::createWithFormat("swim_%d", id);
	auto ac = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
	mainfish->runAction(ac);
	pushBackFigureVec(id, mainfish->getPosition() - mainfish->getContentSize() / 2);


	centerPos = maggiceff->getContentSize() / 2;
	//¸±Óã
	int randarray1[6] = { 2,3,4,7,8,9};
	id = randarray1[rand() % 6];
	auto mainSize = mainfish->getContentSize();
	auto AffiliateSize = FishAniMannage::getInstance()->getSpriteById(id)->getOriginalSize();
	acName = String::createWithFormat("swim_%d", id);
	auto ac1 = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
	auto ac2 = ac1->clone();
	auto ac3 = ac1->clone();
	setAnchorPoint(Point::ANCHOR_MIDDLE);


	auto maggiceff1 = MagicEffect::create(3, false);
	maggiceff1->setPosition(145,maggiceff->getContentSize().height/2);
	addChild(maggiceff1, -1);
	auto sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setPosition(maggiceff1->getPosition());
	sp->runAction(ac1);
	addChild(sp);
	pushBackFigureVec(id, sp->getPosition() - sp->getContentSize() / 2);


	auto maggiceff2 = MagicEffect::create(3, false);
	maggiceff2->setPosition(33, -8);
	addChild(maggiceff2, -1);
	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setPosition(maggiceff2->getPosition());
	sp->runAction(ac2);
	addChild(sp);
	pushBackFigureVec(id, sp->getPosition() - sp->getContentSize() / 2);
	

	auto maggiceff3 = MagicEffect::create(3, false);
	maggiceff3->setPosition(33, 8+maggiceff->getContentSize().height);
	addChild(maggiceff3, -1);
	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setPosition(maggiceff3->getPosition());
	sp->runAction(ac3);
	addChild(sp);
	pushBackFigureVec(id, sp->getPosition() - sp->getContentSize() / 2);

}