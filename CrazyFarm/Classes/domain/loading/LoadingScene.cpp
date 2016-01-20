#include "domain/loading/LoadingScene.h"
#include "config/ConfigSign.h"
#include "config/ConfigManager.h"
#include "fish/FishAniMannage.h"
#include "utill/AnimationUtil.h"
#include "server/HttpMannger.h"
#include "domain/user/User.h"
#include "lobby/LobbyScene.h"
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
	auto bg = Sprite::create("lobbyBG.png");
	bg->setPosition(480, 270);
	addChild(bg);
	
	runAction(Sequence::create(CallFunc::create([&]{login();
		loadRes();}),DelayTime::create(2.0f), CallFunc::create([&]{Director::getInstance()->replaceScene(LobbyScene::createScene()); }), nullptr));
	return true;
}


void LoadingScene::loadedCallBack()
{
	//haveLoadedNum++;
	//this->runAction(CCDelayTime::create(15));
	//char tmp[10];
	//sprintf(tmp, "%%%d", (int)((float)haveLoadedNum / totalNum * 100));
	//ttf->setString(tmp);  //更改加载进度
	//if (haveLoadedNum == 9)
	//{
	//	this->removeChild(ttf, true);   //加载完成后，移除加载进度显示
	//	CCScene *newscne = HelloWorld::scene();
	//	CCDirector::sharedDirector()->replaceScene(newscne); //场景切换
	//}
}

void LoadingScene::loadRes()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("batch_frame_bullet.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gun_frame.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("batch_frame_net.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gift_frame.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game_scene_frame.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("unlock_cannon_frame.plist");
	///load ani
	AnimationUtil::getInstance()->addAnimationBySpriteName("ani/water/aniWater%d.jpg", "aniWater", 3.0f, 30);
	AnimationUtil::getInstance()->addAnimationBySpriteName("ani/shootFire/aniShoot%d.png", "aniShoot", 0.5f, 5);
	AnimationUtil::getInstance()->addAnimationBySpriteName("ani/bubble/aniBubble%d.png", "aniBubble", 2.0f, 19);
	AnimationUtil::getInstance()->addAnimationBySpriteName("ani/net_ice/netIce%d.png", "iceNet", 0.7f, 18);
	AnimationUtil::getInstance()->addAnimationBySpriteName("ani/net_fire/netFire%d.png", "fireNet", 0.7f, 18);
	//load fish ani
	int i = 1;
	for (int i = 1; i < 100; i++)
	{
		auto jsonPath = String::createWithFormat("fish/fish_frame_%d.json", i);
		auto plistPath = String::createWithFormat("fish/fish_frame_%d.plist", i);
		if (!FishAniMannage::getInstance()->loadAniByJsonAndPlist(jsonPath->getCString(), plistPath->getCString()))
		{

		}
	}

	ConfigManager::getInstance()->LoadConfig();

	ConfigSign::getInstance()->LoadConfig();
	
}

void LoadingScene::login()
{
	auto name = User::getInstance()->getUserId();
	if (name == "guest")
	{
		HttpMannger::getInstance()->HttpToPostRequestRegisterInfo("test_1000",88888, 123, 123);
	}
	else
	{
		HttpMannger::getInstance()->HttpToPostRequestLogInInfo("test_1000",name, 88888, 123, 123);
	}
}