#include "GameOverLayer.h"
#include "StringManager.h"

USING_NS_CC;
using namespace ui;

// on "init" you need to initialize your instance
bool GameOverLayer::init()
{
	if ( !PopupLayer::init() )
	{
		return false;
	}

	//获取游戏区域
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//添加背景图片
	m_background = Sprite::create("dialog.png");
	m_background->setScale(2.0f);
	m_size = m_background->getContentSize() * m_background->getScale();
	m_background->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
	this->addChild(m_background);

	auto bar = Sprite::create("dialog_bar.png");
	bar->setScale(2.0f);
	bar->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 - m_size.height/2 + m_size.height/3*2));
	this->addChild(bar);

	//添加标题
	m_title = Label::createWithTTF("title", "fonts/MNJKATONG.ttf", 100);		//加载迷你简卡通字体
	if (m_title != NULL)
	{
		m_title->setPosition(Vec2(m_background->getPositionX(), m_background->getPositionY() + m_size.height/3));
		addChild(m_title, 1);
	}

	//添加文本内容
	m_content = Label::createWithTTF("content", "fonts/MNJKATONG.ttf", 120);	//加载迷你简卡通字体
	if (m_content != NULL)
	{
		m_content->setPosition(m_background->getPosition());
		addChild(m_content, 1);
	}

	return true;
}

//设置标题
void GameOverLayer::SetTitle(const string& title)
{
	m_title->setString(title);
}

//设置文本内容
void GameOverLayer::SetContent(const string& content)
{
	m_content->setString(content);
}

//设置按钮类型
void GameOverLayer::SetButtonType(ButtonType type)
{
	switch (type)
	{
	case ButtonType::BUTTONTYPE_OK:
		{
			//OK button
			m_btnOK = Button::create("tools/continue_normal.png", "tools/continue_pressed.png");
			m_btnOK->setPosition(Vec2(m_background->getPositionX() - m_size.width/2 + m_size.width/3,
				m_background->getPositionY() - m_size.height/3 + m_btnOK->getContentSize().height/2));
			m_btnOK->addTouchEventListener(CC_CALLBACK_2(GameOverLayer::buttonOkCallback, this));
			this->addChild(m_btnOK);
		}
		break;
	case ButtonType::BUTTONTYPE_OKCANCEL:
		{
			//OK button
			m_btnOK = Button::create("tools/continue_normal.png", "tools/continue_pressed.png");
			m_btnOK->setPosition(Vec2(m_background->getPositionX() - m_size.width/2 + m_size.width/3,
				m_background->getPositionY() - m_size.height/3 + m_btnOK->getContentSize().height/2));
			m_btnOK->addTouchEventListener(CC_CALLBACK_2(GameOverLayer::buttonOkCallback, this));
			this->addChild(m_btnOK);

			//Cancel button
			m_btnCancel = Button::create("tools/return_normal.png", "tools/return_pressed.png");
			m_btnCancel->setPosition(Vec2(m_background->getPositionX() - m_size.width/2 + m_size.width/3*2,
				m_background->getPositionY() - m_size.height/3 + m_btnCancel->getContentSize().height/2));
			m_btnCancel->addTouchEventListener(CC_CALLBACK_2(GameOverLayer::buttonCancelCallback, this));
			this->addChild(m_btnCancel);
		}
		break;
	case ButtonType::BUTTONTYPE_YESNO:
		{
			//Yes button
			m_btnYes = Button::create("tools/continue_normal.png", "tools/continue_pressed.png");
			m_btnYes->setPosition(Vec2(m_background->getPositionX() - m_size.width/2 + m_size.width/3,
				m_background->getPositionY() - m_size.height/3 + m_btnYes->getContentSize().height/2));
			m_btnYes->addTouchEventListener(CC_CALLBACK_2(GameOverLayer::buttonOkCallback, this));
			this->addChild(m_btnYes);

			//No button
			m_btnNo = Button::create("tools/return_normal.png", "tools/return_pressed.png");
			m_btnNo->setPosition(Vec2(m_background->getPositionX() - m_size.width/2 + m_size.width/3*2,
				m_background->getPositionY() - m_size.height/3 + m_btnNo->getContentSize().height/2));
			m_btnNo->addTouchEventListener(CC_CALLBACK_2(GameOverLayer::buttonCancelCallback, this));
			this->addChild(m_btnNo);
		}
		break;
	default:
		break;
	}
}

//YES按钮回调函数
void GameOverLayer::buttonYesCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event)
{
	if (cocos2d::ui::Widget::TouchEventType::BEGAN == event)
	{
		DestroySelf(sender, ButtonResult::BUTTONRESULT_YES);
	}
}

//NO按钮回调函数
void GameOverLayer::buttonNoCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event)
{
	if (cocos2d::ui::Widget::TouchEventType::BEGAN == event)
	{
		DestroySelf(sender, ButtonResult::BUTTONRESULT_NO);
	}
}

//OK按钮回调函数
void GameOverLayer::buttonOkCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event)
{
	if (cocos2d::ui::Widget::TouchEventType::BEGAN == event)
	{
		DestroySelf(sender, ButtonResult::BUTTONRESULT_OK);
	}
}

//Cancel按钮回调函数
void GameOverLayer::buttonCancelCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event)
{
	if (cocos2d::ui::Widget::TouchEventType::BEGAN == event)
	{
		DestroySelf(sender, ButtonResult::BUTTONRESULT_CANCEL);
	}
}

//銷毀layer并调用回调函数
void GameOverLayer::DestroySelf(cocos2d::Ref* sender, ButtonResult result)
{
	this->getEventDispatcher()->removeEventListener(m_touchListener);
	m_callback(sender, result);
	this->removeFromParentAndCleanup(true);
}