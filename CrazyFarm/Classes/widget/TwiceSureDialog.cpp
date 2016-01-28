#include "TwiceSureDialog.h"

TwiceSureDialog* TwiceSureDialog::createDialog(const char* tipStr, const ccMenuCallback& callback)
{
	TwiceSureDialog* ref = new TwiceSureDialog();
	if (ref&&ref->init(tipStr,callback))
	{
		ref->autorelease();
	}
	else
	{
		ref = nullptr;
	}
	return ref;
}

void TwiceSureDialog::setCloseButtonCallback(const ccMenuCallback& closecallback)
{
	close->setCallback(closecallback);
}

bool TwiceSureDialog::init(const  char* tipStr, const ccMenuCallback& callback)
{
	Layer::init();
	bool bRet = false;
	do
	{
		auto colorlayer = LayerColor::create();
		colorlayer->setColor(ccc3(0, 0, 0));
		colorlayer->setOpacity(180);
		addChild(colorlayer, -1);
		
		auto bg = Sprite::create("TwiceSureDialog.png");
		bg->setPosition(480, 270);
		addChild(bg, -1);

		close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(TwiceSureDialog::closeButtonCallBack, this));
		close->setPosition(bg->getContentSize());
		
		auto sure = MenuItemImage::create("btn_queding.png", "btn_queding_2.png", callback);
		sure->setPosition(bg->getContentSize().width / 2, 40);

		auto menu = Menu::create(close, sure, nullptr);
		menu->setPosition(bg->getPosition()-bg->getContentSize()/2);
		addChild(menu);


		auto label = LabelTTF::create(tipStr, "arial", 20);
		label->setColor(Color3B(12, 64, 109));
		label->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
		label->setDimensions(Size(261, 0));
		label->setPosition(bg->getContentSize().width / 2, 163);
			bg->addChild(label);

		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(TwiceSureDialog::onTouchBegan, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);

		//添加系统返回键监听
		auto listener = EventListenerKeyboard::create();
		listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
			switch (code)
			{
			case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
				/*removeFromParentAndCleanup(1);*/
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

void TwiceSureDialog::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}