#include "fish/Fish.h"
#include "fish/FishAniMannage.h"
#include "utill/CircleMoveTo.h"
#include "FishManage.h"
#include "FishAniMannage.h"
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
	fishGold = fishdata.baseReward;
	this->grabProbability = fishdata.probability;
	this->fishType = fishType;
	this->speed = fishdata.move_speed;
	this->experience = getFishExperienceByType(fishType);
	this->resoureName = getSrcByType(fishType);///2_02.png
	BonusPoorGold = fishdata.bonus_pool_reward;
	setuiId(fishdata.uiId);
	initFishAnim(fishdata.uiId);
	
	
}

void Fish::initFishAnim(int fishType){
	initWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(fishType));

	auto acName = String::createWithFormat("swim_%d", fishType);
	auto ac = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));
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

string Fish::getSrcByType(int type){
	/*return FishAniMannage::getInstance()->getSpriteById(type);*/
	switch (type)
	{
	case FISHTYPE_1:
		return "0_0";
	case FISHTYPE_2:
		return "2_0";
	case FISHTYPE_3:
		return "5_0";
	case FISHTYPE_4:
		return "8_0";
	case FISHTYPE_5:
		return "10_0";
	case FISHTYPE_6:
		return "11_0";
	case FISHTYPE_7:
		return "14_0";
	case FISHTYPE_8:
		return "16_0";
	default:
		return "0_0";
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
		acNoRepeat->setTag(888);
		this->runAction(acNoRepeat);
		delay = DelayTime::create(acNoRepeat->getDuration());
	}
	else
	{
		delay = DelayTime::create(0);
	}
	this->runAction(Sequence::create(delay, RemoveSelf::create(1), CallFunc::create([&]{FishManage::getInstance()->removeFish(this,0); }), nullptr));
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


	auto acName = String::createWithFormat("swim_%d", fishType);
	auto ac = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));

	m_shadesprite = Sprite::createWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(fishType));
	m_shadesprite->setPosition(getPositionX() + getContentSize().width*0.15, getPositionY() + getContentSize().height*-0.15);
	getParent()->addChild(m_shadesprite, 4);
	m_shadesprite->setColor(Color3B::BLACK);
	m_shadesprite->setOpacity(GLubyte(150));
	m_shadesprite->runAction(ac);
	schedule(schedule_selector(Fish::ShadeUpdata),0.0f,CC_REPEAT_FOREVER,0.0F);
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
	m_shadesprite->removeFromParentAndCleanup(1);
	removeFromParentAndCleanup(1);
}


void Fish::onDead()
{
	stopAllActions();
	auto acName = String::createWithFormat("dead_%d", fishType);
	auto ac = Repeat::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()),1);
	auto ac1 = ac->clone();
	m_shadesprite->runAction(ac1);
	runAction(Sequence::create(ac, CallFunc::create(CC_CALLBACK_0(Fish::removeself,this)),nullptr));
}
