#include "lobby/LobbyScene.h"
#include "core/GameScene.h"
#include "utill/Chinese.h"
#include "utill/AnimationUtil.h"
#include "ConfigItem.h"
#include "config/ConfigVipLevel.h"
#include "config/ConfigTurrent.h"
#include "User.h"
Scene* LobbyScene::createScene()
{
	auto scene = Scene::create();

	auto layer = LobbyScene::create();

	scene->addChild(layer);

	return scene;
}

bool LobbyScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
    //add all fish plsit
	loadResource();
	auto user = User::getInstance();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* lobby_bg = Sprite::create("lobbyBG.png");
	lobby_bg->setPosition(visibleSize.width/2,visibleSize.height/2);
	addChild(lobby_bg,-1);

	

	//头像框
	auto spHeadFrame = Sprite::create("HeadFrame.png");
	spHeadFrame->setPosition(visibleSize.width*0.14, visibleSize.height*0.9);
	addChild(spHeadFrame);
	auto sssize = spHeadFrame->getContentSize();

	auto spHead = Sprite::create();
	int sex = rand() % 2;
	if (sex)
	{
		spHead->setTexture("headMan.png");
	}
	else
	{
		spHead->setTexture("headWomen.png");
	}
	spHead->setPosition(sssize.width*0.14, sssize.height*0.63);
	spHeadFrame->addChild(spHead);

	auto userName = LabelTTF::create(user->getUserName(), "arial", 20);
	userName->setPosition(sssize.width*0.6, sssize.height*0.87);
	spHeadFrame->addChild(userName);

	auto userlevel = LabelTTF::create(Value(user->getLevel()).asString().c_str(), "arial", 20);
	userlevel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	userlevel->setPosition(sssize.width*0.245, sssize.height *0.17);
	spHeadFrame->addChild(userlevel);

	auto viplevelFrame = Sprite::create("viplevelFrame.png");
	viplevelFrame->setPosition(sssize.width * 1.05, sssize.height*0.88);
	auto viplevel = LabelTTF::create(Value(user->getVipLevel()).asString().c_str(), "arial", 20);
	viplevel->setPosition(Vec2(viplevelFrame->getContentSize() / 2)+Vec2(0,2));
	viplevelFrame->addChild(viplevel);
	spHeadFrame->addChild(viplevelFrame);

	auto exeDescribe = LabelTTF::create(user->getLevelDesc(), "arial", 17);
	exeDescribe->setPosition(sssize.width*0.63, sssize.height*0.47);
	spHeadFrame->addChild(exeDescribe);

	//金币
	auto coinFrame = Sprite::create("coinFrame.png");
	coinFrame->setPosition(visibleSize.width*0.45, visibleSize.height*0.95);
	addChild(coinFrame);
	sssize = coinFrame->getContentSize();
	auto coin = Sprite::create("coin.png");
	coin->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	coin->setPosition(3, sssize.height *0.49);
	coinFrame->addChild(coin);

	auto userCoin = LabelTTF::create(Value(user->getCoins()).asString().c_str(), "arial", 20);
	userCoin->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	userCoin->setPosition(sssize.width*0.85, sssize.height *0.5);
	userCoin->setColor(Color3B(254,248,52));
	coinFrame->addChild(userCoin);

	auto addCoin = MenuItemImage::create("addBtn_nor.png", "addBtn_click.png", CC_CALLBACK_1(LobbyScene::payCoinCallback,this));
	addCoin->setAnchorPoint(Point::ANCHOR_MIDDLE);
	addCoin->setPosition(coinFrame->getPositionX() + sssize.width*0.48, coinFrame->getPositionY());


	//钻石
	auto diamondFrame = Sprite::create("coinFrame.png");
	diamondFrame->setPosition(visibleSize.width*0.74, visibleSize.height*0.95);
	addChild(diamondFrame);
	sssize = diamondFrame->getContentSize();
	auto diamond = Sprite::create("diamond.png");
	diamond->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	diamond->setPosition(1, sssize.height *0.495);
	diamond->setScale(0.8);
	diamondFrame->addChild(diamond);

	auto userdiamond = LabelTTF::create(Value(user->getDiamonds()).asString().c_str(), "arial", 20);
	userdiamond->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	userdiamond->setPosition(sssize.width*0.85, sssize.height *0.5);
	userdiamond->setColor(Color3B(254, 248, 52));
	diamondFrame->addChild(userdiamond);

	auto adddiamond = MenuItemImage::create("addBtn_nor.png", "addBtn_click.png", CC_CALLBACK_1(LobbyScene::payDiamondCallback, this));
	adddiamond->setAnchorPoint(Point::ANCHOR_MIDDLE);
	adddiamond->setPosition(diamondFrame->getPositionX() + sssize.width*0.48, diamondFrame->getPositionY());



	auto menu = Menu::create(addCoin, adddiamond, nullptr);
	menu->setPosition(Point::ZERO);
	addChild(menu);
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


void LobbyScene::loadResource(){
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fish_frame_0.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fish_frame_2.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fish_frame_5.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fish_frame_8.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fish_frame_10.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fish_frame_11.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fish_frame_14.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fish_frame_16.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("batch_frame_bullet.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gun_frame.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("batch_frame_net.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gift_frame.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game_scene_frame.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("unlock_cannon_frame.plist");
	///load ani
	AnimationUtil::getInstance()->addAnimationBySpriteName("ani/water/aniWater%d.jpg","aniWater",2.0f,20);
	AnimationUtil::getInstance()->addAnimationBySpriteName("ani/shootFire/aniShoot%d.png", "aniShoot", 0.5f, 5);
	AnimationUtil::getInstance()->addAnimationBySpriteName("ani/bubble/aniBubble%d.png", "aniBubble", 2.0f, 19);
	//load json
	ConfigItem::getInstance()->LoadConfig();
	ConfigVipLevel::getInstance()->LoadConfig();
	ConfigTurrent::getInstance()->LoadConfig();
}


void LobbyScene::createRoomLayer()
{

}


void LobbyScene::payCoinCallback(Ref*psend)
{

}
void LobbyScene::payDiamondCallback(Ref*psend)
{

}