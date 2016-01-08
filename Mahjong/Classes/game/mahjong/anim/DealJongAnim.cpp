#include "game/mahjong/anim/DealJongAnim.h"

bool DealJongAnim::init(){
	if (!Layer::init()){
	  
		return false;
	}
	initPosition();
	showDealJong();
	return true;
}

void DealJongAnim::showDealJong(){
	
	dealHero();

}

void DealJongAnim::initPosition(){
	 heroStarPos =  Point(300,100);
	 leftStarPos =  Point(300, 100);
	 rightStarPos =  Point(300, 100);
	 oppositeStarPos =  Point(300, 100);
}

void DealJongAnim::dealHero(){
	//step1 绘制发牌的牌组
	Sprite* pai1 = Sprite::create("gamemj/xiaogais.png");
	pai1->setPosition(ccp(0, 0));
	Sprite* pai2 = Sprite::create("gamemj/xiaogais.png");
	pai2->setPosition(ccp(50, 0));
	Sprite* pai3 = Sprite::create("gamemj/xiaogais.png");
	pai3->setPosition(ccp(0, 20));
	Sprite* pai4 = Sprite::create("gamemj/xiaogais.png");
	pai4->setPosition(ccp(50, 20));
	Sprite* total = Sprite::create();
	total->setScale(0.3f);
	total->setAnchorPoint(ccp(0, 0));
	total->setPosition(ccp(460, 260));
	total->addChild(pai1);
	total->addChild(pai2);
	total->addChild(pai3);
	total->addChild(pai4);
	this->addChild(total);
	ScaleTo* scale = ScaleTo::create(0.2f, 1.0f);
	MoveTo* move1 = MoveTo::create(0.2f, ccp(300, 100));
	Spawn* spawn1 = Spawn::create(scale, move1, NULL);
	total->runAction(spawn1);
}

Point DealJongAnim::caluMove2Pos(int type){
	if (type == JongDirection::hero){
	
	}
	else if (type == JongDirection::left){

	}
	else if (type == JongDirection::right){


	}
	else if (type == JongDirection::opposite){


	}else{	
		CCLOG("DealJongAnim -> caluMove2Pos : error");
	}


}