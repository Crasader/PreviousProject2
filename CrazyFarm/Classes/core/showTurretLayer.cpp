#include "lobby/viplayer/VipLayer.h"
#include "ConfigItem.h"
#include "User.h"
#include "widget/MyTableView.h"
#include "utill/Chinese.h"

void VIPView::tableCellTouched(TableView* table, TableViewCell* cell){

}
Size VIPView::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx){
	return CCSizeMake(250, 600);
}
cocos2d::extension::TableViewCell* VIPView::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx){
	VipCell *cell = (VipCell*)table->dequeueCell();
	if (!cell) {
		cell = VipCell::create();
	}
	else
	{

	}
	cell->setValue(idx+1);
	return cell;
}
ssize_t VIPView::numberOfCellsInTableView(cocos2d::extension::TableView *table){
	return 9;
}




















Scene* VIPLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = VIPLayer::create();

	scene->addChild(layer);

	return scene;
}

bool VIPLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	bool bRet = false;
	do 
	{
		tableviewDelegate = new VIPView();
		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto colorlayer = LayerColor::create();
		colorlayer->setColor(ccc3(0, 0, 0));
		colorlayer->setOpacity(180);
		addChild(colorlayer, -1);
		auto bg = Sprite::create("VIP_di.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg);

		////再充值XX元成为VIP
		auto nowVip = User::getInstance()->getVipLevel();
		auto nowChargeMoney = User::getInstance()->getChargeMoney();
		auto vipConfig = ConfigVipLevel::getInstance();
		auto nextVip = vipConfig->getVipLevel(nowVip + 1);
	


	
		

		auto VipExpFram = Sprite::create("VIP_exp.png");
		VipExpFram->setPosition(visibleSize.width*0.5, visibleSize.height*0.2);
		addChild(VipExpFram);

		auto VIPtitle = Sprite::create("VIPtxt.png");
		VIPtitle->setPosition(visibleSize.width*0.2, visibleSize.height*0.2);
		addChild(VIPtitle);

		auto VIPTTF = LabelAtlas::create(Value(nowVip).asString(), "VIPnum.png", 31, 43, '0');
		VIPTTF->setAnchorPoint(Point::ANCHOR_MIDDLE);
		VIPTTF->setPosition(visibleSize.width*0.2 + 60, visibleSize.height*0.2);
		addChild(VIPTTF);

		auto scale = ((float)nowChargeMoney) / ((float)nextVip.charge_money);

		auto VipExpBar = Sprite::create("VIP_expBar.png");
		VipExpBar->setPosition(VipExpFram->getContentSize() / 2);
		VipExpBar->setScaleX(scale*(302.0 / 100.0));
		VipExpFram->addChild(VipExpBar);

		auto VIPtitle1 = Sprite::create("VIPtxt.png");
		VIPtitle1->setPosition(visibleSize.width*0.8, visibleSize.height*0.2);
		addChild(VIPtitle1);

		auto VIPTTF1 = LabelAtlas::create(Value(nowVip+1).asString(), "VIPnum.png", 31, 43, '0');
		VIPTTF1->setAnchorPoint(Point::ANCHOR_MIDDLE);
		VIPTTF1->setPosition(visibleSize.width*0.8 + 60, visibleSize.height*0.2);
		addChild(VIPTTF1);


/*
		auto frame = Sprite::create("txtPriceDes.png");
		frame->setScaleX(3);
		frame->setPosition(visibleSize.width*0.4, visibleSize.height*0.1);
		addChild(frame);*/

		
		auto chinaword = ChineseWord("VIPdes");
		auto strdec = String::createWithFormat(chinaword.c_str(), nextVip.charge_money - nowChargeMoney, nextVip.vip_level);
		auto ttf = LabelTTF::create(strdec->getCString(), "Airal", 20);
		ttf->setAnchorPoint(Point::ANCHOR_MIDDLE);
		ttf->setPosition(visibleSize.width*0.5, visibleSize.height*0.1);
		addChild(ttf);


		







		//tableview
		MyTableView* tableView = MyTableView::create(tableviewDelegate, Size(800,500));
		tableView->setDirection(ScrollView::Direction::HORIZONTAL);
		tableView->setPosition(60,170);
		tableView->setDelegate(tableviewDelegate);
		addChild(tableView);
		tableView->reloadData();



		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(VIPLayer::onTouchBegan, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);


		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(VIPLayer::closeButtonCallBack, this));
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

void VIPLayer::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}

void VIPLayer::chankanCallBack(Ref*pesend)
{

}