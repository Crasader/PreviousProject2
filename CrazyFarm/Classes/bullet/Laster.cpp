#include "bullet/Laster.h"
#include "utill/FunUtil.h"
bool Laster::init(){

	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!ui::Scale9Sprite::initWithFile("game/ui/ani/TX_JiGuang/TX_JiGuang_1.png"));
		setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		//runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniJiGuangBar")));




		scheduleUpdate();
		bRet = true;
	} while (0);
	return bRet;
}



void Laster::update(float delta)
{
	auto fish = pPlayerTurret->getLightFish();
	if (fish)
	{
		setPosition(pPlayerTurret->getLasterOrginPos());
		Vec2 m_pos = pPlayerTurret->getLasterOrginPos();
		Vec2 targetPos = fish->getPosition();
		auto distance = m_pos.distance(targetPos);
		setScaleX(distance/792);
		auto angle = getTurretRotation(m_pos,targetPos);
		setRotation(-90+angle);
	}
	else
	{
		removeFromParentAndCleanup(1); 
	}
}