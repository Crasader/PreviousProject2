#include "game/mahjong/player/PlayerRight.h"

bool PlayerRight::init(){
	if (!PlayerBase::init()){

		return false;
	}
	count = 0;
	drawHandJong();
	addCoustomListener();
	return true;
}


void PlayerRight::drawHandJong(){
	for (int i = 0; i < this->jongNum; i++)
	{
		Jong* jong = Jong::create();
		jong->showJong(8, -1);
		jong->setPosition(ccp(RIGHT_POS_X, RIGHT_POS_Y - 25 * i));
		this->addChild(jong,2);
	}
}


void PlayerRight::playerTurn(){
	Jong* jong = Jong::create();
	jong->showJong(8, -11);
	jong->setPosition(ccp(RIGHT_POS_X, RIGHT_POS_Y +45));
	this->addChild(jong,1);
	MoveTo* move = MoveTo::create(0.2f, ccp(RIGHT_POS_X, RIGHT_POS_Y+25));
	ActionInterval* dou = EaseBackInOut::create(move);
	jong->runAction(dou);
}

void PlayerRight::drawPlayedJong(int ctype){
	Jong* jong = Jong::create();
	jong->showJong(5, ctype);
	jong->setPosition(ccp(RIGHT_POS_X, RIGHT_POS_Y + 25));
	int tar = count % 6;
	this->addChild(jong, 6 - tar);
	//贝塞尔移动
	log("POINT : x= %f,y=%f", getPlayedJongPos().x, getPlayedJongPos().y);
	Point startPoint = Point(RIGHT_POS_X, RIGHT_POS_Y + 25);
	Point endPoint = getPlayedJongPos();
	ccBezierConfig bezier; // 创建贝塞尔曲线  
	bezier.controlPoint_1 = startPoint; // 起始点  
	bezier.controlPoint_2 = Point(startPoint.x + (endPoint.x - startPoint.x) * 0.5,
		startPoint.y + (endPoint.y - startPoint.x)*0.5); //控制点
	bezier.endPosition = endPoint; // 结束位置    
	BezierTo *actionMove = BezierTo::create(0.5f, bezier);
	jong->runAction(actionMove);

}

void PlayerRight::drawCurrent(){
	Sprite* bg = Sprite::create("gamemj/jong_show.png");
	bg->setPosition(ccp(265, 330));
	this->addChild(bg);
	Jong* jong = Jong::create();
	jong->showJong(0, 11);
	//log("POINT : x= %f,y=%f", getPlayedJongPos().x, getPlayedJongPos().y);
	jong->setPosition(ccp(265, 330));
	this->addChild(jong);
}


void PlayerRight::drawHuaJong(int cType){


}


Point PlayerRight::getPlayedJongPos(){
	//计算当前玩家的出牌位置,起始点ccp(375,165)
	int row = count / 6;
	int line = count % 6;
	Point originPos = Point(580, 260);
	if (row == 0) {
		return Point(originPos.x, originPos.y + 25 * line);
	}
	else if (row == 1) {
		return Point(originPos.x + 29, originPos.y + 25 * line);
	}
	else {
		return Point(originPos.x + 29 * 2, originPos.y + 25 * line);
	}
}








void PlayerRight::addCoustomListener(){
	auto dealJongListener = EventListenerCustom::create("player_turn",
		[=](EventCustom* event) {
		playerTurn();
		drawPlayedJong(11);
		drawCurrent();
		count++;
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(
		dealJongListener, 1);

}

