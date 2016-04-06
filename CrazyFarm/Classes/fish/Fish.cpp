#include "fish/Fish.h"
#include "fish/FishAniMannage.h"
#include "utill/CircleMoveTo.h"
#include "FishManage.h"
#include "FishAniMannage.h"
#include "utill/AnimationUtil.h"
#include"utill/FunUtil.h"
#include "utill/Audio.h"
#include "domain/game/GameManage.h"
#include "utill/MagicEffect.h"

bool Fish::init(){
	if (!Sprite::init())
	{
		return false;
	}
	
	return true;
}

void Fish::initFish(int fishID){

	scheduleUpdate();
	setisAutoRemove(true);
	aniEmptyNode = Node::create();
	addChild(aniEmptyNode);
	setTargeLightTurret(nullptr);
	setTargeLockTurret(nullptr);
	schedule(schedule_selector(Fish::moveUpdata), 0, CC_REPEAT_FOREVER, 0);
	m_movetype = 0;
	setFishType(getFishTypeByID(fishID));

	if (getFishType()==ArrangeFish)
	{
		auto fishdata = ConfigFish::getInstance()->getFish(fishID);
		fishGold = getintRandonNumByAtoB(fishdata.baseRewardStart, fishdata.baseRewardEnd);
		this->grabProbability = fishdata.probability;
		this->fishID = fishID;
		this->speed = getRandValueInVec(fishdata.move_speeds);
		this->experience = getFishExperienceByID(fishID);
		this->BonusPoorGold = fishdata.bonus_pool_reward;
		setFishType(getFishTypeByID(fishID));
		setuiId(fishdata.uiId);
		initFishAnim(fishdata.uiId);
		rewards = fishdata.rewards;
		LogEventFish::getInstance()->addFishCreateTimes(fishID);
	}
	else if (getFishType()==AllKilledFish)
	{
		int fishid = getRand(Server_Seed) % 2 ? getRand(Server_Seed) % 7 + 4 : getRand(Server_Seed) % 6 + 30;
		auto fishdata = ConfigFish::getInstance()->getFish(fishid);
		if (fishid == 44)
		{
			fishGold = getintRandonNumByAtoB(fishdata.baseRewardStart, fishdata.baseRewardEnd, 50);
		}
		else
		{
			fishGold = getintRandonNumByAtoB(fishdata.baseRewardStart, fishdata.baseRewardEnd);
		}
		this->grabProbability = fishdata.probability;
		this->fishID = fishID;
		this->speed = getRandValueInVec(fishdata.move_speeds);
		this->experience = getFishExperienceByID(fishid);
		setFishType(getFishTypeByID(fishID));
		initFishAnim(fishdata.uiId);
		setuiId(fishdata.uiId);
		obbdatas = ConfigFishCollisionOBB::getInstance()->getFishFOBBPoints(fishdata.uiId);
		rewards = fishdata.rewards;
		centerPos = getContentSize() / 2;
		auto aninode = Sprite::create("game/ui/effect/allkilledEffect.png");
		aninode->setPosition(getContentSize() / 2);
		addChild(aninode, -1);
		aninode->runAction(RepeatForever::create(RotateBy::create(7, 360)));
		LogEventFish::getInstance()->addFishCreateTimes(fishID);
	}
	else
	{
		auto fishdata = ConfigFish::getInstance()->getFish(fishID);
		fishGold = getintRandonNumByAtoB(fishdata.baseRewardStart, fishdata.baseRewardEnd);
		this->grabProbability = fishdata.probability;
		this->fishID = fishID;
		this->speed = getRandValueInVec(fishdata.move_speeds);
		this->experience = getFishExperienceByID(fishID);

		BonusPoorGold = fishdata.bonus_pool_reward;
		setuiId(fishdata.uiId);
		initFishAnim(fishdata.uiId);
		rewards = fishdata.rewards;
		obbdatas = ConfigFishCollisionOBB::getInstance()->getFishFOBBPoints(fishdata.uiId);
		LogEventFish::getInstance()->addFishCreateTimes(fishID);
		centerPos = getCentrenPos();
	}
	addShader();

}

