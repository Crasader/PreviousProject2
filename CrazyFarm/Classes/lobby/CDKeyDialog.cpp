#include "lobby/CDKeyDialog.h"
#include "server/HttpMannger.h"
#include "domain/ToolTip/TwiceSureDialog.h"
#include "utill/FunUtil.h"
bool CDKeyDialog::init()
{
	if ( !BaseLayer::init() )
	{
		return false;
	}
	bool bRet = false;
	do 
	{
		auto size = Director::getInstance()->getVisibleSize();
		auto bg = Sprite::create("TwiceSureDialog.png");
		bg->setPosition(size / 2);
		addChild(bg);


		auto frame = Sprite::create("RegisterInputFrame.png");
		frame->setPosition(Vec2(bg->getContentSize().width / 2, 130));
		bg->addChild(frame);

		_editRepeatword = ui::EditBox::create(Size(270, 51), ui::Scale9Sprite::create());
		_editRepeatword->setPosition(Vec2(bg->getContentSize().width / 2, 130));
		_editRepeatword->setFontName("Arial");
		_editRepeatword->setFontSize(20);
		_editRepeatword->setFontColor(Color3B::YELLOW);
		_editRepeatword->setPlaceHolder(ChineseWord("cinYourCDkey").c_str());
		_editRepeatword->setPlaceholderFontColor(Color3B::GRAY);
		_editRepeatword->setPlaceholderFontSize(25);
		_editRepeatword->setMaxLength(14);
		_editRepeatword->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
		_editRepeatword->setDelegate(this);
		bg->addChild(_editRepeatword);

		auto tip = Sprite::create("cinYourCDkey.png");
		tip->setPosition(Vec2(bg->getContentSize().width / 2, 184));
		bg->addChild(tip);

		

		auto bt = MenuItemImage::create("btn_queding.png", "btn_queding_2.png", CC_CALLBACK_1(CDKeyDialog::quedingcallback, this));
		bt->setPosition(bg->getContentSize().width / 2, 48);
	



		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(CDKeyDialog::closeButtonCallBack, this));
		close->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
		close->setPosition(bg->getContentSize() + Size(10, 10));



		auto menu = Menu::create(bt, close, nullptr);
		menu->setPosition(0, 0);
		bg->addChild(menu);

		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(CDKeyDialog::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(CDKeyDialog::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(CDKeyDialog::onTouchEnded, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);


		

		auto aniNode = Sprite::create();
		aniNode->setPosition(20, 100);
		bg->addChild(aniNode, 5);
		aniNode->runAction(getForeverAcByNameAndInterval("aniBubble", 0));

		aniNode = Sprite::create();
		aniNode->setPosition(bg->getContentSize().width - 20, 100);
		bg->addChild(aniNode, 5);
		runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create([=]{aniNode->runAction(getForeverAcByNameAndInterval("aniBubble", 0)); }), nullptr));
		bRet = true;
	} while (0);
	

	return bRet;
}
bool CDKeyDialog::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}
void CDKeyDialog::quedingcallback(Ref*send)
{
	auto item = (MenuItem*)send;
	item->setEnabled(false);

	auto listen = EventListenerCustom::create("CDKEY", [=](EventCustom*event)
	{
		CDkeyValue *value = (CDkeyValue*)(event->getUserData());
		TwiceSureDialog*dialog;
		switch (value->_errorcode)
		{
		case 0:
			dialog = TwiceSureDialog::createDialog("get cdkey successful");
			break;
		case 404:
			dialog = TwiceSureDialog::createDialog("time out");
			break;
		default:
			dialog = TwiceSureDialog::createDialog(value->_errormsg.c_str());
			break;
		}
		dialog->setPosition(0, 0);
		getParent()->addChild(dialog, 30);
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("CDKEY");
		removeFromParentAndCleanup(true);

	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listen, 1);
	HttpMannger::getInstance()->HttpToPostRequestCDKey(_editRepeatword->getText());
	
}

void CDKeyDialog::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(true);
}

void CDKeyDialog::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
	log("editBox %p DidBegin !", editBox);
}

void CDKeyDialog::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{
	log("editBox %p DidEnd !", editBox);
}

void CDKeyDialog::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
	log("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void CDKeyDialog::editBoxReturn(ui::EditBox* editBox)
{
	auto str = String::createWithFormat("%s", editBox->getText());
	editBox->setText(str->getCString());
	log("editBox %p was returned !", editBox);

}
void CDKeyDialog::httpCallback(Ref*psend)
{
	CDkeyValue *value = (CDkeyValue*)psend;
	TwiceSureDialog*dialog;
	switch (value->_errorcode)
	{
	case 0:
		dialog = TwiceSureDialog::createDialog("get cdkey successful");
		break;
	case 404:
		dialog = TwiceSureDialog::createDialog("time out");
		break;
	default:
		dialog = TwiceSureDialog::createDialog(value->_errormsg.c_str());
		break;
	}
	dialog->setPosition(0, 0);
	getParent()->addChild(dialog, 30);
	NotificationCenter::getInstance()->removeObserver(this, "CDKEY");
	removeFromParentAndCleanup(true);
}