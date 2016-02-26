#include "showTurretCell.h"
#include "utill/Chinese.h"
#include "config/ConfigTurrent.h"
#include "domain/user/User.h"
#include "lobby/shop/payLayer.h"
#include "domain/logevent/LogEventPageChange.h"
#include "lobby/viplayer/VipLayer.h"
#include "domain/game/GameManage.h"
#include "domain/logevent/LogEventTurrentUpgrade.h"
#include "domain/bag/BagManager.h"
bool showTurretCell::init(){

	setAnchorPoint(Point::ANCHOR_MIDDLE);


	bg = Sprite::create();
	bg->setPosition(88, 121.5);
	bg->setContentSize(Size(176, 243));
	addChild(bg);
	auto size = bg->getContentSize();

	propSprite = Sprite::create();
	propSprite->setPosition(size.width / 2, size.height / 2 - 20);
	addChild(propSprite);

	auto bottom = Sprite::create("VIPbottomFrame.png");
	bottom->setPosition(0, 0);
	bottom->setAnchorPoint(Point::ZERO);
	addChild(bottom);

	

	ShowPaoshade = Sprite::create("ShowPaoshade.png");
	ShowPaoshade->setPosition(size/2);
	addChild(ShowPaoshade);
	ShowPaoshade->setVisible(false);

	
	
	muptleTTF = LabelAtlas::create("0", "unLockNumTTF.png", 13, 19, '0');
	muptleTTF->setAnchorPoint(Point::ANCHOR_MIDDLE);
	muptleTTF->setPosition(size.width*0.52, size.height*0.9+3);
	addChild(muptleTTF);
	muptleTTF->setVisible(false);



	button = MenuItemImage::create();
	button->setContentSize(Size(161, 74));
	button->setPosition(size.width / 2, size.height*0.18-5);
	button->setCallback(CC_CALLBACK_1(showTurretCell::ButtonCallback,this));
	auto diamondNumTTF = LabelAtlas::create("0", "unLockNumTTF.png", 13, 19, '0');
	diamondNumTTF->setPosition(Point::ANCHOR_MIDDLE);
	diamondNumTTF->setPosition(button->getContentSize()/2);
	diamondNumTTF->setVisible(false);
	button->addChild(diamondNumTTF,1,10);

	auto menu = Menu::create(button, nullptr);
	menu->setPosition(0, 0);
	addChild(menu);


	showVipPaoName = Sprite::create();
	showVipPaoName->setPosition(size.width / 2, size.height*0.95-30);
	addChild(showVipPaoName);
	showVipPaoName->setVisible(false);


	ShowPaolight = Sprite::create("ShowPaolight.png");
	ShowPaolight->setPosition(size / 2);
	addChild(ShowPaolight);
	ShowPaolight->setVisible(false);


	lock = Sprite::create("smalllock.png");
	lock->setPosition(Vec2(77,86));
	propSprite->addChild(lock);
	lock->setVisible(false);

	lockTTf = Sprite::create("locksuccessTTf.png");
	lockTTf->setPosition(button->getPosition());
	addChild(lockTTf);
	lockTTf->setVisible(false);

	SendCoin = Sprite::create("sendCoin.png");
	SendCoin->setPosition(size.width / 2, 99);
	addChild(SendCoin);
	SendCoin->setVisible(false);

	zengCoinTTf = LabelAtlas::create("0", "unLockNumTTF.png", 13, 19, '0');
	zengCoinTTf->setAnchorPoint(Point::ANCHOR_MIDDLE);
	zengCoinTTf->setPosition(size.width/2,99);
	zengCoinTTf->setVisible(false);
	addChild(zengCoinTTf);
	quex3 = Sprite::create("quex3.png");
	quex3->setPosition(zengCoinTTf->getPosition());
	addChild(quex3);
	quex3->setVisible(false);
	return true;
}



