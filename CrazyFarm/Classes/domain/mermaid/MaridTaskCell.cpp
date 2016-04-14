#include "MaridTaskCell.h"
#include "utill/AnimationUtil.h"

MaridTaskCell* MaridTaskCell::create(int fishid, int totalnum)
{
	MaridTaskCell *pRet = new MaridTaskCell();
	if (pRet && pRet->init(fishid, totalnum))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
bool MaridTaskCell::init(int fishid, int totalnum)
{
	if (!Sprite::initWithFile("maridtaskframe_1.png"))
	{
		return false;
	}
	bool bRet = false;
	do
	{ 
		setfishid(fishid);
		_totalnum = totalnum;
		auto size = getContentSize();

		auto str = String::createWithFormat("%d.png", getfishid());
		auto sp = Sprite::createWithSpriteFrameName(str->getCString());
		sp->setPosition(43, size.height/2);
		addChild(sp,1);

		auto label = LabelAtlas::create("0", "taskNum.png", 16, 22, '0');
		label->setPosition(105, size.height/2+1);
		label->setAnchorPoint(Point::ANCHOR_MIDDLE);
		addChild(label,1);
		
		label->setName("_curnum");
		str = String::createWithFormat(":%d", totalnum);
		auto label1 = LabelAtlas::create(str->getCString(), "nextPoolNum.png", 11, 19, '0');
		label1->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
		label1->setPosition(label->getPosition() + label->getContentSize() / 2);
		addChild(label1,1);
		bRet = true;
	} while (0);


	return bRet;
}

void MaridTaskCell::addfish()
{
	_curnum++;
	if (_curnum>=_totalnum)
	{
		onFinish();
		_curnum = _totalnum;
	}
	auto label = (LabelAtlas*)getChildByName("_curnum");
	label->setString(Value(_curnum).asString());
}
void MaridTaskCell::onFinish()
{
	if (isFinish)
	{
		return;
	}
	auto sp = Sprite::create();
	sp->runAction(Sequence::create(AnimationUtil::getInstance()->getAnimate("aniMaridLight"), CallFunc::create([=]{setTexture("maridtaskframe_2.png"); }),RemoveSelf::create(true), nullptr));
	sp->setPosition(getContentSize() / 2);
	addChild(sp);
		isFinish = true;


}