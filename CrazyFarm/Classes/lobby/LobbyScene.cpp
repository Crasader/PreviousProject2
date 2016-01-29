#include "lobby/LobbyScene.h"
#include "core/GameScene.h"
#include "utill/Chinese.h"
#include "utill/AnimationUtil.h"
#include "domain/user/User.h"
#include "fish/FishRouteData.h"
#include "lobby/bag/bagLayer.h"
#include "fish/FishAniMannage.h"
#include "fish/FishGroupData.h"
#include "server/HttpClientUtill.h"
#include "data/GameData.h"
#include "config/ConfigManager.h"
#include "config/ConfigSign.h"
#include "signlayer/SignInLayer.h"
#include "utill/Toast.h"
#include "viplayer/VipLayer.h"
#include "lobby/shop/paylayer.h"
#include "utill/dayUtil.h"
#include "lobby/ScrollText.h"
#include "lobby/Nobility/NobilityLayer.h"
#include "core/SettingDialog.h"
#include "domain/marquee/MarqueeManager.h"
#include "utill/FunUtil.h"
#include "core/TurnTableDialog.h"
#include "domain/ranklist/RanklistLayer.h"
#include "utill/Audio.h"
#include "lobby/FeedbackLayer.h"
#include "lobby/FirstPayLayer.h"
#include "domain/logevent/LogEventSpcEvent.h"
#include "domain/logevent/LogEventTurrentUpgrade.h"
#include "lobby/roomlayer/RoomLayer.h"
#include "lobby/FeedbackLayer.h"
#include "widget/TwiceSureDialog.h"
#include "widget/LightEffect.h"
#include "utill/CircleMoveToEx.h"
enum 
{
	kZorderMenu = 10,
	kZorderDialog = 20
};
const Vec2 roomPos[5] = { Vec2(-300, 300), Vec2(212, 300), Vec2(500, 300), Vec2(788, 300), Vec2(960+300, 300)};

roomCell * roomCell::createCell(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback)
{
	roomCell *ret = new (std::nothrow) roomCell();
	if (ret && ret->initWithNormalImage(normalImage, selectedImage,"", callback))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}


Scene* LobbyScene::createScene()
{
	auto scene = Scene::create();

	auto layer = LobbyScene::create();

	scene->addChild(layer,0,888);

	return scene;
}

