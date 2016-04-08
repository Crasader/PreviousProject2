#include "fish/FishManage.h"
#include "fish/FishGroupData.h"
#include "utill/FunUtil.h"
#include "fish/FishArrangeOne.h"
#include "fish/FishArrangeTwo.h"
#include "fish/FishArrangeThree.h"
#include "fish/FishArrangeFourh.h"
#include "data/GameData.h"
#include "utill/CollisionUtill.h"
#include "domain/game/GameManage.h"
#include "fish/FishOfAllKilled.h"
#include "domain/ai/AIManager.h"
#define BOOMFISHCIRCLE 200
FishManage* FishManage::_instance = 0;

FishManage* FishManage::getInstance(){
	if (_instance == 0){
		_instance = new FishManage();
	}
	return _instance;
}

FishManage::FishManage(){

}

Vector<Fish*> &FishManage::getAllFishInPool(){
	return fishPool;
}

int FishManage::getAllFishInPoolCount() {
    return fishPool.size();
}

Point FishManage::getBestRewardPostion() {
    Point point;
    point.x = 480;
    point.y = 270;
    int coin = 0;
    
    for(int i=0; i<fishPool.size(); i++) {
        if(coin < fishPool.at(i)->getFishGold()) {
            point = fishPool.at(i)->getPosition();
        }
    }
    return point ;
    
}

Fish* FishManage::createFishSingle(){
	auto fish = Fish::create();
	int randType = getRand(Server_Seed) % 27 + 1;   // TODO : change 27 to config by fish list numbers
	fish->initFish(randType);
	fishPool.pushBack(fish);
	return fish;
}
Fish* FishManage::createFishSingle(int type){
	auto fish = getFreeFishInCache();
	if (!fish)
	{
		return nullptr;
	}
	fish->setVisible(true);
	fish->initFish(type);
	fishPool.pushBack(fish);	
	
	if (fish->getFishType()==BossFish)
	{
		GameManage::getInstance()->getGuiLayer()->onBossWarning(type);
	}
	else if (fish->getFishType() == GoldFish)
	{
		AIManager::getInstance()->addCreateGoldFish();
	}

	return fish;
}
void FishManage::moveFishToCacheFromPool(Fish*fish)
{
	for (auto var:fishPool)
	{
		if (var==fish)
		{
			fish->setTag(-1);
			fishPool.eraseObject(fish);
			cacheFishPool.push_back(fish);
			return;
		}
	}
}
bool FishManage::initFishPool()
{
	fishPool.clear();
	cacheFishPool.clear();
	for (int i = 0; i < 500; i++)
	{
		auto fish = Fish::create();
		fish->setTag(-1);
		fish->retain();
		cacheFishPool.push_back(fish);
		m_layer->addChild(fish);
	}
	return true;
}
void FishManage::cleanVector()
{
	fishPool.clear();
}
Fish* FishManage::getFreeFishInCache()
{
	if (cacheFishPool.size()<=0)
	{
		return nullptr;
	}

	auto fish = cacheFishPool.back();
	cacheFishPool.pop_back();
	fish->setTag(1);
	return fish;
}
Fish* FishManage::createFishArrange(int type){
	Fish* fish = Fish::create();
	fish->initFish(type);
	fishPool.pushBack(fish);
	return fish;
}

void FishManage::createFishMonmentInterval(int fishid, int route,Vec2 startPos)
{
	Fish* fish = FishManage::getInstance()->createFishSingle(fishid);
	if (fish)
	{
		fish->setVisible(false);
		fish->setisAutoRemove(false);
		fish->setRoute(route);
		fish->setPosition(startPos);
		fish->setZOrder(fish->getFishZorder());
	}
	

	 
}


