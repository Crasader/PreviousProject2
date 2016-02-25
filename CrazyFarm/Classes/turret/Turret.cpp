#include "Turret/Turret.h"
#include "utill/Audio.h"
#include "domain/Newbie/NewbieMannger.h"
#include "utill/AnimationUtil.h"
#define SCALETURRET 0.75
bool Turret::init(){
	if (!Sprite::init()){
		return false;
	}
	
	emptySp = nullptr;
	return true;
}

void Turret::initWithType(int type){
	auto path = String::createWithFormat("game/ui/turret/pao_%d.png", type);
	initWithFile(path->getCString());
	setScale(SCALETURRET);
	turretType = type;
	if (emptySp)
	{
		emptySp->removeFromParentAndCleanup(1);
	}
	emptySp = Sprite::create();
	emptySp->setPosition(getContentSize().width/2, getContentSize().height*0.9);
	addChild(emptySp);
	 

}



void Turret::shoot()
{
	if (!isrobot)
	{
		Audio::getInstance()->playShootVoic();
	}

	auto distance = getContentSize().height*SCALETURRET*0.1;
	auto movebypos = Vec2(distance*cos(CC_DEGREES_TO_RADIANS(90-getRotation())), distance*sin(CC_DEGREES_TO_RADIANS(90-getRotation())));
	runAction(Sequence::createWithTwoActions(Spawn::create(ScaleTo::create(0.025f, 1 * SCALETURRET, 0.8*SCALETURRET), MoveBy::create(0.025, Vec2(-movebypos.x, -movebypos.y)),nullptr),
		Spawn::create(ScaleTo::create(0.025f, 1 * SCALETURRET, 1.0*SCALETURRET), MoveBy::create(0.025, movebypos), nullptr)));

	if (NewbieMannger::getInstance()->getNBShootCounts() != -1&&!isrobot)
	{
		NewbieMannger::getInstance()->setNBShootCounts(NewbieMannger::getInstance()->getNBShootCounts() + 1);
	}
}
void Turret::upgradeTurret()
{
	///Éý¼¶ÅÚËþ
}
void Turret::degradeTurret()
{
	///½µ¼¶ÅÚËþ
}


void Turret::changeToLightTurret()
{
	auto str = String::createWithFormat("pao_jiguang.png");
	setTexture(str->getCString());
}
void Turret::changeToNormalTurret()
{
	auto path = String::createWithFormat("game/ui/turret/pao_%d.png", turretType);
	setTexture(path->getCString());
}
void Turret::changeToNewTurret(int uiid)
{

	auto path = String::createWithFormat("game/ui/turret/pao_%d.png", uiid);
	setTexture(path->getCString());
	setScale(SCALETURRET);
	turretType = uiid;
	
	runAction(Sequence::create(AnimationUtil::getInstance()->getAnimate("aniHuanpao"), CallFunc::create([=]{setScale(0); }), ScaleTo::create(0.1f, SCALETURRET), nullptr));

}