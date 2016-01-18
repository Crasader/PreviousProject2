#include "game/mahjong/player/PlayerOpposite.h"

bool PlayerOpposite::init(){
	if (!PlayerBase::init()){

		return false;
	}
	count = 0;
	drawHandJong();
	addCoustomListener();
	return true;
}


void PlayerOpposite::drawHandJong(){
	for (int i = 0; i < this->jongNum; i++)
	{
		Jong* jong = Jong::create();
		jong->showJong(6, -1);
		jong->setPosition(ccp(OPPOSITE_POS_X + 31 * i, OPPOSITE_POS_Y));
		this->addChild(jong);
	}
}


void PlayerOpposite::playerTurn(){
	Jong* jong = Jong::create();
	jong->showJong(6, -1);
	jong->setPosition(ccp(OPPOSITE_POS_X-31, OPPOSITE_POS_Y + 20));
	this->addChild(jong);
	MoveTo* move = MoveTo::create(0.2f, ccp(OPPOSITE_POS_X - 31, OPPOSITE_POS_Y));
	ActionInterval* dou = EaseBackInOut::create(move);
	jong->runAction(dou);
}

void PlayerOpposite::drawPlayedJong(int ctype){
	Jong* jong = Jong::create();
	jong->showJong(7, ctype);
	jong->setPosition(ccp(OPPOSITE_POS_X - 31, OPPOSITE_POS_Y));
	if (count / 6 == 0){
		this->addChild(jong, 3);
	}
	else if (count / 6 == 1){
		this->addChild(jong, 2);
	}
	else{
		this->addChild(jong, 1);
	}
	//贝塞尔移动
	Point startPoint = ccp(OPPOSITE_POS_X - 31, OPPOSITE_POS_Y);
	Point endPoint = getPlayedJongPos();
	log("POINT : x= %f,y=%f", getPlayedJongPos().x, getPlayedJongPos().y);
	ccBezierConfig bezier; // 创建贝塞尔曲线  
	bezier.controlPoint_1 = startPoint; // 起始点  
	bezier.controlPoint_2 = ccp(startPoint.x + (endPoint.x - startPoint.x) * 0.5,
		startPoint.y + (endPoint.y - startPoint.x)*0.5); //控制点
	bezier.endPosition = endPoint; // 结束位置    
	BezierTo *actionMove = BezierTo::create(0.5f, bezier);
	jong->runAction(actionMove);

}

void PlayerOpposite::drawCurrent(){
	Sprite* bg = Sprite::create("gamemj/jong_show.png");
	Point pos = Point(480, 450);
	bg->setPosition(pos);
	this->addChild(bg,4);
	Jong* jong = Jong::create();
	jong->showJong(0, 11);
	//log("POINT : x= %f,y=%f", getPlayedJongPos().x, getPlayedJongPos().y);
	jong->setPosition(pos);
	this->addChild(jong,4);
}


void PlayerOpposite::drawHuaJong(int cType){


}


Point PlayerOpposite::getPlayedJongPos(){
	//计算当前玩家的出牌位置,起始点ccp(375,165)
	int row = count / 6;
	int line = count % 6;
	Point originPos = ccp(550, 400);
	if (row == 0) {
		return ccp(originPos.x - 25 * line, originPos.y);
	}
	else if (row == 1) {
		return ccp(originPos.x - 25 * line, originPos.y+30);
	}
	else {
		return ccp(originPos.x - 25 * line, originPos.y+30*2);
	}
}




void PlayerOpposite::addCoustomListener(){
	auto dealJongListener = EventListenerCustom::create("player_turn",
		[=](EventCustom* event) {
		//playerTurn();
		//drawPlayedJong(11);
		//drawCurrent();
		//count++;
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(
		dealJongListener, 1);

}