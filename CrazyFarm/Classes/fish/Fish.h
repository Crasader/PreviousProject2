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
	int speed;//����ƶ��ٶ�
	int fishType;//�������
	int experience;//��ľ���ֵ
	int fishGold;//��Ľ�Ǯ
	int BonusPoorGold;//����صĽ��
	float  rotation;//��ת�ĽǶ�
	int getFishGoldByType(int type);
	int getFishExperienceByType(int type);
	float getFishSpeedByType(int type);
	void initFishAnim(int fishType);
	void moveFishStraight(float dt);//ֱ���ƶ�
	void moveFishCircle(float dt);//Բ���˶�
	void moveFishRandomStraight(float dt);//���ֱ���˶�
	void moveFishRandomStraightForBigFish(float dt);//�������ֱ���˶�
	void moveFishRandomCurve(float dt);//��������˶�
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
	//·��
	Route m_Route;
	//��Ӱ
	std::vector<ShadeData> shadedatas;
	Vector<Sprite*>  m_shadesprites;
	FishShader* m_shadesprite = nullptr;
	void ShadeUpdata(float dt);
	void ShadeResume();
	void ShadePause();
};

#endif