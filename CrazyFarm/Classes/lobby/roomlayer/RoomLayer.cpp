#include "RoomLayer.h"
#include "config/ConfigRoom.h"
#include "domain/user/User.h"
#include "utill/dayUtil.h"


RoomLayer * RoomLayer::createLayer()
{
	RoomLayer *ret = new  RoomLayer();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}
const Vec2 roomPos[5] = { Vec2(-300-480, 30), Vec2(250-480, 30), Vec2(500-480, 0), Vec2(750-480, 30), Vec2(960 + 300-480,30) };


bool RoomLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}	
	bool bRet = false;
	do 
	{
		setContentSize(Size(960, 340));
		createRoomLayer();
		//屏蔽向下触摸
		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(RoomLayer::onTouchBegan, this);
		listenr1->onTouchMoved = CC_CALLBACK_2(RoomLayer::onTouchMoved, this);
		listenr1->onTouchEnded = CC_CALLBACK_2(RoomLayer::onTouchEnded, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);
		this->scheduleUpdate();
		bRet = true;
	} while (0);
	return bRet;
}

void RoomLayer::update(float delta)
{
	touchtime += delta;
	
}

bool RoomLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (touchtime<0.4f)
	{
		return false;
	}
	auto pos = touch->getLocation(); 
	if (pos.y > 100 && pos.y < 440)
	{
		diffx = 0;
		return true;
	}
	
	return false;
}

void RoomLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
	
}
void RoomLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	auto startPos = touch->getStartLocation();
	auto endPos = touch->getLocation();
	diffx = startPos.x - endPos.x;
	if (diffx > 20)
	{
		isTouchMove = true;
		moveRoomLeft();
		touchtime = 0;
	}
	else if (diffx < -20)
	{
		moveRoomRight();
		isTouchMove = false;
		touchtime = 0;
	}
	else
	{
		if (endPos.x > 480)
		{
			moveRoomLeft();
			touchtime = 0;
		}
		else
		{
			moveRoomRight();
			touchtime = 0;
		}
	}
}

void RoomLayer::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}

void RoomLayer::createRoomLayer()
{
	auto visibisize = Director::getInstance()->getVisibleSize();

	auto maxlevl = User::getInstance()->getMaxTurrentLevel();
	auto k = sortRoomByMaxlevel(maxlevl);
	auto menu = Menu::create();
	menu->setPosition(Point::ZERO);
	addChild(menu,2);
	for (size_t i = 0; i < k.size(); i++)
	{
		

		auto cell = RoomCell::createCell(k[i]);
		cell->setTag(i + 1);
		cell->setPosition(roomPos[i + 1]);
		cell->setAnchorPoint(Point::ANCHOR_MIDDLE);
		roomCells.pushBack(cell);
		menu->addChild(cell);
     

		switch (i + 1)
		{
		case 4:
			cell->setVisible(false);
			cell->setScale(0.7);
			break;
		case 1:
			cell->setEnabled(false);
			cell->setScale(0.7);
			cell->setColor(Color3B(128, 128, 128));
			cell->stopNormalAni();
			cell->getChildByName("onLinePlayer")->getChildByName("onLinePlayCount")->setColor(Color3B(128, 128, 128));
			break;
		case 2:
			
			cell->setEnabled(true);
			cell->resumeNormalAni(); 
			cell->playScaleAni();
			cell->setScale(1);
			cell->setColor(Color3B(255, 255, 255));
			cell->getChildByName("onLinePlayer")->getChildByName("onLinePlayCount")->setColor(Color3B(255, 255, 255));
			break;
		case 3:
			cell->setEnabled(false);
			cell->setScale(0.7);
			cell->stopNormalAni();
			cell->setColor(Color3B(128, 128, 128));
			cell->getChildByName("onLinePlayer")->getChildByName("onLinePlayCount")->setColor(Color3B(128, 128, 128));
			break;
		default:
			break;
		}



	}

}

std::vector<Room> RoomLayer::sortRoomByMaxlevel(int maxLevel)
{
	auto roomDatas = ConfigRoom::getInstance()->getRooms();
	///获得最大可进房间ID
	int i = roomDatas.size() - 1;
	for (; i > 0; i--)
	{
		if (roomDatas[i].unlock_turrent_level <= maxLevel)
		{
			break;
		}
	}
	std::vector<Room> curData;
	curData.resize(roomDatas.size());
	int maxRoomId = i;
	int j = 0;
	for (; j < curData.size(); j++)
	{
		curData[j] = roomDatas[i];
		i++;
		if (i >= roomDatas.size())
		{
			break;
		}
	}
	int k = 0;
	for (; k <= maxRoomId - 1; k++)
	{
		j++;
		curData[j] = roomDatas[k];

	}
	std::vector<Room> curData2;
	curData2.resize(curData.size());
	for (int z = 0; z < curData2.size();z++)
	{
		int x = z - 1<0 ? curData2.size()-1 : z - 1;
		curData2[z] = curData[x];
	}
	for (auto var :curData2)
	{
		CCLOG("%d", var.room_id);
		
	}
CCLOG("**************************************");
	return curData2;
}

