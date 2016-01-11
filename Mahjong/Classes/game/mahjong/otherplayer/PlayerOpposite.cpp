#include "game/mahjong/otherplayer/PlayerOpposite.h"

bool PlayerOpposite::init(){
	if (!Sprite::init()){

		return false;
	}
	//头像的绘制
	HeadPortrait* head = new HeadPortrait();
	drawHeadPortrait(head);
	return true;
}


//绘制玩家的头像
void PlayerOpposite::drawHeadPortrait(HeadPortrait* headPortrait){
	//绘制背景
	Sprite* head_bg = Sprite::create("gamemj/head_bg.png");
	head_bg->setPosition(ccp(300, 460));
	this->addChild(head_bg);
}