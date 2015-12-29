#ifndef __LOBBY_SCENE_H__
#define __LOBBY_SCENE_H__
#include "cocos2d.h"

USING_NS_CC;


class LobbyScene : public cocos2d::Scene
{
public:

    virtual bool init();

    void startGame();

	void rechargeGold();

	void showSettingLayer();

	void autoStartGame(float dt);

	void updateScene(float dt);


    CREATE_FUNC(LobbyScene);
};
#endif