bool LobbyScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
    //add all fish plsit
	//loadResource();
	auto user = User::getInstance();
	auto leveldata = user->getLevelData();


	Audio::getInstance()->playBGM(LOBBYBGM);


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* lobby_bg = Sprite::create("lobbyBG.png");
	lobby_bg->setPosition(visibleSize.width/2,visibleSize.height/2);
	addChild(lobby_bg,-1);

	

	//头像框
	auto spHeadFrame = Sprite::create("HeadFrame.png");
	spHeadFrame->setPosition(visibleSize.width*0.05, visibleSize.height*0.94);
	addChild(spHeadFrame,1,"spHeadFrame");
	

	auto spHead = Sprite::create();
	int sex = rand() % 2;
	if (sex)
	{
		spHead->setTexture("headMan.png");
	}
	else
	{
		spHead->setTexture("headWomen.png");
	}
	spHead->setPosition(23, 30);
	spHeadFrame->addChild(spHead);


	auto userFrame = Sprite::create("coinFrame.png");
	userFrame->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	userFrame->setPosition(spHeadFrame->getPositionX(), spHeadFrame->getPositionY());
	addChild(userFrame);
	auto sssize = userFrame->getContentSize();

	auto userName = LabelTTF::create(user->getUserName(), "arial", 20);
	userName->setAnchorPoint(Point::ANCHOR_MIDDLE);
	userName->setPosition(sssize.width*0.5, sssize.height*0.5);
	userFrame->addChild(userName);

	//等级
	/*auto userlevel = LabelTTF::create(Value(leveldata.levelId).asString().c_str(), "arial", 20);
	userlevel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	userlevel->setPosition(sssize.width*0.245, sssize.height *0.17);
	spHeadFrame->addChild(userlevel);
	*/
	auto viplevelFrame = Sprite::create("viplevelFrame.png");
	viplevelFrame->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	viplevelFrame->setPosition(sssize.width * 1, sssize.height*0.5);
	auto viplevel = LabelAtlas::create(Value(user->getVipLevel()).asString().c_str(), "vipLevelNum.png", 11,16,'0');
	viplevel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	viplevel->setPosition(Vec2(viplevelFrame->getContentSize() / 2));
	viplevelFrame->addChild(viplevel);
	userFrame->addChild(viplevelFrame);

	//经验
	//////////////////////////////////////////////////
	//auto leveldataa = user->getLevelData();
	//auto levelDes = String::createWithFormat("%d:%d", leveldataa.haveExp, leveldataa.passNeedExp);


	//auto exeMur = (leveldataa.haveExp*1.0) / (1.0*leveldataa.passNeedExp);
	//auto exeBarLeft = Sprite::create("exe_left.png");
	//exeBarLeft->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	//exeBarLeft->setPosition(sssize.width*0.33, sssize.height*0.47);
	//spHeadFrame->addChild(exeBarLeft);
	//auto exeBarMid = Sprite::create("exe_mid.png");
	//exeBarMid->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	//exeBarMid->setScaleX(140.0 / exeBarMid->getContentSize().width*exeMur);
	//exeBarMid->setPosition(exeBarLeft->getContentSize().width, exeBarLeft->getContentSize().height / 2);
	//exeBarLeft->addChild(exeBarMid);
	//auto exeBarRight = Sprite::create("exe_right.png");
	//exeBarRight->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	//exeBarRight->setPosition(exeBarMid->getBoundingBox().size.width+exeBarLeft->getContentSize().width/2, exeBarMid->getContentSize().height / 2);
	//exeBarLeft->addChild(exeBarRight);



	//auto exeDescribe = LabelAtlas::create(levelDes->getCString(), "exeNum.png", 12,18,'0');
	//exeDescribe->setAnchorPoint(Point::ANCHOR_MIDDLE);
	//exeDescribe->setPosition(sssize.width*0.63, sssize.height*0.47);
	//spHeadFrame->addChild(exeDescribe);




	//金币
	auto coinFrame = Sprite::create("coinFrame.png");
	coinFrame->setPosition(visibleSize.width*0.39, visibleSize.height*0.94);
	addChild(coinFrame);
	sssize = coinFrame->getContentSize();
	auto coin = Sprite::create("coin.png");
	coin->setAnchorPoint(Point::ANCHOR_MIDDLE);
	coin->setPosition(5, sssize.height *0.5);
	coinFrame->addChild(coin);

	userCoin = LabelTTF::create(Value(user->getCoins()).asString().c_str(), "arial", 20);
	userCoin->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	userCoin->setPosition(sssize.width*0.83, sssize.height *0.5);
	userCoin->setColor(Color3B(254,248,52));
	coinFrame->addChild(userCoin);

	auto addCoin = MenuItemImage::create("addBtn_nor.png", "addBtn_click.png", CC_CALLBACK_1(LobbyScene::payCoinCallback,this));
	addCoin->setAnchorPoint(Point::ANCHOR_MIDDLE);
	addCoin->setPosition(coinFrame->getPositionX() + sssize.width*0.48, coinFrame->getPositionY());

	auto effect = LightEffect::create();
	effect->setPosition(0, 0);
	coin->addChild(effect);
	//钻石
	auto diamondFrame = Sprite::create("coinFrame.png");
	diamondFrame->setPosition(visibleSize.width*0.64, visibleSize.height*0.94);
	addChild(diamondFrame);
	sssize = diamondFrame->getContentSize();
	auto diamond = Sprite::create("diamond1.png");
	diamond->setAnchorPoint(Point::ANCHOR_MIDDLE);
	diamond->setPosition(5, sssize.height *0.5+2);
	diamondFrame->addChild(diamond);

	userdiamond = LabelTTF::create(Value(user->getDiamonds()).asString().c_str(), "arial", 20);
	userdiamond->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	userdiamond->setPosition(sssize.width*0.83, sssize.height *0.5);
	userdiamond->setColor(Color3B(254, 248, 52));
	diamondFrame->addChild(userdiamond);

	auto adddiamond = MenuItemImage::create("addBtn_nor.png", "addBtn_click.png", CC_CALLBACK_1(LobbyScene::payDiamondCallback, this));
	adddiamond->setAnchorPoint(Point::ANCHOR_MIDDLE);
	adddiamond->setPosition(diamondFrame->getPositionX() + sssize.width*0.48, diamondFrame->getPositionY());

	effect = LightEffect::create();
	effect->setPosition(0, 0);
	diamond->addChild(effect);
	




	MarqueeManager::getInstance()->init();

	//背包
	auto bag = MenuItemImage::create("bag.png", "bag.png", CC_CALLBACK_1(LobbyScene::bagButtonCallback, this));
	bag->setPosition(visibleSize.width*0.28, visibleSize.height*0.10);

	//换奖品
	auto changeReward = MenuItemImage::create("changeReward.png", "changeReward.png", CC_CALLBACK_1(LobbyScene::changeRewardCallback, this));
	changeReward->setPosition(visibleSize.width*0.18, visibleSize.height*0.10);

	auto rankList = MenuItemImage::create("ranklist.png", "ranklist.png", CC_CALLBACK_1(LobbyScene::RankListCallback, this));
	rankList->setPosition(visibleSize.width*0.08, visibleSize.height*0.10);


	auto VIP = MenuItemImage::create("VIP.png", "VIP.png", CC_CALLBACK_1(LobbyScene::showVipCallBack, this));
	VIP->setPosition(visibleSize.width*0.038, visibleSize.height*0.77);

	auto sp = Sprite::create();
	sp->setPosition(VIP->getContentSize() / 2);
	VIP->addChild(sp);
	auto lightsp = Sprite::create();
	lightsp->setPosition(22,39);
	VIP->addChild(lightsp,1);

	scheduleOnce([=](float interval)
	{
		sp->runAction(getForeverAcByNameAndInterval("aniVipButton",2.0));
		lightsp->runAction(getForeverAcByNameAndInterval("aniLightPoint", 2.0));

	}, 0.7f, "11");


	auto guizu = MenuItemImage::create("guizu.png", "guizu.png", CC_CALLBACK_1(LobbyScene::guizuCallback, this));
	guizu->setPosition(visibleSize.width*0.038, visibleSize.height*0.62);


	auto sp1 = Sprite::create();
	sp1->setPosition(guizu->getContentSize() / 2);
	guizu->addChild(sp1);
