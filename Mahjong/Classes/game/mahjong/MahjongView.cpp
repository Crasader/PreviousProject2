#include "game/mahjong/MahjongView.h"
#include "game/mahjong/otherplayer/PlayerLeft.h"
#include "game/mahjong/otherplayer/PlayerRight.h"
#include "game/mahjong/otherplayer/PlayerOpposite.h"

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

	//�����ҵ�λ����
	drawPlayerLeft();
	drawPlayerRight();
	drawPlayerOpposite();
	drawPlayerHero();
	addCoustomListener();
	return true;
}

//��������
void MahjongView::drawPlayerHero(){
	//TODO
    
}

//�������ֱߵ����
void MahjongView::drawPlayerLeft(){
	PlayerLeft* playerLeft = PlayerLeft::create();
	this->addChild(playerLeft);
}


//�������ֱߵ����
void MahjongView::drawPlayerRight(){
	PlayerRight* playerRight = PlayerRight::create();
	this->addChild(playerRight);

}


//���ƶ�������
void MahjongView::drawPlayerOpposite(){
	PlayerOpposite* playerOpposite = PlayerOpposite::create();
	this->addChild(playerOpposite);

}



void MahjongView::addCoustomListener(){
	auto dealJongListener = EventListenerCustom::create("deal_listener", [=](EventCustom* event){

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
