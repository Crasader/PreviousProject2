#include "game/mahjong/player/PlayerRight.h"

bool PlayerRight::init(){
	if (!Sprite::init()){

		return false;
	}
	//ͷ��Ļ���
	HeadPortrait* head = new HeadPortrait();
	drawHeadPortrait(head);
	return true;
}


//������ҵ�ͷ��
void PlayerRight::drawHeadPortrait(HeadPortrait* headPortrait){
	//���Ʊ���
	Sprite* head_bg = Sprite::create("headportrait/touxiangheidi.png");
	head_bg->setScale(0.5);
	head_bg->setPosition(ccp(910, 360));
	this->addChild(head_bg);
}