void Fish::initFishAnim(int fishID){
	//4.5新加，为了让fish类统一
	if (getFishType()==ArrangeFish)
	{
		switch (fishID)
		{
		case 101:
		{
			//主鱼
			int randarray[7] = { 10, 30, 31, 32, 33, 34, 35 };
			int id = randarray[getRand(Server_Seed) % 7];
			auto acName = String::createWithFormat("swim_%d", id);
			auto ac = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
			auto sp1 = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
			sp1->runAction(ac);
			auto maggiceff = MagicEffect::create(1, true);
			maggiceff->setPosition(maggiceff->getContentSize() / 2);
			addChild(maggiceff, 2);
			sp1->setPosition(maggiceff->getPosition());
			addChild(sp1, 2);
			obbdatas = ConfigFishCollisionOBB::getInstance()->getFishFOBBPoints(101);
			fishes.pushBack(sp1);
			centerPos = maggiceff->getContentSize() / 2;

			fishes.pushBack(maggiceff);
			//副鱼
			int randarray1[6] = { 2, 3, 4, 7, 8, 9 };
			id = randarray1[getRand(Server_Seed) % 6];
			acName = String::createWithFormat("swim_%d", id);
			auto ac1 = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
			auto ac2 = ac1->clone();


			auto sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
			sp->runAction(ac1);
			maggiceff = MagicEffect::create(2, true);
			maggiceff->setPosition(-35, centerPos.y);
			addChild(maggiceff, 1);
			sp->setPosition(maggiceff->getPosition());
			addChild(sp, 1);
			fishes.pushBack(sp);
			fishes.pushBack(maggiceff);
			sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
			maggiceff = MagicEffect::create(2, true);
			maggiceff->setPosition(137, centerPos.y);
			addChild(maggiceff, 1);
			sp->setPosition(maggiceff->getPosition());
			sp->runAction(ac2);
			addChild(sp, 1);
			fishes.pushBack(sp);
			fishes.pushBack(maggiceff);
		}
			break;
		case 102:
		{
			//主鱼
			int randarray[7] = { 10, 30, 31, 32, 33, 34, 35 };
			int id = randarray[getRand(Server_Seed) % 7];
			auto mainfish = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));

			auto acName = String::createWithFormat("swim_%d", id);
			auto ac = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
			mainfish->runAction(ac);
			auto maggiceff = MagicEffect::create(1, false);
			maggiceff->stopAllActions();
			maggiceff->setPosition(maggiceff->getContentSize() / 2);
			addChild(maggiceff, 1);
			mainfish->setPosition(maggiceff->getPosition());
			addChild(mainfish, 1);
			fishes.pushBack(mainfish);
			obbdatas = ConfigFishCollisionOBB::getInstance()->getFishFOBBPoints(102);
			centerPos = maggiceff->getContentSize() / 2;
			fishes.pushBack(maggiceff);
			//副鱼
			int randarray1[6] = { 2, 4, 7, 8, 32, 33 };
			id = randarray1[getRand(Server_Seed) % 6];
			auto mainSize = getContentSize();
			auto AffiliateSize = FishAniMannage::getInstance()->getSpriteById(id)->getOriginalSize();
			acName = String::createWithFormat("swim_%d", id);
			auto ac1 = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
			auto ac2 = ac1->clone();
			auto ac3 = ac1->clone();
			auto ac4 = ac1->clone();
			setAnchorPoint(Point::ANCHOR_MIDDLE);
			auto sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
			maggiceff = MagicEffect::create(3, false);
			maggiceff->setPosition(-15, -15);
			addChild(maggiceff, 0);
			sp->setPosition(maggiceff->getPosition());
			sp->runAction(ac1);
			addChild(sp, 1);
			fishes.pushBack(sp);
			fishes.pushBack(maggiceff);
			sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
			maggiceff = MagicEffect::create(3, false);
			maggiceff->setPosition(-15, -15 + 132);
			addChild(maggiceff, 0);
			sp->setPosition(maggiceff->getPosition());
			sp->runAction(ac2);
			addChild(sp, 1);
			fishes.pushBack(sp);
			fishes.pushBack(maggiceff);
			sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
			maggiceff = MagicEffect::create(3, false);
			maggiceff->setPosition(-15 + 132, -15 + 132);
			addChild(maggiceff, 0);
			sp->setPosition(maggiceff->getPosition());
			sp->runAction(ac3);
			addChild(sp, 1);
			fishes.pushBack(sp);
			fishes.pushBack(maggiceff);
			sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
			maggiceff = MagicEffect::create(3, false);
			maggiceff->setPosition(-15 + 132, -15);
			addChild(maggiceff, 0);
			sp->setPosition(maggiceff->getPosition());
			sp->runAction(ac3);
			addChild(sp, 1);
			fishes.pushBack(sp);
			fishes.pushBack(maggiceff);
		}

			break;
		case  103:
		{
			//主鱼
			int randarray[7] = { 10, 30, 31, 32, 33, 34, 35 };
			int id = randarray[getRand(Server_Seed) % 7];

			auto maggiceff = MagicEffect::create(4, false);
			maggiceff->stopAllActions();
			maggiceff->setPosition(0, 0);
			maggiceff->setAnchorPoint(Point::ZERO);
			addChild(maggiceff, 0);
			auto mainfish = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
			mainfish->setPosition(maggiceff->getContentSize() / 2);
			addChild(mainfish, 3);
			centerPos = mainfish->getPosition();
			auto acName = String::createWithFormat("swim_%d", id);
			auto ac = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
			mainfish->runAction(ac);
			obbdatas = ConfigFishCollisionOBB::getInstance()->getFishFOBBPoints(103);
			fishes.pushBack(mainfish);
			fishes.pushBack(maggiceff);
			centerPos = maggiceff->getContentSize() / 2;
			//副鱼
			int randarray1[6] = { 2, 3, 4, 7, 8, 9 };
			id = randarray1[getRand(Server_Seed) % 6];
			acName = String::createWithFormat("swim_%d", id);
			auto ac1 = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
			auto ac2 = ac1->clone();
			auto ac3 = ac1->clone();



			auto maggiceff1 = MagicEffect::create(3, false);
			maggiceff1->setPosition(145, maggiceff->getContentSize().height / 2);
			addChild(maggiceff1, 0);
			auto sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
			sp->setPosition(maggiceff1->getPosition());
			sp->runAction(ac1);
			addChild(sp, 1);
			fishes.pushBack(sp);
			fishes.pushBack(maggiceff1);

			auto maggiceff2 = MagicEffect::create(3, false);
			maggiceff2->setPosition(25, -8);
			addChild(maggiceff2, 0);
			sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
			sp->setPosition(maggiceff2->getPosition());
			sp->runAction(ac2);
			addChild(sp, 1);
			fishes.pushBack(sp);
			fishes.pushBack(maggiceff2);

			auto maggiceff3 = MagicEffect::create(3, false);
			maggiceff3->setPosition(25, 8 + maggiceff->getContentSize().height);
			addChild(maggiceff3, 0);
			sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
			sp->setPosition(maggiceff3->getPosition());
			sp->runAction(ac3);
			addChild(sp, 1);
			fishes.pushBack(sp);
			fishes.pushBack(maggiceff3);
		}
			break;
		case 104:
		{
			//主鱼
			int randarray[9] = { 4, 7, 8, 9, 10, 30, 31, 32, 33 };
			int id = randarray[getRand(Server_Seed) % 9];
			auto maggiceff = MagicEffect::create(5, true);
			maggiceff->setPosition(0, 0);
			maggiceff->setAnchorPoint(Point::ZERO);
			addChild(maggiceff, -1);
			auto mainfish = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
			mainfish->setPosition(maggiceff->getContentSize() / 2);
			addChild(mainfish);
			fishes.pushBack(mainfish);
			fishes.pushBack(maggiceff);
			auto acName = String::createWithFormat("swim_%d", id);
			auto ac = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
			auto ac1 = ac->clone();
			auto ac2 = ac->clone();
			auto ac3 = ac->clone();
			mainfish->runAction(ac);
			obbdatas = ConfigFishCollisionOBB::getInstance()->getFishFOBBPoints(104);




			auto maggiceff1 = MagicEffect::create(5, true);
			maggiceff1->setPosition(108, maggiceff->getContentSize().height / 2);
			addChild(maggiceff1, -1);
			auto sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
			sp->setPosition(maggiceff1->getPosition());
			sp->runAction(ac1);
			addChild(sp);
			fishes.pushBack(maggiceff1);
			fishes.pushBack(sp);
			centerPos = maggiceff1->getPosition();

			auto maggiceff2 = MagicEffect::create(5, true);
			maggiceff2->setPosition(130, -20);
			addChild(maggiceff2, -1);
			sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
			sp->setPosition(maggiceff2->getPosition());
			sp->runAction(ac2);
			addChild(sp);
			fishes.pushBack(maggiceff2);
			fishes.pushBack(sp);

			auto maggiceff3 = MagicEffect::create(5, true);
			maggiceff3->setPosition(130 + 72, -20);
			addChild(maggiceff3, -1);
			sp = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(id));
			sp->setPosition(maggiceff3->getPosition());
			sp->runAction(ac3);
			addChild(sp);
			fishes.pushBack(sp);
			fishes.pushBack(maggiceff3);
		}

			break;
		default:
			break;
		}
		
		
	}
	else
	{
		initWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(fishID));

		auto acName = String::createWithFormat("swim_%d", fishID);
		auto ac = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
		ac->setTag(kTagAcNormal);
		runAction(ac);

		//BOSS鱼特效
		if (fishID >= 50 && fishID < 60)
		{
			auto aninode = Sprite::create();
			aninode->setPosition(getContentSize().width*0.6, getContentSize().height / 2);
			addChild(aninode, -1);
			aninode->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniBossLight")));
		}
		//黄金鱼特效
		else if (fishID >= 40 && fishID < 50)
		{
			auto aninode = Sprite::create();
			aninode->setPosition(getContentSize().width*0.4, getContentSize().height / 2);
			addChild(aninode);
			aninode->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniGoldfish")));

			if (fishID == 44)
			{
				auto aninode1 = Sprite::create("game/ui/effect/frogEffect.png");
				aninode1->setPosition(getContentSize() / 2);
				addChild(aninode1, -1);
				aninode1->runAction(RepeatForever::create(RotateBy::create(5, 360)));

			}
		}
	}
}
void Fish::update(float dt)
{


	if (getPosition().distance(LastPos) > 0)
	{
		auto raroAngle = 1.5*3.1415926f - (getPosition() - LastPos).getAngle();
		setRotation(CC_RADIANS_TO_DEGREES(raroAngle) + 90);
		LastPos = getPosition();

	}


}



