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
#include <map>

USING_NS_CC;
using namespace ui;
using namespace CocosDenshion;
using std::map;

#define AUDIO_BACKGROUND	"sound/background.mp3"
#define AUDIO_DOWN			"sound/down.mp3"
#define AUDIO_EXPLODE		"sound/explode.mp3"
#define AUDIO_FAILED		"sound/failed.mp3"

DragModeGameMainScene::DragModeGameMainScene()
	: m_curGroup(NULL)
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
    if ( !Layer::init() )
    {
        return false;
    }

	//获取游戏区域
	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_origin = Director::getInstance()->getVisibleOrigin();
	m_winSize = Director::getInstance()->getWinSize();

	//层
	int nZOrderBackground = -10;
	int nZOrderWidget = -8;

	//利用plist文件初始化打包图片
	SpriteManager::GetInstance()->InitSpriteFramesWithFile("sprites.plist");
	SpriteManager::GetInstance()->InitSpriteFramesWithFile("game.plist");
	//添加背景图
	auto background = Sprite::create("background_main.png");
	background->setPosition(Vec2(m_origin.x + m_visibleSize.width / 2, m_origin.y + m_visibleSize.height / 2));
	this->addChild(background, nZOrderBackground);

	//添加ready方块背景图
	auto readyBoxFrame = Sprite::createWithSpriteFrameName("operateFrame.png");
	readyBoxFrame->setPosition(240, 130);
	addChild(readyBoxFrame, nZOrderBackground + 1);

	//添加小部件层
	m_widget = DragModeGameWidget::create();
	this->addChild(m_widget, nZOrderWidget);





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

	//const Vec2& posScore = m_widget->GetScorePosition();
	//const Vec2& posFirstBlock = m_widget->GetFirstBlockPosition();
	//const Size& sizeScore = m_widget->GetScoreSize();
	//const Rect& rectNext = m_widget->GetNextRect();

	////初始化GameField
	//GameField::GetInstance()->Init(posFirstBlock);

	////////////////////////////////////////////////////////////////////////////
	////添加背景图
	//auto background = Sprite::create("background.png");
	//background->setPosition(Vec2(m_origin.x + m_visibleSize.width/2, m_origin.y + m_visibleSize.height/2));
	//this->addChild(background, nZOrderBackground);

	////////////////////////////////////////////////////////////////////////////
	////添加方向按钮
	//auto bottomButton = Button::create("direction_bottom.png", "direction_bottom_pressed.png", "", Widget::TextureResType::PLIST);
	//bottomButton->setPosition(Vec2(posScore.x, m_origin.y + m_visibleSize.height/10 + bottomButton->getContentSize().height/2));
	//bottomButton->addTouchEventListener(CC_CALLBACK_2(DragModeGameMainScene::buttonSpeedupCallback, this));
	//this->addChild(bottomButton);

	//auto topButton = Button::create("direction_top.png", "direction_top_pressed.png", "", Widget::TextureResType::PLIST);
	//topButton->setPosition(Vec2(posScore.x, bottomButton->getPositionY() + bottomButton->getContentSize().height/2*3));
	//topButton->addTouchEventListener(CC_CALLBACK_2(DragModeGameMainScene::buttonDirectDownCallback, this));
	//this->addChild(topButton);

	//auto leftButton = Button::create("direction_left.png", "direction_left_pressed.png", "", Widget::TextureResType::PLIST);
	//leftButton->setPosition(Vec2(posScore.x - bottomButton->getContentSize().height/4 - leftButton->getContentSize().width/2,
	//	bottomButton->getPositionY() + bottomButton->getContentSize().height/4*3));
	//leftButton->addTouchEventListener(CC_CALLBACK_2(DragModeGameMainScene::buttonLeftCallback, this));
	//this->addChild(leftButton);

	//auto rightButton = Button::create("direction_right.png", "direction_right_pressed.png", "", Widget::TextureResType::PLIST);
	//rightButton->setPosition(Vec2(posScore.x + bottomButton->getContentSize().height/4 + rightButton->getContentSize().width/2,
	//	bottomButton->getPositionY() + bottomButton->getContentSize().height/4*3));
	//rightButton->addTouchEventListener(CC_CALLBACK_2(DragModeGameMainScene::buttonRightCallback, this));
	//this->addChild(rightButton);

	////添加旋转按钮
	//auto rotateButton = Button::create("rotate.png", "rotate_pressed.png", "", Widget::TextureResType::PLIST);
	//rotateButton->setPosition(Vec2(rectNext.origin.x + rectNext.size.width/2, bottomButton->getPositionY() + bottomButton->getContentSize().height/4*3));
	//rotateButton->addTouchEventListener(CC_CALLBACK_2(DragModeGameMainScene::buttonRotateCallback, this));
	//this->addChild(rotateButton);

	////////////////////////////////////////////////////////////////////////////
	////添加标签
	//m_labelLine = Label::createWithTTF("Line: 0", "fonts/Marker Felt.ttf", 40);
	//float nInterval = ((posScore.y - sizeScore.height/2) - (topButton->getPositionY() + topButton->getContentSize().height/2)) / 2;
	//m_labelLine->setPosition(Vec2(posScore.x, topButton->getPositionY() + topButton->getContentSize().height/2 + nInterval));
	//this->addChild(m_labelLine);
	//m_labelLevel = Label::createWithTTF("Level: 1", "fonts/Marker Felt.ttf", 40);
	//m_labelLevel->setPosition(Vec2(rotateButton->getPositionX(), m_labelLine->getPositionY()));
	//this->addChild(m_labelLevel);

	////设置随机数种子
	//srand((unsigned)time(NULL));

	////设置游戏参数
	//m_level = 1;		//级别
	//m_score = 0;		//分数
	//m_line = 0;			//消去的行数


	////获取当前图形
	//m_widget->GetNextBlockGroup(m_curGroup, this);

	////利用plist文件卸载打包图片
	//SpriteManager::GetInstance()->UnInitSpriteFramesWithFile("sprites.plist");

	////定时移动当前图形
	//this->schedule(schedule_selector(DragModeGameMainScene::MoveDownCurBlockGroup), 1.0f / m_level);

	//触摸屏事件监听
	m_touchListener = EventListenerTouchOneByOne::create();
	//m_touchListener->onTouchBegan = [&](Touch* touch, Event* unused_event)->bool { return true; };
	m_touchListener->onTouchBegan = CC_CALLBACK_2(DragModeGameMainScene::onTouchBegan, this);
	m_touchListener->onTouchMoved = CC_CALLBACK_2(DragModeGameMainScene::onTouchMoved, this);
	m_touchListener->onTouchEnded = CC_CALLBACK_2(DragModeGameMainScene::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_touchListener, this);
	//利用plist文件卸载打包图片
	SpriteManager::GetInstance()->UnInitSpriteFramesWithFile("sprites.plist");
	SpriteManager::GetInstance()->UnInitSpriteFramesWithFile("game.plist");
	////Android按键监听
	//m_keyboardListener = EventListenerKeyboard::create();
	//m_keyboardListener->onKeyPressed = CC_CALLBACK_2(DragModeGameMainScene::onKeyPressed, this);
	//m_keyboardListener->onKeyReleased = CC_CALLBACK_2(DragModeGameMainScene::onKeyReleased, this);
	//this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_keyboardListener, this);

	////弹出层不启用
	//m_bPopupLayerWorking = false;

	////添加音效
	//SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_DOWN);
	//SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_EXPLODE);
	//SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_FAILED);
	//SimpleAudioEngine::getInstance()->preloadBackgroundMusic(AUDIO_BACKGROUND);

	////播放背景音乐
	//SimpleAudioEngine::getInstance()->playBackgroundMusic(AUDIO_BACKGROUND, true);

	////设置音效音量
	//float fVolumeBgm = DBManager::GetInstance()->GetBgmVolume();
	//float fVolumeEffects = DBManager::GetInstance()->GetEffectsVolume();
	////GameDifficulty diff = DBManager::GetInstance()->GetGameDifficulty();
	//SimpleAudioEngine::getInstance()->setEffectsVolume(fVolumeBgm);
	//SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(fVolumeEffects);

    return true;
}

