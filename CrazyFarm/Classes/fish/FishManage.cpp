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

int FishManage::getAllFishInPoolCount() {
    return fishPool.size();
}

Fish* FishManage::createFishSingle(){
	auto fish = Fish::create();
	int randType = rand() % 27+1;
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
	int border = rand() % 10;
	switch (border){
	case 0:
	case 1:
	case 2:
	case 3:
	{
		auto x = fish->getBoundingBox().size.width;
		auto y = rand() % (int)(visibleSize.height);
		fish->setRotation(0);
		fish->setPosition(ccp(-x, y));
		fish->setDirection(RIGHT);
		break; }
	case 4:{
		auto x = rand() % (int)(visibleSize.width);
		auto y = fish->getBoundingBox().size.width;
		fish->setPosition(ccp(x, visibleSize.height + y));
		fish->setRotation(90);
		fish->setDirection(DOWN);
		break;
	}
	case 5:
	case 6:
	case 7:
	case 8:{
		auto x = fish->getBoundingBox().size.width;
		auto y = rand() % (int)(visibleSize.height);
		fish->setPosition(ccp(visibleSize.width + x, y));
		fish->setRotation(180);
		fish->setDirection(LEFT);
		break; }
	case 9:{
		auto x = rand() % (int)(visibleSize.width);
		auto y = fish->getBoundingBox().size.width;
		fish->setPosition(ccp(x, -y));
		fish->setRotation(270);
		fish->setDirection(UP);
		break; }
	}
}

void FishManage::removeFishWhichSwimOut()
{
	auto visibisize = Director::getInstance()->getVisibleSize();
	
	Vector<Fish*> needRemoveFishs;
	for (auto fish : fishPool)
	{
		auto box = ((Fish*)fish)->getBoundingBox();
		Rect rect = Rect(-100-box.size.width, -100-box.size.height, visibisize.width + box.size.width+200, visibisize.height + box.size.height+200);
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

void FishManage::cleanVector()
{
	fishPool.clear();
}


void FishManage::LoadOnement()
{
    m_nowMonent = MomentManager::getInstance()->getNewMoment();
}

void FishManage::UpdateWhenController(float dt)
{
	if (m_nowMonent)
	{
		if (m_nowMonent->updata(dt))
		{
			m_layer->loadNewMonent();
		}
		
	}
}

void FishManage::createFishByOneMonet(int fishGroupId, int costTime, Vec2 startPos, Vec2 endPos, int movetype)
{
    if(movetype == 2) {
        auto fish = createFishSingle(fishGroupId);
        fish->setPosition(startPos);
        fish->runAction(MoveTo::create(costTime, endPos));
        m_layer->addChild(fish);
    }else if(movetype == 1) {
        // TODO : need support any postion ;
        Fish* fish = createFishSingle(fishGroupId);
        fish->setRotation(0);
        fish->setDirection(RIGHT);
        fish->setPosition(startPos);
        fish->move(3);
        m_layer->addChild(fish);
    }else if(movetype == 3) {
        // TODO :
    }
	
}
