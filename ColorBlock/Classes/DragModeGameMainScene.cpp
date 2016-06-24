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

	//��ȡ��Ϸ����
	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_origin = Director::getInstance()->getVisibleOrigin();
	m_winSize = Director::getInstance()->getWinSize();

	//��
	int nZOrderBackground = -10;
	int nZOrderWidget = -8;

	//����plist�ļ���ʼ�����ͼƬ
	SpriteManager::GetInstance()->InitSpriteFramesWithFile("sprites.plist");
	SpriteManager::GetInstance()->InitSpriteFramesWithFile("game.plist");
	//��ӱ���ͼ
	auto background = Sprite::create("background_main.png");
	background->setPosition(Vec2(m_origin.x + m_visibleSize.width / 2, m_origin.y + m_visibleSize.height / 2));
	this->addChild(background, nZOrderBackground);

	//���ready���鱳��ͼ
	auto readyBoxFrame = Sprite::createWithSpriteFrameName("operateFrame.png");
	readyBoxFrame->setPosition(240, 130);
	addChild(readyBoxFrame, nZOrderBackground + 1);

	//���С������
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

	////��ʼ��GameField
	//GameField::GetInstance()->Init(posFirstBlock);

	////////////////////////////////////////////////////////////////////////////
	////��ӱ���ͼ
	//auto background = Sprite::create("background.png");
	//background->setPosition(Vec2(m_origin.x + m_visibleSize.width/2, m_origin.y + m_visibleSize.height/2));
	//this->addChild(background, nZOrderBackground);

	////////////////////////////////////////////////////////////////////////////
	////��ӷ���ť
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

	////�����ת��ť
	//auto rotateButton = Button::create("rotate.png", "rotate_pressed.png", "", Widget::TextureResType::PLIST);
	//rotateButton->setPosition(Vec2(rectNext.origin.x + rectNext.size.width/2, bottomButton->getPositionY() + bottomButton->getContentSize().height/4*3));
	//rotateButton->addTouchEventListener(CC_CALLBACK_2(DragModeGameMainScene::buttonRotateCallback, this));
	//this->addChild(rotateButton);

	////////////////////////////////////////////////////////////////////////////
	////��ӱ�ǩ
	//m_labelLine = Label::createWithTTF("Line: 0", "fonts/Marker Felt.ttf", 40);
	//float nInterval = ((posScore.y - sizeScore.height/2) - (topButton->getPositionY() + topButton->getContentSize().height/2)) / 2;
	//m_labelLine->setPosition(Vec2(posScore.x, topButton->getPositionY() + topButton->getContentSize().height/2 + nInterval));
	//this->addChild(m_labelLine);
	//m_labelLevel = Label::createWithTTF("Level: 1", "fonts/Marker Felt.ttf", 40);
	//m_labelLevel->setPosition(Vec2(rotateButton->getPositionX(), m_labelLine->getPositionY()));
	//this->addChild(m_labelLevel);

	////�������������
	//srand((unsigned)time(NULL));

	////������Ϸ����
	//m_level = 1;		//����
	//m_score = 0;		//����
	//m_line = 0;			//��ȥ������


	////��ȡ��ǰͼ��
	//m_widget->GetNextBlockGroup(m_curGroup, this);

	////����plist�ļ�ж�ش��ͼƬ
	//SpriteManager::GetInstance()->UnInitSpriteFramesWithFile("sprites.plist");

	////��ʱ�ƶ���ǰͼ��
	//this->schedule(schedule_selector(DragModeGameMainScene::MoveDownCurBlockGroup), 1.0f / m_level);

	//�������¼�����
	m_touchListener = EventListenerTouchOneByOne::create();
	//m_touchListener->onTouchBegan = [&](Touch* touch, Event* unused_event)->bool { return true; };
	m_touchListener->onTouchBegan = CC_CALLBACK_2(DragModeGameMainScene::onTouchBegan, this);
	m_touchListener->onTouchMoved = CC_CALLBACK_2(DragModeGameMainScene::onTouchMoved, this);
	m_touchListener->onTouchEnded = CC_CALLBACK_2(DragModeGameMainScene::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_touchListener, this);
	//����plist�ļ�ж�ش��ͼƬ
	SpriteManager::GetInstance()->UnInitSpriteFramesWithFile("sprites.plist");
	SpriteManager::GetInstance()->UnInitSpriteFramesWithFile("game.plist");
	////Android��������
	//m_keyboardListener = EventListenerKeyboard::create();
	//m_keyboardListener->onKeyPressed = CC_CALLBACK_2(DragModeGameMainScene::onKeyPressed, this);
	//m_keyboardListener->onKeyReleased = CC_CALLBACK_2(DragModeGameMainScene::onKeyReleased, this);
	//this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_keyboardListener, this);

	////�����㲻����
	//m_bPopupLayerWorking = false;

	////�����Ч
	//SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_DOWN);
	//SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_EXPLODE);
	//SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_FAILED);
	//SimpleAudioEngine::getInstance()->preloadBackgroundMusic(AUDIO_BACKGROUND);

	////���ű�������
	//SimpleAudioEngine::getInstance()->playBackgroundMusic(AUDIO_BACKGROUND, true);

	////������Ч����
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


