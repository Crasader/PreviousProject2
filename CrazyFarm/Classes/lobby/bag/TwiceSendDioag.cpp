#include "TwiceSendDioag.h"
#include "utill/Audio.h"
#include "utill/Chinese.h"
#include "server/HttpMannger.h"
#include "domain/ToolTip/ToolTipMannger.h"
#include "domain/bag/BagManager.h"
TwiceSendDioag*TwiceSendDioag::createTwiceSendDioag(int itemid,int itemnum)
{
	TwiceSendDioag*ref = new TwiceSendDioag();
	if (ref&&ref->init(itemid,itemnum))
	{
		ref->autorelease();
	}
	else
	{
		ref = nullptr;
	}
	return ref;
}





bool TwiceSendDioag::init(int itemid,int itemidnum)
{
	BaseLayer::init();
	bool bRet = false;
	do 
	{
		
		auto bg = Sprite::create("TwiceSureDialog.png");
		bg->setPosition(480, 270);
		addChild(bg, -1);
		
		m_itemid = itemid;


		auto spPath = String::createWithFormat("item_%d.png", itemid);
		auto sp = Sprite::create(spPath->getCString());
		sp->setPosition(86, 182);
		sp->setScale(0.8);
		bg->addChild(sp);
		//道具名称
		auto str = String::createWithFormat("propName_%d", m_itemid);
		auto label = LabelTTF::create(ChineseWord(str->getCString()).c_str(), "arial", 20);
		label->setColor(Color3B(12, 64, 109));
		label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		label->setPosition(141, 195);
		bg->addChild(label);
		//赠送数量	
		str = String::createWithFormat(ChineseWord("sendPropNum").c_str(),itemidnum);
		label = LabelTTF::create(str->getCString(), "arial", 20);
		label->setColor(Color3B(12, 64, 109));
		label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		label->setPosition(141, 165);
		bg->addChild(label);

		
		auto frame = Sprite::create("RegisterInputFrame.png");
		frame->setPosition(Vec2(bg->getContentSize().width / 2, 100));
		frame->setScaleX(0.8);
		bg->addChild(frame);

		_editRepeatword = ui::EditBox::create(Size(210, 51), ui::Scale9Sprite::create());
		_editRepeatword->setPosition(Vec2(bg->getContentSize().width / 2, 100));
		_editRepeatword->setFontName("Arial");
		_editRepeatword->setFontSize(20);
		_editRepeatword->setFontColor(Color3B::WHITE);
		_editRepeatword->setPlaceHolder(ChineseWord("cinYourSendName").c_str());
		_editRepeatword->setPlaceholderFontColor(Color3B::GRAY);
		_editRepeatword->setPlaceholderFontSize(25);
		_editRepeatword->setMaxLength(14);
		_editRepeatword->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
		_editRepeatword->setDelegate(this);
		bg->addChild(_editRepeatword);



		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(TwiceSendDioag::closeButtonCallBack, this));
		close->setPosition(bg->getContentSize());

		auto sure = MenuItemImage::create("btn_goumai_1.png", "btn_goumai_2.png", CC_CALLBACK_1(TwiceSendDioag::sureButtonCallBack, this));
		sure->setPosition(bg->getContentSize().width / 2, 40);

		auto menu = Menu::create(close, sure, nullptr);
		menu->setPosition(bg->getPosition() - bg->getContentSize() / 2);
		addChild(menu);





		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(TwiceSendDioag::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(TwiceSendDioag::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(TwiceSendDioag::onTouchEnded, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, bg);


		bRet = true;
	} while (0);
	

	return bRet;
}



void TwiceSendDioag::sureButtonCallBack(Ref*send)
{


	auto listen = EventListenerCustom::create("get_sendPresent", [=](EventCustom*event)
	{
		SendPresentValue *value = (SendPresentValue*)(event->getUserData());
		if (value->_errorcode==0)
		{
			ToolTipMannger::showDioag("send scuess");
			BagManager::getInstance()->addreward(value->rewards._itemid, -value->rewards._num);
		}
		else
		{
			ToolTipMannger::showDioag(value->_errormsg);
		}

		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("get_sendPresent");
		removeFromParentAndCleanup(true);

	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listen, 1);
	HttpMannger::getInstance()->HttpToPostRequestSendPresent(m_itemid,_editRepeatword->getText());

}

void TwiceSendDioag::closeButtonCallBack(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	removeFromParentAndCleanup(true);
}

void TwiceSendDioag::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
	log("editBox %p DidBegin !", editBox);
}

void TwiceSendDioag::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{
	log("editBox %p DidEnd !", editBox);
}

void TwiceSendDioag::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
	log("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void TwiceSendDioag::editBoxReturn(ui::EditBox* editBox)
{
	auto str = String::createWithFormat("%s", editBox->getText());
	editBox->setText(str->getCString());
	log("editBox %p was returned !", editBox);

}
