#include "showTurretCell.h"
#include "utill/Chinese.h"
#include "config/ConfigTurrent.h"
bool showTurretCell::init(){

	auto bg = Sprite::create("ShowPaobg.png");
	bg->setPosition(88, 121.5);
	addChild(bg);
	auto size = bg->getContentSize();

	propSprite = Sprite::create();
	propSprite->setPosition(size / 2);
	addChild(propSprite);

	ShowPaoshade = Sprite::create("ShowPaoshade.png");
	ShowPaoshade->setAnchorPoint(Point::ZERO);
	ShowPaoshade->setPosition(0, 0);
	addChild(ShowPaoshade);


	
	muptleTTF = LabelAtlas::create("0", "unLockNumTTF.png", 13, 19, '0');
	muptleTTF->setAnchorPoint(Point::ANCHOR_MIDDLE);
	muptleTTF->setPosition(size.width*0.55, size.height*0.9);
	addChild(muptleTTF);

	

	button = MenuItemImage::create();
	button->setContentSize(Size(161, 74));
	button->setPosition(size.width / 2, size.height*0.13);
	button->setCallback(CC_CALLBACK_1(showTurretCell::ButtonCallback,this));
	auto diamondNumTTF = LabelAtlas::create("0", "unLockNumTTF.png", 13, 19, '0');
	diamondNumTTF->setPosition(Point::ANCHOR_MIDDLE);
	diamondNumTTF->setPosition(button->getContentSize()/2);
	button->addChild(diamondNumTTF,1,10);

	auto menu = Menu::create(button, nullptr);
	menu->setPosition(0, 0);
	addChild(menu);
	lockSp = Sprite::create();
	lockSp->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
	lockSp->setPosition(size.width -5, size.height);
	addChild(lockSp);



	return true;
}



void showTurretCell::setMultipleValue(int index)
{
	auto turret = ConfigTurrent::getInstance()->getTurrentByIndex(index);
	muptleTTF->setString(Value(turret.multiple).asString().c_str());
}
void showTurretCell::setVippaoValue(int index)
{

}


void showTurretCell::IsBeToued()
{

}

void showTurretCell::ButtonCallback(Ref* psend)
{

}