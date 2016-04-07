#include "lobby/bag/SetNameLayer.h"
#include "server/HttpMannger.h"
#include "domain/user/User.h"
#include "server/HttpMsgDefine.h"
#include "domain/ToolTip/TwiceSureDialog.h"
#include "domain/login/LoginMannger.h"
#include "widget/LoadingCircle.h"
bool SetNameLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	bool bRet = false;
	do 
	{
		auto colorbg = LayerColor::create();
		colorbg->setPosition(0, 0);
		colorbg->setColor(Color3B::BLACK);
		colorbg->setOpacity(128);
		addChild(colorbg, -1);

		auto bg = Sprite::create("RegisterBg.png");
		bg->setPosition(480, 270);
		addChild(bg,0,"bg");

		sex = 0;
		auto spor = Sprite::create("or.png");
		spor->setPosition(480, 400);
		addChild(spor);

		sexBoy = SexHead::create(0, 1);
		sexBoy->setPosition(480 - 65, 400);
		addChild(sexBoy);

		sexGirl = SexHead::create(1, 0);
		sexGirl->setPosition(480 + 65, 400);
		addChild(sexGirl);



		auto size = bg->getContentSize();

		///请输入账号
		auto txt1 = Sprite::create("TxtInputName.png");
		txt1->setPosition(size.width / 2, 288);
		bg->addChild(txt1);

		auto frame = Sprite::create("RegisterInputFrame.png");
		frame->setPosition(Vec2(size.width / 2, 250));
		bg->addChild(frame);

		_editNickname = ui::EditBox::create(Size(270, 51), ui::Scale9Sprite::create());
		_editNickname->setPosition(Vec2(size.width / 2, 250));
		_editNickname->setFontName("Arial");
		_editNickname->setFontSize(20);
		_editNickname->setFontColor(Color3B::YELLOW);
		_editNickname->setPlaceHolder(ChineseWord("InputName_1").c_str());
		_editNickname->setPlaceholderFontColor(Color3B::GRAY);
		_editNickname->setPlaceholderFontSize(25);
		_editNickname->setMaxLength(14);
		_editNickname->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
		_editNickname->setDelegate(this);
		bg->addChild(_editNickname);
		///请输入密码
		txt1 = Sprite::create("TxtInputPassword.png");
		txt1->setPosition(size.width / 2, 215);
		bg->addChild(txt1);



		frame = Sprite::create("RegisterInputFrame.png");
		frame->setPosition(Vec2(size.width / 2, 176));
		bg->addChild(frame);
		_editPassword = ui::EditBox::create(Size(270, 51), ui::Scale9Sprite::create());
		_editPassword->setPosition(Vec2(size.width / 2, 176));
		_editPassword->setFontName("Arial");
		_editPassword->setFontSize(20);
		_editPassword->setFontColor(Color3B::YELLOW);
		_editPassword->setPlaceHolder(ChineseWord("InputName_2").c_str());
		_editPassword->setPlaceholderFontColor(Color3B::GRAY);
		_editPassword->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
		_editPassword->setPlaceholderFontSize(25);
		_editPassword->setMaxLength(14);
		_editPassword->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
		_editPassword->setDelegate(this);
		bg->addChild(_editPassword);
		///请再次输入密码
		txt1 = Sprite::create("TxtRepetInputPassword.png");
		txt1->setPosition(size.width / 2, 142);
		bg->addChild(txt1);



		frame = Sprite::create("RegisterInputFrame.png");
		frame->setPosition(Vec2(size.width / 2, 105));
		bg->addChild(frame);
		_editRepeatword = ui::EditBox::create(Size(270, 51), ui::Scale9Sprite::create());
		_editRepeatword->setPosition(Vec2(size.width / 2, 105));
		_editRepeatword->setFontName("Arial");
		_editRepeatword->setFontSize(20);
		_editRepeatword->setFontColor(Color3B::YELLOW);
		_editRepeatword->setPlaceHolder(ChineseWord("InputName_3").c_str());
		_editRepeatword->setPlaceholderFontColor(Color3B::GRAY);
		_editRepeatword->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
		_editRepeatword->setPlaceholderFontSize(25);
		_editRepeatword->setMaxLength(14);
		_editRepeatword->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
		_editRepeatword->setDelegate(this);
		bg->addChild(_editRepeatword);


		auto sureBt = MenuItemImage::create("btn_queding.png", "btn_queding_2.png", CC_CALLBACK_1(SetNameLayer::quedingcallback, this));
		sureBt->setPosition(size.width / 2, 40);
		sureBt->setName("sureBt");

		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(SetNameLayer::closeButtonCallBack, this));
		close->setPosition(size);
		close->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);

		auto menu = Menu::create(close, sureBt, nullptr);
		menu->setPosition(0, 0);
		bg->addChild(menu, 1, "menu");
		scheduleUpdate();


		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(SetNameLayer::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(SetNameLayer::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(SetNameLayer::onTouchEnded, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
		bRet = true;
	} while (0);
	

	return bRet;
}
bool SetNameLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	auto pos = touch->getLocation();
	auto rect1 = sexBoy->getBoundingBox();
	auto rect2 = sexGirl->getBoundingBox();
	if (rect1.containsPoint(pos))
	{
		sexBoy->setIsChoose(true);
		sexGirl->setIsChoose(false);
		sex = 0;
	}
	else if (rect2.containsPoint(pos))
	{
		sexBoy->setIsChoose(false);
		sexGirl->setIsChoose(true);
		sex = 1;
	}
	return true;
}

