#include "UpgradeSureDialog.h"
#include "widget/GiftCell.h"
#include "domain/game/GameManage.h"
#include "domain/bag/BagManager.h"
UpgradeSureDialog*UpgradeSureDialog::create(std::vector<LevelRewardItem> levelRewardItems)
{
	UpgradeSureDialog*p = new UpgradeSureDialog();
	if (p&&p->init(levelRewardItems))
	{
		p->autorelease();
	}
	else
	{
		p = nullptr;
	}
	return p;
}



bool UpgradeSureDialog::init(std::vector<LevelRewardItem> levelRewardItems)
{
	m_levelRewardItems = levelRewardItems;
	auto bg = Sprite::create("dialogCommonBg.png");
	bg->setPosition(480, 270);
	addChild(bg, -1,"bg");

	auto size = bg->getContentSize();
	auto title = Sprite::create("lingqujiangliTXT.png");
	title->setPosition(size.width/ 2, 297);
	bg->addChild(title);

	auto dec = Sprite::create("shengjijiangliTXT.png");
	dec->setPosition(size.width / 2, 250);
	bg->addChild(dec);

	auto sure = MenuItemImage::create("btn_lingqu_1.png", "btn_lingqu_2.png");
	sure->setPosition(bg->getContentSize().width / 2, 55);
	sure->setCallback(CC_CALLBACK_1(UpgradeSureDialog::sureButtonCallBack, this));
	
	auto menu = Menu::create(sure, nullptr);
	menu->setPosition(bg->getPosition() - bg->getContentSize() / 2);
	addChild(menu,0,"menu");

	for (int i = 0; i < m_levelRewardItems.size();i++)
	{
		auto cell = GiftCell::create(m_levelRewardItems[i].item_id, m_levelRewardItems[i].num);
		cell->setPosition(290 + i * 125, 278);
		addChild(cell);
		cells.pushBack(cell);
	}
	
	

	

	auto listenr1 = EventListenerTouchOneByOne::create();
	listenr1->onTouchBegan = CC_CALLBACK_2(UpgradeSureDialog::onTouchBegan, this);
	listenr1->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);

	//添加系统返回键监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			/*removeFromParentAndCleanup(1);*/
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	/////////弹出动画
	setScale(0);
	runAction(Sequence::create(ScaleTo::create(0.2f, 1.0f), ScaleTo::create(0.07f, 0.8f), ScaleTo::create(0.07f, 1.0f), nullptr));
	return true;
}



void UpgradeSureDialog::sureButtonCallBack(Ref*psend)
{
	getChildByName("bg")->removeFromParentAndCleanup(1);
	getChildByName("menu")->removeFromParentAndCleanup(1);
	for (auto var:cells)
	{
		var->runAction(Sequence::create(Spawn::create(ScaleTo::create(0.5f, 1.5f), MoveBy::create(0.5f, Vec2(0, 100)), nullptr), DelayTime::create(0.5f), MoveTo::create(1.0f, convertToNodeSpace(GameManage::getInstance()->getGameLayer()->GetMyTurret()->getPosition())), RemoveSelf::create(), nullptr));
	}
	runAction(Sequence::create(DelayTime::create(2.1f), CallFunc::create([&]
	{
		removeFromParentAndCleanup(1);
		for (auto var : m_levelRewardItems)
		{
			BagManager::getInstance()->changeItemCount(var.item_id, var.num);
		}
	}
	), nullptr));

}