void FishManage::createFishGroup(int grouptag)
{
	auto gp = FishGroupData::getInstance()->getGroupBytag(grouptag);
	for (int i = 0; i < gp.singleTypefishGroups.size(); i++)
	{
		auto singlegp = gp.singleTypefishGroups[i];
		for (int j = 0; j < singlegp.fishCount; j++)
		{
			auto ac = Sequence::create(DelayTime::create(j*singlegp.IntervalCreateTime), CallFunc::create([=]{
				Fish* fish = FishManage::getInstance()->createFishSingle(singlegp.fishID);
				if (fish)
				{
					fish->setVisible(false);
					fish->setisAutoRemove(false);
					fish->setRoute(singlegp.fishRoute);
					fish->setPosition(singlegp.startPos);
					fish->setZOrder(fish->getFishZorder());
				}
				
				 

			}), nullptr);
			m_layer->getCreateFishAcNode()->runAction(ac)->setTag(20 + j);
		}

	}

}


void FishManage::createFishAssign(int fishId, int momentEightroutetag)
{
	if (fishId>300&&fishId<600)
	{
		createFishQueue(fishId, momentEightroutetag);
		return;
	}
	if (fishId>1000&&fishId<10000)
	{
		int count = fishId / 1000;
		int id = (fishId - count * 1000) / 10;
		float interval = fishId % 10;
		for (int i = 0; i < count;i++)
		{
			m_layer->getCreateFishAcNode()->runAction(Sequence::create(DelayTime::create(i*interval), CallFunc::create([=]{
				Fish* fish = fish = createFishSingle(id);
				if (fish)
				{
					fish->setVisible(false);
					fish->setisAutoRemove(false);
					fish->setMonentEightRoute(momentEightroutetag);
					fish->setZOrder(fish->getFishZorder());
				}
				
				
				 

			}), nullptr));
			
		}
		return;
	}
	Fish*fish= createFishSingle(fishId);
	if (fish)
	{
		fish->setVisible(false);
		fish->setisAutoRemove(false);
		fish->setMonentEightRoute(momentEightroutetag);
		fish->setZOrder(fish->getFishZorder());
	}
	

	 
}

