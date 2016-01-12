#include "VipCell.h"
#include "utill/Chinese.h"
bool VipCell::init(){

	auto bg = Sprite::create("VIPFrame.png");
	bg->setPosition(88, 142.5);
	addChild(bg);
	auto size = bg->getContentSize();

	propSprite = Sprite::create();
	propSprite->setPosition(size / 2);
	addChild(propSprite);

	auto bottomFrame = Sprite::create("VIPbottomFrame.png");
	bottomFrame->setAnchorPoint(Point::ZERO);
	bottomFrame->setPosition(0,41);
	addChild(bottomFrame);


	 VIPtitle = Sprite::create("VIPtxt.png");
	VIPtitle->setPosition(size.width*0.45, size.height*0.8+21);
	addChild(VIPtitle);
	
	VIPTTF = LabelAtlas::create("0", "VIPnum.png", 31, 43, '0');
	VIPTTF->setAnchorPoint(Point::ANCHOR_MIDDLE);
	VIPTTF->setPosition(size.width*0.75, size.height*0.8+21);
	addChild(VIPTTF);



	VIPname = Sprite::create();
	VIPname->setPosition(size.width / 2, size.height*0.23+36);
	addChild(VIPname);

	VIPdec = Sprite::create();
	VIPdec->setPosition(size.width *0.51, size.height*0.1+36);
	addChild(VIPdec);


	PriceDecTTF = LabelTTF::create("0", "arial", 20);
	PriceDecTTF->setPosition(size.width *0.51, size.height*0.1-10);
	addChild(PriceDecTTF);

	return true;
}

int VIPprice[9] = { 20, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000 };

void VipCell::setValue(int vipLevel)
{
	auto spPath = String::createWithFormat("turret/pao_%d.png", vipLevel);
	propSprite->setTexture(spPath->getCString());
	spPath = String::createWithFormat("VIPname_%d.png", vipLevel);
	VIPname->setTexture(spPath->getCString());
	spPath = String::createWithFormat("VIPdec_%d.png", vipLevel);
	VIPdec->setTexture(spPath->getCString());

	VIPTTF->setString(Value(vipLevel).asString().c_str());

	auto dec = String::createWithFormat(ChineseWord("priceVIPdes").c_str(), VIPprice[vipLevel]);
	PriceDecTTF->setString(dec->getCString());
}

void VipCell::IsBeToued()
{


}