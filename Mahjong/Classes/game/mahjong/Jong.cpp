#include "game/mahjong//Jong.h"

bool Jong::init(){
	if (!Node::init()){
		return false;
	}
	backGround = Sprite::create();
	this->addChild(backGround);
	content = Sprite::create();
	this->addChild(content);
	return true;
}

void Jong::showJong(int bType, int cType){
	this->setBType(bType);
	drawBackGround(bType);
	drawContent(cType);
	this->setJongType(cType);
}

Rect Jong::getJongBoundingBox(){
	Rect rect;
	//CCLOG("scale = %f",getScale());
	//CCLOG("width = %f", content->getBoundingBox().size.width);
	rect.setRect(this->getPositionX() - content->getBoundingBox().size.width  * getScale() / 2,
		this->getPositionY() - content->getBoundingBox().size.height  * getScale() / 2,
		content->getBoundingBox().size.width  * getScale(),
		content->getBoundingBox().size.height  * getScale());
	return rect;
}



void Jong::drawBackGround(int bType){
	switch (bType)
	{
	case 0:
		backGround->setTexture("gamemj/xiali.png");
		break;
	case 1:
		backGround->setTexture("gamemj/xiatang2.png");
		break;
	case 2:
		backGround->setTexture("gamemj/xiatang2.png");
		break;
	default:
		break;
	}
	
}


void Jong::drawContent(int cType){
	setJongScale(this->getBType());
	setJongPosition(this->getBType());
	switch (cType)
	{
	case JongEnum::wan_1:
		content->setTexture("jongs/wan_1.png");
		break;
	case JongEnum::wan_2:
		content->setTexture("jongs/wan_2.png");
		break;
	case JongEnum::wan_3:
		content->setTexture("jongs/wan_3.png");
		break;
	case JongEnum::wan_4:
		content->setTexture("jongs/wan_4.png");
		break;
	case JongEnum::wan_5:
		content->setTexture("jongs/wan_5.png");
		break;
	case JongEnum::wan_6:
		content->setTexture("jongs/wan_6.png");
		break;
	case JongEnum::wan_7:
		content->setTexture("jongs/wan_7.png");
		break;
	case JongEnum::wan_8:
		content->setTexture("jongs/wan_8.png");
		break;
	case JongEnum::wan_9:
		content->setTexture("jongs/wan_9.png");
		break;
	case JongEnum::tong_1:
		content->setTexture("jongs/tong_1.png");
		break;
	case JongEnum::tong_2:
		content->setTexture("jongs/tong_2.png");
		break;
	case JongEnum::tong_3:
		content->setTexture("jongs/tong_3.png");
		break;
	case JongEnum::tong_4:
		content->setTexture("jongs/tong_4.png");
		break;
	case JongEnum::tong_5:
		content->setTexture("jongs/tong_5.png");
		break;
	case JongEnum::tong_6:
		content->setTexture("jongs/tong_6.png");
		break;
	case JongEnum::tong_7:
		content->setTexture("jongs/tong_7.png");
		break;
	case JongEnum::tong_8:
		content->setTexture("jongs/tong_8.png");
		break;
	case JongEnum::tong_9:
		content->setTexture("jongs/tong_9.png");
		break;
	default:
		break;
	}
}


void Jong::setJongScale(int bType){
	if (bType == 2){
		content->setScale(0.5f);
	}
}


void Jong::setJongPosition(int bType){
	if (bType == 2){
		content->setPosition(ccp(backGround->getPosition().x, backGround->getPosition().y));
	}
	else{
		content->setPosition(ccp(backGround->getPosition().x, backGround->getPosition().y - 10));
	
	}
}