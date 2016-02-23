#include "ChangeGiftLayer.h"
#include "domain/user/User.h"
#include "domain/bag/BagManager.h"
#include "utill/Chinese.h"




bool ChangeGiftLayer::init()
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
		auto bg = Sprite::create("changeRewardBg.png");
		bg->setPosition(size / 2);
		addChild(bg);


		auto label = LabelTTF::create(ChineseWord("ChangeGiftTxt").c_str(), "arial", 20);
		label->setPosition(bg->getContentSize().width / 2+10, 380);
		label->setAnchorPoint(Point::ANCHOR_MIDDLE);
		bg->addChild(label);

		auto str = Value(BagManager::getInstance()->getItemNum(1013)).asString();
		auto num = LabelAtlas::create(str.c_str(), "medalNum.png", 16, 24, '0');
		num->setPosition(104, 0);
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
			cell->setPosition(139+12.5 + cell->getContentSize().width/2+cell->getContentSize().width*0.85*(i-1), 220);
			addChild(cell, 1, i);
		}

		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(ChangeGiftLayer::closeButtonCallBack, this));
		close->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
		close->setPosition(bg->getContentSize());



		auto menu = Menu::create(close, nullptr);
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

