#include "game/mahjong/otherplayer/PlayerRight.h"

bool PlayerRight::init(){
	if (!Sprite::init()){

		return false;
	}
	//ͷ��Ļ���
	PlayerInfo* head = new PlayerInfo();
	drawHeadPortrait(head);
	return true;
}


//������ҵ�ͷ��
void PlayerRight::drawHeadPortrait(PlayerInfo* headPortrait){
	//���Ʊ���
	Sprite* head_bg = Sprite::create("gamemj/head_bg.png");
	head_bg->setPosition(ccp(910, 360));
	this->addChild(head_bg);
}