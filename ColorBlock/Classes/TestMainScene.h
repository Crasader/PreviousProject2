#pragma once
#include "cocos2d.h"
#include "Box2D/Box2D.h"                                                  


#define PTM_RATIO 32                                                      


class HelloWorld : public cocos2d::Layer
{
	b2World* world;


public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	virtual ~HelloWorld();
	virtual void update(float dt);



	CREATE_FUNC(HelloWorld);

	void initPhysics();
	void addNewSpriteAtPosition(cocos2d::Vec2 p);


};