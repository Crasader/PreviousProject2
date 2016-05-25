#include "MissionCell.h"
#include "utill/Chinese.h"
#include "domain/ranklist/RanklistManager.h"
#include "config/ConfigExp.h"
#include "domain/bag/BagManager.h"
#include "domain/game/GameManage.h"
#include "domain/ToolTip/ToolTipMannger.h"
#include "widget/MyLabelAtlas.h"
bool MissionCell::init(){

	auto bg = Sprite::create("missionBg.png");
	auto size = bg->getContentSize();
	bg->setPosition(size/2);
	addChild(bg,0,"bg");




	_missionContant = Sprite::create();
	_missionContant->setPosition(118, 80);
	bg->addChild(_missionContant);

	auto sp = Sprite::create("missionBarFrane.png");
	sp->setPosition(140-20, 41);
	bg->addChild(sp,0,"missionBarFrane");

	_progressbar = ui::LoadingBar::create("missionBar.png");
	_progressbar->setAnchorPoint(Point::ANCHOR_MIDDLE);
	_progressbar->setPosition(sp->getContentSize() / 2 + Size(0, 0));
	sp->addChild(_progressbar);

	_progressPercent = MyLabelAtlas::create("0", "nextPoolNum.png", 11, 19, '0',112);
	_progressPercent->setAnchorPoint(Point::ANCHOR_MIDDLE);
	_progressPercent->setPosition(_progressbar->getContentSize() / 2);
	_progressbar->addChild(_progressPercent);

	_rewardProp = Sprite::create();
	_rewardProp->setScale(0.8);
	_rewardProp->setPosition(350, 59);
	bg->addChild(_rewardProp);

	_rewardPropNum = LabelAtlas::create("", "missionRewardNum.png", 14, 20, '0');
	_rewardPropNum->setAnchorPoint(Point(0, 0.5));
	_rewardPropNum->setPosition(395, 59);
	bg->addChild(_rewardPropNum);




	bt = MenuItemImage::create();
	bt->setCallback(CC_CALLBACK_1(MissionCell::btCallback, this));
	bt->setPosition(587, 59);
	auto menu = Menu::create(bt, nullptr);
	menu->setPosition(0, 0);
	bg->addChild(menu);
	return true;
}

void MissionCell::btCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	bool isfinish = (_item.current_nums >= _item.require_nums);
	if (isfinish)
	{
		EventListenerCustom* _listener2 = EventListenerCustom::create("get_mission_rewards", [=](EventCustom* event){

			MissionRewardValue*value = static_cast<MissionRewardValue*>(event->getUserData());
			if (value->_errorcode == 0)
			{
				for (auto var : value->rewards)
				{
					BagManager::getInstance()->addreward(var._itemid, var._num);
				}
				_item.isReceive = true;
				for (auto &var : MissionManager::getInstance()->getMissionListData())
				{
					if (var.mission_id == _item.mission_id)
					{
						var = _item;
						break;
					}
				}
				setValue(_item);
			}
			else
			{
				ToolTipMannger::showDioag(value->_errormsg);
			}
		
			Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("get_mission_rewards");
			LoadingCircle::RemoveLoadingCircle();

		});
		LoadingCircle::showLoadingCircle();
		Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listener2, 1);
		HttpMannger::getInstance()->HttpToPostRequestGetMissionReward(_item.mission_id);
	}
	else
	{
		GameManage::getInstance()->getLobbyLayer()->quickBeginCallback(nullptr);
	}
	
}
void MissionCell::setValue(MissionListItem item)
{
	_item = item;
	if (_item.current_nums>=_item
		.require_nums)
	{
		_item.current_nums = _item.require_nums;
	}
	auto str = String::createWithFormat("CrazyFarm_Mission_%d.png", _item.mission_id);
	_missionContant->setTexture(str->getCString());
	str = String::createWithFormat("%d:%d", _item.current_nums, _item.require_nums);
	_progressPercent->setString(str->getCString());
	_progressbar->setPercent(((float)_item.current_nums) / ((float)_item.require_nums)*100);
	str = String::createWithFormat("item_%d.png", _item.rewards.at(0)._itemid);
	_rewardProp->setTexture(str->getCString());
	str = String::createWithFormat(":%d", _item.rewards.at(0)._num);
	_rewardPropNum->setString(str->getCString());


	if (_item.isReceive)
	{
		bt->setNormalImage(Sprite::create("Havetoreceive.png"));
		bt->setEnabled(false);
		getChildByName("bg")->getChildByName("missionBarFrane")->setVisible(false);
	}
	else
	{
		bool isfinish = (_item.current_nums >= _item.require_nums);
		if (isfinish)
		{
			bt->setNormalImage(Sprite::create("missionGet_1.png"));
			bt->setSelectedImage(Sprite::create("missionGet_2.png"));
			bt->setEnabled(true);
		}
		else
		{
			bt->setNormalImage(Sprite::create("missionGoto_1.png"));
			bt->setSelectedImage(Sprite::create("missionGoto_2.png"));
			bt->setEnabled(true);
		}
		getChildByName("bg")->getChildByName("missionBarFrane")->setVisible(true);
	}

}




void MissionCell::IsBeToued()
{


}