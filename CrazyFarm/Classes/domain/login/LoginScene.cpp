#include "LoginScene.h"
#include "LoginMannger.h"
#include "domain/loading/LoadingScene.h"
#include "domain/ToolTip/TwiceSureDialog.h"
#include "domain/login/RegisterDialog.h"
#include "domain/login/DropDownListBox.h"
#include "server/HttpMsgDefine.h"
#include "domain/user/User.h"
#include "widget/LoadingCircle.h"
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

	nicknames = LoginMannger::getInstance()->getMemoryNickname();
	std::string nickname;
	if (nicknames.size()>0)
	{
		 nickname = nicknames.back();
	}
	else
	{
		nickname = "";
	}


	auto password = UserDefault::getInstance()->getStringForKey(nickname.c_str(),"defaultWord");
	auto bg = Sprite::create("loginBg.png");
	bg->setPosition(480, 270);
	addChild(bg, -1);



	
	auto loginBt = MenuItemImage::create("loginGame_1.png", "loginGame_2.png", CC_CALLBACK_1(LoginScene::loginCallBack, this));
	loginBt->setPosition(480, 87);
	loginBt->setName("loginBt");
	

	auto frame = Sprite::create("loginFram.png");
	frame->setPosition(480, 232);
	addChild(frame);
	//输入账号	
	_editName = ui::EditBox::create(Size(240, 53), ui::Scale9Sprite::create());
	_editName->setPosition(Vec2(480, 232));
	_editName->setFontName("Arial");
	_editName->setFontSize(20);
	_editName->setFontColor(Color3B::YELLOW);
	_editName->setText(nickname.c_str());
	_editName->setMaxLength(14);
	_editName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	_editName->setDelegate(this);
	addChild(_editName);
	auto Bt = MenuItemImage::create("ChangeIdBt.png", "ChangeIdBt_2.png", CC_CALLBACK_1(LoginScene::RegisterCallBack, this));
	Bt->setAnchorPoint(Point(1, 0.5));
	Bt->setPosition(_editName->getPositionX() + 167.5, _editName->getPositionY());
	auto BtTxt = Sprite::create("TxtRegister.png");
	BtTxt->setPosition(Bt->getContentSize() / 2);
	Bt->addChild(BtTxt);

	Vec2 changeIDpos =Vec2( frame->getPositionX() - frame->getContentSize().width / 2 + 20, frame->getPositionY() - 3);
	//输入密码	
	frame = Sprite::create("loginFram.png");
	frame->setPosition(480, 169);
	addChild(frame);
	_editPassword = ui::EditBox::create(Size(240, 53), ui::Scale9Sprite::create());
	_editPassword->setPosition(Vec2(480, 169));
	_editPassword->setFontName("Arial");
	_editPassword->setFontSize(20);
	_editPassword->setInputFlag(EditBox::InputFlag::PASSWORD);
	_editPassword->setFontColor(Color3B::YELLOW);
	_editPassword->setText(password.c_str());
	_editPassword->setMaxLength(14);
	_editPassword->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
	_editPassword->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	_editPassword->setDelegate(this);
	addChild(_editPassword);
	_editPassword->setEnabled(false);
	auto Bt1 = MenuItemImage::create("ChangeIdBt.png", "ChangeIdBt_2.png", CC_CALLBACK_1(LoginScene::findPasswordCallBack, this));
	Bt1->setAnchorPoint(Point(1, 0.5));
	Bt1->setPosition(_editPassword->getPositionX() + 167.5, _editPassword->getPositionY());
	auto BtTxt1 = Sprite::create("TxtFindWord.png");
	BtTxt1->setPosition(Bt1->getContentSize() / 2);
	Bt1->addChild(BtTxt1);

	auto lockSp = Sprite::create("lockPassWord.png");
	lockSp->setAnchorPoint(Point(0, 0.5));
	lockSp->setPosition(frame->getPositionX() - frame->getContentSize().width / 2+20, frame->getPositionY());
	addChild(lockSp);

	auto menu = Menu::create(loginBt,nullptr);
	menu->setPosition(0, 0);
	addChild(menu, 2, "menu");



	auto btMenu = Menu::create(Bt,Bt1, nullptr);
	btMenu->setPosition(0, 0);
	addChild(btMenu,2);

	auto sp = Sprite::create("dropdown.png");


	CCSize size = CCSizeMake(80, 30);
	//创建下拉列表框对象
	DropDownList* listBox = DropDownList::create(sp, size);
	listBox->setLoginscene(this);
	for (auto it = nicknames.rbegin(); it != nicknames.rend(); it++)
	{
		listBox->addLabel(it->c_str());
	}
	listBox->setAnchorPoint(Point(0,0.5));
	listBox->setPosition(changeIDpos-Vec2(30,15));
	addChild(listBox, 2);


	return true;
}
void LoginScene::moreIdCallback(Ref*psend)
{

}
void LoginScene::RegisterCallBack(Ref*psend)
{
	auto dialog = RegisterDialog::create();
	dialog->setPosition(0, 0);
	addChild(dialog, 20);
}
void LoginScene::findPasswordCallBack(Ref*psend)
{
	
}
void LoginScene::loginCallBack(Ref*psend)
{
	log("touch login");
	if (_editName->getText()=="")
	{
		return;
	}
	NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(LoginScene::httpCallback), "login", NULL);
	((MenuItemImage*)psend)->setEnabled(false);
	LoadingCircle::showLoadingCircle();
	LoginMannger::getInstance()->toLogin(_editName->getText(), _editPassword->getText());	
}
void LoginScene::httpCallback(Ref*psend)
{
	LoadingCircle::RemoveLoadingCircle();
	LoginValue *value = (LoginValue*)psend;
	switch (value->_errorcode)
	{
	case 0:
	{
		User::getInstance()->setSessionid(value->_sesssionid);
	
		User::getInstance()->setUserName(_editName->getText());
	
		LoginMannger::getInstance()->addMemoryNickname(_editName->getText(), _editPassword->getText());

	
		auto scene = LoadingScene::createScene();	
		Director::getInstance()->replaceScene(scene);
	}
		break;
	case 404:
	{
		auto menu = getChildByName("menu");
		auto bt = menu->getChildByName("loginBt");
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



void LoginScene::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
	editBox->setText("");
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
	editBox->setFontColor(Color3B::YELLOW);
	if (editBox==_editName)
	{
		/*auto str = String::createWithFormat("%s", _editName->getText());*/
		_editPassword->setEnabled(true);
		_editPassword->setText("");
	}
	
	log("editBox %p was returned !", editBox);

}
void LoginScene::setChangeNickName(std::string srt)
{

	_editName->setText(srt.c_str());
	_editName->setFontColor(Color3B::YELLOW);
	_editPassword->setText(UserDefault::getInstance()->getStringForKey(srt.c_str()).c_str());
	_editPassword->setEnabled(false);

}