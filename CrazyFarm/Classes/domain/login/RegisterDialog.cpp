#include "RegisterDialog.h"
#include "LoginMannger.h"
#include "utill/Chinese.h"
#include "domain/loading/LoadingScene.h"
#include "server/HttpMsgDefine.h"
#include "domain/ToolTip/TwiceSureDialog.h"
#include "domain/user/User.h"
#include "domain/Newbie/NewbieMannger.h"
bool RegisterDialog::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto colorbg = LayerColor::create();
	colorbg->setPosition(0, 0);
	colorbg->setColor(Color3B::BLACK);
	colorbg->setOpacity(128);
	addChild(colorbg, -1);

	auto bg = Sprite::create("RegisterBg.png");
	bg->setPosition(480, 270);
	addChild(bg);

	sex = 0;
	auto spor = Sprite::create("or.png");
	spor->setPosition(480, 400);
	addChild(spor);

	sexBoy = SexHead::create(0, 1);
	sexBoy->setPosition(480-65, 400);
	addChild(sexBoy);

	sexGirl = SexHead::create(1, 0);
	sexGirl->setPosition(480+65, 400);
	addChild(sexGirl);



	auto size = bg->getContentSize();

	///ÇëÊäÈëÕËºÅ
	auto txt1 = Sprite::create("TxtInputName.png");
	txt1->setPosition(size.width / 2, 288);
	bg->addChild(txt1);

	auto frame = Sprite::create("RegisterInputFrame.png");
	frame->setPosition(Vec2(size.width / 2, 250));
	bg->addChild(frame);

	_editNickname = ui::EditBox::create(Size(270, 51), ui::Scale9Sprite::create());
	_editNickname->setPosition(Vec2(size.width/2, 250));
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
	///ÇëÊäÈëÃÜÂë
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
	///ÇëÔÙ´ÎÊäÈëÃÜÂë
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


	auto sureBt = MenuItemImage::create("btn_queding.png", "btn_queding_2.png", CC_CALLBACK_1(RegisterDialog::loginCallBack, this));
	sureBt->setPosition(size.width/2, 40);
	sureBt->setName("surebt");
	auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(RegisterDialog::closeCallBack, this));
	close->setPosition(size);
	close->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
	
	auto menu = Menu::create(close, sureBt, nullptr);
	menu->setPosition(0, 0);
	bg->addChild(menu, 1, "menu");
	scheduleUpdate();


	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(RegisterDialog::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(RegisterDialog::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(RegisterDialog::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	return true;
}
void RegisterDialog::closeCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}

int  RegisterDialog::checkRegister(std::string nickname, std::string password, std::string repetPassword)
{
	if (nickname.size()>5 && nickname.size()<13 && password.size()>5&&password.size()<13&&password==repetPassword)
	{
		return 0;
	}
	else
	{
		return -1;
	}
	if (nickname==""||password==""||repetPassword=="")
	{
		return -1;
	}
}
void RegisterDialog::loginCallBack(Ref*psend)
{
	std::string nickname = _editNickname->getText();
	std::string password = _editPassword->getText();
	std::string repeatPassword = _editRepeatword->getText();

	int type = checkRegister(nickname, password, repeatPassword);
	if (type==0)
	{
		LoginMannger::getInstance()->toRegister(nickname.c_str(), password.c_str(), sex);

		((MenuItemImage*)psend)->setEnabled(false);
		NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(RegisterDialog::httpCallback), "register", NULL);
	}
	
}


bool RegisterDialog::onTouchBegan(Touch *touch, Event *unused_event)
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
void RegisterDialog::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
	log("editBox %p DidBegin !", editBox);
}

void RegisterDialog::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{
	log("editBox %p DidEnd !", editBox);
}

void RegisterDialog::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
	log("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void RegisterDialog::editBoxReturn(ui::EditBox* editBox)
{
	auto str = String::createWithFormat("%s", editBox->getText());
	editBox->setText(str->getCString());
	log("editBox %p was returned !", editBox);

}


void RegisterDialog::httpCallback(Ref*psend)
{
	RegisterValue *value = (RegisterValue*)psend;
	switch (value->_errorcode)
	{
	case 0:
	{	
		User::getInstance()->setSessionid(value->_sesssionid);
		User::getInstance()->setUserName(_editNickname->getText());
		User::getInstance()->setUserGender(sex);
		LoginMannger::getInstance()->addMemoryNickname(_editNickname->getText(), _editPassword->getText());
		auto scene = LoadingScene::createScene();
		Director::getInstance()->replaceScene(scene);
		NewbieMannger::getInstance()->setNBRewards(value->rewards);
		NewbieMannger::getInstance()->setisAllowdedGetFirstReward(true);
	}
		break;
	case 404:
	{
		auto menu = getChildByName("menu");
		auto bt = menu->getChildByName("surebt");
		((MenuItemImage*)bt)->setEnabled(true);
		auto dioag = TwiceSureDialog::createDialog(ChineseWord("LoginTimeOut").c_str());
		dioag->setPosition(0, 0);
		addChild(dioag, 30);
	}
	break;
	default:
	{
		auto menu = getChildByName("menu");
		auto bt = menu->getChildByName("loginBt");
		((MenuItemImage*)bt)->setEnabled(true);
		auto dioag = TwiceSureDialog::createDialog(value->_errormsg.c_str());
		dioag->setPosition(0, 0);
		addChild(dioag, 30);
	}
	break;
	}
	NotificationCenter::getInstance()->removeObserver(this, "CDKEY");

}