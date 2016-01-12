#include "NobilityLayer.h"
#include "User.h"
bool NobilityLayer::init()
{
	if (!Layer::init()){
		return false;
	}	


	auto colorlayer = LayerColor::create();
	colorlayer->setColor(ccc3(0, 0, 0));
	colorlayer->setOpacity(180);
	addChild(colorlayer, -1);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	
	auto bg = Sprite::create("NobilityBG.png");
	bg->setPosition(visibleSize / 2);
	addChild(bg);





	return true;

}
NobilityLayer * NobilityLayer::createLayer()
{
	NobilityLayer *ret = new  NobilityLayer();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}