#include "lobby/LobbyScene.h"
#include "game/mahjong/MjGameScene.h"


bool LobbyScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//add game bg to layer
	Sprite* lobby_bg = Sprite::create("main/mainbk.jpg");
	lobby_bg->setPosition(visibleSize.width/2,visibleSize.height/2);
	lobby_bg->setScale(0.5);
	this->addChild(lobby_bg,-1);
	//add statr menu to layer

	MenuItemImage* mahjong = MenuItemImage::create("main/mainmajiang.png", "main/mainmajiang.png", CC_CALLBACK_0(LobbyScene::startGame,this));
	mahjong->setScale(0.5);
	Menu* gameMenu = Menu::create(mahjong,NULL);
	gameMenu->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(gameMenu, 1);
	


	//添加系统返回键监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			//TODO 展示退出界面
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void LobbyScene::startGame(){
	Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
}