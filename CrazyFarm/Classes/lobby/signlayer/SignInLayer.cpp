#include"SignInLayer.h"
#include "utill/dayUtil.h"
#include "config/ConfigSign.h"
#include "utill/Toast.h"
SignCell::SignCell()
{

}


SignCell* SignCell::create(int day, int proptype, int propnum, int signtype)
{
	SignCell* bRet = new SignCell();
	if (bRet&&bRet->init(day,proptype,propnum,signtype))
	{
		bRet->autorelease(); 
			return bRet; 
	}
	else 
	{ 
	  delete bRet; 
	  bRet = NULL; 
	  return NULL; 
	} 
}

bool SignCell::init(int day, int proptype, int propnum, int signtype)
{
	
	bool bRet = false;
	while (!bRet)
	{
		char* type;
		if (signtype == 1)
		{
			type = "normal";
		}
		else if (signtype == 2)
		{
			type = "click";
		}
		//bg
		bg = Sprite::create(String::createWithFormat(("bg_%s.png"),type)->getCString());
		bg->setPosition(Point::ZERO);
		auto bgsize = bg->getContentSize();
		addChild(bg);

		//day
		auto daystr = String::createWithFormat("day_%d_%s.png", day, type);
		auto daysprite = Sprite::create(daystr->getCString());
		daysprite->setPosition(bgsize.width / 2, bgsize.height*0.8);
		bg->addChild(daysprite);

		//proptype 
		char* propstr;
		switch (proptype)
		{
		case 1:
			propstr = "tip";
			break;
		case 2:
			propstr = "plustime";
			break;
		case 3:
			propstr = "refresh";
			break;
		default:
			break;
		}
		auto propsprite = Sprite::create(String::createWithFormat(("prop_%s_%s.png"), propstr, type)->getCString());
		propsprite->setPosition(bgsize.width / 2, bgsize.height*0.45);
		bg->addChild(propsprite);
		//num
		auto nLabel = LabelAtlas::create((String::createWithFormat(":%d", propnum))->getCString(), (String::createWithFormat("sign/Num_%s.png", type))->getCString(),17,18,'0');
		nLabel->setPosition(bgsize.width *0.3, bgsize.height*0.10);
		bg->addChild(nLabel);
		bRet = true;

	}
	return bRet;
}

void SignCell::SetBlind()
{
	bg->setTexture("bg_blind.png");
}





bool SignInLayer::init()
{
	if (!Layer::init()){
		return false;
	}	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	nSeqSignDay = CalculateTheDayToSign();
	
	auto bg = Sprite::create("showFishAniFrame.png");
	bg->setPosition(visibleSize / 2);
	addChild(bg);

	auto button = MenuItemImage::create("btn_small_1.png", "btn_small_2.png", CC_CALLBACK_1(SignInLayer::gainRewardsCallback, this));
	button->setPosition(bg->getContentSize().width / 2, bg->getContentSize().height*0.2);
	auto menu = Menu::create(button, nullptr);
	menu->setPosition(0, 0);
	bg->addChild(menu);

	auto listenr1 = EventListenerTouchOneByOne::create();
	listenr1->onTouchBegan = CC_CALLBACK_2(SignInLayer::onTouchBegan, this);
	listenr1->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);


	if (nSeqSignDay == -1)
	{
		runAction(Sequence::create(CallFunc::create([&]{Toast::show("time out", 3, getParent()); }), DelayTime::create(3.1), RemoveSelf::create(1),nullptr));
	}
	else if (nSeqSignDay == 0)
	{
		runAction(Sequence::create(CallFunc::create([&]{Toast::show("already signed", 3, getParent()); }), DelayTime::create(3.1), RemoveSelf::create(1),nullptr));
	}
	return true;

}


int SignInLayer::CalculateTheDayToSign()
{
	if (!ConfigSign::getInstance()->isGetDataSuccess())
	{
		return -1;
	}
	auto str = UserDefault::getInstance()->getStringForKey(KEY_LASTSIGNDAY, "-1");
	auto sToday = ConfigSign::getInstance()->getToday();
	if (str == "-1")
	{
		return 1;
	}
	else if (str == sToday)
	{
		return 0;
	}
	SystemTime* lastDay = new SystemTime(str);
	SystemTime* toDay = new SystemTime(sToday);
	bool isContinue = SystemTime::isContinuousByAandB(lastDay, toDay);
	if (isContinue)
	{
		int dayCout = UserDefault::getInstance()->getIntegerForKey(KEY_SEQSIGNDAY,0);
		return (dayCout + 1) > 7 ? 1:dayCout + 1;
	}
	else
	{
		return 1;
	}


	
}
void SignInLayer::gainRewardsCallback(Ref* psend)
{
	if (nSeqSignDay<1||nSeqSignDay>7)
	{
		return;
	}
	auto reWards = ConfigSign::getInstance()->getRewardsByDay(nSeqSignDay);
	std::string str;
	String *perStr;
	for (auto var:reWards)
	{
		perStr = String::createWithFormat("reward id=%d,num=%d,probability=%d&&&&&&", var.propID, var.propNum, var.probability);
		str += perStr->getCString();
	}
	Toast::show(str.c_str(), 3, getParent());
	//Ç©µ½
	UserDefault::getInstance()->setIntegerForKey(KEY_SEQSIGNDAY, nSeqSignDay + 1);
	UserDefault::getInstance()->setStringForKey(KEY_LASTSIGNDAY,ConfigSign::getInstance()->getToday());




}