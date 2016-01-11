#include "game/mahjong/otherplayer/PlayerOpposite.h"

bool PlayerOpposite::init(){
	if (!Sprite::init()){

		return false;
	}
	//ͷ��Ļ���
	PlayerInfo* head = new PlayerInfo();
	drawHeadPortrait(head);
	return true;
}


//������ҵ�ͷ��
void PlayerOpposite::drawHeadPortrait(PlayerInfo* headPortrait){
	//���Ʊ���
	Sprite* head_bg = Sprite::create("gamemj/head_bg.png");
	head_bg->setPosition(ccp(300, 460));
	this->addChild(head_bg);
}