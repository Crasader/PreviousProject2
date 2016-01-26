#include "GetRewardNode.h"
#include "utill/AnimationUtil.h"
#include "domain/user/User.h"
#include "domain/logevent/LogEventBankrupt.h"
GetRewardNode* GetRewardNode::create(Bankrupt baknrupt)
{
	GetRewardNode *pRet = new GetRewardNode();
	if (pRet && pRet->init(baknrupt))
	{
		
			pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool GetRewardNode::init(Bankrupt baknrupt)
{
	initWithFile("getRewardsNormal.png");
	bool bRet = false;
	do 
	{	
		m_baknrupt = baknrupt;
		char* mtime = new char[100];
		int s = ((int)m_baknrupt.wait_time + 1) % 60;
		int m = ((int)m_baknrupt.wait_time) / 60;
		sprintf(mtime, "%02d:%02d", m, s);
		auto label = LabelAtlas::create(mtime, "getRewardTimeNum.png", 10, 15, '0');
		label->setPosition(getContentSize().width / 2, 23);
		label->setAnchorPoint(Point::ANCHOR_MIDDLE);
		addChild(label, 0, "time");
		scheduleUpdate();
		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(GetRewardNode::onTouchBegan, this);
		listenr1->setSwallowTouches(false);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);
		bRet = true;
	} while (0);
	return bRet;
}
void GetRewardNode::update(float dt)
{
	m_baknrupt.wait_time -= dt;
	char* mtime = new char[100];
	int s = (((int)m_baknrupt.wait_time + 1) % 60);
	int m = (((int)m_baknrupt.wait_time )/ 60);
	sprintf(mtime, "%02d:%02d", m, s);
	auto label = (LabelAtlas*)getChildByName("time");
	label->setString(mtime);
	if (m_baknrupt.wait_time<=0)
	{
		isTimeOut = true;
		label->setVisible(false);
		runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniGainRewards")));
		unscheduleUpdate();
	}
}

bool GetRewardNode::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (isTimeOut)
	{
		User::getInstance()->addCoins(m_baknrupt.coins);
		removeFromParentAndCleanup(1);
		LogEventBankrupt::getInstance()->sendDataToServer(1, 1);
		BankruptManager::getInstance()->addTodayRequestTime();
	}
	return true;
}