void showTurretCell::setMultipleValue(int index)
{
	auto size = bg->getContentSize();
	propSprite->setPosition(size.width / 2, size.height / 2 +20);

	m_type = 2;
	button->setScale(0.9);
	setScale(0.9);
	
	bg->setTexture("ShowPaobg.png");
	auto maxlevl = User::getInstance()->getMaxTurrentLevel();
	auto turret = ConfigTurrent::getInstance()->getTurrentByIndex(index);
	auto nowIndex = ConfigTurrent::getInstance()->getIndexByMaxlv(maxlevl);
	muptleTTF->setString(Value(turret.multiple).asString().c_str());
	muptleTTF->setVisible(true);
	button->setNormalSpriteFrame(SpriteFrame::create("btn_big_1.png",Rect(0,0,161,74)));
	button->setSelectedSpriteFrame(SpriteFrame::create("btn_big_2.png", Rect(0, 0, 161, 74)));
	auto diamondNumTTF = (LabelAtlas*)button->getChildByTag(10);
	diamondNumTTF->setVisible(true);
	diamondNumTTF->setString(Value(turret.unlockPrice).asString().c_str());
	ShowPaolight->setVisible(false);


	ShowPaolight->setVisible(false);
	if (nowIndex>=index) //已解锁
	{
		lock->setVisible(false);
		button->setVisible(false);
		lockTTf->setVisible(true);
		ShowPaoshade->setVisible(false);
		

		zengCoinTTf->setVisible(false);
		SendCoin->setVisible(false);
		quex3->setVisible(false);
	}
	else if ((nowIndex+1) == index)//下一级
	{
		lock->setVisible(true);
		button->setVisible(true);
		lockTTf->setVisible(false);
		ShowPaoshade->setVisible(false);
		ShowPaolight->setVisible(true);

		SendCoin->setVisible(true);
		zengCoinTTf->setVisible(true);
		zengCoinTTf->setString(Value(turret.rewardList.at(0).num).asString());
		quex3->setVisible(false);
	}
	else//未解锁
	{
		lock->setVisible(true);
		button->setVisible(true);
		lockTTf->setVisible(false);
		ShowPaoshade->setVisible(true);
		ShowPaolight->setVisible(false);

		SendCoin->setVisible(true);
	
		zengCoinTTf->setVisible(false);
		quex3->setVisible(true);
		if (nowIndex<(index-3))
		{
			
		}
		
	}

	/*if (nextTurret.turrentId < turret.turrentId)
	{
		lock->setVisible(false);
		button->setVisible(true);
		lockTTf->setVisible(false);
		ShowPaoshade->setVisible(true);

		zengCoinTTf->setVisible(false);
		SendCoin->setVisible(false);
		quex3->setVisible(false);
	}	
	else if (nextTurret.turrentId == turret.turrentId)
	{
		lock->setVisible(true);
		button->setVisible(true);
		lockTTf->setVisible(false);
		ShowPaoshade->setVisible(false);
		ShowPaolight->setVisible(true);

		SendCoin->setVisible(true);
		zengCoinTTf->setVisible(true);
		zengCoinTTf->setString(Value(turret.rewardList.at(0).num).asString());
		quex3->setVisible(false);
	}
	else
	{
		lock->setVisible(true);
		button->setVisible(false);
		lockTTf->setVisible(true);
		ShowPaoshade->setVisible(false);


		if (nextTurret.turrentId > (turret.turrentId+5))
		{
		}
		SendCoin->setVisible(true);
		zengCoinTTf->setString(Value(turret.rewardList.at(0).num).asString());
	}

*/
	if (turret.multiple>30)
	{
		propSprite->setTexture("pao_2.png");
	}
	else
	{
		propSprite->setTexture("pao_1.png");
	}
}
void showTurretCell::setVippaoValue(int index)
{
	m_type = 1;
	auto viplv = User::getInstance()->getVipLevel();
	bg->setTexture("VIPFrame.png");
	
	showVipPaoName->setVisible(true);
	auto path = String::createWithFormat("VIPname_%d.png", index);
	showVipPaoName->setTexture(path->getCString());

	button->setNormalSpriteFrame(SpriteFrame::create("btn_huoqu_1.png", Rect(0, 0, 161, 74)));
	button->setSelectedSpriteFrame(SpriteFrame::create("btn_huoqu_2.png", Rect(0, 0, 161, 74)));
	path = String::createWithFormat("pao_%d.png", index+2);
	propSprite->setTexture(path->getCString());
	setAnchorPoint(Point::ANCHOR_MIDDLE);	
	button->setScale(0.9);
	setScale(0.9);
	if (index == (viplv+1))
	{
		ShowPaolight->setVisible(true);
	}
	else
	{
		ShowPaolight->setVisible(false);
	
	}

	if (index>viplv)
	{
		button->setVisible(true);
		lockTTf->setVisible(false);
		lock->setVisible(true);
	}
	else
	{
		button->setVisible(false);
		lockTTf->setVisible(true);
		lock->setVisible(false); 
	}
}


void showTurretCell::IsBeToued()
{

}




