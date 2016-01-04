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
	drawBackGround(bType);
	drawContent(cType);
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
	backGround->setTexture("gamemj/xiali.png");
}


void Jong::drawContent(int cType){

	switch (cType)
	{
	case JongEnum::wan_1:
		content->setTexture("majiang/yiwan.png");
		break;
	case JongEnum::wan_2:
		content->setTexture("majiang/erwan.png");
		break;
	case JongEnum::wan_3:
		content->setTexture("majiang/sanwan.png");
		break;
	case JongEnum::wan_4:
		content->setTexture("majiang/siwan.png");
		break;
	case JongEnum::wan_5:
		content->setTexture("majiang/wuwan.png");
		break;
	case JongEnum::wan_6:
		content->setTexture("majiang/liuwan.png");
		break;
	case JongEnum::wan_7:
		content->setTexture("majiang/qiwan.png");
		break;
	case JongEnum::wan_8:
		content->setTexture("majiang/bawan.png");
		break;
	case JongEnum::wan_9:
		content->setTexture("majiang/jiuwan.png");
		break;
	case JongEnum::tong_1:
		content->setTexture("majiang/yitong.png");
		break;
	case JongEnum::tong_2:
		content->setTexture("majiang/ertong.png");
		break;
	case JongEnum::tong_3:
		content->setTexture("majiang/santong.png");
		break;
	case JongEnum::tong_4:
		content->setTexture("majiang/sitong.png");
		break;
	case JongEnum::tong_5:
		content->setTexture("majiang/wutong.png");
		break;
	case JongEnum::tong_6:
		content->setTexture("majiang/liutong.png");
		break;
	case JongEnum::tong_7:
		content->setTexture("majiang/qitong.png");
		break;
	case JongEnum::tong_8:
		content->setTexture("majiang/batong.png");
		break;
	case JongEnum::tong_9:
		content->setTexture("majiang/jiutong.png");
		break;
	default:
		break;
	}
}
