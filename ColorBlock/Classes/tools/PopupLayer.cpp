#include "PopupLayer.h"
#include "StringManager.h"

USING_NS_CC;

using namespace ui;

PopupLayer::PopupLayer()
	: m_touchListener(NULL)
	, m_btnOK(NULL)
	, m_btnCancel(NULL)
	, m_btnYes(NULL)
	, m_btnNo(NULL)
	, m_btnExit(NULL)
{

}

// on "init" you need to initialize your instance
bool PopupLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	//��ȡ��Ϸ����
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//���͸������
	auto shader = LayerColor::create(Color4B(0, 0, 0, 128), visibleSize.width, visibleSize.height);
	this->addChild(shader, -1);

	//�������¼�����
	m_touchListener = EventListenerTouchOneByOne::create();
	m_touchListener->onTouchBegan = CC_CALLBACK_2(PopupLayer::onTouchBegan, this);
	m_touchListener->onTouchMoved = CC_CALLBACK_2(PopupLayer::onTouchMoved, this);
	m_touchListener->onTouchEnded = CC_CALLBACK_2(PopupLayer::onTouchEnded, this);
	m_touchListener->onTouchCancelled = CC_CALLBACK_2(PopupLayer::onTouchCancelled, this);
	m_touchListener->setSwallowTouches(true);
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_touchListener, this);
	this->getEventDispatcher()->addEventListenerWithFixedPriority(m_touchListener, -128);

	return true;
}

//���ð�ť�ص�����
void PopupLayer::SetCallBackFunc(ButtonTouchCallback callfunc)
{
	m_callback = callfunc;
}

//����layer�����ûص�����
void PopupLayer::DestroySelf(cocos2d::Ref* sender, ButtonResult result)
{
	this->getEventDispatcher()->removeEventListener(m_touchListener);
	m_callback(sender, result);
	this->removeFromParentAndCleanup(true);
}

void PopupLayer::onEnter()
{

}

void PopupLayer::onExit()
{
	Layer::onExit();
}

// ������ʼ�¼�
bool PopupLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	auto touchLocation = touch->getLocation();
	log("PopupLayer --- point(%f, %f)", touchLocation.x, touchLocation.y);

	Button* buttons[] = {m_btnOK, m_btnCancel, m_btnYes, m_btnNo, m_btnExit};
	for (int i=0; i<sizeof(buttons)/sizeof(Button*); i++)
	{
		if (buttons[i] != NULL)
		{
			const Size& size = buttons[i]->getContentSize();
			const Vec2& pos = buttons[i]->getPosition();
			Rect rect = Rect(pos.x - size.width/2, pos.y - size.height/2, size.width, size.height);
			if (rect.containsPoint(touchLocation))
			{
				buttons[i]->setBright(false);
				buttons[i]->onTouchBegan(touch, unused_event);
				break;
			}
		}
	}

	return true;
}

// ��������
void PopupLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	auto touchLocation = touch->getLocation();
	Button* buttons[] = {m_btnOK, m_btnCancel, m_btnYes, m_btnNo, m_btnExit};
	for (int i=0; i<sizeof(buttons)/sizeof(Button*); i++)
	{
		if (buttons[i] != NULL)
		{
			const Size& size = buttons[i]->getContentSize();
			const Vec2& pos = buttons[i]->getPosition();
			Rect rect = Rect(pos.x - size.width/2, pos.y - size.height/2, size.width, size.height);
			if (rect.containsPoint(touchLocation))
			{
				buttons[i]->onTouchMoved(touch, unused_event);
				break;
			}
		}
	}
}

// ���������¼�
void PopupLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	auto touchLocation = touch->getLocation();
	Button* buttons[] = {m_btnOK, m_btnCancel, m_btnYes, m_btnNo, m_btnExit};
	for (int i=0; i<sizeof(buttons)/sizeof(Button*); i++)
	{
		if (buttons[i] != NULL)
		{
			const Size& size = buttons[i]->getContentSize();
			const Vec2& pos = buttons[i]->getPosition();
			Rect rect = Rect(pos.x - size.width/2, pos.y - size.height/2, size.width, size.height);
			if (rect.containsPoint(touchLocation))
			{
				buttons[i]->setBright(true);
				buttons[i]->onTouchEnded(touch, unused_event);
				break;
			}
		}
	}
}

// ����ȡ���¼�
void PopupLayer::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	auto touchLocation = touch->getLocation();
	Button* buttons[] = {m_btnOK, m_btnCancel, m_btnYes, m_btnNo, m_btnExit};
	for (int i=0; i<sizeof(buttons)/sizeof(Button*); i++)
	{
		if (buttons[i] != NULL)
		{
			const Size& size = buttons[i]->getContentSize();
			const Vec2& pos = buttons[i]->getPosition();
			Rect rect = Rect(pos.x - size.width/2, pos.y - size.height/2, size.width, size.height);
			if (rect.containsPoint(touchLocation))
			{
				buttons[i]->setBright(true);
				buttons[i]->onTouchCancelled(touch, unused_event);
				break;
			}
		}
	}
}