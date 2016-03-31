#include "MissionLayer.h"
#include "MissionManager.h"
#include "utill/Chinese.h"
#include "domain/user/User.h"

void MissionView::tableCellTouched(TableView* table, TableViewCell* cell){

}
Size MissionView::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx){
	return CCSizeMake(700, 106);
}
cocos2d::extension::TableViewCell* MissionView::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx){
	MissionCell *cell = (MissionCell*)table->dequeueCell();
	if (!cell) {
		cell = MissionCell::create();
	}
	else
	{

	}
	cell->setValue(MissionManager::getInstance()->getMissionListData().at(idx));
	return cell;
}
ssize_t MissionView::numberOfCellsInTableView(cocos2d::extension::TableView *table){
	return MissionManager::getInstance()->getMissionListData().size();
}




Scene* MissionLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = MissionLayer::create();

	scene->addChild(layer);

	return scene;
}

bool MissionLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	bool bRet = false;
	do 
	{
		tableviewDelegate = new MissionView();
		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto bg = Sprite::create("missionFrame.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg);



		//tableview
		tableView = MyTableView::create(tableviewDelegate, Size(894,383));
		tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
		tableView->setDirection(ScrollView::Direction::VERTICAL);
		tableView->setPosition(35,26);
		tableView->setDelegate(tableviewDelegate);
		bg->addChild(tableView);
		tableView->reloadData();

	
		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(MissionLayer::onTouchBegan, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);


		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(MissionLayer::closeButtonCallBack, this));
		close->setPosition(bg->getContentSize());
		close->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);

		auto sp1 = Sprite::create("tab_1.png");
		auto txt1 = Sprite::create("dayMission_1.png");
		txt1->setPosition(sp1->getContentSize() / 2);
		sp1->addChild(txt1);
		auto sp2 = Sprite::create("tab_2.png");
		auto txt2 = Sprite::create("dayMission_2.png");
		txt2->setPosition(sp2->getContentSize() / 2);
		sp2->addChild(txt2);

		auto coinButton = MenuItemSprite::create(sp1,sp2, CC_CALLBACK_1(MissionLayer::changeTypeCallBack, this));
		coinButton->setName("coin");
		coinButton->setPosition(109+22, 439);
		coinButton->setEnabled(false);


		sp1 = Sprite::create("tab_1.png");
		txt1 = Sprite::create("achieveMission_1.png");
		txt1->setPosition(sp1->getContentSize() / 2);
		sp1->addChild(txt1);
		 sp2 = Sprite::create("tab_2.png");
		txt2 = Sprite::create("achieveMission_2.png");
		txt2->setPosition(sp2->getContentSize() / 2);
		sp2->addChild(txt2);

		auto expButton = MenuItemSprite::create(sp1,sp2, CC_CALLBACK_1(MissionLayer::changeTypeCallBack, this));
		expButton->setName("exp");
		expButton->setPosition(298+22, 439);
		auto menu = Menu::create(close, coinButton, expButton,nullptr);
		menu->setPosition(Point::ZERO);
		bg->addChild(menu);
		coinButton->selected();


	//添加系统返回键监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			removeFromParentAndCleanup(1);
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
		bRet = true;
	} while (0);
	

	return bRet;
}

void MissionLayer::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}

void MissionLayer::changeTypeCallBack(Ref*psend)
{
	auto bt = (MenuItemImage*)(psend);
	auto btName = bt->getName();
	if (btName == "coin")
	{
		bt->setEnabled(false);
		bt->selected();
		auto otherBt = (MenuItemImage*)bt->getParent()->getChildByName("exp");
		otherBt->unselected();
		otherBt->setEnabled(true);
		changeToCoinRanklist();
	}
	else
	{
		bt->setEnabled(false);
		bt->selected();
		auto otherBt = (MenuItemImage*)bt->getParent()->getChildByName("coin");
		otherBt->unselected();
		otherBt->setEnabled(true);
		changeToexpRanklist();
	}
}
void MissionLayer::changeToexpRanklist()
{
	/*coinsp->setTexture("EXP.png");
	
	haveCoinTTF->setString(ChineseWord("haveExp").c_str());
	CoinNumTTF->setString(Value(User::getInstance()->getExp()).asString().c_str());




	bool isZero = (User::getInstance()->getExp() <= 0);
	auto rank = RanklistManager::getInstance()->getRankByExp(User::getInstance()->getExp());
	std::string rankTxt = Value(rank).asString().c_str();
	if (isZero)
	{
		rankTxt += ":";
	}
	labelRank->setString(rankTxt.c_str());
	tableviewDelegate = new MissionView();
	tableviewDelegate->setType(1);
	tableView->setDelegate(tableviewDelegate);
	tableView->setDataSource(tableviewDelegate);
	tableView->reloadData();*/
}

void MissionLayer::changeToCoinRanklist()
{
	/*coinsp->setTexture("coin.png");
	haveCoinTTF->setString(ChineseWord("haveCoin").c_str());
	auto coinStr = String::createWithFormat("%ld", User::getInstance()->getCoins())->getCString();
	CoinNumTTF->setString(coinStr);




	bool isZero = (User::getInstance()->getCoins() <= 0);
	auto rank = RanklistManager::getInstance()->getRankByCoin(User::getInstance()->getCoins());
	std::string rankTxt = Value(rank).asString().c_str();
	if (isZero)
	{
		rankTxt += ":";
	}
	labelRank->setString(rankTxt.c_str());
	tableviewDelegate = new MissionView();
	tableviewDelegate->setType(2);
	tableView->setDelegate(tableviewDelegate);
	tableView->setDataSource(tableviewDelegate);
	tableView->reloadData();*/
}