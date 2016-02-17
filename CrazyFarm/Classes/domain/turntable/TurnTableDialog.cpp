#include "TurnTableDialog.h"
#include "domain/turntable/CTurntable.h"
#include "domain/bag/BagManager.h"
#include "domain/bonuspool/BonusPoolManager.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
bool TurnTableDialog::init()
{
	Layer::init();
	bool bRet = false;
	do
	{ 

		auto colorlayer = LayerColor::create();
		colorlayer->setColor(ccc3(0, 0, 0));
		colorlayer->setOpacity(180);
		addChild(colorlayer, -1);

		auto size = Director::getInstance()->getVisibleSize();
		auto table = CTurntable::create();
		table->setPosition(size / 2);
		addChild(table,1);

		auto title = Sprite::create("turntableTitle.png");
		title->setPosition(size.width / 2, 480);
		addChild(title);

		

		createBottomFrame(BonusPoolManager::getInstance()->allowBonusPool());


		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(TurnTableDialog::closeButtonCallBack, this));
		close->setPosition(730, 430);
		auto menu = Menu::create(close, nullptr);
		menu->setPosition(Point::ZERO);
		addChild(menu);

		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(TurnTableDialog::onTouchBegan, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);



		bRet = true;
	} while (0);


	return bRet;
}
void TurnTableDialog::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}
void TurnTableDialog::choujiangButtonCallBack(Ref*psend)
{

}
void TurnTableDialog::showGoldFishButtonCallBack(Ref*psend)
{

}

void TurnTableDialog::onGetRewards(BonuspoolRewardItem reward)
{
	BagManager::getInstance()->changeItemCount(reward.item_id, reward.num);
	BonusPoolManager::getInstance()->cleanCoinsAndFishCounts();
}

void TurnTableDialog::createBottomFrame(bool isFinish)
{
	auto sp = Sprite::create("nowBounsPool.png");
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	sp->setPosition(960 / 2, 38);
	addChild(sp);

	auto tiptxt = Sprite::create("TXTbounsTip.png");
	tiptxt->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	tiptxt->setPosition(960 / 2, 9);
	addChild(tiptxt);
	if (isFinish)
	{
		//继续获取更多话费
		auto txt = Sprite::create("TXTJixu.png");
		txt->setPosition(169, 69);
		sp->addChild(txt);
		auto smallcoin = Sprite::create("smallCoin.png");
		smallcoin->setPosition(54, 34);
		sp->addChild(smallcoin);
		//经验条
		auto bonus = BonusPoolManager::getInstance()->getNextBonuspool();
		int nextCoin;
		if (bonus)
		{
			nextCoin = bonus->start_coins;
		}
		else
		{
			nextCoin = -1;
		}
		auto barframe = Sprite::create("bounsbarframe.png");
		barframe->setPosition(181, 33);
		sp->addChild(barframe);

		auto bar = Scale9Sprite::create("turnTableExeBar.png", Rect(0, 0, 26, 24), Rect(8, 0, 11, 24));
		bar->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		bar->setPosition(5, barframe->getContentSize().height / 2);
		barframe->addChild(bar);

		auto nowCoin = BonusPoolManager::getInstance()->getCoins();
		auto label = LabelAtlas::create(Value(nowCoin).asString(), "nowPoolNum.png", 13, 21, '0');
		label->setScale(0.9);
		label->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		label->setPosition(barframe->getContentSize().width / 2 - 5, barframe->getContentSize().height / 2);
		barframe->addChild(label);
		// “/”符号
		label = LabelAtlas::create(":", "nextPoolNum.png", 11, 19, '0');
		label->setAnchorPoint(Point::ANCHOR_MIDDLE);
		label->setPosition(barframe->getContentSize() / 2);
		barframe->addChild(label);

		
		if (nextCoin == -1)
		{
			auto max = Sprite::create("MAX.png");
			max->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
			max->setPosition(label->getPositionX() + label->getContentSize().width / 2, label->getPositionY());
			barframe->addChild(max);
			max->setScale(0.9);
			bar->setContentSize(Size(197, 24));
		}
		else
		{
			auto nextlabel = LabelAtlas::create(Value(nextCoin).asString(), "nextPoolNum.png", 11, 19, '0');
			label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
			label->setPosition(label->getPositionX() + label->getContentSize().width / 2, label->getPositionY());
			barframe->addChild(label);
			auto scale = (float)nowCoin / (float)nextCoin;
			bar->setContentSize(Size(scale*26.0f / 197, 24));
		}
		//按钮
		auto bt = MenuItemImage::create("btn_choujiang_1.png", "btn_choujiang_2.png", CC_CALLBACK_1(TurnTableDialog::choujiangButtonCallBack, this));
		bt->setPosition(382, 45);
		auto menu = Menu::create(bt, nullptr);
		menu->setPosition(Point::ZERO);
		sp->addChild(menu);
	}
	else
	{
		//再杀几条黄金鱼
		auto txt = Sprite::create("TXTzshjy.png");
		txt->setPosition(169, 69);
		sp->addChild(txt);
		
		auto goldfishneed = LabelAtlas::create(Value(BonusPoolManager::getInstance()->getFishNeedCatchToChoujiang()).asString(), "nowPoolNum.png", 13, 21, '0');
		goldfishneed->setScale(1.5);
		goldfishneed->setAnchorPoint(Point::ANCHOR_MIDDLE);
		goldfishneed->setPosition(54, 13);
		txt->addChild(goldfishneed);

		//经验条
		auto bonus = BonusPoolManager::getInstance();
		auto nowfish = bonus->getFishCounts();
		auto allowdfish = bonus->getAllowCatchFishCounts();

		auto barframe = Sprite::create("bounsbarframe.png");
		barframe->setPosition(181, 33);
		sp->addChild(barframe);

		auto bar = Scale9Sprite::create("turnTableExeBar.png", Rect(0, 0, 26, 24), Rect(8, 0, 11, 24));
		bar->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		bar->setPosition(5, barframe->getContentSize().height / 2);
		barframe->addChild(bar);

		
		auto label = LabelAtlas::create(Value(nowfish).asString(), "nowPoolNum.png", 13, 21, '0');
		label->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		label->setPosition(barframe->getContentSize().width / 2 - 10, barframe->getContentSize().height / 2);
		barframe->addChild(label);
		auto str = String::createWithFormat(":%d", allowdfish);
		label = LabelAtlas::create(str->getCString(), "nextPoolNum.png", 11, 19, '0');
		label->setAnchorPoint(Point::ANCHOR_MIDDLE);
		label->setPosition(barframe->getContentSize() / 2);
		barframe->addChild(label);


		//按钮
		auto bt = MenuItemImage::create("btn_showgoldFish_1.png", "btn_showgoldFish_2.png", CC_CALLBACK_1(TurnTableDialog::showGoldFishButtonCallBack, this));
		bt->setPosition(382, 45);
		auto menu = Menu::create(bt, nullptr);
		menu->setPosition(Point::ZERO);
		sp->addChild(menu);
	}
}