#include "LobbyScene.h"
#include "GameScene.h"
#include"Audio.h"
#include"GameData.h"
#include "SimpleAudioEngine.h"
//#include"SignInLayer.h"
//#include"CallAndroidMethod.h"
#include "GameConfig.h"
Scene* LobbyScene::createScene()
{
	auto scene = Scene::create();

	auto layer = LobbyScene::create();
	scene->addChild(layer);

	return scene;
}

bool LobbyScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	GAMEDATA::getInstance()->gameState = GAMEDATA::Start;
	Audio::getInstance()->prepare();
	if (GAMEDATA::getInstance()->getMusicState()){
		Audio::getInstance()->playBGM();
	}

	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
//            if (!GAMEDATA::getInstance()->getisautobegin())
//            {
//                LogEventOnExit();
//                CallAndroidMethod::getInstance()->quit();
//            }
                exit(0);//quit game
			break;
		}
	};
	EventListenerTouchOneByOne* listener1 = EventListenerTouchOneByOne::create();

	listener1->onTouchBegan = CC_CALLBACK_2(LobbyScene::onTouchBegan, this);
	listener1->onTouchMoved = CC_CALLBACK_2(LobbyScene::onTouchMoved, this);
	listener1->onTouchEnded = CC_CALLBACK_2(LobbyScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);


	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//add game bg to layer
	Sprite* lobby_bg = Sprite::create("lobby_bg.jpg");
	lobby_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(lobby_bg, -1);
	//add start menu to layer
	int val = getDayCnt("PayMonthFlag");
	if (val == 0)
	{
		if (GAMEDATA::getInstance()->getMonthCard()){
			GAMEDATA::getInstance()->setTipNum(GAMEDATA::getInstance()->getTipNum() + 2);
//            CallAndroidMethod::getInstance()->showMonthCardToast();
			addDayCnt("PayMonthFlag");
		}
		
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ||CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	if(GAMEDATA::getInstance()->getLoginTimes()==0){
		GAMEDATA::getInstance()->setLoginTimes(1);
	}else{
//        if (!CallAndroidMethod::getInstance()->isSignToday()&&!GAMEDATA::getInstance()->getisfirsttimegame()){
//                Size visibleSize = Director::getInstance()->getVisibleSize();
//                Node* pause_layer1 = SignInLayer::create();
//                pause_layer1->setPosition(Point::ZERO);
//                this->addChild(pause_layer1, 2);
//        }
	}
#endif

	//add music
	MenuItemImage *open = MenuItemImage::create("open.png", "open.png");
	MenuItemImage *close = MenuItemImage::create("close.png", "close.png");
	if (GAMEDATA::getInstance()->getMusicState()){
		CCMenuItemToggle *close1 = MenuItemToggle::createWithTarget(this, menu_selector(LobbyScene::musicCallback), open, close, NULL);
		close1->setPosition(ccp(-190, -353));
		Menu* itemToggleMenu = Menu::create(close1, NULL);
		this->addChild(itemToggleMenu, 1);
	}
	else{
		MenuItemToggle *close1 = MenuItemToggle::createWithTarget(this, menu_selector(LobbyScene::musicCallback), close, open, NULL);
		close1->setPosition(ccp(-190,-353));
		Menu* itemToggleMenu = Menu::create(close1, NULL);
		this->addChild(itemToggleMenu, 1);
	}

	
	start_btn = MenuItemImage::create("start_game_btn_normal.png", "start_game_btn_clicked.png", CC_CALLBACK_0(LobbyScene::startGame, this));
	
	start_btn->setPosition(visibleSize.width / 2, visibleSize.height * 0.3);
	Menu* start_game = Menu::create();
	start_game->setPosition(Point::ZERO);
	start_btn->retain();
	start_game->addChild(start_btn);
	this->addChild(start_game,1);

	auto scaleani = Sequence::create(ScaleTo::create(0.2, 1.05, 0.95),
			ScaleTo::create(0.2, 0.95, 1.05), ScaleTo::create(0.2, 1.0, 1.0), ScaleTo::create(0.2, 1.05, 0.95), ScaleTo::create(0.2, 0.95, 1.05), ScaleTo::create(0.2, 1.0, 1.0), nullptr);
	//more game btn
	start_btn->runAction(RepeatForever::create(scaleani));
	if (GAMEDATA::getInstance()->openTehui){
//        auto tehui = Menu::create();
//        auto spriteNormal_tehui = Sprite::create("te_hui.png");
//        Rect _rect1 = Rect(spriteNormal_tehui->getPositionX(), spriteNormal_tehui->getPositionY(), spriteNormal_tehui->getContentSize().width, spriteNormal_tehui->getContentSize().height);
//        auto spriteSelected_tehui = Sprite::createWithTexture(spriteNormal_tehui->getTexture(), _rect1, false);
//        spriteSelected_tehui->setScale(1.1);
//        settingBtnOkItem_tehui = MenuItemSprite::create(spriteNormal_tehui, spriteSelected_tehui, nullptr, CC_CALLBACK_0(LobbyScene::payTehui, this));
//        settingBtnOkItem_tehui->setPosition(Point(visibleSize.width * 0.9, visibleSize.height*0.47));
//        tehui->addChild(settingBtnOkItem_tehui);
//        tehui->setPosition(Point(0, 0));
//        this->addChild(tehui);
	}

//    if (GAMEDATA::getInstance()->getisfirsttimegame())
//    {
//        CallAndroidMethod::getInstance()->logevent("IconToGame", "NA", "NA");
//    }

	GameConfig::getInstance()->LoadConfig();
	
	auto state = GAMEDATA::getInstance()->gameState;
	if (state == GAMEDATA::GameState::Start&&!GAMEDATA::getInstance()->getispaythiscount() && !GAMEDATA::getInstance()->getispay())
	{
		this->setKeyboardEnabled(false);
		listener->setEnabled(false);
	}
	

	this->schedule(schedule_selector(LobbyScene::ShowPayPoints), 0.0f);
	this->scheduleUpdate();
//    auto phone = Sprite::create("phonenum.png");
//    phone->setPosition(visibleSize.width / 2, visibleSize.height*0.05);
//    addChild(phone);

	return true;
}

