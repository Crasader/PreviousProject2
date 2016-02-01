#pragma once
#include "cocos2d.h"
#include "fish/Fish.h"
#include "AnimationUtil.h"
USING_NS_CC;

//Åö×²¼ì²â
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