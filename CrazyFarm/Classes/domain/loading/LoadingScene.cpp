#include "domain/loading/LoadingScene.h"
#include "config/ConfigSign.h"
#include "config/ConfigManager.h"
#include "fish/FishAniMannage.h"
#include "utill/AnimationUtil.h"
#include "server/HttpMannger.h"
#include "domain/user/User.h"
#include "lobby/LobbyScene.h"
#include "domain/user/DeviceInfo.h"
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
void LoadingScene::addPlistPngRes(std::string filename)
{
	Director::getInstance()->getTextureCache()->addImageAsync(filename + "png",
		[=](Texture2D *texture)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(filename+("plist"), texture);
	});
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
	AnimationUtil::getInstance()->addAnimationBySpriteName("game/ui/ani/water/aniWater%d.jpg", "aniWater", 3.0f, 30);
	AnimationUtil::getInstance()->addAnimationBySpriteName("game/ui/ani/shootFire/aniShoot%d.png", "aniShoot", 0.5f, 5);
	AnimationUtil::getInstance()->addAnimationBySpriteName("game/ui/ani/bubble/aniBubble%d.png", "aniBubble", 2.5f, 46);
	AnimationUtil::getInstance()->addAnimationBySpriteName("game/ui/ani/net_ice/netIce%d.png", "iceNet", 0.7f, 18);
	AnimationUtil::getInstance()->addAnimationBySpriteName("game/ui/ani/net_fire/netFire%d.png", "fireNet", 0.7f, 18);
	AnimationUtil::getInstance()->addAnimationBySpriteName("game/ui/ani/gold/goldAni_%d.png", "aniGold", 0.3f, 5);
	AnimationUtil::getInstance()->addAnimationBySpriteName("game/ui/ani/silver/yinbi_%d.png", "aniSilver", 0.3f, 5);
	AnimationUtil::getInstance()->addAnimationBySpriteName("game/ui/ani/zhaohuan/TX_ZhaoHuan_%d.png", "aniZhaoHuan", 1.1f, 37);
	AnimationUtil::getInstance()->addAnimationBySpriteName("game/ui/ani/TX_DongJie/TX_qpdj_%d.png", "aniTXTdj", 1.1f, 14);
	AnimationUtil::getInstance()->addAnimationBySpriteName("game/ui/ani/TX_BaoZha/TX_BaoZha_%d.png", "aniTXTBoom", 2.2f, 28);
	AnimationUtil::getInstance()->addAnimationBySpriteName("game/ui/ani/TX_ShiYongJiNeng/TX_SYJN_%d.png", "aniTurretLock", 0.5f, 6);
	AnimationUtil::getInstance()->addAnimationBySpriteName("game/ui/ani/TX_MiaoZhun/TX_MiaoZhun_%d.png", "aniFishLock", 0.8f, 10);
	AnimationUtil::getInstance()->addAnimationBySpriteName("game/ui/ani/TX_ShengJi/TX_ShengJi_%d.png", "aniShengji", 1.5, 21);
	//load fish ani
	int i = 1;
	for (int i = 1; i < 100; i++)
	{
		auto jsonPath = String::createWithFormat("game/ui/fish/fish_frame_%d.json", i);
		auto plistPath = String::createWithFormat("game/ui/fish/fish_frame_%d.plist", i);
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
		HttpMannger::getInstance()->HttpToPostRequestRegisterInfo(DeviceInfo::getChange_id(), DeviceInfo::getImei(), DeviceInfo::getHd_type(), DeviceInfo::getHd_factory());
	}
	else
	{
		HttpMannger::getInstance()->HttpToPostRequestLogInInfo(DeviceInfo::getChange_id(), name, DeviceInfo::getImei(), DeviceInfo::getHd_type(), DeviceInfo::getHd_factory());
	}
}