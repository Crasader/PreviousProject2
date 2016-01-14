#include "MyDialog.h"

bool MyDialog::init()
{
	Layer::init();
	bool bRet = false;
	do
	{
		auto colorlayer = LayerColor::create();
		colorlayer->setColor(ccc3(0, 0, 0));
		colorlayer->setOpacity(180);
		addChild(colorlayer, -1);
		
		auto bg = Sprite::create("dialogCommonBg.png");
		bg->setPosition(480, 270);
		addChild(bg, -1);

		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(MyDialog::onTouchBegan, this);
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
		bRet = true;
	} while (0);


	return bRet;
}
