#include "core/GameGuiLayer.h"
#include "domain/bankrupt/BankruptManager.h"
#include "lobby/FirstPayLayer.h"
#include "domain/logevent/LogEventPageChange.h"
#include "core/showFishLayer.h"
#include "domain/Newbie/NewbieMannger.h"
#include "domain/game/GameManage.h"
#include "domain/bag/BagManager.h"
enum
{
	kZorderMenu = 10,
	kZorderDialog = 20
};


bool GameGuiLayer::init(){
	if ( !Layer::init() )
	{
		return false;
	}
	colorBg = LayerColor::create();
	colorBg->setColor(Color3B::BLACK);
	colorBg->setOpacity(0);
	addChild(colorBg, -1);


	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto menu = Menu::create();
	menu->setPosition(Point::ZERO);
	addChild(menu,kZorderMenu);
	
	Audio::getInstance()->playBGM(GAMEBGM);
	
	auto sprbg = Sprite::create("EarnCoins.png");
	sprbg->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	sprbg->setPosition(visibleSize.width-5, visibleSize.height*0.305);
	addChild(sprbg, 11);

	sEainCoin = MyMenuItemGainMoney::create();
	sEainCoin->setPosition(visibleSize.width + 50, visibleSize.height*0.3);
	menu->addChild(sEainCoin);


	
	sUpgradeTurret = MyMenuItemUpgrade::create();
	sUpgradeTurret->setPosition(visibleSize.width+50, visibleSize.height*0.5);
	menu->addChild(sUpgradeTurret);


	sprbg = Sprite::create("UpgradeButton.png");
	sprbg->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	sprbg->setPosition(visibleSize.width-5,visibleSize.height*0.505);
	addChild(sprbg,11);

	///¶³½á
	auto skillbutton = SkillFreezeButton::createSkillFreezeButton();
	skillbutton->setPosition(visibleSize.width*0.45, visibleSize.height*0.073+7);
	skillbutton->setScale(0.9);
	addChild(skillbutton);
	skillManager::getInstance()->addskillButton(1, skillbutton);
	//ºËµ¯
	auto skillbutton1 = SkillBombButton::createSkillBombButton();
	skillbutton1->setPosition(visibleSize.width*0.03, visibleSize.height*0.48 + 10);
	skillbutton1->setScale(0.7);
	addChild(skillbutton1);
	skillManager::getInstance()->addskillButton(4, skillbutton1);
	//ÕÙ»½
	auto skillbutton2 = SkillSummonButton::createSkillSummonButton();
	skillbutton2->setPosition(visibleSize.width*0.03, visibleSize.height*0.20+10);
	skillbutton2->setScale(0.7);
	addChild(skillbutton2);
	skillManager::getInstance()->addskillButton(3, skillbutton2);
	//À×µç	
	auto skillbutton3 = SkillLightButton::createSkillLightButton();
	skillbutton3->setPosition(visibleSize.width*0.03, visibleSize.height*0.34+10);
	skillbutton3->setScale(0.7);
	addChild(skillbutton3);
	skillManager::getInstance()->addskillButton(5, skillbutton3);
	//Ëø¶¨
	auto skillbutton4 = SkillLockButton::createSkillLockButton();
	skillbutton4->setPosition(visibleSize.width*0.55, visibleSize.height*0.073+7);
	skillbutton4->setScale(0.9);
	addChild(skillbutton4);
	skillManager::getInstance()->addskillButton(2, skillbutton4);

	auto addcoinButton = MenuItemImage::create("huoquCoinBT.png", "huoquCoinBT.png", CC_CALLBACK_1(GameGuiLayer::addCoinCallBack, this));
	addcoinButton->setPosition(910, 397);
	auto addcoinani = Sprite::create("rorateLightCoin.png");
	addcoinani->setPosition(addcoinButton->getPosition()+Point(0,10));
	addChild(addcoinani);
	addcoinani->runAction(RepeatForever::create(RotateBy::create(5, 360)));
	menu->addChild(addcoinButton);


	createSettingBoard();
	showRandonBubbleAni();
	createGuizuGiftLayer();
	if (GameData::getInstance()->getRoomID() > 1)
	{
		beginMaridTaskTime();
	}


	GameData::getInstance()->setisOnGameScene(true);
	scheduleOnce(schedule_selector(GameGuiLayer::playRandVoice), rand() % 4 + 5);
	scheduleUpdate();

	GameData::getInstance()->setisPlayerOneGame(true);

	/*Test fun begin*/
	/*runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create([&]{GameManage::getInstance()->onPlayerUpgrade(); }), nullptr));*/
	/*Test fun end*/
	return true;

}
void GameGuiLayer::refreshSkillNum()
{

}


