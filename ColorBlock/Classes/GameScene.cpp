#include "GameScene.h"
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

#include <map>

USING_NS_CC;
using namespace ui;
using namespace CocosDenshion;
using std::map;

#define AUDIO_BACKGROUND	"sound/background.mp3"
#define AUDIO_DOWN			"sound/down.mp3"
#define AUDIO_EXPLODE		"sound/explode.mp3"
#define AUDIO_FAILED		"sound/failed.mp3"

GameScene::GameScene()
	: m_curGroup(NULL)
{

}

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	//设置随机数种子
	srand((unsigned)time(NULL));

	//设置游戏参数
	m_level = 1;		//级别
	m_score = 0;		//分数
	m_line = 0;			//消去的行数
	m_moveState = BlockMove::BLOCKMOVE_NONE;
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

	//添加小部件层
	m_widget = GameWidget::create();
	this->addChild(m_widget, nZOrderWidget);
	const Vec2& posScore = m_widget->GetScorePosition();
	const Vec2& posFirstBlock = m_widget->GetFirstBlockPosition();
	const Size& sizeScore = m_widget->GetScoreSize();
	const Rect& rectNext = m_widget->GetNextRect();

	//初始化GameField
	GameField::GetInstance()->Init(posFirstBlock);

	//////////////////////////////////////////////////////////////////////////
	//添加背景图
	auto background = Sprite::create("background_main.png");
	background->setPosition(Vec2(m_origin.x + m_visibleSize.width/2, m_origin.y + m_visibleSize.height/2));
	this->addChild(background, nZOrderBackground);


	auto girdboxFrame = Sprite::createWithSpriteFrameName("girdBoxesFrame.png");
	girdboxFrame->setPosition(m_visibleSize / 2);
	addChild(girdboxFrame, nZOrderBackground);



	//////////////////////////////////////////////////////////////////////////

	float cx = 100;
	float cy = 110;
	float dx = 95;
	//添加方向按钮
	
	auto leftButton = Button::create("btLeft_1.png", "btLeft_2.png", "", Widget::TextureResType::PLIST);
	leftButton->setPosition(Vec2(cx, cy));
	leftButton->addTouchEventListener(CC_CALLBACK_2(GameScene::buttonLeftCallback, this));
	this->addChild(leftButton);
	cx += dx;

	auto bottomButton = Button::create("btBottom.png", "btBottom.png", "", Widget::TextureResType::PLIST);
	bottomButton->setPosition(Vec2(cx, cy));
	bottomButton->addTouchEventListener(CC_CALLBACK_2(GameScene::buttonSpeedupCallback, this));
	this->addChild(bottomButton);
	cx += dx;

	//添加旋转按钮
	auto rotateButton = Button::create("btRotate_1.png", "btRotate_2.png", "", Widget::TextureResType::PLIST);
	rotateButton->setPosition(Vec2(cx, cy));
	rotateButton->addTouchEventListener(CC_CALLBACK_2(GameScene::buttonRotateCallback, this));
	this->addChild(rotateButton);
	cx += dx;

	auto rightButton = Button::create("btRight_1.png", "btRight_2.png", "", Widget::TextureResType::PLIST);
	rightButton->setPosition(Vec2(cx, cy));
	rightButton->addTouchEventListener(CC_CALLBACK_2(GameScene::buttonRightCallback, this));
	this->addChild(rightButton);
	cx += dx;


	//////////////////////////////////////////////////////////////////////////
	//添加标签
	m_labelLine = LabelAtlas::create(Value(m_line).asString(),"scoreNum.png",16,25,'0');
	m_labelLine->setPosition(70,611);
	m_labelLine->setAnchorPoint(Point::ANCHOR_MIDDLE);
	this->addChild(m_labelLine);




	//获取当前图形
	m_widget->GetNextBlockGroup(m_curGroup, this);

	//利用plist文件卸载打包图片
	SpriteManager::GetInstance()->UnInitSpriteFramesWithFile("sprites.plist");
	SpriteManager::GetInstance()->UnInitSpriteFramesWithFile("game.plist");
	//定时移动当前图形
	this->schedule(schedule_selector(GameScene::MoveDownCurBlockGroup), 1.0f / m_level);

	//触摸屏事件监听
	m_touchListener = EventListenerTouchOneByOne::create();
	//m_touchListener->onTouchBegan = [&](Touch* touch, Event* unused_event)->bool { return true; };
	m_touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	m_touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	m_touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_touchListener, this);

	//Android按键监听
	m_keyboardListener = EventListenerKeyboard::create();
	m_keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	m_keyboardListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_keyboardListener, this);

	//弹出层不启用
	m_bPopupLayerWorking = false;

	//添加音效
	SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_DOWN);
	SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_EXPLODE);
	SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_FAILED);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(AUDIO_BACKGROUND);

	//播放背景音乐
	SimpleAudioEngine::getInstance()->playBackgroundMusic(AUDIO_BACKGROUND, true);

	//设置音效音量
	float fVolumeBgm = DBManager::GetInstance()->GetBgmVolume();
	float fVolumeEffects = DBManager::GetInstance()->GetEffectsVolume();
	//GameDifficulty diff = DBManager::GetInstance()->GetGameDifficulty();
	SimpleAudioEngine::getInstance()->setEffectsVolume(fVolumeBgm);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(fVolumeEffects);

    return true;
}