void DragModeGameMainScene::update(float delta)
{

}

bool DragModeGameMainScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	auto touchLocation = touch->getLocation();
	//log("point(%f, %f)\n", touchLocation.x, touchLocation.y);
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


	//弹出层标记
	m_bPopupLayerWorking = true;

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
	//触摸点坐标
	auto touchLocation = touch->getLocation();
	m_widget->onTouchMoved(touch, unused_event);
}

void DragModeGameMainScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	//停止左右移动
	//m_moveState = BlockMove::BLOCKMOVE_NONE;
	m_widget->onTouchEnded(touch, unused_event);
}

void DragModeGameMainScene::onExit()
{
	Node::onExit();

	//释放方块资源
	SpriteManager::GetInstance()->UnInit();

	//释放音频资源
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->stopAllEffects();
	SimpleAudioEngine::getInstance()->unloadEffect(AUDIO_DOWN);
	SimpleAudioEngine::getInstance()->unloadEffect(AUDIO_EXPLODE);
	SimpleAudioEngine::getInstance()->unloadEffect(AUDIO_FAILED);
}




//重新开始游戏
void DragModeGameMainScene::Restart()
{
	//触摸屏事件监听
	m_touchListener = EventListenerTouchOneByOne::create();
	//m_touchListener->onTouchBegan = [&](Touch* touch, Event* unused_event)->bool { return true; };
	m_touchListener->onTouchBegan = CC_CALLBACK_2(DragModeGameMainScene::onTouchBegan, this);
	m_touchListener->onTouchMoved = CC_CALLBACK_2(DragModeGameMainScene::onTouchMoved, this);
	m_touchListener->onTouchEnded = CC_CALLBACK_2(DragModeGameMainScene::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_touchListener, this);

	//Android按键监听
	m_keyboardListener = EventListenerKeyboard::create();
	m_keyboardListener->onKeyPressed = CC_CALLBACK_2(DragModeGameMainScene::onKeyPressed, this);
	m_keyboardListener->onKeyReleased = CC_CALLBACK_2(DragModeGameMainScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_keyboardListener, this);

	//弹出层标记
	m_bPopupLayerWorking = false;

	//行数、级数
	m_line = 0;
	m_level = 1;


	//分数清0
	m_widget->ResetScore();

	//重置所有方块
	vector<BlockObject>::iterator itBlock;
	for (itBlock=m_vecBlocks.begin(); itBlock!=m_vecBlocks.end(); ++itBlock)
	{
		removeChild(itBlock->sprite);
	}
	m_vecBlocks.clear();

	//获取下一个方块
	delete m_curGroup;
	m_curGroup = NULL;


	////定时移动当前图形
	//this->unschedule(schedule_selector(DragModeGameMainScene::MoveDownCurBlockGroup));
	//this->schedule(schedule_selector(DragModeGameMainScene::MoveDownCurBlockGroup), 1.0f / m_level);

	//播放背景音乐
	SimpleAudioEngine::getInstance()->playBackgroundMusic(AUDIO_BACKGROUND, true);
}

