#include "ExitLayer.h"
#include "StringManager.h"

USING_NS_CC;
using namespace ui;

// on "init" you need to initialize your instance
bool ExitLayer::init()
{
	if ( !PopupLayer::init() )
	{
		return false;
	}

	//获取游戏区域
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//添加背景图片
	auto background = Sprite::create("dialog.png");
	background->setScaleX(2.0f);
	background->setScaleY(0.8f);
	auto size = Size(background->getContentSize().width * background->getScaleX(),
		background->getContentSize().height * background->getScaleY());
	background->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
	this->addChild(background);

	auto bar = Sprite::create("dialog_bar.png");
	bar->setScale(2.0f);
	bar->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 - size.height/2 + size.height/2));
	this->addChild(bar);

	//添加标题
	auto text = StringManager::GetInstance()->GetString("leave_game");
	auto title = Label::createWithTTF(text, "fonts/MNJKATONG.ttf", 100);	//加载迷你简卡通字体
	if (title != NULL)
	{
		title->setPosition(Vec2(background->getPositionX(), background->getPositionY() + size.height/4));
		addChild(title, 1);
	}

	//Exit button
	
	m_btnExit = Button::create("tools/exit_normal.png", "tools/exit_pressed.png");
	m_btnExit->setPosition(Vec2(background->getPositionX() - size.width/2 + size.width/3,
		background->getPositionY() - size.height/3 + m_btnExit->getContentSize().height/4));
	m_btnExit->addTouchEventListener(CC_CALLBACK_2(ExitLayer::buttonExitCallback, this));
	this->addChild(m_btnExit);

	//Cancel button
	m_btnCancel = Button::create("tools/cancel_normal.png", "tools/cancel_pressed.png");
	m_btnCancel->setPosition(Vec2(background->getPositionX() - size.width/2 + size.width/3*2,
		background->getPositionY() - size.height/3 + m_btnCancel->getContentSize().height/4));
	m_btnCancel->addTouchEventListener(CC_CALLBACK_2(ExitLayer::buttonCancelCallback, this));
	this->addChild(m_btnCancel);

	return true;
}

//Exit按钮回调函数
void ExitLayer::buttonExitCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event)
{
	if (cocos2d::ui::Widget::TouchEventType::BEGAN == event)
	{
		DestroySelf(sender, ButtonResult::BUTTONRESULT_EXIT);
	}
}

//Cancel按钮回调函数
void ExitLayer::buttonCancelCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event)
{
	if (cocos2d::ui::Widget::TouchEventType::BEGAN == event)
	{
		DestroySelf(sender, ButtonResult::BUTTONRESULT_CONTINUE);
	}
}