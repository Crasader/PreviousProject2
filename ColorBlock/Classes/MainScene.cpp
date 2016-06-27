#include "MainScene.h"
#include "GameScene.h"
#include "AboutScene.h"
#include "SetupScene.h"
#include "Sqlite/DBManager.h"
#include "tools/ExitLayer.h"
#include "tools/VolumeScene.h"
#include "DragModeGameMainScene.h"
#include "utill/Audio.h"
#include "utill/AnimationUtil.h"
#include "utill/MyMenuItemButton.h"
#include "MsgDefine.h"
USING_NS_CC;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	//获取数据库信息
	DBManager::GetInstance()->GetDataFromDB();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	SpriteManager::GetInstance()->InitSpriteFramesWithFile("MainScene.plist");

	//////////////////////////////
	// 2. 添加背景图
	auto background = Sprite::create("background_main.png");
	background->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
	this->addChild(background, -1);


	auto title = Sprite::createWithSpriteFrameName("title.png");
	title->setPosition(visibleSize.width / 2, 600);
	addChild(title, -1);
    /////////////////////////////
    // 3. 添加菜单
	auto FallDownModeBt = MenuItemSprite::create(
		SPRITE("FallDownModeBt_1.png"),
		SPRITE("FallDownModeBt_2.png"),
		CC_CALLBACK_1(MainScene::menuStartCallback, this));
	FallDownModeBt->setPosition(240,393);
	FallDownModeBt->setTag(1);

	auto DragModeBt = MenuItemSprite::create(
		SPRITE("DragModeBt_1.png"),
		SPRITE("DragModeBt_2.png"),
		CC_CALLBACK_1(MainScene::menuStartCallback, this));
	DragModeBt->setPosition(240,249);
	DragModeBt->setTag(2);


	float cx = 80;
	float cy = 105;
	float dx = 110;

	auto giftItem = MyMenuItemButton::create(
		"menuItemFrame_1.png",
		"menuItemFrame_2.png",
		Sprite::createWithSpriteFrameName("gift.png"),
		CC_CALLBACK_1(MainScene::menuGiftCallback, this));
	giftItem->setPosition(cx,cy);
	cx += dx;

	auto moreGameItem = MyMenuItemButton::create(
		"menuItemFrame_1.png",
		"menuItemFrame_2.png",
		Sprite::createWithSpriteFrameName("moreGame.png"),
		CC_CALLBACK_1(MainScene::menuMoreGameCallback, this));
	moreGameItem->setPosition(cx, cy);
	cx += dx;


	auto sp = Sprite::createWithSpriteFrameName("menuItemFrame_1.png");
	auto open = Sprite::createWithSpriteFrameName("open.png");
	open->setPosition(sp->getContentSize() / 2);
	sp->addChild(open);

	auto sp1 = Sprite::createWithSpriteFrameName("menuItemFrame_2.png");
	auto open1 = Sprite::createWithSpriteFrameName("open.png");
	open1->setPosition(sp1->getContentSize() / 2);
	sp1->addChild(open1);
	auto  openItem = MenuItemSprite::create(sp,sp1);

	sp = Sprite::createWithSpriteFrameName("menuItemFrame_1.png");
	auto close = Sprite::createWithSpriteFrameName("close.png");
	close->setPosition(sp->getContentSize() / 2);
	sp->addChild(close);

	sp1 = Sprite::createWithSpriteFrameName("menuItemFrame_2.png");
	auto close1 = Sprite::createWithSpriteFrameName("close.png");
	close1->setPosition(sp1->getContentSize() / 2);
	sp1->addChild(close1);
	auto closeItem = MenuItemSprite::create(sp,sp1);
	MenuItemToggle* volumBt;
	if (DBManager::GetInstance()->GetBgmVolume()>0)
	{
		volumBt = MenuItemToggle::createWithTarget(this, menu_selector(MainScene::menuMusicCallback), openItem, closeItem, nullptr);
	}
	else
	{
		volumBt = MenuItemToggle::createWithTarget(this, menu_selector(MainScene::menuMusicCallback), closeItem, openItem, nullptr);
	}
	volumBt->setPosition(cx, cy);
	cx += dx;

	auto aboutItem = MyMenuItemButton::create(
		"menuItemFrame_1.png",
		"menuItemFrame_2.png",
		Sprite::createWithSpriteFrameName("help.png"),
		CC_CALLBACK_1(MainScene::menuAboutCallback, this));
	aboutItem->setPosition(cx, cy);
	cx += dx;


    // create menu, it's an autorelease object
    m_menu = Menu::create(FallDownModeBt,DragModeBt,giftItem,aboutItem,volumBt,moreGameItem,nullptr);
    m_menu->setPosition(Vec2::ZERO);
    this->addChild(m_menu, 1);
    
	//Android按键监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(MainScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//没有弹出层
	m_bPopupLayerWorking = false;
	loadRes();
    return true;
}
void MainScene::loadRes()
{
	static bool isLoad = false;
	if (!isLoad)
	{
		isLoad = true;
		AnimationUtil::getInstance()->addAnimationBySpriteFrameName("TX_xiaochu.plist", "TX_xiaochu_%.4d.png", "ani_xiaochu", 0.15f, 25);
		AnimationUtil::getInstance()->addAnimationBySpriteFrameName("Tx_Flower.plist", "treasure_chest_%.4d@2x.png", "ani_flower", 0.5f, 12);
		AnimationUtil::getInstance()->addAnimationBySpriteFrameName("Tx_Scrap.plist", "scrap%.2d.png", "ani_scrap", 0.5f, 7);
		SpriteManager::GetInstance()->InitSpriteFramesWithFile("otherScene.plist");
	}
}
void MainScene::menuMusicCallback(Ref*psend)
{
	if (DBManager::GetInstance()->GetBgmVolume()>0)
	{
		DBManager::GetInstance()->SetBgmVolume(0);
	}
	else
	{
		DBManager::GetInstance()->SetBgmVolume(50);
	}
	Audio::getInstance()->setBGMValue(DBManager::GetInstance()->GetBgmVolume());
}
//按键按下
void MainScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	//在弹出层启用的条件下屏蔽按键消息
	if (m_bPopupLayerWorking)
	{
		return;
	}
}

