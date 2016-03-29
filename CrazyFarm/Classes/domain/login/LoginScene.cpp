#include "LoginScene.h"
#include "LoginMannger.h"
#include "domain/loading/LoadingScene.h"
#include "domain/ToolTip/TwiceSureDialog.h"
Scene* LoginScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoginScene::create();
	scene->addChild(layer, 0, 888);
	return scene;
}

bool LoginScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto nickname = LoginMannger::getInstance()->getMemoryNickname().at(0);
	auto password = UserDefault::getInstance()->getStringForKey(nickname,"defaultWord").c_str();
	auto bg = Sprite::create("loginBg.png");
	bg->setPosition(480, 270);
	addChild(bg, -1);



	
	auto loginBt = MenuItemImage::create("loginGame_1.png", "loginGame_2.png", CC_CALLBACK_1(LoginScene::loginCallBack, this));
	loginBt->setPosition(480, 87);
	loginBt->setName("loginBt");
	



	//�����˺�	
	_editName = ui::EditBox::create(Size(335, 53), ui::Scale9Sprite::create("loginFram.png"));
	_editName->setPosition(Vec2(480, 232));
	_editName->setFontName("Arial");
	_editName->setFontSize(20);
	_editName->setFontColor(Color3B::YELLOW);
	auto str = String::createWithFormat("    %s", nickname.c_str());
	_editName->setText(str->getCString());
	_editName->setMaxLength(14);
	_editName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	_editName->setDelegate(this);
	addChild(_editName);
	auto Bt = MenuItemImage::create("ChangeIdBt.png", "ChangeIdBt.png", CC_CALLBACK_1(LoginScene::changeIdCallBack, this));
	Bt->setAnchorPoint(Point(1, 0.5));
	Bt->setPosition(_editName->getPositionX() + 167.5, _editName->getPositionY());
	auto BtTxt = Sprite::create();
	BtTxt->setPosition(Bt->getContentSize() / 2);
	Bt->addChild(BtTxt);

	//��������	
	_editPassword = ui::EditBox::create(Size(335, 53), ui::Scale9Sprite::create("loginFram.png"));
	_editPassword->setPosition(Vec2(480, 169));
	_editPassword->setFontName("Arial");
	_editPassword->setFontSize(20);
	_editPassword->setEnabled(false);
	_editPassword->setInputFlag(EditBox::InputFlag::PASSWORD);
	_editPassword->setFontColor(Color3B::YELLOW);
	auto str = String::createWithFormat("    %s", password.c_str());
	_editPassword->setText(str->getCString());
	_editPassword->setMaxLength(14);
	_editPassword->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	_editPassword->setDelegate(this);
	addChild(_editName);
	auto Bt1 = MenuItemImage::create("ChangeIdBt.png", "ChangeIdBt.png", CC_CALLBACK_1(LoginScene::findPasswordCallBack, this));
	Bt1->setAnchorPoint(Point(1, 0.5));
	Bt1->setPosition(_editPassword->getPositionX() + 167.5, _editPassword->getPositionY());
	auto BtTxt1 = Sprite::create();
	BtTxt1->setPosition(Bt1->getContentSize() / 2);
	Bt1->addChild(BtTxt1);

	auto menu = Menu::create(loginBt, Bt,nullptr);
	menu->setPosition(0, 0);
	addChild(menu, 1, "menu");
	return true;
}
void LoginScene::changeIdCallBack(Ref*psend)
{

}
void LoginScene::findPasswordCallBack(Ref*psend)
{

}
void LoginScene::loginCallBack(Ref*psend)
{
	char nickname[20];
	char passWord[20];
	auto txt = _editName->getText();
	int num = sscanf(txt, "    %s",
		&nickname);
	txt = _editPassword->getText();
	num = sscanf(txt, "    %s",
		&passWord);
	((MenuItemImage*)psend)->setEnabled(false);
	LoginMannger::getInstance()->toLogin(nickname,passWord);
	scheduleUpdate();
	nTempTime = 0;
	
}
void LoginScene::update(float delta)
{
	nTempTime += delta;
	if (LoginMannger::getInstance()->getisLoginSuccess())
	{
		Director::getInstance()->replaceScene(LoadingScene::createScene());
		unscheduleUpdate();
	}
	if (nTempTime>5)
	{
		auto menu = getChildByName("menu");
		auto bt = menu->getChildByName("loginBt");
		((MenuItemImage*)bt)->setEnabled(true);
		auto dioag = TwiceSureDialog::createDialog(ChineseWord("LoginTimeOut").c_str());
		dioag->setPosition(0, 0);
		addChild(dioag, 30);
		unscheduleUpdate();
	}
}


void LoginScene::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
	log("editBox %p DidBegin !", editBox);
}

void LoginScene::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{
	log("editBox %p DidEnd !", editBox);
}

void LoginScene::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
	log("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void LoginScene::editBoxReturn(ui::EditBox* editBox)
{
	auto str = String::createWithFormat("%s", _editName->getText());
	_editName->setText(str->getCString());
	log("editBox %p was returned !", editBox);

}