int Fish::getFishGoldByID(int fishID){
	//TODO
	return 0;
}
FISHTYPE Fish::getFishTypeByID(int fishID)
{
	if (fishID<40)
	{
		return NormalFish;
	}
	else if (fishID>=40&&fishID<50)
	{
		return GoldFish;
	}
	else if (fishID >= 50 && fishID < 60)
	{
		return BossFish;
	}
	else if (fishID ==201)
	{
		return BoomFish;
	}
	else if (fishID == 202)
	{
		return AllKilledFish;
	}
	else if (fishID >=100&&fishID<200)
	{
		return ArrangeFish;
	}
}

int Fish::getFishExperienceByID(int fishID){
	//TODO
	return ConfigFish::getInstance()->getFish(fishID).exp;
}

float Fish::getFishSpeedByID(int fishID){
	return 80;
}

void Fish::moveUpdata(float dt)
{
	switch (m_movetype)
	{
	case 1:
		moveFishStraight(dt);
		break;
	case 2:
		moveFishCircle(dt);
		break;
	case 3:
		moveFishRandomStraight(dt);
		break;
	case 4:
		moveFishRandomStraightForBigFish(dt);
		break;
	default:
		break;
	}
}

void Fish::move(int moveType){
	//选择鱼的移动模式
	unscheduleUpdate();
	m_movetype = moveType;
	
}

