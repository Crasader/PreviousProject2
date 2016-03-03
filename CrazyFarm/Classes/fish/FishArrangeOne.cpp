#include "fish/FishArrangeOne.h"
#include "fish/FishAniMannage.h"
#include "utill/MagicEffect.h"
#include "utill/FunUtil.h"



void FishArrangeOne::initFishAnim(int fishID)
{
	//����
	int randarray[7] = { 10, 30, 31, 32, 33, 34, 35 };
	int id = randarray[rand()%7];
	auto acName = String::createWithFormat("swim_%d", id);
	auto ac = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
	auto sp1 = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp1->runAction(ac);
	auto maggiceff = MagicEffect::create(1, true);
	maggiceff->setAnchorPoint(Point::ZERO);
	maggiceff->setPosition(0,0);
	addChild(maggiceff,2);
	sp1->setPosition(maggiceff->getContentSize() / 2);
	maggiceff->addChild(sp1);
	obbdatas = ConfigFishCollisionOBB::getInstance()->getFishFOBBPoints(101);
	fishes.pushBack(sp1);
	centerPos = maggiceff->getContentSize() / 2;


	//����
	int randarray1[6] = { 2,3,4,7,8,9 };
	id = randarray1[rand() % 6];
	acName = String::createWithFormat("swim_%d", id);
	auto ac1 = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
	auto ac2 = ac1->clone();


	auto sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	sp->runAction(ac1);
	maggiceff = MagicEffect::create(2, true);
	maggiceff->setPosition(-35, centerPos.y);
	addChild(maggiceff,1);
	sp->setPosition(maggiceff->getContentSize()/2);
	maggiceff->addChild(sp);
	fishes.pushBack(sp);

	sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
	maggiceff = MagicEffect::create(2, true);
	maggiceff->setPosition(137, centerPos.y);
	addChild(maggiceff, 1);
	sp->setPosition(maggiceff->getContentSize()/2);
	sp->runAction(ac2);
	maggiceff->addChild(sp);
	fishes.pushBack(sp);

}

