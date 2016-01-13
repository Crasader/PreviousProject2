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

void BagCell::setValue(BagItem item)
{
	if (item.itemId==-1)
	{
		propSprite->setVisible(false);
		propNum->setVisible(false);
		return;
	}
	setpropID(item.itemId);
	setpropNum(item.num);
	auto spPath = String::createWithFormat("item_%d.png", item.itemId);
	propSprite->setTexture(spPath->getCString());
	propNum->setString(Value(item.num).asString().c_str());
}

void BagCell::IsBeToued()
{
	///TODO:���߱����ʱ��Ļص�;
	CCLOG("propIDl: %d is be touched", m_nCellId);
}