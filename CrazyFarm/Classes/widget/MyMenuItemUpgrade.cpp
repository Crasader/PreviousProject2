#include "MyMenuItemUpgrade.h"
#include "domain/user/User.h"
#include "config/ConfigTurrent.h"
#include "domain/bag/BagManager.h"
#include "data/GameData.h"
#include "core/showTurretLayer.h"
#include "domain/logevent/LogEventTurrentUpgrade.h"
#include "domain/globalschedule/GlobalSchedule.h"
#include "domain/game/GameManage.h"
enum 
{
	kTagMutpleLabel = 10,
	kTagExeDec = 11,
	kTagExeBar = 12,
	kTagCoinLabel=13

};

MyMenuItemUpgrade * MyMenuItemUpgrade::create()
{
	MyMenuItemUpgrade *ret = new (std::nothrow) MyMenuItemUpgrade();
	if (ret && ret->initWithNormalImage("UnlockFrame_1.png", "UnlockFrame_1.png", "", CC_CALLBACK_1(MyMenuItemUpgrade::ItemCallBack, ret)))
	{
		ret->initItem();
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}
void MyMenuItemUpgrade::ItemCallBack(Ref* psend)
{
	if (isElongate)
	{
		commonNode->setVisible(false);
		unfinishedNode->setVisible(false);
		nodeZeng->setVisible(false);
		runAction(MoveBy::create(0.5f, Vec2(166, 0)));
		isElongate = false;
	
		if (isFinish)
		{
			auto pNode = getChildByName("blinkAni");
			if (pNode)
			{
				pNode->removeFromParentAndCleanup(1);
			}

			auto a = User::getInstance()->getMaxTurrentLevel();
			auto m_turretdata = ConfigTurrent::getInstance()->getNextTurrent(a);
			User::getInstance()->setMaxTurrentLevel(m_turretdata.multiple);
			LogEventTurrentUpgrade::getInstance()->sendDataToServer(m_turretdata.multiple, GlobalSchedule::getInstance()->getGameTime());
			User::getInstance()->addDiamonds(-m_turretdata.unlockPrice);
			auto vec = m_turretdata.rewardList;
			for (auto var:vec)
			{
				if (var.itemId==1001)
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
			txt1->setPosition(pos.x+5, pos.y + 150);
			GameManage::getInstance()->getGuiLayer()->addChild(txt1);
			auto ttf = LabelAtlas::create(Value(m_turretdata.multiple).asString().c_str(),"unLockNumTTF.png", 13, 19,'0');
			ttf->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
			ttf->setPosition(0, txt1->getContentSize().height/2);
			txt1->addChild(ttf);
			auto txt2 = Sprite::create("lockTurretTXT1.png");
			txt2->setAnchorPoint(Point(1, 0.5));
			txt2->setPosition(0,ttf->getContentSize().height/2);
			ttf->addChild(txt2);
			auto ttf1 = LabelAtlas::create(Value(m_turretdata.rewardList.at(0).num).asString().c_str(), "multipleNum.png", 15, 21, '0');
			ttf1->setPosition(txt1->getContentSize().width, txt1->getContentSize().height/2);
			ttf1->setAnchorPoint(Point(0, 0.5));
			txt1->addChild(ttf1);
			txt1->runAction(Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(1), nullptr));
			//金币掉落
			for (int i = 0; i < 15;i++)
			{
				auto aniCoin = Sprite::create();
				aniCoin->setPosition(pos.x+40*(rand_0_1()-0.5), pos.y + 70);
				aniCoin->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniGold")));
				aniCoin->runAction(Sequence::create(DelayTime::create(0.05f*i), MoveBy::create(0.23f, Vec2(0, 86)), MoveBy::create(0.13f, Vec2(0, -86)), MoveBy::create(0.1f, Vec2(0, 27.5)), MoveBy::create(0.1f, Vec2(0, -27.5)), DelayTime::create(0.6f), MoveTo::create(0.16f, pos), RemoveSelf::create(1), nullptr));
				GameManage::getInstance()->getGuiLayer()->addChild(aniCoin,5);
			}
			//金币数字
			auto str = String::createWithFormat(":%d", m_turretdata.rewardList.at(0).num);
			auto label = LabelAtlas::create(str->getCString(),"TTFaniGold.png", 23, 34, '0');
			label->setAnchorPoint(Point::ANCHOR_MIDDLE);
			label->setPosition(GameManage::getInstance()->getGameLayer()->GetMyTurret()->getCoinLabelPos()+Vec2(0,60));
			label->setScale(0);
			label->runAction(ScaleTo::create(0.1, 1));
			label->runAction(Sequence::create(DelayTime::create(3.0f), RemoveSelf::create(), nullptr));
			GameManage::getInstance()->getGuiLayer()->addChild(label,5);
			GameManage::getInstance()->getGameLayer()->RefreShmyPlayerTurret();
		}
		else
		{
			auto layer = showTurretLayer::create(2);
			layer->setPosition(Point::ZERO);
			getParent()->getParent()->addChild(layer,20,50);
			///////弹出充值
		}
		
	}
	else
	{
		isElongate = true;
		setValue();
		runAction(MoveBy::create(0.5f, Vec2(-166, 0)));
		runAction(Sequence::create(DelayTime::create(4.0f), CallFunc::create([&]{
			if (isElongate==false)
			{
				return;
			}
			auto pNode = getChildByName("blinkAni");
			if (pNode)
			{
				pNode->removeFromParentAndCleanup(1);
			}
			runAction(MoveBy::create(0.5f, Vec2(166, 0)));
			commonNode->setVisible(false);
			unfinishedNode->setVisible(false);
			nodeZeng->setVisible(false);
			isElongate = false;
		}), nullptr));
	}
}

void MyMenuItemUpgrade::initItem()
{
	auto maxlevel = User::getInstance()->getMaxTurrentLevel();
	auto turretData = ConfigTurrent::getInstance()->getNextTurrent(maxlevel);
	auto zengList = turretData.rewardList;
	int coinnum;
	for (auto zeng:zengList)
	{
		if (zeng.itemId == 1001)
		{
			coinnum = zeng.num;
			break;
		}
	}

	nodeZeng = Node::create();
	nodeZeng->setPosition(Point::ZERO);
	unfinishedNode = Node::create();
	unfinishedNode->setPosition(Point::ZERO);
	addChild(unfinishedNode,1);
	addChild(nodeZeng,1);
	commonNode = Node::create();
	commonNode->setPosition(Point::ZERO);
	addChild(commonNode,1);
	nodeZeng->setVisible(false);
	unfinishedNode->setVisible(false);
	auto size = getContentSize();
	auto unLockTxt = Sprite::create("clickLockTXT.png");
	unLockTxt->setPosition(size.width*0.41, 33);
	commonNode->addChild(unLockTxt);
	auto mutpleLabel = LabelAtlas::create("0", "unLockNumTTF.png", 13, 19, '0');
	mutpleLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	mutpleLabel->setPosition(size.width*0.44+5,49.5);
	commonNode->addChild(mutpleLabel, 1, kTagMutpleLabel);

	//已经满足条件
	auto zeng = Sprite::create("zeng.png");
	zeng->setPosition(size.width*0.14, size.height*0.29);
	nodeZeng->addChild(zeng, 1);
	auto coinNum = LabelAtlas::create(Value(coinnum).asString().c_str(), "bonusNumTTF.png", 14, 21, '0');
	coinNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
	coinNum->setPosition(size.width*0.28+23, size.height*0.29);
	nodeZeng->addChild(coinNum, 1,kTagCoinLabel);
	auto coin = Sprite::create("smallCoin.png");
	coin->setPosition(size.width*0.6, size.height*0.29);
	nodeZeng->addChild(coin);
	//不满足条件
	auto diamond = Sprite::create("smallDiamond.png");
	diamond->setPosition(size.width*0.15+2, size.height*0.29);
	unfinishedNode->addChild(diamond);
	//经验条
	auto exeBarFrame = Sprite::create("exeBarFrameDiamond.png");
	exeBarFrame->setPosition(size.width*0.40+10, size.height*0.29);
	unfinishedNode->addChild(exeBarFrame,1,"exeFrame");
	auto exeBar = Sprite::create("exeBarDiamond.png");
	exeBar->setPosition(0+2,exeBarFrame->getContentSize().height/2);
	exeBar->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	exeBarFrame->addChild(exeBar,1,kTagExeBar);

	auto exeDec = LabelAtlas::create("0", "bonusNumTTF.png", 14, 21, '0');
	exeDec->setScale(0.8);
	exeDec->setAnchorPoint(Point::ANCHOR_MIDDLE);
	exeDec->setPosition(exeBarFrame->getContentSize() / 2);
	exeBarFrame->addChild(exeDec,1,kTagExeDec);

	isElongate = false;
	commonNode->setVisible(false);
	unfinishedNode->setVisible(false);
	nodeZeng->setVisible(false);
}

void MyMenuItemUpgrade::setValue()
{

	commonNode->setVisible(true);
	auto maxlevel = User::getInstance()->getMaxTurrentLevel();
	auto turretData = ConfigTurrent::getInstance()->getNextTurrent(maxlevel);	
	auto zengList = turretData.rewardList;
	auto diamondNum = User::getInstance()->getDiamonds();
	isFinish = diamondNum >= turretData.unlockPrice ? true : false;
	auto str = String::createWithFormat("%d:%d", diamondNum, turretData.unlockPrice);
	auto scalex = ((float)diamondNum)/((float)turretData.unlockPrice);
	int coinnum;
	for (auto zeng : zengList)
	{
		if (zeng.itemId == 1001)
		{
			coinnum = zeng.num;
			break;
		}
	}

	auto node = (LabelAtlas*)commonNode->getChildByTag(kTagMutpleLabel);
	node->setString(Value(turretData.multiple).asString().c_str());
	if (isFinish)
	{
		nodeZeng->setVisible(true);
		node = (LabelAtlas*)nodeZeng->getChildByTag(kTagCoinLabel);
		node->setString(Value(coinnum).asString().c_str());
		showBlinkAni();
	}
	else
	{
		unfinishedNode->setVisible(true);
		auto frame = unfinishedNode->getChildByName("exeFrame");
		node = (LabelAtlas*)frame->getChildByTag(kTagExeDec);
		node->setString(str->getCString());

		auto node1 = frame->getChildByTag(kTagExeBar);
		node1->setScaleX(0.93*scalex);
	}
}

void MyMenuItemUpgrade::showBlinkAni()
{
	auto node = Sprite::create("UnlockFrame_2.png");
	node->setPosition(getContentSize() / 2);
	addChild(node, -1, "blinkAni");
	node->runAction(RepeatForever::create(Sequence::create(FadeOut::create(0.5f), FadeIn::create(0.5f), nullptr)));
}
void MyMenuItemUpgrade::showPopup()
{
	if (isElongate == true)
	{
		return;
	}
	else
	{
		isElongate = true;
		setValue();
		runAction(MoveBy::create(0.5f, Vec2(-166, 0)));

		if (isFinish)
		{
			showBlinkAni();
		}
		else
		{
			runAction(Sequence::create(DelayTime::create(4.0f), CallFunc::create([&]{
				if (isElongate == true)
				{
					auto pNode = getChildByName("blinkAni");
					if (pNode)
					{
						pNode->removeFromParentAndCleanup(1);
					}
					commonNode->setVisible(false);
					unfinishedNode->setVisible(false);
					nodeZeng->setVisible(false);
					runAction(MoveBy::create(0.5f, Vec2(166, 0)));
					isElongate = false;
				};

			}), nullptr));
		}
	}
	
}
