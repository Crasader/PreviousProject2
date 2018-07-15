#include "GameResultScene.h"
#include "GameResultLayer.h"
#include "Audio.h"
#include "CallAndroidMethod.h"
#include "GameData.h"
Scene* GameResultScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameResultScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameResultScene::init(){
if ( !Scene::init() )
	{
		return false;
	}
  //add layers to this scene
	Audio::getInstance()->playSound(GAME_FAIL);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Layer* result_result = GameResultLayer::create();
	result_result->setAnchorPoint(ccp(0, 0));
	result_result->setPosition(ccp(0, 0));
	this->addChild(result_result);


	auto event = String::createWithFormat("level_%d", GAMEDATA::getInstance()->getLevel());
	CallAndroidMethod::getInstance()->logevent(event->getCString(), "failed", "NA");
	return true;
}