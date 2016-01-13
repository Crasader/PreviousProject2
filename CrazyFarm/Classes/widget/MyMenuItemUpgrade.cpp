#include "MyMenuItemUpgrade.h"
#include "User.h"
#include "config/ConfigTurrent.h"
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
	if (ret && ret->initWithNormalImage("UnlockFrame_1.png", "UnlockFrame_1.png", "", CC_CALLBACK_1(MyMenuItemUpgrade::ItemCallBack, ret)));
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
	}
	else
	{
		setValue();
		runAction(MoveBy::create(0.5f, Vec2(-30, 0)));
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
	unLockTxt->setPosition(size.width*0.3, size.height*0.75);
	commonNode->addChild(unLockTxt);
	auto mutpleLabel = LabelAtlas::create("0", "unLockNumTTF.png", 13, 19, '0');
	mutpleLabel->setPosition(size.width*0.25, size.height*0.75);
	commonNode->addChild(mutpleLabel, 1, kTagMutpleLabel);

	//已经满足条件
	auto zeng = Sprite::create("zeng.png");
	zeng->setPosition(size.width*0.1, size.height*0.25);
	nodeZeng->addChild(zeng, 1);
	auto coinNum = LabelAtlas::create(Value(coinnum).asString().c_str(), "bonusNumTTF.png", 14, 21, '0');
	coinNum->setPosition(size.width*0.28, size.height*0.25);
	nodeZeng->addChild(coinNum, 1,kTagCoinLabel);
	auto coin = Sprite::create("smallCoin.png");
	coin->setPosition(size.width*0.6, size.height*0.25);
	commonNode->addChild(coin);
	//不满足条件
	auto diamond = Sprite::create("smallDiamond.png");
	diamond->setPosition(size.width*0.1, size.height*0.25);
	unfinishedNode->addChild(diamond);
	//经验条
	auto exeBarFrame = Sprite::create("exeBarFrameDiamond.png");
	exeBarFrame->setPosition(size.width*0.24, size.height*0.25);
	unfinishedNode->addChild(exeBarFrame,1,"exeFrame");
	auto exeBar = Sprite::create("exeBarDiamond.png");
	exeBar->setPosition(0, 0);
	exeBar->setAnchorPoint(Point::ZERO);
	exeBarFrame->addChild(exeBar,1,kTagExeBar);

	auto exeDec = LabelAtlas::create("0", "bonusNumTTF.png", 14, 21, '0');
	exeDec->setPosition(exeBarFrame->getContentSize() / 2);
	exeBarFrame->addChild(exeDec,1,kTagExeDec);

	isElongate = false;
	commonNode->setVisible(false);
	unfinishedNode->setVisible(false);
	nodeZeng->setVisible(false);
}

void MyMenuItemUpgrade::setValue()
{
	bool isFinish;
	
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
		node = (LabelAtlas*)getChildByTag(kTagCoinLabel);
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
