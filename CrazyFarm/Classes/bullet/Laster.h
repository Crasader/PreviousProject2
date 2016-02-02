#pragma once
#include "cocos2d.h" 
#include "turret/PlayerTurret.h"
#include "fish/Fish.h"
using namespace cocos2d;

class Laster :public Sprite{
public:
	virtual bool init();
	CREATE_FUNC(Laster);
	void setTarget(Fish* fish);
	void update(float delta);
private:
	CC_SYNTHESIZE(PlayerTurret*, pPlayerTurret, PlayerTurret);
	Fish*m_target = nullptr;

};
