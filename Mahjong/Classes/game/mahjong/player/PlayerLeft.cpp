#include "game/mahjong/player/PlayerLeft.h"
bool PlayerLeft::init(){
	if (!Sprite::init()){
	
		return false;
	}
	//头像的绘制
	HeadPortrait* head = new HeadPortrait();
	drawHeadPortrait(head);
	return true;
}



//绘制玩家的头像
void PlayerLeft::drawHeadPortrait(HeadPortrait* headPortrait){
	//绘制背景
	Sprite* head_bg = Sprite::create("headportrait/touxiangheidi.png");
	head_bg->setScale(0.5);
	head_bg->setPosition(ccp(50, 360));
	this->addChild(head_bg);
}