void Fish::moveFishStraight(float dt){
	//TODO 鱼的直线移动
	Point nextPos = getNextPostion(getPosition(), dt*speed, this->getRotation());
	setPosition(getPosition() + nextPos);

}

void Fish::moveFishCircle(float dt){
	//TODO 鱼的圆形移动
	Point circlePoint = this->getPosition();
	auto cirlce = CircleBy::create(circlePoint, 2, 360, 10, true);
	this->runAction(cirlce);
}

void Fish::moveFishRandomStraight(float dt){
	Point nextPos = getRandomPostion(speed,dt, fMoveAngle);
	setPosition(getPosition() + nextPos);
	setRotation(360 - fMoveAngle);
}

void Fish::moveFishRandomStraightForBigFish(float dt){

	Point nextPos = getRandomPostionForBigFish(speed, dt, fMoveAngle);
	setPosition(getPosition()+nextPos);
	setRotation(360 - fMoveAngle);
}



void Fish::moveFishRandomCurve(float dt)
{
	float angle = 0;
	Point nextPos = getRandomPostion(dt*speed, this->getDirection(), angle);
	setPosition(nextPos);

	runAction(RotateTo::create(0.1, 360 - angle));
}

Point Fish::getNextPostion(Point pos, float speed, float degree){
	//TODO 完善鱼的直线移动
	if (degree < 0){
		degree += 360;
	}
	//图片自身朝下
	float next_x = speed*cos(CC_DEGREES_TO_RADIANS(degree));
	float next_y = speed*sin(CC_DEGREES_TO_RADIANS(degree));
	int rotation = (int)degree % 360;
	if (rotation < 90){
		pos.x += abs(next_x);
		pos.y -= abs(next_y);
		return Vec2(next_x, -next_y);
	}
	else if (rotation >= 90 && rotation < 180){
		pos.x -= abs(next_x);
		pos.y -= abs(next_y);
		return Vec2(-next_x, -next_y);
	}
	else if (rotation >= 180 && rotation < 270){
		pos.x -= abs(next_x);
		pos.y += abs(next_y);
		return Vec2(next_x, next_y);
	}
	else if (rotation >= 270 && rotation < 360){
		pos.x += abs(next_x);
		pos.y += abs(next_y);
		return Vec2(next_x, -next_y);
	}
	return  Point(pos.x, pos.y);
}


