#include "core/GameGuiLayer.h"
#include "RoomManager.h"
#include "utill/define.h"
#include "utill/SkillButton.h"
#include "utill/AnimationUtil.h"
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
	addChild(menu,10);
	
	auto  buttonPlay = MenuItemImage::create("unlockBg.png", "unlockBg.png", CC_CALLBACK_1(GameGuiLayer::ButtentouchEvent, this));
	buttonPlay->setPosition(visibleSize.width, visibleSize.height*0.60);	
	menu->addChild(buttonPlay);
	auto sprbg = Sprite::create("UpgradeButton.png");
	sprbg->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sprbg->setPosition(buttonPlay->getContentSize().width *0.3, buttonPlay->getContentSize().height*0.52);
	buttonPlay->addChild(sprbg);

	auto  buttonPlay1 = MenuItemImage::create("unlockBg.png", "unlockBg.png", CC_CALLBACK_1(GameGuiLayer::ButtentouchEvent, this));
	buttonPlay1->setPosition(visibleSize.width, visibleSize.height*0.40);
	menu->addChild(buttonPlay1);
	auto sprbg1 = Sprite::create("EarnCoins.png");
	sprbg1->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sprbg1->setPosition(buttonPlay1->getContentSize().width *0.3, buttonPlay1->getContentSize().height / 2);
	buttonPlay1->addChild(sprbg1);

	///¶³½á
	auto skillbutton = SkillButton::createSkillButton(2.0f, "skillStencil.png", "prop_freeze.png", "prop_freeze.png", 9);
	skillbutton->setPosition(visibleSize.width*0.45, visibleSize.height*0.073);
	addChild(skillbutton);
	//Ëø¶¨
	skillbutton = SkillButton::createSkillButton(2.0f, "skillStencil.png", "prop_lock.png", "prop_lock.png", 9);
	skillbutton->setPosition(visibleSize.width*0.55, visibleSize.height*0.073);
	addChild(skillbutton);

	showRandonBubbleAni();
	return true;

}
void GameGuiLayer::ButtentouchEvent(Ref *pSender)
{
	CCLOG("TODO CALLBAK");
}

void GameGuiLayer::showRandonBubbleAni()
{
	CCLOG("SHOW BUBBLE ANI");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto aniNode = Sprite::create();
	aniNode->setPosition(rand() % ((int)(visibleSize.width)), rand() % ((int)(visibleSize.height)));
	addChild(aniNode, 5);
	aniNode->runAction(Sequence::create(AnimationUtil::getInstance()->getAnimate("aniBubble"), RemoveSelf::create(1), nullptr));
	int k = rand() % 30 + 50;
	float nexttime = ((float)k) / 10;
	runAction(Sequence::create(DelayTime::create(nexttime), CallFunc::create(CC_CALLBACK_0(GameGuiLayer::showRandonBubbleAni, this)), nullptr));
}