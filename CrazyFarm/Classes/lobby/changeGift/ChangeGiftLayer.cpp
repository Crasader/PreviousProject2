#include "ChangeGiftLayer.h"
#include "domain/user/User.h"
#include "domain/bag/BagManager.h"
#include "utill/Chinese.h"
#include "server/HttpMannger.h"
#include "RecordGiftLayer.h"
#include "domain/ToolTip/ToolTipMannger.h"
#include "widget/MyLabelAtlas.h"

bool ChangeGiftLayer::init()
{
	if ( !BaseLayer::init() )
	{
		return false;
	}
	bool bRet = false;
	do 
	{
	
		auto size = Director::getInstance()->getVisibleSize();
		auto bg = Sprite::create("changeRewardBg.png");
		bg->setPosition(size / 2);
		addChild(bg);


		auto label = LabelTTF::create(ChineseWord("ChangeGiftTxt").c_str(), "arial", 18);
		label->setPosition(bg->getContentSize().width / 2, 383);
		label->setAnchorPoint(Point::ANCHOR_MIDDLE);
		bg->addChild(label);

		auto str = Value(BagManager::getInstance()->getItemNum(1013)/10).asString();
		auto num = MyLabelAtlas::create(str.c_str(), "medalNum.png", 16, 24, '0',30);
		num->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
		num->setPosition(100, 0);
		label->addChild(num);

		//换奖品列表
		for (int i = 1; i <= 3;i++)
		{
			auto cell = ChangeGiftCell::create();
			cell->setValue(i);
			cell->setAnchorPoint(Point::ANCHOR_MIDDLE);
			if (i==2)
			{
				cell->setisSelected(true);
			}
			else
			{
				cell->setisSelected(false);
			}
			cell->setPosition(139+12.5 + cell->getContentSize().width/2+cell->getContentSize().width*0.85*(i-1), 200);
			addChild(cell, 1, i);
		}
		auto chakan = MenuItemImage::create("btn_small_1.png", "btn_small_2.png", CC_CALLBACK_1(ChangeGiftLayer::chakanButtonCallBack, this));
		chakan->setPosition(575,383);


		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(ChangeGiftLayer::closeButtonCallBack, this));
		close->setAnchorPoint(Point::ANCHOR_MIDDLE);
		close->setPosition(bg->getContentSize()-Size(50,50));



		auto menu = Menu::create(close, chakan, nullptr);
		menu->setPosition(0, 0);
		bg->addChild(menu);

		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(ChangeGiftLayer::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(ChangeGiftLayer::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(ChangeGiftLayer::onTouchEnded, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	//添加系统返回键监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:

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
bool ChangeGiftLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}
void ChangeGiftLayer::onTouchMoved(Touch *touch, Event *unused_event)
{

}
void ChangeGiftLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	auto pos = touch->getLocation();
	ChangeGiftCell* seleteCell = nullptr;
	for (int i = 1; i <= 3;i++)
	{
		auto cell = (ChangeGiftCell*)getChildByTag(i);
		if (cell->getBoundingBox().containsPoint(pos))
		{
			seleteCell = cell;
			break;
		}
	}
	if (seleteCell!=nullptr)
	{
		for (int i = 1; i <= 3;i++)
		{
			auto cell = (ChangeGiftCell*)getChildByTag(i);
			if (cell == seleteCell)
			{
				cell->setisSelected(true);
			}
			else
			{
				cell->setisSelected(false);
			}
		}
	}


}
void ChangeGiftLayer::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}

void ChangeGiftLayer::chakanButtonCallBack(Ref*psend)
{
	EventListenerCustom* _listener2 = EventListenerCustom::create("record_gift_info", [=](EventCustom* event){

		RecordGiftValue*value = static_cast<RecordGiftValue*>(event->getUserData());
		if (value->_errorcode == 0)
		{
			auto layer = RecordGiftLayer::create(value->_items);
			layer->setPosition(0, 0);
			addChild(layer, 30);
		}
		else
		{
			ToolTipMannger::showDioag(value->_errormsg);
		}

		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("record_gift_info");
		LoadingCircle::RemoveLoadingCircle();

	});
	LoadingCircle::showLoadingCircle();
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listener2, 1);
	HttpMannger::getInstance()->HttpToPostRequestToRecordGift();
}