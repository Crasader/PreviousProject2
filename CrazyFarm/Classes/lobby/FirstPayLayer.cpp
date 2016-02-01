#include "lobby/FirstPayLayer.h"
#include "domain/user/User.h"
#include "domain/pay/Pay.h"
bool FirstPayLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	bool bRet = false;
	do 
	{
		auto layer = LayerColor::create();
		layer->setColor(Color3B::BLACK);
		layer->setOpacity(128);
		addChild(layer,-1);
		auto size = Director::getInstance()->getVisibleSize();
		auto bg = Sprite::create("firstPayBg.png");
		bg->setPosition(size / 2);
		addChild(bg);


		

		auto bt = MenuItemImage::create("btn_huoqu_1.png", "btn_huoqu_2.png", CC_CALLBACK_1(FirstPayLayer::quedingcallback, this));
		bt->setPosition(bg->getContentSize().width*0.6, 110);
	



		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(FirstPayLayer::closeButtonCallBack, this));
		close->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
		close->setPosition(bg->getContentSize());



		auto menu = Menu::create(bt, close, nullptr);
		menu->setPosition(0, 0);
		bg->addChild(menu);

		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(FirstPayLayer::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(FirstPayLayer::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(FirstPayLayer::onTouchEnded, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	//添加系统返回键监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			removeFromParentAndCleanup(1);
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
		bRet = true;
	} while (0);
	

	return bRet;
}
bool FirstPayLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}
void FirstPayLayer::quedingcallback(Ref*)
{
	//首冲HTTP请求
	Pay::getInstance()->Overbooking(14, m_eventPoint);

	removeFromParentAndCleanup(1);
}

void FirstPayLayer::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}

