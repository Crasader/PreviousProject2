#include "fish/Fish.h"
#include "fish/FishAniMannage.h"
#include "utill/CircleMoveTo.h"
bool Fish::init(){
	if (!Sprite::init())
	{
		return false;
	}
	scheduleUpdate();
	return true;
}

void Fish::initFish(int fishType){
	auto fishdata = ConfigFish::getInstance()->getFish(fishType);
	fishGold = fishdata.baseReward;
	this->grabProbability = fishdata.probability;
	this->fishType = fishType;
	this->speed = getFishSpeedByType(fishType);;
	this->experience = getFishExperienceByType(fishType);
	this->resoureName = getSrcByType(fishType);///2_02.png
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
	return 100;
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
	default:
	{
		schedule(schedule_selector(Fish::moveFishRandomStraight), Director::getInstance()->getAnimationInterval(), CC_REPEAT_FOREVER, 0);
	}

		
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
	
	float randnum = (rand() % 4+8)/10.0f;

	Point nextPos = getRandomPostion(dt*speed*randnum, this->getDirection(), fMoveAngle);
	auto move = MoveBy::create(dt, nextPos);	
	runAction(move);
	/*update(dt);*/
	setRotation(360 - fMoveAngle);
	/*runAction(RotateTo::create(0.1, 360-angle));*/
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

Point Fish::getRandomPostion(float speed, swimDirection direction, float &angle)
{
	float diffAngle = (rand() % 70 - 30) / 100.0f;
	angle += diffAngle;

	/*switch (direction)
	{
	case DOWN:
	angle = rand() % 5+225;
	break;
	case LEFT:
	angle = rand() % 90 + 135;
	break;
	case RIGHT:
	angle = rand() % 90 - 45;
	break;
	case UP:
	angle = rand() % 90+45 ;
	break;
	default:
	return Vec2(0, 0);
	}*/
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
		switch (p->moveState)
		{
		case 1:
		{	
			p->pointarray->retain();
			acArray->pushBack(CardinalSplineBy::create(p->time, p->pointarray, 1));
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
	if (RepetActionArray.size() > 0)
	{
		this->runAction(Sequence::create(delay, CallFunc::create([&](){
		runAction(RepeatForever::create(Sequence::create(RepetActionArray)));
		}), nullptr));

	}
}

bool Fish::checkOutBorder(){
	return false;
}

Sprite* Fish::getRectSprite(){
	return image;
}

int Fish::getFishType() {
    return fishType;
}