void GameScene::update(float delta)
{

}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	auto touchLocation = touch->getLocation();
	//log("point(%f, %f)\n", touchLocation.x, touchLocation.y);


	return true;
}

//按键按下
void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	//log("key:%d", (int)keyCode);
	if (m_bPopupLayerWorking)
	{
		return;
	}
	
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
		buttonRotateCallback(this, Widget::TouchEventType::BEGAN);
		break;
	case EventKeyboard::KeyCode::KEY_W:
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		buttonDirectDownCallback(this, ui::Widget::TouchEventType::BEGAN);
		break;
	case EventKeyboard::KeyCode::KEY_S:
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		buttonSpeedupCallback(this, ui::Widget::TouchEventType::BEGAN);
		break;
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		buttonLeftCallback(this, ui::Widget::TouchEventType::BEGAN);
		break;
	case EventKeyboard::KeyCode::KEY_D:
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		buttonRightCallback(this, ui::Widget::TouchEventType::BEGAN);
		break;
	default:
		break;
	}
}

//按键弹起
void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	//log("key:%d", (int)keyCode);
	if (m_bPopupLayerWorking)
	{
		return;
	}

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_BACK:	//返回键(Only avaliable on Desktop and Android)
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		//退出游戏
		ExitGame();
#endif
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		buttonRotateCallback(this, Widget::TouchEventType::ENDED);
		break;
	case EventKeyboard::KeyCode::KEY_W:
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		buttonDirectDownCallback(this, ui::Widget::TouchEventType::ENDED);
		break;
	case EventKeyboard::KeyCode::KEY_S:
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		buttonSpeedupCallback(this, ui::Widget::TouchEventType::ENDED);
		break;
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		buttonLeftCallback(this, ui::Widget::TouchEventType::ENDED);
		break;
	case EventKeyboard::KeyCode::KEY_D:
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		buttonRightCallback(this, ui::Widget::TouchEventType::ENDED);
		break;
	default:
		break;
	}
}

//退出游戏
void GameScene::ExitGame()
{
	//停止下落方块
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	this->unschedule(schedule_selector(GameScene::MoveDownCurBlockGroup));

	//弹出层标记
	m_bPopupLayerWorking = true;

	//弹出对话框层
	auto exit = ExitLayer::create();
	exit->SetCallBackFunc(CC_CALLBACK_2(GameScene::buttonPopupCallback, this));
	this->addChild(exit);
}

//确认退出游戏
void GameScene::DoExitGame()
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

void GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	//触摸点坐标
	auto touchLocation = touch->getLocation();

}

void GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	//停止左右移动
	//m_moveState = BlockMove::BLOCKMOVE_NONE;

}

void GameScene::onExit()
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

