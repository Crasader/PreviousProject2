#include "game/mahjong/player/PlayerRight.h"

bool PlayerRight::init(){
	if (!PlayerBase::init()){

		return false;
	}
	drawHandJong();
	return true;
}

void PlayerRight::drawHandJong(){
	//TODO gamemj/zuoli.png
	for (int i = 0; i < this->jongNum; i++)
	{
		Sprite* jongs = Sprite::create("gamemj/youli.png");
		jongs->setPosition(ccp(RIGHT_POS_X, RIGHT_POS_Y - 25 * i));
		this->addChild(jongs);
	}
}

