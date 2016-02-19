#include "TurntableCell.h"

TurntableCell* TurntableCell::create(int propID, int propNum)
{
	TurntableCell* bRet = new TurntableCell();
	if (bRet&&bRet->init(propID, propNum))
	{
		bRet->autorelease(); 
			return bRet; 
	}
	else 
	{ 
	  delete bRet; 
	  bRet = NULL; 
	  return NULL; 
	} 
}

bool TurntableCell::init(int propID, int propNum)
{
	auto spPath = String::createWithFormat("sign_%d.png", propID);
	initWithFile(spPath->getCString());
	bool bRet = false;
	while (!bRet)
	{

		auto num = LabelAtlas::create(Value(propNum).asString().c_str(),"prop_num.png", 19,23,'0');
		num->setScale(0.9);
		num->setAnchorPoint(Point::ANCHOR_MIDDLE);
		num->setPosition(getContentSize().width*0.5, getContentSize().height*-0.1);
		addChild(num);
		bRet = true;
	}
	return bRet;
}

