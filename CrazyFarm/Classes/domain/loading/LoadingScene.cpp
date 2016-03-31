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
#include "utill/Chinese.h"
#include "utill/CircleMoveTo.h"
#include "utill/Audio.h"
#include "lobby/signlayer/SignMannger.h"
#include "domain/ToolTip/TwiceSureDialog.h"
#include "domain/Newbie/NewbieMannger.h"
#include "domain/login/LoginScene.h"



LoadingScene*LoadingScene::create(bool isisFirstComingNeedRegister)
{
	LoadingScene *pRet = new LoadingScene();
	if (pRet && pRet->init(isisFirstComingNeedRegister))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
Scene* LoadingScene::createScene(bool isisFirstComingNeedRegister)
{
	auto scene = Scene::create();

	auto layer = LoadingScene::create(isisFirstComingNeedRegister);

	scene->addChild(layer, 0, 888);

	return scene;
}

bool LoadingScene::init(bool isisFirstComingNeedRegister)
{
	if (!Layer::init())
	{
		return false;
	}
	auto bg = Sprite::create("loading_new.jpg");
	bg->setPosition(480, 270);
	addChild(bg);



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
	showTip();


	Audio::getInstance()->prepare();
	scheduleUpdate();

	if (isisFirstComingNeedRegister)
	{
		toRegister();
	}
	else
	{
		load();
	}
	return true;
}

void LoadingScene::update(float dt)
{
	loadingBar->setPercent(((float)temp) / 15.0f*100+1);
	if (temp >= 15 && isRegisterdialog)///TODo:第一次登陆没网
	{
	
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, LobbyScene::createScene()));
		unscheduleUpdate();
	}
}
void LoadingScene::load()
{
	loadRes();
}


void LoadingScene::loadAniWithPng(const char *filepath, const char *animatname, float time, int numOfpng, bool isSetRestoreOriginalFrame)
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
			data->isSetRestoreOriginalFrame = isSetRestoreOriginalFrame;
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
	AnimationUtil::getInstance()->addAnimationBySpriteName(data->filepath, data->animatname, data->time, data->numOfpng,data->isSetRestoreOriginalFrame);
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




void LoadingScene::toRegister()
{
	isRegisterdialog = false;
	LoginMannger::getInstance()->toRegister();
	NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(LoadingScene::httpCallback), "firstRegister", NULL);

}
void LoadingScene::httpCallback(Ref*psend)
{
	FirstRegisterValue *value = (FirstRegisterValue*)psend;
	switch (value->_errorcode)
	{
	case 0:
		isRegisterdialog = true;
		User::getInstance()->setSessionid(value->_sesssionid);
		User::getInstance()->setUserName(value->username);
		User::getInstance()->setUserGender(0);
		LoginMannger::getInstance()->addMemoryNickname(value->username.c_str(), "defalut");
		NewbieMannger::getInstance()->setNBRewards(value->rewards);
		NewbieMannger::getInstance()->setisAllowdedGetFirstReward(true);
		load();
		break;
	case 404:
	{
		auto scene = LoginScene::createScene();
		Director::getInstance()->replaceScene(scene);
		auto dioag = TwiceSureDialog::createDialog(ChineseWord("LoginTimeOut").c_str());
		dioag->setPosition(0, 0);
		scene->addChild(dioag, 30);
	}
	break;
	default:
	{
		auto scene = LoginScene::createScene();
		Director::getInstance()->replaceScene(scene);
		auto dioag = TwiceSureDialog::createDialog(value->_errormsg.c_str());
		dioag->setPosition(0, 0);
		scene->addChild(dioag, 30);
	}
	break;
	}
	NotificationCenter::getInstance()->removeObserver(this, "firstRegister");
	delete value;
}



void LoadingScene::loadRes()
{
	
	
	ConfigManager::getInstance()->LoadConfig();

	/*ConfigSign::getInstance()->LoadConfig();*/
	//大厅动画
	loadAniWithPng("game/ui/ani/bowen/bowen_%d.png", "aniBowen", 3.0f, 30);
	loadAniWithPng("game/ui/ani/gainRewards/aniGetRewards%d.png", "aniGainRewards", 1.3f, 10);
	loadAniWithPng("game/ui/ani/VipButton/TX_VIP_%d.png", "aniVipButton", 1.3, 20);
	loadAniWithPng("game/ui/ani/firstPay/TX_ShouChong_%d.png", "aniFirstPay", 1.3f, 10);
	loadAniWithPng("game/ui/ani/guizu/TX_GuiZu_%d.png", "aniGuizu", 1.3f, 10);
	loadAniWithPng("game/ui/ani/firstBox/firstBox_%d.png", "anifirstBox", 0.5f, 5,false);
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
	
	
}






void LoadingScene::showTip()
{
	int randNum = 0;
	auto str = String::createWithFormat("LoadingTip%d", randNum);
	auto label = LabelTTF::create(ChineseWord(str->getCString()).c_str(), "arial", 21);
	label->setColor(Color3B::WHITE);
	label->setAnchorPoint(Point::ANCHOR_MIDDLE);
	label->setPosition(480, 30);
	addChild(label);
}