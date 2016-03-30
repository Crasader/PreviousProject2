#include "lobby/CDKeyDialog.h"
#include "server/HttpMannger.h"
#include "domain/ToolTip/TwiceSureDialog.h"
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
		bg->setPosition(size / 2+Size(0,50));
		addChild(bg);


		auto frame = Sprite::create("RegisterInputFrame.png");
		frame->setPosition(Vec2(bg->getContentSize().width / 2, 154));
		bg->addChild(frame);

		_editRepeatword = ui::EditBox::create(Size(270, 51), ui::Scale9Sprite::create());
		_editRepeatword->setPosition(Vec2(bg->getContentSize().width / 2, 154));
		_editRepeatword->setFontName("Arial");
		_editRepeatword->setFontSize(20);
		_editRepeatword->setFontColor(Color3B::YELLOW);
		_editRepeatword->setPlaceHolder(ChineseWord("InputName_1").c_str());
		_editRepeatword->setPlaceholderFontColor(Color3B::GRAY);
		_editRepeatword->setPlaceholderFontSize(25);
		_editRepeatword->setMaxLength(14);
		_editRepeatword->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
		_editRepeatword->setDelegate(this);
		bg->addChild(_editRepeatword);


		

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
	HttpMannger::getInstance()->HttpToPostRequestCDKey(_editRepeatword->getText());
		NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(CDKeyDialog::httpCallback), "CDKEY", NULL);
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