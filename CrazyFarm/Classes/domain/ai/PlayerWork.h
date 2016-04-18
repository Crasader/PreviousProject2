#ifndef _PLAYERWORK_H_
#define _PLAYERWORK_H_
#include "cocos2d.h"
#include "fish/Fish.h"
using namespace cocos2d;

enum PlayWorktype
{
	Robot_UpdateTurrent,
	Robot_UsingSkill,
	Robot_Fire,
	Invalid = -1

};


class PlayerWork {

public:

	PlayWorktype _workeType;
	//升级降级
	int diffTurretLv;
	//开火
	bool _isFire;
	float _angle;
	//锁定激光
	Fish* _lockFish = nullptr;


private:
    
};

#endif
