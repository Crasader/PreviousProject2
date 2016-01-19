#pragma once
#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
using namespace cocos2d;

struct ShootData
{
	float shootInterval;
	int shootSpeed;
};


class GameConfig {

public:
	static GameConfig* getInstance();
	bool loadConfig();
	ShootData getShootData(){ return shootData; };
private:
	GameConfig();
	static GameConfig* _instance;
	ShootData shootData;
};


