#include "net/Net.h"
#include "utill/FunUtil.h"
#include "data/GameData.h"
bool Net::init(){
	if (!Sprite::init()){
		return false;
	}
	return true;
}

void Net::initNetByType(TurretData turretdata){
	
	initWithFile(getFrameNameByType(turretdata.ui_type, turretdata.net_type));
	schedule(schedule_selector(Net::destroySelf),0,0,1);
}

std::string Net::getFrameNameByType(int ui_type, int net_type){
	auto str = String::createWithFormat("gamelayer/bulletAndNet/net_%d_%d.png", ui_type, net_type);
	return str->getCString();
}


void Net::destroySelf(float dt){
	this->removeFromParent();
}

void Net::checkCatchFish(Bullet*bullet){
	auto allFish = FishManage::getInstance()->getAllFishInPool();
	Vector<Fish*> fishNeedRemove;
	auto turretdata = bullet->getTurretdata();
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
	bullet->getCoinForFish(fishNeedRemove);
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