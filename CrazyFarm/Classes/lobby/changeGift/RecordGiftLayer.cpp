#include "RecordGiftLayer.h"
#include "utill/Chinese.h"
#include "domain/user/User.h"
#include "domain/ToolTip/ToolTipMannger.h"
#include "widget/LoadingCircle.h"
#include "utill/Audio.h"
void RecordGiftView::tableCellTouched(TableView* table, TableViewCell* cell){

}
Size RecordGiftView::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx){
	return CCSizeMake(915, 72);
}
cocos2d::extension::TableViewCell* RecordGiftView::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx){
	RecordGiftCell *cell = (RecordGiftCell*)table->dequeueCell();
	if (!cell) {
		cell = RecordGiftCell::create();
	}
	else
	{

	}
	cell->setValue(_items.at(idx));
	auto str = String::createWithFormat("RecordGiftCellBg_%d.png", idx % 2);
	cell->bg->setSpriteFrame(SpriteFrame::create(str->getCString(),Rect(0,0,16,16)));
	cell->bg->setContentSize(Size(915, 72));
	return cell;
}
ssize_t RecordGiftView::numberOfCellsInTableView(cocos2d::extension::TableView *table){
	return _items.size();
}


RecordGiftLayer*RecordGiftLayer::create(std::vector<RecordGiftItem> items)
{
	RecordGiftLayer *pRet = new RecordGiftLayer();
	if (pRet && pRet->init(items)) 
		{ 
		pRet->autorelease(); 
		return pRet; 
		} 
		else 
		{ 
		delete pRet; 
		pRet = NULL; 
		return NULL; 
		} 
	}


bool RecordGiftLayer::init(std::vector<RecordGiftItem> items)
{
	if ( !Layer::init() )
	{
		return false;
	}
	bool bRet = false;
	do 
	{
		tableviewDelegate = new RecordGiftView();
		tableviewDelegate->setRecordItem(items);
		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto bg = Sprite::create("bigFrameBg.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg);

		auto title = Sprite::create("RecordTitle.png");
		title->setPosition(480, 511);
		addChild(title);

		title = Sprite::create("RecordTitle1.png");
		title->setPosition(480, 443);
		addChild(title);

		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(RecordGiftLayer::onTouchBegan, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);

		tableView = MyTableView::create(tableviewDelegate, Size(914, 389));
		tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
		tableView->setDirection(ScrollView::Direction::VERTICAL);
		tableView->setPosition(25, 20);
		tableView->setDelegate(tableviewDelegate);
		addChild(tableView);
		tableView->reloadData();
		
		auto close = MenuItemImage::create("btn_back_1.png", "btn_back_2.png", CC_CALLBACK_1(RecordGiftLayer::closeButtonCallBack, this));
		close->setPosition(65, 515);
		auto menu = Menu::create(close, nullptr);
		menu->setPosition(0, 0);
		addChild(menu);

		bRet = true;
	} while (0);
	

	return bRet;
}

void RecordGiftLayer::closeButtonCallBack(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	removeFromParentAndCleanup(1);
}