#include "game/mahjong/otherplayer/PlayerOpposite.h"

bool PlayerOpposite::init(){
	if (!PlayerSprite::init()){

		return false;
	}
	//ͷ��Ļ���
	PlayerInfo* head = new PlayerInfo();
	this->drawHeadPortrait(head);
	this->setHeadPostion(ccp(300, 460));
	return true;
}