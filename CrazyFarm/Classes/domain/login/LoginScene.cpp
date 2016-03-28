#include "LoginScene.h"
#include "LoginMannger.h"
#include "domain/loading/LoadingScene.h"
#include "domain/ToolTip/TwiceSureDialog.h"
Scene* LoginScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoginScene::create();
	scene->addChild(layer, 0, 888);
	return scene;
}

bool LoginScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto bg = Sprite::create("loginBg.png");
	bg->setPosition(480, 270);
	addChild(bg, -1);

	auto loginBt = MenuItemImage::create("loginGame_1.png", "loginGame_2.png", CC_CALLBACK_1(LoginScene::loginCallBack, this));
	loginBt->setPosition(480, 150);
	loginBt->setName("loginBt");
	auto menu = Menu::create(loginBt, nullptr);
	menu->setPosition(0, 0);
	addChild(menu,1,"menu");
	
	return true;
}
void LoginScene::loginCallBack(Ref*psend)
{
	((MenuItemImage*)psend)->setEnabled(false);
	LoginMannger::getInstance()->login();
	scheduleUpdate();
	nTempTime = 0;
	
}
void LoginScene::update(float delta)
{
	nTempTime += delta;
	if (LoginMannger::getInstance()->getisLoginSuccess())
	{
		Director::getInstance()->replaceScene(LoadingScene::createScene());
		unscheduleUpdate();
	}
	if (nTempTime>5)
	{
		auto menu = getChildByName("menu");
		auto bt = menu->getChildByName("loginBt");
		((MenuItemImage*)bt)->setEnabled(true);
		auto dioag = TwiceSureDialog::createDialog(ChineseWord("LoginTimeOut").c_str());
		dioag->setPosition(0, 0);
		addChild(dioag, 30);
		unscheduleUpdate();
	}
}