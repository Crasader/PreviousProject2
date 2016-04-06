#include "lobby/bag/ShowBoxLayer.h"
#include "domain/user/User.h"
#include "lobby/bag/BagCell.h"
#include "domain/bag/BagManager.h"
#include "utill/FunUtil.h"
#include "domain/skill/skillManager.h"
#include "lobby/viplayer/VipLayer.h"
#include "domain/coinBox/CoinBox.h"
#include "lobby/bag/bagLayer.h"
#include "config/ConfigChest.h"
#include "domain/ToolTip/TwiceSureDialog.h"
#include "server/HttpMannger.h"
ShowBoxLayer*ShowBoxLayer::create(int itemid)
{
	ShowBoxLayer *pRet = new ShowBoxLayer();
	if (pRet && pRet->init(itemid))
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

bool ShowBoxLayer::init(int itemid)
{
	if ( !Layer::init() )
	{
		return false;
	}
	bool bRet = false;
	do 
	{
		m_itemId = itemid;
		auto layer = LayerColor::create();
		layer->setColor(Color3B::BLACK);
		layer->setOpacity(128);
		addChild(layer,-1);
		auto size = Director::getInstance()->getVisibleSize();
		auto bg = Sprite::create("showItemBg.png");
		bg->setPosition(size / 2);
		addChild(bg);

		BagItem item;
		item.itemId = itemid;
		item.type = Prop_ItemBox;
		item.num = BagManager::getInstance()->getItemNum(itemid);
		auto cell = BagCell::create();
		cell->setValue(item);
		cell->setPosition(480, 373);
		addChild(cell);
		
		Iitem = ConfigItem::getInstance()->getItemById(itemid);
		auto label = LabelTTF::create(Iitem.itemName.c_str(), "arial", 20);
		label->setPosition(480, 300);
		label->setAnchorPoint(Point::ANCHOR_MIDDLE);
		addChild(label);
		if (itemid == 1008)
		{

			auto label1 = LabelTTF::create(ChineseWord("coinBox").c_str(), "arail", 18);
			label1->setColor(Color3B::YELLOW);
			label1->setPosition(480, 200);
			label1->setAnchorPoint(Point::ANCHOR_MIDDLE);
			addChild(label1);
		}
		else
		{

			auto lv = User::getInstance()->getUserBoxLevel();
			auto box = ConfigChest::getInstance()->getChestByItemId(m_itemId);
			if (lv < box.chest_level)
			{
				auto chineseKey = String::createWithFormat("TXTBox_%d", m_itemId);
				auto str3 = String::createWithFormat(ChineseWord(chineseKey->getCString()).c_str(), CoinBox::getInstance()->getBoxConfigInfoByItemID(m_itemId).catch_fish_per);
				auto label3 = LabelTTF::create(str3->getCString(), "arail", 18);
				label3->setColor(Color3B::YELLOW);
				label3->setPosition(480, 200);
				label3->setAnchorPoint(Point::ANCHOR_MIDDLE);
				addChild(label3);
			}
			else
			{
				auto str2 = String::createWithFormat(ChineseWord("nextBox").c_str(), CoinBox::getInstance()->getBoxConfigInfoByItemID(m_itemId).money);
				auto label2 = LabelTTF::create(str2->getCString(), "arail", 18);
				label2->setColor(Color3B::YELLOW);
				label2->setPosition(480, 200);
				label2->setAnchorPoint(Point::ANCHOR_MIDDLE);
				addChild(label2);
			}
	
			
		}
		
			auto BtBuy = MenuItemImage::create("btn_shiyong_1.png", "btn_shiyong_2.png", CC_CALLBACK_1(ShowBoxLayer::quedingcallback, this));
		BtBuy->setPosition(480,80);
		BtBuy->setName("surebt");
		auto BtSend = MenuItemImage::create("btn_zengsong_1.png", "btn_zengsong_2.png", CC_CALLBACK_1(ShowBoxLayer::quedingcallback, this));
		BtSend->setPosition(480-90, 80);


		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(ShowBoxLayer::closeButtonCallBack, this));
		close->setPosition(644,470);



		auto menu = Menu::create(BtBuy, close, nullptr);
		menu->setPosition(0, 0);
		addChild(menu,0,"menu");

		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(ShowBoxLayer::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(ShowBoxLayer::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(ShowBoxLayer::onTouchEnded, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	//����ϵͳ���ؼ�����
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			
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
bool ShowBoxLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

void ShowBoxLayer::quedingcallback(Ref*psend)
{
	((MenuItem*)psend)->setEnabled(false);
	if (m_itemId ==1008)
	{
		User::getInstance()->addCoins(CoinBox::getInstance()->getPerCoinBox());
		BagManager::getInstance()->changeItemCount(m_itemId, -1);
		((BagLayer*)getParent())->gettableview()->reloadData();
		removeFromParentAndCleanup(1);
	}
	else
	{
		HttpMannger::getInstance()->HttpToPostRequestOpenBox(m_itemId);
		LoadingCircle::showLoadingCircle();
		NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(ShowBoxLayer::httpCallback), "openBox", NULL);
	}
	
	
}

void ShowBoxLayer::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}

void ShowBoxLayer::httpCallback(Ref*psend)
{
	LoadingCircle::RemoveLoadingCircle();
	OpenBoxValue *value = (OpenBoxValue*)psend;
	TwiceSureDialog*dialog;
	switch (value->_errorcode)
	{
	case 0:
		BagManager::getInstance()->changeItemCount(m_itemId, -1);
		User::getInstance()->addCoins(value->_reward_coins);
		User::getInstance()->setUserBoxLevel(value->_chestLevel);
		if (value->_reward_coins > 0)
		{
			auto str = String::createWithFormat(ChineseWord("getXXcoin").c_str(), value->_reward_coins);
			dialog = TwiceSureDialog::createDialog(str->getCString());
		}
		else
		{
			auto str = String::createWithFormat("upgrade chest lv to %d", value->_chestLevel);
			dialog = TwiceSureDialog::createDialog(str->getCString());
		}
		break;
	case 404:
		dialog = TwiceSureDialog::createDialog("time out");
		break;
	default:
		dialog = TwiceSureDialog::createDialog(value->_errormsg.c_str());
		break;
	}
	dialog->setPosition(0, 0);
	getParent()->addChild(dialog, 30);
	NotificationCenter::getInstance()->removeObserver(this, "openBox");
	((BagLayer*)getParent())->gettableview()->reloadData();
	removeFromParentAndCleanup(true);
	
}