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
#include "utill/AnimationUtil.h"
#include <map>
#include "tools/PauseLayer.h"
#include "utill/SkillButton.h"

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
	,m_gameTouchType(Touch_Normal)
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
	auto db = DBManager::GetInstance();
	//�������������
	srand((unsigned)time(NULL));

	//������Ϸ����
	m_level = 1;		//����
	m_score = 0;		//����
	m_line = 0;			//��ȥ������
	m_moveState = BlockMove::BLOCKMOVE_NONE;
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

	//���С������
	m_widget = GameWidget::create();
	this->addChild(m_widget, nZOrderWidget);
	const Vec2& posScore = m_widget->GetScorePosition();
	const Vec2& posFirstBlock = m_widget->GetFirstBlockPosition();
	const Size& sizeScore = m_widget->GetScoreSize();
	const Rect& rectNext = m_widget->GetNextRect();

	//��ʼ��GameField
	GameField::GetInstance()->Init(posFirstBlock);

	//////////////////////////////////////////////////////////////////////////
	//��ӱ���ͼ
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
	//��ӷ���ť
	auto operateFrame = Sprite::createWithSpriteFrameName("operateFrame.png");
	operateFrame->setPosition(240, cy);
	addChild(operateFrame, nZOrderBackground + 1);

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

	//�����ת��ť
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
	//��ӱ�ǩ
	m_labelLine = LabelAtlas::create(Value(m_line).asString(),"scoreNum.png",16,25,'0');
	m_labelLine->setPosition(70,615);
	m_labelLine->setAnchorPoint(Point::ANCHOR_MIDDLE);
	this->addChild(m_labelLine);

	///��� ���ܰ���
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

	getNextGroup();

	auto skillmenu = Menu::create();
	skillmenu->setPosition(0, 0);
	addChild(skillmenu, 5);
	for (int i = 1; i <= 2; i++)
	{
		auto skillbutton = SkillButton::createSkillButton(i, db->GetSkillNum(i));
		skillbutton->setPosition(432, 424 - i * 100);
		skillmenu->addChild(skillbutton);
	}


	//����plist�ļ�ж�ش��ͼƬ
	SpriteManager::GetInstance()->UnInitSpriteFramesWithFile("sprites.plist");
	SpriteManager::GetInstance()->UnInitSpriteFramesWithFile("game.plist");
	//��ʱ�ƶ���ǰͼ��
	this->schedule(schedule_selector(GameScene::MoveDownCurBlockGroup), 1.0f / m_level);


	//Android��������
	m_keyboardListener = EventListenerKeyboard::create();
	m_keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	m_keyboardListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_keyboardListener, this);

	//�����㲻����
	m_bPopupLayerWorking = false;

	//�����Ч
	SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_DOWN);
	SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_EXPLODE);
	SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_FAILED);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(AUDIO_BACKGROUND);

	//���ű�������
	SimpleAudioEngine::getInstance()->playBackgroundMusic(AUDIO_BACKGROUND, true);

	//������Ч����
	float fVolumeBgm = DBManager::GetInstance()->GetBgmVolume();
	float fVolumeEffects = DBManager::GetInstance()->GetEffectsVolume();
	SimpleAudioEngine::getInstance()->setEffectsVolume(fVolumeBgm);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(fVolumeEffects);


	 auto listener = EventListenerTouchOneByOne::create();
	 listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	 listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	 listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	 this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}
void GameScene::getNextGroup()
{
	//��ȡ��ǰͼ��
	m_widget->GetNextBlockGroup(m_curGroup, this);
	showShadeInBottom(m_curGroup->GetBlocks());

}
void GameScene::update(float delta)
{

}
bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	if (m_gameTouchType == Touch_Normal)
	{
		return false;
	}
}

void GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
}

void GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	//�ж�����Ƿ񻬶�ȡ�����
	auto startPos = touch->getPreviousLocation();
	auto endPos = touch->getLocation();
	if (startPos.distance(endPos)>50)
	{
		return;
	}
	else
	{
		switch (m_gameTouchType)
		{
		case Touch_SkillKnock:
			KnockBlock(endPos);
			break;
		case Touch_SkillFill:
			FillBlock(endPos);
			break;
		default:
			break;
		}
	}
}


