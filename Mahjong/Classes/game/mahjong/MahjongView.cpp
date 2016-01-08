#include "game/mahjong/MahjongView.h"
#include "game/mahjong/otherplayer/PlayerLeft.h"
#include "game/mahjong/otherplayer/PlayerRight.h"
#include "game/mahjong/otherplayer/PlayerOpposite.h"
#include "game/mahjong/PlayerHero.h"

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

	//����Զ����¼��ļ���
	addCoustomListener();
	//���Է���
	testButton();
	return true;
}

//��������
void MahjongView::drawPlayerHero(){
	//TODO
	PlayerHero* playerHero = PlayerHero::create();
	this->addChild(playerHero);
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

void MahjongView::dealJongs(){
	dealJongsAnim();
}


void MahjongView::dealJongsAnim(){
	//step1 ���Ʒ��Ƶ�����
	Sprite* pai1 = Sprite::create("gamemj/xiaogais.png");
	pai1->setPosition(ccp(0, 0));
	Sprite* pai2 = Sprite::create("gamemj/xiaogais.png");
	pai2->setPosition(ccp(50, 0));
	Sprite* pai3 = Sprite::create("gamemj/xiaogais.png");
	pai3->setPosition(ccp(0, 20));
	Sprite* pai4 = Sprite::create("gamemj/xiaogais.png");
	pai4->setPosition(ccp(50, 20));
	Sprite* total = Sprite::create();
	total->setScale(0.3f);
	total->setAnchorPoint(ccp(0, 0));
	total->setPosition(ccp(460, 260));
	total->addChild(pai1);
	total->addChild(pai2);
	total->addChild(pai3);
	total->addChild(pai4);
	this->addChild(total);
	

	//step2 ��ʼ�ַ�����
	for (int i = 0; i < 3; i++){
	
	}
	ScaleTo* scale = ScaleTo::create(0.2f, 1.0f);
	MoveTo* move1 = MoveTo::create(0.2f, ccp(480, 50));
	Spawn* spawn1 = Spawn::create(scale, move1,NULL);
	MoveTo* move2= MoveTo::create(0.2f, ccp(960, 260));
	Spawn* spawn2 = Spawn::create(scale, move2, NULL);
	MoveTo* move3 = MoveTo::create(0.2f, ccp(480, 500));
	Spawn* spawn3 = Spawn::create(scale, move3, NULL);
	MoveTo* move4 = MoveTo::create(0.2f, ccp(0, 260));
	Spawn* spawn4 = Spawn::create(scale, move4, NULL);
	Sequence* seq = Sequence::create(spawn1, spawn2, spawn3, spawn4,NULL);
	total->runAction(seq);
}


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
	EventCustom event("deal_listener");
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}


//���Է���
void MahjongView::testButton(){
	MenuItemImage* image = MenuItemImage::create("gamemj/test.png", "gamemj/test.png", CC_CALLBACK_0(MahjongView::testEvent, this));
	Menu* testMenu = Menu::create(image, NULL);
	testMenu->setPosition(ccp(480, 270));
	this->addChild(testMenu, 1);
}