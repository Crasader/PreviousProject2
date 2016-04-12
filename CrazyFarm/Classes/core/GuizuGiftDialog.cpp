#include "GuizuGiftDialog.h"
#include "domain/nobility/NobilityManager.h"
#include "domain/user/User.h"
#include "domain/bag/BagManager.h"
bool GuizuGiftDialog::init()
{
	MyDialog::init();
	bool bRet = false;
	do
	{  
		auto size = Director::getInstance()->getVisibleSize();  
		auto sp = Sprite::create("lingqujiangliTXT.png");
		sp->setPosition(size.width / 2, 405);
		addChild(sp);
		sp = Sprite::create("tequanjiangliTXT.png");
		sp->setPosition(size.width / 2, 370);
		addChild(sp);
		auto button = MenuItemImage::create("btn_lingqu_1.png", "btn_lingqu_2.png",CC_CALLBACK_1(GuizuGiftDialog::lingquCallback,this));
		button->setPosition(size.width / 2, 190);
		auto menu = Menu::create(button, nullptr);
		menu->setPosition(Point::ZERO);
		addChild(menu);

		auto vec = NobilityManager::getInstance()->getNobilityRewadItems();
		int i = 0;
		for (auto var:vec)
		{
			auto propNum = LabelAtlas::create(Value(var._num).asString().c_str(), "guizuPropNum.png", 15, 22,'0');
			propNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
			auto path = String::createWithFormat("item_%d.png", var._itemid);
			auto prop = Sprite::create(path->getCString());
			if (var._itemid == 1001)
			{
				propNum->setPosition(prop->getContentSize().width / 2, 17);
			}
			else
			{
				propNum->setPosition(74, 17);
			}
			prop->addChild(propNum);
			prop->setPosition(prop->getContentSize().width*0.5 + 260 + i*(22 + prop->getContentSize().width), 300);
			addChild(prop);
			i++;
		}


		bRet = true;
	} while (0);


	return bRet;
}
void GuizuGiftDialog::lingquCallback(Ref*psend)
{
	auto vec = NobilityManager::getInstance()->getNobilityRewadItems();
	for (auto var:vec)
	{
		BagManager::getInstance()->addreward(var._itemid, var._num);

	}

	removeFromParentAndCleanup(1);
	EventCustom event("show_poppage");
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}