//��������
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

//��������
void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	//log("key:%d", (int)keyCode);
	if (m_bPopupLayerWorking)
	{
		return;
	}

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_BACK:	//���ؼ�(Only avaliable on Desktop and Android)
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		//�˳���Ϸ
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

//�˳���Ϸ
void GameScene::ExitGame()
{
	//ֹͣ���䷽��
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	this->unschedule(schedule_selector(GameScene::MoveDownCurBlockGroup));

	//��������
	m_bPopupLayerWorking = true;

	//�����Ի����
	auto exit = ExitLayer::create();
	exit->SetCallBackFunc(CC_CALLBACK_2(GameScene::buttonPopupCallback, this));
	this->addChild(exit);
}

//ȷ���˳���Ϸ
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



void GameScene::onExit()
{
	BaseGame::onExit();

	//�ͷŷ�����Դ
	SpriteManager::GetInstance()->UnInit();
	//�ͷ���Ƶ��Դ
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->stopAllEffects();
	SimpleAudioEngine::getInstance()->unloadEffect(AUDIO_DOWN);
	SimpleAudioEngine::getInstance()->unloadEffect(AUDIO_EXPLODE);
	SimpleAudioEngine::getInstance()->unloadEffect(AUDIO_FAILED);
}

//�����ƶ���ǰͼ��
void GameScene::MoveDownCurBlockGroup(float dt)
{
	//����������ʱ��������
	if (m_bPopupLayerWorking)
	{
		return;
	}

	const Size& size = SpriteManager::GetInstance()->GetBlockSize();
	if (IsCurBlockGroupCanMoveDown())
	{
		//�����ƶ�
		for (int i=0; i<4; i++)
		{
			m_curGroup->GetBlocks()[i].row++;	//����������1
			m_curGroup->ResetBlockPosition(i);	//�������÷��������
		}

		//�䵽��ʹ�
		if (!IsCurBlockGroupCanMoveDown())
		{
			//���ŷ�����ص���Ч
			SimpleAudioEngine::getInstance()->playEffect(AUDIO_DOWN);

			//��ӵ�ǰͼ���еķ��鵽���鼯����
			//AddCurBlockGroupToBlocks();
		}
	}
	else
	{
		//��ӵ�ǰͼ���еķ��鵽���鼯����
		AddCurBlockGroupToBlocks();
	}
}

//�жϵ�ǰͼ���Ƿ��������
bool GameScene::IsCurBlockGroupCanMoveDown()
{
	bool bAdjoined = false;
	vector<BlockObject>::const_iterator cit;
	for (int i=0; i<4; i++)
	{
		const BlockObject& curBlobk = m_curGroup->GetBlocks()[i];

		//�ж��Ƿ񵽵�
		if (curBlobk.row >= GameField::GetInstance()->GetBlockRowCount() - 1)
		{
			bAdjoined = true;
			break;
		}

		//�ж��Ƿ�����з�����������
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

//��ӵ�ǰͼ���еķ��鵽���鼯����
void GameScene::AddCurBlockGroupToBlocks()
{
	//����ǰ������ӵ����鼯��
	for (int i=0; i<4; i++)
	{
		m_vecBlocks.push_back(m_curGroup->GetBlocks()[i]);
	}

	//��ȥ���еķ���
	if (!ReleaseBlocksOnFullLine())
	{
		//����һ�е÷�
		m_widget->BlockGroupLanding();

		//���ŷ�����ص���Ч
		//SimpleAudioEngine::getInstance()->playEffect(AUDIO_DOWN);
	}
	else
	{
		//������ȥ�е���Ч
		SimpleAudioEngine::getInstance()->playEffect(AUDIO_EXPLODE);
	}

	//�����Ƿ񵽶�
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
			GameOver();	//��Ϸ����
			return;
		}
	}

	//���õ�ǰͼ��
	delete m_curGroup;
	m_curGroup = NULL;
	getNextGroup();
}