void FishManage::createFishQueue(int fishId, int momentEightroutetag)
{
	if (fishId>300&&fishId<400)
	{
		int id = fishId-300;
		//鱼1
		auto fish = createFishSingle(id);
		Size size;
		if (fish)
		{
			size = fish->getContentSize();
			fish->setVisible(false);
			fish->setisAutoRemove(false);
			fish->setMonentEightRoute(momentEightroutetag);
			fish->setZOrder(fish->getFishZorder());
			fish->setPosition(MonmetEightRoutedata::getInstance()->getRouteBytag(momentEightroutetag).startPos + Vec2(size.width / 2 + 10, 0));
		}
		else
		{
			return;
		}
		 
		//鱼2
		fish = createFishSingle(id);
		if (fish)
		{
			fish->setVisible(false);
			fish->setisAutoRemove(false);
			fish->setMonentEightRoute(momentEightroutetag);
			fish->setZOrder(fish->getFishZorder());
			fish->setPosition(MonmetEightRoutedata::getInstance()->getRouteBytag(momentEightroutetag).startPos + Vec2(-size.width / 2 - 10, 20 + size.height / 2));
		}
		else
		{
			return;
		}
		
		 
		//鱼3
		fish = createFishSingle(id);
		if (fish)
		{
			fish->setVisible(false);
			fish->setisAutoRemove(false);
			fish->setMonentEightRoute(momentEightroutetag);
			fish->setZOrder(fish->getFishZorder());
			fish->setPosition(MonmetEightRoutedata::getInstance()->getRouteBytag(momentEightroutetag).startPos + Vec2(-size.width / 2 - 10, -20 - size.height / 2));
		}
		else
		{
			return;
		}
		
		 
	}
	else if (fishId>400&&fishId<500)
	{
		int id = fishId-400;
		//鱼1
		auto fish = createFishSingle(id);
		Size size;
		if (fish)
		{
			size = fish->getContentSize();
			fish->setVisible(false);
			fish->setisAutoRemove(false);
			fish->setMonentEightRoute(momentEightroutetag);
			fish->setZOrder(fish->getFishZorder());
			fish->setPosition(MonmetEightRoutedata::getInstance()->getRouteBytag(momentEightroutetag).startPos + Vec2(-(size.width / 2 + 10), -(20 + size.height / 2)));
		}
		else
		{
			return;
		}
		 
		//鱼2
		fish = createFishSingle(id);
		if (fish)
		{
			fish->setVisible(false);
			fish->setisAutoRemove(false);
			fish->setMonentEightRoute(momentEightroutetag);
			fish->setZOrder(fish->getFishZorder());
			fish->setPosition(MonmetEightRoutedata::getInstance()->getRouteBytag(momentEightroutetag).startPos + Vec2(-(size.width / 2 + 10), 20 + size.height / 2));
		}
		else
		{
			return;
		}

		
		 
		//鱼3
		fish = createFishSingle(id);
		if (fish)
		{
			fish->setVisible(false);
			fish->setisAutoRemove(false);
			fish->setMonentEightRoute(momentEightroutetag);
			fish->setZOrder(fish->getFishZorder());
			fish->setPosition(MonmetEightRoutedata::getInstance()->getRouteBytag(momentEightroutetag).startPos + Vec2(size.width / 2 + 10, -(20 + size.height / 2)));
		}
		else
		{
			return;
		}
		//鱼4
		fish = createFishSingle(id);
		if (fish)
		{
			fish->setVisible(false);
			fish->setisAutoRemove(false);
			fish->setMonentEightRoute(momentEightroutetag);
			fish->setZOrder(fish->getFishZorder());
			fish->setPosition(MonmetEightRoutedata::getInstance()->getRouteBytag(momentEightroutetag).startPos + Vec2(size.width / 2 + 10, 20 + size.height / 2));
		}
		else
		{
			return;
		} 
	}
	else 
	{
		int id = fishId-500;
		//鱼1
		auto fish = createFishSingle(id);
		Size size;
		if (fish)
		{
			size = fish->getContentSize();
			fish->setVisible(false);
			fish->setisAutoRemove(false);
			fish->setMonentEightRoute(momentEightroutetag);
			fish->setZOrder(fish->getFishZorder());
			fish->setPosition(MonmetEightRoutedata::getInstance()->getRouteBytag(momentEightroutetag).startPos + Vec2(-(size.width / 2 + 10), -(20 + size.height / 2)));
		}
		else
		{
			return;
		}
		
		 
		//鱼2
		fish = createFishSingle(id);
		if (fish)
		{
			fish->setVisible(false);
			fish->setisAutoRemove(false);
			fish->setMonentEightRoute(momentEightroutetag);
			fish->setZOrder(fish->getFishZorder());
			fish->setPosition(MonmetEightRoutedata::getInstance()->getRouteBytag(momentEightroutetag).startPos + Vec2(-(size.width / 2 + 10), 20 + size.height / 2));
		}
		else
		{
			return;
		}
	
		 
		//鱼3
		fish = createFishSingle(id);
		if (fish)
		{
			fish->setVisible(false);
			fish->setisAutoRemove(false);
			fish->setMonentEightRoute(momentEightroutetag);
			fish->setZOrder(fish->getFishZorder());
			fish->setPosition(MonmetEightRoutedata::getInstance()->getRouteBytag(momentEightroutetag).startPos + Vec2(size.width / 2 + 10, -(20 + size.height / 2)));
		}
		else
		{
			return;
		}

		
		 
		//鱼4
		fish = createFishSingle(id);
		if (fish)
		{
			fish->setVisible(false);
			fish->setisAutoRemove(false);
			fish->setMonentEightRoute(momentEightroutetag);
			fish->setZOrder(fish->getFishZorder());
			fish->setPosition(MonmetEightRoutedata::getInstance()->getRouteBytag(momentEightroutetag).startPos + Vec2(size.width / 2 + 10, 20 + size.height / 2));
		}
		else
		{
			return;
		}

		//鱼5
		fish = createFishSingle(id);
		if (fish)
		{
			fish->setVisible(false);
			fish->setisAutoRemove(false);
			fish->setMonentEightRoute(momentEightroutetag);
			fish->setZOrder(fish->getFishZorder());
			fish->setPosition(MonmetEightRoutedata::getInstance()->getRouteBytag(momentEightroutetag).startPos + Vec2(0, 0));
		}
		else
		{
			return;
		}

		
		 
	}
}






