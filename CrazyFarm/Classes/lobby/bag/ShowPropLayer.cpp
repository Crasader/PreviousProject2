#include "lobby/bag/ShowPropLayer.h"
#include "domain/user/User.h"
#include "lobby/bag/BagCell.h"
#include "domain/bag/BagManager.h"
#include "utill/FunUtil.h"


ShowPropLayer*ShowPropLayer::create(int itemid)
{
	ShowPropLayer *pRet = new ShowPropLayer();
	if (pRet && pRet->init(itemid))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool ShowPropLayer::init(int itemid)
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
		auto bg = Sprite::create("showItemBg.png");
		bg->setPosition(size / 2);
		addChild(bg);

		BagItem item;
		item.itemId = itemid;
		item.num = BagManager::getInstance()->getItemNum(itemid);
		auto cell = BagCell::create();
		cell->setValue(item);
		cell->setPosition(480, 33);
		addChild(cell);
		
		Iitem = ConfigItem::getInstance()->getItemById(itemid);
		auto label = LabelTTF::create(Iitem.itemName.c_str(), "arial", 20);
		label->setPosition(480, 300);
		label->setAnchorPoint(Point::ANCHOR_MIDDLE);
		addChild(label);

		auto str = String::createWithFormat(ChineseWord("itemDanJia").c_str(), Iitem.buyPrice);
		label = LabelTTF::create(str->getCString(), "arail", 18);
		label->setColor(Color3B::YELLOW);
		label->setPosition(320, 250);
		label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
		addChild(label);

		label = LabelTTF::create(Iitem.itemDesc.c_str(), "arail", 18);
		label->setPosition(320, 230);
		label->setDimensions(Size(283, 0));
		label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
		addChild(label);


		auto BtBuy = MenuItemImage::create("btn_goumai_1.png", "btn_goumai_2.png", CC_CALLBACK_1(ShowPropLayer::quedingcallback, this));
		BtBuy->setPosition(480+90,80);
		
		auto BtSend = MenuItemImage::create("btn_zengsong_1.png", "btn_zengsong_2.png", CC_CALLBACK_1(ShowPropLayer::quedingcallback, this));
		BtSend->setPosition(480-90, 80);


		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(ShowPropLayer::closeButtonCallBack, this));
		close->setPosition(644,470);



		auto menu = Menu::create(BtBuy,BtSend, close, nullptr);
		menu->setPosition(0, 0);
		addChild(menu);

		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(ShowPropLayer::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(ShowPropLayer::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(ShowPropLayer::onTouchEnded, this);
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
bool ShowPropLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

void ShowPropLayer::quedingcallback(Ref*)
{
	
}

void ShowPropLayer::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}

