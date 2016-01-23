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





	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* lobby_bg = Sprite::create("lobbyBG.png");
	lobby_bg->setPosition(visibleSize.width/2,visibleSize.height/2);
	addChild(lobby_bg,-1);

	

	//头像框
	auto spHeadFrame = Sprite::create("HeadFrame.png");
	spHeadFrame->setPosition(visibleSize.width*0.14, visibleSize.height*0.9);
	addChild(spHeadFrame);
	auto sssize = spHeadFrame->getContentSize();

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
	spHead->setPosition(sssize.width*0.14, sssize.height*0.63);
	spHeadFrame->addChild(spHead);

	auto userName = LabelTTF::create(user->getUserName(), "arial", 20);
	userName->setPosition(sssize.width*0.6, sssize.height*0.87);
	spHeadFrame->addChild(userName);

	auto userlevel = LabelTTF::create(Value(leveldata.levelId).asString().c_str(), "arial", 20);
	userlevel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	userlevel->setPosition(sssize.width*0.245, sssize.height *0.17);
	spHeadFrame->addChild(userlevel);

	auto viplevelFrame = Sprite::create("viplevelFrame.png");
	viplevelFrame->setPosition(sssize.width * 1.05, sssize.height*0.88);
	auto viplevel = LabelAtlas::create(Value(user->getVipLevel()).asString().c_str(), "vipLevelNum.png", 11,16,'0');
	viplevel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	viplevel->setPosition(Vec2(viplevelFrame->getContentSize() / 2));
	viplevelFrame->addChild(viplevel);
	spHeadFrame->addChild(viplevelFrame);
	////////////////////////////////////////////////
	auto leveldataa = user->getLevelData();
	auto levelDes = String::createWithFormat("%d:%d", leveldataa.haveExp, leveldataa.passNeedExp);


	auto exeMur = (leveldataa.haveExp*1.0) / (1.0*leveldataa.passNeedExp);
	auto exeBarLeft = Sprite::create("exe_left.png");
	exeBarLeft->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	exeBarLeft->setPosition(sssize.width*0.33, sssize.height*0.47);
	spHeadFrame->addChild(exeBarLeft);
	auto exeBarMid = Sprite::create("exe_mid.png");
	exeBarMid->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	exeBarMid->setScaleX(140.0 / exeBarMid->getContentSize().width*exeMur);
	exeBarMid->setPosition(exeBarLeft->getContentSize().width, exeBarLeft->getContentSize().height / 2);
	exeBarLeft->addChild(exeBarMid);
	auto exeBarRight = Sprite::create("exe_right.png");
	exeBarRight->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	exeBarRight->setPosition(exeBarMid->getBoundingBox().size.width+exeBarLeft->getContentSize().width/2, exeBarMid->getContentSize().height / 2);
	exeBarLeft->addChild(exeBarRight);



	auto exeDescribe = LabelAtlas::create(levelDes->getCString(), "exeNum.png", 12,18,'0');
	exeDescribe->setAnchorPoint(Point::ANCHOR_MIDDLE);
	exeDescribe->setPosition(sssize.width*0.63, sssize.height*0.47);
	spHeadFrame->addChild(exeDescribe);

	//金币
	auto coinFrame = Sprite::create("coinFrame.png");
	coinFrame->setPosition(visibleSize.width*0.45, visibleSize.height*0.95);
	addChild(coinFrame);
	sssize = coinFrame->getContentSize();
	auto coin = Sprite::create("coin.png");
	coin->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	coin->setPosition(3, sssize.height *0.49);
	coinFrame->addChild(coin);

	userCoin = LabelTTF::create(Value(user->getCoins()).asString().c_str(), "arial", 20);
	userCoin->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	userCoin->setPosition(sssize.width*0.85, sssize.height *0.5);
	userCoin->setColor(Color3B(254,248,52));
	coinFrame->addChild(userCoin);

	auto addCoin = MenuItemImage::create("addBtn_nor.png", "addBtn_click.png", CC_CALLBACK_1(LobbyScene::payCoinCallback,this));
	addCoin->setAnchorPoint(Point::ANCHOR_MIDDLE);
	addCoin->setPosition(coinFrame->getPositionX() + sssize.width*0.48, coinFrame->getPositionY());


	//钻石
	auto diamondFrame = Sprite::create("coinFrame.png");
	diamondFrame->setPosition(visibleSize.width*0.74, visibleSize.height*0.95);
	addChild(diamondFrame);
	sssize = diamondFrame->getContentSize();
	auto diamond = Sprite::create("diamond.png");
	diamond->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	diamond->setPosition(1, sssize.height *0.495);
	diamond->setScale(0.8);
	diamondFrame->addChild(diamond);

	userdiamond = LabelTTF::create(Value(user->getDiamonds()).asString().c_str(), "arial", 20);
	userdiamond->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	userdiamond->setPosition(sssize.width*0.85, sssize.height *0.5);
	userdiamond->setColor(Color3B(254, 248, 52));
	diamondFrame->addChild(userdiamond);

	auto adddiamond = MenuItemImage::create("addBtn_nor.png", "addBtn_click.png", CC_CALLBACK_1(LobbyScene::payDiamondCallback, this));
	adddiamond->setAnchorPoint(Point::ANCHOR_MIDDLE);
	adddiamond->setPosition(diamondFrame->getPositionX() + sssize.width*0.48, diamondFrame->getPositionY());


	


	MarqueeManager::getInstance()->init();

	//背包
	auto bag = MenuItemImage::create("bag.png", "bag.png", CC_CALLBACK_1(LobbyScene::bagButtonCallback, this));
	bag->setPosition(visibleSize.width*0.28, visibleSize.height*0.08);

	//换奖品
	auto changeReward = MenuItemImage::create("changeReward.png", "changeReward.png", CC_CALLBACK_1(LobbyScene::changeRewardCallback, this));
	changeReward->setPosition(visibleSize.width*0.18, visibleSize.height*0.08);

	auto rankList = MenuItemImage::create("ranklist.png", "ranklist.png", CC_CALLBACK_1(LobbyScene::RankListCallback, this));
	rankList->setPosition(visibleSize.width*0.08, visibleSize.height*0.08);


	auto VIP = MenuItemImage::create("VIP.png", "VIP.png", CC_CALLBACK_1(LobbyScene::showVipCallBack, this));
	VIP->setPosition(visibleSize.width*0.05, visibleSize.height*0.70);

	auto guizu = MenuItemImage::create("guizu.png", "guizu.png", CC_CALLBACK_1(LobbyScene::guizuCallback, this));
	guizu->setPosition(visibleSize.width*0.05, visibleSize.height*0.55);

	auto fistPay = MenuItemImage::create("firstPayGIft.png", "firstPayGIft.png", CC_CALLBACK_1(LobbyScene::guizuCallback, this));
	fistPay->setPosition(visibleSize.width*0.05, visibleSize.height*0.40);


	//快速开始
	auto quickBegin = MenuItemImage::create("quickbegin_1.png", "quickbegin_2.png", CC_CALLBACK_1(LobbyScene::quickBeginCallback, this));
	quickBegin->setPosition(820, 87);
	auto menu = Menu::create(addCoin, adddiamond, bag, guizu, changeReward, quickBegin,rankList,VIP,fistPay,nullptr);
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
	
	createRoomLayer();

	/*this->scheduleOnce(schedule_selector(LobbyScene::showSign), 1.0f);*/  //签到崩溃

	this->scheduleOnce(schedule_selector(LobbyScene::showMarquee), 1.0f);
	scheduleUpdate();

	//test


	

	

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

	auto maxlevl = User::getInstance()->getMaxTurrentLevel();
	auto k = sortRoomByMaxlevel(maxlevl);
	auto menu = Menu::create();
	menu->setPosition(Point::ZERO);
	addChild(menu);
	for (size_t i = 0; i < k.size(); i++)
	{
		auto spPath = String::createWithFormat("level_%d.png", k[i].ui_id);
		auto cell = roomCell::createCell(spPath->getCString(), spPath->getCString(), CC_CALLBACK_1(LobbyScene::beginGameCallback, this));
		cell->setMinEnterLevel(k[i].unlock_turrent_level);
		cell->setTag(i+1);
		cell->setRoomid(k[i].room_id);
		cell->setPosition(roomPos[i+1]);


		//加锁和人数
		cell->setIslock(false);
		auto minLevel = cell->getMinEnterLevel();
		auto userLevel = User::getInstance()->getMaxTurrentLevel();
		if (userLevel < minLevel)
		{
			cell->setIslock(true);
			cell->setEnabled(false);
			auto lock = Sprite::create("lock.png");
			lock->setPosition(cell->getContentSize().width*0.2, cell->getContentSize().height*0.8);
			cell->addChild(lock);
		}
		///设置房间人数

		int nHour = SystemTime::getNowHour();
		int nPlayerNum = ConfigRoom::getInstance()->getPlayerCounts(nHour, cell->getRoomid());
		auto sp = Sprite::create("onLinePlayer.png");
		sp->setPosition(cell->getContentSize().width*0.4, cell->getContentSize().height*0.14);
		cell->addChild(sp,0,"onLinePlayer");
		auto label = LabelAtlas::create(Value(nPlayerNum).asString().c_str(), "onLineNum.png", 13, 20, '0');
		label->setAnchorPoint(Point::ZERO);
		label->setPosition(sp->getContentSize().width, 3);
		sp->addChild(label,0,"onLinePlayCount");






		roomCells.pushBack(cell);
		menu->addChild(cell);


		switch (i+1)
		{
		case 4:
			cell->setVisible(false);
			break;
		case 1:
			cell->setEnabled(false);
			cell->setScale(0.8);
			cell->setColor(Color3B(128, 128, 128));
			cell->getChildByName("onLinePlayer")->getChildByName("onLinePlayCount")->setColor(Color3B(128, 128, 128));
			break;
		case 2:
			cell->setScale(1);
			cell->setEnabled(true);
			cell->setColor(Color3B(255, 255, 255));
			cell->getChildByName("onLinePlayer")->getChildByName("onLinePlayCount")->setColor(Color3B(255, 255, 255));
			break;
		case 3:
			cell->setEnabled(false);
			cell->setScale(0.8);
			cell->setColor(Color3B(128, 128, 128));
			cell->getChildByName("onLinePlayer")->getChildByName("onLinePlayCount")->setColor(Color3B(128, 128, 128));
			break;
		default:
			break;
		}
	
		

	}
	//lockTheRoom();

}


