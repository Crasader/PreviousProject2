#include "game/mahjong/otherplayer/PlayerLeft.h"
bool PlayerLeft::init(){
	if (!Sprite::init()){
	
		return false;
	}
	//ͷ��Ļ���
	PlayerInfo* head = new PlayerInfo();
	drawHeadPortrait(head);
	return true;
}



//������ҵ�ͷ��
void PlayerLeft::drawHeadPortrait(PlayerInfo* headPortrait){
	//���Ʊ���
	Sprite* head_bg = Sprite::create("gamemj/head_bg.png");
	head_bg->setPosition(ccp(50, 360));
	this->addChild(head_bg);
}