void LobbyScene::showMoreGame(){
	Audio::getInstance()->playBtnEffect();
//    CallAndroidMethod::getInstance()->showMoreGame();
}

void LobbyScene::payTehui(){
	Audio::getInstance()->playBtnEffect();
//    CallAndroidMethod::getInstance()->requestEvent(32);
}

void LobbyScene::startGame(){

	start_btn->stopAllActions();
	start_btn->selected();
	auto scene = GameConfig::getInstance()->getSceneOfChangeStyleByName(GameScene::create(), "StartToGame");
	Director::getInstance()->replaceScene(scene);
	Audio::getInstance()->playBtnEffect();

	GAMEDATA::getInstance()->setisfirsttimegame(false);
	GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Ready;

}


void LobbyScene::music(){


}

void LobbyScene::musicCallback(CCObject* pSender)
{
	Audio::getInstance()->playBtnEffect();
	MenuItemToggle* temp = (MenuItemToggle*)pSender;
	if (GAMEDATA::getInstance()->getMusicState()){
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		GAMEDATA::getInstance()->setMusicState(false);
		GAMEDATA::getInstance()->setSoundState(false);
	}
	else{
		GAMEDATA::getInstance()->setMusicState(true);
		GAMEDATA::getInstance()->setSoundState(true);
		Audio::getInstance()->playBGM();
	}

}


void LobbyScene::ShowAni(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	{
		auto scaleto1 = ScaleTo::create(0.1f, 1.5f, 1.0f);
		auto moveto1 = MoveTo::create(0.1f, Vec2(visibleSize.width *0.45, visibleSize.height * 0.3));
		auto scaleto2 = ScaleTo::create(0.1f, 1.0f, 1.5f);
		auto moveto2 = MoveTo::create(0.1f, Vec2(visibleSize.width *0.55, visibleSize.height * 0.3));
		auto scaleto3 = ScaleTo::create(0.1f, 1.4f, 1.0f);
		auto moveto3 = MoveTo::create(0.1f, Vec2(visibleSize.width *0.50, visibleSize.height * 0.3));
		auto scaleto4 = ScaleTo::create(0.1f, 1.0f, 1.0f);
		start_btn->runAction(Sequence::create(Spawn::create(scaleto1, moveto1, nullptr), Spawn::create(scaleto2, moveto2, nullptr), Spawn::create(scaleto3, moveto3, nullptr), scaleto4, nullptr));
	}
	//特惠礼包
	if (settingBtnOkItem_tehui)
	{
		auto actionUp1 = Sequence::create(ScaleTo::create(0.1, 0.95, 1.05),
		ScaleTo::create(0.1, 1.0, 1.0), ScaleTo::create(0.1, 1.05,0.95), ScaleTo::create(0.1, 1.0, 1.0), nullptr);
		settingBtnOkItem_tehui->runAction(RepeatForever::create(actionUp1));
	}

	//标题
	{
		auto dealy = DelayTime::create(0.6f);
		auto moveto = MoveTo::create(0.12f, Vec2(visibleSize.width / 2, visibleSize.height*0.62));
		auto scaleto1 = ScaleTo::create(0.12f, 0.8f, 1.4f);

		auto scaleto2 = ScaleTo::create(0.08f, 1.4f, 0.8f);

		auto scaleto3 = ScaleTo::create(0.08f, 0.9f, 1.2f);

		auto scaleto4 = ScaleTo::create(0.08f, 1.0f, 1.0f);

		//auto scaleto5 = ScaleTo::create(0.16f, 0.95f, 1.1f);

		auto scaleto6 = ScaleTo::create(0.8f, 1.0f, 1.0f);

		Title->runAction(Sequence::create(dealy, Spawn::create(moveto, scaleto1, nullptr), scaleto2, scaleto3, scaleto4, scaleto6, nullptr));
	}

	ballani(1);

}

