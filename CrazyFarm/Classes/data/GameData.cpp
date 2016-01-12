#include "data/GameData.h"
#include "cocos2d.h"
using namespace cocos2d;

GameData* GameData::_instance = 0;

GameData::GameData(){
	this->init();
}

void GameData::init(){
	setRoomID(-1);
}

GameData* GameData::getInstance(){
	if(_instance == 0){
		_instance = new GameData();
	}
	return _instance;
}