//向下移动当前图形
void GameScene::MoveDownCurBlockGroup(float dt)
{
	//弹出层启用时候不作处理
	if (m_bPopupLayerWorking)
	{
		return;
	}

	const Size& size = SpriteManager::GetInstance()->GetBlockSize();
	if (/*m_curGroup->MoveDown(m_vecBlocks)*/IsCurBlockGroupCanMoveDown())
	{
		//向下移动
		for (int i=0; i<4; i++)
		{
			m_curGroup->GetBlocks()[i].row++;	//方块行数加1
			m_curGroup->ResetBlockPosition(i);	//重新设置方块的坐标
		}

		//落到最低处
		if (!IsCurBlockGroupCanMoveDown())
		{
			//播放方块落地的音效
			SimpleAudioEngine::getInstance()->playEffect(AUDIO_DOWN);

			//添加当前图形中的方块到方块集合中
			//AddCurBlockGroupToBlocks();
		}
	}
	else
	{
		//添加当前图形中的方块到方块集合中
		AddCurBlockGroupToBlocks();
	}
}

//判断当前图形是否可以下落
bool GameScene::IsCurBlockGroupCanMoveDown()
{
	bool bAdjoined = false;
	vector<BlockObject>::const_iterator cit;
	for (int i=0; i<4; i++)
	{
		const BlockObject& curBlobk = m_curGroup->GetBlocks()[i];

		//判断是否到底
		if (curBlobk.row >= GameField::GetInstance()->GetBlockRowCount() - 1)
		{
			bAdjoined = true;
			break;
		}

		//判断是否和已有方块上下相邻
		for (cit=m_vecBlocks.begin(); cit!=m_vecBlocks.end(); ++cit)
		{
			const BlockObject& block = *cit;
			if ((curBlobk.col == block.col) && (curBlobk.row + 1 == block.row))
			{
				bAdjoined = true;
				break;
			}
		}

		if (bAdjoined)
		{
			break;
		}
	}

	return !bAdjoined;
}

//添加当前图形中的方块到方块集合中
void GameScene::AddCurBlockGroupToBlocks()
{
	//将当前方块添加到方块集合
	for (int i=0; i<4; i++)
	{
		m_vecBlocks.push_back(m_curGroup->GetBlocks()[i]);
	}

	//消去满行的方块
	if (!ReleaseBlocksOnFullLine())
	{
		//落下一行得分
		m_widget->BlockGroupLanding();

		//播放方块落地的音效
		//SimpleAudioEngine::getInstance()->playEffect(AUDIO_DOWN);
	}
	else
	{
		//播放消去行的音效
		SimpleAudioEngine::getInstance()->playEffect(AUDIO_EXPLODE);
	}

	//方块是否到顶
	int lowest = 0;
	vector<BlockObject>::const_iterator cit;
	for (cit=m_vecBlocks.begin(); cit!=m_vecBlocks.end(); ++cit)
	{
		if (lowest > cit->row)
		{
			lowest = cit->row;
		}

		if (lowest < 0)
		{
			GameOver();	//游戏结束
			return;
		}
	}

	//重置当前图形
	delete m_curGroup;
	m_curGroup = NULL;
	m_widget->GetNextBlockGroup(m_curGroup, this);
}