void Fish::onLockShoot(PlayerTurret*turret)
{
	auto aniFishLockNode = Sprite::create();
	aniFishLockNode->setPosition(centerPos);
	addChild(aniFishLockNode,10,"lockani");
	aniFishLockNode->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniFishLock")));
	setTargeLockTurret(turret);
}
void Fish::stopLockShoot()
{
	auto node = getChildByName("lockani");
	if (node)
	{
		node->removeFromParentAndCleanup(1);
	}
	setTargeLockTurret(nullptr);

}

void Fish::onLightShoot(PlayerTurret*turret)
{
	auto aniFishLightNode = Sprite::create();
	aniFishLightNode->setPosition(centerPos);
	addChild(aniFishLightNode,10,"lightani");
	aniFishLightNode->setGlobalZOrder(10);
	aniFishLightNode->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniDianQiu")));
	setTargeLightTurret(turret);

}
void Fish::stopLightShoot()
{
	auto node = getChildByName("lightani");
	if (node)
	{
		node->removeFromParentAndCleanup(1);
	}
	setTargeLightTurret(nullptr);
}


Point Fish::getRandomPostion(float speed, float dt, float &angle)
{
	speed *= dt;
	float diffAngle = (rand_0_1() *6.0f-3.0f)/10.0f;
	auto fps = Director::getInstance()->getAnimationInterval();
	angle += diffAngle*dt*1/fps;
	return Vec2(speed*cos(CC_DEGREES_TO_RADIANS(angle)), speed*sin(CC_DEGREES_TO_RADIANS(angle)));

}
Point Fish::getRandomPostionForBigFish(float speed, float dt, float &angle)
{
	speed *= dt;
	float diffAngle = (rand_0_1() *6.0f - 3.0f)*3.0/5/50;
	angle += diffAngle;
	return Vec2(speed*cos(CC_DEGREES_TO_RADIANS(angle)), speed*sin(CC_DEGREES_TO_RADIANS(angle)));

}
void Fish::setRoute(int routeTag)
{
	m_Route = FishRouteData::getInstance()->getRouteBytag(routeTag);

	auto actionArray = Vector<FiniteTimeAction*>();


	
	RoutePoint* p = m_Route.head;
	while (p != nullptr)
	{
		Vector<FiniteTimeAction*> *acArray;
		acArray = &actionArray;
	
		acArray->pushBack(DelayTime::create(p->delay));
		acArray->pushBack(CallFunc::create([&]{setVisible(true); }));
		switch (p->moveState)
		{
		case 1:
		{	
			acArray->pushBack(MoveBy::create(p->time, p->MoveByPos));
		}
			break;
		
		case 2:
		{
			//圆周运动
			acArray->pushBack(CircleMoveTo::create(p->time, p->centrePos, p->ScaleDiff, p->circleAngle,p->isClockwise));
		}
		break;
		case 3:
		{
			auto str = String::createWithFormat("%s_%d", p->aniName.c_str(), fishID);
			acArray->pushBack(FishAniMannage::getInstance()->getAnimate(str->getCString()));
		}
		break;
		default:
			break;
		}

		p = p->next;
	}
	auto acNoRepeat = Sequence::create(actionArray);
	runAction(acNoRepeat)->setTag(kTagAcMove);
	runAction(Sequence::create(DelayTime::create(acNoRepeat->getDuration()), CallFunc::create([&]{GameManage::getInstance()->CatchTheFishOntheTurrent(this, 0, nullptr); }), nullptr));
}


