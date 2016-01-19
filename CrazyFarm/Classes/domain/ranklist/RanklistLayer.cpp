#include "domain/ranklist/RanklistLayer.h"
#include "domain/ranklist/RanklistManager.h"
#include "utill/Chinese.h"

void RanklistView::tableCellTouched(TableView* table, TableViewCell* cell){

}
Size RanklistView::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx){
	return CCSizeMake(892, 100);
}
cocos2d::extension::TableViewCell* RanklistView::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx){
	RanklistCell *cell = (RanklistCell*)table->dequeueCell();
	if (!cell) {
		cell = RanklistCell::create();
	}
	else
	{

	}
	if (m_type == 1)
	{
		cell->setExpValue(idx);
	}
	else
	{
		cell->setCoinValue(idx);
	}
	return cell;
}
ssize_t RanklistView::numberOfCellsInTableView(cocos2d::extension::TableView *table){
	if (m_type==1)
	{
		return RanklistManager::getInstance()->getExpRankListData().size();
	}
	else
	{
		return RanklistManager::getInstance()->getCoinRankListData().size();
	}
}




Scene* RanklistLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = RanklistLayer::create();

	scene->addChild(layer);

	return scene;
}

bool RanklistLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	bool bRet = false;
	do 
	{
		tableviewDelegate = new RanklistView();
		tableviewDelegate->setType(2);
		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto bg = Sprite::create("ranklistBg.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg);



		//tableview
		auto tableView = MyTableView::create(tableviewDelegate, Size(894,387));
		tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
		tableView->setDirection(ScrollView::Direction::VERTICAL);
		tableView->setPosition(35,20);
		tableView->setDelegate(tableviewDelegate);
		addChild(tableView);
		tableView->reloadData();



		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(RanklistLayer::onTouchBegan, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);


		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(RanklistLayer::closeButtonCallBack, this));
		close->setPosition(800, 480);
		auto menu = Menu::create(close, nullptr);
		menu->setPosition(Point::ZERO);
		addChild(menu);


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

void RanklistLayer::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}

void RanklistLayer::chankanCallBack(Ref*pesend)
{

}