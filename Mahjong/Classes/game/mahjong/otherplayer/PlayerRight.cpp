#include "game/mahjong/otherplayer/PlayerRight.h"

bool PlayerRight::init(){
	if (!Sprite::init()){

		return false;
	}
	//Í·ÏñµÄ»æÖÆ
	PlayerInfo* head = new PlayerInfo();
	this->drawHeadPortrait(head);
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