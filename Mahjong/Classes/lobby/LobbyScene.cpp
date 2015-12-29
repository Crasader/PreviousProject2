#include "lobby/LobbyScene.h"


bool LobbyScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//add game bg to layer
	Sprite* lobby_bg = Sprite::create("main/mainbk.jpg");
	lobby_bg->setScale(0.5);
	lobby_bg->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(lobby_bg,-1);
	//add statr menu to layer

	//MenuItemImage* start_btn = MenuItemImage::create("start_game_normal.png","start_game_pressed.png",CC_CALLBACK_0(LobbyScene::startGame,this));
	//Menu* start_game = Menu::create(start_btn,NULL);
	//start_game->setPosition(visibleSize.width/2,visibleSize.height/4);
	//this->addChild(start_game);

	//   //金币显示的背景框
	//Sprite* playerGold = Sprite::create("fish_gold.png");
	//playerGold->setPosition(ccp(visibleSize.width-150,visibleSize.height-50));
	//this->addChild(playerGold);
	////金币数字显示
	//LabelAtlas* playerGoldNum = LabelAtlas::create("200", "player_gold_num.png", 14, 19, '0');
	//playerGoldNum->setPosition(ccp(visibleSize.width - 120, visibleSize.height - 60));
	//this->addChild(playerGoldNum);

	////金币充值按钮
	//MenuItemImage* recharge_image = MenuItemImage::create("fish_gold.png", "fish_gold.png", CC_CALLBACK_0(LobbyScene::rechargeGold, this));
	//Menu* recharge = Menu::create(recharge_image,NULL);
	//recharge->setPosition(ccp(visibleSize.width -50, visibleSize.height - 50));
	//this->addChild(recharge);

	////设置按钮
	//MenuItemImage* settting_img = MenuItemImage::create("btn_setting.png", "btn_setting.png", CC_CALLBACK_0(LobbyScene::showSettingLayer, this));
	//Menu* settting = Menu::create(settting_img, NULL);
	//settting->setPosition(ccp(50,100));
	//this->addChild(settting);

	////公告底图
	//auto bgk = Sprite::createWithSpriteFrameName("input_bg.png");
	//bgk->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 150));
	//addChild(bgk);

	//// 公告上的喇叭
	//auto bgv = Sprite::createWithSpriteFrameName("bt_paste.png");
	//bgv->setPosition(Vec2(visibleSize.width / 2-150, visibleSize.height / 2 + 150));
	//addChild(bgv);



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

}

void LobbyScene::rechargeGold(){
	//TODO 弹出计费点
}

void LobbyScene::showSettingLayer(){
	//TODO 弹出设置界面
}