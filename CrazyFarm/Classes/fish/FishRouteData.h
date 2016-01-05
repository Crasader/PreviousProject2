#pragma once
#include "cocos2d.h"

using namespace cocos2d;


struct RoutePoint  //鱼的运行轨迹点
{
	RoutePoint* next;
	float time;
	float delay;
	bool isRepeat;  //是否循环
	int moveState;  //1直线 2圆 3帧动画
	//直线配置
	PointArray * pointarray;
	//圆配置
	Vec2 centrePos;
	int cicrleTime;
	//动画配置
	std::string aniName;
	
};

struct Route  //运行轨迹   
{
	RoutePoint* head;
};


class FishRouteData{
public:
	static FishRouteData* getInstance();
	static void destroyInstance();
	bool loadRouteConfig();
	Route getRouteBytag(int tag); 
private:
	std::map<int,Route> map_TagToRoute;
	static FishRouteData* _pInstance;

};