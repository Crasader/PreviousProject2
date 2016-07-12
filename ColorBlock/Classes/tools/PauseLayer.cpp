#include "PauseLayer.h"
#include "StringManager.h"
#include "MsgDefine.h"
USING_NS_CC;
using namespace ui;

// on "init" you need to initialize your instance
bool PauseLayer::init()
{
	if ( !BaseLayer::init() )
	{
		return false;
	}

	//获取游戏区域
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();



	//标题
	auto title = Sprite::createWithSpriteFrameName("titlePause.png");
	title->setPosition(238, 616+600);
	addChild(title);

	title->runAction(EaseElasticOut::create(MoveBy::create(0.3f, Vec2(0, -600))));

	//按键
	auto exitBt = MenuItemSprite::create(SPRITE("btBackOnPause_1.png"),SPRITE("btBackOnPause_2.png"), CC_CALLBACK_1(BaseLayer::menuExitCallback, this));
	exitBt->setPosition(84, 312);
	auto continueBt = MenuItemSprite::create(SPRITE("btContinueOnPause_1.png"), SPRITE("btContinueOnPause_2.png"), CC_CALLBACK_1(BaseLayer::menuContinueCallback, this));
	continueBt->setPosition(240, 415);
	auto reStartBt = MenuItemSprite::create(SPRITE("btRestartOnPause_1.png"), SPRITE("btRestartOnPause_2.png"), CC_CALLBACK_1(BaseLayer::menuReStartCallback, this));
	reStartBt->setPosition(480-84, 312);


	auto menu = Menu::create(exitBt, continueBt, reStartBt, nullptr);
	menu->setPosition(0, 0);
	addChild(menu);

	for (auto item:menu->getChildren())
	{
		item->setScale(0.1);
		item->runAction(EaseElasticOut::create(ScaleTo::create(0.3f, 1.0)));
	}

	return true;
}