#include "TwiceSureChangePropDialog.h"
#include "utill/FunUtil.h"
#include "domain/ToolTip/ToolTipMannger.h"
#include "server/HttpMannger.h"
#include "widget/LoadingCircle.h"
#include "domain/bag/BagManager.h"
TwiceSureChangePropDialog*TwiceSureChangePropDialog::createTwiceChangeGiftTip(int itemid,int num)
{
	TwiceSureChangePropDialog*ref = new TwiceSureChangePropDialog();
	if (ref&&ref->init(itemid,num))
	{
		ref->autorelease();
	}
	else
	{
		ref = nullptr;
	}
	return ref;
}





bool TwiceSureChangePropDialog::init(int itemid, int num)
{
	Layer::init();
	bool bRet = false;
	do
	{
		_itemid = itemid;
		_num = num;
		auto colorLayer = LayerColor::create();
		colorLayer->setColor(ccc3(0, 0, 0));
		colorLayer->setOpacity(180);
		colorLayer->setPosition(0, 0);
		addChild(colorLayer, -1);
		auto bg = Sprite::create("TwiceSureDialog.png");
		bg->setPosition(480, 270);
		addChild(bg, 1, "bg");


		auto sure = MenuItemImage::create("btn_queding.png", "btn_queding_2.png", CC_CALLBACK_1(TwiceSureChangePropDialog::sureButtonCallBack, this));
		sure->setPosition(bg->getContentSize().width / 2, 48);

		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(TwiceSureChangePropDialog::closeButtonCallBack, this));
		close->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
		close->setPosition(bg->getContentSize() + Size(10, 10));

		auto menu = Menu::create(sure,close, nullptr);
		menu->setPosition(0, 0);
		bg->addChild(menu);


		auto label = LabelTTF::create("sure to change", "arial", 20);
		label->setColor(Color3B(12, 64, 109));
		label->setAnchorPoint(Point::ANCHOR_MIDDLE);
		label->setDimensions(Size(261, 0));
		label->setPosition(bg->getContentSize().width / 2, 165);
		bg->addChild(label);

		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(TwiceSureChangePropDialog::onTouchBegan, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);


		/////////µ¯³ö¶¯»­
		bg->setScale(0);
		bg->runAction(Sequence::create(ScaleTo::create(0.2f, 1.0f), ScaleTo::create(0.07f, 0.8f), ScaleTo::create(0.07f, 1.0f), nullptr));
		showRandonBubbleAni();
		bRet = true;
	} while (0);


	return bRet;
}

void TwiceSureChangePropDialog::sureButtonCallBack(Ref*psend)
{
	EventListenerCustom* _listener2 = EventListenerCustom::create("change_gift", [=](EventCustom* event){
		changGiftValue*value = static_cast<changGiftValue*>(event->getUserData());
		if (value->_errorcode == 0)
		{
			BagManager::getInstance()->addreward(_itemid, _num);
		}
		else
		{

		}
		ToolTipMannger::showDioag(value->_errormsg);
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("change_gift");
		LoadingCircle::RemoveLoadingCircle();
		removeFromParentAndCleanup(1);

	});
	LoadingCircle::showLoadingCircle();
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listener2, 1);
	if (_itemid==1002)
	{
		HttpMannger::getInstance()->HttpToPostRequestToChangeReward(2,"");
	}
	else if (_itemid == 1006)
	{
		HttpMannger::getInstance()->HttpToPostRequestToChangeReward(3, "");
	}
}

void TwiceSureChangePropDialog::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}
void TwiceSureChangePropDialog::showRandonBubbleAni()
{
	auto node = getChildByName("bg");

	auto aniNode = Sprite::create();
	aniNode->setPosition(20, 100);
	node->addChild(aniNode, 5);
	aniNode->runAction(getForeverAcByNameAndInterval("aniBubble", 0));

	aniNode = Sprite::create();
	aniNode->setPosition(node->getContentSize().width - 20, 100);
	node->addChild(aniNode, 5);
	runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create([=]{aniNode->runAction(getForeverAcByNameAndInterval("aniBubble", 0)); }), nullptr));

}