auto 	lightsp1 = Sprite::create();
	
lightsp1->setPosition(22, 39);
guizu->addChild(lightsp1, 1);
	scheduleOnce([=](float interval)
	{
		sp1->runAction(getForeverAcByNameAndInterval("aniGuizu",2.0));
		lightsp1->runAction(getForeverAcByNameAndInterval("aniLightPoint", 2.0));

	}, 0.1f, "111");
	


	auto fistPay = MenuItemImage::create("firstPayGIft.png", "firstPayGIft.png", CC_CALLBACK_1(LobbyScene::FirstPayCallback, this));
	fistPay->setPosition(visibleSize.width*0.038, visibleSize.height*0.47);
	auto sp2 = Sprite::create();
	sp2->setPosition(fistPay->getContentSize() / 2);
	fistPay->addChild(sp2);

	auto lightsp2 = Sprite::create();
	lightsp2->setPosition(22, 39);
	fistPay->addChild(lightsp2, 1);
	scheduleOnce([=](float interval)
	{
		sp2->runAction(getForeverAcByNameAndInterval("aniFirstPay", 2.0));
		lightsp2->runAction(getForeverAcByNameAndInterval("aniLightPoint", 2.0));

	}, 1.1f, "1");

	//快速开始
	auto quickBegin = MenuItemImage::create("quickbegin_1.png", "quickbegin_2.png", CC_CALLBACK_1(LobbyScene::quickBeginCallback, this));
	quickBegin->setPosition(820, 87);

	auto aninode1 = Sprite::create("quickStart2.png");
	aninode1->setPosition(quickBegin->getPosition());
	addChild(aninode1);
	aninode1->runAction(RepeatForever::create(Sequence::create(Spawn::create(FadeIn::create(0.001), ScaleTo::create(0.001, 0), nullptr), Spawn::create(FadeOut::create(3.0), ScaleTo::create(3.0, 1.5), nullptr), nullptr)));
	
	auto aninode2 = Sprite::create();
	aninode2->setPosition(quickBegin->getContentSize()/2);
	quickBegin->addChild(aninode2);
	aninode2->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniraroteLight")));



	if (user->getIsHavePay())
	{
		fistPay->setVisible(false);
	}

	////退出
	auto exitBt = MenuItemImage::create("onExit_1.png", "onExit_2.png", CC_CALLBACK_1(LobbyScene::onExitCallback, this));
	exitBt->setPosition(926, 509);
	//音量

	auto open = MenuItemImage::create("musicon_1.png", "musicon_2.png");
	auto close = MenuItemImage::create("musicoff_1.png", "musicoff_2.png");
	MenuItemToggle *close1;
	if (GameData::getInstance()->getMusicState()){
		close1 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(LobbyScene::onAudioOnOffCallback, this), open, close, nullptr);
		close1->setPosition(ccp(926, 509-74));
	}
	else{
		close1 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(LobbyScene::onAudioOnOffCallback,this), close, open, nullptr);
		close1->setPosition(ccp(926, 509-74));
	}
	//客服
	auto feedbackbt = MenuItemImage::create("kefu_1.png", "kefu_2.png", CC_CALLBACK_1(LobbyScene::feedBackCallback, this));
	feedbackbt->setPosition(926, 509-74-74);


	auto menu = Menu::create(addCoin, adddiamond, bag, guizu, changeReward, quickBegin, rankList, VIP, fistPay, exitBt,close1,feedbackbt,nullptr);
	menu->setPosition(Point::ZERO);
	addChild(menu, kZorderMenu);
	createRoomLayer();
	//添加系统返回键监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			//TODO 展示退出界面
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto listenr1 = EventListenerTouchOneByOne::create();
	listenr1->onTouchBegan = CC_CALLBACK_2(LobbyScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);
	

	this->scheduleOnce(schedule_selector(LobbyScene::showSign), 1.0f);  //签到崩溃

	this->scheduleOnce(schedule_selector(LobbyScene::showMarquee), 1.0f);
	scheduleUpdate();

	//太阳光
	auto sun = Sprite::create("sunAni.png");
	sun->setPosition(480, 535);
	sun->runAction(RepeatForever::create(Sequence::create(Spawn::create(ScaleTo::create(3.0f, 0), FadeOut::create(2.0f), nullptr), DelayTime::create(1.0f), Spawn::create(ScaleTo::create(1.0f, 1), FadeIn::create(1.0f), DelayTime::create(1.0f), nullptr), nullptr)));
	addChild(sun,kZorderMenu);

	auto sunline = Sprite::create("sunlineAni.png");
	sunline->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	sunline->setPosition(sun->getPosition());
	sunline->setScaleX(0.5);
	addChild(sunline);
	sunline->setRotation(45);
	sunline->runAction(RepeatForever::create(Sequence::create( FadeIn::create(2.0f), DelayTime::create(1.0f), FadeOut::create(1.0f), DelayTime::create(1.0f),nullptr)));
	sunline = Sprite::create("sunlineAni.png");
	sunline->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	sunline->setPosition(sun->getPosition());
	addChild(sunline);
	sunline->setScaleX(0.5);
	sunline->setRotation(135);
	sunline->runAction(RepeatForever::create(Sequence::create(FadeIn::create(2.0f), DelayTime::create(1.0f), FadeOut::create(1.0f), DelayTime::create(1.0f), nullptr)));
	


	auto fish1 = Sprite::create();
	fish1->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniLobbyFish1")));
	fish1->setPosition(0, 78);
	fish1->runAction(RepeatForever::create(Sequence::create(MoveBy::create(10, Vec2(1000, 0)), DelayTime::create(10), MoveTo::create(0, Vec2(0, 78)), nullptr)));
	addChild(fish1);

	auto fish2 = Sprite::create();
	fish2->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniLobbyFish2")));
	fish2->setPosition(0, 101);
	fish2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(15, Vec2(1000, 0)), DelayTime::create(5), MoveTo::create(0, Vec2(0, 101)), nullptr)));
	addChild(fish2);

	auto fish3 = Sprite::create();
	fish3->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniLobbyFish3")));
	fish3->setPosition(960, 59);
	fish3->runAction(RepeatForever::create(Sequence::create(MoveBy::create(18, Vec2(-1000, 0)), DelayTime::create(2), MoveTo::create(0, Vec2(960, 59)), nullptr)));
	addChild(fish3);

	langspEmpty = Sprite::create();
	langspEmpty->setPosition(visibleSize.width / 2 + 20, visibleSize.height*0.3 + 20);
	langspEmpty->runAction(RepeatForever::create(/*EaseSineIn::create*/(RotateBy::create(10.0f, 360))));
	addChild(langspEmpty);
	lang = Sprite::create("spindrift.png");
	lang->setPosition(10,10);
	langspEmpty->addChild(lang);
	return true;
}
void LobbyScene::showSign(float dt)
{
	auto seqday = ConfigSign::getInstance()->CalculateTheDayToSign();
	if (seqday == 0)
	{

	}
	else if (seqday == -1)
	{

	}
	else
	{
		auto sign = SignInLayer::createLayer(seqday);
		sign->setPosition(Point::ZERO);
		addChild(sign,kZorderDialog);
	}
}

