#include "MyMenuItemUpgrade.h"
#include "domain/user/User.h"
#include "config/ConfigTurrent.h"
#include "domain/bag/BagManager.h"
#include "data/GameData.h"
#include "core/showTurretLayer.h"
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
		runAction(MoveBy::create(0.5f, Vec2(180, 0)));
		isElongate = false;
		if (isFinish)
		{
			auto a = User::getInstance()->getMaxTurrentLevel();
			auto m_turretdata = ConfigTurrent::getInstance()->getNextTurrent(a);
			User::getInstance()->setMaxTurrentLevel(m_turretdata.multiple);
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
		runAction(MoveBy::create(0.5f, Vec2(-180, 0)));
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
	addChild(unfinishedNode);
	addChild(nodeZeng);
	commonNode = Node::create();
	commonNode->setPosition(Point::ZERO);
	addChild(commonNode);
	nodeZeng->setVisible(false);
	unfinishedNode->setVisible(false);
	auto size = getContentSize();
	auto unLockTxt = Sprite::create("clickLockTXT.png");
	unLockTxt->setPosition(size.width*0.38, 38/*size.height*0.40*/);
	commonNode->addChild(unLockTxt);
	auto mutpleLabel = LabelAtlas::create("0", "unLockNumTTF.png", 13, 19, '0');
	mutpleLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	mutpleLabel->setPosition(size.width*0.41,56 /*size.height*0.50*/);
	commonNode->addChild(mutpleLabel, 1, kTagMutpleLabel);

	//已经满足条件
	auto zeng = Sprite::create("zeng.png");
	zeng->setPosition(size.width*0.15+5, size.height*0.29);
	nodeZeng->addChild(zeng, 1);
	auto coinNum = LabelAtlas::create(Value(coinnum).asString().c_str(), "bonusNumTTF.png", 14, 21, '0');
	coinNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
	coinNum->setPosition(size.width*0.28+20, size.height*0.29);
	nodeZeng->addChild(coinNum, 1,kTagCoinLabel);
	auto coin = Sprite::create("smallCoin.png");
	coin->setPosition(size.width*0.6, size.height*0.29);
	nodeZeng->addChild(coin);
	//不满足条件
	auto diamond = Sprite::create("smallDiamond.png");
	diamond->setPosition(size.width*0.15+5, size.height*0.29);
	unfinishedNode->addChild(diamond);
	//经验条
	auto exeBarFrame = Sprite::create("exeBarFrameDiamond.png");
	exeBarFrame->setPosition(size.width*0.40+10, size.height*0.29);
	unfinishedNode->addChild(exeBarFrame,1,"exeFrame");
	auto exeBar = Sprite::create("exeBarDiamond.png");
	exeBar->setPosition(0, 0);
	exeBar->setAnchorPoint(Point::ZERO);
	exeBarFrame->addChild(exeBar,1,kTagExeBar);

	auto exeDec = LabelAtlas::create("0", "bonusNumTTF.png", 14, 21, '0');
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
	isFinish = diamondNum > turretData.unlockPrice ? true : false;
	auto node = (LabelAtlas*)commonNode->getChildByTag(kTagMutpleLabel);
	node->setString(Value(turretData.multiple).asString().c_str());
	if (isFinish)
	{
		nodeZeng->setVisible(true);
		node = (LabelAtlas*)nodeZeng->getChildByTag(kTagCoinLabel);
		node->setString(Value(coinnum).asString().c_str());
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
		runAction(MoveBy::create(0.5f, Vec2(-180, 0)));

		if (isFinish)
		{
			//闪烁动画
		}
		else
		{
			runAction(Sequence::create(DelayTime::create(3.5f), CallFunc::create([&]{
				if (isElongate == true)
				{
					commonNode->setVisible(false);
					unfinishedNode->setVisible(false);
					nodeZeng->setVisible(false);
					runAction(MoveBy::create(0.5f, Vec2(180, 0)));
					isElongate = false;
				};

			}), nullptr));
		}
	}
	
}
