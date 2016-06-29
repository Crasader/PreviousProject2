#include "BasePayLayer.h"
#include "PxPayMannger.h"
BasePayLayer* BasePayLayer::create(std::vector<ImageElement> items)
{
	BasePayLayer *pRet = new(std::nothrow) BasePayLayer();
	if (pRet && pRet->init(items))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}
bool BasePayLayer::init(std::vector<ImageElement> items)
{
	if (!Layer::init())
	{
		return false;
	}
	this->setAnchorPoint(Vec2(0, 1.0f));

	PayUiConfig::getInstance()->LoadConfig();
	visisize = Director::getInstance()->getVisibleSize();
	auto Uiconfig = items;
	auto oriPath = "pui/";
	auto menu = Menu::create();
	for (auto elenmt: Uiconfig)
	{
        if (elenmt.type == "image")
        {
			auto sprite = Sprite::create(oriPath + elenmt.defaultname);
			auto size = sprite->getContentSize();
			sprite->setAnchorPoint(Point(0,1));
			sprite->setScaleX(elenmt.width / size.width);
			sprite->setScaleY(elenmt.height / size.height);
			sprite->setPosition(Director::getInstance()->convertToUI(Vec2(elenmt.xx, elenmt.yy)));
			addChild(sprite);
			
        }
		else if (elenmt.type == "confirmbutton")
		{
			auto button = Button::create(oriPath + elenmt.defaultname, oriPath + elenmt.specialname);
			auto size = button->getContentSize();
			button->setPosition(Director::getInstance()->convertToUI(Vec2(elenmt.xx, elenmt.yy)));
			button->setAnchorPoint(Point(0, 1));
			button->setScaleX(elenmt.width / size.width);
			button->setScaleY(elenmt.height / size.height);
			button->addTouchEventListener(CC_CALLBACK_2(BasePayLayer::quedingButton, this));
			button->setName("confirmbutton");
			addChild(button);
		}
		else if (elenmt.type == "cancelbutton")
		{
			auto button = Button::create(oriPath + elenmt.defaultname, oriPath + elenmt.specialname);
			auto size = button->getContentSize();
			button->setPosition(Director::getInstance()->convertToUI(Vec2(elenmt.xx, elenmt.yy)));
			button->setAnchorPoint(Point(0, 1));
			button->setScaleX(elenmt.width / size.width);
			button->setScaleY(elenmt.height / size.height);
			button->addTouchEventListener(CC_CALLBACK_2(BasePayLayer::quxiaoButton, this));
			button->setName("cancelbutton");
			addChild(button);
		}
	}





	//´¥ÃþÆÁ±Î
	auto listenr1 = EventListenerTouchOneByOne::create();
	listenr1->onTouchBegan = [=](Touch*touch, Event*event){return true; };
	listenr1->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);
	return true;
}



void BasePayLayer::quedingButton(Ref* psender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
    {
		PxPayMannger::getInstance()->requestEvent(_eventid);
		removeFromParentAndCleanup(1);
    }
	
}
void BasePayLayer::quxiaoButton(Ref* psender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		PxPayMannger::getInstance()->cancelEvent(_eventid);
		removeFromParentAndCleanup(1);
	}
	
}
