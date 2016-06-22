#include "TestMainScene.h"
USING_NS_CC;
Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	// ��ʼ����������  
	this->initPhysics();

	auto listen = EventListenerTouchOneByOne::create();
	listen->onTouchBegan = [=](Touch* touch, Event* event)
	{
		auto pos = touch->getLocation();
		addNewSpriteAtPosition(pos);
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen, this);
	//��ʼ��Ϸѭ��  
	scheduleUpdate();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("blocks.plist");

	return true;
}
void HelloWorld::initPhysics()
{
	Size s = Director::getInstance()->getVisibleSize();

	//��������  
	b2Vec2 gravity;
	gravity.Set(0.0f, -10.0f);
	//��������  
	world = new b2World(gravity);
	// ���������Ƿ�����  
	world->SetAllowSleeping(true);
	// ���������������
	world->SetContinuousPhysics(true);

	//�������嶨��  
	b2BodyDef groundBodyDef;
	//���½�  
	groundBodyDef.position.Set(0, 0);


	//������������  
	b2Body* groundBody = world->CreateBody(&groundBodyDef);


	//����һ���бߵ���״  
	b2EdgeShape groundBox;


	// �ײ�  
	groundBox.Set(b2Vec2(0, 0), b2Vec2(s.width / PTM_RATIO, 0));
	//ʹ�üо߹̶���״��������  
	groundBody->CreateFixture(&groundBox, 0);


	// ����  
	groundBox.Set(b2Vec2(0, s.height / PTM_RATIO),
		b2Vec2(s.width / PTM_RATIO, s.height / PTM_RATIO));
	groundBody->CreateFixture(&groundBox, 0);


	// ���  
	groundBox.Set(b2Vec2(0, s.height / PTM_RATIO), b2Vec2(0, 0));                           groundBody->CreateFixture(&groundBox, 0);


	// �ұ�  
	groundBox.Set(b2Vec2(s.width / PTM_RATIO, s.height / PTM_RATIO),
		b2Vec2(s.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&groundBox, 0);


}
HelloWorld::~HelloWorld()
{
	CC_SAFE_DELETE(world);
}
void HelloWorld::addNewSpriteAtPosition(Vec2 p)
{
	log("Add sprite %0.2f x %02.f", p.x, p.y);


	//�����������澫�����  
	auto sprite = Sprite::createWithSpriteFrameName("block02.png");
	sprite->setPosition(Vec2(p.x, p.y));
	this->addChild(sprite);


	//���嶨��  
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(p.x / PTM_RATIO, p.y / PTM_RATIO);
	b2Body *body = world->CreateBody(&bodyDef);
	body->SetUserData(sprite);


	// ����2�׼����ĺ�����״  
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1, 1);


	// �о߶���  
	b2FixtureDef fixtureDef;
	//���üоߵ���״  
	fixtureDef.shape = &dynamicBox;
	//�����ܶ�  
	fixtureDef.density = 1.0f;
	//����Ħ��ϵ��  
	fixtureDef.friction = 0.3f;
	//ʹ�üо߹̶���״��������    
	body->CreateFixture(&fixtureDef);


}
void HelloWorld::update(float dt)
{
	float timeStep = 0.03f;
	int32 velocityIterations = 8;
	int32 positionIterations = 1;


	world->Step(timeStep, velocityIterations, positionIterations);


	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != nullptr) {
			Sprite* sprite = (Sprite*)b->GetUserData();
			sprite->setPosition(Vec2(b->GetPosition().x *
				PTM_RATIO, b->GetPosition().y * PTM_RATIO));
			sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
}