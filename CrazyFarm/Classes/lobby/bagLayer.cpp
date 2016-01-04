#include "lobby/bagLayer.h"
#include "ConfigItem.h"
#include "User.h"
Scene* BagLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = BagLayer::create();

	scene->addChild(layer);

	return scene;
}

bool BagLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	bool bRet = false;
	do 
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto bg = Sprite::create("bagBG.jpg");
		bg->setPosition(visibleSize / 2);
		addChild(bg,-1);
		auto user = User::getInstance();
		auto leveldata = user->getLevelData();
		auto bagFram = Sprite::create("bagFrame.png");
		bagFram->setPosition(visibleSize.width/2, visibleSize.height*0.45);
		addChild(bagFram);
		auto sssize = bagFram->getContentSize();
		//����
		auto titleFram = Sprite::create("redframe.png");
		titleFram->setPosition(sssize.width / 2, sssize.height*0.95);
		auto title = Sprite::create("bagTitle.png");
		title->setPosition(titleFram->getContentSize().width*0.5,titleFram->getContentSize().height*0.6);
		titleFram->addChild(title);
		bagFram->addChild(titleFram);


		//������Ϣ��
		auto playinfoFram = Sprite::create("playinfoFram.png");
		playinfoFram->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		playinfoFram->setPosition(15, sssize.height*0.45);
		bagFram->addChild(playinfoFram);
		auto sssize2 = playinfoFram->getContentSize();
		auto spHead = Sprite::create();
		int sex = rand() % 2;
		if (sex)
		{
			spHead->setTexture("bagMale.png");
		}
		else
		{
			spHead->setTexture("bagFamale.png");
		}
		spHead->setPosition(sssize2.width*0.19, sssize2.height*0.82);
		playinfoFram->addChild(spHead);
		//�ǳ�
		auto userName = LabelTTF::create(user->getUserName(), "arial", 20);
		userName->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
		userName->setPosition(sssize2.width*0.62, sssize2.height*0.83);
		playinfoFram->addChild(userName);
		//�ȼ�
		auto spLV = Sprite::create("LV.png");
		spLV->setPosition(sssize2.width*0.385, sssize2.height*0.74);
		playinfoFram->addChild(spLV);
		auto userlevel = LabelAtlas::create(Value(leveldata.levelId).asString().c_str(), "levelnum.png", 12, 17, '0');
		userlevel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		userlevel->setPosition(spLV->getPositionX()+spLV->getContentSize().width, spLV->getPositionY());
		playinfoFram->addChild(userlevel);
		//���
		auto userCoin = LabelTTF::create(Value(user->getCoins()).asString().c_str(), "arial", 20);
		userCoin->setAnchorPoint(Point::ANCHOR_MIDDLE);
		userCoin->setPosition(sssize2.width*0.65, sssize2.height *0.60);
		userCoin->setColor(Color3B::WHITE);
		playinfoFram->addChild(userCoin);
		//��ʯ
		auto userdiamond = LabelTTF::create(Value(user->getDiamonds()).asString().c_str(), "arial", 20);
		userdiamond->setAnchorPoint(Point::ANCHOR_MIDDLE);
		userdiamond->setPosition(sssize2.width*0.65, sssize2.height *0.485);
		userdiamond->setColor(Color3B::WHITE);
		playinfoFram->addChild(userdiamond);
		//VIP
		auto viplevel = LabelTTF::create(Value(user->getVipLevel()).asString().c_str(), "arial", 20);
		viplevel->setPosition(sssize2.width*0.65, sssize2.height *0.37);
		playinfoFram->addChild(viplevel);
		//����
		//////////////////////////////////////////////////////////
		auto exeDescribe = LabelTTF::create("100/200", "arial", 17);
		exeDescribe->setPosition(sssize2.width*0.72, sssize2.height*0.74);
		playinfoFram->addChild(exeDescribe);









		//������Ϣ��
		auto baginfoFram = Sprite::create("baginFrame.png");
		baginfoFram->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		baginfoFram->setPosition(sssize.width-15, sssize.height*0.45);
		bagFram->addChild(baginfoFram);



		auto chakan = MenuItemImage::create("btn_small_1.png", "btn_small_2.png", CC_CALLBACK_1(BagLayer::chankanCallBack, this));
		chakan->setPosition(visibleSize.width*0.48, visibleSize.height * 0.3103);
		auto chakan1 = MenuItemImage::create("btn_small_1.png", "btn_small_2.png", CC_CALLBACK_1(BagLayer::chankanCallBack, this));
		chakan1->setPosition(visibleSize.width*0.48, visibleSize.height * 0.2303);
		auto setname = MenuItemImage::create("btn_big_1.png", "btn_big_2.png", CC_CALLBACK_1(BagLayer::chankanCallBack, this));
		setname->setPosition(visibleSize.width*0.30, visibleSize.height * 0.125);


		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(BagLayer::closeButtonCallBack, this));
		close->setPosition(sssize.width/2 + bagFram->getPositionX(), sssize.height);
		auto menu = Menu::create(close, chakan,chakan1,setname,nullptr);
		menu->setPosition(Point::ZERO); 
		addChild(menu);

	//���ϵͳ���ؼ�����
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			removeFromParentAndCleanup(1);
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

void BagLayer::closeButtonCallBack(Ref*psend)
{
	Director::getInstance()->popScene();
}

void BagLayer::chankanCallBack(Ref*pesend)
{

}