void Fish::setMonentEightRoute(int routeTag)
{
	auto momentEightRoute = MonmetEightRoutedata::getInstance()->getRouteBytag(routeTag);

	setPosition(momentEightRoute.startPos);

	auto actionArray = Vector<FiniteTimeAction*>();


	MonmentEightRoutePoint* p = momentEightRoute.head;
	while (p != nullptr)
	{
		Vector<FiniteTimeAction*> *acArray= &actionArray;
		
		acArray->pushBack(DelayTime::create(p->delay));
		acArray->pushBack(CallFunc::create([&]{setVisible(true); }));
		switch (p->moveState)
		{
		case 1:
		{
			acArray->pushBack(MoveBy::create(p->time, p->MoveByPos));
		}
		break;

		case 2:
		{
			//圆周运动
			acArray->pushBack(CircleMoveTo::create(p->time, p->centrePos, p->ScaleDiff, p->circleAngle, p->isClockwise));
		}
		break;
		case 3:
		{
			auto str = String::createWithFormat("%s_%d", p->aniName.c_str(), fishID);
			auto ac = FishAniMannage::getInstance()->getAnimate(str->getCString());
			if (ac)
			{

				auto seq = Sequence::create(
					CallFunc::create([=]{
					this->stopActionByTag(kTagAcNormal);
					Audio::getInstance()->playSound(FISH50JUMP);
				}), ac, CallFunc::create([=]{
					auto acName = String::createWithFormat("swim_%d", this->fishID);
					auto ac = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
					ac->setTag(kTagAcNormal);
					this->runAction(ac);
					auto pos = this->getPosition();
					auto rad = CC_DEGREES_TO_RADIANS(360-this->getRotation());
					this->setPosition(pos + Vec2(cos(rad) * 5, sin(rad) * 5));
				}), nullptr);
				acArray->pushBack(seq);
			}
			
		}
		break;
		case 4:
		{
			ccBezierConfig tr0;
			tr0.endPosition = p->curPos;
			tr0.controlPoint_1 = p->besizerPos1;
			tr0.controlPoint_2 = p->besizerPos2;
			acArray->pushBack(BezierBy::create(p->time, tr0));
		}
		break;
		default:
			break;
		}

		p = p->next;
	}

	auto acNoRepeat = Sequence::create(actionArray);
	runAction(acNoRepeat)->setTag(kTagAcMove);
	runAction(Sequence::create(DelayTime::create(acNoRepeat->getDuration()), CallFunc::create([&]{GameManage::getInstance()->CatchTheFishOntheTurrent(this, 0, nullptr); }), nullptr));
}


void Fish::addShader()
{
	if (getFishType()==ArrangeFish)
	{
		return;
	}
	auto m_shadesprite = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(nUiID));
	m_shadesprite->setPosition(getContentSize().width*0.65,getContentSize().height*0.35);
	addChild(m_shadesprite, -1,"shader");


	auto acName = String::createWithFormat("swim_%d", nUiID);
	auto ac = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
	m_shadesprite->setColor(Color3B::BLACK);
	m_shadesprite->setOpacity(GLubyte(150));
	m_shadesprite->runAction(ac);

}
void Fish::ShadeUpdata(float dt)
{
	auto m_shadesprite = getChildByName("shader");
	if (m_shadesprite!=nullptr)
	{
		m_shadesprite->setPosition(getPositionX() + getContentSize().width*0.15, getPositionY() + getContentSize().height*-0.15);
		m_shadesprite->setRotation(getRotation());
	}
}



Sprite* Fish::getRectSprite(){
	return image;
}

int Fish::getFishID() {
    return fishID;
}


void Fish::removeself()
{
	
	stopLightShoot();
	stopLockShoot();	
	setVisible(false);
	stopAllActions();
	unscheduleAllCallbacks();
	removeAllChildrenWithCleanup(1);
	FishManage::getInstance()->moveFishToCacheFromPool(this);
	//removeFromParentAndCleanup(1);
}

