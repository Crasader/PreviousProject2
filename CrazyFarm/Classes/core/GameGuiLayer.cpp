#include "core/GameGuiLayer.h"
#include "RoomManager.h"
#include "utill/define.h"
#include "utill/SkillButton.h"
#include "utill/AnimationUtil.h"
#include "lobby/LobbyScene.h"
#include "User.h"
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
	buttonPlay->setTag(kTagUpgradeTurret);
	menu->addChild(buttonPlay);
	auto sprbg = Sprite::create("UpgradeButton.png");
	sprbg->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sprbg->setPosition(buttonPlay->getContentSize().width *0.3, buttonPlay->getContentSize().height*0.52);
	buttonPlay->addChild(sprbg);

	auto  buttonPlay1 = MenuItemImage::create("unlockBg.png", "unlockBg.png", CC_CALLBACK_1(GameGuiLayer::ButtentouchEvent, this));
	buttonPlay1->setPosition(visibleSize.width, visibleSize.height*0.40);
	buttonPlay1->setTag(kTagEarnCoins);
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




	createSettingBoard();
	showRandonBubbleAni();
	return true;

}
void GameGuiLayer::ButtentouchEvent(Ref *pSender)
{
	auto node = (Node*)pSender;
	switch (node->getTag())
	{
		case kTagUpgradeTurret:
			User::getInstance()->setMaxTurrentLevel(User::getInstance()->getMaxTurrentLevel() + 1);
			break;
		case  kTagEarnCoins:
			User::getInstance()->addCoins(1000);
			break;
	default:
		break;
	}

	CCLOG("TODO CALLBAK");
}
void GameGuiLayer::exitCallback(Ref *pSender)
{
	Director::getInstance()->replaceScene(LobbyScene::createScene());
}

void GameGuiLayer::showRandonBubbleAni()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto aniNode = Sprite::create();
	aniNode->setPosition(rand() % ((int)(visibleSize.width)), rand() % ((int)(visibleSize.height/2)));
	addChild(aniNode, 5);
	aniNode->runAction(Sequence::create(AnimationUtil::getInstance()->getAnimate("aniBubble"), RemoveSelf::create(1), nullptr));
	int k = rand() % 30 + 50;
	float nexttime = ((float)k) / 10;
	runAction(Sequence::create(DelayTime::create(nexttime), CallFunc::create(CC_CALLBACK_0(GameGuiLayer::showRandonBubbleAni, this)), nullptr));
}


void GameGuiLayer::createSettingBoard()
{
	auto menuset = Menu::create();
	menuset->setPosition(Point::ZERO);
	addChild(menuset);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	setttingBoard = MenuItemImage::create("settingBG.png", "settingBG.png", CC_CALLBACK_1(GameGuiLayer::showSettingCallback, this));
	setttingBoard->setPosition(visibleSize.width / 2, visibleSize.height + 20);
	menuset->addChild(setttingBoard);
	auto menu = Menu::create();
	menu->setPosition(Point::ZERO);
	setttingBoard->addChild(menu);
	

	auto exitButton = MenuItemImage::create("exit_1.png", "exit_1.png", CC_CALLBACK_1(GameGuiLayer::exitCallback, this));
	exitButton->setPosition(50,65);
	menu->addChild(exitButton);

	auto settingButton = MenuItemImage::create("setting_button1.png", "setting_button1.png", CC_CALLBACK_1(GameGuiLayer::settingCallback, this));
	settingButton->setPosition(114, 65);
	menu->addChild(settingButton);

	auto showFishButton = MenuItemImage::create("fish_button1.png", "fish_button1.png", CC_CALLBACK_1(GameGuiLayer::showFishCallback, this));
	showFishButton->setPosition(178, 65);
	menu->addChild(showFishButton);
	
	


}


void GameGuiLayer::settingCallback(Ref *pSender)
{
	;
}
void GameGuiLayer::showFishCallback(Ref *pSender)
{

}
void GameGuiLayer::showSettingCallback(Ref*pSender)
{
	setttingBoard->setEnabled(false);
	setttingBoard->runAction(MoveBy::create(0.2, Vec2(0, -70)));
	setttingBoard->runAction(Sequence::create(DelayTime::create(5.0f), CallFunc::create([&]
	{
		if (setttingBoard->isEnabled() == false)
		{
			setttingBoard->runAction(Sequence::create(MoveBy::create(0.2, Vec2(0, 70)), CallFunc::create([&]{setttingBoard->setEnabled(true); }),nullptr));
		}
	}),nullptr));
}