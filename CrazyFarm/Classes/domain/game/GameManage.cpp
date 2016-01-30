#include "domain/game/GameManage.h"

GameManage* GameManage::_instance = 0;

GameManage* GameManage::getInstance(){
	if (_instance == 0){
		_instance = new GameManage();
	}
	return _instance;
}

GameManage::GameManage(){

}
void GameManage::showLockTurrent()
{
	m_pGuilayer->showLockUpdataTurret();
}