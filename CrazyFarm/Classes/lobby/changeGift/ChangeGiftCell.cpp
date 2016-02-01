#include "ChangeGiftCell.h"



bool ChangeGiftCell::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Sprite::initWithFile("changewardCellBg.png"));

		colorBg = Sprite::create("changewardCellFrame.png");
		colorBg->setPosition(getContentSize() / 2);
		addChild(colorBg, 1);

		giftCell = Sprite::create();
		giftCell->setPosition(getContentSize().width / 2, 130);
		addChild(giftCell);

		giftName = Sprite::create();
		giftName->setPosition(getContentSize().width / 2, 214);
		addChild(giftName);

		bt = MenuItemImage::create("btn_duihuan_1.png", "btn_duihuan_2.png", CC_CALLBACK_1(ChangeGiftCell::changeButtonCallback, this));
		bt->setPosition(getContentSize().width / 2, 60);
		auto menu = Menu::create(bt, nullptr);
		menu->setPosition(Point::ZERO);
		addChild(menu);
		setisSelected(false);
		scheduleUpdate();
		bRet = true;
	} while (0);

	return bRet;
}

void ChangeGiftCell::setValue(int type) //1:钻石 2：话费3：冰冻锁定
{
	m_type = type;
	auto str = String::createWithFormat("giftName_%d.png", m_type);
	giftName->setTexture(str->getCString());
	str = String::createWithFormat("giftItem_%d.png", m_type);
	giftCell->setTexture(str->getCString());
}

void ChangeGiftCell::update(float delta)
{
	if (m_isSelected)
	{
	/*	colorBg->setVisible(false);*/
		bt->setEnabled(true);
		colorBg->setVisible(false);
		setScale(1);
	}
	else
	{
		/*colorBg->setVisible(true);*/
		bt->setEnabled(false);
		colorBg->setVisible(true);
		setScale(0.7);
	}
}
void ChangeGiftCell::changeButtonCallback(Ref* psend)
{

}

