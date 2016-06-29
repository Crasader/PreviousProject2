#include "BaseGame.h"


bool BaseGame::init()
{
	Layer::init();
	return true;
}

void BaseGame::onExit()
{
	Layer::onExit();
	removeNotifications();
}
void BaseGame::onEnter()
{
	Layer::onEnter();
	InitNotifications();
}

void BaseGame::InitNotifications()
{
	//游戏暂停
	EventListenerCustom* listener = EventListenerCustom::create(MSG_PAUSE, [=](EventCustom* event){onPause(); });
	getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
	//游戏恢复
	listener = EventListenerCustom::create(MSG_RESUME, [=](EventCustom* event){onResum(); CCLOG("onResume"); });
	getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
	//重新开始
	listener = EventListenerCustom::create(MSG_REBEGIN, [=](EventCustom* event){onRebegin(); });
	getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
	//返回大厅
	listener = EventListenerCustom::create(MSG_BACKMAINSCENE, [=](EventCustom* event){onBackMainScene(); });
	getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
	//使用技能
	listener = EventListenerCustom::create(MSG_USESKILL, [=](EventCustom* event){SkillInfo *skillid = ((SkillInfo*)event->getUserData()); onUseSkill(skillid); });
	getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
}
void BaseGame::removeNotifications()
{
	getEventDispatcher()->removeCustomEventListeners(MSG_PAUSE);
	getEventDispatcher()->removeCustomEventListeners(MSG_RESUME);
	getEventDispatcher()->removeCustomEventListeners(MSG_REBEGIN);
	getEventDispatcher()->removeCustomEventListeners(MSG_BACKMAINSCENE);
	getEventDispatcher()->removeCustomEventListeners(MSG_USESKILL);
}

void BaseGame::CreateEffect()
{
	auto star = Sprite::createWithSpriteFrameName("effect_star.png");
	star->setPosition(56, 443);
	addChild(star,-10);
	star->setOpacity(0);
	star->runAction(RepeatForever::create(Sequence::create(DelayTime::create(1.0f), Spawn::create(FadeIn::create(1.5), ScaleTo::create(1.5, 1.0), nullptr), DelayTime::create(1.5f),Spawn::create(FadeOut::create(0.001), ScaleTo::create(0.001, 0), nullptr), DelayTime::create(3.5f), nullptr)));

	auto metor = Sprite::createWithSpriteFrameName("effect_star_meteor.png");
	metor->setRotation(135.0f);
	metor->setPosition(480, 850);
	auto ac = Sequence::create(Spawn::createWithTwoActions(CCEaseSineIn::create(MoveTo::create(1.0f, Vec2(-50, 240))), DelayTime::create(1.0f)), DelayTime::create(6.5f), Spawn::createWithTwoActions(MoveTo::create(0.001f, Vec2(480, 850)), FadeIn::create(0000.1f)), nullptr);
	metor->runAction(RepeatForever::create(ac));
	addChild(metor,-10);
}