void LobbyScene::showMarquee(float dt)
{
	auto DisplayBoard = ScrollText::create();
	DisplayBoard->setPosition(498, 463);
	addChild(DisplayBoard, kZorderMenu);

}


void LobbyScene::update(float delta)
{
	lang->setRotation(-langspEmpty->getRotation());
	refreshCoinLabel();
}
void LobbyScene::loadResource(){
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("batch_frame_bullet.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gun_frame.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("batch_frame_net.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gift_frame.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game_scene_frame.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("unlock_cannon_frame.plist");
	///load ani
	AnimationUtil::getInstance()->addAnimationBySpriteName("ani/water/aniWater%d.jpg","aniWater",3.0f,30);
	AnimationUtil::getInstance()->addAnimationBySpriteName("ani/shootFire/aniShoot%d.png", "aniShoot", 0.5f, 5);
	AnimationUtil::getInstance()->addAnimationBySpriteName("ani/bubble/aniBubble%d.png", "aniBubble", 2.0f, 19);
	//load fish ani
	int i = 1;
	for (int i = 1; i < 100; i++)
	{
		auto jsonPath = String::createWithFormat("fish/fish_frame_%d.json", i);
		auto plistPath = String::createWithFormat("fish/fish_frame_%d.plist", i);
		if (!FishAniMannage::getInstance()->loadAniByJsonAndPlist(jsonPath->getCString(),plistPath->getCString()))
		{
		
		}
	}
    
    ConfigManager::getInstance()->LoadConfig();
	
	ConfigSign::getInstance()->LoadConfig();
	FishRouteData::getInstance()->loadConfig();
	FishGroupData::getInstance()->loadConfig();

}


void LobbyScene::createRoomLayer()
{
	auto visibisize = Director::getInstance()->getVisibleSize();
	auto layer = RoomLayer::createLayer();
	layer->setAnchorPoint(Point::ANCHOR_MIDDLE);
	layer->setPosition(visibisize / 2);
	addChild(layer,kZorderMenu-1);
	//auto maxlevl = User::getInstance()->getMaxTurrentLevel();
	//auto k = sortRoomByMaxlevel(maxlevl);
	//auto menu = Menu::create();
	//menu->setPosition(Point::ZERO);
	//addChild(menu);
	//for (size_t i = 0; i < k.size(); i++)
	//{
	//	auto spPath = String::createWithFormat("level_%d.png", k[i].ui_id);
	//	auto cell = roomCell::createCell(spPath->getCString(), spPath->getCString(), CC_CALLBACK_1(LobbyScene::beginGameCallback, this));
	//	cell->setMinEnterLevel(k[i].unlock_turrent_level);
	//	cell->setTag(i+1);
	//	cell->setRoomid(k[i].room_id);
	//	cell->setPosition(roomPos[i+1]);


	//	//加锁和人数
	//	cell->setIslock(false);
	//	auto minLevel = cell->getMinEnterLevel();
	//	auto userLevel = User::getInstance()->getMaxTurrentLevel();
	//	if (userLevel < minLevel)
	//	{
	//		cell->setIslock(true);
	//		cell->setEnabled(false);
	//		auto lock = Sprite::create("lock.png");
	//		lock->setPosition(cell->getContentSize().width*0.2, cell->getContentSize().height*0.8);
	//		cell->addChild(lock);
	//	}
	//	///设置房间人数

	//	int nHour = SystemTime::getNowHour();
	//	int nPlayerNum = ConfigRoom::getInstance()->getPlayerCounts(nHour, cell->getRoomid());
	//	auto sp = Sprite::create("onLinePlayer.png");
	//	sp->setPosition(cell->getContentSize().width*0.4, cell->getContentSize().height*0.14);
	//	cell->addChild(sp,0,"onLinePlayer");
	//	auto label = LabelAtlas::create(Value(nPlayerNum).asString().c_str(), "onLineNum.png", 13, 20, '0');
	//	label->setAnchorPoint(Point::ZERO);
	//	label->setPosition(sp->getContentSize().width, 3);
	//	sp->addChild(label,0,"onLinePlayCount");






	//	roomCells.pushBack(cell);
	//	menu->addChild(cell);


	//	switch (i+1)
	//	{
	//	case 4:
	//		cell->setVisible(false);
	//		break;
	//	case 1:
	//		cell->setEnabled(false);
	//		cell->setScale(0.8);
	//		cell->setColor(Color3B(128, 128, 128));
	//		cell->getChildByName("onLinePlayer")->getChildByName("onLinePlayCount")->setColor(Color3B(128, 128, 128));
	//		break;
	//	case 2:
	//		cell->setScale(1);
	//		cell->setEnabled(true);
	//		cell->setColor(Color3B(255, 255, 255));
	//		cell->getChildByName("onLinePlayer")->getChildByName("onLinePlayCount")->setColor(Color3B(255, 255, 255));
	//		break;
	//	case 3:
	//		cell->setEnabled(false);
	//		cell->setScale(0.8);
	//		cell->setColor(Color3B(128, 128, 128));
	//		cell->getChildByName("onLinePlayer")->getChildByName("onLinePlayCount")->setColor(Color3B(128, 128, 128));
	//		break;
	//	default:
	//		break;
	//	}
	//
	//	

	//}
	//lockTheRoom();

}


void LobbyScene::payCoinCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	auto paylayer = payLayer::createLayer(1);
	paylayer->setPosition(Point::ZERO);
	addChild(paylayer, kZorderDialog);
}
void LobbyScene::payDiamondCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	auto paylayer = payLayer::createLayer(2);
	paylayer->setPosition(Point::ZERO);
	addChild(paylayer, kZorderDialog);
}
void LobbyScene::beginGameCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	auto cell = (roomCell*)psend;
	GameData::getInstance()->setRoomID(cell->getRoomid());
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::create()));
}

