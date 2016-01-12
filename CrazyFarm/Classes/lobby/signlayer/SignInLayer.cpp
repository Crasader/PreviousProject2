#include"SignInLayer.h"
#include "utill/dayUtil.h"
#include "config/ConfigSign.h"
#include "utill/Toast.h"
#include "SignCell.h"
#include "SpliceCell.h"
bool SignInLayer::init(int seqday)
{
	if (!Layer::init()){
		return false;
	}	


	auto colorlayer = LayerColor::create();
	colorlayer->setColor(ccc3(0, 0, 0));
	colorlayer->setOpacity(180);
	addChild(colorlayer, -1);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	nSeqSignDay = seqday;
	auto bg = Sprite::create("signBg.png");
	bg->setPosition(visibleSize / 2);
	addChild(bg);


	auto frame = Sprite::create("signFrame.png");
	frame->setPosition(visibleSize.width / 2-8, visibleSize.height*0.58-5);
	addChild(frame);
	for (int i = 1; i <= 7;i++)
	{
		if (i>nSeqSignDay)
		{
			auto sp = Sprite::create("sign_lock.png");
			sp->setPosition(90.28 / 2 + (i - 1)*90.28,71);
			frame->addChild(sp);
		}
		else
		{
			auto reward = getRewardInVectorByProbability(ConfigSign::getInstance()->getRewardsByDay(nSeqSignDay));
			auto sp = SignCell::create(reward.propID,reward.propNum);
			sp->setPosition(90.28 / 2 + (i - 1)*90.28, 71);
			frame->addChild(sp);
		}
	}


	auto button = MenuItemImage::create("gainButton_1.png", "gainButton_2.png", CC_CALLBACK_1(SignInLayer::gainRewardsCallback, this));
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
SignInLayer * SignInLayer::createLayer(int seqday)
{
	SignInLayer *ret = new  SignInLayer();
	if (ret && ret->init(seqday))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}


void SignInLayer::gainRewardsCallback(Ref* psend)
{
	if (nSeqSignDay<1||nSeqSignDay>7)
	{
		return;
	}
	UserDefault::getInstance()->setIntegerForKey(KEY_SEQSIGNDAY, nSeqSignDay + 1);
	UserDefault::getInstance()->setStringForKey(KEY_LASTSIGNDAY,ConfigSign::getInstance()->getToday());

	this->removeFromParentAndCleanup(1);
}

void SignInLayer::updata(float dt)
{

}

SignRewardItem SignInLayer::getRewardInVectorByProbability(std::vector<SignRewardItem> vec)
{
	int k = rand() % 100 + 1;
	int totalNum = 0;
	for (auto var:vec)
	{
		if (k>var.probability)
		{
			return var;
		}
		else k += var.probability;
	}
	return vec.at(0);
}