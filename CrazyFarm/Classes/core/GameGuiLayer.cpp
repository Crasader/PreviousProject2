#include "core/GameGuiLayer.h"
#include "RoomManager.h"
#include "utill/define.h"


enum 
{
	kTagUpgradeTurret = 1,
	kTagEarnCoins = 2
};




skillCell* skillCell::create(char* spName, int propNum)
{
	auto cell = new skillCell();
	if (cell&&cell->init(spName,propNum))
	{
		cell->autorelease();
		return cell;
	}
	else
	{
		cell = nullptr;
		return cell;
	}
}

bool skillCell::init(char* spName, int propNum)
{
	return true;
}


bool GameGuiLayer::init(){
	if ( !Layer::init() )
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto menu = Menu::create();
	menu->setPosition(Point::ZERO);
	addChild(menu);
	auto sprbg = Sprite::create("unlockBg.png");
	sprbg->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	sprbg->setPosition(visibleSize.width, visibleSize.height*0.45);
	addChild(sprbg);

	auto  buttonPlay = MenuItemImage::create("UpgradeButton.png", "UpgradeButton.png", CC_CALLBACK_1(GameGuiLayer::ButtentouchEvent, this));
	buttonPlay->setPosition(sprbg->getPosition());
	menu->addChild(buttonPlay);

	auto sprbg1 = Sprite::create("unlockBg.png");
	sprbg1->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	sprbg1->setPosition(visibleSize.width, visibleSize.height*0.45);
	addChild(sprbg1);

	auto buttonPlay1 = MenuItemImage::create("EarnCoins.png", "EarnCoins.png", CC_CALLBACK_1(GameGuiLayer::ButtentouchEvent, this));
	buttonPlay1->setPosition(sprbg1->getPosition());
	menu->addChild(buttonPlay1);
	return true;
}
void GameGuiLayer::ButtentouchEvent(Ref *pSender)
{

}
