#include "game/mahjong/player/PlayerLeft.h"

bool PlayerLeft::init(){
	if (!PlayerBase::init()){
	
		return false;
	}
	count = 0;
	drawHandJong();
	addCoustomListener();
	return true;
}


void PlayerLeft::drawHandJong(){
	for (int i = 0; i < this->jongNum; i++)
	{
		Jong* jong = Jong::create();
		jong->showJong(4, -1);
		jong->setPosition(ccp(LEFT_POS_X, LEFT_POS_Y - 25 * i));
		this->addChild(jong);
	}
}



void PlayerLeft::drawPlayedJong(){
	




}



void PlayerLeft::drawHuaJong(){


}


Point PlayerLeft::getPlayedJongPos(){
	//计算当前玩家的出牌位置,起始点ccp(375,165)
	int row = count / 6;
	int line = count % 6;
	Point originPos = ccp(375, 165);
	if (row == 0) {
		return ccp(originPos.x, originPos.y + 27 * line);
	}
	else if (row == 1) {
		return ccp(originPos.x - 38, originPos.y + 27 * line);
	}
	else {
		return ccp(originPos.x - 38 * 2, originPos.y + 27 * line);
	}
}


void PlayerLeft::drawCurrent(){



}


void PlayerLeft::addCoustomListener(){
	auto dealJongListener = EventListenerCustom::create("player_turn",
		[=](EventCustom* event) {
		log("abc acb cba bacbbcab ");
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(
		dealJongListener, 1);

}