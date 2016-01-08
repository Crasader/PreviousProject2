#include "fish/FishManage.h"
#include "fish/FishGroupData.h"
#include "utill/FunUtil.h"
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

Point FishManage::getBestRewardPostion() {
    Point point;
    point.x = 480;
    point.y = 270;
    int current_id = 0;
    
    for(int i=0; i<fishPool.size(); i++) {
        if(current_id < fishPool.at(i)->getFishType()) {
            point = fishPool.at(i)->getPosition();
        }
    }
    return point ;
    
}

Fish* FishManage::createFishSingle(){
	auto fish = Fish::create();
	int randType = rand() % 27+1;   // TODO : change 27 to config by fish list numbers
	fish->initFish(randType);
	fishPool.pushBack(fish);
	return fish;
}
Fish* FishManage::createFishSingle(int type){
	auto fish = Fish::create();
	fish->initFish(type);
	fishPool.pushBack(fish);	
	fish->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	return fish;
}
void FishManage::createFishGroup(int grouptag)
{
	auto gp = FishGroupData::getInstance()->getGroupBytag(grouptag);
	for (int i = 0; i < gp.singleTypefishGroups.size(); i++)
	{
		auto singlegp = gp.singleTypefishGroups[i];
		for (int j = 0; j < singlegp.fishCount; j++)
		{
			m_layer->runAction(Sequence::create(DelayTime::create(j*singlegp.IntervalCreateTime), CallFunc::create([=]{
				Fish* fish = FishManage::getInstance()->createFishSingle(singlegp.fishID);
				fish->setRoute(singlegp.fishRoute);
				fish->setPosition(singlegp.startPos);
				m_layer->addChild(fish);
			}), nullptr));
		}

	}

}

void FishManage::removeFish(Fish* fish){
	fishPool.eraseObject(fish);
}


void FishManage::decideFishPos(Fish* fish){
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//æˆ∂®Ω¯»Î∆¡ƒªµƒ±ﬂΩÁ
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
	m_layer = nullptr; 
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

void FishManage::createFishByOneMonet(OneMoment onemonent)
{

	switch (onemonent.move_type)
	{
	case 1:
		{
			Fish* fish = createFishSingle(onemonent.fishgroup_id);
			auto k = getAngleByPos(Vec2(onemonent.start_position_x, onemonent.start_position_y));
			fish->setMoveAngle(k);
			auto startPos = CalculateDiffMarginPos(Vec2(onemonent.start_position_x, onemonent.start_position_y), fish->getContentSize().width);
			fish->setPosition(startPos);
			fish->move(3);
			m_layer->addChild(fish);
		}
		break;
	case 2:
		{
			auto fish = createFishSingle(onemonent.fishgroup_id);
			auto startPos = CalculateDiffMarginPos(Vec2(onemonent.start_position_x, onemonent.start_position_y),fish->getContentSize().width);
			fish->setPosition(startPos);
			auto endpos = CalculateDiffMarginPos(Vec2(onemonent.end_position_x, onemonent.end_position_y), fish->getContentSize().width + 150);
			fish->runAction(Sequence::create(MoveTo::create(onemonent.end_time - onemonent.start_time+5, endpos), nullptr));
			m_layer->addChild(fish);
		}
		break;
	case 3:
		{
			//TODO:  «˙œﬂ‘À∂Ø
		}
		break;
	default:
	break;
	}
}