void SetNameLayer::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
	log("editBox %p DidBegin !", editBox);
}

void SetNameLayer::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{
	log("editBox %p DidEnd !", editBox);
}

void SetNameLayer::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
	log("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void SetNameLayer::editBoxReturn(ui::EditBox* editBox)
{
	auto str = String::createWithFormat("%s", editBox->getText());
	editBox->setText(str->getCString());
	log("editBox %p was returned !", editBox);

}

void SetNameLayer::quedingcallback(Ref*psend)
{

	auto item = (MenuItem*)psend;
	item->setEnabled(false);
	std::string nickname = _editNickname->getText();
	std::string password = _editPassword->getText();
	std::string repeatPassword = _editRepeatword->getText();

	int type = checkRegister(nickname, password, repeatPassword);//TODO:校验处理
	if (type == 0)
	{
		HttpMannger::getInstance()->HttpToPostRequestBindName(nickname.c_str(), sex, password.c_str());
		LoadingCircle::showLoadingCircle();
		NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(SetNameLayer::httpCallback), "setname", NULL);
		item->setEnabled(false);
	}
	else
	{
		auto dialog = TwiceSureDialog::createDialog("error parame");
		dialog->setPosition(0, 0);
		getParent()->addChild(dialog,30);
		item->setEnabled(true);
	}

}

void SetNameLayer::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}

bool SetNameLayer::checkTheName(const char* name)
{
	CCLOG("%d", std::strlen(name));
	return true;
}

int  SetNameLayer::checkRegister(std::string nickname, std::string password, std::string repetPassword)
{
	if (nickname.size() > 5 && nickname.size() < 13 && password.size() > 5 && password.size() < 13 && password == repetPassword)
	{
		return 0;
	}
	else
	{
		return -1;
	}
	if (nickname == "" || password == "" || repetPassword == "")
	{
		return -1;
	}
}

void SetNameLayer::httpCallback(Ref*psend)
{
	LoadingCircle::RemoveLoadingCircle();
	SetNameValue *value = (SetNameValue*)psend;
	auto menu = getChildByName("bg")->getChildByName("menu");
	auto bt = ((MenuItem*)(menu->getChildByName("sureBt")));
	TwiceSureDialog*dialog;
	switch (value->_errorcode)
	{
	case 0:
		LoginMannger::getInstance()->removeMemoryNickname(User::getInstance()->getUserName().c_str());
		User::getInstance()->setUserName(_editNickname->getText());
		User::getInstance()->setUserGender(sex);
		User::getInstance()->setHaveSetName();
		dialog = TwiceSureDialog::createDialog("set name successful");
		LoginMannger::getInstance()->addMemoryNickname(_editNickname->getText(), _editPassword->getText());
		
		break;
	case 404:
		dialog = TwiceSureDialog::createDialog("time out");
		bt->setEnabled(true);
		break;
	default:
		dialog = TwiceSureDialog::createDialog(value->_errormsg.c_str());
		bt->setEnabled(true);
		break;
	}
	dialog->setPosition(0, 0);
	getParent()->addChild(dialog, 30);
	NotificationCenter::getInstance()->removeObserver(this, "CDKEY");
	if (value->_errorcode==0)
	{
		removeFromParentAndCleanup(true);
	}
	
}