#include "domain/loading/LoadingScene.h"
#include "config/ConfigSign.h"
#include "config/ConfigManager.h"
#include "fish/FishAniMannage.h"
#include "utill/AnimationUtil.h"
#include "utill/FunUtil.h"
#include "server/HttpMannger.h"
#include "domain/user/User.h"
#include "lobby/LobbyScene.h"
#include "domain/user/DeviceInfo.h"
#include "core/GameScene.h"
#include "domain/login/LoginMannger.h"



Scene* LoadingScene::createScene()
{
	auto scene = Scene::create();

	auto layer = LoadingScene::create();

	scene->addChild(layer, 0, 888);

	return scene;
}

bool LoadingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto bg = Sprite::create("loading2.jpg");
	bg->setPosition(480, 270);
	addChild(bg);
	AnimationUtil::getInstance()->addAnimationBySpriteName("game/ui/ani/bubble/aniBubble%d.png", "aniBubble", 3.5f, 46);
	load();

	auto aniNode = Sprite::create();
	aniNode->setPosition(900, 150);
	addChild(aniNode, 5);
	aniNode->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniBubble")));

	aniNode = Sprite::create();
	aniNode->setPosition(76, 150);
	addChild(aniNode, 5);
	aniNode->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniBubble")));


	auto loadingbarFrame = Sprite::create("loadingbar1.png");
	loadingbarFrame->setPosition(480,75);
	addChild(loadingbarFrame);

	loadingBar = ui::LoadingBar::create("loadingbar2.png");
	loadingBar->setAnchorPoint(Point::ANCHOR_MIDDLE);
	loadingBar->setPosition(loadingbarFrame->getContentSize() / 2+Size(10,0));
	loadingbarFrame->addChild(loadingBar);


	scheduleUpdate();
	return true;
}

void LoadingScene::update(float dt)
{
	loadingBar->setPercent(((float)temp) / 60.0f*100);
	if (temp>=59)
	{
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, LobbyScene::createScene()));
		unscheduleUpdate();
	}
}
void LoadingScene::load()
{
	loadRes();
}


void LoadingScene::loadAniWithPng(const char *filepath, const char *animatname, float time, int numOfpng)
{
	for (int i = 1; i <= numOfpng;i++)
	{
		auto path = String::createWithFormat(filepath, i);
		LoadAniData*data = nullptr;
		if (i==numOfpng)
		{
			data = new LoadAniData();
			strcpy(data->animatname, animatname);
			strcpy(data->filepath, filepath);
			data->time = time;
			data->numOfpng = numOfpng;
		}
		Director::getInstance()->getTextureCache()->addImageAsync(path->getCString(),
			CC_CALLBACK_1(LoadingScene::imageAsyncCallback, this, data));
		
	}
}
void LoadingScene::imageAsyncCallback(Texture2D* texture,void*aniData)
{
	if (aniData == nullptr)
	{
		return;
	}
	LoadAniData*data = (LoadAniData*)aniData;
	AnimationUtil::getInstance()->addAnimationBySpriteName(data->filepath, data->animatname, data->time, data->numOfpng);
	delete data;
	temp++;
}

void LoadingScene::loadFishAni(const char* PngName, const char* jsonName, const char* plistName)
{
	LoadFishAniData*data = new LoadFishAniData();
	strcpy(data->jsonName, jsonName);
	strcpy(data->plistName, plistName);
	Director::getInstance()->getTextureCache()->addImageAsync(PngName,
		CC_CALLBACK_1(LoadingScene::imageFishAniAsyncCallback, this, data));
}
void LoadingScene::imageFishAniAsyncCallback(Texture2D* texture, void*aniData)
{
	LoadFishAniData*data = (LoadFishAniData*)aniData;
	FishAniMannage::getInstance()->loadAniByJsonAndPlist(data->jsonName, data->plistName);
	delete data;
	temp++;
}






