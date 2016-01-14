#include "NotarizeExitDialog.h"
#include "lobby/LobbyScene.h"
bool NotarizeExitDialog::init()
{
	MyDialog::init();
	bool bRet = false;
	do
	{  
		auto size = Director::getInstance()->getVisibleSize();  
		auto sp = Sprite::create("tuichuyouxiTXT.png");
		sp->setPosition(size.width / 2, 405);
		addChild(sp);
		sp = Sprite::create("likaiyouxiTXT.png");
		sp->setPosition(457, 313);
		addChild(sp);
		
		auto queren = MenuItemImage::create("btn_queding_1.png", "btn_queding_2.png", CC_CALLBACK_1(NotarizeExitDialog::querenCallback, this));
		queren->setPosition(329, 200);
		auto close = MenuItemImage::create("btn_quxiao_1.png", "btn_quxiao_2.png", CC_CALLBACK_1(NotarizeExitDialog::closeButtonCallBack, this));
		close->setPosition(629, 200);
		auto menu = Menu::create(close, queren, nullptr);
		menu->setPosition(Point::ZERO);
		addChild(menu);
		bRet = true;
	} while (0);


	return bRet;
}
void NotarizeExitDialog::querenCallback(Ref*psend)
{
	Director::getInstance()->replaceScene(LobbyScene::createScene());
}


void NotarizeExitDialog::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}