#include "VipCell.h"

bool VipCell::init(){

	auto bg = Sprite::create("VIPFrame.png");
	bg->setPosition(88, 121.5);
	addChild(bg);
	auto size = bg->getContentSize();

	propSprite = Sprite::create();
	propSprite->setPosition(size / 2);
	addChild(propSprite);

	auto bottomFrame = Sprite::create("VIPbottomFrame.png");
	bottomFrame->setAnchorPoint(Point::ZERO);
	bottomFrame->setPosition(0, 0);
	addChild(bottomFrame);


	 VIPtitle = Sprite::create("VIP.png");
	VIPtitle->setPosition(size.width*0.47, size.height*0.8);
	addChild(VIPtitle);
	
	VIPTTF = LabelAtlas::create("0", "VIPnum.png", 31, 43, '0');
	VIPTTF->setPosition(size.width*0.75, size.height*0.8);
	addChild(VIPTTF);



	VIPname = Sprite::create();
	VIPname->setPosition(size.width / 2, size.height*0.23);
	addChild(VIPname);

	VIPdec = Sprite::create();
	VIPdec->setPosition(size.width *0.51, size.height*0.1);
	addChild(VIPdec);
	


	return true;
}

void VipCell::setValue(int vipLevel)
{
	auto spPath = String::createWithFormat("turret/pao_%d.png", vipLevel);
	propSprite->setTexture(spPath->getCString());
	spPath = String::createWithFormat("VIPname_%d.png", vipLevel);
	VIPname->setTexture(spPath->getCString());
	spPath = String::createWithFormat("VIPdec_%d.png", vipLevel);
	VIPdec->setTexture(spPath->getCString());

	VIPTTF->setString(Value(vipLevel).asString().c_str());
}

void VipCell::IsBeToued()
{


}