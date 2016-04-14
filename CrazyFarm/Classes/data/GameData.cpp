#include "data/GameData.h"
#include "cocos2d.h"
#include "domain/user/User.h"
using namespace cocos2d;

GameData* GameData::_instance = 0;

GameData::GameData(){
	this->init();
}

void GameData::init(){
	setRoomID(-1);
	setIsOnMaridTask(false);
	setisOnBankrupt(false);
	setisPlayerOneGame(false);
	setisOnGameScene(false);
	setisDirectUseSkill(false);
	setisOnGroupComing(false);
	setisLoadMsgOnGame(false);
	setTouchLockTurretType(0);

	setgainCoin(0);
	setcostCoin(0);
	setchangeExp(0);
	getCatchFishes().clear();
	setshootCounts(0);
	
}

GameData* GameData::getInstance(){
	if(_instance == 0){
		_instance = new GameData();
	}
	return _instance;
}
Turrent GameData::getTurrentData()
{
	auto turrent = ConfigTurrent::getInstance()->getTurrent(nNowLevel); 
	return turrent; 
}

void GameData::setSoundState(bool state) {
	UserDefault::getInstance()->setBoolForKey("soundState", state);
}

bool GameData::getSoundState() {
	return UserDefault::getInstance()->getBoolForKey("soundState", true);
}

void GameData::setMusicState(bool state) {
	UserDefault::getInstance()->setBoolForKey("musicState", state);
}

bool GameData::getMusicState() {
	return UserDefault::getInstance()->getBoolForKey("musicState", true);
}


unsigned int GameData::getRandomSeed()
{
	_RandomSeed--;
		return _RandomSeed;
}
void GameData::setRandomSeed(unsigned int var)
{
	_RandomSeed = var;
}

void GameData::addCatchFishes(int fishid, int level)
{
	for (auto &var:_catchFishes)
	{
		if (var.Multiple == level)
		{
			var.fishids.push_back(fishid);
			return;
		}
	}
	CatchFishIdByMultiple info;
	info.fishids.push_back(fishid);
	info.Multiple = level;
	_catchFishes.push_back(info);
	return;
}
void GameData::addGoldCatchFishes(int fishid)
{
	_goldFishIds.push_back(fishid);
}