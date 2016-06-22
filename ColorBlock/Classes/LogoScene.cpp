#include "LogoScene.h"
#include "MainScene.h"

USING_NS_CC;

Scene* LogoScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LogoScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LogoScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	//��ȡ��Ϸ����
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//���LogoͼƬ
	auto logo = Sprite::create("Aikuyu.png");
	logo->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
	this->addChild(logo);

	//�ɽ�������������Ч����
	auto actionFadeIn = FadeIn::create(0.5f);
	auto actionFadeOut = FadeOut::create(0.3f);//actionFadeIn->reverse();
	logo->setOpacity(122);							//����͸����
	logo->runAction(Sequence::create(actionFadeIn, CallFunc::create(CC_CALLBACK_0(LogoScene::LeaveLogoScene, this)), nullptr));

    return true;
}

//�л�����
void LogoScene::LeaveLogoScene()
{
	Director::getInstance()->replaceScene(MainScene::createScene());
}