void LobbyScene::payCoinCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICK);
	auto paylayer = payLayer::createLayer(1);
	paylayer->setPosition(Point::ZERO);
	addChild(paylayer, kZorderDialog);
}
void LobbyScene::payDiamondCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICK);
	auto paylayer = payLayer::createLayer(2);
	paylayer->setPosition(Point::ZERO);
	addChild(paylayer, kZorderDialog);
}
void LobbyScene::beginGameCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICK);
	auto cell = (roomCell*)psend;
	GameData::getInstance()->setRoomID(cell->getRoomid());
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::create()));
}

void LobbyScene::bagButtonCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICK);
	Director::getInstance()->pushScene(BagLayer::createScene());
}

void LobbyScene::changeRewardCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICK);
	auto layer = SettingDialog::create();
	layer->setPosition(Point::ZERO);
	addChild(layer, kZorderDialog);
}
void LobbyScene::RankListCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICK);
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
	Audio::getInstance()->playSound(CLICK);
	auto guizulayer = NobilityLayer::createLayer();
	guizulayer->setPosition(Point::ZERO);
	addChild(guizulayer, kZorderDialog);
}


void LobbyScene::showVipCallBack(Ref*psend)
{
	Audio::getInstance()->playSound(CLICK);
	auto viplayer = VIPLayer::create();
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
	Audio::getInstance()->playSound(CLICK);
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

