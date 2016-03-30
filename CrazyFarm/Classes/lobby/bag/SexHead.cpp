#include "SexHead.h"


SexHead* SexHead::create(int sex, int isChoose)
{
	auto head = new SexHead();
	if (head->init(sex,isChoose)&&head)
	{
		head->autorelease();
	}
	else
	{
		head = nullptr;
	}
	return head;

}

bool SexHead::init(int sex, int isChoose)
{
	if (sex)
	{
		initWithFile("bagFamale.png");
	}
	else
	{
		initWithFile("bagMale.png");
	}
	auto sp = Sprite::create("sexChooseFlag.png");
	sp->setPosition(80, 28);
	addChild(sp,0,10);
	if (isChoose)
	{
		setIsChoose(true);
	}
	else
	{
		setIsChoose(false);
	}
	return true;
}
void SexHead::setIsChoose(bool isChoose)
{
	getChildByTag(10)->setVisible(isChoose);
	if (isChoose)
	{
		setScale(1.0);
	}
	else
	{
		setScale(0.8);
	}
}