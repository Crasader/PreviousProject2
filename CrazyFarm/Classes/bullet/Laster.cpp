#include "bullet/Laster.h"

bool Laster::init(){

	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Sprite::initWithFile("game/ui/ani/TX_JiGuang/TX_JiGuang_1.png"));
		setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);





		scheduleUpdate();
		bRet = true;
	} while (0);
	return bRet;
}

void Laster::setTarget(Fish* fish)
{
	if (fish)
	{
		m_target = fish;
	}
}

void Laster::update(float delta)
{
	if (m_target)
	{
		Vec2 m_pos = pPlayerTurret->getLasterOrginPos();
		Vec2 targetPos = m_target->getPosition();
		setScaleX(m_pos.distance(targetPos) / 100.0f * 792);
		setRotation((targetPos - m_pos).getAngle());
	}
}