//��ȥͬ�еķ���
bool GameScene::ReleaseBlocksOnFullLine()
{
	//��ȡ�����������Ѿ���С�����ź���
	map<int/*�к�*/, int/*��ǰ�еķ�����*/> mapRow;
	m_vecFullRow.clear();
	vector<BlockObject>::const_iterator cit;
	for (cit=m_vecBlocks.begin(); cit!=m_vecBlocks.end(); ++cit)
	{
		if (++mapRow[cit->row] == GameField::GetInstance()->GetBlockColCount())
		{
			m_vecFullRow.push_back(cit->row);
		}
	}

	//û�п�����ȥ����
	if (m_vecFullRow.empty())
	{
		return false;
	}
	for (auto row:m_vecFullRow)
	{
		float cy = 0.0f;
		for (auto block:m_vecBlocks)
		{
			if (row == block.row)
			{
				auto ani = Sprite::create();
				ani->setPosition(240, block.sprite->getPositionY());
				addChild(ani, 5 + 1);
				ani->runAction(Sequence::createWithTwoActions(AnimationUtil::getInstance()->getAnimate("ani_xiaochu"),RemoveSelf::create(true)));
				break;
			}
		}
	}
	float dealy = AnimationUtil::getInstance()->getAnimate("ani_xiaochu")->getAnimation()->getDuration();
	runAction(Sequence::create(DelayTime::create(dealy), CallFunc::create([=]
	{

		//���������ȥ������
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

		//�ӷ���
		int score = m_vecFullRow.size() * 5;				//��ȥһ�е�5��
		int scoresExtra[] = { 3, 5, 8 };						//������ȥ2,3,4�ж����3,5,8��
		if (nSeriesNumber >= 2 && nSeriesNumber <= 4)
		{
			score += scoresExtra[nSeriesNumber - 2];		//����ӷ�
		}
		m_score += score;

		//�ӷ�
		m_widget->AddScore(m_vecFullRow);

		//��������
		m_line += nSeriesNumber;
		if (m_line / 10 >= m_level)
		{
			//�޸��ƶ���ǰͼ�ε��ٶ�
			this->unschedule(schedule_selector(GameScene::MoveDownCurBlockGroup));
			this->schedule(schedule_selector(GameScene::MoveDownCurBlockGroup), 1.0f / ++	m_level);
			RefreshLevel();
		}
		RefreshLine();

		//��ȥ����
		vector<BlockObject>::iterator it;
		vector<int>::const_iterator citFullRow;
		for (citFullRow = m_vecFullRow.begin(); citFullRow != m_vecFullRow.end(); ++citFullRow)
		{
			for (it = m_vecBlocks.begin(); it != m_vecBlocks.end();)
			{
				if (*citFullRow == it->row)
				{
					//��ȥ���еķ���
					this->removeChild(it->sprite);
					it = m_vecBlocks.erase(it);
				}
				else
				{
					++it;
				}
			}
		}

		//��ʱ��ȥ���еķ���
		this->scheduleOnce(schedule_selector(GameScene::RemoveFullRowBlocks), 0.3f);

	}), nullptr));



	//������ȥ��Ч
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
				//����������ķ��������ƶ�
				itBlock->row++;
				BlockGroup::ResetBlockPosition(*itBlock);
			}
		}
	}
}

//�����ƶ���ǰͼ��
void GameScene::MoveLeftrightCurBlockGroup(float dt)
{
	switch (m_moveState)
	{
	case BlockMove::BLOCKMOVE_LEFT:		//�����ƶ�
		m_curGroup->MoveLeft(m_vecBlocks);
		break;
	case BlockMove::BLOCKMOVE_RIGHT:	//�����ƶ�
		m_curGroup->MoveRight(m_vecBlocks);
		break;
	case BlockMove::BLOCKMOVE_NONE:		//ֹͣ�ƶ�
		this->unschedule(schedule_selector(GameScene::MoveLeftrightCurBlockGroup));
		break;
	default:
		break;
	}
	showShadeInBottom(m_curGroup->GetBlocks());
}

