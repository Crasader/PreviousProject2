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

	_missionContant = MyLabelTTF::create("0", "arial", 20,158);
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

	_progressPercent = MyLabelAtlas::create("0", "VIPexp_num.png", 14, 22, '0',112);
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
	bool isfinish = (_item.current_nums >= _item.require_nums);
	if (isfinish)
	{
		EventListenerCustom* _listener2 = EventListenerCustom::create("get_achieve_rewards", [=](EventCustom* event){

			AchieveRewardValue*value = static_cast<AchieveRewardValue*>(event->getUserData());
			if (value->_errorcode == 0)
			{
				for (auto var : value->rewards)
				{
					BagManager::getInstance()->addreward(var._itemid, var._num);
				}
				if (value->_new_task_item.tag!=-1)
				{
					_item = value->_new_task_item;
				}
				else
				{
					_item.isReceive = true;
				}
				setValue(_item);
				for (auto &var:MissionManager::getInstance()->getAchieveListData())
				{
					if (var.mission_id == _item.mission_id)
					{
						var = _item;
						break;
					}
				}
			}
			else 
			{
				ToolTipMannger::showDioag(value->_errormsg);
			}
			Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("get_achieve_rewards");
			LoadingCircle::RemoveLoadingCircle();

		});
		LoadingCircle::showLoadingCircle();
		Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listener2, 1);
		HttpMannger::getInstance()->HttpToPostRequestGetAchieveReward(_item.mission_id);
	}
	else
	{
		GameManage::getInstance()->getLobbyLayer()->quickBeginCallback(nullptr);
	}
	
}
void AchieveCell::setValue(AchieveListItem item)
{

	_item = item;
	auto str = String::createWithFormat("CrazyFarm_achieve_icon_%d.png", item.mission_id);
	_icon->setTexture(str->getCString());
	str = String::createWithFormat("CrazyFarm_achieve_content_%d.png", item.mission_id);
	_missionName->setTexture(str->getCString());
	str = String::createWithFormat("sign_%d.png", _item.rewards.at(0)._itemid);
	_rewardProp->setTexture(str->getCString());
	str = String::createWithFormat(":%d", _item.rewards.at(0)._num);
	_rewardPropNum->setString(str->getCString());

	if (_item.isReceive == true && _item.current_level == _item.max_level)
	{
		_stars->setValue(_item.max_level, _item.current_level);
	}
	else
	{
		_stars->setValue(_item.max_level, _item.current_level - 1);
	}
	
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

	if (_item.max_level==_item.current_level&&_item.isReceive)
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