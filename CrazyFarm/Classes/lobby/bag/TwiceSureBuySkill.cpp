#include "TwiceSureBuySkill.h"
#include "domain/skill/skillManager.h"
#include "utill/Chinese.h"
#include "domain/bag/BagManager.h"
#include "domain/ToolTip/TwiceSureDialog.h"
#include "server/HttpMannger.h"
#include "domain/ToolTip/ToolTipMannger.h"
#include "lobby/bag/bagLayer.h"
TwiceSureBuySkill*TwiceSureBuySkill::createTwiceBuySkillTip(int itemid)
{
	TwiceSureBuySkill*ref = new TwiceSureBuySkill();
	if (ref&&ref->init(itemid))
	{
		ref->autorelease();
	}
	else
	{
		ref = nullptr;
	}
	return ref;
}





bool TwiceSureBuySkill::init(int itemid)
{
	Layer::init();
	bool bRet = false;
	do 
	{
		auto colorlayer = LayerColor::create();
		colorlayer->setColor(ccc3(0, 0, 0));
		colorlayer->setOpacity(180);
		colorlayer->setPosition(0,0);
		addChild(colorlayer, -1);
		auto bg = Sprite::create("TwiceSureDialog.png");
		bg->setPosition(480, 270);
		addChild(bg, -1);
		
		m_itemid = itemid;
		auto price = skillManager::getInstance()->getSkillPriceById(skillManager::getInstance()->getSkillInfoByitemId(m_itemid).skill_id);
		auto spPath = String::createWithFormat("item_%d.png", itemid);
		auto sp = Sprite::create(spPath->getCString());
		sp->setPosition(76, 150);
		bg->addChild(sp);
		//��������
		auto str = String::createWithFormat("propName_%d",m_itemid);
		auto label = LabelTTF::create(ChineseWord(str->getCString()).c_str(), "arial", 20);
		label->setColor(Color3B(12, 64, 109));
		label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		label->setPosition(141, 195);
		bg->addChild(label);
		//��������	
		 str = String::createWithFormat(ChineseWord("buyPropNum").c_str(), 200/price);
		label = LabelTTF::create(str->getCString(), "arial", 20);
		label->setColor(Color3B(12, 64, 109));
		label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		label->setPosition(141, 165);
		bg->addChild(label);
		//��������
		str = String::createWithFormat(ChineseWord("propPrice").c_str(), 200);
		label = LabelTTF::create(str->getCString(), "arial", 20);
		label->setColor(Color3B(12, 64, 109));
		label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		label->setPosition(141, 135);
		bg->addChild(label);




		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(TwiceSureBuySkill::closeButtonCallBack, this));
		close->setPosition(bg->getContentSize());

		auto sure = MenuItemImage::create("btn_goumai_1.png", "btn_goumai_2.png", CC_CALLBACK_1(TwiceSureBuySkill::sureButtonCallBack,this));
		sure->setPosition(bg->getContentSize().width / 2, 40);

		auto menu = Menu::create(close, sure, nullptr);
		menu->setPosition(bg->getPosition() - bg->getContentSize() / 2);
		addChild(menu);




	//���ϵͳ���ؼ�����
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
	
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
		bRet = true;
	} while (0);
	

	return bRet;
}

void TwiceSureBuySkill::sureButtonCallBack(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	if (User::getInstance()->getDiamonds()>=200)
	{
		if (User::getInstance()->getMaxTurrentLevel()>300)
		{
			HttpMannger::getInstance()->HttpToPostRequestToBuyItem(m_itemid);
			LoadingCircle::showLoadingCircle();
			EventListenerCustom* _listener2 = EventListenerCustom::create("buyitem", [=](EventCustom* event){

				LoadingCircle::RemoveLoadingCircle();
				BuyBagItemValue *value = (BuyBagItemValue*)event->getUserData();
				auto menu = getChildByName("bg")->getChildByName("menu");
				auto bt = ((MenuItem*)(menu->getChildByName("sureBt")));
				TwiceSureDialog*dialog;
				switch (value->_errorcode)
				{
				case 0:
				{
					dialog = TwiceSureDialog::createDialog("pay success ");
					BagManager::getInstance()->addreward(m_itemid, value->buyItemNum);
					User::getInstance()->addDiamonds(-value->costDmNum);

					auto layer = Director::getInstance()->getRunningScene()->getChildByTag(888);
					((BagLayer*)layer)->gettableview()->reloadData();
				}
					break;
				case 404:
					dialog = TwiceSureDialog::createDialog("time out");
					bt->setEnabled(true);
					break;
				default:
					dialog = TwiceSureDialog::createDialog(value->_errormsg.c_str());
					bt->setEnabled(true);
					break;
				}
				dialog->setPosition(0, 0);
				getParent()->addChild(dialog, 30);
				if (value->_errorcode == 0)
				{
					removeFromParentAndCleanup(true);
				}

				Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("buyitem");

			});
			Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listener2, 1);


		}
		else
		{
			auto layer = TwiceSureDialog::createDialog(ChineseWord("bySkillNoNeedTurrentTIP").c_str(), nullptr);
			layer->setPosition(0, 0);
			getParent()->getParent()->addChild(layer, 30);
		}
		
	}
	getParent()->removeFromParentAndCleanup(1);
}

void TwiceSureBuySkill::closeButtonCallBack(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	removeFromParentAndCleanup(1);
}