//��������
void DragModeGameMainScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	//log("key:%d", (int)keyCode);

}

//��������
void DragModeGameMainScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	onPause();
}

//�˳���Ϸ
void DragModeGameMainScene::ExitGame()
{
	//ֹͣ���䷽��
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();


	//��������
	m_bPopupLayerWorking = true;

	////�����Ի����
	//auto exit = ExitLayer::create();
	//exit->SetCallBackFunc(CC_CALLBACK_2(DragModeGameMainScene::buttonPopupCallback, this));
	//this->addChild(exit);
}

//ȷ���˳���Ϸ
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
	//����������
	auto touchLocation = touch->getLocation();
	m_widget->onTouchMoved(touch, unused_event);
}

void DragModeGameMainScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	//ֹͣ�����ƶ�
	//m_moveState = BlockMove::BLOCKMOVE_NONE;
	m_widget->onTouchEnded(touch, unused_event);
}

void DragModeGameMainScene::onExit()
{
	Node::onExit();

	//�ͷŷ�����Դ
	SpriteManager::GetInstance()->UnInit();

	//�ͷ���Ƶ��Դ
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->stopAllEffects();
	SimpleAudioEngine::getInstance()->unloadEffect(AUDIO_DOWN);
	SimpleAudioEngine::getInstance()->unloadEffect(AUDIO_EXPLODE);
	SimpleAudioEngine::getInstance()->unloadEffect(AUDIO_FAILED);
}




//���¿�ʼ��Ϸ
void DragModeGameMainScene::Restart()
{
	//�������¼�����
	m_touchListener = EventListenerTouchOneByOne::create();
	//m_touchListener->onTouchBegan = [&](Touch* touch, Event* unused_event)->bool { return true; };
	m_touchListener->onTouchBegan = CC_CALLBACK_2(DragModeGameMainScene::onTouchBegan, this);
	m_touchListener->onTouchMoved = CC_CALLBACK_2(DragModeGameMainScene::onTouchMoved, this);
	m_touchListener->onTouchEnded = CC_CALLBACK_2(DragModeGameMainScene::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_touchListener, this);

	//Android��������
	m_keyboardListener = EventListenerKeyboard::create();
	m_keyboardListener->onKeyPressed = CC_CALLBACK_2(DragModeGameMainScene::onKeyPressed, this);
	m_keyboardListener->onKeyReleased = CC_CALLBACK_2(DragModeGameMainScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_keyboardListener, this);

	//��������
	m_bPopupLayerWorking = false;

	//����������
	m_line = 0;
	m_level = 1;


	//������0
	m_widget->ResetScore();

	//�������з���
	vector<BlockObject>::iterator itBlock;
	for (itBlock=m_vecBlocks.begin(); itBlock!=m_vecBlocks.end(); ++itBlock)
	{
		removeChild(itBlock->sprite);
	}
	m_vecBlocks.clear();

	//��ȡ��һ������
	delete m_curGroup;
	m_curGroup = NULL;


	////��ʱ�ƶ���ǰͼ��
	//this->unschedule(schedule_selector(DragModeGameMainScene::MoveDownCurBlockGroup));
	//this->schedule(schedule_selector(DragModeGameMainScene::MoveDownCurBlockGroup), 1.0f / m_level);

	//���ű�������
	SimpleAudioEngine::getInstance()->playBackgroundMusic(AUDIO_BACKGROUND, true);
}

void DragModeGameMainScene::GameOver()
{
	//����ʧ����Ч
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playEffect(AUDIO_FAILED);
	//this->unschedule(schedule_selector(DragModeGameMainScene::MoveDownCurBlockGroup));

// 	auto logo = LogoScene::createScene();
// 	Director::getInstance()->replaceScene(logo);
// 	return;
	//this->unscheduleAllCallbacks();

	//�������¼�����
// 	auto listener = EventListenerTouchOneByOne::create();
// 	listener->onTouchBegan = [&](Touch* touch, Event* unused_event)->bool { return true; };
// 	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
// 	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
// 	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
// 	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//this->getEventDispatcher()->removeAllEventListeners();

	//��ӷ�����sqlite���ݿ�
	DBManager::GameScore gameScore;
	gameScore.name = "Unknown";
	gameScore.time = CommonFunction::GetCurrentTime();
	gameScore.score = m_widget->GetScore();
	DBManager::GetInstance()->AddScore(gameScore);

	//��ʾ����
	std::stringstream ss;
	ss << m_widget->GetScore();
	std::string strScore = ss.str();
	auto score = StringManager::GetInstance()->GetString("score");

	//��������
	m_bPopupLayerWorking = true;

	//������Ϸ������
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