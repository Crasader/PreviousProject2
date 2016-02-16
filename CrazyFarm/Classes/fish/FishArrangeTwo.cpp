#include "fish/FishArrangeTwo.h"
#include "fish/FishAniMannage.h"
#include "utill/MagicEffect.h"
#include "utill/FunUtil.h"
#include "config/ConfigFishCollisionRange.h"

void FishArrangeTwo::initFishAnim(int fishType)
{
	//Ö÷Óã
	int randarray[7] = { 10, 30, 31, 32, 33, 34, 35 };
	int id = randarray[rand() % 7];
	auto mainfish = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	mainfish->setAnchorPoint(Point::ZERO);
	mainfish->setPosition(0, 0);
	addChild(mainfish);
	auto acName = String::createWithFormat("swim_%d", id);
	auto ac = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
	mainfish->runAction(ac);
	auto maggiceff = MagicEffect::create(1, false);
	maggiceff->setPosition(mainfish->getContentSize() / 2);
	maggiceff->stopAllActions();
	mainfish->addChild(maggiceff, -1);
	pushBackFigureVec(id, Vec2(0,0));
	//¸±Óã
	int randarray1[6] = { 2,4,7,8,32,33 };
id = randarray1[rand() % 6];
	auto mainSize = getContentSize();
	auto AffiliateSize = FishAniMannage::getInstance()->getSpriteById(id)->getOriginalSize();
	acName = String::createWithFormat("swim_%d", id);
	auto ac1 = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
	auto ac2 = ac1->clone();
	auto ac3 = ac1->clone();
	auto ac4 = ac1->clone();
	setAnchorPoint(Point::ANCHOR_MIDDLE);

	auto sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE);	
	sp->setPosition(-15, -15);
	sp->runAction(ac1);
	addChild(sp);
	maggiceff = MagicEffect::create(3, false);
	maggiceff->setPosition(sp->getContentSize() / 2);
	maggiceff->setScale(sp->getContentSize().width / maggiceff->getContentSize().width);
	sp->addChild(maggiceff, -1);
	pushBackFigureVec(id, sp->getPosition() - sp->getContentSize() / 2);

	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sp->setPosition(-15,-15+102);
	sp->runAction(ac2);
	addChild(sp);
	maggiceff = MagicEffect::create(3, false);
	maggiceff->setPosition(sp->getContentSize() / 2);
	maggiceff->setScale(sp->getContentSize().width / maggiceff->getContentSize().width);
	sp->addChild(maggiceff, -1);
	pushBackFigureVec(id, sp->getPosition() - sp->getContentSize() / 2);
	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sp->setPosition(-15+102,-15+102);
	sp->runAction(ac3);
	addChild(sp);
	maggiceff = MagicEffect::create(3, false);
	maggiceff->setPosition(sp->getContentSize() / 2);
	maggiceff->setScale(sp->getContentSize().width / maggiceff->getContentSize().width);
	sp->addChild(maggiceff, -1);
	pushBackFigureVec(id, sp->getPosition() - sp->getContentSize() / 2);
	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sp->setPosition(-15+102,-15 );
	sp->runAction(ac4);
	addChild(sp);
	maggiceff = MagicEffect::create(3, false);
	maggiceff->setPosition(sp->getContentSize() / 2);
	maggiceff->setScale(sp->getContentSize().width / maggiceff->getContentSize().width);
	sp->addChild(maggiceff, -1);
	pushBackFigureVec(id, sp->getPosition() - sp->getContentSize() / 2);
}