void FishManage::decideFishPos(Fish* fish){
	auto visibleSize = Director::getInstance()->getVisibleSize();
	int border = getRand(Server_Seed) % 10;
	switch (border){
	case 0:
	case 1:
	case 2:
	case 3:
	{
		auto x = fish->getBoundingBox().size.width/2;
		auto y = getRand(Server_Seed) % (int)(visibleSize.height);
		fish->setRotation(0);
		fish->setPosition(ccp(-x, y));
		fish->setDirection(RIGHT);
		break; }
	case 4:{
		auto x = getRand(Server_Seed) % (int)(visibleSize.width);
		auto y = fish->getBoundingBox().size.height/2;
		fish->setPosition(ccp(x, visibleSize.height + y));
		fish->setRotation(90);
		fish->setDirection(DOWN);
		break;
	}
	case 5:
	case 6:
	case 7:
	case 8:{
		auto x = fish->getBoundingBox().size.width/2;
		auto y = getRand(Server_Seed) % (int)(visibleSize.height);
		fish->setPosition(ccp(visibleSize.width + x, y));
		fish->setRotation(180);
		fish->setDirection(LEFT);
		break; }
	case 9:{
		auto x = getRand(Server_Seed) % (int)(visibleSize.width);
		auto y = fish->getBoundingBox().size.height/2;
		fish->setPosition(ccp(x, -y));
		fish->setRotation(270);
		fish->setDirection(UP);
		break; }
	}
}

void FishManage::removeFishWhichSwimOut()
{
	auto visibisize = Director::getInstance()->getVisibleSize();
	
	Vector<Fish*> needRemoveFishs;
	for (auto fish : fishPool)
	{
		auto box = ((Fish*)fish)->getBoundingBox();
		Rect rect = Rect(-5-box.size.width, -5-box.size.height, visibisize.width + box.size.width*2+10, visibisize.height + box.size.height*2+10);
		auto pos = fish->getPosition();
		if (!rect.containsPoint(pos)&&fish->getisAutoRemove())
		{
			needRemoveFishs.pushBack(fish);
		}
	}
	for (auto fish : needRemoveFishs)
	{
		GameManage::getInstance()->CatchTheFishOntheTurrent(fish, 0, nullptr);
		
	}
}
void FishManage::createFishRand(int fishID)
{
	Fish* fish = FishManage::getInstance()->createFishSingle(fishID);
	if (!fish)
	{
		return;
	}
	decideFishPos(fish);
	
	auto k = getAngleByPos(Vec2(fish->getPositionX(), fish->getPositionY()));
	if (fishID<50)
	{
		k += rand_0_1() * 30 - 15;
	}
	else
	{
		k += rand_0_1() * 20 - 10;
	}
	
	fish->setMoveAngle(k);
	if (fishID<50)
	{
		fish->move(3);
	}
	else
	{
		fish->move(4);
	}
	
	fish->setZOrder(fish->getFishZorder());
	 

}
void FishManage::createFishArrangeRand(int fishID)
{
	auto fish = createFishSingle(fishID);
	if (fish)
	{
		decideFishPos(fish);
		auto k = getAngleByPos(Vec2(fish->getPositionX(), fish->getPositionY()));
		k += rand_0_1() * 20 - 10;
		fish->setMoveAngle(k);
		fish->move(4);
		fish->setZOrder(fish->getFishZorder());
	}
	
	 

}



void FishManage::LoadOnement(Moment*monent)
{
	///需要优化
    m_nowMonent = monent;
}

