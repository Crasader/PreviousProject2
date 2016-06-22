#include "BaseLayer.h"
#include "StringManager.h"

USING_NS_CC;
using namespace ui;

// on "init" you need to initialize your instance
bool BaseLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	//Ìí¼Ó±³¾°Í¼Æ¬
	auto colorlayer = LayerColor::create();
	colorlayer->setColor(ccc3(0, 0, 0));
	colorlayer->setOpacity(180);
	addChild(colorlayer, -1);
	//´¥ÃşÆÁ±Î
	auto listenr1 = EventListenerTouchOneByOne::create();
	listenr1->onTouchBegan = [=](Touch*touch, Event*event){return true; };
	listenr1->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);

	return true;
}

void BaseLayer::menuReStartCallback(cocos2d::Ref* sender)
{
	removeFromParentAndCleanup(1);
	EventCustom event(MSG_REBEGIN);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}
void BaseLayer::menuExitCallback(cocos2d::Ref* sender)
{
	removeFromParentAndCleanup(1);
	EventCustom event(MSG_BACKMAINSCENE);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}
void BaseLayer::menuContinueCallback(cocos2d::Ref* sender)
{
	removeFromParentAndCleanup(1);
	EventCustom event(MSG_RESUME);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}