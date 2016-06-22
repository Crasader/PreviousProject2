#include "VolumeScene.h"
#include "SetupScene.h"
#include "Sqlite/DBManager.h"
#include "../MainScene.h"

USING_NS_CC;


Scene* VolumeScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = VolumeScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool VolumeScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//添加背景
    auto sprite = Sprite::create("background.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);

	//添加确定按钮
	 auto okItem = MenuItemImage::create(
                                        "setup/ok_normal.png",
                                        "setup/ok_pressed.png",
                                        CC_CALLBACK_1(VolumeScene::menuCallOK, this));
	 okItem->setPosition(Vec2(origin.x + visibleSize.width/3, origin.y + visibleSize.height/4));
    
	//添加返回按钮
	 auto returnItem = MenuItemImage::create(
                                           "setup/return_normal.png",
                                           "setup/return_pressed.png",
                                           CC_CALLBACK_1(VolumeScene::menuCallreturn, this));
	 returnItem->setPosition(Vec2(origin.x + visibleSize.width/3*2, origin.y + visibleSize.height/4));

    // create menu, it's an autorelease object
    auto menu = Menu::create(okItem, returnItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	//添加音量图片
	auto volumeSprite = Sprite::create("setup/volume.png");
    volumeSprite->setPosition(Vec2(origin.x + visibleSize.width/5 + visibleSize.width/20, origin.y + visibleSize.height/4*3));
	this->addChild(volumeSprite);

	//添加音量Slider
	auto fBgmVolume = DBManager::GetInstance()->GetBgmVolume();
	m_volumeSlider = ui::Slider::create();
	m_volumeSlider->setPercent(fBgmVolume);
	m_volumeSlider->loadBarTexture("setup/slider.png");
	m_volumeSlider->addEventListener(CC_CALLBACK_2(VolumeScene::sliderEvent, this));
	m_volumeSlider->loadSlidBallTextures("setup/sliderballnormal.png", "setup/sliderballnormal.png", "");
	m_volumeSlider->setTag(1);
	m_volumeSlider->setPosition(Vec2(origin.x + visibleSize.width / 8 * 5 - visibleSize.width / 20, origin.y + visibleSize.height / 4 * 3));
	this->addChild(m_volumeSlider);
	//添加音效图片
	auto sfSprite = Sprite::create("setup/soundEffect.png");
    sfSprite->setPosition(Vec2(origin.x + visibleSize.width/5 + visibleSize.width/20, origin.y + visibleSize.height/4*2));
	this->addChild(sfSprite);

	//添加音效
	auto fEffectsVolume = DBManager::GetInstance()->GetEffectsVolume();
	m_volumeEffectslider = ui::Slider::create();
	m_volumeEffectslider->setPercent(fEffectsVolume);
	m_volumeEffectslider->loadSlidBallTextures("setup/sliderballnormal.png", "setup/sliderballnormal.png", "");
	m_volumeEffectslider->loadBarTexture("setup/slider.png");
	m_volumeEffectslider->addEventListener(CC_CALLBACK_2(VolumeScene::sliderEvent, this));
	m_volumeEffectslider->setTag(2);
	m_volumeEffectslider->setPosition(Vec2(origin.x + visibleSize.width/8*5 - visibleSize.width/20, origin.y + visibleSize.height/4*2));
	this->addChild(m_volumeEffectslider);

    return true;
}

void VolumeScene::menuCallOK(Ref *pSender)
{
	auto fBgmVolume = m_volumeSlider->getPercent();
	auto fEffectsVolume = m_volumeEffectslider->getPercent();
	DBManager::GetInstance()->SetBgmVolume(fBgmVolume);
	DBManager::GetInstance()->SetEffectsVolume(fEffectsVolume);
	Director::getInstance()->replaceScene(SetupScene::createScene());
}

void VolumeScene::menuCallreturn(Ref *pSender)
{
	Director::getInstance()->replaceScene(SetupScene::createScene());
}

void VolumeScene::sliderEvent(Ref *pSender, ui::Slider::EventType type)
{
	if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
	{

		ui::Slider* slider = dynamic_cast<ui::Slider*>(pSender);
		auto  percent = (float)slider->getPercent();
		//if (percent <= 15.0)
		//{
		//	slider->setPercent(15.0);
		//	percent = 15.0;
		//}
		//else if (percent >= 85.0)
		//{
		//	slider->setPercent(85.0);
		//	percent = 85.0;

		//}
		//float curValue = (percent - 15.0) / 70.0;
		auto curValue = slider->getPercent();
		int tag = slider->getTag();
		if (tag == 1)
		{
			DBManager::GetInstance()->SetBgmVolume(curValue);

		}
		else
		{
			DBManager::GetInstance()->SetEffectsVolume(curValue);
		}

	}
}