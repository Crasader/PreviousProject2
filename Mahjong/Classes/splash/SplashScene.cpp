#include "splash/SplashScene.h"
#include "lobby/LobbyScene.h"

Scene* SplashScene::createScene()
{
	auto scene = Scene::create();

	auto layer = SplashScene::create();

	scene->addChild(layer);

	return scene;
}

bool SplashScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//add all  plsit
	loadResource();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//add game bg to layer
	Sprite* splash_bg = Sprite::create("mainlogin/login.jpg");
	splash_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	splash_bg->setScale(0.5);
	this->addChild(splash_bg, -1);

	//添加登录按钮
	MenuItemImage* phoneLogin = MenuItemImage::create("mainlogin/zcbt1.png", "mainlogin/zcbt1.png", CC_CALLBACK_0(SplashScene::loginByPhone, this));
	phoneLogin->setScale(0.5);
	phoneLogin->setPosition(-150, -6);
	MenuItemImage* passLogin = MenuItemImage::create("mainlogin/zcbt2.png", "mainlogin/zcbt2.png", CC_CALLBACK_0(SplashScene::loginByPass, this));
	passLogin->setScale(0.5);
	passLogin->setPosition(150, 0);
	MenuItemImage* visitorLogin = MenuItemImage::create("mainlogin/zcbt4.png", "mainlogin/zcbt4.png", CC_CALLBACK_0(SplashScene::loginByVisitor, this));
	visitorLogin->setScale(0.5);
	visitorLogin->setPosition(350, 0);
	Menu* loginMenu = Menu::create(phoneLogin, passLogin, visitorLogin,NULL);
	loginMenu->setPosition(visibleSize.width / 2,80);
	//loginMenu->alignItemsHorizontallyWithPadding(40);
	this -> addChild(loginMenu,1);

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



void SplashScene::loginByPhone(){
	Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
}

void SplashScene::loginByPass(){
	Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
}

void SplashScene::loginByVisitor(){
	Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
}


void SplashScene::loadResource(){
	// TODO 
}