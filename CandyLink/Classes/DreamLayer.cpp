#include "DreamLayer.h"
#include "GameData.h"
USING_NS_CC;

DreamLayer* DreamLayer::create(int dreamId) {
	auto dre = new DreamLayer();
	if (dre && dre->init(dreamId)) {
		dre->autorelease();
		return dre;
	}
	else {
		CC_SAFE_DELETE(dre);
		return nullptr;
	}
}

bool DreamLayer::init(int dreamId) {
	if (!Layer::init()) {
		return false;
	}
	loadContent(dreamId);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch *touch, Event *unused_event) {
		return true;
	};
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

void DreamLayer::loadContent(int id) {
	auto visiblieSize = Director::getInstance()->getVisibleSize();
    
	auto bg = Sprite::create("payui/pay_bg.png");
	bg->setPosition(visiblieSize.width / 2, visiblieSize.height / 2);
	addChild(bg);
    if(id == 6 || id == 12 ||id == 13 ||id == 14){
        bg->setTexture("ay_bg_1.png");
    }
    auto title = Sprite::create();
    title->setPosition(visiblieSize.width / 2, visiblieSize.height / 2 + 100);
    addChild(title);
    if(id == 1){
        title->setTexture("pay_title_1.png");
    }else if(id == 2){
         title->setTexture("pay_title_2.png");
    }else if(id == 3){
        title->setTexture("pay_title_3.png");
    }else if(id == 4){
        title->setTexture("pay_title_4.png");
    }else if(id == 5){
        title->setTexture("pay_title_5.png");
    }else if(id == 6){
        title->setTexture("pay_title_6 .png");
    }
    
	auto box = Sprite::create();
	box->setPosition(visiblieSize.width / 2, visiblieSize.height / 2-30 );
	addChild(box);
    if(id == 1||id ==3){
        box->setTexture("pay_tip_goods_1.png");
    }else if(id ==2||id == 7||id == 8||id == 9||id == 10){
          box->setTexture("pay_tip_goods_2.png");
    }else if(id == 4){
        box->setTexture("pay_tip_goods_3.png");
    }else if(id == 5){
        box->setTexture("pay_tip_goods_4.png");
    }
    if(id == 6 || id == 12 ||id == 13 ||id == 14){
        box->setVisible(false);
    }

	auto confirm = MenuItemImage::create("payui/pay_confirm_up.png","payui/pay_confirm_down.png",CC_CALLBACK_1(DreamLayer::doConfirmEvent,this));
	confirm->setTag(id);
	auto confirmMenu = Menu::create(confirm, NULL);
	confirmMenu->setPosition(visiblieSize.width/2, visiblieSize.height / 2-200);
	addChild(confirmMenu);

	auto close = MenuItemImage::create("payui/pay_cancel_up.png", "payui/pay_cancel_down.png", CC_CALLBACK_1(DreamLayer::closeView, this));
	close->setTag(id);
	auto closeMenu = Menu::create(close, NULL);
	closeMenu->setPosition(visiblieSize.width-20, visiblieSize.height-20);
	addChild(closeMenu);
}

void DreamLayer::doConfirmEvent(Ref* ref) {
	MenuItem* tem = (MenuItem*)ref;
	int id = tem->getTag();
    if(id == 1){
        GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Playing;
        GAMEDATA::getInstance()->settime(20);
    }
	removeFromParent();
}

void DreamLayer::closeView(Ref* ref) {
	MenuItemImage* tem = (MenuItemImage*)ref;
	int id = tem->getTag();
    if(id == 1){
        GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Playing;
        GAMEDATA::getInstance()->settime(20);
    }
	removeFromParent();
}

