#include "TwiceSureChangePhoneDialog.h"
#include "server/HttpMannger.h"
#include "domain/bag/BagManager.h"
#include "domain/ToolTip/ToolTipMannger.h"




bool TwiceSureChangePhoneDialog::init()
{
	if (!MyDialog::init())
	{
		return false;
	}
	bool bRet = false;
	do{
		auto sp = Sprite::create("lingqujiangliTXT.png");
		sp->setPosition(480, 415);
		addChild(sp);

		auto frame = Sprite::create("RegisterInputFrame.png");
		frame->setPosition(Vec2(480, 230));
		addChild(frame);
		_editPhone = ui::EditBox::create(Size(270, 51), ui::Scale9Sprite::create());
		_editPhone->setPosition(Vec2(480, 230));
		_editPhone->setFontName("Arial");
		_editPhone->setFontSize(20);
		_editPhone->setFontColor(Color3B::YELLOW);
		_editPhone->setPlaceHolder(ChineseWord("feedbackTip").c_str());
		_editPhone->setPlaceholderFontColor(Color3B::GRAY);
		_editPhone->setPlaceholderFontSize(25);
		_editPhone->setMaxLength(14);
		_editPhone->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
		_editPhone->setDelegate(this);
		addChild(_editPhone);

		frame = Sprite::create("RegisterInputFrame.png");
		frame->setPosition(Vec2(480, 180));
		addChild(frame);
		_editRepeatPhone = ui::EditBox::create(Size(270, 51), ui::Scale9Sprite::create());
		_editRepeatPhone->setPosition(Vec2(480, 230));
		_editRepeatPhone->setFontName("Arial");
		_editRepeatPhone->setFontSize(20);
		_editRepeatPhone->setFontColor(Color3B::YELLOW);
		_editRepeatPhone->setPlaceHolder(ChineseWord("feedbackTip").c_str());
		_editRepeatPhone->setPlaceholderFontColor(Color3B::GRAY);
		_editRepeatPhone->setPlaceholderFontSize(25);
		_editRepeatPhone->setMaxLength(14);
		_editRepeatPhone->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
		_editRepeatPhone->setDelegate(this);
		addChild(_editRepeatPhone);
		



		auto bt = MenuItemImage::create("btn_tijiao_1.png", "btn_tijiao_2.png", CC_CALLBACK_1(TwiceSureChangePhoneDialog::quedingcallback, this));
		bt->setPosition(480, 60);




		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(TwiceSureChangePhoneDialog::closeButtonCallBack, this));
		close->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
		close->setPosition(960,540);



		auto menu = Menu::create(bt, close, nullptr);
		menu->setPosition(0, 0);
		addChild(menu);

		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(TwiceSureChangePhoneDialog::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(TwiceSureChangePhoneDialog::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(TwiceSureChangePhoneDialog::onTouchEnded, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
		bRet = true;
	} while (0);


	return bRet;
}
bool TwiceSureChangePhoneDialog::onTouchBegan(Touch *touch, Event *unused_event)
{

	return true;
}

void TwiceSureChangePhoneDialog::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
	log("editBox %p DidBegin !", editBox);
}

void TwiceSureChangePhoneDialog::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{
	log("editBox %p DidEnd !", editBox);
}

void TwiceSureChangePhoneDialog::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
	log("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void TwiceSureChangePhoneDialog::editBoxReturn(ui::EditBox* editBox)
{
	auto str = String::createWithFormat("%s", editBox->getText());
	editBox->setText(str->getCString());
	log("editBox %p was returned !", editBox);

}

void TwiceSureChangePhoneDialog::quedingcallback(Ref*)
{
	auto txt1 = _editPhone->getText();
	auto txt2 = _editRepeatPhone->getText();
	if (txt1==txt2&&strlen(txt1)==strlen("13011111111"))
	{
		EventListenerCustom* _listener2 = EventListenerCustom::create("change_gift", [=](EventCustom* event){
			changGiftValue*value = static_cast<changGiftValue*>(event->getUserData());
			if (value->_errorcode == 0)
			{
				BagManager::getInstance()->addreward(1013, -300);
			}
			else
			{

			}
			ToolTipMannger::showDioag(value->_errormsg);
			Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("change_gift");
			LoadingCircle::RemoveLoadingCircle();
			removeFromParentAndCleanup(1);

		});
		LoadingCircle::showLoadingCircle();
		Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listener2, 1);
		HttpMannger::getInstance()->HttpToPostRequestToChangeReward(1, txt1);
	}
	else
	{
		ToolTipMannger::showDioag("input error info!");
	}

}

void TwiceSureChangePhoneDialog::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}


