#include "game/mahjong/player/PlayerLeft.h"
bool PlayerLeft::init(){
	if (!Sprite::init()){
	
		return false;
	}
	//ͷ��Ļ���
	HeadPortrait* head = new HeadPortrait();
	drawHeadPortrait(head);
	return true;
}



//������ҵ�ͷ��
void PlayerLeft::drawHeadPortrait(HeadPortrait* headPortrait){
	//���Ʊ���
	Sprite* head_bg = Sprite::create("headportrait/touxiangheidi.png");
	head_bg->setScale(0.5);
	head_bg->setPosition(ccp(50, 360));
	this->addChild(head_bg);
}

