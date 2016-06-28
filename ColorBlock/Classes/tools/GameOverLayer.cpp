#include "GameOverLayer.h"
#include "StringManager.h"

USING_NS_CC;
using namespace ui;
GameOverLayer* GameOverLayer::create(int score)
{
	GameOverLayer *pRet = new(std::nothrow) GameOverLayer();
	if (pRet && pRet->init(score))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool GameOverLayer::init(int score)
{
	if (!BaseLayer::init())
	{
		return false;
	}
	_score = score;
	//获取游戏区域
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto title = SPRITE("txtGameOver.png");
	title->setPosition(240, 510+800);
	addChild(title);
	title->runAction(MoveTo::create(0.5f, Vec2(240, 510)));
	auto btBack = MenuItemSprite::create(SPRITE("btBack_1.png"), SPRITE("btBack_2.png"), nullptr, CC_CALLBACK_1(BaseLayer::menuExitCallback, this));
	btBack->setPosition(140, 150);

	auto btRestart = MenuItemSprite::create(SPRITE("btPlayAgain_1.png"), SPRITE("btPlayAgain_2.png"), nullptr, CC_CALLBACK_1(BaseLayer::menuReStartCallback, this));
	btRestart->setPosition(480 - 140, 150);

	auto menu = Menu::create(btBack, btRestart, nullptr);
	menu->setPosition(0, 0);
	addChild(menu);

	label = LabelAtlas::create("0", "resultNum.png", 29, 44, '0');
	label->setPosition(300, 80);
	label->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	title->addChild(label, 0, 10);


	scheduleUpdate();

	return true;
}
const float aniTime = 1.0f;
int getCurrencyRankByRange(int startRank, int endRank, float startValue, float endValue, float curValue)
{
	float fTemp = (curValue) / (endValue - startValue);
	auto currrRank = endRank - (endRank - startRank)*fTemp;
	return currrRank;
}
void GameOverLayer::update(float delta){
	if (_totalTime>aniTime)
	{
		return; 
	}
	_totalTime += delta;
	int scoreNum = getCurrencyRankByRange(_score,0, 0.0f, aniTime, _totalTime);
	label->setString(cocos2d::String::createWithFormat("%d", scoreNum)->getCString());
	
}