void LobbyScene::BallAniCallback(Node* pSender)
{
	pSender->setScale(0.9f, 1.1f);
}


void LobbyScene::onTouchEnded(Touch *touch, Event *event)
{
	CCLOG("x:%f,y:%f", touch->getLocation().x, touch->getLocation().y);
}


void LobbyScene::ShowPayPoints(float dt)
{
	auto state = GAMEDATA::getInstance()->gameState;
	if (state == GAMEDATA::GameState::Start&&!GAMEDATA::getInstance()->getispaythiscount() && !GAMEDATA::getInstance()->getispay())
	{

		GAMEDATA::getInstance()->setispaythiscount(true);
		GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Paying;
//        if (GAMEDATA::getInstance()->getTimes()==0)
//        {
//            CallAndroidMethod::getInstance()->requestEvent(33);
//
//        }
//        else
//        {
//            CallAndroidMethod::getInstance()->requestEvent(36);
//        }

	}

}


void LobbyScene::autobegingame(float dt)
{

	if (GAMEDATA::getInstance()->gameState == GAMEDATA::GameState::Start)
	{
		GAMEDATA::getInstance()->setisautobegin(false);
		startGame();
	}

}
void LobbyScene::update(float delta)
{
	if (GAMEDATA::getInstance()->getisautobegin())
	{

		scheduleOnce(schedule_selector(LobbyScene::autobegingame), 1.0f);
		unscheduleUpdate();
		return;
	}
}


void LobbyScene::LogEventOnExit()
{
	if (GAMEDATA::getInstance()->levelvector.size() > 0)
	{
		String str;
		for (auto k : GAMEDATA::getInstance()->levelvector)
		{
			str.append(String::createWithFormat("%d", k)->getCString());
		}
//        CallAndroidMethod::getInstance()->logevent("Game_quit", str.getCString(), "0");
		GAMEDATA::getInstance()->levelvector.clear();
	}


}

void LobbyScene::ballani(float dt)
{
	{
		auto scaleani = Sequence::create(ScaleTo::create(0.08, 1.1, 0.9),
			ScaleTo::create(0.08, 0.9, 1.1), ScaleTo::create(0.08, 1.0, 1.0), ScaleTo::create(0.08, 1.1, 0.9), ScaleTo::create(0.08, 0.9, 1.1), ScaleTo::create(0.08, 1.0, 1.0)/*, CallFuncN::create(this, callfuncN_selector(LobbyScene::BallAniCallback))*/, nullptr);

		for (int i = 0; i < 5; i++)
		{
			auto node = getChildByTag(i + 20);
			/*node->stopAllActions();*/
			node->runAction(Sequence::create(DelayTime::create(i *0.50), scaleani, nullptr));
		}
	}

}


int  LobbyScene::XygGetToday()
{
	int day = 1900;
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	day += timeinfo->tm_year;
	day = day * 100 + timeinfo->tm_mon + 1;
	day = day * 100 + timeinfo->tm_mday;

	return day;
}


int LobbyScene::getDayCnt(const char* key)
{
	//保存格式为2015031202 20150312为年月日，02为使用次数
	int val = CCUserDefault::sharedUserDefault()->getIntegerForKey(key,0);
	if (val <= 0)
	{
		return 0;
	}

	int day = XygGetToday();
	//不是今天
	if (val / 100 != day)
	{
		return 0;
	}
	else
	{
		return val % 100;
	}
}

void LobbyScene::addDayCnt(const char* key)
{
	int val = getDayCnt(key);
	CCUserDefault::sharedUserDefault()->setIntegerForKey(key, XygGetToday() * 100 + val + 1);
	CCUserDefault::sharedUserDefault()->flush();
}
