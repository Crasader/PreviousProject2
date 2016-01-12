#include "game/mahjong/MahjongView.h"
#include "game/mahjong/otherplayer/PlayerLeft.h"
#include "game/mahjong/otherplayer/PlayerRight.h"
#include "game/mahjong/otherplayer/PlayerOpposite.h"
#include "game/mahjong/PlayerHero.h"
#include "game/mahjong/anim/DealJongAnim.h"

bool MahjongView::init(){
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* view_bg = Sprite::create("gamemj/mj_background.jpg");
	view_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(view_bg,-1);

	drawMenu();

	//添加玩家到位置上
	drawPlayerLeft();
	drawPlayerRight();
	drawPlayerOpposite();
	drawPlayerHero();

	//添加自定义事件的监听
	addCoustomListener();
	//测试方法
	testButton();
	return true;
}

void MahjongView::drawMenu(){
	auto chatButton = MenuItemImage::create("gamemj/button_chat_1.png","gamemj/button_chat_2.png",CC_CALLBACK_0(MahjongView::chatButton,this));
	auto billingButton = MenuItemImage::create("gamemj/button_billing_1.png", "gamemj/button_billing_2.png", CC_CALLBACK_0(MahjongView::billingButton, this));
	auto packageButton = MenuItemImage::create("gamemj/button_package_1.png", "gamemj/button_package_2.png", CC_CALLBACK_0(MahjongView::packageButton, this));
	Menu* myMenu = Menu::create(chatButton, billingButton, packageButton,NULL);
	myMenu->setPosition(ccp(210,25));
	myMenu->alignItemsHorizontallyWithPadding(15);
	this->addChild(myMenu);

	auto quitBut = MenuItemImage::create("gamemj/button_quit_1.png", "gamemj/button_quit_2.png", CC_CALLBACK_0(MahjongView::quitButton, this));
	Menu* quit = Menu::create(quitBut, NULL);
	quit->setPosition(ccp(35,505));
	this->addChild(quit);
}

//绘制主角
void MahjongView::drawPlayerHero(){
	//TODO
	PlayerHero* playerHero = PlayerHero::create();
	this->addChild(playerHero,2);
}

//绘制左手边的玩家
void MahjongView::drawPlayerLeft(){
	PlayerLeft* playerLeft = PlayerLeft::create();
	this->addChild(playerLeft);
}


//绘制右手边的玩家
void MahjongView::drawPlayerRight(){
	PlayerRight* playerRight = PlayerRight::create();
	this->addChild(playerRight);

}


//绘制对面的玩家
void MahjongView::drawPlayerOpposite(){
	PlayerOpposite* playerOpposite = PlayerOpposite::create();
	this->addChild(playerOpposite);

}

void MahjongView::dealJongs(){
	DealJongAnim* dealJongAnim = DealJongAnim::create();
	this->addChild(dealJongAnim);
}

//聊天按钮
void MahjongView::chatButton(){

}



//账单按钮
void MahjongView::billingButton(){

}


//背包按钮
void MahjongView::packageButton(){


}

//退出按钮
void  MahjongView::quitButton(){
	EventCustom event("player_hero_turn");
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}


//自定义事件监听
void MahjongView::addCoustomListener(){
	auto dealJongListener = EventListenerCustom::create("deal_listener", [=](EventCustom* event){
		dealJongs();
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(dealJongListener, 1);
}


void MahjongView::addTouchListener(){
	//添加系统返回键监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			// TODO 展示退出界面
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}


//测试方法
void MahjongView::testEvent(){
	//EventCustom event("deal_listener");
	//Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}


//测试方法
void MahjongView::testButton(){
	//MenuItemImage* image = MenuItemImage::create("gamemj/test.png", "gamemj/test.png", CC_CALLBACK_0(MahjongView::testEvent, this));
	//Menu* testMenu = Menu::create(image, NULL);
	//testMenu->setPosition(ccp(480, 270));
	//this->addChild(testMenu, 1);
}