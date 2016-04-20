#include "EmailCell.h"
#include "utill/Chinese.h"
#include "EmailManager.h"
#include "domain/ToolTip/ToolTipMannger.h"
bool EmailCell::init(){

	auto bg = Sprite::create("emailcellBg.png");
	auto size = bg->getContentSize();
	bg->setPosition(size/2);
	addChild(bg,0,"bg");



	isReadIcon = Sprite::create();
	isReadIcon->setPosition(42, 30.5);
	bg->addChild(isReadIcon,2);

	isHaveReward = Sprite::create();
	isHaveReward->setPosition(293, 30.5);
	bg->addChild(isHaveReward,2);
	

	EmailTitle = Label::create("", "arial", 20);
	EmailTitle->setPosition(85, 30.5);
	bg->addChild(EmailTitle,2);
	EmailTitle->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);

	auto frame = Sprite::create("emailcellTouched.png");
	frame->setPosition(size / 2);
	bg->addChild(frame, 1,"frame");
	frame->setVisible(false);
	return true;
}
void EmailCell::setIsTouched(bool isTouched)
{
	getChildByName("bg")->getChildByName("frame")->setVisible(isTouched);
}
void EmailCell::setValue(EmailListItem item)
{
	_item = item;
	EmailTitle->setString(item.email_title);
	if (item.email_rewards.size()>0)
	{
		isHaveReward->setVisible(true);
		if (item.isRead)
		{
			isHaveReward->setTexture("TXTIsRecive.png");
		}
		else
		{
			isHaveReward->setTexture("accessory.png");
		}
		
	}
	else
	{
		isHaveReward->setVisible(false);
	}
	if (item.isRead)
	{
		isReadIcon->setTexture("isreadtrue.png");
	}
	else
	{
		isReadIcon->setTexture("isreadfalse.png");
	}
}

void EmailCell::IsBeToued()
{
	if (_item.isRead)
	{
		return;
	}
	EmailManager::getInstance()->SendToGetRequestByEmailId(_item.mailbox_id);

}