void Fish::onHeart()
{
	if (getFishType()==ArrangeFish)
	{
		for (auto child : fishes)
		{
			auto ac = child->getActionByTag(50);
			if (ac)
			{
				child->stopAllActionsByTag(50);
			}
			auto action = Sequence::create(
				CallFunc::create([=]{child->setColor(Color3B(135, 105, 80)); }),
				DelayTime::create(0.3f),
				CallFunc::create([=]{child->setColor(Color3B::WHITE); }),
				nullptr);
			action->setTag(50);
			child->runAction(action);
		}
	}
	else
	{
		auto ac = aniEmptyNode->getActionByTag(50);
		if (ac)
		{
			aniEmptyNode->stopAllActionsByTag(50);
		}
		auto action = Sequence::create(
			CallFunc::create([=]{setColor(Color3B(135, 105, 80)); }),
			DelayTime::create(0.3f),
			CallFunc::create([=]{setColor(Color3B::WHITE); }),
			nullptr);
		action->setTag(50);
		aniEmptyNode->runAction(action);
	}


	

	
}
void Fish::onFreeze()
{
	if (getFishType()==ArrangeFish)
	{
		for (auto child : fishes)
		{
			child->pause();
		}
	}
	else
	{
		pause();
		auto node = getChildByName("shader");
		if (node)
		{
			node->pause();
		}
	}
	
	//冻结时候无受击动画处理
	//_scheduler->pauseTarget(this);
	//stopAllActionsByTag(kTagAcNormal);
	//_eventDispatcher->pauseEventListenersForTarget(this);
}
void Fish::onFreezeResume()
{
	if (getFishType()==ArrangeFish)
	{
		for (auto child : fishes)
		{
			child->resume();
		}
	}
	else
	{
		resume();
		auto node = getChildByName("shader");
		if (node)
		{
			node->resume();
		}
	}
	
}

void Fish::onDead()
{
	if (getFishType()==ArrangeFish)
	{
		onFreezeResume();
		stopAllActions();
		runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create(CC_CALLBACK_0(Fish::removeself, this)), nullptr));
	}
	else
	{
		stopAllActions();
		unscheduleAllCallbacks();
		onFreezeResume();
		stopLockShoot();
		stopLightShoot();

		auto acName = String::createWithFormat("dead_%d", nUiID);
		auto ac = Repeat::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()), 1);
		auto ac1 = ac->clone();
		auto m_shadesprite = getChildByName("shader");
		if (m_shadesprite)
		{
			m_shadesprite->runAction(RepeatForever::create(ac));
		}
		runAction(RepeatForever::create(ac));
		runAction(Sequence::create(DelayTime::create(1.2f), CallFunc::create(CC_CALLBACK_0(Fish::removeself, this)), nullptr));

		if (getFishType() == GoldFish)
		{
			setScale(1.5f);
			runAction(RotateBy::create(1.2f, 180));
		}
		//声音
		if (fishID < 20)
		{
			/*Audio::getInstance()->playSound(CATCHSMALL);*/
		}
		else if (fishID >= 20 && fishID < 30)
		{
			/*Audio::getInstance()->playSound(CATCHMID);*/
		}
		else if (fishID >= 30 && fishID < 40)
		{
			/*Audio::getInstance()->playSound(CATCHBIG);*/
		}
		else if (fishID >= 40 && fishID < 50)
		{

		}
		else
		{
			Audio::getInstance()->playSound(CATCHGIRLFISH);
		}
	}

	
	
}


void Fish::ShadeResume()
{
	auto m_shadesprite = getChildByName("shader");
	if (m_shadesprite)
	{
		m_shadesprite->resume();
	}
	
}
void Fish::ShadePause()
{
	auto m_shadesprite = getChildByName("shader");
	if (m_shadesprite)
	{
		m_shadesprite->pause();
	}
}

