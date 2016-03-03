#include "bullet/Bullet.h"
#include "data/GameData.h"
#include "domain/magnate/MagnateManager.h"
#include "core/GameLayer.h"
#include "domain/gameConfig/gameConfig.h"
#include "config/ConfigNewbieFishCatch.h"
#include "domain/game/GameManage.h"
bool Bullet::init(){
	if (!Sprite::init()){
		return false;
	}
	return true;
}

void Bullet::initBullet(TurretData turretdata, float rotation){
	this->bulletRotation = rotation;
	this->bulletSpeed = getSpeedByType(1);
	m_turretdata = turretdata;
	initWithFile(getSrcByType(turretdata.ui_type, turretdata.net_type));
	scheduleUpdate();
}



string Bullet::getSrcByType(int ui_type, int net_type){
	
	auto str = String::createWithFormat("game/ui/gamelayer/bulletAndNet/bullet_%d_%d.png", ui_type, net_type);
	return str->getCString();

}

void Bullet::moveToLockfish(float time, Fish*fish)
{
	runAction(Sequence::create(MoveTo::create(time, fish->convertToWorldSpace(fish->getCentrenPos())), CallFunc::create([=]{

		setVisible(false); 
		((GameLayer*)getParent())->createNet(this);
		auto turretdata = getTurretdata();
		auto curryFish = fish;
		if (curryFish == nullptr)
		{
			return;
		}
		LogEventFish::getInstance()->addFishHitTimes(curryFish->getFishID());
		float k = rand_0_1();
		float per = curryFish->getGrabProbability();

		if (!getPlayerTurret()->isRobot)
		{
			LogEventFish::getInstance()->addFishUserCostCoin(curryFish->getFishID(), getPlayerTurret()->getTurrentMupltData().multiple);
			float perForLevel = ConfigNewbieFishCatch::getInstance()->getperByLevelAndFishID(User::getInstance()->getLevelData().levelId, fish->getFishID());
			if (perForLevel > 0)
			{
				per = perForLevel;
			}
		}
		if (k < (per*turretdata.catch_per))
		{
			GameManage::getInstance()->CatchTheFishOntheTurrent(curryFish, 1, getPlayerTurret());
		}
		removeFromParentAndCleanup(1); 
	
	
	
	}
	), nullptr));
}

int Bullet::getSpeedByType(int type){
	return GameConfig::getInstance()->getShootData().shootSpeed;
}

void Bullet::update(float dt){
	//子弹运动
	Point nextPos = getNextPostion(getPosition(), bulletSpeed*dt, this->getRotation());
	auto move = MoveBy::create(dt, nextPos);
	this->runAction(move);
}


Point Bullet::getNextPostion(Point pos, float speed, float degree){
	//CCLOG("degree : %f", degree);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float next_x = pos.x + speed*sin(CC_DEGREES_TO_RADIANS(degree));
	float next_y = pos.y + speed*cos(CC_DEGREES_TO_RADIANS(degree));
	if (checkHeightBorder(next_y)){
		this->setRotation(180 - this->getRotation());
		next_x = pos.x + speed*sin(CC_DEGREES_TO_RADIANS(this->getRotation()));
		next_y = pos.y + speed*cos(CC_DEGREES_TO_RADIANS(this->getRotation()));
	}
	else if (checkWidthBorder(next_x)){
		this->setRotation(-this->getRotation());
		next_x = pos.x + speed*sin(CC_DEGREES_TO_RADIANS(this->getRotation()));
		next_y = pos.y + speed*cos(CC_DEGREES_TO_RADIANS(this->getRotation()));
	}
	return  Point(speed*sin(CC_DEGREES_TO_RADIANS(this->getRotation())), speed*cos(CC_DEGREES_TO_RADIANS(this->getRotation())));
}


bool Bullet::checkHeightBorder(float y){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (y < 0 || y > visibleSize.height){
		return true;
	}
	return false;
}

bool Bullet::checkWidthBorder(float x){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (x < 0 || x > visibleSize.width){
		return true;
	}
	return false;
}

void Bullet::getCoinForFish(Vector<Fish*> fishs)
{
	for(auto var : fishs)
	{
		
		pPlayerTurret->getCoinByFish(var);
	}
}

void Bullet::moveTolockFishUpadate(float dt)
{
	if (target!=nullptr)
	{
	//TODO::改写成跟踪模式，每帧获得目标位置
	}
}
std::vector<OBBEX> Bullet::getObbs()
{
	std::vector<OBBEX> vec;
	
	switch (m_turretdata.net_type)
	{
	case 1:
		vec.push_back(OBBEX(convertToWorldSpace(Vec2(0, 0)), convertToWorldSpace(Vec2(16, 0)), convertToWorldSpace(Vec2(16, 42)), convertToWorldSpace(Vec2(0, 42))));
		break;
	case 2:
		vec.push_back(OBBEX(convertToWorldSpace(Vec2(0, 0)), convertToWorldSpace(Vec2(54, 0)), convertToWorldSpace(Vec2(54, 42)), convertToWorldSpace(Vec2(0, 42))));
		break;
	case 3:
		vec.push_back(OBBEX(convertToWorldSpace(Vec2(0, 0)), convertToWorldSpace(Vec2(56, 0)), convertToWorldSpace(Vec2(56, 53)), convertToWorldSpace(Vec2(0, 53))));
		break;
	default:
		break;
	}
	return vec;
	
}

std::vector<OBB> Bullet::getOBBByCocos()
{

	std::vector<OBB> vec;
	switch (m_turretdata.net_type)
	{
	case 1:
	{
		AABB aabb = AABB(Vec3(0, 0, 0), Vec3(16, 42, 0));
		OBB obb = OBB(aabb);
		obb.transform(getNodeToWorldTransform());
		vec.push_back(obb);
	}
		break;
	case 2:
	{
		AABB aabb = AABB(Vec3(0, 0, 0), Vec3(16, 42, 0));
		OBB obb = OBB(aabb);
		obb.transform(getNodeToWorldTransform());
		vec.push_back(obb);
	}
	{
		AABB aabb = AABB(Vec3(38, 0, 0), Vec3(54, 42, 0));
		OBB obb = OBB(aabb);
		obb.transform(getNodeToWorldTransform());
		vec.push_back(obb);
	}
		break;
	case 3:
	{
		AABB aabb = AABB(Vec3(0, 0, 0), Vec3(16, 42, 0));
		OBB obb = OBB(aabb);
		obb.transform(getNodeToWorldTransform());
		vec.push_back(obb);
	}
	{
		AABB aabb = AABB(Vec3(40, 0, 0), Vec3(56, 42, 0));
		OBB obb = OBB(aabb);
		obb.transform(getNodeToWorldTransform());
		vec.push_back(obb);
	}
	{
		AABB aabb = AABB(Vec3(20, 11, 0), Vec3(36, 53, 0));
		OBB obb = OBB(aabb);
		obb.transform(getNodeToWorldTransform());
		vec.push_back(obb);
	}
		break;
	default:
		break;
	}
	return vec;
}