void LobbyScene::bagButtonCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	Director::getInstance()->pushScene(BagLayer::createScene());
}

void LobbyScene::changeRewardCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	auto layer = SettingDialog::create();
	layer->setPosition(Point::ZERO);
	addChild(layer, kZorderDialog);
}
void LobbyScene::RankListCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	RanklistManager::getInstance()->loadConfig();
	runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create([&]
	{
		if (RanklistManager::getInstance()->IsSuccess())
		{
			auto layer = RanklistLayer::create();
			layer->setPosition(Point::ZERO);
			addChild(layer, kZorderDialog);
		}
	}), nullptr));
	
}


void LobbyScene::refreshCoinLabel()
{
	auto user = User::getInstance();
	userdiamond->setString(Value(user->getDiamonds()).asString());
	userCoin->setString(Value(user->getCoins()).asString());
}





bool LobbyScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	auto pos = touch->getLocation();
	if (getChildByName("spHeadFrame")->getBoundingBox().containsPoint(pos))
	{
		bagButtonCallback(nullptr);
		return false;
	}
	if (pos.y>100&&pos.y<440)
	{
		if (pos.x>480)
		{
			moveRoomLeft();
		}
		else
		{
			moveRoomRight();
		}
	}
	return false;
}

void LobbyScene::moveRoomLeft()
{
	for (auto cell:roomCells)
	{
		cell->setVisible(true);
		auto tag = cell->getTag();
		if (--tag<1)
		{
			tag = 4;
		}
		cell->setTag(tag);

		
		switch (tag)
		{
		case 4:
			cell->setVisible(false);
			cell->runAction(MoveTo::create(0.1f, roomPos[tag]));
			break;
		case 1:
			cell->setEnabled(false);
			cell->setScale(0.8);
			cell->setColor(Color3B(128, 128, 128));
			cell->runAction(MoveTo::create(0.1f, roomPos[tag]));
			cell->getChildByName("onLinePlayer")->getChildByName("onLinePlayCount")->setColor(Color3B(128, 128, 128));
			break;
		case 2:
			cell->setScale(1);
			if (!cell->getIslock())
			{
				cell->setEnabled(true);
			}
			cell->setColor(Color3B(255,255,255));
			cell->runAction(MoveTo::create(0.1f, roomPos[tag]));
			cell->getChildByName("onLinePlayer")->getChildByName("onLinePlayCount")->setColor(Color3B(255, 255, 255));
			break;
		case 3:
			cell->setPosition(roomPos[4]);
			cell->setEnabled(false);
			cell->setScale(0.8);
			cell->setColor(Color3B(128, 128, 128));
			cell->getChildByName("onLinePlayer")->getChildByName("onLinePlayCount")->setColor(Color3B(128, 128, 128));
			cell->runAction(MoveTo::create(0.1f, roomPos[tag]));
			break;
		default:
			break;
		}
	}
}
void LobbyScene::moveRoomRight()
{

	for (auto cell : roomCells)
	{
		cell->setVisible(true);
		auto tag = cell->getTag();
		if (++tag >4)
		{
			tag = 1;
		}
		cell->setTag(tag);


		switch (tag)
		{
		case 4:
			cell->setVisible(false);
			cell->runAction(MoveTo::create(0.1f, roomPos[tag]));
			break;
		case 1:
			cell->setEnabled(false);
			cell->setScale(0.8);
			cell->setColor(Color3B(128, 128, 128));
			cell->getChildByName("onLinePlayer")->getChildByName("onLinePlayCount")->setColor(Color3B(128, 128, 128));
			cell->runAction(MoveTo::create(0.1f, roomPos[tag]));
			break;
		case 2:
			cell->setScale(1);
			if (!cell->getIslock())
			{
				cell->setEnabled(true);
			}
			cell->setColor(Color3B(255, 255, 255));
			cell->getChildByName("onLinePlayer")->getChildByName("onLinePlayCount")->setColor(Color3B(255, 255, 255));
			cell->runAction(MoveTo::create(0.1f, roomPos[tag]));
			break;
		case 3:
			cell->setPosition(roomPos[4]);
			cell->setEnabled(false);
			cell->setScale(0.8);
			cell->setColor(Color3B(128, 128, 128));
			cell->getChildByName("onLinePlayer")->getChildByName("onLinePlayCount")->setColor(Color3B(128, 128, 128));
			cell->runAction(MoveTo::create(0.1f, roomPos[tag]));
			break;
		default:
			break;
		}
	}
}

