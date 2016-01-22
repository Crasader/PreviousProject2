#include "TurnTableDialog.h"
#include "domain/turntable/CTurntable.h"

#include "domain/bag/BagManager.h"
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
		addChild(table);

		auto title = Sprite::create("turntableTitle.png");
		title->setPosition(size.width / 2, 480);
		addChild(title);

		auto sp = Sprite::create("nowBounsPool.png");
		sp->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
		sp->setPosition(size.width / 2, 12);
		addChild(sp);

		//¾­ÑéÌõ
		auto bonus = BonusPoolManager::getInstance()->getNextBonuspool();
		auto nowCoin = BonusPoolManager::getInstance()->getCoins();
		auto nextCoin = bonus.start_coins;

		

		auto label = LabelAtlas::create(Value(nowCoin).asString(), "nowPoolNum.png", 13, 21, '0');
		label->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		label->setPosition(230, 41);
		sp->addChild(label);
		auto str = String::createWithFormat(":%d", nextCoin);
		label = LabelAtlas::create(str->getCString(), "nextPoolNum.png.png", 11, 19, '0');
		label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		label->setPosition(230, 41);
		sp->addChild(label);
		auto scale = (float)nowCoin / (float)nextCoin;
		auto bar = Sprite::create("turnTableExeBar.png");
		bar->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		bar->setPosition(153, 41);
		sp->addChild(bar);
		bar->setScaleX(scale*162.0f / 100.0f);

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

void TurnTableDialog::onGetRewards(BonuspoolRewardItem reward)
{
	BagManager::getInstance()->changeItemCount(reward.item_id, reward.num);
	BonusPoolManager::getInstance()->cleanCoinsAndFishCounts();
}