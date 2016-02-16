#include "MyMenuItemGainMoney.h"
#include "domain/bonuspool/BonusPoolManager.h"
#include "core/TurnTableDialog.h"
#include "domain/logevent/LogEventPageChange.h"
enum 
{
	kTagMutpleLabel = 10,
	kTagExeDec = 11,
	kTagExeBar = 12,
	kTagCoinLabel=13

};

MyMenuItemGainMoney * MyMenuItemGainMoney::create()
{
	MyMenuItemGainMoney *ret = new (std::nothrow) MyMenuItemGainMoney();
	if (ret && ret->initWithNormalImage("UnlockFrame_1.png", "UnlockFrame_1.png", "", CC_CALLBACK_1(MyMenuItemGainMoney::ItemCallBack, ret)));
	{
		ret->initItem();
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}
void MyMenuItemGainMoney::ItemCallBack(Ref* psend)
{
	isFinish = true;
	 BonusPoolManager::getInstance()->addCoins(100000);
	 BonusPoolManager::getInstance()->addCoins(100000);
	 BonusPoolManager::getInstance()->addCoins(100000);
	 BonusPoolManager::getInstance()->addCoins(100000);
	 BonusPoolManager::getInstance()->addCoins(100000);
	 BonusPoolManager::getInstance()->addCoins(100000);
	 BonusPoolManager::getInstance()->addCoins(100000);
	if (isElongate)
	{
		commonNode->setVisible(false);
		runAction(MoveBy::create(0.5f, Vec2(166, 0)));
		isElongate = false;
		if (isFinish)
		{
			auto dioag = TurnTableDialog::create();
			dioag->setPosition(Point::ZERO);
			LogEventPageChange::getInstance()->addEventItems(2, 10, 0);
			getParent()->getParent()->addChild(dioag,20);
		}
		else
		{
			
		}
	}
	else
	{
		isElongate = true;
		setValue();
		runAction(MoveBy::create(0.5f, Vec2(-166, 0)));
		runAction(Sequence::create(DelayTime::create(5.0f), CallFunc::create([&]{
			if (isElongate == false)
			{
				return;
			}
			runAction(MoveBy::create(0.5f, Vec2(166, 0)));
			commonNode->setVisible(false);
			isElongate = false;
		}), nullptr));
	}
}

void MyMenuItemGainMoney::initItem()
{

	commonNode = Node::create();
	commonNode->setPosition(Point::ZERO);
	addChild(commonNode);
	commonNode->setVisible(false);
	auto size = getContentSize();
	auto txt = Sprite::create("fishPoolTxt.png");
	txt->setPosition(size.width*0.38+5, size.height/2);
	commonNode->addChild(txt);

	//¾­ÑéÌõ
	auto exeBarFrame = Sprite::create("exeBarFrameDiamond.png");
	exeBarFrame->setPosition(size.width*0.40 + 16, 50);
	commonNode->addChild(exeBarFrame, 1, "exeFrame");
	auto exeBar = Sprite::create("exeBarDiamond.png");
	exeBar->setPosition(2, exeBarFrame->getContentSize().height/2);
	exeBar->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	exeBarFrame->addChild(exeBar, 1, kTagExeBar);

	auto exeDec = LabelAtlas::create("0", "bonusNumTTF.png", 14, 21, '0');
	exeDec->setAnchorPoint(Point::ANCHOR_MIDDLE);
	exeDec->setPosition(exeBarFrame->getContentSize() / 2);
	exeBarFrame->addChild(exeDec, 1, kTagExeDec);



	
	auto coinNum = LabelAtlas::create(Value(0).asString().c_str(), "bonusNumTTF.png", 14, 21, '0');
	coinNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
	coinNum->setPosition(size.width*0.28+24, size.height*0.29-4);
	commonNode->addChild(coinNum, 1, kTagCoinLabel);
	auto coin = Sprite::create("smallCoin.png");
	coin->setPosition(size.width*0.6, size.height*0.29-2);
	commonNode->addChild(coin);
	
	

	isElongate = false;
	commonNode->setVisible(false);

}

void MyMenuItemGainMoney::setValue()
{

	commonNode->setVisible(true);
	int nowFish = BonusPoolManager::getInstance()->getFishCounts();
	int alowdFish = BonusPoolManager::getInstance()->getAllowCatchFishCounts();
	int poolNum = BonusPoolManager::getInstance()->getCoins();
	auto str = String::createWithFormat("%d:%d", nowFish, alowdFish);
	auto scalex = ((float)nowFish) / ((float)alowdFish);

	
	isFinish = nowFish >= alowdFish ? true : false;
	auto node = (LabelAtlas*)commonNode->getChildByTag(kTagCoinLabel);
	node->setString(Value(poolNum).asString().c_str());
	auto frame = commonNode->getChildByName("exeFrame");
	node = (LabelAtlas*)frame->getChildByTag(kTagExeDec);
	node->setString(str->getCString());
	auto node1 = frame->getChildByTag(kTagExeBar);
	node1->setScaleX(0.93*scalex);
	
}
