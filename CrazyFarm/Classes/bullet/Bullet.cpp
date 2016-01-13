#include "bullet/Bullet.h"
#include "data/GameData.h"
#include "domain/magnate/MagnateManager.h"

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
	
	auto str = String::createWithFormat("gamelayer/bulletAndNet/bullet_%d_%d.png", ui_type, net_type);
	return str->getCString();

}



int Bullet::getSpeedByType(int type){
	switch (type)
	{
	case BULLETTYPE_1:
		return 300;
	case BULLETTYPE_2:
		return 300;
	case BULLETTYPE_3:
		return 300;
	case BULLETTYPE_4:
		return 300;
	case BULLETTYPE_5:
		return 300;
	case BULLETTYPE_6:
		return 300;
	case BULLETTYPE_7:
		return 300;
	case BULLETTYPE_8:
		return 300;
	default:
		return 300;
	}
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
		auto event = GameData::getInstance()->getevent();
		if (GameData::getInstance()->getShotCount() >= event.fireTimes)
		{
			User::getInstance()->addDiamonds(event.num);
			GameData::getInstance()->setShotCount(0);
			GameData::getInstance()->setevent(MagnateManager::getInstance()->getDiamandMagnateEvent());
			//TODO::在鱼上得到奖品UI显示
		}
		pPlayerTurret->getCoinByFish(var);
	}
}