//按键弹起
void MainScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	//在弹出层启用的条件下屏蔽按键消息
	if (m_bPopupLayerWorking)
	{
		return;
	}

	//log("key:%d", (int)keyCode);
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_BACK:	//返回键(Only avaliable on Desktop and Android)
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		//退出游戏
		ExitGame();
#endif
		break;
	case EventKeyboard::KeyCode::KEY_MENU:	//菜单键(Only avaliable on Desktop and Android)
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		NULL;
#endif
	default:
		break;
	}
}

//退出游戏
void MainScene::ExitGame()
{
	//启用弹出层
	m_bPopupLayerWorking = true;

	auto exit = ExitLayer::create();
	exit->SetCallBackFunc(CC_CALLBACK_2(MainScene::buttonPopupCallback, this));
	addChild(exit, 111);
}

//弹出框按钮事件
void MainScene::buttonPopupCallback(Ref* sender, ButtonResult result)
{
	//没有弹出层
	m_bPopupLayerWorking = false;

	switch (result)
	{
	case ButtonResult::BUTTONRESULT_EXIT:		//退出游戏
		DoExitGame();
		break;
	case ButtonResult::BUTTONRESULT_CONTINUE:	//取消退出游戏
		this->getEventDispatcher()->pauseEventListenersForTarget(m_menu, true);
		this->scheduleOnce(schedule_selector(MainScene::DelayContinue), 0.3f);
		break;
	default:
		break;
	}
}

//延时进入主界面
void MainScene::DelayContinue(float dt)
{
	this->getEventDispatcher()->resumeEventListenersForTarget(m_menu, true);
}

//确认退出游戏
void MainScene::DoExitGame()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void MainScene::menuStartCallback(Ref* pSender)
{
	int tag = ((Node*)pSender)->getTag();
	if (tag ==1)
	{
		Director::getInstance()->replaceScene(GameScene::createScene());
	}
	else
	{
		Director::getInstance()->replaceScene(DragModeGameMainScene::createScene());
	}
}

void MainScene::menuMoreGameCallback(cocos2d::Ref* pSender)
{

}

void MainScene::menuGiftCallback(cocos2d::Ref* pSender)
{
	
}

void MainScene::menuAboutCallback(cocos2d::Ref* pSender)
{

}

void MainScene::menuDragModeGameCallback(Ref*psend)
{
	
}
