#include "fish/FishManage.h"
#include "fish/FishGroupData.h"
#include "utill/FunUtil.h"
#include "fish/FishArrangeOne.h"
#include "fish/FishArrangeTwo.h"
#include "fish/FishArrangeThree.h"
#include "fish/FishArrangeFourh.h"
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
	fish->setAnchorPoint(Point::ANCHOR_MIDDLE);
	return fish;
}
Fish* FishManage::createFishArrange(int type){
	Fish* fish ;
	switch (type)
	{
	case 101:
		fish = FishArrangeOne::create();
		break;
	case 102:
		fish = FishArrangeTwo::create();
		break;
	case 103:
		fish = FishArrangeThree::create();
		break;
	case 104:
		fish = FishArrangeFourh::create();
		break;
	default:
		break;
	}
	
	fish->initFish(type);
	fishPool.pushBack(fish);
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
				fish->setVisible(false);
				fish->setisAutoRemove(false);
				fish->setRoute(singlegp.fishRoute);
				fish->setPosition(singlegp.startPos);
				m_layer->addChild(fish,5);
				fish->addShader();
		
			}), nullptr));
		}

	}

}


void FishManage::createFishAssign(int fishId, int momentEightroutetag)
{
	
	Fish*fish;
	if (fishId>=100)
	{
		fish = createFishArrange(fishId);
	}
	else
	{
		fish = createFishSingle(fishId);
	}
	fish->setVisible(false);
	fish->setisAutoRemove(false);
	fish->setMonentEightRoute(momentEightroutetag);
	m_layer->addChild(fish,5);

	fish->addShader();
}
void FishManage::createFishByEightMonment(MomentEightItemPer per)
{
	if (per.fishRoute!=-1)
	{
		createFishAssign(per.fish_id, per.fishRoute);

	}
	else
	{
		if (per.fish_id>=100)
		{
			createFishArrangeRand(per.fish_id);
		}
		else
		{
			createFishRand(per.fish_id);
		}
	}
}

void FishManage::removeFish(Fish* fish,bool isDead){
	auto lockfish = m_layer->GetMyTurret()->getLockFish();
	if (fish == lockfish)
	{
		m_layer->GetMyTurret()->setLockFish(nullptr);
	}
	fishPool.eraseObject(fish);
	if (isDead)
	{
		fish->onDead();
	}
	else
	{
		fish->removeself();
	}
	
}


