#include"SignInLayer.h"
#include "utill/dayUtil.h"
#include "config/ConfigSign.h"
#include "utill/Toast.h"
#include "SignCell.h"
#include "SpliceCell.h"
#include "domain/user/User.h"
#include "lobby/LobbyScene.h"
#include "domain/bag/BagManager.h"
#include "utill/Audio.h"
bool SignInLayer::init(int seqday)
{
	if (!Layer::init()){
		return false;
	}	


	auto colorlayer = LayerColor::create();
	colorlayer->setColor(ccc3(0, 0, 0));
	colorlayer->setOpacity(180);
	addChild(colorlayer, -1,"color");
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	nSeqSignDay = seqday;
	auto bg = Sprite::create("signBg.png");
	bg->setPosition(visibleSize / 2);
	addChild(bg,0,"bg");


	auto frame = Sprite::create("signFrame.png");
	frame->setPosition(visibleSize.width / 2-8, visibleSize.height*0.58+9);
	addChild(frame,0,"signframe");
	for (int i = 1; i <= 7;i++)
	{
		if (i>nSeqSignDay)
		{
			auto sp = Sprite::create("sign_lock.png");
			sp->setPosition(90.28 / 2 + (i - 1)*90.28,71);
			frame->addChild(sp,-1);
		}
		else
		{	
			int curindex = -1;
			auto reward = getRewardInVectorByProbability(ConfigSign::getInstance()->getRewards(), curindex);
			if (User::getInstance()->getVipLevel() > 0)
			{
				reward.propNum *= 2;
			}
			rewards.push_back(reward);

			auto sp = SpliceCell::create(curindex,4.0f+(i-1)*0.5f);
			sp->setAnchorPoint(Point::ANCHOR_MIDDLE);
			sp->setPosition(90.28 / 2 + (i - 1)*90.28-83/2, 71-142/2+13);
			frame->addChild(sp,-1);
			SpliceCells.pushBack(sp);
			CCLOG("day = %d,curindex = %d", i, curindex);
			curindexs.push_back(curindex);
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




	//auto anisp = Sprite::create("signAni_1.png");
	//anisp->setAnchorPoint(Point::ZERO);
	//anisp->setPosition(-23,-19);
	//bg->addChild(anisp);
	//anisp->runAction(RepeatForever::create(Blink::create(0.8f, 1)));

	//anisp = Sprite::create("signAni_2.png");
	//anisp->setAnchorPoint(Point::ZERO);
	//anisp->setPosition(-23,-19);
	//bg->addChild(anisp);
	//anisp->runAction(Sequence::create(DelayTime::create(0.4f), CallFunc::create([=]{anisp->runAction(RepeatForever::create(Blink::create(0.8f, 1))); }),nullptr));


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

	((MenuItemImage*)psend)->setEnabled(false);
	if (nSeqSignDay<1||nSeqSignDay>7)
	{
		return;
	}
	Audio::getInstance()->playSound(FRUITSIGN);
	CCLOG("begin");
	for (auto var : SpliceCells)
	{
		var->setBegin();
	}
	runAction(Sequence::create(DelayTime::create(nSeqSignDay*0.5 + 4.0f + 1.0f), CallFunc::create([=]{
		UserDefault::getInstance()->setIntegerForKey(KEY_SEQSIGNDAY, nSeqSignDay);
	UserDefault::getInstance()->setStringForKey(KEY_LASTSIGNDAY, ConfigSign::getInstance()->getToday());
	getChildByName("signframe")->setVisible(false);
	getChildByName("bg")->setVisible(false);
	getChildByName("color")->setVisible(false);
	for (int i = 0; i < curindexs.size();i++)
	{
		auto sp = Sprite::create("signRewards.png", Rect(0, 406-83 * curindexs.at(i), 83, 83));
		sp->setPosition(213 + i*90.28, 330);
		sp->runAction(Sequence::create(Spawn::create(MoveTo::create(1.0f, Vec2(259.2, 48)), ScaleTo::create(1.0f, 0.1f), nullptr), RemoveSelf::create(), nullptr));
		getParent()->addChild(sp, 30);
	}
	runAction(Sequence::create(DelayTime::create(1.2f), CallFunc::create([=]{
		for (auto var : rewards)
	{
		if (var.propID == 1001)
		{
			User::getInstance()->addCoins(var.propNum);
		}
		else if (var.propID == 1002)
		{
			User::getInstance()->addDiamonds(var.propNum);
		}
		else
		{
			BagManager::getInstance()->changeItemCount(var.propID, var.propNum);
		}
	}

	((LobbyScene*)(this->getParent()))->guizuCallback(nullptr);
	for (auto var : rewards)
	{
		if (var.propID == 1001)
		{
			User::getInstance()->addCoins(var.propNum);
		}
		else if (var.propID == 1002)
		{
			User::getInstance()->addDiamonds(var.propNum);
		}
		else
		{
			BagManager::getInstance()->changeItemCount(var.propID, var.propNum);
		}
	}	this->removeFromParentAndCleanup(1);}), nullptr));
	

 }), nullptr));
	
}

void SignInLayer::updata(float dt)
{

}

SignRewardItem SignInLayer::getRewardInVectorByProbability(std::vector<SignRewardItem> vec,int &curindex)
{
	int randNum = rand() % 100 + 1;
	int per = 0;
	for (int i = 0; i < vec.size();i++)
	{
		per += vec.at(i).probability;
		if (randNum<per)
		{
			curindex = i;
			return vec.at(i);
		}
	}
	curindex = 0;
	return vec.at(0);
}