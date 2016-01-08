#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_
#include "cocos2d.h"
using namespace cocos2d;

class GAMEDATA{
public:
	static GAMEDATA* getInstance();


private:
	GAMEDATA();
	void init();
	static GAMEDATA* _instance;
	CC_SYNTHESIZE(int, nRoomId, RoomID);

};

#endif
