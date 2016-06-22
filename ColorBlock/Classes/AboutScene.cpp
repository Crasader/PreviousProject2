#include "AboutScene.h"
#include "MainScene.h"

USING_NS_CC;

Scene* AboutScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = AboutScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool AboutScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//////////////////////////////
	// 2. ��ӱ���ͼ
	auto background = Sprite::create("background.png");
	background->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
	this->addChild(background, -1);

	//////////////////////////////
	// 3. ��ӹ���ͼƬ
	auto about = Sprite::create("tools/about.png");
	about->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
	this->addChild(about);

	//��Ӱ汾��Ϣ
// 	auto version = Label::createWithTTF("v1.00.00", "fonts/FZPTY.ttf", 52);	//���ط�����ͷ���������
// 	if (version != NULL)
// 	{
// 		version->setColor(Color3B(232, 143, 29));	//YELLOW800
// 		version->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 + version->getContentSize().height));
// 		addChild(version);
// 	}

    /////////////////////////////
    // 4. ��Ӳ˵�
	auto okItem = MenuItemImage::create(
		"tools/ok_normal.png",
		"tools/ok_pressed.png",
		CC_CALLBACK_1(AboutScene::menuOkCallback, this));
	okItem->setPosition(Vec2(origin.x + visibleSize.width/2,
		about->getPositionY() - about->getContentSize().height/2 + okItem->getContentSize().height));

    // create menu, it's an autorelease object
    auto menu = Menu::create(okItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}

void AboutScene::menuOkCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(MainScene::createScene());
}