#include "fish/FishArrangeFourh.h"
#include "fish/FishAniMannage.h"
#include "utill/MagicEffect.h"
#include "utill/FunUtil.h"
#include "config/ConfigFishCollisionRange.h"
void FishArrangeFourh::initFishAnim(int fishID)
{
	//����
	int randarray[9] = { 4,7,8,9,10, 30, 31, 32, 33 };
	int id = randarray[rand() % 9];
	auto maggiceff = MagicEffect::create(5, true);
	maggiceff->setPosition(0, 0);
	maggiceff->setAnchorPoint(Point::ZERO);
	addChild(maggiceff, -1);
	auto mainfish = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	mainfish->setPosition(maggiceff->getContentSize() / 2);
	addChild(mainfish);
	auto acName = String::createWithFormat("swim_%d", id);
	auto ac = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
	auto ac1 = ac->clone();
	auto ac2 = ac->clone();
	auto ac3 = ac->clone();
	mainfish->runAction(ac);
	pushBackFigureVec(id, mainfish->getPosition() - mainfish->getContentSize() / 2);
	
	auto maggiceff1 = MagicEffect::create(5, true);
	maggiceff1->setPosition(108, maggiceff->getContentSize().height / 2);
	addChild(maggiceff1, -1);
	auto sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setPosition(maggiceff1->getPosition());
	sp->runAction(ac1);
	addChild(sp);
	pushBackFigureVec(id, sp->getPosition() - sp->getContentSize() / 2);


	auto maggiceff2 = MagicEffect::create(5, true);
	maggiceff2->setPosition(130, -20);
	addChild(maggiceff2, -1);
	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setPosition(maggiceff2->getPosition());
	sp->runAction(ac2);
	addChild(sp);
	pushBackFigureVec(id, sp->getPosition() - sp->getContentSize() / 2);


	auto maggiceff3 = MagicEffect::create(5, true);
	maggiceff3->setPosition(130+72,-20);
	addChild(maggiceff3, -1);
	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->setPosition(maggiceff3->getPosition());
	sp->runAction(ac3);
	addChild(sp);
	pushBackFigureVec(id, sp->getPosition() - sp->getContentSize() / 2);
}

