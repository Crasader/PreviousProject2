#include "net/Net.h"
#include "utill/FunUtil.h"
#include "data/GameData.h"
#include "bullet/BulletManage.h"
#include "utill/AnimationUtil.h"
#include "utill/CollisionUtill.h"
#include "domain/logevent/LogEventFish.h"
#include "domain/game/GameManage.h"
bool Net::init(){
	if (!Sprite::init()){
		return false;
	}
	return true;
}

void Net::initNetByType(){
	TurretData turretdata = m_bullet->getTurretdata();
	initWithFile(getFrameNameByType(turretdata.ui_type, turretdata.net_type));
	initAniByType(turretdata.ui_type, turretdata.net_type);
	setScale(0);
	m_bullet->removeFromParentAndCleanup(1);
	runAction(Sequence::create(ScaleTo::create(0.1, 1.2), ScaleTo::create(0.05, 0.9), ScaleTo::create(0.05, 1.0),CallFunc::create([&]{checkCatchFish(); }),FadeOut::create(0.5), RemoveSelf::create(1), nullptr));
}

//
//int ui_type; // 1火焰;2冰冻
//int net_type;  // 1,1张网;2,2张;3,三张

void Net::initAniByType(int ui_type, int net_type)
{
	auto size = getContentSize();
	std::string aniName= "";
	aniName = (ui_type == 1 ? "fireNet" : "iceNet");

		switch (net_type)
		{
		case 1:
		{
			auto sp = Sprite::create();
			sp->setPosition(size / 2);
			addChild(sp);
			sp->runAction(AnimationUtil::getInstance()->getAnimate(aniName.c_str()));
		}
			break;
		case 2:
		{
			auto sp = Sprite::create();
			sp->setPosition(size.width*0.25, size.height / 2);
			addChild(sp);
			sp->runAction(AnimationUtil::getInstance()->getAnimate(aniName.c_str()));
			sp = Sprite::create();
			sp->setPosition(size.width*0.75,size.height/2);
			addChild(sp);
			sp->runAction(AnimationUtil::getInstance()->getAnimate(aniName.c_str()));
		}
			break;
		case 3:
		{
			auto sp = Sprite::create();
			sp->setPosition(size.width*1.0 / 3.0, size.height*1.0 / 3.0);
			addChild(sp);
			sp->runAction(AnimationUtil::getInstance()->getAnimate(aniName.c_str()));
			sp = Sprite::create();
			sp->setPosition(size.width*1.0 / 3.0, size.height*1.0 / 3.0);
			addChild(sp);
			sp->runAction(AnimationUtil::getInstance()->getAnimate(aniName.c_str()));
			sp = Sprite::create();
			sp->setPosition(size.width/2, size.height*2.0 / 3.0);
			addChild(sp);
			sp->runAction(AnimationUtil::getInstance()->getAnimate(aniName.c_str()));
		}
			break;
		default:
			break;
		}
}


std::string Net::getFrameNameByType(int ui_type, int net_type){
	auto str = String::createWithFormat("game/ui/gamelayer/bulletAndNet/net_%d_%d.png", ui_type, net_type);
	return str->getCString();
}

void Net::setBullet(Bullet* bullet)
{
	m_bullet = bullet;
}


void Net::checkCatchFish(){
	auto allFish = FishManage::getInstance()->getAllFishInPool();

	for (Fish* fish : allFish){
		if (CollisionUtill::isCollisionRect(fish->getBoundingFigures(), getBoundingBox())){
			fish->onHeart();

		}
	}

}