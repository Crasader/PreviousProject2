#include "RedPackCell.h"
#include "RedPackLayer.h"
#include "domain/user/User.h"
#include "utill/Audio.h"



bool RedPackLayer::init()
{
	if ( !Layer::init() )
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

		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto bg = Sprite::create("redPackBg.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg,0,"bg");

		float startx = 136;
		float diffx = 237;
		for (int i = 1; i <= 3;i++)
		{
			auto cell = RedPackCell::create(i);
			cell->setPosition(startx, bg->getContentSize().height / 2-20);
			startx += diffx;
			bg->addChild(cell);
		}


		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(RedPackLayer::closeButtonCallBack, this));
		close->setPosition(bg->getContentSize()-Size(0,30));
		close->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);

		
		auto menu = Menu::create(close,nullptr);
		menu->setPosition(Point::ZERO);
		bg->addChild(menu);


		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(RedPackLayer::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(RedPackLayer::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(RedPackLayer::onTouchEnded, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	
		bRet = true;
	} while (0);
	

	return bRet;
}

void RedPackLayer::closeButtonCallBack(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	removeFromParentAndCleanup(1);
}