void LobbyScene::lockTheRoom()
{
	for (auto cell : roomCells)
	{
		cell->setIslock(false);
		auto minLevel = cell->getMinEnterLevel();
		auto userLevel = User::getInstance()->getMaxTurrentLevel();
		if (userLevel<minLevel)
		{
			cell->setIslock(true);
			cell->setEnabled(false);
			auto lock = Sprite::create("lock.png");
			lock->setPosition(cell->getContentSize().width*0.2, cell->getContentSize().height*0.8);
			cell->addChild(lock);
		}
		///设置房间人数

		int nHour= SystemTime::getNowHour();
		int nPlayerNum = ConfigRoom::getInstance()->getPlayerCounts(nHour, cell->getRoomid());
		auto sp = Sprite::create("onLinePlayer.png");
		sp->setPosition(cell->getContentSize().width*0.4, cell->getContentSize().height*0.15);
		cell->addChild(sp);
		auto label = LabelAtlas::create(Value(nPlayerNum).asString().c_str(), "onLineNum.png", 13, 20, '0');
		label->setAnchorPoint(Point::ZERO);
		label->setPosition(sp->getContentSize().width, 3);
		sp->addChild(label);



	}
}



void LobbyScene::guizuCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	auto guizulayer = NobilityLayer::createLayer();
	guizulayer->setPosition(Point::ZERO);
	addChild(guizulayer, kZorderDialog);
}


