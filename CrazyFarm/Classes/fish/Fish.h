#ifndef __FISH_H__
#define __FISH_H__
#include "cocos2d.h"
#include "utill/CircleBy.h"
#include "config/ConfigFish.h"
#include "fish/FishRouteData.h"
#include "fish/FishShader.h"
using namespace cocos2d;

enum swimDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};
struct ShadeData
{
	int uiid;
	Point pos;
	ShadeData(int id, Point p){ uiid = id; pos = p; };
};


class FishShader;
class Fish :public Sprite{
public:
	virtual bool init();
	CREATE_FUNC(Fish);
	virtual void initFish(int fishType);
	void move(int moveType);
	void setRoute(int routeTag);
	void setMonentEightRoute(int monentEightrouteTag);
	Sprite* getRectSprite();
	int getFishGold(){ return fishGold; }
	float getGrabProbability(){ return grabProbability; }
    int getFishType();
	int getFishExperience(){ return experience; };
	int getBounsPoorGold(){ return BonusPoorGold; };
	virtual void addShader();
	void removeself();		
	virtual void onDead();
	void onHeart();
	void onFreeze();
	void onFreezeResume();
	void createDropOutAniByCoin(Point belongPos,int curMoney);
protected:
	
	void update(float);
	float grabProbability;
	int speed;//鱼的移动速度
	int fishType;//鱼的类型
	int experience;//鱼的经验值
	int fishGold;//鱼的金钱
	int BonusPoorGold;//奖金池的金币
	float  rotation;//旋转的角度
	int getFishGoldByType(int type);
	int getFishExperienceByType(int type);
	float getFishSpeedByType(int type);
	void initFishAnim(int fishType);
	void moveFishStraight(float dt);//直线移动
	void moveFishCircle(float dt);//圆周运动
	void moveFishRandomStraight(float dt);//随机直线运动
	void moveFishRandomStraightForBigFish(float dt);//大鱼随机直线运动
	void moveFishRandomCurve(float dt);//随机曲线运动
	Point getNextPostion(Point pos,float speed,float degree);
	Point getRandomPostion(float speed, float dt,float &angle);
	Point getRandomPostionForBigFish(float speed, float dt, float &angle);
	
	Sprite* image;

	CC_SYNTHESIZE(swimDirection, nDirection, Direction);
	Point LastPos;

	CC_SYNTHESIZE(float, fMoveAngle, MoveAngle);
	CC_SYNTHESIZE(int, nUiID, uiId);
	CC_SYNTHESIZE(bool, bIsAutoRemove, isAutoRemove);
	Vector<FiniteTimeAction*> RepetActionArray;
	//路径
	Route m_Route;
	//阴影
	std::vector<ShadeData> shadedatas;
	Vector<Sprite*>  m_shadesprites;
	FishShader* m_shadesprite = nullptr;
	void ShadeUpdata(float dt);
	void ShadeResume();
	void ShadePause();
};

#endif