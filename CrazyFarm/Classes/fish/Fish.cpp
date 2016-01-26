#include "fish/Fish.h"
#include "fish/FishAniMannage.h"
#include "utill/CircleMoveTo.h"
#include "FishManage.h"
#include "FishAniMannage.h"
#include "utill/AnimationUtil.h"
#include"utill/FunUtil.h"
#include "utill/Audio.h"
#include "Config/ConfigFishCollisionRange.h"

enum 
{
	kTagAcNormal = 10
};
bool Fish::init(){
	if (!Sprite::init())
	{
		return false;
	}
	scheduleUpdate();
	setisAutoRemove(true);
	
	return true;
}

void Fish::initFish(int fishType){
	auto fishdata = ConfigFish::getInstance()->getFish(fishType);
	fishGold = getintRandonNumByAtoB(fishdata.baseRewardStart, fishdata.baseRewardEnd);
	this->grabProbability = fishdata.probability;
	this->fishType = fishType;
	this->speed = fishdata.move_speed;
	this->experience = getFishExperienceByType(fishType);
	BonusPoorGold = fishdata.bonus_pool_reward;
	setuiId(fishdata.uiId);
	initFishAnim(fishdata.uiId);
	figures = ConfigFishCollisionRange::getInstance()->getFishFigures(fishdata.uiId);
	LogEventFish::getInstance()->addFishCreateTimes(fishType);
}

void Fish::initFishAnim(int fishType){
	initWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(fishType));

	auto acName = String::createWithFormat("swim_%d", fishType);
	auto ac = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
	ac->setTag(kTagAcNormal);
	runAction(ac);

	
	

}
void Fish::update(float dt)
{

	
	if (getPosition().distance(LastPos) > 0)
	{
		auto raroAngle = 1.5*3.1415926f - (getPosition() - LastPos).getAngle();
		setRotation(CC_RADIANS_TO_DEGREES(raroAngle)+90);
		LastPos = getPosition();

	}
}



int Fish::getFishGoldByType(int type){
	//TODO
	return 0;
}


int Fish::getFishExperienceByType(int type){
	//TODO
	return ConfigFish::getInstance()->getFish(type).exp;
}


float Fish::getFishSpeedByType(int type){
	return 80;
}

void Fish::move(int moveType){
	//选择鱼的移动模式
	unscheduleUpdate();
	switch (moveType)
	{
	case 1:
		schedule(schedule_selector(Fish::moveFishStraight), 0, CC_REPEAT_FOREVER, 0);
		break;
	case 2:
		schedule(schedule_selector(Fish::moveFishCircle), 0, 0, 0);
		break;
	case 3:
		schedule(schedule_selector(Fish::moveFishRandomStraight), Director::getInstance()->getAnimationInterval(), CC_REPEAT_FOREVER, 0);	
		break;
	case 4:
		schedule(schedule_selector(Fish::moveFishRandomStraightForBigFish), 5, CC_REPEAT_FOREVER, 0);
		break;
	}
}

void Fish::moveFishStraight(float dt){
	//TODO 鱼的直线移动
	Point nextPos = getNextPostion(getPosition(), dt*speed, this->getRotation());
	auto move = MoveBy::create(dt, nextPos);
	this->runAction(move);
}

void Fish::moveFishCircle(float dt){
	//TODO 鱼的圆形移动
	Point circlePoint = this->getPosition();
	auto cirlce = CircleBy::create(circlePoint, 2, 360, 10, true);
	this->runAction(cirlce);
}

void Fish::moveFishRandomStraight(float dt){
	//TOOD 鱼的随机直线运动
	


	Point nextPos = getRandomPostion(speed,dt, fMoveAngle);
	auto move = MoveBy::create(dt, nextPos);	
	runAction(move);
	setRotation(360 - fMoveAngle);
}

void Fish::moveFishRandomStraightForBigFish(float dt){
	//TOOD 鱼的随机直线运动


	Point nextPos = getRandomPostionForBigFish(speed, dt, fMoveAngle);
	auto move = MoveBy::create(dt, nextPos);
	runAction(Spawn::create(move,RotateTo::create(dt,360-fMoveAngle),nullptr));
}



void Fish::moveFishRandomCurve(float dt)
{
	float angle = 0;
	Point nextPos = getRandomPostion(dt*speed, this->getDirection(), angle);
	auto move = MoveBy::create(dt, nextPos);
	this->runAction(EaseSineOut::create(move));

	runAction(RotateTo::create(0.1, 360 - angle));
}

Point Fish::getNextPostion(Point pos, float speed, float degree){
	//TODO 完善鱼的直线移动
	if (degree < 0){
		degree += 360;
	}
	pause();
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
	float diffAngle = (rand_0_1() *6.0f - 3.0f)*3;
	angle += diffAngle;
	return Vec2(speed*cos(CC_DEGREES_TO_RADIANS(angle)), speed*sin(CC_DEGREES_TO_RADIANS(angle)));

}
void Fish::setRoute(int routeTag)
{
	m_Route = FishRouteData::getInstance()->getRouteBytag(routeTag);

	auto actionArray = Vector<FiniteTimeAction*>();

	RepetActionArray = Vector<FiniteTimeAction*>();
	
	RoutePoint* p = m_Route.head;
	while (p != nullptr)
	{
		Vector<FiniteTimeAction*> *acArray;
		if (p->isRepeat)
		{
			acArray = &RepetActionArray;
		}
		else
		{
			acArray = &actionArray;
		}
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
			auto str = String::createWithFormat("%s_%d", p->aniName.c_str(), fishType);
			acArray->pushBack(FishAniMannage::getInstance()->getAnimate(str->getCString()));
		}
		break;
		default:
			break;
		}

		p = p->next;
	}
	DelayTime*delay;
	if (actionArray.size()>0)
	{
		auto acNoRepeat = Sequence::create(actionArray);
		acNoRepeat->setTag(kTagAcNormal);
		this->runAction(acNoRepeat);
		delay = DelayTime::create(acNoRepeat->getDuration());
	}
	else
	{
		delay = DelayTime::create(0);
	}
	auto ac = Sequence::create(delay, RemoveSelf::create(1), CallFunc::create([&]{FishManage::getInstance()->removeFish(this, 0); }), nullptr);
	ac->setTag(kTagAcNormal);
	this->runAction(ac);
	if (RepetActionArray.size() > 0)
	{
		this->runAction(Sequence::create(delay, CallFunc::create([&](){
		runAction(RepeatForever::create(Sequence::create(RepetActionArray)));
		}), nullptr));

	}
}