//������ť�¼�
void GameScene::buttonPopupCallback(Ref* sender, ButtonResult result)
{
	//��������
	m_bPopupLayerWorking = false;

	switch (result)
	{
	case ButtonResult::BUTTONRESULT_OK:			//������Ϸ
		Restart();
		break;
	case ButtonResult::BUTTONRESULT_CANCEL:		//����������
		Director::getInstance()->replaceScene(MainScene::createScene());
		break;
	case ButtonResult::BUTTONRESULT_EXIT:		//�˳���Ϸ
		DoExitGame();
		break;
	case ButtonResult::BUTTONRESULT_CONTINUE:	//ȡ���˳���Ϸ
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

//���¿�ʼ��Ϸ
void GameScene::Restart()
{

	//��������
	m_bPopupLayerWorking = false;

	//����������
	m_line = 0;
	m_level = 1;
	RefreshLine();
	RefreshLevel();

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
	m_curGroup->removeFromeParent();
	delete m_curGroup;
	m_curGroup = NULL;
	getNextGroup();

	//��ʱ�ƶ���ǰͼ��
	this->unschedule(schedule_selector(GameScene::MoveDownCurBlockGroup));
	this->schedule(schedule_selector(GameScene::MoveDownCurBlockGroup), 1.0f / m_level);

	//���ű�������
	SimpleAudioEngine::getInstance()->playBackgroundMusic(AUDIO_BACKGROUND, true);
}

void GameScene::GameOver()
{
	//����ʧ����Ч
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playEffect(AUDIO_FAILED);
	this->unschedule(schedule_selector(GameScene::MoveDownCurBlockGroup));



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

//////////////////////////////////////////////////////////////////////////
//�Զ��尴ť�¼�
void GameScene::buttonSpeedupCallback(Ref* sender, cocos2d::ui::Widget::TouchEventType event)
{
	switch (event)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		//��ʱ�����ƶ���ǰͼ�Σ�ÿ��20�Σ�
		this->unschedule(schedule_selector(GameScene::MoveDownCurBlockGroup));
		this->schedule(schedule_selector(GameScene::MoveDownSpeedup), 1.0f/20);
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		NULL;
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		//ȡ����ʱ�����ƶ���ǰͼ��
		this->unschedule(schedule_selector(GameScene::MoveDownSpeedup));
		this->schedule(schedule_selector(GameScene::MoveDownCurBlockGroup), 1.0f/m_level);
		break;
	default:
		break;
	}
}

//����
void GameScene::buttonLeftCallback(Ref* sender, cocos2d::ui::Widget::TouchEventType event)
{
	switch (event)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		//��ʱ�����ƶ�(ÿ֡�ƶ�һ��)
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

//����
void GameScene::buttonRightCallback(Ref* sender, cocos2d::ui::Widget::TouchEventType event)
{
	switch (event)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		//��ʱ�����ƶ�(ÿ֡�ƶ�һ��)
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

//��ת
void GameScene::buttonRotateCallback(Ref* sender, cocos2d::ui::Widget::TouchEventType event)
{
	if (cocos2d::ui::Widget::TouchEventType::BEGAN == event)
	{
		m_curGroup->Rotate(m_vecBlocks);
		showShadeInBottom(m_curGroup->GetBlocks());
	}
}
void GameScene::showShadeInBottom(const vector<BlockObject>& blocks)
{
	for (auto var : m_shadeblocks)
	{
		var.sprite->removeFromParentAndCleanup(1);
	}
	m_shadeblocks.clear();
	for (auto var : blocks)
	{
		BlockObject ob;
		ob.index = -1;
		ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(SHADESPRITEBLOCK);
		ob.col = var.col;
		ob.row = var.row;
		addChild(ob.sprite);
		m_shadeblocks.push_back(ob);
	}
	vector<BlockObject>::const_iterator cit;
	int nMoveRowCount = 0;
	bool bIntersect = false;
	for (int row = m_shadeblocks[3].row + 1; row < GameField::GetInstance()->GetBlockRowCount(); row++)
	{
		for (int i = 0; i < 4; i++)
		{
			//��ǰ�����Ƿ�����ƶ�(row - m_blocks[3].row)��
			for (cit = m_vecBlocks.begin(); cit != m_vecBlocks.end(); ++cit)
			{
				if (cit->col == m_shadeblocks[i].col && cit->row == m_shadeblocks[i].row + (row - m_shadeblocks[3].row))
				{
					bIntersect = true;
					break;
				}
			}

			if (bIntersect)
			{
				break;
			}
		}

		if (bIntersect)
		{
			break;
		}
		else
		{
			nMoveRowCount++;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		m_shadeblocks[i].row += (nMoveRowCount > 0 ? (nMoveRowCount - 0) : 0);
		Vec2 posBlock = Vec2::ZERO;
		GameField::GetInstance()->GetBlockPosition(m_shadeblocks[i].row, m_shadeblocks[i].col, posBlock);
		m_shadeblocks[i].sprite->setPosition(posBlock);
	}
}
//�����½�
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

//�������亯��
void GameScene::MoveDownSpeedup(float dt)
{
	MoveDownCurBlockGroup(0);
}

//ˢ�±�ǩ
void GameScene::RefreshLine()
{

	m_labelLine->setString(Value(m_line).asString());
}

void GameScene::RefreshLevel()
{
	//std::stringstream ss;
	//ss << "Level: " << m_level;

	//std::string text;
	//text = ss.str();
	//m_labelLevel->setString(text);
}

void GameScene::onRebegin()
{
	Restart();
}
void GameScene::onPause()
{
	pause();
	auto layer = PauseLayer::create();
	layer->setPosition(0, 0);
	addChild(layer);
	
}
void GameScene::onResum()
{
	resume();
}
void GameScene::onBackMainScene()
{
	Director::getInstance()->replaceScene(MainScene::createScene());
}
void GameScene::onUseSkill(SkillInfo*skill)
{
	if (skill->num>-1)
	{	
		switch (skill->Id)
		{
		case Skill_Knock:
			m_gameTouchType = Touch_SkillKnock;
			break;
		case Skill_Fill:
			m_gameTouchType = Touch_SkillFill;
			break;
		case Skill_Revivi:
			//TODO:  ����;
			break;
		default:
			break;
		}
		DBManager::GetInstance()->SetSkillNum(skill->Id, DBManager::GetInstance()->GetSkillNum(skill->Id));
	}
	else
	{
		//��Ʒ�
	}
}
void GameScene::FillBlock(Vec2 pos)
{
	int row = -1;
	int col = -1;
	m_widget->GetRowAndColByPos(pos, row, col);
	for (auto iter = m_vecBlocks.begin(); iter != m_vecBlocks.end(); iter++)
	{
		if (iter->col == col&&iter->row == row)
		{
			return;
		}
	}
	BlockObject ob;
	ob.index = -1;
	ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(8);
	ob.col = col;
	ob.row = row;
	addChild(ob.sprite);
	Vec2 posBlock = Vec2::ZERO;
	GameField::GetInstance()->GetBlockPosition(ob.row, ob.col, posBlock);
	ob.sprite->setPosition(posBlock);
	m_vecBlocks.push_back(posBlock);
	//����Ƿ�����
	ReleaseBlocksOnFullLine();
}
void GameScene::KnockBlock(Vec2 pos)
{
	int row = -1;
	int col = -1;
	m_widget->GetRowAndColByPos(pos, row, col);
	for (auto iter = m_vecBlocks.begin(); iter != m_vecBlocks.end();iter++)
	{
		if (iter->col == col&&iter->row == row)
		{
			iter->sprite->removeFromParentAndCleanup(1);
			m_vecBlocks.erase(iter);
			m_gameTouchType = Touch_Normal;
			break;
		}
	}
}