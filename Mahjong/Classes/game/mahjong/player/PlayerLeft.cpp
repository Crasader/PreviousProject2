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


void PlayerLeft::playerTurn(){
	Jong* jong = Jong::create();
	jong->showJong(4, -1);
	jong->setPosition(ccp(LEFT_POS_X, LEFT_POS_Y - 320));
	this->addChild(jong);
	MoveTo* move = MoveTo::create(0.2f, ccp(LEFT_POS_X, LEFT_POS_Y - 340));
	ActionInterval* dou = EaseBackInOut::create(move);
	jong->runAction(dou);
}

void PlayerLeft::drawPlayedJong(int ctype){
	Jong* jong = Jong::create();
	jong->showJong(5, ctype);
	//log("POINT : x= %f,y=%f", getPlayedJongPos().x, getPlayedJongPos().y);
	jong->setPosition(ccp(LEFT_POS_X, LEFT_POS_Y - 340));
	this->addChild(jong);
	//贝塞尔移动
	Point startPoint = ccp(LEFT_POS_X, LEFT_POS_Y - 340);
	Point endPoint = getPlayedJongPos();
	ccBezierConfig bezier; // 创建贝塞尔曲线  
	bezier.controlPoint_1 = startPoint; // 起始点  
	bezier.controlPoint_2 = ccp(startPoint.x + (endPoint.x - startPoint.x) * 0.5,
		startPoint.y + (endPoint.y - startPoint.x)*0.5); //控制点
	bezier.endPosition = endPoint; // 结束位置    
	BezierTo *actionMove = BezierTo::create(0.5f, bezier);
	jong->runAction(actionMove);

}

void PlayerLeft::drawCurrent(){
	Sprite* bg = Sprite::create("gamemj/jong_show.png");
	bg->setPosition(ccp(265, 330));
	this->addChild(bg);
	Jong* jong = Jong::create();
	jong->showJong(0, 11);
	//log("POINT : x= %f,y=%f", getPlayedJongPos().x, getPlayedJongPos().y);
	jong->setPosition(ccp(265,330));
	this->addChild(jong);
}


void PlayerLeft::drawHuaJong(int cType){


}


Point PlayerLeft::getPlayedJongPos(){
	//计算当前玩家的出牌位置,起始点ccp(375,165)
	int row = count / 6;
	int line = count % 6;
	Point originPos = ccp(375, 370);
	if (row == 0) {
		return ccp(originPos.x, originPos.y - 25 * line);
	}
	else if (row == 1) {
		return ccp(originPos.x - 29, originPos.y - 25 * line);
	}
	else {
		return ccp(originPos.x - 29 * 2, originPos.y - 25 * line);
	}
}








void PlayerLeft::addCoustomListener(){
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