#include "maridTaskPlane.h"
#include "MermaidTaskMannger.h"

maridTaskPlane* maridTaskPlane::create(int lefttime, std::vector<MarriedTaskFishItem> items)
{
	maridTaskPlane *pRet = new maridTaskPlane();
	if (pRet && pRet->init(lefttime, items))
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
void maridTaskPlane::addMaridTaskfish(int fishid)
{
	for (auto var : _cells)
	{
		if (var->getfishid() == fishid)
		{
			var->addfish();
		}
	}
}
void maridTaskPlane::onExit()
{
	Sprite::onExit();
	MermaidTaskMannger::getInstence()->setTaskPlane(nullptr);
}
bool maridTaskPlane::init(int lefttime, std::vector<MarriedTaskFishItem> items)
{
	if (!Sprite::init())
	{
		return false;
	}
	bool bRet = false;
	do
	{
		setMarriedTaskFishItems(items);
		MermaidTaskMannger::getInstence()->setTaskPlane(this);

		_lefttime = lefttime;
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game/ui/fish/fish_frame.plist");
		auto size = getContentSize();
		for (int i = 0; i < items.size();i++)
		{
			auto cell = MaridTaskCell::create(items[i].fishid, items[i].nums);
			cell->setPosition(-50, i*40+19);
			addChild(cell);
			cell->runAction(Sequence::create(DelayTime::create(0.3f), MoveBy::create(0.2f, Vec2(125, 0)), nullptr));
			_cells.push_back(cell);
		}
		auto box = Sprite::create("mermaidbox.png");
		box->setPosition(70, 129);
		addChild(box);
		labelNum = LabelTTF::create("0","Arial",20);
		labelNum->setPosition(70,box->getContentSize().height/2);
		labelNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
		box->addChild(labelNum);
		labelNum->setVisible(false);
		
		runAction(Sequence::create(DelayTime::create((items.size() - 1)*0.3 + 0.2), CallFunc::create([=]{scheduleUpdate(); }), nullptr));
		bRet = true;
	} while (0);


	return bRet;
}


void maridTaskPlane::update(float delta)
{
	labelNum->setVisible(true);
	nNowtime += delta;
	char* mtime = new char[100];
	int s = ((int)(_lefttime - nNowtime)) % 60;
	int m = (_lefttime - nNowtime) / 60;
	if (s < 0){
		s = 00;
	}
	if (m < 0){
		m = 00;
	}
	sprintf(mtime, "%.2d:%.2d", m, s);
	labelNum->setString(mtime);

	if (nNowtime>_lefttime)//未完成
	{	
		auto sp = Sprite::create("TXTNoFinished.png");
		sp->setPosition(480, 270);
		getParent()->addChild(sp, 30);
		sp->runAction(Sequence::create(DelayTime::create(3.0f), RemoveSelf::create(1), nullptr));

		removeFromParentAndCleanup(1);
		return;
	}
	//auto info = GameData::getInstance()->getmermaidTask()->getMermaidTaskOnlineInfo().mermaidTaskItems;
	//auto isSuccess = GameData::getInstance()->getmermaidTask()->isSuccess();
	//for (auto var : info)
	//{
	//	auto label = (LabelAtlas*)getChildByTag(var.fishId);
	//	label->setString(Value(var.current_num).asString().c_str());
	//}
	//if (isSuccess)//完成
	//{
	//	LogEventMermaid::getInstance()->addDataToSend(GameData::getInstance()->getRoomID(), nNowtime, GameData::getInstance()->getmermaidTask()->getMermaidTaskOnlineInfo().coins);
	//	CoinBox::getInstance()->addCoinBox(GameData::getInstance()->getmermaidTask()->getMermaidTaskOnlineInfo().coins);
	//	GameManage::getInstance()->getGameLayer()->onGetReward(1008, 1);
	//	((GameGuiLayer*)getParent())->beginMaridTaskTime(0);
	//	auto sp = Sprite::create("TXTFinished.png");
	//	sp->setPosition(480, 270);
	//	auto nameLabel = LabelTTF::create(User::getInstance()->getUserName(), "arial", 20);
	//	nameLabel->setPosition(192, 71);
	//	nameLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	//	sp->addChild(nameLabel);
	//	getParent()->addChild(sp, 30);
	//	sp->runAction(Sequence::create(DelayTime::create(3.0f), RemoveSelf::create(1), nullptr));
	//	removeFromParentAndCleanup(1);
	//	return;
	//}
	//if (nNowtime>GameData::getInstance()->getmermaidTask()->getMermaidTaskConfigInfo().continue_time)//未完成
	//{	
	//	LogEventMermaid::getInstance()->addDataToSend(GameData::getInstance()->getRoomID(), 0, GameData::getInstance()->getmermaidTask()->getMermaidTaskOnlineInfo().coins);
	//	((GameGuiLayer*)getParent())->beginMaridTaskTime(0);
	//	auto sp = Sprite::create("TXTNoFinished.png");
	//	sp->setPosition(480, 270);
	//	getParent()->addChild(sp, 30);
	//	sp->runAction(Sequence::create(DelayTime::create(3.0f), RemoveSelf::create(1), nullptr));

	//	removeFromParentAndCleanup(1);
	//	return;
	//}
	
}

void maridTaskPlane::onFinishSecuss()
{
	for (auto var : _cells)
	{
		if (!var->isFinish)
		{
			var->addfish();
		}
	}
	removeFromParentAndCleanup(1);
}