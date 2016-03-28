#include "data/GAMESTATE.h"
#include "cocos2d.h"
using namespace cocos2d;

GAMESTATE* GAMESTATE::_instance = 0;

GAMESTATE::GAMESTATE() {

}

void GAMESTATE::init() {

}


GAMESTATE* GAMESTATE::getInstance() {
	if (_instance == 0) {
		_instance = new GAMESTATE();
	}
	return _instance;
}