void LoadingScene::loadRes()
{
	login();

	ConfigManager::getInstance()->LoadConfig();

	ConfigSign::getInstance()->LoadConfig();
	//大厅动画
	loadAniWithPng("game/ui/ani/bowen/bowen_%d.png", "aniBowen", 3.0f, 30);
	loadAniWithPng("game/ui/ani/shootFire/aniShoot%d.png", "aniShoot", 0.5f, 5);
	
	loadAniWithPng("game/ui/ani/net_ice/netIce%d.png", "iceNet", 0.7f, 18);
	loadAniWithPng("game/ui/ani/net_fire/netFire%d.png", "fireNet", 0.7f, 18);
	loadAniWithPng("game/ui/ani/gold/goldAni_%d.png", "aniGold", 0.3f, 5);
	loadAniWithPng("game/ui/ani/silver/yinbi_%d.png", "aniSilver", 0.3f, 5);
	loadAniWithPng("game/ui/ani/zhaohuan/TX_ZhaoHuan_%d.png", "aniZhaoHuan", 1.1f, 37);
	loadAniWithPng("game/ui/ani/TX_DongJie/TX_qpdj_%d.png", "aniTXTdj", 1.1f, 14);
	loadAniWithPng("game/ui/ani/TX_BaoZha/TX_BaoZha_%d.png", "aniTXTBoom", 2.2f, 28);
	loadAniWithPng("game/ui/ani/TX_ShiYongJiNeng/TX_SYJN_%d.png", "aniTurretLock", 0.5f, 6);
	loadAniWithPng("game/ui/ani/TX_MiaoZhun/TX_MiaoZhun_%d.png", "aniFishLock", 0.8f, 10);
	loadAniWithPng("game/ui/ani/TX_ShengJi/TX_ShengJi_%d.png", "aniShengji", 1.5f, 21);
	loadAniWithPng("game/ui/ani/gainRewards/aniGetRewards%d.png", "aniGainRewards", 1.3f, 10);
	loadAniWithPng("game/ui/ani/VipButton/TX_VIP_%d.png", "aniVipButton", 1.3, 20);
	loadAniWithPng("game/ui/ani/firstPay/TX_ShouChong_%d.png", "aniFirstPay", 1.3f, 10);
	loadAniWithPng("game/ui/ani/guizu/TX_GuiZu_%d.png", "aniGuizu", 1.3f, 10);
	loadAniWithPng("game/ui/ani/firstBox/firstBox_%d.png", "anifirstBox", 0.5f, 5);
	//房间动画
	loadAniWithPng("game/ui/ani/roomcell/roomAni_2_%d.png", "aniRoom_id2", 0.5f, 4);
	loadAniWithPng("game/ui/ani/roomcell/roomAni_3_%d.png", "aniRoom_id3", 0.5f, 4);
	loadAniWithPng("game/ui/ani/roomcell/roomAni_4_%d.png", "aniRoom_id4", 0.5f, 3);
	loadAniWithPng("game/ui/ani/LightPoint/TX_ShanGuang_%d.png", "aniLightPoint", 1.0f, 14);
	loadAniWithPng("game/ui/ani/capLight/capLight_%d.png", "anicapLight", 0.8f, 8);
	loadAniWithPng("game/ui/ani/caidai/TX_CaiDai_%d.png", "aniCaidai", 1.5f, 24);
	//大厅鱼
	loadAniWithPng("game/ui/ani/lobbyfish1/TX_YU_%d.png", "aniLobbyFish1", 1.6f, 16);
	loadAniWithPng("game/ui/ani/lobbyfish2/TX_YU2_%d.png", "aniLobbyFish2", 1.4f, 14);
	loadAniWithPng("game/ui/ani/lobbyfish3/TX_YU3_%d.png", "aniLobbyFish3", 0.9f, 9);
	//游戏内动画
	loadAniWithPng("game/ui/ani/TX_DianGuang/TX_DianGuang_%d.png", "aniJiGuangBottom", 0.4f, 6);
	loadAniWithPng("game/ui/ani/TX_JiGuang/TX_JiGuang_%d.png", "aniJiGuangBar", 0.2f, 3);
	loadAniWithPng("game/ui/ani/TX_BossLight/TX_BOSS_%d.png", "aniBossLight", 1.0f, 16);
	loadAniWithPng("game/ui/ani/TX_GoldFish/aniGoldfish_%d.png", "aniGoldfish", 2.0f, 18);
	loadAniWithPng("game/ui/ani/TX_DianQiu/TX_DianQiu_%d.png", "aniDianQiu", 1.0f, 13);
	loadAniWithPng("game/ui/ani/TX_shandian/shandian_%d.png", "aniShandian", 0.5f, 4);
	loadAniWithPng("game/ui/ani/TX_huanpao/aniHuanpao_%d.png", "aniHuanpao", 0.3f, 7);

	//load fish ani
	for (int i = 1; i <= 10; i++)
	{
		auto jsonPath = String::createWithFormat("game/ui/fish/fish_frame_%d.json", i);
		auto plistPath = String::createWithFormat("game/ui/fish/fish_frame_%d.plist", i);
		auto pngPath = String::createWithFormat("game/ui/fish/fish_frame_%d.png", i);
		loadFishAni(pngPath->getCString(), jsonPath->getCString(), plistPath->getCString());
	}
	for (int i = 30; i <= 37; i++)
	{
		auto jsonPath = String::createWithFormat("game/ui/fish/fish_frame_%d.json", i);
		auto plistPath = String::createWithFormat("game/ui/fish/fish_frame_%d.plist", i);
		auto pngPath = String::createWithFormat("game/ui/fish/fish_frame_%d.png", i);
		loadFishAni(pngPath->getCString(), jsonPath->getCString(), plistPath->getCString());
	}
	for (int i = 40; i <= 44; i++)
	{
		auto jsonPath = String::createWithFormat("game/ui/fish/fish_frame_%d.json", i);
		auto plistPath = String::createWithFormat("game/ui/fish/fish_frame_%d.plist", i);
		auto pngPath = String::createWithFormat("game/ui/fish/fish_frame_%d.png", i);
		loadFishAni(pngPath->getCString(), jsonPath->getCString(), plistPath->getCString());
	}
	for (int i = 50; i <= 52; i++)
	{
		auto jsonPath = String::createWithFormat("game/ui/fish/fish_frame_%d.json", i);
		auto plistPath = String::createWithFormat("game/ui/fish/fish_frame_%d.plist", i);
		auto pngPath = String::createWithFormat("game/ui/fish/fish_frame_%d.png", i);
		loadFishAni(pngPath->getCString(), jsonPath->getCString(), plistPath->getCString());
	}	
}





void LoadingScene::login()
{
	LoginMannger::getInstance()->login();
}