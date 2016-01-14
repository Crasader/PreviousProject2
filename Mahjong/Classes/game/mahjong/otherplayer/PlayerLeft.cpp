#include "game/mahjong/otherplayer/PlayerLeft.h"
bool PlayerLeft::init(){
	if (!PlayerSprite::init()){
	
		return false;
	}
	//Í·ÏñµÄ»æÖÆ
	PlayerInfo* head = new PlayerInfo();
	drawHeadPortrait(head);
	drawHandJong();
	return true;
}


void PlayerLeft::drawHandJong(){
	//TODO gamemj/zuoli.png
	for (int i = 0; i < this->jongNum; i++)
	{
		Sprite* jongs = Sprite::create("gamemj/zuoli.png");
		jongs->setPosition(ccp(LEFT_POS_X, LEFT_POS_Y - 25 * i));
		this->addChild(jongs);
	}
}



void PlayerLeft::drawPlayedJong(){
	//TODO




}


void getPlayedJongPos(){
	//TODO


}