void DragModeGameMainScene::GameOver()
{
	//播放失败音效
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playEffect(AUDIO_FAILED);
	//this->unschedule(schedule_selector(DragModeGameMainScene::MoveDownCurBlockGroup));

// 	auto logo = LogoScene::createScene();
// 	Director::getInstance()->replaceScene(logo);
// 	return;
	//this->unscheduleAllCallbacks();

	//触摸屏事件监听
// 	auto listener = EventListenerTouchOneByOne::create();
// 	listener->onTouchBegan = [&](Touch* touch, Event* unused_event)->bool { return true; };
// 	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
// 	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
// 	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
// 	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//this->getEventDispatcher()->removeAllEventListeners();

	//添加分数到sqlite数据库
	DBManager::GameScore gameScore;
	gameScore.name = "Unknown";
	gameScore.time = CommonFunction::GetCurrentTime();
	gameScore.score = m_widget->GetScore();
	DBManager::GetInstance()->AddScore(gameScore);

	//显示分数
	std::stringstream ss;
	ss << m_widget->GetScore();
	std::string strScore = ss.str();
	auto score = StringManager::GetInstance()->GetString("score");

	//弹出层标记
	m_bPopupLayerWorking = true;

	//弹出游戏结束层
	auto popup = GameOverLayer::create();
	popup->setPosition(0, 0);
	this->addChild(popup);
}






void DragModeGameMainScene::onRebegin()
{
	Restart();
}
void DragModeGameMainScene::onPause()
{
	pause();
	auto layer = PauseLayer::create();
	layer->setPosition(0, 0);
	addChild(layer);

}
void DragModeGameMainScene::onResum()
{
	resume();
}
void DragModeGameMainScene::onBackMainScene()
{
	Director::getInstance()->replaceScene(MainScene::createScene());
}
void DragModeGameMainScene::onUseSkill(SkillInfo*skill)
{

}