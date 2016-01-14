#include "game/mahjong/otherplayer/PlayerOpposite.h"

bool PlayerOpposite::init(){
	if (!PlayerSprite::init()){

		return false;
	}
	//Í·ÏñµÄ»æÖÆ
	PlayerInfo* head = new PlayerInfo();
	this->drawHeadPortrait(head);
	drawHandJong();
	return true;
}

void PlayerOpposite::drawHandJong(){
	for (int i = 0; i < this->jongNum; i++)
	{
		Sprite* jongs = Sprite::create("gamemj/shangli.png");
		jongs->setPosition(ccp(OPPOSITE_POS_X +31 * i, OPPOSITE_POS_Y));
		this->addChild(jongs);
	}
}