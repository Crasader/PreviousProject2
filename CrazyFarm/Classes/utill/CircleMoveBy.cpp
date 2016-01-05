#include "CircleMoveBy.h"



CircleMoveBy* CircleMoveBy::create(float duration, const CCPoint& center, float scale, float angle)
{
	CircleMoveBy *pRet = new CircleMoveBy();
	pRet->initWithDuration(duration, center, scale, angle);
	pRet->autorelease();

	return pRet;
}

bool CircleMoveBy::initWithDuration(float duration, const CCPoint& center, float scaleDiff, float angle)
{
	if (CCActionInterval::initWithDuration(duration))
	{
		this->m_duration = duration;
		this->m_center = center;
		this->m_scaleDiff = scaleDiff;
		this->m_currScale = 1.0f;
		this->m_angle = angle;

		/************************************************************************/
		/* 计算每次update调用时需要转动的弧度                                   */
		/************************************************************************/
		this->m_anglePreFrame = angle / duration * CCDirector::sharedDirector()->getAnimationInterval() / (180 / M_PI);
		this->m_frameCnts = 0;
		return true;
	}
	return false;
}

void CircleMoveBy::startWithTarget(CCNode *pTarget)
{
	CCActionInterval::startWithTarget(pTarget);
	m_initPos = pTarget->getPosition();
}
void CircleMoveBy::update(float time)
{
	m_frameCnts++;
	m_currScale += m_scaleDiff;

	CCPoint newPos = ccpRotateByAngle(m_initPos, m_center, m_frameCnts * m_anglePreFrame);
	CCPoint diff = ccpSub(newPos, m_center);
	newPos = diff * m_currScale + m_center;

	getTarget()->setPosition(newPos);

	

	//debug
#if 1
	CCLOG("circle pos x:%f y:%f", newPos.x, newPos.y);
	CCDrawNode *node = CCDrawNode::create();
	node->drawDot(newPos, 3, ccc4f(128, 128, 128, 128));
	getTarget()->getParent()->addChild(node);
#endif

}