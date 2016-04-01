#include "LoadingCircle.h"
LoadingCircle*LoadingCircle::_circle = nullptr;
LoadingCircle* LoadingCircle::create()
{
	LoadingCircle* bRet = new LoadingCircle();
	if (bRet&&bRet->init())
	{
		bRet->autorelease(); 
			return bRet; 
	}
	else 
	{ 
	  delete bRet; 
	  bRet = NULL; 
	  return NULL; 
	} 
}

bool LoadingCircle::init()
{
	Sprite::initWithFile("waitcircle.png");
	bool bRet = false;
	while (!bRet)
	{
		
		runAction(RepeatForever::create(RotateBy::create(2.0f, 360)));

		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = [](Touch*touch, Event* event){
			return true;
		};
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);
		bRet = true;
	}
	return bRet;
}

void LoadingCircle::showLoadingCircle()
{
	_circle = LoadingCircle::create();
	_circle->setPosition(480, 270);
	Director::getInstance()->getRunningScene()->addChild(_circle, 100);

	auto colorLayer = LayerColor::create();
	colorLayer->setColor(Color3B::BLACK);
	colorLayer->setOpacity(150);
	_circle->getParent()->addChild(colorLayer, _circle->getZOrder() - 1, "loadingColorBg");
}
void LoadingCircle::RemoveLoadingCircle()
{
	if (_circle)
	{
		auto node = _circle->getParent()->getChildByName("loadingColorBg");
		if (node)
		{
			node->removeFromParentAndCleanup(1);
		}
		_circle->removeFromParentAndCleanup(1);
		_circle = nullptr;
	}
	else
	{
		return;
	}
}