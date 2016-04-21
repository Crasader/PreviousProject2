#include "RedPackCell.h"
#include "utill/Audio.h"
#include "utill/Chinese.h"
#include "RedPackChangeCDkey.h"
#include "utill/JniFunUtill.h"
#include "server/HttpMannger.h"
RedPackCell* RedPackCell::create(int type)
{ 
	RedPackCell *pRet = new RedPackCell(); 
	if (pRet && pRet->init(type))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
bool RedPackCell::init(int type){
	initWithFile("redPackCellbg.png");


	_type = type; 
	auto size = getContentSize();

	auto str = String::createWithFormat("redPackIcon_%d.png", _type);
	auto icon = Sprite::create(str->getCString());
	icon->setPosition(size.width / 2, 143);
	addChild(icon);

	str = String::createWithFormat("redPackContent_%d.png", _type);
	auto content = Sprite::create(str->getCString());
	content->setPosition(size.width / 2, 272);
	addChild(content);


	auto bt = MenuItemImage::create("btn_1.png", "btn_2.png", CC_CALLBACK_1(RedPackCell::btCallback, this));
	bt->setAnchorPoint(Point(0.5, 0.5));
	bt->setPosition(size.width/2, 45);

	str = String::createWithFormat("btn_redPack_%d.png", _type);
	auto BtTxt = Sprite::create(str->getCString());
	BtTxt->setPosition(bt->getContentSize() / 2);
	bt->addChild(BtTxt);

	
	auto menu = Menu::create(bt, nullptr);
	menu->setPosition(0, 0);
	addChild(menu);


	auto txtframe = Sprite::create("redPackTipFrame.png");
	txtframe->setPosition(size.width / 2, -20);
	addChild(txtframe);

	str = String::createWithFormat("redpacktip_%d", _type);
	auto label = Label::create(ChineseWord(str->getCString()), "arial", 17);
	txtframe->addChild(label);
	label->setPosition(txtframe->getContentSize() / 2);
	label->setAnchorPoint(Point::ANCHOR_MIDDLE);
	return true;
}

void RedPackCell::btCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	switch (_type)
	{
	case 1:
	{
		auto dog = RedPackChangeCDkey::create();
		dog->setPosition(0, 0);
		getParent()->getParent()->addChild(dog, 30);
		break;
	}
	case 2:
	{
		auto listen = EventListenerCustom::create("get_wxshareinfo", [=](EventCustom*event)
		{
			WXShareInfoValue *value = (WXShareInfoValue*)(event->getUserData());
			
			Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("get_wxshareinfo");
		

		});
		Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listen, 1);
		HttpMannger::getInstance()->HttpToPostRequestGetWxSharedInfo();
	}
		JniFunUtill::getInstance()->WXShare();
		break;
	default:
		break;
	}
	
}