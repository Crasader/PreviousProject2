#include "EmailContent.h"
#include "utill/Audio.h"
#include "utill/Chinese.h"
#include "widget/GiftCell.h"
#include "widget/MyCustomLabelTTF.h"
EmailContent* EmailContent::create(EmailListItem item)
{
	EmailContent *pRet = new EmailContent();
	if (pRet && pRet->init(item))
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
bool EmailContent::init(EmailListItem item)
{
	if (!Sprite::initWithFile("emailContentBg.png"))
	{
		return false;
	}
	bool bRet = false;
	do 
	{
		auto createtimestr = String::createWithFormat(ChineseWord("EmailCreatTime").c_str(), item.email_create_time / 10000, item.email_create_time % 10000 / 100, item.email_create_time % 100);
		auto labelCreateTime = Label::create(createtimestr->getCString(), "arial", 20);
		labelCreateTime->setPosition(24,373);
		labelCreateTime->setColor(Color3B::BLACK);
		labelCreateTime->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		addChild(labelCreateTime);

		auto contentstr = String::createWithFormat(ChineseWord("EmailContent").c_str(),item.email_content.c_str());
		auto labelcontent = Label::create(contentstr->getCString(), "arial", 20);
		labelcontent->setPosition(24, 335);
		labelcontent->setMaxLineWidth(14.5 * 20);
		labelcontent->setColor(Color3B::BLACK);
		labelcontent->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
		addChild(labelcontent);


		if (item.email_rewards.size()>0)
		{
			auto icon = Sprite::create("Accessory.png");
			icon->setPosition(30, 156);
			icon->setScale(0.7);
			addChild(icon);


			auto label1 = Label::create(ChineseWord("Accessory"), "arial", 17);
			label1->setPosition(icon->getPositionX()+icon->getContentSize().width/2,icon->getPositionY());
			label1->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
			label1->setColor(Color3B::BLACK);
			addChild(label1);

			auto label2= Label::create(ChineseWord("ItemPutYourBag"), "arial", 17);
			label2->setColor(Color3B::RED);
			label2->setPosition(label1->getPositionX() + label1->getContentSize().width, label1->getPositionY());
			label2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
			addChild(label2);

			float startx = 59;
			for (auto var:item.email_rewards)
			{
				auto sp = GiftCell::create(var._itemid, var._num);
				sp->setPosition(startx, 85);
				addChild(sp);
				sp->setScale(0.6);
				startx += 60;
			}
		}
		
		bRet = true;
	} while (0);
	

	return bRet;
}
