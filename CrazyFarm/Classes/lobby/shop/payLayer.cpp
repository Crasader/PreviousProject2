#include "payLayer.h"
#include "ConfigItem.h"
#include "BagManager.h"
#include "User.h"
#include "widget/MyTableView.h"
enum 
{
	kDesignTagCell1,
	kDesignTagCell2,

};


void payTableViewCell::setPayValue(int idx)
{
	auto bagData = BagManager::getInstance();

	auto node = (PayCell*)getChildByTag(kDesignTagCell1);
	node->setDiamondValue(idx*2+1);

	node = (PayCell*)getChildByTag(kDesignTagCell2);
	node->setDiamondValue(idx * 2 + 2);

}

bool payTableViewCell::init()
{
	bool ret = false;
	do
	{

		float startX = 30;
		float offsetX = 280;
		float offsetY = -10;
		cell0 = PayCell::create();
		cell0->setAnchorPoint(Point::ZERO);
		cell0->setPosition(ccp(startX, offsetY));
		addChild(cell0, 0, kDesignTagCell1);
		startX += offsetX;

		cell1 = PayCell::create();
		cell1->setAnchorPoint(Point::ZERO);
		cell1->setPosition(ccp(startX, offsetY));
		addChild(cell1, 1,kDesignTagCell2);
		startX += offsetX;

		ret = true;
	} while (0);
	return ret;
}



void payView::tableCellTouched(TableView* table, TableViewCell* cell){
	MyTableView * myTableView = (MyTableView*)table;
	Point lastEnd = myTableView->getLastEnd();
	PayCell * selectedCell = NULL;
	PayCell * cell0 = (PayCell*)cell->getChildByTag(kDesignTagCell1);
	PayCell * cell1 = (PayCell*)cell->getChildByTag(kDesignTagCell2);
	CCPoint end = cell->convertToNodeSpace(lastEnd);
	CCRect bb1 = cell0->boundingBox();
	CCRect bb2 = cell1->boundingBox();
	if (bb1.containsPoint(end))
	{
		selectedCell = cell0;
	}
	else if (bb2.containsPoint(end))
	{
		selectedCell = cell1;
	}
	selectedCell->IsBeToued();
}
Size payView::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx){
	return CCSizeMake(278, 86);
}
cocos2d::extension::TableViewCell* payView::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx){
	payTableViewCell *cell = (payTableViewCell*)table->dequeueCell();
	if (!cell) {
		cell = payTableViewCell::create();
	}
	else
	{

	}
	cell->setPayValue(idx);
	return cell;
}
ssize_t payView::numberOfCellsInTableView(cocos2d::extension::TableView *table){
	return 6;
}




















Scene* payLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = payLayer::create();

	scene->addChild(layer);

	return scene;
}

bool payLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	bool bRet = false;
	do 
	{
		tableviewDelegate = new payView();
		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto bg = Sprite::create("paybg.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg,-1);
	
		auto bottomframe = Sprite::create("bottomFrame.png");
		bottomframe->setPosition(visibleSize.width / 2, visibleSize.height*0.5);
		addChild(bottomframe);
	

		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(payLayer::closeButtonCallBack, this));
		close->setPosition(700,400);
		auto menu = Menu::create(close,nullptr);
		menu->setPosition(Point::ZERO); 
		addChild(menu);





		//背包
		MyTableView* tableView = MyTableView::create(tableviewDelegate, bottomframe->getContentSize());
		tableView->setAnchorPoint(Point::ZERO);
		tableView->setDirection(ScrollView::Direction::VERTICAL);
		tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
		tableView->setPosition(5,10);
		tableView->setDelegate(tableviewDelegate);
		bottomframe->addChild(tableView);
		tableView->reloadData();






		//屏蔽向下触摸
		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(payLayer::onTouchBegan, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);
		

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

void payLayer::closeButtonCallBack(Ref*psend)
{
	Director::getInstance()->popScene();
}