//消去同行的方块
bool GameScene::ReleaseBlocksOnFullLine()
{
	//获取所有行数（已经从小到大排好序）
	map<int/*行号*/, int/*当前行的方块数*/> mapRow;
	m_vecFullRow.clear();
	vector<BlockObject>::const_iterator cit;
	for (cit=m_vecBlocks.begin(); cit!=m_vecBlocks.end(); ++cit)
	{
		if (++mapRow[cit->row] == GameField::GetInstance()->GetBlockColCount())
		{
			m_vecFullRow.push_back(cit->row);
		}
	}

	//没有可以消去的行
	if (m_vecFullRow.empty())
	{
		return false;
	}

	//获得连续消去的行数
	int nSeriesNumber = 1;
	switch (m_vecFullRow.size())
	{
	case 2:
		nSeriesNumber = (m_vecFullRow.at(0) + 1 == m_vecFullRow.at(1)) ? 2 : 1;
		break;
	case 3:
		nSeriesNumber = (m_vecFullRow.at(0) + 1 == m_vecFullRow.at(1) && m_vecFullRow.at(1) + 1 == m_vecFullRow.at(2)) ? 3 : 2;
		break;
	case 4:
		nSeriesNumber = 4;
		break;
	default:
		break;
	}

	//加分数
	int score = m_vecFullRow.size() * 5;				//消去一行得5分
	int scoresExtra[] = {3, 5, 8};						//连续消去2,3,4行额外得3,5,8分
	if (nSeriesNumber >= 2 && nSeriesNumber <= 4)
	{
		score += scoresExtra[nSeriesNumber - 2];		//额外加分
	}
	m_score += score;

	//加分
	m_widget->AddScore(m_vecFullRow);

	//增加行数
	m_line += nSeriesNumber;
	if (m_line / 25 >= m_level)
	{
		//修改移动当前图形的速度
		this->unschedule(schedule_selector(GameScene::MoveDownCurBlockGroup));
		this->schedule(schedule_selector(GameScene::MoveDownCurBlockGroup), 1.0f / ++m_level);
		RefreshLevel();
	}
	RefreshLine();

	//消去方块
	vector<BlockObject>::iterator it;
	vector<int>::const_iterator citFullRow;
	for (citFullRow=m_vecFullRow.begin(); citFullRow!=m_vecFullRow.end(); ++citFullRow)
	{
		for (it=m_vecBlocks.begin(); it!=m_vecBlocks.end();)
		{
			if (*citFullRow == it->row)
			{
				//消去满行的方块
				this->removeChild(it->sprite);
				it = m_vecBlocks.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	//定时消去满行的方块
	this->scheduleOnce(schedule_selector(GameScene::RemoveFullRowBlocks), 0.3f);

	//播放消去音效
	return true;
}

void GameScene::RemoveFullRowBlocks(float dt)
{
	vector<BlockObject>::iterator itBlock;
	vector<int>::const_iterator citFullRow;
	for (citFullRow=m_vecFullRow.begin(); citFullRow!=m_vecFullRow.end(); ++citFullRow)
	{
		for (itBlock=m_vecBlocks.begin(); itBlock!=m_vecBlocks.end(); ++itBlock)
		{
			if (itBlock->row < *citFullRow)
			{
				//在满行上面的方块向下移动
				itBlock->row++;
				BlockGroup::ResetBlockPosition(*itBlock);
			}
		}
	}
}

//左右移动当前图形
void GameScene::MoveLeftrightCurBlockGroup(float dt)
{
	switch (m_moveState)
	{
	case BlockMove::BLOCKMOVE_LEFT:		//向左移动
		m_curGroup->MoveLeft(m_vecBlocks);
		break;
	case BlockMove::BLOCKMOVE_RIGHT:	//向右移动
		m_curGroup->MoveRight(m_vecBlocks);
		break;
	case BlockMove::BLOCKMOVE_NONE:		//停止移动
		this->unschedule(schedule_selector(GameScene::MoveLeftrightCurBlockGroup));
		break;
	default:
		break;
	}
}

//弹出框按钮事件
void GameScene::buttonPopupCallback(Ref* sender, ButtonResult result)
{
	//弹出层标记
	m_bPopupLayerWorking = false;

	switch (result)
	{
	case ButtonResult::BUTTONRESULT_OK:			//继续游戏
		Restart();
		break;
	case ButtonResult::BUTTONRESULT_CANCEL:		//返回主界面
		Director::getInstance()->replaceScene(MainScene::createScene());
		break;
	case ButtonResult::BUTTONRESULT_EXIT:		//退出游戏
		DoExitGame();
		break;
	case ButtonResult::BUTTONRESULT_CONTINUE:	//取消退出游戏
		SimpleAudioEngine::getInstance()->playBackgroundMusic(AUDIO_BACKGROUND, true);
		this->schedule(schedule_selector(GameScene::MoveDownCurBlockGroup), 1.0f / m_level);
		break;
	case ButtonResult::BUTTONRESULT_NONE:
		NULL;
		break;
	default:
		break;
	}
}

//重新开始游戏
void GameScene::Restart()
{
	//触摸屏事件监听
	m_touchListener = EventListenerTouchOneByOne::create();
	//m_touchListener->onTouchBegan = [&](Touch* touch, Event* unused_event)->bool { return true; };
	m_touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	m_touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	m_touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_touchListener, this);

	//Android按键监听
	m_keyboardListener = EventListenerKeyboard::create();
	m_keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	m_keyboardListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_keyboardListener, this);

	//弹出层标记
	m_bPopupLayerWorking = false;

	//行数、级数
	m_line = 0;
	m_level = 1;
	RefreshLine();
	RefreshLevel();

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
	m_widget->GetNextBlockGroup(m_curGroup, this);

	//定时移动当前图形
	this->unschedule(schedule_selector(GameScene::MoveDownCurBlockGroup));
	this->schedule(schedule_selector(GameScene::MoveDownCurBlockGroup), 1.0f / m_level);

	//播放背景音乐
	SimpleAudioEngine::getInstance()->playBackgroundMusic(AUDIO_BACKGROUND, true);
}

void GameScene::GameOver()
{
	//播放失败音效
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playEffect(AUDIO_FAILED);
	this->unschedule(schedule_selector(GameScene::MoveDownCurBlockGroup));

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
 	popup->SetTitle(score);
 	popup->SetContent(strScore);
	popup->SetCallBackFunc(CC_CALLBACK_2(GameScene::buttonPopupCallback, this));
	popup->SetButtonType(ButtonType::BUTTONTYPE_OKCANCEL);
	this->addChild(popup);
}

//////////////////////////////////////////////////////////////////////////
//自定义按钮事件
void GameScene::buttonSpeedupCallback(Ref* sender, cocos2d::ui::Widget::TouchEventType event)
{
	switch (event)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		//定时加速移动当前图形（每秒20次）
		this->unschedule(schedule_selector(GameScene::MoveDownCurBlockGroup));
		this->schedule(schedule_selector(GameScene::MoveDownSpeedup), 1.0f/20);
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		NULL;
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		//取消定时加速移动当前图形
		this->unschedule(schedule_selector(GameScene::MoveDownSpeedup));
		this->schedule(schedule_selector(GameScene::MoveDownCurBlockGroup), 1.0f/m_level);
		break;
	default:
		break;
	}
}

