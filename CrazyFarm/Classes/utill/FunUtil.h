#pragma once
#include "cocos2d.h"
#include "fish/Fish.h"
#include "AnimationUtil.h"
#include "data/GameData.h"
#include "utill/OBB.h"
USING_NS_CC;

//获得随机数By随机因子，默认随机时间因子
int getRand(unsigned int _Seed = time(nullptr));
//碰撞检测
bool collision(Sprite*spA, Sprite*spB);
bool collision(Rect rectA, Rect rectB);
float  getAngleByPos(Vec2 pos);
Vec2 CalculateDiffMarginPos(Vec2 pos,float diff);
float getRandonNumByAtoB(float A, float B);
int getCurrencyRankByRange(int startRank, int endRank, int startValue, int endValue, int curValue);

std::string SpliceDataForPostHttp(std::vector<std::string> strs);
std::string  SpliceDataForPostHttp(std::string str1, ...);

std::string NewAtoI(int num);
std::string NewAtoI(long num);

int getintRandonNumByAtoB(int A, int B, int Interval=1);

std::string myWrap(std::string str, int length);

int getRandValueInVec(std::vector<int> vec);


Action* getForeverAcByNameAndInterval(const char* name,float interval);

float getTurretRotation(Point start_pos, Point pos);
unsigned long getCurrentTime();
bool line_rect_intersection(Point start_p, Point end_p, Rect rect);
template<typename Fwd>
void upsetVector(std::vector<Fwd> &vec)
{
	int n = vec.size();
	int T = 10;
	int temp,i,j;
	while (T--)
	{
		i = getRand() % n;
		j = getRand() % n;
		temp = vec[i];
		vec[i] = vec[j];
		vec[j] = temp;
	}
}


template<typename Fkd>
Fkd getRandValueInVector(Vector<Fkd> &vec)
{
	return vec.at(getRand() % vec.size());
}