void showTurretCell::ButtonCallback(Ref* psend)
{

	if (m_type == 1)
	{
		///VIP充值	
		auto layer = VIPLayer::create();
		layer->setPosition(0, 0);
		GameManage::getInstance()->getGuiLayer()->addChild(layer, 20);
		GameManage::getInstance()->getGuiLayer()->getChildByTag(50)->removeFromParentAndCleanup(1);
		LogEventPageChange::getInstance()->addEventItems(2, 7, 0);
	}
	else
	{
		auto maxlevel = User::getInstance()->getMaxTurrentLevel();
		auto turretData = ConfigTurrent::getInstance()->getNextTurrent(maxlevel);
		auto zengList = turretData.rewardList;
		auto diamondNum = User::getInstance()->getDiamonds();
		bool isFinish = diamondNum >= turretData.unlockPrice ? true : false;
		if (isFinish)
		{
			auto a = User::getInstance()->getMaxTurrentLevel();
			auto m_turretdata = ConfigTurrent::getInstance()->getNextTurrent(a);
			User::getInstance()->setMaxTurrentLevel(m_turretdata.multiple);
			LogEventTurrentUpgrade::getInstance()->sendDataToServer(m_turretdata.multiple, GlobalSchedule::getInstance()->getGameTime());
			User::getInstance()->addDiamonds(-m_turretdata.unlockPrice);
			auto vec = m_turretdata.rewardList;
			for (auto var : vec)
			{
				if (var.itemId == 1001)
				{
					User::getInstance()->addCoins(var.num);
				}
				else if (var.itemId == 1002)
				{
					User::getInstance()->addDiamonds(var.num);
				}
				else
				{
					BagManager::getInstance()->changeItemCount(var.itemId, var.num);
				}

			}
			GameData::getInstance()->setnowLevel(m_turretdata.multiple);
			//解锁成功字样提示
			auto layer = Director::getInstance()->getRunningScene()->getChildByTag(777);
			auto pos = GameManage::getInstance()->getGameLayer()->GetMyTurret()->getPosition();
			auto txt1 = Sprite::create("lockTurretTXT2.png");
			txt1->setPosition(pos.x + 5, pos.y + 150);
			GameManage::getInstance()->getGuiLayer()->addChild(txt1);
			auto ttf = LabelAtlas::create(Value(m_turretdata.multiple).asString().c_str(), "unLockNumTTF.png", 13, 19, '0');
			ttf->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
			ttf->setPosition(0, txt1->getContentSize().height / 2);
			txt1->addChild(ttf);
			auto txt2 = Sprite::create("lockTurretTXT1.png");
			txt2->setAnchorPoint(Point(1, 0.5));
			txt2->setPosition(0, ttf->getContentSize().height / 2);
			ttf->addChild(txt2);
			auto ttf1 = LabelAtlas::create(Value(m_turretdata.rewardList.at(0).num).asString().c_str(), "multipleNum.png", 15, 21, '0');
			ttf1->setPosition(txt1->getContentSize().width, txt1->getContentSize().height / 2);
			ttf1->setAnchorPoint(Point(0, 0.5));
			txt1->addChild(ttf1);
			txt1->runAction(Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(1), nullptr));
			//金币掉落
			for (int i = 0; i < 15; i++)
			{
				auto aniCoin = Sprite::create();
				aniCoin->setPosition(pos.x + 40 * (rand_0_1() - 0.5), pos.y + 70);
				aniCoin->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniGold")));
				aniCoin->runAction(Sequence::create(DelayTime::create(0.05f*i), MoveBy::create(0.23f, Vec2(0, 86)), MoveBy::create(0.13f, Vec2(0, -86)), MoveBy::create(0.1f, Vec2(0, 27.5)), MoveBy::create(0.1f, Vec2(0, -27.5)), DelayTime::create(0.6f), MoveTo::create(0.16f, pos), RemoveSelf::create(1), nullptr));
				GameManage::getInstance()->getGuiLayer()->addChild(aniCoin, 5);
			}
			//金币数字
			auto str = String::createWithFormat(":%d", m_turretdata.rewardList.at(0).num);
			auto label = LabelAtlas::create(str->getCString(), "TTFaniGold.png", 23, 34, '0');
			label->setAnchorPoint(Point::ANCHOR_MIDDLE);
			label->setPosition(GameManage::getInstance()->getGameLayer()->GetMyTurret()->getCoinLabelPos() + Vec2(0, 60));
			label->setScale(0);
			label->runAction(ScaleTo::create(0.1, 1));
			label->runAction(Sequence::create(DelayTime::create(3.0f), RemoveSelf::create(), nullptr));
			GameManage::getInstance()->getGuiLayer()->addChild(label, 5);
			GameManage::getInstance()->getGameLayer()->RefreShmyPlayerTurret();
			Director::getInstance()->getRunningScene()->getChildByTag(888)->getChildByTag(50)->removeFromParentAndCleanup(1);
		}
		else
		{
			auto layer = payLayer::createLayer(2);
			layer->setPosition(0, 0);
			layer->setEventPont(12);
			Director::getInstance()->getRunningScene()->getChildByTag(888)->addChild(layer, 20);
			Director::getInstance()->getRunningScene()->getChildByTag(888)->getChildByTag(50)->removeFromParentAndCleanup(1);
			LogEventPageChange::getInstance()->addEventItems(2, 13, 5);
		}
	}

}