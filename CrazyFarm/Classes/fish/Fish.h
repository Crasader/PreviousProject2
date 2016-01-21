#ifndef __FISH_H__
#define __FISH_H__
#include "cocos2d.h"
#include "utill/CircleBy.h"
#include "config/ConfigFish.h"
#include "fish/FishRouteData.h"
using namespace cocos2d;

#define FISHTYPE_1 1
#define FISHTYPE_2 2
#define FISHTYPE_3 3
#define FISHTYPE_4 4
#define FISHTYPE_5 5
#define FISHTYPE_6 6
#define FISHTYPE_7 7
#define FISHTYPE_8 8


enum swimDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};


using namespace std;

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
	void addShader();
	void removeself();		
	void onDead();

protected:
	
	void update(float);
	float grabProbability;
	int speed;//����ƶ��ٶ�
	int fishType;//�������
	int experience;//��ľ���ֵ
	int fishGold;//��Ľ�Ǯ
	int BonusPoorGold;//����صĽ��
	float  rotation;//��ת�ĽǶ�
	string resoureName;//��Դ����
	string getSrcByType(int type);
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
	Sprite* m_shadesprite = nullptr;
	void ShadeUpdata(float dt);
	void ShadeResume();
	void ShadePause();
};

#endif