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
	
	runAction(Sequence::create(ScaleTo::create(0.1, 1.2), ScaleTo::create(0.05, 0.9), ScaleTo::create(0.05, 1.0),CallFunc::create([&]{checkCatchFish(); }),FadeOut::create(0.5), CallFunc::create([&]{m_bullet->cleanup(); }), RemoveSelf::create(1), nullptr));
}

//
//int ui_type; // 1����;2����
//int net_type;  // 1,1����;2,2��;3,����

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
	Vector<Fish*> fishNeedRemove;
	auto turretdata = m_bullet->getTurretdata();
	for (Fish* fish : allFish){
		if (CollisionUtill::isCollisionRect(fish->getBoundingFigures(), getBoundingBox())){
			float k = rand_0_1();
			LogEventFish::getInstance()->addFishHitTimes(fish->getFishID());
			if (!m_bullet->getPlayerTurret()->isRobot)
			{
				LogEventFish::getInstance()->addFishUserCostCoin(fish->getFishID(),m_bullet->getPlayerTurret()->getTurrentMupltData().multiple);
			}
			if (k<(fish->getGrabProbability()*turretdata.catch_per))
			{
				fishNeedRemove.pushBack(fish);
			//ui�Ƴ�
				
			}
			
		}
	}
	auto data = GameData::getInstance();
	for (Fish* fish : fishNeedRemove){	
		GameManage::getInstance()->CatchTheFishOntheTurrent(fish, 1, m_bullet->getPlayerTurret());
		fish = nullptr;
	}
}