#pragma once


#include "cocos2d.h"
using namespace cocos2d;



class LoadingScene : public Layer
{
public:
	CREATE_FUNC(LoadingScene);
	static cocos2d::Scene* createScene();

	virtual bool init();

	void load();
	void login();
	void loadRes();
	void loadedCallBack();
	//void update(float delta);

	void addPlistPngRes(std::string filename);
private:

};


