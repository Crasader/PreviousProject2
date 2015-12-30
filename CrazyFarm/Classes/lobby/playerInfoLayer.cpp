#include "lobby/playerInfoLayer.h"
#include "ConfigItem.h"
Scene* PlayInfoLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = PlayInfoLayer::create();

	scene->addChild(layer);

	return scene;
}

bool PlayInfoLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	bool bRet = false;
	do 
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
	//add game bg to layer

		auto bg = Sprite::create("game_pause.jpg");
		bg->setPosition(visibleSize / 2);
		addChild(bg);

	//添加系统返回键监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			removeFromParentAndCleanup(1);
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
		bRet = true;
	} while (bRet);
	

	return true;
}

