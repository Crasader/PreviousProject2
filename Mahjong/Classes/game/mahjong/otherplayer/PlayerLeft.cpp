#include "game/mahjong/otherplayer/PlayerLeft.h"
bool PlayerLeft::init(){
	if (!PlayerSprite::init()){
	
		return false;
	}
	//ͷ��Ļ���
	PlayerInfo* head = new PlayerInfo();
	drawHeadPortrait(head);
	return true;
}

