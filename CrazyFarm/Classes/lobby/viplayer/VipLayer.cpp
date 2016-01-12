#include "lobby/viplayer/VipLayer.h"
#include "ConfigItem.h"
#include "User.h"
#include "widget/MyTableView.h"


void VIPView::tableCellTouched(TableView* table, TableViewCell* cell){

}
Size VIPView::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx){
	return CCSizeMake(200, 243);
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









		//auto user = User::getInstance();
		//auto leveldata = user->getLevelData();
		//auto bagFram = Sprite::create("bagFrame.png");
		//bagFram->setPosition(visibleSize.width/2, visibleSize.height*0.45);
		//addChild(bagFram);
		//auto sssize = bagFram->getContentSize();
		////标题
		//auto titleFram = Sprite::create("redframe.png");
		//titleFram->setPosition(sssize.width / 2, sssize.height*0.95);
		//auto title = Sprite::create("bagTitle.png");
		//title->setPosition(titleFram->getContentSize().width*0.5,titleFram->getContentSize().height*0.6);
		//titleFram->addChild(title);
		//bagFram->addChild(titleFram);


		////人物信息框
		//auto playinfoFram = Sprite::create("playinfoFram.png");
		//playinfoFram->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		//playinfoFram->setPosition(15, sssize.height*0.45);
		//bagFram->addChild(playinfoFram);
		//auto sssize2 = playinfoFram->getContentSize();
		//auto spHead = Sprite::create();
		//int sex = rand() % 2;
		//if (sex)
		//{
		//	spHead->setTexture("bagMale.png");
		//}
		//else
		//{
		//	spHead->setTexture("bagFamale.png");
		//}
		//spHead->setPosition(sssize2.width*0.19, sssize2.height*0.82);
		//playinfoFram->addChild(spHead);
		////昵称
		//auto userName = LabelTTF::create(user->getUserName(), "arial", 20);
		//userName->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
		//userName->setPosition(sssize2.width*0.62, sssize2.height*0.83);
		//playinfoFram->addChild(userName);
		////等级
		//auto spLV = Sprite::create("LV.png");
		//spLV->setPosition(sssize2.width*0.385, sssize2.height*0.74);
		//playinfoFram->addChild(spLV);
		//auto userlevel = LabelAtlas::create(Value(leveldata.levelId).asString().c_str(), "levelnum.png", 12, 17, '0');
		//userlevel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		//userlevel->setPosition(spLV->getPositionX()+spLV->getContentSize().width, spLV->getPositionY());
		//playinfoFram->addChild(userlevel);
		////金币
		//auto userCoin = LabelTTF::create(Value(user->getCoins()).asString().c_str(), "arial", 20);
		//userCoin->setAnchorPoint(Point::ANCHOR_MIDDLE);
		//userCoin->setPosition(sssize2.width*0.65, sssize2.height *0.60);
		//userCoin->setColor(Color3B::WHITE);
		//playinfoFram->addChild(userCoin);
		////钻石
		//auto userdiamond = LabelTTF::create(Value(user->getDiamonds()).asString().c_str(), "arial", 20);
		//userdiamond->setAnchorPoint(Point::ANCHOR_MIDDLE);
		//userdiamond->setPosition(sssize2.width*0.65, sssize2.height *0.485);
		//userdiamond->setColor(Color3B::WHITE);
		//playinfoFram->addChild(userdiamond);
		////VIP
		//auto viplevel = LabelTTF::create(Value(user->getVipLevel()).asString().c_str(), "arial", 20);
		//viplevel->setPosition(sssize2.width*0.65, sssize2.height *0.37);
		//playinfoFram->addChild(viplevel);
		////经验
		////////////////////////////////////////////////////////////
		//

		//auto leveldataa = user->getLevelData();
		//auto levelDes = String::createWithFormat("%d:%d", leveldataa.haveExp, leveldataa.passNeedExp);
		//

		//auto exeMur = (leveldataa.haveExp*1.0) / (1.0*leveldataa.passNeedExp);
		//auto exeBarLeft = Sprite::create("exe_left.png");
		//exeBarLeft->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		//exeBarLeft->setPosition(sssize2.width*0.51, sssize2.height*0.745);
		//playinfoFram->addChild(exeBarLeft);
		//auto exeBarMid = Sprite::create("exe_mid.png");
		//exeBarMid->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		//exeBarMid->setScaleX(140.0 / exeBarMid->getContentSize().width*exeMur);
		//exeBarMid->setPosition(exeBarLeft->getContentSize().width, exeBarLeft->getContentSize().height / 2);
		//exeBarLeft->addChild(exeBarMid);
		//auto exeBarRight = Sprite::create("exe_right.png");
		//exeBarRight->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		//exeBarRight->setPosition(exeBarMid->getBoundingBox().size.width, exeBarMid->getContentSize().height / 2);
		//exeBarMid->addChild(exeBarRight);


		//auto exeDescribe = LabelAtlas::create(levelDes->getCString(), "exeNum.png", 12, 18, '0');
		//exeDescribe->setAnchorPoint(Point::ANCHOR_MIDDLE);
		//exeDescribe->setPosition(sssize2.width*0.72, sssize2.height*0.74);
		//playinfoFram->addChild(exeDescribe);






		////背包信息框
		//auto baginfoFram = Sprite::create("baginFrame.png");
		//baginfoFram->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		//baginfoFram->setPosition(sssize.width-15, sssize.height*0.45);
		//bagFram->addChild(baginfoFram);



		//auto chakan = MenuItemImage::create("btn_small_1.png", "btn_small_2.png", CC_CALLBACK_1(BagLayer::chankanCallBack, this));
		//chakan->setPosition(visibleSize.width*0.48, visibleSize.height * 0.3103);
		//auto chakan1 = MenuItemImage::create("btn_small_1.png", "btn_small_2.png", CC_CALLBACK_1(BagLayer::chankanCallBack, this));
		//chakan1->setPosition(visibleSize.width*0.48, visibleSize.height * 0.2303);
		//auto setname = MenuItemImage::create("btn_big_1.png", "btn_big_2.png", CC_CALLBACK_1(BagLayer::chankanCallBack, this));
		//setname->setPosition(visibleSize.width*0.30, visibleSize.height * 0.125);


		//auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(BagLayer::closeButtonCallBack, this));
		//close->setPosition(sssize.width/2 + bagFram->getPositionX(), sssize.height);
		//auto menu = Menu::create(close, chakan,chakan1,setname,nullptr);
		//menu->setPosition(Point::ZERO); 
		//addChild(menu);





		//背包
		MyTableView* tableView = MyTableView::create(tableviewDelegate, Size(700,300));
		tableView->setAnchorPoint(Point::ZERO);
		tableView->setDirection(ScrollView::Direction::HORIZONTAL);
		tableView->setPosition(60,200);
		tableView->setDelegate(tableviewDelegate);
		addChild(tableView);
		tableView->reloadData();



		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(VIPLayer::onTouchBegan, this);
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

void VIPLayer::closeButtonCallBack(Ref*psend)
{
	Director::getInstance()->popScene();
}

void VIPLayer::chankanCallBack(Ref*pesend)
{

}