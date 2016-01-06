#include "net/Net.h"
#include "utill/FunUtil.h"
bool Net::init(){
	if (!Sprite::init()){
		return false;
	}
	return true;
}

void Net::initNetByType(int type){
	/*this->initWithSpriteFrameName(getFrameNameByType(type));*/
	initWithFile("netFrame.png");
	schedule(schedule_selector(Net::destroySelf),0,0,1);
}

std::string Net::getFrameNameByType(int type){
	switch (type)
	{
	case NET_TYPE_0:
		return "net0.png";
	case NET_TYPE_1:
		return "net1.png";
	case NET_TYPE_2:
		return "net2.png";
	default:
		return "net0.png";
	}
}


void Net::destroySelf(float dt){
	this->removeFromParent();
}

void Net::checkCatchFish(Bullet*bullet){
	auto allFish = FishManage::getInstance()->getAllFishInPool();
	Vector<Fish*> fishNeedRemove;
	for (Fish* fish : allFish){
		if (collision(this,fish)){
			//进行捕获判断
			//TODO 添加捕获概率
			int k = rand() % 100 + 1;
			if (k>(100-fish->getGrabProbability()*100))
			{
				fishNeedRemove.pushBack(fish);
			//ui移除
				fish->removeFromParent();
			}
			
		}
	}
	bullet->getCoinForFish(fishNeedRemove);
	for (Fish* fish : fishNeedRemove){
		FishManage::getInstance()->removeFish(fish);
	}
}