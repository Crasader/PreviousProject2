#include "DragModeGameMainScene.h"
#include "MainScene.h"
#include "Block/GameField.h"
#include "Block/SpriteManager.h"
#include "SimpleAudioEngine.h"
#include "Sqlite/DBManager.h"
#include "tools/GameOverLayer.h"
#include "tools/ExitLayer.h"
#include "tools/StringManager.h"
#include "LogoScene.h"
#include "ui/UIButton.h"
#include "cocostudio/CocoStudio.h"
#include "CommonFunction.h"
#include "tools/PauseLayer.h"
#include "utill/SkillButton.h"
#include "utill/Audio.h"
#include <map>

USING_NS_CC;
using namespace ui;
using namespace CocosDenshion;
using std::map;


const int kTagBaseSkillButton = 80;
DragModeGameMainScene::DragModeGameMainScene()
{

}

Scene* DragModeGameMainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = DragModeGameMainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool DragModeGameMainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !BaseGame::init() )
    {
        return false;
    }
	auto db = DBManager::GetInstance();
	//获取游戏区域
	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_origin = Director::getInstance()->getVisibleOrigin();
	m_winSize = Director::getInstance()->getWinSize();

	//层
	int nZOrderBackground = -10;
	int nZOrderWidget = -8;

	SpriteManager::GetInstance()->InitSpriteFramesWithFile("game.plist");
	//添加背景图
	auto background = Sprite::create("background_main.png");
	background->setPosition(Vec2(m_origin.x + m_visibleSize.width / 2, m_origin.y + m_visibleSize.height / 2));
	this->addChild(background, nZOrderBackground);

	//添加ready方块背景图
	auto readyBoxFrame = Sprite::createWithSpriteFrameName("operateFrame.png");
	readyBoxFrame->setPosition(240, 100);
	addChild(readyBoxFrame, nZOrderBackground + 1);

	//添加小部件层
	m_widget = DragModeGameWidget::create();
	this->addChild(m_widget, 5+1);





	auto pauseButton = Button::create("btPause_1.png", "btPause_2.png", "", Widget::TextureResType::PLIST);
	pauseButton->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
	pauseButton->setPosition(Vec2(0, 800));
	pauseButton->addTouchEventListener([=](Ref* sender, cocos2d::ui::Widget::TouchEventType event){
		if (event == Widget::TouchEventType::ENDED)
		{
			onPause();
		}
	});
	this->addChild(pauseButton);


	//技能按钮




	auto skillbutton = SkillButton::createSkillButton(81, db->GetSkillNum(81));
	skillbutton->setPosition(Vec2(240-100,213));
	skillbutton->setTag(kTagBaseSkillButton+1);
	addChild(skillbutton, 5);

	skillbutton = SkillButton::createSkillButton(82, db->GetSkillNum(82));
	skillbutton->setPosition(Vec2(240 + 100, 213));
	addChild(skillbutton,5);
	skillbutton->setTag(kTagBaseSkillButton + 2);
	//触摸屏事件监听
	m_touchListener = EventListenerTouchOneByOne::create();
	m_touchListener->onTouchBegan = CC_CALLBACK_2(DragModeGameMainScene::onTouchBegan, this);
	m_touchListener->onTouchMoved = CC_CALLBACK_2(DragModeGameMainScene::onTouchMoved, this);
	m_touchListener->onTouchEnded = CC_CALLBACK_2(DragModeGameMainScene::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_touchListener, this);
	



	Audio::getInstance()->playBGM(AUDIO_BGMDROPMODE);

	//设置音效音量
	float fVolumeBgm = DBManager::GetInstance()->GetBgmVolume();
	float fVolumeEffects = DBManager::GetInstance()->GetEffectsVolume();
	Audio::getInstance()->setBGMValue(fVolumeBgm);
	Audio::getInstance()->setEffectValue(fVolumeEffects);
	scheduleUpdate();
    return true;
}

void DragModeGameMainScene::update(float delta)
{
	/*auto bt = (SkillButton*)getChildByTag(kTagBaseSkillButton + 1);
	if (m_widget->getBlocks().size() > 0)
	{
		bt->setEnabled(true);
	}
	else
	{
		bt->setEnabled(false);
	}*/
}

