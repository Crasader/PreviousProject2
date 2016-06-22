#include "SetupScene.h"
#include "MainScene.h"
#include "tools/StringManager.h"
#include "tools/VolumeScene.h"
#include "tools/RankingScene.h"

USING_NS_CC;

Scene* SetupScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SetupScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SetupScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//添加背景
    auto background = Sprite::create("background.png");
	auto pos = Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
    background->setPosition(pos);
    this->addChild(background);

	//添加对话框
	auto dialog = Sprite::create("dialog.png");
	dialog->setScale(2.0f);
	auto size = dialog->getContentSize() * dialog->getScale();
	dialog->setPosition(pos);
	this->addChild(dialog);

	//对话框分割线
	auto bar = Sprite::create("dialog_bar.png");
	bar->setScale(2.0f);
	bar->setPosition(Vec2(pos.x, pos.y - size.height/2 + size.height/4*3));
	this->addChild(bar);

	//添加标题
	auto text = StringManager::GetInstance()->GetString("setup");
	auto title = Label::createWithTTF(text, "fonts/MNJKATONG.ttf", 100);	//加载迷你简卡通字体
	if (title != NULL)
	{
		title->setColor(Color3B::ORANGE);
		title->setPosition(Vec2(pos.x, pos.y + size.height/2 - size.height/8));
		addChild(title);
	}

	//////////////////////////////
	// 2. 添加菜单
	auto volumeItem = MenuItemImage::create(
		"setup/volume_normal.png",
		"setup/volume_pressed.png",
		CC_CALLBACK_1(SetupScene::menuVolumeCallback, this));
	auto height = volumeItem->getContentSize().height;
	auto val = (size.height/4*3 - height*3)/4;
	volumeItem->setPosition(Vec2(pos.x, pos.y - size.height/2 + val*3 + height*2 + height/2));

// 	auto levelItem = MenuItemImage::create(
// 		"setup/level_normal.png",
// 		"setup/level_pressed.png",
// 		CC_CALLBACK_1(SetupScene::menuLevelCallback, this));
// 	levelItem->setPosition(Vec2(pos.x, pos.y - size.height/2 + val*3 + height*2 + height/2));

	auto rankingItem = MenuItemImage::create(
		"setup/ranking_normal.png",
		"setup/ranking_pressed.png",
		CC_CALLBACK_1(SetupScene::menuRankingCallback, this));
	rankingItem->setPosition(Vec2(pos.x, pos.y - size.height/2 + val*2 + height*1 + height/2));

	auto returnItem = MenuItemImage::create(
		"setup/return_normal.png",
		"setup/return_pressed.png",
		CC_CALLBACK_1(SetupScene::menuReturnCallback, this));
	returnItem->setPosition(Vec2(pos.x, pos.y - size.height/2 + val + height/2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(volumeItem, /*levelItem, */rankingItem, returnItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

    return true;
}

void SetupScene::menuVolumeCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(VolumeScene::createScene());
}

void SetupScene::menuLevelCallback(cocos2d::Ref* pSender)
{

}
void SetupScene::menuRankingCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(RankingScene::createScene());
}

void SetupScene::menuReturnCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(MainScene::createScene());
}

void SetupScene::buttonPopupCallback(cocos2d::Ref* sender, ButtonResult result)
{
	switch (result)
	{
	case ButtonResult::BUTTONRESULT_NONE:
		NULL;
		break;
	default:
		break;
	}
}