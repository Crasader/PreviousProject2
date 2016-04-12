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
	//��������
	int diffTurretLv;
	//����
	bool _isFire;
	float _angle;
	//ʹ�ü���
	int skillid;  ///1-5
		//��������
		Fish* _lockFish;
		//�˵�
		Vec2 _boomPos;

private:
    
};

#endif
