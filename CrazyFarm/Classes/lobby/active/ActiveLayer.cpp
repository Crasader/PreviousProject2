#include "ActiveLayer.h"
#include "utill/Chinese.h"
#include "domain/user/User.h"
#include "domain/ToolTip/ToolTipMannger.h"
#include "widget/LoadingCircle.h"
#include "utill/Audio.h"
#include "server/HttpMannger.h"
#include "domain/UrlImage/UrlImageMannger.h"
void ActivetView::tableCellTouched(TableView* table, TableViewCell* cell){

}
Size ActivetView::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx){
	return CCSizeMake(891, 172);
}
cocos2d::extension::TableViewCell* ActivetView::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx){
	ActiveCell *cell = (ActiveCell*)table->dequeueCell();
	if (!cell) {
		cell = ActiveCell::create();
	}
	else
	{

	}
	cell->setImg(itemImgs.at(idx));
	return cell;
}
ssize_t ActivetView::numberOfCellsInTableView(cocos2d::extension::TableView *table){
	return itemImgs.size();
}
void ActivetView::addImg(std::string str)
{
	itemImgs.push_back(str);

}




Scene* ActiveLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = ActiveLayer::create();

	scene->addChild(layer);

	return scene;
}

bool ActiveLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	bool bRet = false;
	do 
	{
		tableviewDelegate = new ActivetView();
		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto bg = Sprite::create("activeFrame.jpg");
		bg->setPosition(visibleSize / 2);
		addChild(bg);

		auto titlefram = Sprite::create("activeTitleFrame.png");
		titlefram->setPosition(480, 511);
		addChild(titlefram);
		auto title = Sprite::create("activeTitle.png");
		title->setPosition(480, 511);
		addChild(title);



		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(ActiveLayer::onTouchBegan, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);


		EventListenerCustom* _listener2 = EventListenerCustom::create("get_active_info", [=](EventCustom* event){

			ActivedValue*value = static_cast<ActivedValue*>(event->getUserData());
			if (value->_errorcode == 0)
			{
				imgs = value->imgUrls;
				for (int i = 0; i < value->imgUrls.size();i++)
				{
					UrlImageMannger::getInstance()->LoadImgByUrl(value->imgUrls.at(i));
				}
			}
			else
			{
				removeFromParentAndCleanup(1);
				ToolTipMannger::showDioag(value->_errormsg);
			}
	
			Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("get_active_info");
		
		});
		LoadingCircle::showLoadingCircle();
		HttpMannger::getInstance()->HttpToPostRequestToGetActiveInfo();
		Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listener2, 1);

		//暂且这样处理
		scheduleOnce([=](float dt){
			LoadingCircle::RemoveLoadingCircle();
			for (auto var:imgs)
			{
				tableviewDelegate->addImg(var);

			}
			tableView = MyTableView::create(tableviewDelegate, Size(894, 450));
			tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
			tableView->setDirection(ScrollView::Direction::VERTICAL);
			tableView->setPosition(35, 40);
			tableView->setDelegate(tableviewDelegate);
			addChild(tableView);
			tableView->reloadData();


			auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(ActiveLayer::closeButtonCallBack, this));
			close->setPosition(960, 540);
			close->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
			auto menu = Menu::create(close, nullptr);
			menu->setPosition(Point::ZERO);
			addChild(menu);
		}, 2.0f,"kk");
		bRet = true;
	} while (0);
	
	
	return bRet;
}
void ActiveLayer::update(float dt)
{

}
void ActiveLayer::closeButtonCallBack(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	removeFromParentAndCleanup(1);
}