void FishManage::UpdataCreateFish(float dt)
{
	for (auto it = waitCreateMomentEightFishs.begin(); it != waitCreateMomentEightFishs.end();)  
	{
		it->wait_time -= dt;
		if (it->wait_time<0)
		{
			int count = getintRandonNumByAtoB(it->fish_startcount, it->fish_endcount);
			for (int i = 0; i < count;i++)
			{
				auto fishid = getRandValueInVec(it->fish_ids);
				auto routesize = it->fishRoutes.size();
				if (routesize>0)
				{
					auto route = getRandValueInVec(it->fishRoutes);
					switch (route)
					{
					case -1:
						if (fishid >= 100 && fishid
							< 200)
						{
							createFishArrangeRand(fishid);
						}
						else
						{
							createFishRand(fishid);
						}
						break;
					case -2:
						createFishAssign(fishid, getRand(Server_Seed) % 16 + 1);
						break;
					case -3:
						createFishAssign(fishid, getRand(Server_Seed) % 4 + 17);
						break;
					default:
						createFishAssign(fishid, route);
						break;
					}
				}
				else
				{
					if (fishid >= 100 && fishid
						< 200)
					{
						createFishArrangeRand(fishid);
					}
					else if (fishid<100||(fishid>200&&fishid<300))
					{
						createFishRand(fishid);
					}
				}
			}
			it=waitCreateMomentEightFishs.erase(it);
		}
		else
		{
			it++;
		}
	}
}
void FishManage::UpdateWhenController(float dt)
{
	if (m_nowMonent)
	{
		if (m_nowMonent->updata(dt))
		{
			CC_SAFE_DELETE(m_nowMonent);
			m_nowMonent = nullptr;
		}
		
	}
}



Fish*FishManage::getFishByPosInPool(Point pos)
{
	for (auto var:fishPool)
	{
		if (CollisionUtill::isCollisionFishAAndPos(var, pos))
		{
			return var;
		}
	}
	return nullptr;
}

void FishManage::createCycleFish(int count, int Radius, int fishID, Point center, Point curPos,float moveTime)
{
	float diffAngle = 360.0f/count;
	for (int i = 0; i < count; i++)
	{
		Fish* fish = FishManage::getInstance()->createFishSingle(fishID); 
		if (fish)
		{
			fish->setisAutoRemove(false);
			fish->setPosition(center.x + Radius*cos(CC_DEGREES_TO_RADIANS(i*diffAngle)), center.y + Radius*sin(CC_DEGREES_TO_RADIANS(diffAngle*i)));
			auto moveto = MoveBy::create(moveTime, curPos);
			fish->runAction(moveto)->setTag(kTagAcMove);
			fish->runAction(Sequence::create(DelayTime::create(moveto->getDuration()), CallFunc::create([=]{GameManage::getInstance()->CatchTheFishOntheTurrent(fish, false, nullptr); }), nullptr));
			fish->setZOrder(fish->getFishZorder());
		}
	
		 
	}
	

}
void FishManage::onAllKilledFishDead(Fish*fish, PlayerTurret* pTurret)
{
	Node* allKillAninode = Node::create();
	allKillAninode->setPosition(0, 0);
	fish->setZOrder(fish->getFishZorder());

	Vector<Fish*> needDeadFishs;
	for (auto var:fishPool)
	{
		if (var->getFishType() == AllKilledFish)
		{
			var->setFishType(AllKilledFishEX);
			needDeadFishs.pushBack(var);
		}
	}
	if (needDeadFishs.size()>0)
	{
		//闪电光圈
		auto sp = Sprite::create();
		sp->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniGuangqiu")));
		sp->setPosition(fish->getPosition());
		allKillAninode->addChild(sp, 2);

		auto shandian = Sprite::create("game/ui/ani/TX_shandian/shandian_1.png");
		shandian->setPosition(fish->getPosition());
		shandian->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		allKillAninode->addChild(shandian,1);
		shandian->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniShandian")));
		auto rorate = getTurretRotation(fish->getPosition(), needDeadFishs.at(0)->getPosition());
		auto distans = fish->getPosition().distance(needDeadFishs.at(0)->getPosition());
		shandian->setRotation(-90 + rorate);
	/*	shandian->setScaleX(distans / 933.0f);*/
		shandian->setTextureRect(Rect(0, 0, distans, 70));
	}
	for (int i = 0; i < needDeadFishs.size();i++)
	{	
		auto var = needDeadFishs.at(i);
		//闪电光圈
		auto sp = Sprite::create();
		sp->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniGuangqiu")));
		sp->setPosition(var->getPosition());
		allKillAninode->addChild(sp, 2);
		//闪电
		if ((i+1)<needDeadFishs.size())
		{

			auto shandian = Sprite::create("game/ui/ani/TX_shandian/shandian_1.png");
			shandian->setPosition(var->getPosition());
			shandian->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
			shandian->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniShandian")));
			auto rorate = getTurretRotation(var->getPosition(), needDeadFishs.at(i + 1)->getPosition());
			auto distans = var->getPosition().distance(needDeadFishs.at(i + 1)->getPosition());
			shandian->setRotation(-var->getRotation()-90 + rorate);
			shandian->setTextureRect(Rect(0, 0, distans, 70));
			/*shandian->setScaleX(distans / 933.0f);*/
			allKillAninode->addChild(shandian, 1);
			GameManage::getInstance()->CatchTheFishOntheTurrent(var, 1, pTurret);
		}
		
	}
	allKillAninode->runAction(Sequence::create(DelayTime::create(1.0f), RemoveSelf::create(), nullptr));

}
void FishManage::onBoomFishDead(Fish*fish, PlayerTurret* pTurret)
{
	auto pos = fish->getPosition();

	auto fishPool = FishManage::getInstance()->getAllFishInPool();
	auto data = GameData::getInstance();
	for (auto var : fishPool)
	{
		if (CollisionUtill::isCollisionFishAAndRect(var, Rect(pos.x - 200, pos.y - 200, 400, 400)))
		{
			GameManage::getInstance()->CatchTheFishOntheTurrent(var, 1, pTurret);
		}
	}
}


