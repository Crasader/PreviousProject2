#include "WaitCircle.h"
#include "domain/pay/Pay.h"

void WaitCircle::ShowPayWaitCircle()
{
	auto circle = WaitCircle::create();
	circle->setName("payCircle");
	circle->setPosition(480, 270);
	Director::getInstance()->getRunningScene()->addChild(circle, 30);
}
void WaitCircle::RemovePayWaitCircle()
{
	auto circle = Director::getInstance()->getRunningScene()->getChildByName("payCircle");
	if (circle)
	{
		circle->removeFromParentAndCleanup(1);
	}
}

void WaitCircle::sendRequestWaitCirCle()
{
	auto circle = Director::getInstance()->getRunningScene()->getChildByName("payCircle");
	if (circle)
	{
		auto node = (WaitCircle*)(circle); 
		node->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([=]{node->DemandEntry(); }), nullptr));
	}
}

bool WaitCircle::init()
{
	initWithFile("lightRorate_5.png");
	runAction(RepeatForever::create(RotateBy::create(2.0f, 360)));

	auto listenr1 = EventListenerTouchOneByOne::create();
	listenr1->onTouchBegan = CC_CALLBACK_2(WaitCircle::onTouchBegan, this);
	listenr1->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);


	runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([=]{DemandEntry(); }),nullptr));
	return true;
}
void WaitCircle::DemandEntry()
{
	static int reqnum = 0;
	Pay::getInstance()->DemandEntry(++reqnum);
}


