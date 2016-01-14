#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_
#include "cocos2d.h"
#include "domain/magnate/MagnateManager.h"
#include "config/ConfigTurrent.h"
using namespace cocos2d;

class GameData {
public:
	static GameData* getInstance();
	Turrent getTurrentData();

private:
	GameData();
	void init();
	static GameData* _instance;
	CC_SYNTHESIZE(int, nRoomId, RoomID);
	CC_SYNTHESIZE(int, nShotCount, ShotCount);
	CC_SYNTHESIZE(MagnateEvent, m_event, event);
	CC_SYNTHESIZE(int, nNowLevel, nowLevel);
};

#endif
