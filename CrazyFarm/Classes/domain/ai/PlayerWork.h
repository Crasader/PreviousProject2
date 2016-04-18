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
	//��������
	int diffTurretLv;
	//����
	bool _isFire;
	float _angle;
	//��������
	Fish* _lockFish = nullptr;


private:
    
};

#endif
