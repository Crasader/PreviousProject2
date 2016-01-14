#include "game/mahjong/player/base/PlayerBase.h"

bool PlayerBase::init(){
	if (!Layer::init()){
		return false;
	}
	return true;
}

void PlayerBase::drawHeadPortrait(PlayerInfo* playerInfo){
	//»æÖÆ±³¾°
	head_bg = Sprite::create("gamemj/head_bg.png");
	this->addChild(head_bg);
	//»æÖÆêÇ³Æ
	nickName = Label::create("Monkey", "Arial", 16);
	this->addChild(nickName);
	//»æÖÆÍ¼Æ¬
	headimage = Sprite::create("gamemj/head_4.png");
	this->addChild(headimage);
	//»æÖÆ×êÊ¯
	diamond = Sprite::create("gamemj/diamond.png");
	this->addChild(diamond);
	//»æÖÆÊý×Ö
	diamondNum = LabelAtlas::create("123", "gamemj/diamond_num.png", 8, 11, '0');
	this->addChild(diamondNum);
}


void PlayerBase::setHeadPostion(Point pos){
	head_bg->setPosition(pos);
	nickName->setPosition(ccp(pos.x,pos.y+50));
	headimage->setPosition(pos);
	diamond->setPosition(ccp(pos.x-28, pos.y - 50));
	diamondNum->setPosition(ccp(pos.x - 18, pos.y - 55));
}