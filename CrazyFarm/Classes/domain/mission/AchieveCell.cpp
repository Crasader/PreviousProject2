#include "AchieveCell.h"
#include "utill/Chinese.h"
#include "domain/ranklist/RanklistManager.h"
#include "config/ConfigExp.h"
#include "domain/bag/BagManager.h"
#include "domain/game/GameManage.h"
#include "domain/ToolTip/ToolTipMannger.h"
bool AchieveCell::init(){

	auto bg = Sprite::create("missionBg.png");
	auto size = bg->getContentSize();
	bg->setPosition(size/2);
	addChild(bg);


	_icon = Sprite::create();
	_icon->setPosition(65, 55);
	bg->addChild(_icon);

	_missionName = Sprite::create();
	_missionName->setPosition(160, 80);
	bg->addChild(_missionName);

	_missionContant = LabelTTF::create("0", "arial", 20);
	_missionContant->setAnchorPoint(Point::ZERO);
	_missionContant->setPosition(115, 30);
	bg->addChild(_missionContant);

	_missionBarFrane = Sprite::create("missionBarFrane.png");
	_missionBarFrane->setPosition(579, 43);
	bg->addChild(_missionBarFrane);

	_progressbar = ui::LoadingBar::create("missionBar.png");
	_progressbar->setAnchorPoint(Point::ANCHOR_MIDDLE);
	_progressbar->setPosition(_missionBarFrane->getContentSize() / 2 + Size(0, 0));
	_missionBarFrane->addChild(_progressbar);

	_progressPercent = LabelAtlas::create("0", "VIPexp_num.png", 14, 22,'0');
	_progressPercent->setAnchorPoint(Point::ANCHOR_MIDDLE);
	_progressPercent->setPosition(_progressbar->getContentSize() / 2);
	_progressbar->addChild(_progressPercent);

	_rewardProp = Sprite::create();
	_rewardProp->setScale(0.5);
	_rewardProp->setPosition(334, 77);
	bg->addChild(_rewardProp);

	_rewardPropNum = LabelAtlas::create("", "missionRewardNum.png", 14, 20, '0');
	_rewardPropNum->setAnchorPoint(Point(0, 0.5));
	_rewardPropNum->setPosition(360, 77);
	bg->addChild(_rewardPropNum);

	_stars = AchieveStar::create();
	_stars->setPosition(308, 24);
	bg->addChild(_stars);
	_txtProgressContant = Sprite::create("txt_achiveProgress.png");
	_txtProgressContant->setPosition(578, 77);
	bg->addChild(_txtProgressContant);

	bt = MenuItemImage::create();
	bt->setCallback(CC_CALLBACK_1(AchieveCell::btCallback, this));
	bt->setPosition(573, 56);
	auto menu = Menu::create(bt, nullptr);
	menu->setPosition(0, 0);
	bg->addChild(menu);
	return true;
}

void AchieveCell::btCallback(Ref*psend)
{

	
}
void AchieveCell::setValue(AchieveListItem item)
{


	_item = item;
	_icon->setTexture(item.tast_icon_url_pic);
	_missionName->setTexture(item.tast_content_url_pic);
	auto str = String::createWithFormat("sign_%d.png", _item.rewards.at(0)._itemid);
	_rewardProp->setTexture(str->getCString());
	str = String::createWithFormat(":%d", _item.rewards.at(0)._num);
	_rewardPropNum->setString(str->getCString());
	_stars->setValue(_item.max_level, _item.current_level - 1);
	_missionContant->setString(_item.task_content);

	if (_item.current_nums==0)
	{
		//进度为0，状态前往
		bt->setNormalImage(Sprite::create("missionGoto_1.png"));
		bt->setSelectedImage(Sprite::create("missionGoto_2.png"));
		bt->setEnabled(true);
		bt->setVisible(true);
		bt->setName("goto");
		_missionBarFrane->setVisible(false);
		_txtProgressContant->setVisible(false);
	}
	else if (_item.current_nums<_item.require_nums)
	{
		_missionBarFrane->setVisible(true);
		_txtProgressContant->setVisible(true);
		str = String::createWithFormat("%d:%d", _item.current_nums, _item.require_nums);
		_progressPercent->setString(str->getCString());
		_progressbar->setPercent(((float)_item.current_nums) / ((float)_item.require_nums) * 100);
		bt->setEnabled(false);
		bt->setVisible(false);
	}
	else
	{
		bt->setNormalImage(Sprite::create("missionGet_1.png"));
		bt->setSelectedImage(Sprite::create("missionGet_2.png"));
		bt->setEnabled(true);
		bt->setVisible(true);
		bt->setName("goto");
		_missionBarFrane->setVisible(false);
		_txtProgressContant->setVisible(false);
	}

	if (_item.max_level==_item.current_level-1)
	{
		bt->setNormalImage(Sprite::create("Havetoreceive.png"));
		bt->setSelectedImage(Sprite::create("Havetoreceive.png"));
		bt->setVisible(true);
		bt->setEnabled(false);
		bt->setName("Havetoreceive");
		_missionBarFrane->setVisible(false);
		_txtProgressContant->setVisible(false);
	}
}




void AchieveCell::IsBeToued()
{


}