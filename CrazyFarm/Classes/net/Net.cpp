#include "net/Net.h"
#include "utill/FunUtil.h"
#include "data/GameData.h"
#include "bullet/BulletManage.h"
#include "utill/AnimationUtil.h"
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
//int ui_type; // 1»ðÑæ;2±ù¶³
//int net_type;  // 1,1ÕÅÍø;2,2ÕÅ;3,ÈýÕÅ

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
	auto str = String::createWithFormat("gamelayer/bulletAndNet/net_%d_%d.png", ui_type, net_type);
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
		if (collision(this,fish)){
			float k = rand_0_1();
			if (k<(fish->getGrabProbability()*turretdata.catch_per))
			{
				fishNeedRemove.pushBack(fish);
			//uiÒÆ³ý
				
			}
			
		}
	}
	auto data = GameData::getInstance();
	m_bullet->getCoinForFish(fishNeedRemove);
	for (Fish* fish : fishNeedRemove){
		if (data->getIsOnMaridTask())
		{
			auto vec = data->getmermaidTask()->getMermaidTaskOnlineInfo().mermaidTaskItems;
			for (auto var:vec)
			{
				if (fish->getFishType() == var.fishId)
				{
					data->getmermaidTask()->addOneCatchFishById(fish->getFishType());
					break;
				}
			}
		}
		FishManage::getInstance()->removeFish(fish,1);
		fish = nullptr;
	}
}