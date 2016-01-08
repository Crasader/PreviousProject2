#include "lobby/LobbyScene.h"
#include "core/GameScene.h"
#include "utill/Chinese.h"
#include "utill/AnimationUtil.h"
#include "User.h"
#include "fish/FishRouteData.h"
#include "lobby/bagLayer.h"
#include "fish/FishAniMannage.h"
#include "fish/FishGroupData.h"
#include "HttpClientUtill.h"
#include "config/ConfigRoom.h"
#include "data/GameData.h"
#include "config/ConfigManager.h"





const Vec2 roomPos[5] = { Vec2(-300, 270), Vec2(192, 270), Vec2(480, 270), Vec2(768, 270), Vec2(960+300, 270)};

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

	scene->addChild(layer);

	return scene;
}

bool LobbyScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
    //add all fish plsit
	loadResource();
	auto user = User::getInstance();
	auto leveldata = user->getLevelData();

	//if (user->getUserId() == "guest")
	//{
	//	HttpClientUtill::getInstance()->onGetHttp("http://114.119.39.150:1701/user/hello", CC_CALLBACK_2(LobbyScene::onHttpRequestCompleted, this));
	//}



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
	auto levelDes = String::createWithFormat("%d / %d", leveldataa.haveExp, leveldataa.passNeedExp);


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
	exeBarRight->setPosition(exeBarMid->getBoundingBox().size.width, exeBarMid->getContentSize().height/2);
	exeBarMid->addChild(exeBarRight);


	//
	//auto exeBar = Sprite::create("exeBar.png");
	//exeBar->setScaleX(150.0 / exeBar->getContentSize().width*exeMur);
	//exeBar->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	//exeBar->setPosition(sssize.width*0.33, sssize.height*0.47);
	//	spHeadFrame->addChild(exeBar);

	auto exeDescribe = LabelTTF::create(levelDes->getCString(), "arial", 17);
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


	


	//背包
	auto bag = MenuItemImage::create("bag.png", "bag.png", CC_CALLBACK_1(LobbyScene::bagButtonCallback, this));
	bag->setPosition(visibleSize.width*0.3, visibleSize.height*0.1);

	auto menu = Menu::create(addCoin, adddiamond, bag, nullptr);
	menu->setPosition(Point::ZERO);
	addChild(menu);
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
	return true;
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
	
	FishRouteData::getInstance()->loadConfig();
	FishGroupData::getInstance()->loadConfig();

}


void LobbyScene::createRoomLayer()
{
	auto visibisize = Director::getInstance()->getVisibleSize();

	auto roomDatas = ConfigRoom::getInstance()->getRooms();
	auto menu = Menu::create();
	menu->setPosition(Point::ZERO);
	addChild(menu);
	for (auto room:roomDatas)
	{
		auto spPath = String::createWithFormat("level_%d.png", room.ui_id);
		auto cell = roomCell::createCell(spPath->getCString(), spPath->getCString(), CC_CALLBACK_1(LobbyScene::beginGameCallback, this));
		cell->setMinEnterLevel(room.unlock_turrent_level);
		cell->setTag(room.room_id);
		cell->setRoomid(room.room_id);
		cell->setPosition(roomPos[room.room_id]);
		roomCells.pushBack(cell);
		menu->addChild(cell);


		switch (room.room_id)
		{
		case 4:
			cell->setVisible(false);
			break;
		case 1:
			cell->setEnabled(false);
			cell->setScale(0.8);
			cell->setColor(Color3B(128, 128, 128));
			break;
		case 2:
			cell->setScale(1);
			cell->setEnabled(true);
			cell->setColor(Color3B(255, 255, 255));
			break;
		case 3:
			cell->setEnabled(false);
			cell->setScale(0.8);
			cell->setColor(Color3B(128, 128, 128));
			break;
		default:
			break;
		}

	}
	lockTheRoom();

}


void LobbyScene::payCoinCallback(Ref*psend)
{
	auto coin = User::getInstance()->addCoins(1000);
	userCoin->setString(Value(coin).asString().c_str());

	
}
void LobbyScene::payDiamondCallback(Ref*psend)
{
	auto diamonds = User::getInstance()->addDiamonds(1000);
	userdiamond->setString(Value(diamonds).asString().c_str());
}
void LobbyScene::beginGameCallback(Ref*psend)
{
	auto cell = (roomCell*)psend;
	GAMEDATA::getInstance()->setRoomID(cell->getRoomid());
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::create()));
}

void LobbyScene::bagButtonCallback(Ref*psend)
{
	Director::getInstance()->pushScene(BagLayer::createScene());
}

void LobbyScene::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}

	long statusCode = response->getResponseCode();
	char statusString[64] = {};
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	log("error buffer: %s", response->getErrorBuffer());
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
	if (doc.HasParseError())
	{
		log("get json data err!");;
	}
	User::getInstance()->setUserID(doc["user_name"].GetString());
	log("error_code:%d", doc["error_code"].GetInt());
	log("error_msg:%s", doc["error_msg"].GetString());
	log("user_name:%s", doc["user_name"].GetString());
	log("session_id:%s", doc["session_id"].GetString());
}

bool LobbyScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	auto pos = touch->getLocation();
	if (pos.y>100&&pos.y<440)
	{
		if (pos.x>480)
		{
			moveRoomRight();
		}
		else
		{
			moveRoomLeft();
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
			break;
		case 2:
			cell->setScale(1);
			if (!cell->getIslock())
			{
				cell->setEnabled(true);
			}
			cell->setColor(Color3B(255,255,255));
			cell->runAction(MoveTo::create(0.1f, roomPos[tag]));
			break;
		case 3:
			cell->setPosition(roomPos[4]);
			cell->setEnabled(false);
			cell->setScale(0.8);
			cell->setColor(Color3B(128, 128, 128));
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
			cell->runAction(MoveTo::create(0.1f, roomPos[tag]));
			break;
		case 2:
			cell->setScale(1);
			if (!cell->getIslock())
			{
				cell->setEnabled(true);
			}
			cell->setColor(Color3B(255, 255, 255));
			cell->runAction(MoveTo::create(0.1f, roomPos[tag]));
			break;
		case 3:
			cell->setPosition(roomPos[4]);
			cell->setEnabled(false);
			cell->setScale(0.8);
			cell->setColor(Color3B(128, 128, 128));
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
	}
}

