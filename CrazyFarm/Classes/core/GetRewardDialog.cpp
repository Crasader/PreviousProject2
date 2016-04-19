#include "GetRewardDialog.h"
#include "utill/AnimationUtil.h"
#include "domain/user/User.h"
#include "domain/logevent/LogEventBankrupt.h"
#include "data/GameData.h"
#include "lobby/shop/payLayer.h"
#include "server/Server.h"
#include "domain/pay/Pay.h"
#include "utill/Chinese.h"
#include "utill/Audio.h"
GetRewardDialog* GetRewardDialog::create(Bankrupt baknrupt)
{
	GetRewardDialog *pRet = new GetRewardDialog();
	if (pRet && pRet->init(baknrupt))
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

bool GetRewardDialog::init(Bankrupt baknrupt)
{
	Layer::init();
	bool bRet = false;
	do 
	{	
		auto colorlayer = LayerColor::create();
		colorlayer->setColor(ccc3(0, 0, 0));
		colorlayer->setOpacity(180);
		addChild(colorlayer, -1);

		auto bg = Sprite::create("BankruptBg.png");
		bg->setPosition(480, 270);
		addChild(bg,0,"bg");


		m_baknrupt = baknrupt;
		auto size = bg->getContentSize();
		auto title = Sprite::create("BankruptTitle.png");
		title->setPosition(size.width / 2, 297);
		bg->addChild(title);

		///救济金
		auto bankruptFrame = Sprite::create("BankruptFrame.png");
		bankruptFrame->setPosition(130, size.height / 2-30);
		bg->addChild(bankruptFrame, 0, "bankruptFrame");
		auto bankruptLabel = LabelTTF::create(ChineseWord("jiujijin").c_str(), "arial", 20);
		bankruptLabel->setColor(Color3B(12, 64, 109));
		bankruptLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
		bankruptLabel->setPosition(bankruptFrame->getContentSize().width / 2, 199);
		bankruptFrame->addChild(bankruptLabel);

		auto coin = Sprite::create("sign_1001.png");
		coin->setPosition(bankruptFrame->getContentSize().width/2,bankruptFrame->getContentSize().height/2+20);
		bankruptFrame->addChild(coin);

		auto bankruptNumstr = String::createWithFormat(":%d", m_baknrupt.coins);
		auto bankruptNum = LabelAtlas::create(bankruptNumstr->getCString(), "missionRewardNum.png", 14, 20, '0');
		bankruptNum->setAnchorPoint(Point(0.5, 0.5));
		bankruptNum->setPosition(coin->getPositionX(), coin->getPositionY()-30);
		bankruptFrame->addChild(bankruptNum);

		auto sp1 = Sprite::create("btn_ling_1.png");
		auto sp2 = Sprite::create("btn_ling_2.png");
	
			auto bt = MenuItemSprite::create(sp1, sp2, Sprite::create("btn_black.png"), CC_CALLBACK_1(GetRewardDialog::lingquCb, this));
		bt->setPosition(bankruptFrame->getContentSize().width / 2, 40);
		bt->setEnabled(false);
		auto menu = Menu::create(bt, nullptr);
		menu->setPosition(0, 0);
		bankruptFrame->addChild(menu, 0, "menu");
		bt->setName("lingqu");

		auto timetip = String::createWithFormat(ChineseWord("bankruptCoinGainTime").c_str(), m_baknrupt.wait_time);
		auto timelabel = Label::create(timetip->getCString(), "arial", 20);
		timelabel->setColor(Color3B::YELLOW);
		timelabel->setPosition(bt->getContentSize().width/2,bt->getContentSize().height/2+8);
		bt->addChild(timelabel, 1, "timelabel");
		
		///今日很能领取几次救济金
		auto txt = Sprite::create("TXTBankruptCount.png");
		txt->setPosition(bankruptFrame->getPositionX(), 255);
		bg->addChild(txt);
		auto countlabel = LabelAtlas::create(Value(baknrupt.time).asString(), "multipleNum.png", 15, 21, '0');
		countlabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
		countlabel->setPosition(1.25 + 152.75, txt->getContentSize().height / 2);
		txt->addChild(countlabel);

		if (m_baknrupt.time==0)
		{
			txt->setVisible(false);
		}

		//计费点
		auto paypointFrame = Sprite::create("changewardCellBg.png");
		paypointFrame->setPosition(363, size.height / 2-30);
		bg->addChild(paypointFrame);

		auto highfree = Sprite::create("highFree.png");
		highfree->setAnchorPoint(Point(0, 1));
		highfree->setPosition(20, paypointFrame->getContentSize().height);
		paypointFrame->addChild(highfree);

		auto BankruptProp = Sprite::create("BankruptProp.png");
		BankruptProp->setPosition(paypointFrame->getContentSize() / 2+Size(0,35));
		paypointFrame->addChild(BankruptProp);

		bt = MenuItemImage::create("btn_goumai_1.png", "btn_goumai_2.png", CC_CALLBACK_1(GetRewardDialog::payCb, this));
		bt->setAnchorPoint(Point::ANCHOR_MIDDLE);
		bt->setPosition(paypointFrame->getContentSize().width / 2, 70);
		menu = Menu::create(bt, nullptr);
		menu->setPosition(0, 0);
		paypointFrame->addChild(menu, 0);




		auto close = MenuItemImage::create("X_1.png", "X_2.png", [=](Ref* sender){
			Audio::getInstance()->playSound(CLICKSURE);
			removeFromParentAndCleanup(1);
		});
		close->setAnchorPoint(Point(1, 1));
		close->setPosition(size+Size(20,20));
		menu = Menu::create(close, nullptr);
		menu->setPosition(0, 0);
		bg->addChild(menu, 0);


		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(GetRewardDialog::onTouchBegan, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);
		scheduleUpdate();
		

		bRet = true;
	} while (0);
	return bRet;
}
void GetRewardDialog::lingquCb(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	Server::getInstance()->sendBankruptRebirth();
	removeFromParentAndCleanup(1);
}
void GetRewardDialog::update(float dt)
{
	m_baknrupt.wait_time -= dt;
	auto bg = getChildByName("bg");
	auto bankruptFrame =bg->getChildByName("bankruptFrame");
	auto menu = bankruptFrame->getChildByName("menu");
	auto bt = menu->getChildByName("lingqu");
	auto timelabel = (Label*)(bt->getChildByName("timelabel"));
	auto timetip = String::createWithFormat(ChineseWord("bankruptCoinGainTime").c_str(), m_baknrupt.wait_time);
	timelabel->setString(timetip->getCString());

	if (m_baknrupt.wait_time<=0)
	{
		((MenuItemSprite*)bt)->setEnabled(true);
		timelabel->setVisible(false);
		unscheduleUpdate();
	}
}

bool GetRewardDialog::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}
void GetRewardDialog::payCb(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	Pay::getInstance()->Overbooking(2, 25, this);
}