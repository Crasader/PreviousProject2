#include "ActiveCell.h"
#include "domain/UrlImage/UrlImageMannger.h"
bool ActiveCell::init(){

	bg = Sprite::create();
	bg->setAnchorPoint(Point::ZERO);
	bg->setPosition(0,0);
	addChild(bg);
	return true;
}


void ActiveCell::setImg(std::string path)
{
	bg->setTexture(UrlImageMannger::getInstance()->getImgNameByUrl(path));
}
