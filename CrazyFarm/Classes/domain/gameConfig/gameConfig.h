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
private:
	GameConfig();
	static GameConfig* _instance;
	CC_SYNTHESIZE(ShootData, shootData, ShootData);
};


