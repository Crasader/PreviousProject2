#include"SignInLayer.h"
#include "utill/dayUtil.h"
#include "config/ConfigSign.h"
#include "utill/Toast.h"
#include "SignCell.h"
#include "SpliceCell.h"
#include "domain/user/User.h"
#include "lobby/LobbyScene.h"
#include "domain/bag/BagManager.h"
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
			auto sp = SpliceCell::create(2);
			sp->setAnchorPoint(Point::ANCHOR_MIDDLE);
			sp->setPosition(90.28 / 2 + (i - 1)*90.28-83/2, 71-142/2+9);
			frame->addChild(sp);
			SpliceCells.pushBack(sp);
			/*auto locksp = Sprite::create("sign_lock.png");
			locksp->setPosition(sp->getPosition());
			frame->addChild(locksp, 1, "lock");*/
			/*auto reward = getRewardInVectorByProbability(ConfigSign::getInstance()->getRewards());
			auto sp = SignCell::create(reward.propID, reward.propNum);
			if (User::getInstance()->getVipLevel()>0)
			{
			reward.propNum *= 2;
			sp->setVipX2();
			}
			sp->setPosition(90.28 / 2 + (i - 1)*90.28, 71);
			frame->addChild(sp);
			rewards.push_back(reward);*/
		}
	}


	auto button = MenuItemImage::create("gainButton_1.png", "gainButton_2.png", CC_CALLBACK_1(SignInLayer::gainRewardsCallback, this));
	button->setPosition(bg->getContentSize().width / 2, bg->getContentSize().height*0.2+20);
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
	for (auto var : SpliceCells)
	{
		var->setBegin();
	}
	return;
	if (nSeqSignDay<1||nSeqSignDay>7)
	{
		return;
	}
	UserDefault::getInstance()->setIntegerForKey(KEY_SEQSIGNDAY, nSeqSignDay );
	UserDefault::getInstance()->setStringForKey(KEY_LASTSIGNDAY,ConfigSign::getInstance()->getToday());
	((LobbyScene*)getParent())->guizuCallback(nullptr);
	for (auto var:rewards)
	{
		if (var.propID==1001)
		{
			User::getInstance()->addCoins(var.propNum);
		}
		else if (var.propID ==1002)
		{
			User::getInstance()->addDiamonds(var.propNum);
		}
		else
		{
			BagManager::getInstance()->changeItemCount(var.propID, var.propNum);
		}
	}
	for (int i = 0; i < SpliceCells.size();i++)
	{
		//TODO:
	}
	//this->removeFromParentAndCleanup(1);
}

void SignInLayer::updata(float dt)
{

}

SignRewardItem SignInLayer::getRewardInVectorByProbability(std::vector<SignRewardItem> vec)
{
	std::vector<SignRewardItem> vec2;
	vec2.resize(vec.size());
	for (int i = 0; i < vec.size(); i++)
	{
		vec2.at(i).propID = vec[i].propID;
		vec2.at(i).propNum = vec[i].propNum;
		int lastPer = (i == 0 ? 0 : vec2[i - 1].probability);
		vec2.at(i).probability = lastPer + vec[i].probability;
	}
	int randNum = rand() % 100 + 1;
	for (auto ite = vec2.begin(); ite != vec2.end(); ite++)
	{
		if (randNum <= ite->probability)
		{
			return *ite;
		}
	}
	return vec.at(0);
}