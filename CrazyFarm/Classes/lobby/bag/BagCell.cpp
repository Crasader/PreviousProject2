#include "BagCell.h"

bool BagCell::init(){
	if (!Sprite::initWithFile("bagbox.png")){
		return false;
	}
	auto size = getContentSize();
	propSprite = Sprite::create();
	propSprite->setPosition(size / 2);
	addChild(propSprite);

	propNum = LabelAtlas::create("0", "bagPropNum.png", 18, 26, '0');
	propNum->setPosition(size.width*0.7, size.height*0.1);
	addChild(propNum);
	return true;
}

void BagCell::setValue(int propId, int num)
{
	setpropID(propId);
	setpropNum(num);
	auto spPath = String::createWithFormat("prop_%d.png", propId);
	propSprite->setTexture(spPath->getCString());
	propNum->setString(Value(num).asString().c_str());
}

void BagCell::IsBeToued()
{
	///TODO:道具被点击时候的回调;
	CCLOG("propIDl: %d is be touched", m_nCellId);
}