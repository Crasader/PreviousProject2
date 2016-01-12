#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_
#include "cocos2d.h"
using namespace cocos2d;

class GameData {
public:
	static GameData* getInstance();


private:
	GameData();
	void init();
	static GameData* _instance;
	CC_SYNTHESIZE(int, nRoomId, RoomID);

};

#endif
