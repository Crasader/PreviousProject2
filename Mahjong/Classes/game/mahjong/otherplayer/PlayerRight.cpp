#include "game/mahjong/otherplayer/PlayerRight.h"

bool PlayerRight::init(){
	if (!Sprite::init()){

		return false;
	}
	//Í·ÏñµÄ»æÖÆ
	PlayerInfo* head = new PlayerInfo();
	this->drawHeadPortrait(head);
	this->setHeadPostion(ccp(910, 360));
	return true;
}

