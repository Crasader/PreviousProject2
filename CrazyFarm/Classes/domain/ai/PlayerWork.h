#ifndef _PLAYERWORK_H_
#define _PLAYERWORK_H_
#include "cocos2d.h"
#include "fish/Fish.h"
using namespace cocos2d;

enum PlayWorktype
{
	Robot_UpdateTurrent,
	Robot_UsingSkill,
	Robot_Fire
};


class PlayerWork {

public:

	PlayWorktype _workeType;
	//升级降级
	int diffTurretLv;
	//开火
	bool _isFire;
	float _angle;
	//使用技能
	int skillid;  ///1-5
		//锁定激光
		Fish* _lockFish;
		//核弹
		Vec2 _boomPos;

private:
    
};

#endif