void FishManage::onClearFish()
{
	clearMomentEightItemFishs();
	m_layer->onClearFish();

}

void FishManage::clearMomentEightItemFishs()
{
	m_layer->getCreateFishAcNode()->stopAllActions();
	waitCreateMomentEightFishs.clear();
}
void FishManage::addMomentEightItemFishs(MomentEightItemFishs fishs)
{
	waitCreateMomentEightFishs.push_back(fishs);
}

Fish*FishManage::getHignSoreInPool()
{
	auto vec = fishPool;
	if (vec.size()==0)
	{
		return nullptr;
	}
	Fish* fish = vec.at(0);
	for (auto var:vec)
	{
		if (var->getFishGold()>=fish->getFishGold())
		{
			fish = var;
		}
	}
	return fish;
}
Fish*FishManage::getLowDistanceInPool(Point pos)
{
	auto vec = fishPool;
	if (vec.size() == 0)
	{
		return nullptr;
	}
	Fish* fish = vec.at(0);
	auto distance = pos.distance(fish->getPosition());
	for (auto var : vec)
	{
		if (pos.distance(var->getPosition()) <= pos.distance(fish->getPosition()))
		{
			fish = var;
		}
	}
	return fish;
}


//server 
void FishManage::addServerItemFishs(MsgFishInfo fishs)
{
	waitCreateFishes.push_back(fishs);
}
void FishManage::clearServerItemFishs()
{
	m_layer->getCreateFishAcNode()->stopAllActions();
	waitCreateFishes.clear();
}
void FishManage::UpdateServerWhenController(float dt)
{

}
void FishManage::UpdataServerCreateFish(float dt)
{
	for (auto it = waitCreateFishes.begin(); it != waitCreateFishes.end();)
	{
		it->time -= dt;
		if (it->time < 0)
		{
			auto route = it->fish_route;
			auto fishid = it->fish_ids;
			switch (route)
			{
			case -1:
				if (fishid >= 100 && fishid
					< 200)
				{
					createFishArrangeRand(fishid);
				}
				else if (fishid>999)
				{
					break;
				}
				else
				{
					createFishRand(fishid);
				}
				break;
			case -2:
				createFishAssign(fishid, getRand(Server_Seed) % 16 + 1);
				break;
			case -3:
				createFishAssign(fishid, getRand(Server_Seed) % 4 + 17);
				break;
			default:
				createFishAssign(fishid, route);
				break;
			}
			it = waitCreateFishes.erase(it);
		}
		else
		{
			it++;
		}
	}
}