//左移
void GameScene::buttonLeftCallback(Ref* sender, cocos2d::ui::Widget::TouchEventType event)
{
	switch (event)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		//定时向左移动(每帧移动一次)
		//float fps = Director::getInstance()->getFrameRate();
		//fps = 10;
		m_curGroup->MoveLeft(m_vecBlocks);
		m_moveState = BlockMove::BLOCKMOVE_LEFT;
		this->schedule(schedule_selector(GameScene::MoveLeftrightCurBlockGroup), 1.0f/(6*m_level >= 30 ? 30 : 6*m_level));
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		NULL;
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		m_moveState = BlockMove::BLOCKMOVE_NONE;
		break;
	default:
		break;
	}
}

//右移
void GameScene::buttonRightCallback(Ref* sender, cocos2d::ui::Widget::TouchEventType event)
{
	switch (event)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		//定时向右移动(每帧移动一次)
		//float fps = Director::getInstance()->getFrameRate();
		//fps = 10;
		m_curGroup->MoveRight(m_vecBlocks);
		m_moveState = BlockMove::BLOCKMOVE_RIGHT;
		this->schedule(schedule_selector(GameScene::MoveLeftrightCurBlockGroup), 1.0f/(6*m_level >= 30 ? 30 : 6*m_level));
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		NULL;
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		m_moveState = BlockMove::BLOCKMOVE_NONE;
		break;
	default:
		break;
	}
}

//旋转
void GameScene::buttonRotateCallback(Ref* sender, cocos2d::ui::Widget::TouchEventType event)
{
	if (cocos2d::ui::Widget::TouchEventType::BEGAN == event)
	{
		m_curGroup->Rotate(m_vecBlocks);
	}
}

//立即下降
void GameScene::buttonDirectDownCallback(Ref* sender, cocos2d::ui::Widget::TouchEventType event)
{
	switch (event)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		m_curGroup->MoveDownDirect(m_vecBlocks, 1);
		MoveDownCurBlockGroup(0);
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		NULL;
		break;
	default:
		break;
	}
}

//加速下落函数
void GameScene::MoveDownSpeedup(float dt)
{
	MoveDownCurBlockGroup(0);
}

//刷新标签
void GameScene::RefreshLine()
{
	std::stringstream ss;
	ss << "Line: " << m_line;

	std::string text;
	text = ss.str();
	m_labelLine->setString(text);
}

void GameScene::RefreshLevel()
{
	//std::stringstream ss;
	//ss << "Level: " << m_level;

	//std::string text;
	//text = ss.str();
	//m_labelLevel->setString(text);
}