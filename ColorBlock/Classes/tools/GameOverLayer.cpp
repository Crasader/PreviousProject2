#include "GameOverLayer.h"
#include "StringManager.h"

USING_NS_CC;
using namespace ui;

// on "init" you need to initialize your instance
bool GameOverLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	//获取游戏区域
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto title = SPRITE("txtGameOver.png");
	title->setPosition(240, 510);
	addChild(title);

	auto btBack = MenuItemSprite::create(SPRITE("btBack_1.png"), SPRITE("btBack_2.png"),nullptr, CC_CALLBACK_1(BaseLayer::menuExitCallback,this));
	btBack->setPosition(140, 150);

	auto btRestart = MenuItemSprite::create(SPRITE("btPlayAgain_1.png"), SPRITE("btPlayAgain_2.png"), nullptr, CC_CALLBACK_1(BaseLayer::menuReStartCallback, this));
	btRestart->setPosition(480 - 140, 150);

	auto menu = Menu::create(btBack, btRestart, nullptr);
	menu->setPosition(0, 0);
	addChild(menu);


	return true;
}
