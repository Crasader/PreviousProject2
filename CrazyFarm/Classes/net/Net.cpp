#include "net/Net.h"
#include "utill/FunUtil.h"
#include "data/GameData.h"
#include "bullet/BulletManage.h"
bool Net::init(){
	if (!Sprite::init()){
		return false;
	}
	return true;
}

void Net::initNetByType(){
	TurretData turretdata = m_bullet->getTurretdata();
	initWithFile(getFrameNameByType(turretdata.ui_type, turretdata.net_type));
	setScale(0);
	runAction(Sequence::create(ScaleTo::create(0.2, 1.0), CallFunc::create([&]{checkCatchFish(); }), DelayTime::create(0.5f), CallFunc::create([&]{m_bullet->cleanup();}), RemoveSelf::create(1), nullptr));
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
			int k = rand() % 100 + 1;
			if (k>(100-fish->getGrabProbability()*100*turretdata.catch_per))
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
		FishManage::getInstance()->removeFish(fish);
		fish = nullptr;
	}
}