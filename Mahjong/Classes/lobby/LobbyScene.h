#ifndef __LOBBY_SCENE_H__
#define __LOBBY_SCENE_H__
#include "cocos2d.h"
#include "socket/ODSocket.h"
#include "utils/PositionInfoUtil.h"
USING_NS_CC;


class LobbyScene : public cocos2d::Scene
{
public:

    virtual bool init();

    void startGame();

	void connectServer();

	void receiveData();

    CREATE_FUNC(LobbyScene);
private:
	ODSocket socket;
};
#endif