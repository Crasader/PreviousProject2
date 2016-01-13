#include "game/mahjong/otherplayer/PlayerSprite.h"

bool PlayerSprite::init(){
	if (!Sprite::init()){
		return false;
	}
	return true;
}

void PlayerSprite::drawHeadPortrait(PlayerInfo* playerInfo){
	//»æÖÆ±³¾°
	head_bg = Sprite::create("gamemj/head_bg.png");
	head_bg->setPosition(ccp(0, 0));
	this->addChild(head_bg);
}


void PlayerSprite::setHeadPostion(Point pos){
	head_bg->setPosition(pos);
}