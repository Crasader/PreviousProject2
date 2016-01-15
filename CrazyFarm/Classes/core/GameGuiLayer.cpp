#include "core/GameGuiLayer.h"
#include "domain/room/RoomManager.h"
#include "utill/define.h"
#include "utill/SkillButton.h"
#include "utill/AnimationUtil.h"
#include "utill/Audio.h"
#include "lobby/LobbyScene.h"
#include "domain/user/User.h"
#include "domain/skill/SkillFreezeButton.h"
#include "domain/skill/SkillSummonButton.h"
#include "domain/skill/SkillLightButton.h"
#include "domain/skill/SkillLockButton.h"
#include "domain/skill/SkillBombButton.h"
#include "widget/MyMenuItemUpgrade.h"
#include "core/SettingDialog.h"
#include "core/NotarizeExitDialog.h"
#include "domain/nobility/NobilityManager.h"
#include "core/GuizuGiftDialog.h"
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
	
	Audio::getInstance()->playBGM(BACKGORUNDMUSIC);
	
	

	/*auto  buttonPlay1 = MenuItemImage::create("unlockBg.png", "unlockBg.png", CC_CALLBACK_1(GameGuiLayer::ButtentouchEvent, this));
	buttonPlay1->setPosition(visibleSize.width, visibleSize.height*0.40);
	buttonPlay1->setTag(kTagEarnCoins);
	menu->addChild(buttonPlay1);
	auto sprbg1 = Sprite::create("EarnCoins.png");
	sprbg1->setAnchorPoint(Point::ANCHOR_MIDDLE);
	sprbg1->setPosition(buttonPlay1->getContentSize().width *0.3, buttonPlay1->getContentSize().height / 2);
	buttonPlay1->addChild(sprbg1);*/

	
	auto sUpgradeTurret = MyMenuItemUpgrade::create();
	sUpgradeTurret->setPosition(visibleSize.width+40, visibleSize.height*0.60);
	menu->addChild(sUpgradeTurret);


	auto sprbg = Sprite::create("UpgradeButton.png");
	sprbg->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	sprbg->setPosition(visibleSize.width,visibleSize.height*0.61);
	addChild(sprbg,11);






	///����
	auto skillbutton = SkillFreezeButton::createSkillFreezeButton();
	skillbutton->setPosition(visibleSize.width*0.45, visibleSize.height*0.073);
	skillbutton->setScale(0.9);
	addChild(skillbutton);
	//����
	auto skillbutton1 = SkillBombButton::createSkillBombButton();
	skillbutton1->setPosition(visibleSize.width*0.55, visibleSize.height*0.073);
	skillbutton1->setScale(0.9);
	addChild(skillbutton1);
	//�ٻ�
	auto skillbutton2 = SkillSummonButton::createSkillSummonButton();
	skillbutton2->setPosition(visibleSize.width*0.03, visibleSize.height*0.20+10);
	skillbutton2->setScale(0.7);
	addChild(skillbutton2);

	auto skillbutton3 = SkillLightButton::createSkillLightButton();
	skillbutton3->setPosition(visibleSize.width*0.03, visibleSize.height*0.34+10);
	skillbutton3->setScale(0.7);
	addChild(skillbutton3);


	auto skillbutton4 = SkillLockButton::createSkillLockButton();
	skillbutton4->setPosition(visibleSize.width*0.03, visibleSize.height*0.48+10);
	skillbutton4->setScale(0.7);
	addChild(skillbutton4);



	createSettingBoard();
	showRandonBubbleAni();
	createGuizuGiftLayer();
	return true;

}

void GameGuiLayer::createGuizuGiftLayer()
{
	auto b = NobilityManager::getInstance()->isGetRewardToday();
	if (b)
	{
		auto layer = GuizuGiftDialog::create();
		layer->setPosition(0, 0);
		addChild(layer);
	}
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
	setttingBoard->runAction(Sequence::create(MoveBy::create(0.2, Vec2(0, 70)), CallFunc::create([&]{setttingBoard->setEnabled(true); }), nullptr));
	auto layer = NotarizeExitDialog::create();
	layer->setPosition(0, 0);
	addChild(layer);
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


void GameGuiLayer::createUpgradeTurret()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto sp = Sprite::create("UpgradeButton.png");
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	sp->setPosition(visibleSize.width, visibleSize.height*0.60);
	addChild(sp);



	auto menuset = Menu::create();
	menuset->setPosition(Point::ZERO);
	addChild(menuset);
	
	UpgradeTurret = MenuItemImage::create("UnlockFrame_1.png", "UnlockFrame_2.png", CC_CALLBACK_1(GameGuiLayer::showUpgradeTurretgCallback, this));
	UpgradeTurret->setPosition(visibleSize.width, visibleSize.height *0.60);
	menuset->addChild(UpgradeTurret);
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
	exitButton->setPosition(50, 65);
	menu->addChild(exitButton);

	auto settingButton = MenuItemImage::create("setting_button1.png", "setting_button1.png", CC_CALLBACK_1(GameGuiLayer::settingCallback, this));
	settingButton->setPosition(114, 65);
	menu->addChild(settingButton);

	auto showFishButton = MenuItemImage::create("fish_button1.png", "fish_button1.png", CC_CALLBACK_1(GameGuiLayer::showFishCallback, this));
	showFishButton->setPosition(178, 65);
	menu->addChild(showFishButton);




}

void GameGuiLayer::onExit()
{
	Layer::onExit();
	Audio::getInstance()->pauseBGM();
}

void GameGuiLayer::settingCallback(Ref *pSender)
{
	setttingBoard->runAction(Sequence::create(MoveBy::create(0.2, Vec2(0, 70)), CallFunc::create([&]{setttingBoard->setEnabled(true); }), nullptr));
	auto layer = SettingDialog::create();
	layer->setPosition(Point::ZERO);
	addChild(layer);
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

void GameGuiLayer::showUpgradeTurretgCallback(Ref*pSender)
{
	setttingBoard->setEnabled(false);
	setttingBoard->runAction(MoveBy::create(0.2, Vec2(0, -70)));
	setttingBoard->runAction(Sequence::create(DelayTime::create(5.0f), CallFunc::create([&]
	{
		if (setttingBoard->isEnabled() == false)
		{
			setttingBoard->runAction(Sequence::create(MoveBy::create(0.2, Vec2(0, 70)), CallFunc::create([&]{setttingBoard->setEnabled(true); }), nullptr));
		}
	}), nullptr));
}