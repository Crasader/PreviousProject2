#include "RankingScene.h"
#include "ui/UIButton.h"
#include "../SetupScene.h"
#include "../Sqlite/DBManager.h"
#include "Block/SpriteManager.h"


USING_NS_CC;


Scene* RankingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = RankingScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool RankingScene::init()
{
	// 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

	//����scrollView�е�������
	auto scroll_layer = Layer::create();
	scroll_layer->setPosition(Vec2::ZERO);
	scroll_layer->setAnchorPoint(Point::ZERO);
	scroll_layer->setContentSize(Size(visibleSize.width/3*2, visibleSize.height/7*6));	//�����������СΪ��600��300��
	
	//��ӱ���
    auto sprite = Sprite::create("background.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite);

	//��ӶԻ���
	auto spriteBG = Sprite::create("dialog.png");
	spriteBG->setScale(2.0f);
	spriteBG->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/7*4 + origin.y));
    this->addChild(spriteBG);

	////��ӷ��ذ�ť
	//auto btnReturn = Button::create("tools/return_normal.png", "tools/return_pressed.png");
	//btnReturn->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/13));
	//btnReturn->addTouchEventListener(CC_CALLBACK_2(RankingScene::buttonReturnCallback, this));
	//this->addChild(btnReturn);

	////���scrollView
	//auto scrollPos = Vec2(origin.x, origin.y + visibleSize.height/6);
	//auto scrollView = ScrollView::create();						//����scrollView
	//scrollView->setViewSize(Size(visibleSize.width, visibleSize.height/5*4));
	//scrollView->setContentOffset(Point::ZERO);
	//scrollView->setDelegate(this);								//����ί��
	//scrollView->setDirection(ScrollView::Direction::VERTICAL);	//���ù�������Ϊ��ֱ
	//scrollView->setAnchorPoint(Point::ZERO);
	//scrollView->setPosition(scrollPos);
	//scrollView->setTouchEnabled(false);
	//this->addChild(scrollView, 1);
	//scrollView->setContainer(scroll_layer);

	////////////////////////////////////////////////////////////////////////////
	////�������

	////��ȡ���ݿ����
	//vector<DBManager::GameScore> ranking;
	//DBManager::GetInstance()->GetFirst10Ranking(ranking);

	//std::string filename;
	//string score;

	////����plist�ļ�������
	//SpriteManager::GetInstance()->InitSpriteFramesWithFile("ranking.plist");
	//
	////�������ͼƬ
	//for (int i=0; i<10; i++)
	//{
	//	filename = StringUtils::format("ranking%02d.png", i+1);
	//	auto sprite = Sprite::createWithSpriteFrameName(filename);
	//	sprite->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/20*(15 - i*2)));
	//	sprite->setTag(i + 1);
	//	scroll_layer->addChild(sprite);

	//	if (i < (int)ranking.size())
	//	{
	//		//score = StringUtils::format("%5d %s", ranking.at(i).score, ranking.at(i).time.c_str());
	//		score = StringUtils::format("%d", ranking.at(i).score);
	//	}
	//	else
	//	{
	//		score = "--";
	//	}

	//	//������ǩ
	//	auto label = Label::createWithTTF(score, "fonts/MNJKATONG.ttf", 52);	//���������ͨ����
	//	if (label != NULL)
	//	{
	//		label->setPosition(sprite->getPositionX() + sprite->getContentSize().width/16, sprite->getPositionY());
	//		scroll_layer->addChild(label);
	//	}
	//}

	////�ӻ����Ƴ�plist�ļ�
	//SpriteManager::GetInstance()->UnInitSpriteFramesWithFile("ranking.plist");

	////��дʵ��scrollview�Ĵ���Ч��
	//auto listenerT = EventListenerTouchOneByOne::create();
	//listenerT->onTouchBegan = [=](Touch * touch,Event * pEvent){
	//	m_firstPoint = touch->getLocation();
	//	m_offset = scrollView->getContentOffset();
	//	Vec2 pos=scroll_layer->getChildByTag(1)->getPosition();
	//	Vec2 scrpos = scroll_layer->getPosition();
	//	auto offect = m_offset.y;
	//	if (!scrollView->getBoundingBox().containsPoint(m_firstPoint))
	//	{
	//		return false;
	//	}
	//	return true;
	//};

	//listenerT->onTouchMoved = [=](Touch * touch,Event * pEvent){
	//	auto movePoint = touch->getLocation();
	//	auto distance = movePoint.y - m_firstPoint.y;
	//	auto offset = m_offset.y;
	//	scrollView->setContentOffset(Vec2(origin.x,distance + offset));
	//};

	//listenerT->onTouchEnded = [=](Touch * touch,Event * pEvent){
	//	auto endPoint = touch->getLocation();
	//	auto distance = endPoint.y - m_firstPoint.y;
	//	auto offset =  m_offset.y;
	//	
	//	Vec2 scrpos = scroll_layer->getPosition();
	//	if(scrpos.y + scroll_layer->getChildByTag(10)->getPositionY() > origin.y + visibleSize.height/20*(15 - 7*2))
	//	{
	//		offset = 0;
	//		distance = visibleSize.height/20*(0 + 2*2);	//��8λ�����һ��
	//	}
	//	else if(scrpos.y + scroll_layer->getChildByTag(1)->getPositionY() < origin.y + visibleSize.height/20*(15 - 0*2))
	//	{
	//		offset=0;
	//		distance=0;
	//	}
	//	auto adjustPoint = Vec2(origin.x, distance + offset);
	//	scrollView->setContentOffsetInDuration(adjustPoint, 0.1f);
	//};
	//
	//listenerT->setSwallowTouches(true);
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerT, this);
	return true;
}

//Cancel��ť�ص�����
//void RankingScene::buttonReturnCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event)
//{
//	if (cocos2d::ui::Widget::TouchEventType::BEGAN == event)
//	{
//		Director::getInstance()->replaceScene(SetupScene::createScene());
//	}
//}