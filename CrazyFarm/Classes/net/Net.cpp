#include "Net.h"
#include "FunUtil.h"
bool Net::init(){
	if (!Sprite::init()){
		return false;
	}
	return true;
}

void Net::initNetByType(int type){
	this->initWithSpriteFrameName(getFrameNameByType(type));
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

void Net::checkCatchFish(){
	auto allFish = FishManage::getInstance()->getAllFishInPool();
	Vector<Fish*> fishNeedRemove;
	for (Fish* fish : allFish){
		if (collision(this,fish)){
			//���в����ж�
			//TODO ��Ӳ������
			fishNeedRemove.pushBack(fish);
			//ui�Ƴ�
			fish->removeFromParent();
		}
	}
	for (Fish* fish : fishNeedRemove){
		FishManage::getInstance()->removeFish(fish);
	}
}