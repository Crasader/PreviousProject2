#include "fish/FishManage.h"
#include "fish/FishGroupData.h"

FishManage* FishManage::_instance = 0;

FishManage* FishManage::getInstance(){
	if (_instance == 0){
		_instance = new FishManage();
	}
	return _instance;
}

FishManage::FishManage(){

}

Vector<Fish*> FishManage::getAllFishInPool(){
	return fishPool;
}

Fish* FishManage::createFishSingle(){
	auto fish = Fish::create();
	int randType = rand() % 8+1;
	fish->initFish(randType);
	fishPool.pushBack(fish);
	return fish;
}
Fish* FishManage::createFishSingle(int type){
	auto fish = Fish::create();
	fish->initFish(type);
	fishPool.pushBack(fish);
	return fish;
}
Vector<Fish*> FishManage::createFishGroup(int grouptag)
{
	auto gp = FishGroupData::getInstance()->getGroupBytag(grouptag);
	for (auto singlegp : gp.singleTypefishGroups)
	{

	}
	Vector<Fish*> a;
	return a;
}

void FishManage::removeFish(Fish* fish){
	fishPool.eraseObject(fish);
}


void FishManage::decideFishPos(Fish* fish){
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//决定进入屏幕的边界
	int border = rand() % 4;
	switch (border){
	case BORDER_LEFT:{
		//获取鱼的大小
		auto x = fish->getBoundingBox().size.width;
		auto y = rand() % (int)(visibleSize.height);
		fish->setRotation(0);
		fish->setPosition(ccp(-x, y));
		fish->setDirection(RIGHT);
		break; }
	case BORDER_TOP:{
		auto x = rand() % (int)(visibleSize.width);
		auto y = fish->getBoundingBox().size.width;
		fish->setPosition(ccp(x, visibleSize.height + y));
		fish->setRotation(90);
		fish->setDirection(DOWN);
		break;
	}
	case BORDER_RIGHT:{
		auto x = fish->getBoundingBox().size.width;
		auto y = rand() % (int)(visibleSize.height);
		fish->setPosition(ccp(visibleSize.width + x, y));
		fish->setRotation(180);
		fish->setDirection(LEFT);
		break; }
	case BORDER_BOTTOM:{
		auto x = rand() % (int)(visibleSize.width);
		auto y = fish->getBoundingBox().size.width;
		fish->setPosition(ccp(x, -y));
		fish->setRotation(270);
		fish->setDirection(UP);
		break; }
	}
	/*fish->setPosition(ccp(visibleSize.width/2 ,visibleSize.height/2));*/
}

void FishManage::removeFishWhichSwimOut()
{
	auto visibisize = Director::getInstance()->getVisibleSize();
	
	Vector<Fish*> needRemoveFishs;
	for (auto fish : fishPool)
	{
		auto box = ((Fish*)fish)->getBoundingBox();
		Rect rect = Rect(-box.size.width, -box.size.height, visibisize.width + box.size.width, visibisize.height + box.size.height);
		auto pos = fish->getPosition();
		if (!rect.containsPoint(pos))
		{
			needRemoveFishs.pushBack(fish);
		}
	}
	for (auto fish : needRemoveFishs)
	{
		fishPool.eraseObject(fish);
		fish->removeFromParentAndCleanup(1);
	}
}