void GameGuiLayer::createGuizuGiftLayer()
{
	auto b = NobilityManager::getInstance()->isGetRewardToday();
	if (b)
	{
		auto layer = GuizuGiftDialog::create();
		layer->setPosition(0, 0);
		addChild(layer,kZorderDialog);
		
	}
}
void GameGuiLayer::addCoinCallBack(Ref*psend)
{
	if (!User::getInstance()->getIsHaveFirstPay())
	{
		auto layer = FirstPayLayer::create();
		layer->setPosition(Point::ZERO);
		layer->setEventPoint(20);
		addChild(layer, kZorderDialog);
		LogEventPageChange::getInstance()->addEventItems(2, 9, 0);
	}
	else
	{
		auto layer = payLayer::createLayer(1);
		layer->setPosition(Point::ZERO);
		addChild(layer, kZorderDialog);
		layer->setEventPont(1);
		LogEventPageChange::getInstance()->addEventItems(2, 12, 0);
	}
}

void GameGuiLayer::exitCallback(Ref *pSender)
{
	Audio::getInstance()->playSound(CLICKSURE);
	setttingBoard->runAction(Sequence::create(MoveBy::create(0.2, Vec2(0, 70)), CallFunc::create([&]{setttingBoard->setEnabled(true); }), nullptr));
	auto layer = NotarizeExitDialog::create();
	layer->setPosition(0, 0);
	addChild(layer, kZorderDialog);
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
	addChild(menuset,kZorderMenu);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	setttingBoard = MenuItemImage::create("settingBG.png", "settingBG.png", CC_CALLBACK_1(GameGuiLayer::showSettingCallback, this));
	setttingBoard->setPosition(visibleSize.width / 2, visibleSize.height + 15);
	menuset->addChild(setttingBoard);
	auto menu = Menu::create();
	menu->setPosition(Point::ZERO);
	setttingBoard->addChild(menu);
	

	auto exitButton = MenuItemImage::create("exit_1.png", "exit_1.png", CC_CALLBACK_1(GameGuiLayer::exitCallback, this));
	exitButton->setPosition(50, 80);
	menu->addChild(exitButton);

	auto settingButton = MenuItemImage::create("setting_button1.png", "setting_button1.png", CC_CALLBACK_1(GameGuiLayer::settingCallback, this));
	settingButton->setPosition(114, 80);
	menu->addChild(settingButton);

	auto showFishButton = MenuItemImage::create("fish_button1.png", "fish_button1.png", CC_CALLBACK_1(GameGuiLayer::showFishCallback, this));
	showFishButton->setPosition(178, 80);
	menu->addChild(showFishButton);



}

void GameGuiLayer::onExit()
{
	
	Layer::onExit();
	Audio::getInstance()->pauseBGM();


}

void GameGuiLayer::settingCallback(Ref *pSender)
{
	Audio::getInstance()->playSound(CLICKSURE);
	setttingBoard->runAction(Sequence::create(MoveBy::create(0.2, Vec2(0, 70)), CallFunc::create([=]{setttingBoard->setEnabled(true); }), nullptr));
	auto layer = SettingDialog::create();
	layer->setPosition(Point::ZERO);
	addChild(layer,kZorderDialog);
}
void GameGuiLayer::showFishCallback(Ref *pSender)
{
	Audio::getInstance()->playSound(CLICKSURE);
	setttingBoard->runAction(Sequence::create(MoveBy::create(0.2, Vec2(0, 70)), CallFunc::create([=]{setttingBoard->setEnabled(true); }), nullptr));
	auto layer = showFishLayer::create();
	layer->setPosition(Point::ZERO);
	addChild(layer, kZorderDialog);
}
void GameGuiLayer::showSettingCallback(Ref*pSender)//BUG
{
	Audio::getInstance()->playSound(CLICKSURE);
	setttingBoard->setEnabled(false);
	setttingBoard->runAction(MoveBy::create(0.2, Vec2(0, -70)));
	setttingBoard->runAction(Sequence::create(DelayTime::create(5.0f), CallFunc::create([&]
	{
		if (setttingBoard->isEnabled() == false)
		{
			setttingBoard->runAction(Sequence::create(MoveBy::create(0.2, Vec2(0, 70)), CallFunc::create([=]{setttingBoard->setEnabled(true); }),nullptr));
		}
	}),nullptr));
}

