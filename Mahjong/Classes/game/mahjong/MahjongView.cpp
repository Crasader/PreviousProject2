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
	Sprite* view_bg = Sprite::create("gamemj/mjzhuobu.jpg");
	view_bg->setScale(0.5);
	view_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(view_bg);

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

//绘制主角
void MahjongView::drawPlayerHero(){
	//TODO
	PlayerHero* playerHero = PlayerHero::create();
	this->addChild(playerHero);
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
	EventCustom event("deal_listener");
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}


//测试方法
void MahjongView::testButton(){
	MenuItemImage* image = MenuItemImage::create("gamemj/test.png", "gamemj/test.png", CC_CALLBACK_0(MahjongView::testEvent, this));
	Menu* testMenu = Menu::create(image, NULL);
	testMenu->setPosition(ccp(480, 270));
	this->addChild(testMenu, 1);
}