void Fish::createDropOutAniByCoin(Point belongPos, int curMoney)
{
	auto node = Node::create(); 
	node->setAnchorPoint(Point::ANCHOR_MIDDLE);
	node->setPosition(getPositionX(), getPositionY() + 50);
	GameManage::getInstance()->getGuiLayer()->addChild(node);
	belongPos = node->convertToNodeSpace(belongPos);
	auto data = ConfigFish::getInstance()->getFishDropCoinData(getuiId());
	Sprite*sp;
	for (int i = 0; i < data.num;i++)
	{
		float diffX=30;
		float diffY=20;
		float orgY = 50;
		sp = Sprite::create();
		if (data.num>5)//两排
		{
			int perLine = data.num / 2;
			sp->setPosition(diffX*(i % perLine), orgY+diffY*(i / perLine));
		}
		else           //一排
		{
			sp->setPosition(diffX*(i % 5), orgY+diffY*(i / 5));
		}
		sp->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate(data.aniName.c_str())));
		sp->runAction(Sequence::create(DelayTime::create(0.1f*i), MoveBy::create(0.23f, Vec2(0, 86)), MoveBy::create(0.13f, Vec2(0, -86)), MoveBy::create(0.1f, Vec2(0, 27.5)), MoveBy::create(0.1f, Vec2(0, -27.5)), DelayTime::create(0.6f), MoveTo::create(0.16f, belongPos),RemoveSelf::create(1),nullptr));
		node->addChild(sp);
	}
	auto str = String::createWithFormat("%s%d", ":",curMoney);
	auto labelpath = String::createWithFormat("TTF%s.png", data.aniName.c_str());
	auto label = LabelAtlas::create(str->getCString(), labelpath->getCString(), 23, 34, '0');
	label->setAnchorPoint(Point::ZERO);
	label->setPosition(0, 0);
	node->addChild(label);
	label->setScale(0);
	label->runAction(ScaleTo::create(0.1, 1));

	node->runAction(Sequence::create(DelayTime::create(data.num*0.1f + 1.5f), RemoveSelf::create(), nullptr));
}

std::vector<OBBEX> Fish::getOBBs()
{
	std::vector<OBBEX> vec;
	for (auto var:obbdatas)
	{
		vec.push_back(OBBEX(convertToWorldSpace(var.leftBottom), convertToWorldSpace(var.rightBottom), convertToWorldSpace(var.rightTop), convertToWorldSpace(var.leftTop)));
	}
	return vec;
}



std::vector<OBB> Fish::getOBBByCocos()
{
	std::vector<OBB> vec;
	for (auto var:obbdatas)
	{
		AABB aabb = AABB(Vec3(var.leftBottom.x, var.leftBottom.y, 0), Vec3(var.rightTop.x, var.rightTop.y, 0));
		OBB obb = OBB(aabb);
		obb.transform(getNodeToWorldTransform());
		vec.push_back(obb);
	}
	return vec;
}

std::vector<Rect> Fish::getAABBBoxs()
{
	std::vector<Rect> vec;
	if (getFishType()==ArrangeFish)
	{
		for (auto child : fishes)
		{
			auto box = child->getBoundingBox();
			auto orgin = convertToWorldSpace(box.origin);
			box.setRect(orgin.x, orgin.y, box.size.width, box.size.height);
			vec.push_back(box);
		}
	}
	else
	{
		vec.push_back(getBoundingBox());
	}
	
	return vec;
}

FishZorder Fish::getFishZorder()
{
	if (fishID>=1&&fishID<=10)
	{
		return kZorderFishS;
	}
	else if (fishID >= 30 && fishID <= 37)
	{
		return kZorderFishM;
	}
	else if (fishID >= 40 && fishID <= 44)
	{
		return kZorderFishL;
	}
	else if (fishID >= 50 && fishID <= 100)
	{
		return kZorderFishXL;
	}
	else if (fishID >= 100 && fishID <= 300)
	{
		return kZorderFishM;
	}
	else
	{
		return kZorderFishM;
	}


}

void Fish::addLockBullet(Bullet*lockbullet)
{
	_lockBullets.push_back(lockbullet);
}
void Fish::removeAllBullet()
{
	for (auto var:_lockBullets)
	{
		if (var->getTag()!=-1)
		{
			var->stopLock();
		}
	}
}

void Fish::removeSingleBullet(Bullet *lockbullet)
{
	for (auto ite = _lockBullets.begin(); ite != _lockBullets.end();ite++)
	{
		if (*ite == lockbullet)
		{
			_lockBullets.erase(ite);
			return;

		}
	}
}

Vec2 Fish::getCentrenPos()
{
	if (getFishType()==ArrangeFish)
	{
		return centerPos;
	}
	
	switch (fishID)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 44:
	case 201:

		return getContentSize() / 2;
		break;
	case 37:
		return Vec2(160,getContentSize().height/2);
	case 40:
		return Vec2(100, getContentSize().height / 2);
	case 41:
		return Vec2(200, getContentSize().height / 2);
	case 42:
		return Vec2(107, getContentSize().height / 2);
	case 43:
		return Vec2(152, getContentSize().height / 2);
	case 50:
		return Vec2(225, getContentSize().height / 2);
	case 51:
		return Vec2(341, getContentSize().height / 2);
	case 52:
		return Vec2(247, getContentSize().height / 2);
	default:
		return getContentSize() / 2;
		break;
	}
	return getContentSize() / 2;
}