void RoomLayer::moveRoomLeft()
{
	for (auto cell : roomCells)
	{
		cell->stopActionByTag(888);
		cell->setVisible(true);
		auto tag = cell->getTag();
		if (--tag < 1)
		{
			tag = 4;
		}
		cell->setTag(tag);


		switch (tag)
		{
		case 4:
			cell->setVisible(false);
			cell->setScale(0.7);
			cell->runAction(MoveTo::create(0.1f, roomPos[tag]));
			break;
		case 1:
			cell->setEnabled(false);
			cell->setScale(0.7);
			cell->setColor(Color3B(128, 128, 128));
			cell->runAction(Sequence::create(MoveTo::create(0.2f, roomPos[tag]), CallFunc::create([=]{cell->stopNormalAni(); }), nullptr));
			cell->getChildByName("onLinePlayer")->getChildByName("onLinePlayCount")->setColor(Color3B(128, 128, 128));
			break;
		case 2:	
			cell->setScale(1);
			cell->setColor(Color3B(255, 255, 255));
			cell->runAction(Sequence::create(MoveTo::create(0.2f, roomPos[tag]), CallFunc::create([=]{cell->resumeNormalAni();cell->setEnabled(true);	cell->playScaleAni(); }), nullptr));
			cell->getChildByName("onLinePlayer")->getChildByName("onLinePlayCount")->setColor(Color3B(255, 255, 255));
			break;
		case 3:
			cell->setPosition(roomPos[4]);
			cell->setEnabled(false);
			
			cell->setScale(0.7);
			cell->setColor(Color3B(128, 128, 128));
			cell->getChildByName("onLinePlayer")->getChildByName("onLinePlayCount")->setColor(Color3B(128, 128, 128));
			cell->runAction(Sequence::create(MoveTo::create(0.2f, roomPos[tag]), CallFunc::create([=]{cell->stopNormalAni(); }), nullptr));
			break;
		default:
			break;
		}
	}
	for (auto cell:roomCells)
	{
		CCLOG("kkkkkkkkkkkkkkkkkkkkk %f", cell->getScale());
	}
}
void RoomLayer::moveRoomRight()
{

	for (auto cell : roomCells)
	{
		cell->stopActionByTag(888);
		cell->setVisible(true);
		auto tag = cell->getTag();
		if (++tag > 4)
		{
			tag = 1;
		}
		cell->setTag(tag);


		switch (tag)
		{
		case 4:
			cell->setVisible(false);
			cell->setScale(0.7);
			cell->runAction(MoveTo::create(0.1f, roomPos[tag]));
			break;
		case 1:
			cell->setEnabled(false);
			cell->setScale(0.7);
			cell->setColor(Color3B(128, 128, 128));
			cell->getChildByName("onLinePlayer")->getChildByName("onLinePlayCount")->setColor(Color3B(128, 128, 128));
			cell->runAction(Sequence::create(MoveTo::create(0.2f, roomPos[tag]), CallFunc::create([=]{cell->stopNormalAni(); }), nullptr));
			break;
		case 2:
		
			cell->setScale(1);
		
			cell->setColor(Color3B(255, 255, 255));
			cell->getChildByName("onLinePlayer")->getChildByName("onLinePlayCount")->setColor(Color3B(255, 255, 255));
			cell->runAction(Sequence::create(MoveTo::create(0.2f, roomPos[tag]), CallFunc::create([=]{cell->resumeNormalAni();		cell->setEnabled(true);cell->playScaleAni(); }), nullptr));
			break;
		case 3:
			cell->setPosition(roomPos[4]);
			cell->setEnabled(false);
			cell->setScale(0.7);
			
			cell->setColor(Color3B(128, 128, 128));
			cell->getChildByName("onLinePlayer")->getChildByName("onLinePlayCount")->setColor(Color3B(128, 128, 128));
			cell->runAction(Sequence::create(MoveTo::create(0.2f, roomPos[tag]), CallFunc::create([=]{cell->stopNormalAni();}),nullptr));
			
			break;
		default:
			break;
		}
	}
}

