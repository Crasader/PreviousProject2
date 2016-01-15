#include "game/mahjong/player/PlayerOpposite.h"

bool PlayerOpposite::init(){
	if (!PlayerBase::init()){

		return false;
	}
	drawHandJong();
	return true;
}


void PlayerOpposite::drawHandJong(){
	for (int i = 0; i < this->jongNum; i++)
	{
		Jong* jong = Jong::create();
		jong->showJong(4, -1);
		jong->setPosition(ccp(OPPOSITE_POS_X, OPPOSITE_POS_Y - 25 * i));
		this->addChild(jong);
	}
}


void PlayerOpposite::playerTurn(){
	Jong* jong = Jong::create();
	jong->showJong(4, -1);
	jong->setPosition(ccp(OPPOSITE_POS_X, OPPOSITE_POS_Y - 320));
	this->addChild(jong);
	MoveTo* move = MoveTo::create(0.2f, ccp(OPPOSITE_POS_X, OPPOSITE_POS_Y - 340));
	ActionInterval* dou = EaseBackInOut::create(move);
	jong->runAction(dou);
}

void PlayerOpposite::drawPlayedJong(int ctype){
	Jong* jong = Jong::create();
	jong->showJong(5, ctype);
	//log("POINT : x= %f,y=%f", getPlayedJongPos().x, getPlayedJongPos().y);
	jong->setPosition(ccp(OPPOSITE_POS_X, OPPOSITE_POS_Y - 340));
	this->addChild(jong);
	//贝塞尔移动
	Point startPoint = ccp(OPPOSITE_POS_X, OPPOSITE_POS_Y - 340);
	Point endPoint = getPlayedJongPos();
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
	bg->setPosition(ccp(265, 330));
	this->addChild(bg);
	Jong* jong = Jong::create();
	jong->showJong(0, 11);
	//log("POINT : x= %f,y=%f", getPlayedJongPos().x, getPlayedJongPos().y);
	jong->setPosition(ccp(265, 330));
	this->addChild(jong);
}


void PlayerOpposite::drawHuaJong(int cType){


}


Point PlayerOpposite::getPlayedJongPos(){
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