void LobbyScene::showVipCallBack(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	auto viplayer = VIPLayer::create();
	/*auto viplayer = FeedbackLayer::create();*/
	viplayer->setPosition(Point::ZERO);
	addChild(viplayer, kZorderDialog);
}
std::vector<Room> LobbyScene::sortRoomByMaxlevel(int maxLevel)
{
	auto roomDatas = ConfigRoom::getInstance()->getRooms();
    ///获得最大可进房间ID
	int i = roomDatas.size()-1;
	for (; i > 0; i--)
	{
		if (roomDatas[i].unlock_turrent_level<=maxLevel)
		{
			break;
		}
	}
	std::vector<Room> curData;
	curData.resize(roomDatas.size());
	int maxRoomId = i;
	int j = 1;
	for (; j < curData.size(); j++)
	{
		curData[j] = roomDatas[i];
		i++;
		if (i >=roomDatas.size())
		{
			break;
		}
	}
	int k = 0;
	for (; k < maxRoomId-1; k++)
	{
		j++;
		curData[j] = roomDatas[k];
		
	}
	if (k == 0)
	{
		k = roomDatas.size() - 1;
	}
	curData[0] = roomDatas[k];

	return curData;
}

void LobbyScene::quickBeginCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	auto maxLevel = User::getInstance()->getMaxTurrentLevel();
	auto roomDatas = ConfigRoom::getInstance()->getRooms();
	///获得最大可进房间ID
	int i = roomDatas.size() - 1;
	for (; i > 0; i--)
	{
		if (roomDatas[i].unlock_turrent_level <= maxLevel)
		{
			break;
		}
	}

	GameData::getInstance()->setRoomID(roomDatas.at(i).room_id);
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::create()));
}

