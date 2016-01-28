#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_
#include "cocos2d.h"
#include "domain/magnate/MagnateManager.h"
#include "config/ConfigTurrent.h"
#include "domain/mermaid/MermaidTask.h"
using namespace cocos2d;

class GameData {
public:
	static GameData* getInstance();
	Turrent getTurrentData();
	void setSoundState(bool state);
	bool getSoundState();
	void setMusicState(bool state);
	bool getMusicState();
private:
	GameData();
	void init();
	static GameData* _instance;
	CC_SYNTHESIZE(int, nRoomId, RoomID);
	CC_SYNTHESIZE(int, nShotCount, ShotCount);
	CC_SYNTHESIZE(MagnateEvent, m_event, event);
	CC_SYNTHESIZE(MagnateEvent, m_propevent, propevent);
	CC_SYNTHESIZE(int, nNowLevel, nowLevel);
	CC_SYNTHESIZE(MermaidTask*, m_Task, mermaidTask);
	CC_SYNTHESIZE(bool, isOnMaridTask, IsOnMaridTask);
	CC_SYNTHESIZE(bool, bIsOnBankrupt, isOnBankrupt);
	CC_SYNTHESIZE(bool, bisPlayerOneGame, isPlayerOneGame);//是否进行过一次游戏
};

#endif