bool DragModeGameMainScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	for (int i = kTagBaseSkillButton + 1; i <= kTagBaseSkillButton + 2; i++)
	{
		auto bt = getChildByTag(i);
		if (bt->getBoundingBox().containsPoint(touch->getLocation()))
		{
			return m_widget->beginUsingSkill(i);
		}
	}
	m_widget->onTouchBegan(touch, unused_event);
	return true;
}


//按键按下
void DragModeGameMainScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	//log("key:%d", (int)keyCode);

}

//按键弹起
void DragModeGameMainScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	onPause();
}

//退出游戏
void DragModeGameMainScene::ExitGame()
{
	//停止下落方块
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();



	////弹出对话框层
	//auto exit = ExitLayer::create();
	//exit->SetCallBackFunc(CC_CALLBACK_2(DragModeGameMainScene::buttonPopupCallback, this));
	//this->addChild(exit);
}

//确认退出游戏
void DragModeGameMainScene::DoExitGame()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void DragModeGameMainScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	m_widget->onTouchMoved(touch, unused_event);
}

void DragModeGameMainScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	m_widget->onTouchEnded(touch, unused_event);
}

void DragModeGameMainScene::onExit()
{
	Node::onExit();

	//释放方块资源
	SpriteManager::GetInstance()->UnInit();

	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->stopAllEffects();
	//利用plist文件卸载打包图片
	SpriteManager::GetInstance()->UnInitSpriteFramesWithFile("sprites.plist");
	SpriteManager::GetInstance()->UnInitSpriteFramesWithFile("game.plist");
}




//重新开始游戏
void DragModeGameMainScene::Restart()
{
	//行数、级数
	m_line = 0;
	m_level = 1;
	//分数清0
	m_widget->ResetScore();
	m_widget->Restart();
	////播放背景音乐
	//SimpleAudioEngine::getInstance()->playBackgroundMusic(AUDIO_BACKGROUND, true);
}

void DragModeGameMainScene::GameOver(int score)
{
	//播放失败音效
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playEffect(AUDIO_GAMEFAILED);


	//添加分数到sqlite数据库
	DBManager::GameScore gameScore;
	gameScore.name = "Unknown";
	gameScore.time = CommonFunction::GetCurrentTime();
	gameScore.score = score;
	DBManager::GetInstance()->AddScore(gameScore);





	//弹出游戏结束层
	auto popup = GameOverLayer::create(score);
	popup->setPosition(0, 0);
	this->addChild(popup,30);
}






void DragModeGameMainScene::onRebegin()
{
	onResum();
	Restart();
}
void DragModeGameMainScene::onPause()
{
	Audio::getInstance()->pauseBGM();
	pause();
	auto layer = PauseLayer::create();
	layer->setPosition(0, 0);
	addChild(layer,30);

}
void DragModeGameMainScene::onResum()
{
	Audio::getInstance()->resumeBGM();
	resume();
}
void DragModeGameMainScene::onBackMainScene()
{
	Director::getInstance()->replaceScene(MainScene::createScene());
}
void DragModeGameMainScene::onUseSkill(SkillInfo*skill)
{

	if (skill->num >= 0)
	{
		switch (skill->Id)
		{
		case Skill_Knock:
			m_widget->setgameTouchType(Touch_SkillKnock);
			break;
		case Skill_Fill:
			m_widget->setgameTouchType(Touch_SkillFill);
			break;
		case Skill_Revivi:
			//TODO:  复活;
			break;
		default:
			break;
		}
		ChangeNumOfSkillButoon((int)skill->Id, -1);
		DBManager::GetInstance()->SetSkillNum(skill->Id, DBManager::GetInstance()->GetSkillNum(skill->Id));
	}
	else
	{
		//起计费
	}
}
void DragModeGameMainScene::InitNotifications()
{
	BaseGame::InitNotifications();
	//游戏结束
	EventListenerCustom* listener = EventListenerCustom::create(MSG_GAMEOVER, [=](EventCustom* event){
		int score = *((int*)(event->getUserData()));
		GameOver(score);
	});
	getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);

}
void DragModeGameMainScene::ChangeNumOfSkillButoon(int skillid, int diffnum)
{
	auto bt = (SkillButton*)(getChildByTag(kTagBaseSkillButton+skillid));
	bt->ChangeSkillNum(diffnum);
}