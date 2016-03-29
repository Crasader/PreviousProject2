#include "RegisterDialog.h"
#include "LoginMannger.h"
#include "utill/Chinese.h"

bool RegisterDialog::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto bg = Sprite::create("RegisterBg.png");
	bg->setPosition(480, 270);
	addChild(bg, -1);


	sexBoy = SexHead::create(0, 1);
	sexBoy->setPosition(116, 350);
	bg->addChild(sexBoy);

	sexGirl = SexHead::create(1, 0);
	sexGirl->setPosition(237, 350);
	bg->addChild(sexGirl);



	auto size = bg->getContentSize();

	///ÇëÊäÈëÕËºÅ
	auto txt1 = Sprite::create("TxtInputName.png");
	txt1->setPosition(size.width / 2, 300);
	bg->addChild(txt1);

	_editNickname = ui::EditBox::create(Size(291, 51), ui::Scale9Sprite::create("RegisterInputFrame.png"));
	_editNickname->setPosition(Vec2(size.width/2, 273));
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
	txt1->setPosition(size.width / 2, 384);
	bg->addChild(txt1);

	_editNickname = ui::EditBox::create(Size(291, 51), ui::Scale9Sprite::create("RegisterInputFrame.png"));
	_editNickname->setPosition(Vec2(size.width / 2, 348));
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
	///ÇëÔÙ´ÎÊäÈëÃÜÂë
	txt1 = Sprite::create("TxtInputName.png");
	txt1->setPosition(size.width / 2, 384);
	bg->addChild(txt1);

	_editNickname = ui::EditBox::create(Size(291, 51), ui::Scale9Sprite::create("RegisterInputFrame.png"));
	_editNickname->setPosition(Vec2(size.width / 2, 348));
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


	auto loginBt = MenuItemImage::create("loginGame_1.png", "loginGame_2.png", CC_CALLBACK_1(LoginScene::loginCallBack, this));
	loginBt->setPosition(480, 87);
	loginBt->setName("loginBt");
	

	auto txt = Sprite::create();
	txt->setPosition(480, 236);
	txt->runAction(RepeatForever::create(Sequence::create(FadeOut::create(0.5f), FadeIn::create(0.5f), DelayTime::create(0.5f), nullptr)));
	addChild(txt);

	
	


	auto Bt = MenuItemImage::create("ChangeIdBt.png", "ChangeIdBt.png", CC_CALLBACK_1(LoginScene::btCallBack, this));
	Bt->setAnchorPoint(Point(1, 0.5));
	Bt->setPosition(_editName->getPositionX() + 167.5, _editName->getPositionY());
	auto BtTxt = Sprite::create();
	BtTxt->setPosition(Bt->getContentSize() / 2);
	BtTxt->setTag(10);
	Bt->addChild(BtTxt);

	if (LoginMannger::getInstance()->checkNicknameIsdefault(nickname.c_str()))
	{
		BtTxt->setTexture("TxtRegister.png");
		BtTxt->setName("register");
		txt->setTexture("TxtGuest.png");
	}
	else
	{
		BtTxt->setTexture("TxtchangeID.png");
		BtTxt->setName("changeID");
		txt->setTexture("TxtNickname.png");
	}

	auto menu = Menu::create(loginBt, Bt,nullptr);
	menu->setPosition(0, 0);
	addChild(menu, 1, "menu");
	return true;
}
void RegisterDialog::btCallBack(Ref*psend)
{
	auto txt = ((MenuItemImage*)psend)->getChildByTag(10);
	auto name = txt->getName();
	if (name == "register")
	{

	}
	else if (name == "changeID")
	{

	}
}
void RegisterDialog::loginCallBack(Ref*psend)
{
	
	
}
void RegisterDialog::update(float delta)
{
	
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
	auto str = String::createWithFormat("%s", _editName->getText());
	_editName->setText(str->getCString());
	log("editBox %p was returned !", editBox);

}