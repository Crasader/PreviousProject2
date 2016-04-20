#include "EmailLayer.h"
#include "EmailManager.h"
#include "utill/Audio.h"
#include "EmailContent.h"
#include "utill/Chinese.h"

bool EmailLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	bool bRet = false;
	do 
	{
		auto colorLayer = LayerColor::create();
		colorLayer->setColor(ccc3(0, 0, 0));
		colorLayer->setOpacity(180);
		colorLayer->setPosition(0, 0);
		addChild(colorLayer, -1);

	
		_EmailViewDelegate = new EmailView();
		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto bg = Sprite::create("EmailBg.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg,0,"bg");

		auto tip = Label::create(ChineseWord("EmailSave30").c_str(), "arial", 16);
		tip->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		tip->setPosition(46, 445);
		bg->addChild(tip);
		tip->setColor(Color3B::RED);

		//tableview
		tableView = MyTableView::create(_EmailViewDelegate, Size(355, 330));
		tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
		tableView->setDirection(ScrollView::Direction::VERTICAL);
		tableView->setPosition(38,90);
		tableView->setDelegate(_EmailViewDelegate);
		bg->addChild(tableView);
		tableView->reloadData();

	
		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(EmailLayer::onTouchBegan, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);


		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(EmailLayer::closeButtonCallBack, this));
		close->setPosition(bg->getContentSize()+Size(10,10));
		close->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);

		auto allRead = MenuItemImage::create("AllRead_1.png", "AllRead_2.png", CC_CALLBACK_1(EmailLayer::allReadCallBack, this));
		allRead->setPosition(299, 47);


		
		auto menu = Menu::create(close, allRead,nullptr);
		menu->setPosition(Point::ZERO);
		bg->addChild(menu);
	
		EmailManager::getInstance()->setEmaiLayer(this);
		bRet = true;
	} while (0);
	

	return bRet;
}
void EmailLayer::showContent(int emailid)
{
	auto bg = getChildByName("bg");
	auto item = EmailManager::getInstance()->getEmailItemById(emailid);
	if (item.mailbox_id!=-1)
	{
		auto node = bg->getChildByName("EmailContent");
		if (node)
		{
			node->removeFromParentAndCleanup(1);
		}
		auto sp = EmailContent::create(item);
		sp->setPosition(552, bg->getContentSize().height / 2-9);
		bg->addChild(sp);
		sp->setName("EmailContent");
	}
	tableView->reloadData();
}
void EmailLayer::closeButtonCallBack(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	removeFromParentAndCleanup(1);
	EmailManager::getInstance()->setEmaiLayer(nullptr);
}

void EmailLayer::allReadCallBack(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	EmailManager::getInstance()->SendToGetRequestAll();
}