void GameGuiLayer::beginMaridTaskTime()
{
	fmaridNowTime = 0;
	GameData::getInstance()->setmermaidTask(MermaidTask::getNewMermaidTask());
	GameData::getInstance()->setIsOnMaridTask(false);
	schedule(schedule_selector(GameGuiLayer::maridTaskTime), 1.0f);
}
void GameGuiLayer::createMermaidTaskPlane()
{
	auto size = Director::getInstance()->getVisibleSize();
	auto sp = Sprite::create("mermaidFrame.png");
	sp->setPosition(-300, size.height*0.5);
	addChild(sp,20);
	auto txt = Sprite::create("TXTmermaid.png");
	txt->setPosition(sp->getContentSize().width*0.6,sp->getContentSize().height/2);
	sp->addChild(txt);
	sp->runAction(Sequence::create(MoveTo::create(0.3, size / 2), DelayTime::create(1.0f), CallFunc::create([=]{txt->runAction(Sequence::create(MoveBy::create(0.3f, Vec2(-800, 0)), CallFunc::create([=]{txt->setPosition(txt->getPositionX() + 1600, txt->getPositionY()); txt->setTexture("TXTmermaidDec.png"); }), MoveBy::create(0.3f, Vec2(-800, 0)), nullptr)); }), DelayTime::create(3.0f),
		 CallFunc::create([=]{txt->removeFromParentAndCleanup(1),sp->setTexture("txt_3.png"); sp->setScale(2); sp->setOpacity(255); }), Spawn::create(ScaleTo::create(0.7, 0.8), FadeOut::create(1), nullptr),
		CallFunc::create([sp]{sp->setTexture("txt_2.png"); sp->setScale(2); sp->setOpacity(255); }), Spawn::create(ScaleTo::create(0.7, 0.8), FadeOut::create(1), nullptr),
		 CallFunc::create([sp]{sp->setTexture("txt_1.png"); sp->setScale(2); sp->setOpacity(255); }), Spawn::create(ScaleTo::create(0.7, 0.8), FadeOut::create(1), nullptr),
		 CallFunc::create([sp]{sp->setTexture("txt_GO.png"); sp->setScale(2); sp->setOpacity(255); }), Spawn::create(ScaleTo::create(0.7, 0.8), FadeOut::create(1), nullptr),
		 CallFunc::create([&]{auto plane = maridTaskPlane::create(); plane->setPosition(-100, 395); plane->runAction(MoveBy::create(0.2f, Vec2(205, 0))); addChild(plane); GameData::getInstance()->setIsOnMaridTask(true); }), nullptr
		)
		);
}

void GameGuiLayer::maridTaskTime(float dt)
{
	if (GameData::getInstance()->getIsOnMaridTask())
	{
		return;
	}
	fmaridNowTime += dt;
	if (fmaridNowTime > GameData::getInstance()->getmermaidTask()->getMermaidTaskConfigInfo().start_wait_time)
	{
		unschedule(schedule_selector(GameGuiLayer::maridTaskTime));
		createMermaidTaskPlane();

	}
}

void GameGuiLayer::playRandVoice(float dt)
{
	Audio::getInstance()->playZhenrenVoice();
	runAction(Sequence::create(DelayTime::create(rand() % 11 + 15), CallFunc::create([=]{playRandVoice(0); }), nullptr));

}

void GameGuiLayer::showLockUpgradeTurret()
{
	sUpgradeTurret->showPopup();
}
void GameGuiLayer::showGainMoneyTurrent()
{
	sEainCoin->showPopup();
}

void GameGuiLayer::onBossWarning(int fishID)
{
	auto Warning = Sprite::create("BossComingRedWarning.png");
	Warning->setPosition(480, 270);
	addChild(Warning, 20);
	auto ac = Sequence::create(FadeOut::create(0.5), FadeIn::create(0.5f), nullptr);
	Warning->runAction(Sequence::create(Repeat::create(ac,5),RemoveSelf::create(),nullptr));
	int imgtype = 1;
	if (fishID==52)
	{
		imgtype = 2;
	}
	auto ac1 = Sequence::create(ScaleTo::create(0.3, 1.0f), ScaleTo::create(0.1, 0.8f), ScaleTo::create(0.1, 1.0f),DelayTime::create(5.0f-0.5f),RemoveSelf::create(),nullptr);
	auto ac2 = ac1->clone();
	auto str = String::createWithFormat("TXTBossComing_%d.png", imgtype);
	auto sp = Sprite::create(str->getCString());
	sp->setPosition(480, 300);
	addChild(sp, 20);
	sp->runAction(ac1);

	str = String::createWithFormat("TXTBossComingDec_%d.png", imgtype);
	sp = Sprite::create(str->getCString());
	sp->setPosition(480, 390);
	addChild(sp, 20);
	sp->runAction(ac2);
}