void Fish::setMonentEightRoute(int routeTag)
{
	auto momentEightRoute = MonmetEightRoutedata::getInstance()->getRouteBytag(routeTag);

	setPosition(momentEightRoute.startPos);

	auto actionArray = Vector<FiniteTimeAction*>();

	RepetActionArray = Vector<FiniteTimeAction*>();

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
			auto str = String::createWithFormat("%s_%d", p->aniName.c_str(), fishType);
			acArray->pushBack(FishAniMannage::getInstance()->getAnimate(str->getCString()));
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
	DelayTime*delay;
	if (actionArray.size() > 0)
	{
		auto acNoRepeat = Sequence::create(actionArray);
		acNoRepeat->setTag(888);
		this->runAction(acNoRepeat);
		delay = DelayTime::create(acNoRepeat->getDuration());
	}
	else
	{
		delay = DelayTime::create(0);
	}
	this->runAction(Sequence::create(delay, RemoveSelf::create(1), CallFunc::create([&]{FishManage::getInstance()->removeFish(this,0); }), nullptr));

}


void Fish::addShader()
{
	m_shadesprite = FishShader::createShader(this);


	
}
void Fish::ShadeUpdata(float dt)
{
	if (m_shadesprite!=nullptr)
	{
		m_shadesprite->setPosition(getPositionX() + getContentSize().width*0.15, getPositionY() + getContentSize().height*-0.15);
		m_shadesprite->setRotation(getRotation());
	}
}



Sprite* Fish::getRectSprite(){
	return image;
}

int Fish::getFishType() {
    return fishType;
}


void Fish::removeself()
{
	
	if (m_shadesprite)
	{
		m_shadesprite->removeFromParentAndCleanup(1);
	}
	removeFromParentAndCleanup(1);
}

void Fish::onHeart()
{
	auto action = Sequence::create(
		TintTo::create(0.1f, 255, 0, 0),
		TintTo::create(0.1f, 255, 255, 255),
		nullptr);
	runAction(action);
}
void Fish::onFreeze()
{
	//冻结时候无受击动画处理
	//_scheduler->pauseTarget(this);
	//stopAllActionsByTag(kTagAcNormal);
	//_eventDispatcher->pauseEventListenersForTarget(this);
}
void Fish::onFreezeResume()
{

	//_scheduler->pauseTarget(this);
	//pauseAllActionsByTag(kTagAcNormal);
	//_eventDispatcher->pauseEventListenersForTarget(this);
}

void Fish::onDead()
{
	stopAllActions();
	unscheduleAllCallbacks();
	auto acName = String::createWithFormat("dead_%d", nUiID);
	auto ac = Repeat::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()),1);
	m_shadesprite->onDead();
	runAction(RepeatForever::create(ac));
	runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(Fish::removeself,this)),nullptr));
	//声音
	if (fishType < 20)
	{
		/*Audio::getInstance()->playSound(CATCHSMALL);*/
	}
	else if (fishType >= 20 && fishType<30)
	{
		/*Audio::getInstance()->playSound(CATCHMID);*/
	}
	else if (fishType >= 30 && fishType<40)
	{
		/*Audio::getInstance()->playSound(CATCHBIG);*/
	}
	else if (fishType >= 40 && fishType<50)
	{
		Audio::getInstance()->playSound(CATCHGOLD);
	}
	else
	{
		Audio::getInstance()->playSound(CATCHGIRLFISH);
	}
	
}


void Fish::ShadeResume()
{

	if (m_shadesprite)
	{
		m_shadesprite->resume();
	}
	
}
void Fish::ShadePause()
{
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
	getParent()->addChild(node);
	belongPos = node->convertToNodeSpace(belongPos);
	auto data = ConfigFish::getInstance()->getFishDropCoinData(ConfigFish::getInstance()->getFish(fishType).uiId);
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
	auto str = String::createWithFormat(":%d", curMoney);
	auto labelpath = String::createWithFormat("TTF%s.png", data.aniName.c_str());
	auto label = LabelAtlas::create(str->getCString(), labelpath->getCString(), 23, 34, '0');
	label->setAnchorPoint(Point::ZERO);
	label->setPosition(0, 0);
	node->addChild(label);
	label->setScale(0);
	label->runAction(ScaleTo::create(0.1, 1));

	node->runAction(Sequence::create(DelayTime::create(data.num*0.1f + 1.5f), RemoveSelf::create(), nullptr));
}

std::vector<CFigure*> Fish::getBoundingFigures()
{
	std::vector<CFigure*> vec;
	for (auto var:figures)
	{
		vec.push_back(var->ApplyAffineTransform(var,getNodeToParentAffineTransform()));
	}
	return vec;
	
}

