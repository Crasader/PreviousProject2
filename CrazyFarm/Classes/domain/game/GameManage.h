#pragma once

#include "cocos2d.h"
#include "core/GameLayer.h"
#include "core/GameGuiLayer.h"
using namespace cocos2d;


class GameManage {
public:
	static GameManage* getInstance();
	void setGuilayer(GameGuiLayer* guilayer){ m_pGuilayer = guilayer; };
	void  setGameyer(GameLayer* layer){ m_pGameyer = layer; };

	GameGuiLayer* getGuiLayer(){
		return m_pGuilayer;
	}
	GameLayer* getGameLayer(){
		return m_pGameyer;
	}
	
	//������ʯ
	void showLockTurrent();
private :
	GameManage();
	static GameManage* _instance;
	GameGuiLayer* m_pGuilayer;
	GameLayer*m_pGameyer;
 };