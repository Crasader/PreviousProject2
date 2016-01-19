#include "Turret/Turret.h"
bool Turret::init(){
	if (!Sprite::init()){
		return false;
	}
	
	emptySp = nullptr;
	return true;
}
#define SCALETURRET 0.75
void Turret::initWithType(int type){
	auto path = String::createWithFormat("turret/pao_%d.png", type);
	initWithFile(path->getCString());
	setScale(SCALETURRET);
	if (emptySp)
	{
		emptySp->removeAllChildrenWithCleanup(1);
	}
	emptySp = Sprite::create();
	emptySp->setPosition(getContentSize().width/2, getContentSize().height*0.9);
	addChild(emptySp);
	 
	/*this->initWithSpriteFrameName(getSrcByType(type));*/
}

string Turret::getSrcByType(int type){
	switch (type)
	{
	case TURRETTYPE_1:
		return "gun_c_2.png";
	case TURRETTYPE_2:
		return "gun_c_3.png";
	case TURRETTYPE_3:
		return "gun_c_4.png";
	case TURRETTYPE_4:
		return "gun_d_2.png";
	case TURRETTYPE_5:
		return "gun_d_3.png";
	case TURRETTYPE_6:
		return "gun_d_4.png";
	default:
		return "gun_c_2.png";
	}
}

void Turret::shoot()
{
	runAction(Sequence::createWithTwoActions(Spawn::create(ScaleTo::create(0.05f, 1 * SCALETURRET, 0.8*SCALETURRET), MoveBy::create(0.05, Vec2(0, -getContentSize().height*SCALETURRET*0.1)),nullptr),
											Spawn::create(ScaleTo::create(0.05f, 1 * SCALETURRET, 1.0*SCALETURRET), MoveBy::create(0.05, Vec2(0, getContentSize().height*SCALETURRET*0.1)), nullptr)));
}
void Turret::upgradeTurret()
{
	///Éý¼¶ÅÚËþ
}
void Turret::degradeTurret()
{
	///½µ¼¶ÅÚËþ
}