#include "LoginScene.h"
#include "LoginMannger.h"
#include "domain/loading/LoadingScene.h"
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
	auto bg = Sprite::create("lobbyBG.jpg");
	bg->setPosition(480, 270);
	addChild(bg, -1);

	auto loginBt = MenuItemImage::create("quickbegin_1.png", "quickbegin_2.png", CC_CALLBACK_1(LoginScene::loginCallBack, this));
	loginBt->setPosition(480, 150);
	auto menu = Menu::create(loginBt, nullptr);
	menu->setPosition(0, 0);
	addChild(menu);
	return true;
}
void LoginScene::loginCallBack(Ref*psend)
{
	LoginMannger::getInstance()->login();
	Director::getInstance()->replaceScene(LoadingScene::createScene());
}