void GameGuiLayer::ShowUseLockTip(Point dmDropPos)
{
	auto bt = skillManager::getInstance()->getButtonByID(2);

	auto str = String::createWithFormat("item_%d.png", 1004);
	auto itemcell = Sprite::create(str->getCString());
	itemcell->setPosition(dmDropPos);
	itemcell->setScale(0);
	addChild(itemcell, 10);
	auto duration = dmDropPos.distance(bt->getPosition()) / 800.0f;
	itemcell->runAction(Sequence::create(Spawn::create(ScaleTo::create(0.5f, 1.0f), MoveTo::create(0.5f, Vec2(403, 373)), nullptr), EaseSineIn::create(MoveTo::create(1.5f, bt->getPosition())), CallFunc::create([=]{
		bt->runAction(Sequence::createWithTwoActions(ScaleTo::create(0.1, 1.1f), ScaleTo::create(0.1, 0.9f)));
		BagManager::getInstance()->addreward(1004, 1);
	})
		, DelayTime::create(0.5f), CallFunc::create([=]{
		auto tipnode = Node::create();
		tipnode->setPosition(0, 0);

		bt->addChild(tipnode, 5, "tipnode");
		auto sp = Sprite::create("SkillHighLight.png");
		sp->setPosition(bt->getContentSize() / 2);
		sp->setScale(1.0 / 0.9);
		tipnode->addChild(sp, 1);
		sp->runAction(RepeatForever::create(Sequence::create(FadeOut::create(0.5f), FadeIn::create(0.5f), DelayTime::create(0.2f), nullptr)));

		auto sPoint = Sprite::create("yellowSpoint.png");
		sPoint->setPosition(Vec2(0, 80));
		tipnode->addChild(sPoint, 20);
		sPoint->runAction(RepeatForever::create(Sequence::create(EaseSineOut::create(MoveBy::create(0.5f, Vec2(0, 30))), EaseSineOut::create(MoveBy::create(0.5f, Vec2(0, -30))), nullptr)));

		auto tiptxt = Sprite::create("TXTUseLockTip.png");
		tiptxt->setPosition(Vec2(0, 150));
		tipnode->addChild(tiptxt);
		tiptxt->runAction(RepeatForever::create(Sequence::create(FadeOut::create(0.5f), FadeIn::create(0.5f), DelayTime::create(0.2f), nullptr))); 

		colorBg->setOpacity(127);


		tipnode->runAction(Sequence::createWithTwoActions(DelayTime::create(10.0f), CallFunc::create([=]{colorBg->setOpacity(0	), tipnode->removeFromParentAndCleanup(1); })));
	}),

		RemoveSelf::create(), nullptr));

}
void GameGuiLayer::ShowUpgradeTurretTip()
{
	sUpgradeTurret->showPopup();
	auto tipnode = Node::create();
	tipnode->setPosition(0, 0);

	addChild(tipnode, 5, "tipUpGradenode");

	setLayerAlpha(127);
	auto sPoint = Sprite::create("yellowSpoint.png");
	sPoint->setPosition(Vec2(794, 335));
	sPoint->setVisible(false);
	sPoint->runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create([=]{sPoint->setVisible(true); }), nullptr));
	tipnode->addChild(sPoint, 20);
	sPoint->runAction(RepeatForever::create(Sequence::create(EaseSineOut::create(MoveBy::create(0.5f, Vec2(0, 30))), EaseSineOut::create(MoveBy::create(0.5f, Vec2(0, -30))), nullptr)));

	tipnode->runAction(Sequence::create(DelayTime::create(10.0f), CallFunc::create([=]{setLayerAlpha(0); }), RemoveSelf::create(), nullptr));
}
void GameGuiLayer::setLayerAlpha(int alpha)
{
	colorBg->setOpacity(alpha);
}

Vec2 GameGuiLayer::getItemPos(int itemid)
{
	auto skillmanager = skillManager::getInstance();
	switch (itemid)
	{
	case 1003:	
	case 1004:
	case 1005:
	case 1006:
	case 1007:	
		return  skillmanager->getButtonByID(skillmanager->getSkillInfoByitemId(itemid).skill_id)->getPosition();
	default:
		return GameManage::getInstance()->getGameLayer()->GetMyTurret()->getCoinLabelPos();
	}
}

void GameGuiLayer::update(float delta)
{
}