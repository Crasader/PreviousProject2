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
		auto txt = String::createWithFormat(":%d", propNum);
		auto num = LabelAtlas::create(txt->getCString(), "turntableCellNum.png", 15, 23, '0');
		num->setAnchorPoint(Point::ANCHOR_MIDDLE);
		num->setPosition(getContentSize().width*0.5, getContentSize().height*-0.05);
		addChild(num);
		bRet = true;
	}
	return bRet;
}

