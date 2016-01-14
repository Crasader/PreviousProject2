#include "game/mahjong/MahjongView.h"
#include "game/mahjong/player/PlayerLeft.h"
#include "game/mahjong/player/PlayerRight.h"
#include "game/mahjong/player/PlayerOpposite.h"
#include "game/mahjong/player/PlayerHero.h"
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

	//�����ҵ�λ����
	drawPlayerLeft();
	drawPlayerRight();
	drawPlayerOpposite();
	drawPlayerHero();

	//����Զ����¼��ļ���
	addCoustomListener();
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

//��������
void MahjongView::drawPlayerHero(){
	//TODO
	PlayerHero* playerHero = PlayerHero::create();
	PlayerInfo* head = new PlayerInfo();
	playerHero->drawHeadPortrait(head);
	playerHero->setHeadPostion(ccp(50, 120));
	this->addChild(playerHero,2);
}

//�������ֱߵ����
void MahjongView::drawPlayerLeft(){
	PlayerLeft* playerLeft = PlayerLeft::create();
	//ͷ��Ļ���
	PlayerInfo* head = new PlayerInfo();
	playerLeft->drawHeadPortrait(head);
	playerLeft->setHeadPostion(ccp(50,360));
	this->addChild(playerLeft);
}


//�������ֱߵ����
void MahjongView::drawPlayerRight(){
	PlayerRight* playerRight = PlayerRight::create();
	PlayerInfo* head = new PlayerInfo();
	playerRight->drawHeadPortrait(head);
	playerRight->setHeadPostion(ccp(910, 360));
	this->addChild(playerRight);

}


//���ƶ�������
void MahjongView::drawPlayerOpposite(){
	PlayerOpposite* playerOpposite = PlayerOpposite::create();
	PlayerInfo* head = new PlayerInfo();
	playerOpposite->drawHeadPortrait(head);
	playerOpposite->setHeadPostion(ccp(285, 460));
	this->addChild(playerOpposite);

}

void MahjongView::dealJongs(){
	DealJongAnim* dealJongAnim = DealJongAnim::create();
	this->addChild(dealJongAnim);
}

//
Sprite* test;
void MahjongView::chatButton(){

}



//�˵���ť
void MahjongView::billingButton(){

}


//������ť
void MahjongView::packageButton(){


}

//�˳���ť
void  MahjongView::quitButton(){
	EventCustom event("player_turn");
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}


//�Զ����¼�����
void MahjongView::addCoustomListener(){
	auto dealJongListener = EventListenerCustom::create("deal_listener", [=](EventCustom* event){
		dealJongs();
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(dealJongListener, 1);
}


void MahjongView::addTouchListener(){
	//���ϵͳ���ؼ�����
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			// TODO չʾ�˳�����
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}


//���Է���
void MahjongView::testEvent(){
	//EventCustom event("deal_listener");
	//Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}


//���Է���
void MahjongView::testButton(){
	//MenuItemImage* image = MenuItemImage::create("gamemj/test.png", "gamemj/test.png", CC_CALLBACK_0(MahjongView::testEvent, this));
	//Menu* testMenu = Menu::create(image, NULL);
	//testMenu->setPosition(ccp(480, 270));
	//this->addChild(testMenu, 1);
}