void LobbyScene::FirstPayCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	auto layer = FirstPayLayer::create();
	layer->setPosition(0, 0);
	addChild(layer, kZorderDialog);
}
void LobbyScene::onExitSureCallback(Ref*psend)
{
	quickBeginCallback(nullptr);
}
void LobbyScene::endGameCallback(Ref*psend)
{
	Director::getInstance()->end();
}
void LobbyScene::onExitCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	auto isPlay = GameData::getInstance()->getisPlayerOneGame();
	if (isPlay)
	{
		auto str = ChineseWord("onExitTip3");
		auto dioag = TwiceSureDialog::createDialog(str.c_str(), CC_CALLBACK_1(LobbyScene::endGameCallback, this));
		dioag->setPosition(0, 0);
		addChild(dioag,kZorderDialog);
	}
	else
	{
		auto str = ChineseWord("onExitTip1");
		auto dioag = TwiceSureDialog::createDialog(str.c_str(), CC_CALLBACK_1(LobbyScene::onExitSureCallback, this));
		dioag->setPosition(0, 0);
		dioag->setCloseButtonCallback(CC_CALLBACK_1(LobbyScene::endGameCallback, this));
		addChild(dioag,kZorderDialog);
	}


	
}
void LobbyScene::onAudioOnOffCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	MenuItemToggle* temp = (MenuItemToggle*)psend;
	if (GameData::getInstance()->getMusicState()){
		Audio::getInstance()->pauseBGM();
		GameData::getInstance()->setMusicState(false);
		GameData::getInstance()->setSoundState(false);
	}
	else{
		GameData::getInstance()->setMusicState(true);
		GameData::getInstance()->setSoundState(true);
		Audio::getInstance()->playBGM(LOBBYBGM);
	}
}
void LobbyScene::feedBackCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	auto layer = FeedbackLayer::create();
	layer->setPosition(Point::ZERO);
	addChild(layer,kZorderDialog);
}