void FishManage::decideFishPos(Fish* fish){
	auto visibleSize = Director::getInstance()->getVisibleSize();
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
		Rect rect = Rect(-50-box.size.width, -50-box.size.height, visibisize.width + box.size.width*2+200, visibisize.height + box.size.height*2+200);
		auto pos = fish->getPosition();
		if (!rect.containsPoint(pos)&&fish->getisAutoRemove())
		{
			needRemoveFishs.pushBack(fish);
		}
	}
	for (auto fish : needRemoveFishs)
	{
		removeFish(fish,0);
		
	}
}
void FishManage::createFishRand(int fishID)
{
	Fish* fish = FishManage::getInstance()->createFishSingle(fishID);
	decideFishPos(fish);
	
	auto k = getAngleByPos(Vec2(fish->getPositionX(), fish->getPositionY()));
	if (fishID<50)
	{
		k += rand_0_1() * 30 - 15;
	}
	else
	{
		k += rand_0_1() * 20 - 10;
	}
	
	fish->setMoveAngle(k);
	if (fishID<50)
	{
		fish->move(3);
	}
	else
	{
		fish->move(4);
	}
	
	m_layer->addChild(fish,5);
	fish->addShader();

}
void FishManage::createFishArrangeRand(int fishID)
{
	auto fish = createFishArrange(fishID);
	decideFishPos(fish);
	auto k = getAngleByPos(Vec2(fish->getPositionX(), fish->getPositionY()));
	k += rand_0_1() * 20 - 10	;
	fish->setMoveAngle(k);
	fish->move(4);
	m_layer->addChild(fish,5);
	fish->addShader();

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

void FishManage::createFishByOneMonet(OneMoment onemonent) {


    if(onemonent.fishgroup_id < 100) {  // single fish
        switch (onemonent.move_type) {
            case 1: {
                Fish* fish = createFishSingle(onemonent.fishgroup_id);
                
                fish->setMoveAngle(onemonent.startAngle);
                auto startPos = CalculateDiffMarginPos(Vec2(onemonent.start_position_x, onemonent.start_position_y), fish->getContentSize().width/2);
                fish->setPosition(startPos);
                fish->move(3);
                m_layer->addChild(fish,5);
				fish->addShader();

            }
                break;
            case 2: {
                auto fish = createFishSingle(onemonent.fishgroup_id);
                auto startPos = CalculateDiffMarginPos(Vec2(onemonent.start_position_x, onemonent.start_position_y),fish->getContentSize().width);
                fish->setPosition(startPos);
                auto endpos = CalculateDiffMarginPos(Vec2(onemonent.end_position_x, onemonent.end_position_y), fish->getContentSize().width + 150);
                fish->runAction(Sequence::create(MoveTo::create(onemonent.end_time - onemonent.start_time+5, endpos), nullptr));
                m_layer->addChild(fish,5);
				fish->addShader();
			
            }
                break;
            case 3: {
                //TODO:  «˙œﬂ‘À∂Ø
            }
                break;
            default:
                break;
        }
    }
	else
	{
		switch (onemonent.move_type) {
		case 1: {
			Fish* fish = createFishArrange(onemonent.fishgroup_id);
			auto k = getAngleByPos(Vec2(onemonent.start_position_x, onemonent.start_position_y));
			fish->setMoveAngle(onemonent.startAngle);
			auto startPos = CalculateDiffMarginPos(Vec2(onemonent.start_position_x, onemonent.start_position_y), fish->getContentSize().width);
			fish->setPosition(startPos);
			fish->move(3);
			m_layer->addChild(fish,5);
			fish->addShader();

		}
				break;
		case 2: {
			auto fish = createFishArrange(onemonent.fishgroup_id);
			auto startPos = CalculateDiffMarginPos(Vec2(onemonent.start_position_x, onemonent.start_position_y), fish->getContentSize().width);
			fish->setPosition(startPos.x, startPos.y);
			auto endpos = CalculateDiffMarginPos(Vec2(onemonent.end_position_x, onemonent.end_position_y), fish->getContentSize().width + 150);
			fish->runAction(Sequence::create(MoveTo::create(onemonent.end_time - onemonent.start_time + 5, Vec2(endpos.x, endpos.y)), nullptr));
			m_layer->addChild(fish,5);
			fish->addShader();

		}
				break;
		case 3: {
			//TODO:  «˙œﬂ‘À∂Ø
		}
				break;
		default:
			break;
		}

		
	}
	
}

Fish*FishManage::getFishByPosInPool(Point pos)
{
	for (auto var:fishPool)
	{
		auto rect = var->getBoundingBox();
		if (rect.containsPoint(pos))
		{
			return var;
		}
	}
	return nullptr;
}

void FishManage::createCycleFish(int count, int Radius, int fishID, Point center, Point curPos,float moveTime)
{
	float diffAngle = 360.0f/count;
	for (int i = 0; i < count; i++)
	{
		Fish* fish = FishManage::getInstance()->createFishSingle(fishID); 
		fish->setisAutoRemove(false);
		fish->setPosition(center.x + Radius*cos(CC_DEGREES_TO_RADIANS(i*diffAngle)), center.y + Radius*sin(CC_DEGREES_TO_RADIANS(diffAngle*i)));
		auto moveto = MoveTo::create(moveTime,curPos);
		fish->runAction(Sequence::create(moveto, RemoveSelf::create(), nullptr));	
		m_layer->addChild(fish,5);
		fish->addShader();
	}
	

}