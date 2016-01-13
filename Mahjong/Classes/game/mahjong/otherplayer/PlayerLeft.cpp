#include "game/mahjong/otherplayer/PlayerLeft.h"
bool PlayerLeft::init(){
	if (!PlayerSprite::init()){
	
		return false;
	}
	//Í·ÏñµÄ»æÖÆ
	PlayerInfo* head = new PlayerInfo();
	drawHeadPortrait(head);
	return true;
}


void PlayerLeft::drawHandJong(){
	//TODO gamemj/zuoli.png
	



}



void PlayerLeft::drawPlayedJong(){
	//TODO




}
